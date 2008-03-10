#include "TestHTTPClient.h"
#include "Http/Client.h"

namespace Slib
{
	TestHTTPClient theHTTPClient;

	// Mini echo server
	class MiniHTTPServer
		: public MT::Thread
	{
	public:
		BinaryData ReceivedData;
		MT::Semaphore semArrived;
		Socket lSocket;
		bool bRunning;
		Exception LastExc;
		bool bException;
		BinaryData myResp;

		MiniHTTPServer(const BinaryData & resp)
			:lSocket(Socket::FAMILY_INET,Socket::TYPE_STREAM, Socket::PROTO_DEFAULT),
			bRunning(false),
			LastExc(_T("no fike"), -1, _T("123123"), _T("!unknown")),
			myResp(resp)
		{
			bException = false;
			int reuse = 1;
			lSocket.setOption(SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
			lSocket.bind(SocketAddressInet(HostInet::LOCALHOST, PortInet(55123)));
		}

		~MiniHTTPServer()
		{
			lSocket.shutdown();
			lSocket.close();
			join(MT::Infinity);

		}

		virtual void ThreadRoutine()
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
				MT::Thread::sleep(1000);

				// Send back reply
				clSocket.send(myResp);

				// Raise semaphore
				semArrived.post();

				clSocket.shutdown();
				clSocket.close();
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
		    lSocket.close();
		    join(MT::Infinity);
		}
	};

	bool TestHTTPClient::TestCtor::OnExecute()
	{	HTTP::Client mClient;

		if (mClient.isConnected())
			return false;

		return true;
	}

	bool TestHTTPClient::TestCtorWrong::OnExecute()
	{	HTTP::Client mClient(SocketAddressInet(HostInet::LOCALHOST, PortInet(44243)));

		if (mClient.isConnected())
			return false;
		return false;
	}

	bool TestHTTPClient::TestChangeHost::OnExecute()
	{	HTTP::Client mClient;

		mClient.changeHost(SocketAddressInet(HostResolver("www.google.com"), PortInet(80)));

		if (!mClient.isConnected())
			return false;
		return true;
	}

	bool TestHTTPClient::TestChangeHostConnected::OnExecute()
	{	HTTP::Client mClient;

		// Connect to server
		mClient.changeHost(SocketAddressInet(HostResolver("www.google.com"), PortInet(80)));

		// Check if it is connected
		if (!mClient.isConnected())
			return false;

		// Connet to another server
		mClient.changeHost(SocketAddressInet(HostResolver("www.in.gr"), PortInet(80)));

		// Check if it is connected
		if (!mClient.isConnected())
			return false;

		return true;
	}

	bool TestHTTPClient::TestReconnect::OnExecute()
	{	HTTP::Client mClient;

		// Connect to server
		mClient.changeHost(SocketAddressInet(HostResolver("www.google.com"), PortInet(80)));

		// Check if it is connected
		if (!mClient.isConnected())
			return false;

		// reconnect
		mClient.reconnect();

		// Check if it is connected
		if (!mClient.isConnected())
			return false;
		return true;
	}

	bool TestHTTPClient::TestReconnectWrong::OnExecute()
	{	HTTP::Client mClient;

		// Check if it is connected
		if (mClient.isConnected())
			return false;

		// reconnect with no server defined!
		try
		{
            mClient.reconnect();
		}
		catch(Exception)
		{   return true;    }

		return false;
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
		MT::Thread::sleep(1500);    //WAit to start

		// Check if it is connected
		if (mClient.isConnected())
			return false;

		// Connect with client
		mClient.changeHost(SocketAddressInet(HostInet::LOCALHOST, PortInet(55123)));

		// Check if it is connected
		if (!mClient.isConnected())
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
		MiniHTTPServer myServer(respBinary);

		// Start server
		myServer.start();
		MT::Thread::sleep(1500);    //Wait to start

		// Check if it is connected
		if (mClient.isConnected())
			return false;

		// Connect with client
		mClient.changeHost(SocketAddressInet(HostInet::LOCALHOST, PortInet(55123)));

		// Check if it is connected
		if (!mClient.isConnected())
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
		MT::Thread::sleep(1500);    //Wait to start

		// Check if it is connected
		if (mClient.isConnected())
			return false;

		// Connect with client
		mClient.changeHost(SocketAddressInet(HostInet::LOCALHOST, PortInet(55123)));

		// Check if it is connected
		if (!mClient.isConnected())
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
		MT::Thread::sleep(1500);    //Wait to start

		// Check if it is connected
		if (mClient.isConnected())
			return false;

		// Connect with client
		mClient.changeHost(SocketAddressInet(HostInet::LOCALHOST, PortInet(55123)));

		// Check if it is connected
		if (!mClient.isConnected())
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
		MT::Thread::sleep(1500);    //Wait to start

		// Check if it is connected
		if (mClient.isConnected())
			return false;

		// Reconncet
		mClient.reconnect();

		theResp = mClient.send(req, 3000);

		if (theResp.render() != resp.render())
			return false;
		return true;
	}
}; //! Slib namespace
