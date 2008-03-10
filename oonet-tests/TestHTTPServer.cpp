#include "TestHTTPServer.h"
#include "Http/Server.h"

namespace OONet
{
	TestHTTPServer theHTTPServer;

	// Mini HTTPServer
	class MyHTTPServer
		:public HTTP::Server
	{
	public:
		virtual ~MyHTTPServer()
		{
			initializeDestruction();
		}


	protected:
		virtual HTTP::Response OnURLRequest(const HTTP::Url & Uri, const HTTP::Request & full_request, const SocketAddressInet & client_addr)
		{
			HTTP::Response tmpResponse;

			tmpResponse.setBody(BinaryData("<HTML><BODY>Dont know how to handle this url!</BODY></HTML>"));
			return tmpResponse;
		}

		virtual void OnPreStart(Socket & listen_socket)
		{
			int reuse = 1;
		    listen_socket.setOption(SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
		};

	};

	bool TestHTTPServer::TestCtor::OnExecute()
	{	MyHTTPServer myServer;
		return true;
	}

	bool TestHTTPServer::TestStart::OnExecute()
	{	MyHTTPServer myServer;

		myServer.start(SocketAddressInet(HostInet::ANY, PortInet(44130)), 100);
		return true;
	}

	bool TestHTTPServer::TestDoubleStart::OnExecute()
	{	MyHTTPServer myServer;

		myServer.start(SocketAddressInet(HostInet::ANY, PortInet(44131)), 100);
		myServer.start(SocketAddressInet(HostInet::ANY, PortInet(44132)), 100);
		return true;
	}

	bool TestHTTPServer::TestStartRecovery::OnExecute()
	{	MyHTTPServer myServer;

		if (myServer.isRunning())
			return false;

		myServer.start(SocketAddressInet(HostInet::LOCALHOST, PortInet(44132)), 10);

		if (!myServer.isRunning())
			return false;

		try
		{myServer.start(SocketAddressInet(HostInet::LOCALHOST, PortInet(44133)), 10);}
		catch(ExceptionAlreadyConnected & e){ e = e; }

		if (!myServer.isRunning())
			return false;

		if (myServer.getClients().size() != 0)
			return false;

		return true;
	}

	bool TestHTTPServer::TestStop::OnExecute()
	{	MyHTTPServer myServer;

		if (myServer.isRunning())
			return false;

		myServer.start(SocketAddressInet(HostInet::LOCALHOST, PortInet(44134)), 10);

		if (!myServer.isRunning())
			return false;

		try
		{myServer.start(SocketAddressInet(HostInet::LOCALHOST, PortInet(44135)), 10);}
		catch(ExceptionAlreadyConnected & e){ e = e; }

		if (!myServer.isRunning())
			return false;

		if (myServer.getClients().size() != 0)
			return false;

		// Stop server
		myServer.stop();

		if (myServer.isRunning())
		return false;

		// Start again
		myServer.start(SocketAddressInet(HostInet::LOCALHOST, PortInet(44136)), 10);

		if (!myServer.isRunning())
			return false;

		return true;
	}

	bool TestHTTPServer::TestStopWrong1::OnExecute()
	{	MyHTTPServer myServer;

		if (myServer.isRunning())
			return false;

		myServer.start(SocketAddressInet(HostInet::LOCALHOST, PortInet(44137)), 10);

		if (!myServer.isRunning())
			return false;

		if (myServer.getClients().size() != 0)
			return false;

		// Stop server
		myServer.stop();

		if (myServer.isRunning())
		return false;

		// Stop again
		myServer.stop();

		if (myServer.isRunning())
		return false;

		return true;
	}


	bool TestHTTPServer::TestStopWrong2::OnExecute()
	{	MyHTTPServer myServer;

		if (myServer.isRunning())
			return false;

		// Stop immediatly
		myServer.stop();

		if (myServer.isRunning())
			return false;

		return true;
	}


	bool TestHTTPServer::TestStopCleanup::OnExecute()
	{	MyHTTPServer myServer;
		Socket mHttpClient(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
		BinaryData RespShouldBe = BinaryData("HTTP/1.1 200 OK\r\nConnection: Keep-Alive\r\nContent-Length: 59\r\n\r\n<HTML><BODY>Dont know how to handle this url!</BODY></HTML>");;
		HTTP::Request myRequest;

		// Format my request
		myRequest.getHeaders().setHeader("Host", "www.google.com");
		if (myServer.isRunning())
			return false;

		myServer.start(SocketAddressInet(HostInet::LOCALHOST, PortInet(44138)), 10);

		if (!myServer.isRunning())
			return false;

		// Connect client
		mHttpClient.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(44138)));

		// Send some data
		mHttpClient.send(myRequest.render());

		// Wait to get back same data
		if (mHttpClient.receive(1000) != RespShouldBe)
			return false;

		// Get count of clients
		if (myServer.getClients().size() != 1)
			return false;

		// Check if client is connected
		if (! myServer.getClients()[0]->isConnected())
			return false;

		// Stop server
		myServer.stop();

		if (myServer.isRunning())
			return false;

		// Get count of clients
		if (myServer.getClients().size() != 0)
			return false;
		return true;
	}

	bool TestHTTPServer::TestDCInvalidClients::OnExecute()
	{	MyHTTPServer myServer;
		Socket mHttpClient(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
		BinaryData RespShouldBe = BinaryData("HTTP/1.1 200 OK\r\nContent-Length: 59\r\n\r\n<HTML><BODY>Dont know how to handle this url!</BODY></HTML>");;
		BinaryData invalidRequest = BinaryData("sfads\r\n\r\n\nasf");

		if (myServer.isRunning())
			return false;

		myServer.start(SocketAddressInet(HostInet::LOCALHOST, PortInet(44140)), 10);

		if (!myServer.isRunning())
			return false;

		// Connect client
		mHttpClient.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(44140)));

		// Send some data
		mHttpClient.send(invalidRequest);

		// Wait to get back same data
		try
		{
			if (mHttpClient.receive(1000) != RespShouldBe)
				return false;
			return false;
		}
		catch(Exception & e)
		{	e=e; return true;	}
		return false;

	}

	bool TestHTTPServer::TestPureVirtuals1::OnExecute()
	{
		MyHTTPServer * pServer;
		Socket mHttpClient(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
		BinaryData RespShouldBe = BinaryData("HTTP/1.1 200 OK\r\nContent-Length: 59\r\n\r\n<HTML><BODY>Dont know how to handle this url!</BODY></HTML>");;

		HTTP::Request myRequest;
		// Format my request
		myRequest.getHeaders().setHeader("Host", "www.google.com");
		BinaryData dRequest = myRequest.render();

		for(long i = 0;i < 1000;i++)
		{
			pServer = new MyHTTPServer();
			pServer->start(SocketAddressInet(HostInet::LOCALHOST, PortInet(44142)), 10);
			mHttpClient = Socket(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
			// Connect client
			mHttpClient.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(44142)));

			// Send some invalid data
			mHttpClient.send(dRequest);

			// Delete it in once
			delete pServer;
		}

		return true;
	}

	bool TestHTTPServer::TestDoS1::OnExecute()
	{	MyHTTPServer myServer;
		Socket mHttpClient(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
		BinaryData RespShouldBe = BinaryData("HTTP/1.1 200 OK\r\nContent-Length: 59\r\n\r\n<HTML><BODY>Dont know how to handle this url!</BODY></HTML>");;
		BinaryData invalidRequest = BinaryData("sfads\r\n\r\n\nasf");
		long i = 0;

		if (myServer.isRunning())
			return false;

		myServer.start(SocketAddressInet(HostInet::LOCALHOST, PortInet(44143)), 1000);

		if (!myServer.isRunning())
			return false;

		try
		{
			for(i = 0;i < 1000;i++)
			{
//				printf("%ld\n", i);

				mHttpClient = Socket(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
				// Connect client
				mHttpClient.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(44143)));

				// Send some invalid data
				mHttpClient.send(invalidRequest);

				mHttpClient.shutdown();
				mHttpClient.close();

			}
		}
		catch(Exception & e)
		{   printf("\nException: %s\n", e.getReport().c_str());
            return false;
		}

		return true;
	}
};	// !OONet namespace
