#include "TestHTTPClient.h"
#include "Http/Client.h"

namespace oonet
{
	TestHTTPClient theHTTPClient;

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

		virtual void thread_routine()
		{	binary_data data;
			http::Request myReq;

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

				if (wt_after_send)
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

		virtual void thread_routine()
		{
			try
			{
				lSocket.listen(2);
				socket clSocket = lSocket.accept();

				// dc client
				sleep(1000);
				clSocket.shutdown();
				clSocket = socket();
			}
			catch(exception &)
			{}
		}

		// Exit server
		void StopS()
		{	lSocket.shutdown();
		    lSocket = socket();
		    join(mt::Infinity);
		}
	};

	bool TestHTTPClient::TestCtor::OnExecute()
	{	http::Client mClient;

		if (mClient.connected())
			return false;

		return true;
	}

	bool TestHTTPClient::TestCtorWrong::OnExecute()
	{	http::Client mClient(socket_address_inet(host_inet::LOCALHOST, port_inet(44243)));

		if (mClient.connected())
			return false;
		return false;
	}

	bool TestHTTPClient::TestConnect::OnExecute()
	{	http::Client mClient;

		mClient.connect(socket_address_inet(host_resolver("www.google.com"), port_inet(80)));

		if (!mClient.connected())
			return false;
		return true;
	}

	bool TestHTTPClient::TestConnectConnected::OnExecute()
	{	http::Client mClient;

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

	bool TestHTTPClient::TestSend::OnExecute()
	{	http::Client mClient;
		http::Response resp, theResp;
		http::Request req;
		binary_data respBinary;

		// Format response
		resp.ErrorCode = "404";
		resp.ErrorMsg = "Not Found";
		resp.setBody(binary_data('a', 60000));
		respBinary = resp.render();

		// Format req
		req.url = "/";
		req.http_type = http::Request::REQUEST_GET;
		req.getHeaders().setHeader("Host", "www.google.com");

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


	bool TestHTTPClient::TestSendTimeOut::OnExecute()
	{	http::Client mClient;
		http::Response theResp;
		http::Request req;
		binary_data respBinary = binary_data("Asdadsasdasdasdasdasd");

		// Format req
		req.url = "/";
		req.http_type = http::Request::REQUEST_GET;
		req.getHeaders().setHeader("Host", "www.google.com");

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

	bool TestHTTPClient::TestSendWrongResponse::OnExecute()
	{	http::Client mClient;
		http::Response theResp;
		http::Request req;
		binary_data respBinary = binary_data("asdfadsf\n\nadsf\n");

		// Format req
		req.url = "/";
		req.http_type = http::Request::REQUEST_GET;
		req.getHeaders().setHeader("Host", "www.google.com");

		// Create http server
		MiniHTTPServer myServer(respBinary);

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

	bool TestHTTPClient::TestReuseDisconnected::OnExecute()
	{	http::Client mClient;
		http::Response resp, theResp;
		http::Request req;
		binary_data respBinary = binary_data("asdfadsf\n\nadsf\n"), respBinary2;

		// Format response
		resp.ErrorCode = "404";
		resp.ErrorMsg = "Not Found";
		resp.setBody(binary_data('a', 60000));
		respBinary2 = resp.render();

		// Format req
		req.url = "/";
		req.http_type = http::Request::REQUEST_GET;
		req.getHeaders().setHeader("Host", "www.google.com");

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

	bool TestHTTPClient::TestSendServerReset::OnExecute()
	{	MiniDCServer myserver;
		http::Request req;
		http::Client mClient;

		myserver.start();
		mt::thread::sleep(1500);    //Wait to star

		// Format req
		req.url = "/";
		req.http_type = http::Request::REQUEST_GET;
		req.getHeaders().setHeader("Host", "www.google.com");

		// Connect with client
		mClient.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(55123)));

		mClient.send(req, 3000);

		return false;
	}
}; // !oonet namespace
