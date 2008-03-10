#include "TestSocket.h"
#include "Socket.h"
#include "SocketAddressInet.h"
#include "Thread.h"

namespace OONet
{
	TestSocket theSocket;

	// Mini echo server
	class MiniEchoServer
		: public MT::Thread
	{
	public:
		BinaryData ReceivedData;
		MT::Semaphore semArrived;
		Socket lSocket;
		bool bRunning;
		Exception LastExc;
		bool bException;

		MiniEchoServer(int _inetType)
			:lSocket(Socket::FAMILY_INET, _inetType, Socket::PROTO_DEFAULT),
			bRunning(false),
			LastExc(_T("no fike"), -1, _T("123123"), _T("!unknown"))
		{
			bException = false;
			int reuse_addr = 1;
			lSocket.setOption(SOL_SOCKET , SO_REUSEADDR, &reuse_addr, sizeof(int));
			lSocket.bind(SocketAddressInet(HostResolver("127.0.0.1"), PortInet(55123)));
		}

		~MiniEchoServer()
		{
            lSocket.shutdown();
            lSocket.close();
            join(MT::Infinity);
		}

		virtual void ThreadRoutine()
		{
			bRunning = true;
			try
			{
				lSocket.listen(1);
				Socket clSocket = lSocket.accept();

				// Wait for data
				BinaryData data = clSocket.receive(1000);

				// Send back
				clSocket.send(data);

				// Raise semaphore
				semArrived.post();

				// Close socket
				clSocket.shutdown();
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
		{	lSocket.shutdown();}
	};

	bool TestSocket::TestTCPCtor::OnExecute()
	{	Socket TCPSocket(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
		return true;
	}

	bool TestSocket::TestUDPCtor::OnExecute()
	{	Socket UDPSocket(Socket::FAMILY_INET, Socket::TYPE_DGRAM, Socket::PROTO_DEFAULT);
		return true;
	}

	bool TestSocket::TestRAWCtor::OnExecute()
	{	Socket RAWSocket(Socket::FAMILY_INET, Socket::TYPE_RAW, Socket::PROTO_DEFAULT);
		return true;
	}

	bool TestSocket::TestWhateverCtor::OnExecute()
	{	Socket InvalidSocket(Socket::FAMILY_INET, 342894, Socket::PROTO_DEFAULT);
		return true;
	}

	bool TestSocket::TestTCPConnect::OnExecute()
	{	Socket TCPSocket(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
		BinaryData msg("LOULOU'm!");

		// Start a tcp echo server
		MiniEchoServer EchoServer(Socket::TYPE_STREAM);
		EchoServer.start();
		MT::Thread::sleep(1500);
		if (EchoServer.bException)
			throw(EchoServer.LastExc);
		// Connect to server and send smthing
		TCPSocket.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(55123)));

		// Send some shit
		TCPSocket.send(msg);
		EchoServer.semArrived.wait(1000);
		BinaryData reply = TCPSocket.receive(1000);
		if (reply != msg)
			return false;

		// Close server
		EchoServer.StopS();
		return true;
	}

	bool TestSocket::TestTCPConnectWrong::OnExecute()
	{	Socket TCPSocket(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);

		// connect on a fake address
		TCPSocket.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(39456)));
		return false;
	}

	bool TestSocket::TestBindWrong::OnExecute()
	{	Socket TCPSocket(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);

		TCPSocket.bind(SocketAddressInet(HostResolver("123.1.1.1"), PortInet(1)));
		return false;
	}

	bool TestSocket::TestBindRebind::OnExecute()
	{	Socket TCPSocket(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);

		// Bind in an address
		TCPSocket.bind(SocketAddressInet(HostResolver("127.0.0.1"), PortInet(59123)));
		// Bind in same address
		TCPSocket.bind(SocketAddressInet(HostResolver("127.0.0.1"), PortInet(59123)));
		return false;
	}

	bool TestSocket::TestBind::OnExecute()
	{	Socket TCPSocket(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
		SocketAddressInet bind_addr(HostInet::LOCALHOST, PortInet(59123));

		// Bind in an address
		TCPSocket.bind(bind_addr);

		// Get local peer
		SocketAddressInet realb_addr = TCPSocket.getLocalAddress();

		if (realb_addr != bind_addr)
			return false;
		return true;
	}
};	 // !OONet namespace
/*

class SimpleClient : public MT::Thread
{
private:
    Socket * sock;
public:
    void ThreadRoutine(void)
    {
        sock = new Socket(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
        // Wait for server to start
        MT::Thread::Sleep(3000);
        sock->Connect(SocketAddressInet(HostInet::LOCALHOST, 4449));

        delete sock;
    }
} simpleClient;

bool TestSocket(void)
{

    // Test 1.
    std::cout << "1. Create 2 ipv4 tcp socket\n";
    Socket sockTcp = Socket(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
    Socket sockTcp2 = Socket(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);

    // Test 2.
    std::cout << "2. Create a ipv4 udp socket\n";
    Socket sockUdp = Socket(Socket::FAMILY_INET, Socket::TYPE_DGRAM, Socket::PROTO_DEFAULT);

    // Test 3.
    std::cout << "3. Try to connect with one tcp sock at www.google.com:80\n";
    sockTcp.Connect(SocketAddressInet(HostResolver("www.google.com"), PortInet(80)));

    // Test 4.
    std::cout << "4. Try to connect with second tcp sock at www.google.com:80\n";
    sockTcp2.Connect(SocketAddressInet(HostResolver("www.google.com"), PortInet(80)));

    // Test 5.
    std::cout << "5. Trying to reconnect at the same address with the same socket\n";
    try {
        sockTcp.Connect(SocketAddressInet(HostResolver("www.google.com"), PortInet(80)));
    }
    catch(ExceptionAlreadyConnected &e)
    {   e=e; std::cout <<"Catched!\n";   }

    // Test 6.
    std::cout << "6. Send data and get data\n";
    sockTcp.Send(BinaryData("GET / HTTP/1.1\nHost: www.google.com\n\n"));
    BinaryData temp = sockTcp.Receive(1000);
    std::cout << temp.GetStringA();

    // Test 7.
    std::cout << "7. Recreate tcp socket and try to connect again\n";
    sockTcp = Socket(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
    sockTcp.Connect(SocketAddressInet(HostResolver("www.google.com"), PortInet(80)));


    // Test 8.
    std::cout << "8. Try to listen an unbinded socket\n";
    sockTcp = Socket(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
	try
	{
		sockTcp.Listen(30);
		SocketAddressInet addr = sockTcp.getLocalAddress();
		std::cout << addr.getInetAddress().toString() << "\n";
		std::cout << addr.getInetPort().toString() << std::endl;
	}
	catch(Exception & e)
    {   e=e; std::cout <<"Catched!\n";   }

    // Test 9
    std::cout << "9. Test accept connections\n";
    sockTcp = Socket(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
    sockTcp.Bind(SocketAddressInet(HostInet::LOCALHOST, 4449));
    sockTcp.Listen(2);

    // Start client
    simpleClient.Start();
    Socket clsock = sockTcp.Accept();
    SocketAddressInet claddr = clsock.getLocalAddress();
    std::cout <<  claddr.getInetAddress().toString();


    // Create a tcp socket and try to connect twice
    Socket * psock = new Socket(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
    try
    {
        psock->Connect(SocketAddressInet(HostResolver("glaros"), 80));
        psock->Bind(SocketAddressInet(HostResolver::ANY, 5002));
        psock->Connect(SocketAddressInet(HostResolver("www.google.com"), 80));
    }catch (Exception & e)
    {
    }
	delete psock;

    // Create a tcp socket
    std::cout << "Bind Test: (TCP)\n";
    psock = new Socket(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);

    std::cout << "TEST 1: Bind at an invalid address\n";
    try{  psock->Bind(SocketAddressInet(HostResolver("130.2.2.2"), 2));    }
    catch(Exception &e) {}

    std::cout << "TEST 2: Bind at super user port\n";
    try{    psock->Bind(SocketAddressInet(HostResolver::ANY, 53));    }
    catch(Exception &e){}

    std::cout << "TEST 3: Bind at normal port\n";
    psock->Bind(SocketAddressInet(HostResolver::LOCALHOST, 4000));
   delete psock;

    /////////////
    // UDP / Binds
    std::cout << "Bind Test: (UDP)\n";
    psock = new Socket(Socket::FAMILY_INET, Socket::TYPE_DGRAM, Socket::PROTO_DEFAULT);

    std::cout << "TEST 1: Bind at an invalid address\n";
    try{  psock->Bind(SocketAddressInet(HostResolver("130.2.2.2"), 2));    }
    catch(Exception &e) {}

    std::cout << "TEST 2: Bind at super user port\n";
    try{    psock->Bind(SocketAddressInet(HostResolver::ANY, 53));    }
    catch(Exception &e){}

    std::cout << "TEST 3: Bind at normal port\n";
    psock->Bind(SocketAddressInet(HostResolver::LOCALHOST, 4000));
    delete psock;


    //////////////
    // Listen TCP
    std::cout << "Listen Test(TCP)\n";
    psock = new Socket(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
    psock->Bind(SocketAddressInet(HostResolver("0.0.0.0"), 3000));
    psock->Listen(10);
    delete psock;

    ///////////////
    // Listen UDP - Invalid
    std::cout << "Listen Test(UDP)\n";
    psock = new Socket(Socket::FAMILY_INET, Socket::TYPE_DGRAM, Socket::PROTO_DEFAULT);
    psock->Bind(SocketAddressInet(HostResolver::ANY, 30001));
    try { psock->Listen(10); }catch(Exception &e){}
    delete psock;


    //////////////
    // Accept connections
    std::cout << "Accept 1 connection at port 3000\n";
    psock = new Socket(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
    psock->Bind(SocketAddressInet(HostResolver::ANY, 3000));
    psock->Listen(1);
    try {Socket ClientSocket = psock->Accept();}catch(Exception &e){}
	return true;
}
*/
