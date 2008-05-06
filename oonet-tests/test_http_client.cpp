#include "test_http_client.hpp"
#include <oonet/http/client.hpp>
#include <oonet/http/server.hpp>

namespace oonet
{
	namespace test
	{
		test_http_client test_http_client_inst;

		// Mini echo server
		class MiniHTTPServer
			: public mt::thread
		{
		public:
			binary_data ReceivedData;
			mt::semaphore semArrived;
			socket lSocket;
			bool bRunning;
			exception LastExc;
			bool bException;
			binary_data myResp;
			long wt_after_send;

			MiniHTTPServer(const binary_data & resp, long wt_after = 0)
				:lSocket(socket::FAMILY_INET,socket::TYPE_STREAM, socket::PROTO_DEFAULT),
				bRunning(false),
				LastExc(_T("no fike"), -1, _T("123123"), _T("!unknown")),
				myResp(resp),
				wt_after_send(wt_after)
			{
				bException = false;
				int reuse = 1;
				lSocket.set_option(SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
				lSocket.bind(socket_address_inet(host_inet::LOCALHOST, port_inet(55123)));
			}

			~MiniHTTPServer()
			{
				lSocket.shutdown();
				lSocket = socket();
				join(mt::Infinity);

			}

			virtual void operator()()
			{	binary_data data;
				http::request myReq;

				bRunning = true;
				try
				{
					lSocket.listen(2);
					socket clSocket = lSocket.accept();

					// Wait for data
					while(1)
					{
						try
						{
							data += clSocket.receive(1000);
							myReq.parse(data);
						}
						catch(http::ExceptionIncomplete)
						{	continue;
						}
						break;
					}

					// Wait a bit to reproduce lag
					mt::thread::sleep(1000);

					// Send back reply
					clSocket.send(myResp);

					if (wt_after_send != 0)
						mt::thread::sleep(wt_after_send);
					// Raise semaphore
					semArrived.post();

					clSocket.shutdown();
					clSocket = socket();
				}
				catch(exception & e)
				{	LastExc = e;
					bException = true;
					semArrived.post();
				}
				bRunning = false;
			}

			// Exit server
			void StopS()
			{	lSocket.shutdown();
				lSocket = socket();
				join(mt::Infinity);
			}
		};

		// Mini echo server
		class MiniDCServer
			: public mt::thread
		{
		public:
			socket lSocket;

			MiniDCServer()
				:lSocket(socket::FAMILY_INET,socket::TYPE_STREAM, socket::PROTO_DEFAULT)
			{
				int reuse = 1;
				lSocket.set_option(SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
				lSocket.bind(socket_address_inet(host_inet::LOCALHOST, port_inet(55123)));
			}

			~MiniDCServer()
			{
				lSocket.shutdown();
				lSocket = socket();
				join(mt::Infinity);

			}

			virtual void operator()()
			{
				try
				{
					lSocket.listen(2);
					socket clSocket = lSocket.accept();

					// dc client
					sleep(100);
					clSocket.shutdown();
					clSocket = socket();
				}
				catch(exception)
				{}
			}

			// Exit server
			void StopS()
			{	lSocket.shutdown();
				lSocket = socket();
				join(mt::Infinity);
			}
		};

		class HTTPServer
			: public http::server
		{
		public:
			void parametrize_listen_socket(socket & l_sock)
			{
				int reuse = 1;
				l_sock.set_option(SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
			}

			http::response std_resp;
			http::response on_url_request(const http::request & full_request, const socket_address_inet & client_addr)
			{
				return std_resp;
			}
		};

		bool test_http_client::TestCtor::operator()()
		{	http::client mClient;

			if (mClient.connected())
				return false;

			return true;
		}

		bool test_http_client::TestCtorWrong::operator()()
		{	http::client mClient(socket_address_inet(host_inet::LOCALHOST, port_inet(44243)));

			if (mClient.connected())
				return false;
			return false;
		}

		bool test_http_client::TestConnect::operator()()
		{	http::client mClient;

			mClient.connect(socket_address_inet(host_resolver("www.google.com"), port_inet(80)));

			if (!mClient.connected())
				return false;
			return true;
		}

		bool test_http_client::TestConnectConnected::operator()()
		{	http::client mClient;

			// Connect to server
			mClient.connect(socket_address_inet(host_resolver("www.google.com"), port_inet(80)));

			// Check if it is connected
			if (!mClient.connected())
				return false;

			// Connet to another server
			mClient.connect(socket_address_inet(host_resolver("www.in.gr"), port_inet(80)));

			// Check if it is connected
			if (!mClient.connected())
				return false;

			return true;
		}

		bool test_http_client::TestSend::operator()()
		{	http::client mClient;
			http::response resp, theResp;
			http::request req;
			binary_data respBinary;

			// Format response
			resp.status_code() = 404;
			resp.reason_phrase() = binary_data("Not Found");
			resp.body() = binary_data('a', 60000);
			respBinary = resp.render();
			respBinary += respBinary;

			// Format req
			req.uri() = http::url("/");
			req.request_method() = http::request::REQUEST_GET;
			req.headers().add("Host", "www.google.com");

			// Create http server
			MiniHTTPServer myServer(respBinary);

			// Start server
			myServer.start();
			mt::thread::sleep(1500);    //WAit to start

			// Check if it is connected
			if (mClient.connected())
				return false;

			// Connect with client
			mClient.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(55123)));

			// Check if it is connected
			if (!mClient.connected())
				return false;

			// Send request
			theResp = mClient.send(req, 3000);

			if (theResp.render() != resp.render())
				return false;

			return true;
		}

		bool test_http_client::TestSendSpeed::operator()()
		{	http::client mClient;
			http::response resp, theResp;
			http::request req;
			binary_data respBinary;

			// Format response
			resp.status_code() = 404;
			resp.reason_phrase() = binary_data("Not Found");
			resp.body() = binary_data('a', 1000);
			respBinary = resp.render();

			// Format req
			req.uri() = http::url("/");
			req.request_method() = http::request::REQUEST_GET;
			req.headers().add("Host", "www.google.com");

			// Create http server
			HTTPServer myServer;
			myServer.std_resp = resp;

			// Start server
			myServer.start_listen(socket_address_inet(host_inet::LOCALHOST, port_inet(55123)), 100);
			mt::thread::sleep(500);    //WAit to start


			// Connect with client
			mClient.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(55123)));

			for(int i = 0;i < (50 * 1000);i ++)
			{
				//if ((i % 5000) == 0)
				//printf("%d\n", i);

				// Send request
				theResp = mClient.send(req, 3000);
			}

			if (theResp.render() != resp.render())
				return false;

			return true;
		}

		bool test_http_client::TestSendTimeOut::operator()()
		{	http::client mClient;
			http::response theResp;
			http::request req;
			binary_data respBinary = binary_data("Asdadsasdasdasdasdasd");

			// Format req
			req.uri() = http::url("/");
			req.request_method() = http::request::REQUEST_GET;
			req.headers().add("Host", "www.google.com");

			// Create http server
			MiniHTTPServer myServer(respBinary, 4000);

			// Start server
			myServer.start();
			mt::thread::sleep(1500);    //Wait to start

			// Check if it is connected
			if (mClient.connected())
				return false;

			// Connect with client
			mClient.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(55123)));

			// Check if it is connected
			if (!mClient.connected())
				return false;

			// Send request
			theResp = mClient.send(req, 3000);

			return false;
		}

		bool test_http_client::TestSendWrongResponse::operator()()
		{	http::client mClient;
			http::response theResp;
			http::request req;
			binary_data respBinary = binary_data("asdfadsf\n\nadsf\n");

			// Format req
			req.uri() = http::url("/");
			req.request_method() = http::request::REQUEST_GET;
			req.headers().add("Host", "www.google.com");

			// Create http server
			MiniHTTPServer myServer(respBinary, 100);

			// Start server
			myServer.start();
			mt::thread::sleep(1500);    //Wait to start

			// Check if it is connected
			if (mClient.connected())
				return false;

			// Connect with client
			mClient.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(55123)));

			// Check if it is connected
			if (!mClient.connected())
				return false;

			// Send request
			theResp = mClient.send(req, 3000);

			return false;
		}

		bool test_http_client::TestReuseDisconnected::operator()()
		{	http::client mClient;
			http::response resp, theResp;
			http::request req;
			binary_data respBinary = binary_data("asdfadsf\n\nadsf\n"), respBinary2;

			// Format response
			resp.status_code() = 404;
			resp.reason_phrase() = binary_data("Not Found");
			resp.body() = binary_data('a', 60000);
			respBinary2 = resp.render();

			// Format req
			req.uri() = http::url("/");
			req.request_method() = http::request::REQUEST_GET;
			req.headers().add("Host", "www.google.com");

			// Create http server
			MiniHTTPServer myServer1(respBinary);

			// Start server
			myServer1.start();
			mt::thread::sleep(1500);    //Wait to start

			// Check if it is connected
			if (mClient.connected())
				return false;

			// Connect with client
			mClient.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(55123)));

			// Check if it is connected
			if (!mClient.connected())
				return false;

			// Send request
			try
			{
				theResp = mClient.send(req, 3000);
				return false;
			}
			catch(http::ExceptionWrongFormat)
			{}

			// Create new http server
			myServer1.StopS();
			MiniHTTPServer myServer2(respBinary2);
			myServer2.start();
			mt::thread::sleep(1500);    //Wait to start

			// Check if it is connected
			if (mClient.connected())
				return false;

			// Reconncet
			mClient.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(55123)));

			theResp = mClient.send(req, 3000);

			if (theResp.render() != resp.render())
				return false;
			return true;
		}

		bool test_http_client::TestSendServerReset::operator()()
		{	MiniDCServer myserver;
			http::request req;
			http::client mClient;

			myserver.start();
			mt::thread::sleep(500);    //Wait to star


			// Format req
			req.uri() = http::url("/");
			req.request_method() = http::request::REQUEST_GET;
			req.headers().add("Host", "www.google.com");

			for(int i = 0;i < 1000;i++)
			{
				// Connect with client
				mClient.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(55123)));

				mClient.send(req, 3000);
			}
			return false;
		}
	}	// !test namespace
}; // !oonet namespace
