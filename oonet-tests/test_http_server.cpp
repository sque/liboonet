#include "test_http_server.hpp"
#include <oonet/http/server.hpp>

namespace oonet
{
	namespace test
	{
		test_http_server test_http_server_inst;

		// Mini HTTPServer
		class MyHTTPServer
			:public http::server
		{
		public:
			virtual ~MyHTTPServer()
			{	initialize_destruction();
			}


			handlers_pool_type & pool()
			{	return handlers_pool();	}

		protected:
			virtual http::response on_url_request(const http::request & full_request, const socket_address_inet & client_addr)
			{
				http::response tmpResponse;
				tmpResponse.body() = binary_data("<HTML><BODY>Dont know how to handle this url!</BODY></HTML>");

				return tmpResponse;
			}

			virtual void parametrize_listen_socket(socket & l_sock)
			{
				int reuse = 1;
				l_sock.set_option(SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
			};

		};

		bool test_http_server::TestCtor::operator()()
		{	MyHTTPServer myServer;
			return true;
		}

		bool test_http_server::TestStart::operator()()
		{	MyHTTPServer myServer;

			myServer.start_listen(socket_address_inet(host_inet::ANY, port_inet(44130)), 100);
			return true;
		}

		bool test_http_server::TestDoubleStart::operator()()
		{	MyHTTPServer myServer;

			myServer.start_listen(socket_address_inet(host_inet::ANY, port_inet(44131)), 100);
			myServer.start_listen(socket_address_inet(host_inet::ANY, port_inet(44132)), 100);
			return true;
		}

		bool test_http_server::TestStartRecovery::operator()()
		{	MyHTTPServer myServer;

			if (myServer.listening())
				return false;

			myServer.start_listen(socket_address_inet(host_inet::LOCALHOST, port_inet(44132)), 10);

			if (!myServer.listening())
				return false;

			try
			{myServer.start_listen(socket_address_inet(host_inet::LOCALHOST, port_inet(44133)), 10);}
			catch(ExceptionAlreadyConnected & e){ e = e; }

			if (!myServer.listening())
				return false;

			if (myServer.pool().size() != 0)
				return false;

			return true;
		}

		bool test_http_server::TestStop::operator()()
		{	MyHTTPServer myServer;

			if (myServer.listening())
				return false;

			myServer.start_listen(socket_address_inet(host_inet::LOCALHOST, port_inet(44134)), 10);

			if (!myServer.listening())
				return false;

			try
			{
				myServer.start_listen(socket_address_inet(host_inet::LOCALHOST, port_inet(44135)), 10);
			}
			catch(ExceptionAlreadyConnected & e)
			{ e = e; }

			if (!myServer.listening())
				return false;

			if (myServer.pool().size() != 0)
				return false;

			// Stop server
			myServer.stop_listen();

			if (myServer.listening())
				return false;

			// Start again
			myServer.start_listen(socket_address_inet(host_inet::LOCALHOST, port_inet(44136)), 10);

			if (!myServer.listening())
				return false;

			return true;
		}

		bool test_http_server::TestStopWrong1::operator()()
		{	MyHTTPServer myServer;

			if (myServer.listening())
				return false;

			myServer.start_listen(socket_address_inet(host_inet::LOCALHOST, port_inet(44137)), 10);

			if (!myServer.listening())
				return false;

			if (myServer.pool().size() != 0)
				return false;

			// Stop server
			myServer.stop_listen();

			if (myServer.listening())
				return false;

			// Stop again
			myServer.stop_listen();

			if (myServer.listening())
				return false;

			return true;
		}


		bool test_http_server::TestStopWrong2::operator()()
		{	MyHTTPServer myServer;

			if (myServer.listening())
				return false;

			// Stop immediatly
			myServer.stop_listen();

			if (myServer.listening())
				return false;

			return true;
		}


		bool test_http_server::TestStopCleanup::operator()()
		{	MyHTTPServer myServer;
			socket mHttpClient(socket::FAMILY_INET, socket::TYPE_STREAM, socket::PROTO_DEFAULT);
			binary_data RespShouldBe = binary_data("HTTP/1.1 200 OK\r\nContent-Length: 59\r\n\r\n<HTML><BODY>Dont know how to handle this url!</BODY></HTML>");;
			http::request myRequest;

			// Format my request
			myRequest.headers().insert("Host", "www.google.com");
			if (myServer.listening())
				return false;

			myServer.start_listen(socket_address_inet(host_inet::LOCALHOST, port_inet(44138)), 10);

			if (!myServer.listening())
				return false;

			// Connect client
			mHttpClient.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(44138)));

			// Send some data
			mHttpClient.send(myRequest.render());

			// Wait to get back same data
			if (mHttpClient.receive(1000) != RespShouldBe)
				return false;

			// Get count of clients
			if (myServer.pool().size() != 1)
				return false;

			// Check if client is connected
			if (! myServer.pool().front()->connected())
				return false;

			// Stop server
			myServer.stop_listen();

			if (myServer.listening())
				return false;

			// Get count of clients
			if (myServer.pool().size() != 1)
				return false;
			return true;
		}

		bool test_http_server::TestDCInvalidClients::operator()()
		{	MyHTTPServer myServer;
			socket mHttpClient(socket::FAMILY_INET, socket::TYPE_STREAM, socket::PROTO_DEFAULT);
			binary_data RespShouldBe = binary_data("HTTP/1.1 200 OK\r\nContent-Length: 59\r\n\r\n<HTML><BODY>Dont know how to handle this url!</BODY></HTML>");;
			binary_data invalidRequest = binary_data("sfads\r\n\r\n\nasf");

			if (myServer.listening())
				return false;

			myServer.start_listen(socket_address_inet(host_inet::LOCALHOST, port_inet(44140)), 10);

			if (!myServer.listening())
				return false;

			// Connect client
			mHttpClient.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(44140)));

			// Send some data
			mHttpClient.send(invalidRequest);

			// Wait to get back same data
			try
			{
				if (mHttpClient.receive(1000) != RespShouldBe)
					return false;
				return false;
			}
			catch(exception)
			{	return true;	}
			return false;

		}

		bool test_http_server::TestPureVirtuals1::operator()()
		{
			MyHTTPServer * pServer;
			socket mHttpClient(socket::FAMILY_INET, socket::TYPE_STREAM, socket::PROTO_DEFAULT);
			binary_data RespShouldBe = binary_data("HTTP/1.1 200 OK\r\nContent-Length: 59\r\n\r\n<HTML><BODY>Dont know how to handle this url!</BODY></HTML>");;

			http::request myRequest;
			// Format my request
			myRequest.headers().insert("Host", "www.google.com");
			binary_data dRequest = myRequest.render();

			for(long i = 0;i < 1000;i++)
			{
				pServer = new MyHTTPServer();
				pServer->start_listen(socket_address_inet(host_inet::LOCALHOST, port_inet(44142)), 10);
				mHttpClient = socket(socket::FAMILY_INET, socket::TYPE_STREAM, socket::PROTO_DEFAULT);
				// Connect client
				mHttpClient.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(44142)));

				// Send some invalid data
				mHttpClient.send(dRequest);

				// Delete it in once
				delete pServer;
			}

			return true;
		}

		bool test_http_server::TestDoS1::operator()()
		{	MyHTTPServer myServer;
			socket mHttpClient(socket::FAMILY_INET, socket::TYPE_STREAM, socket::PROTO_DEFAULT);
			binary_data RespShouldBe = binary_data("HTTP/1.1 200 OK\r\nContent-Length: 59\r\n\r\n<HTML><BODY>Dont know how to handle this url!</BODY></HTML>");;
			binary_data invalidRequest = binary_data("sfads\r\n\r\n\nasf");
			long i = 0;

			if (myServer.listening())
				return false;

			myServer.start_listen(socket_address_inet(host_inet::LOCALHOST, port_inet(44143)), 1000);

			if (!myServer.listening())
				return false;

			try
			{
				for(i = 0;i < 1000;i++)
				{
					//printf("%d\n", i);
					mHttpClient = socket(socket::FAMILY_INET, socket::TYPE_STREAM, socket::PROTO_DEFAULT);
					// Connect client
					mHttpClient.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(44143)));

					// Send some invalid data
					mHttpClient.send(invalidRequest);

					mHttpClient.shutdown();
					mHttpClient = socket();

				}
			}
			catch(exception & e)
			{   printf("\nException: %s\n", e.get_report().c_str());
				return false;
			}

			return true;
		}
	}	// !test namespace
};	// !oonet namespace
