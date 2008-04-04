#include "TestHTTPClient.h"
#include "Http/Client.h"

namespace OONet
{
	TestHTTPClient theHTTPClient;

	// Mini echo server
	class MiniHTTPServer
		: public MT::thread
	{
	public:
		BinaryData ReceivedData;
		MT::semaphore semArrived;
		Socket lSocket;
		bool bRunning;
		Exception LastExc;
		bool bException;
		BinaryData myResp;
		long wt_after_send;

		MiniHTTPServer(const BinaryData & resp, long wt_after = 0)
			:lSocket(Socket::FAMILY_INET,Socket::TYPE_STREAM, Socket::PROTO_DEFAULT),
			bRunning(false),
			LastExc(_T("no fike"), -1, _T("123123"), _T("!unknown")),
			myResp(resp),
			wt_after_send(wt_after)
		{
			bException = false;
			int reuse = 1;
			lSocket.set_option(SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
			lSocket.bind(SocketAddressInet(HostInet::LOCALHOST, PortInet(55123)));
		}

		~MiniHTTPServer()
		{
			lSocket.shutdown();
			lSocket = Socket();
			join(MT::Infinity);

		}

		virtual void thread_routine()
		{	BinaryData data;
			HTTP::Request myReq;

			bRunning = true;
			try
			{
				lSocket.listen(2);
				Socket clSocket = lSocket.accept();

				// Wait for data
				while(1)
				{
					try
					{
						data += clSocket.receive(1000);
						myReq.parse(data);
					}
					catch(HTTP::ExceptionIncomplete)
					{	continue;
					}
					break;
				}

				// Wait a bit to reproduce lag
				MT::thread::sleep(1000);

				// Send back reply
				clSocket.send(myResp);

				if (wt_after_send)
					MT::thread::sleep(wt_after_send);
				// Raise semaphore
				semArrived.post();

				clSocket.shutdown();
				clSocket = Socket();
			}
			catch(Exception & e)
			{	LastExc = e;
				bException = true;
				semArrived.post();
			}
			bRunning = false;
		}

		// Exit server
		void StopS()
		{	lSocket.shutdown();
		    lSocket = Socket();
		    join(MT::Infinity);
		}
	};

	// Mini echo server
	class MiniDCServer
		: public MT::thread
	{
	public:
		Socket lSocket;

		MiniDCServer()
			:lSocket(Socket::FAMILY_INET,Socket::TYPE_STREAM, Socket::PROTO_DEFAULT)
		{
			int reuse = 1;
			lSocket.set_option(SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
			lSocket.bind(SocketAddressInet(HostInet::LOCALHOST, PortInet(55123)));
		}

		~MiniDCServer()
		{
			lSocket.shutdown();
			lSocket = Socket();
			join(MT::Infinity);

		}

		virtual void thread_routine()
		{
			try
			{
				lSocket.listen(2);
				Socket clSocket = lSocket.accept();

				// dc client
				sleep(1000);
				clSocket.shutdown();
				clSocket = Socket();
			}
			catch(Exception &)
			{}
		}

		// Exit server
		void StopS()
		{	lSocket.shutdown();
		    lSocket = Socket();
		    join(MT::Infinity);
		}
	};

	bool TestHTTPClient::TestCtor::OnExecute()
	{	HTTP::Client mClient;

		if (mClient.connected())
			return false;

		return true;
	}

	bool TestHTTPClient::TestCtorWrong::OnExecute()
	{	HTTP::Client mClient(SocketAddressInet(HostInet::LOCALHOST, PortInet(44243)));

		if (mClient.connected())
			return false;
		return false;
	}

	bool TestHTTPClient::TestConnect::OnExecute()
	{	HTTP::Client mClient;

		mClient.connect(SocketAddressInet(HostResolver("www.google.com"), PortInet(80)));

		if (!mClient.connected())
			return false;
		return true;
	}

	bool TestHTTPClient::TestConnectConnected::OnExecute()
	{	HTTP::Client mClient;

		// Connect to server
		mClient.connect(SocketAddressInet(HostResolver("www.google.com"), PortInet(80)));

		// Check if it is connected
		if (!mClient.connected())
			return false;

		// Connet to another server
		mClient.connect(SocketAddressInet(HostResolver("www.in.gr"), PortInet(80)));

		// Check if it is connected
		if (!mClient.connected())
			return false;

		return true;
	}

	bool TestHTTPClient::TestSend::OnExecute()
	{	HTTP::Client mClient;
		HTTP::Response resp, theResp;
		HTTP::Request req;
		BinaryData respBinary;

		// Format response
		resp.ErrorCode = "404";
		resp.ErrorMsg = "Not Found";
		resp.setBody(BinaryData('a', 60000));
		respBinary = resp.render();

		// Format req
		req.url = "/";
		req.http_type = HTTP::Request::REQUEST_GET;
		req.getHeaders().setHeader("Host", "www.google.com");

		// Create http server
		MiniHTTPServer myServer(respBinary);

		// Start server
		myServer.start();
		MT::thread::sleep(1500);    //WAit to start

		// Check if it is connected
		if (mClient.connected())
			return false;

		// Connect with client
		mClient.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(55123)));

		// Check if it is connected
		if (!mClient.connected())
			return false;

		// Send request
		theResp = mClient.send(req, 3000);

		if (theResp.render() != resp.render())
			return false;

		return true;
	}


	bool TestHTTPClient::TestSendTimeOut::OnExecute()
	{	HTTP::Client mClient;
		HTTP::Response theResp;
		HTTP::Request req;
		BinaryData respBinary = BinaryData("Asdadsasdasdasdasdasd");

		// Format req
		req.url = "/";
		req.http_type = HTTP::Request::REQUEST_GET;
		req.getHeaders().setHeader("Host", "www.google.com");

		// Create http server
		MiniHTTPServer myServer(respBinary, 4000);

		// Start server
		myServer.start();
		MT::thread::sleep(1500);    //Wait to start

		// Check if it is connected
		if (mClient.connected())
			return false;

		// Connect with client
		mClient.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(55123)));

		// Check if it is connected
		if (!mClient.connected())
			return false;

		// Send request
		theResp = mClient.send(req, 3000);

		return false;
	}

	bool TestHTTPClient::TestSendWrongResponse::OnExecute()
	{	HTTP::Client mClient;
		HTTP::Response theResp;
		HTTP::Request req;
		BinaryData respBinary = BinaryData("asdfadsf\n\nadsf\n");

		// Format req
		req.url = "/";
		req.http_type = HTTP::Request::REQUEST_GET;
		req.getHeaders().setHeader("Host", "www.google.com");

		// Create http server
		MiniHTTPServer myServer(respBinary);

		// Start server
		myServer.start();
		MT::thread::sleep(1500);    //Wait to start

		// Check if it is connected
		if (mClient.connected())
			return false;

		// Connect with client
		mClient.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(55123)));

		// Check if it is connected
		if (!mClient.connected())
			return false;

		// Send request
		theResp = mClient.send(req, 3000);

		return false;
	}

	bool TestHTTPClient::TestReuseDisconnected::OnExecute()
	{	HTTP::Client mClient;
		HTTP::Response resp, theResp;
		HTTP::Request req;
		BinaryData respBinary = BinaryData("asdfadsf\n\nadsf\n"), respBinary2;

		// Format response
		resp.ErrorCode = "404";
		resp.ErrorMsg = "Not Found";
		resp.setBody(BinaryData('a', 60000));
		respBinary2 = resp.render();

		// Format req
		req.url = "/";
		req.http_type = HTTP::Request::REQUEST_GET;
		req.getHeaders().setHeader("Host", "www.google.com");

		// Create http server
		MiniHTTPServer myServer1(respBinary);

		// Start server
		myServer1.start();
		MT::thread::sleep(1500);    //Wait to start

		// Check if it is connected
		if (mClient.connected())
			return false;

		// Connect with client
		mClient.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(55123)));

		// Check if it is connected
		if (!mClient.connected())
			return false;

		// Send request
		try
		{
			theResp = mClient.send(req, 3000);
			return false;
		}
		catch(HTTP::ExceptionWrongFormat)
		{}

		// Create new http server
		myServer1.StopS();
		MiniHTTPServer myServer2(respBinary2);
		myServer2.start();
		MT::thread::sleep(1500);    //Wait to start

		// Check if it is connected
		if (mClient.connected())
			return false;

		// Reconncet
		mClient.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(55123)));

		theResp = mClient.send(req, 3000);

		if (theResp.render() != resp.render())
			return false;
		return true;
	}

	bool TestHTTPClient::TestSendServerReset::OnExecute()
	{	MiniDCServer myserver;
		HTTP::Request req;
		HTTP::Client mClient;

		myserver.start();
		MT::thread::sleep(1500);    //Wait to star

		// Format req
		req.url = "/";
		req.http_type = HTTP::Request::REQUEST_GET;
		req.getHeaders().setHeader("Host", "www.google.com");

		// Connect with client
		mClient.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(55123)));

		mClient.send(req, 3000);

		return false;
	}
}; // !OONet namespace
