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
		Socket clSocket;

		MiniEchoServer(int _inetType)
			:lSocket(Socket::FAMILY_INET, _inetType, Socket::PROTO_DEFAULT),
			bRunning(false),
			LastExc(_T("no fike"), -1, _T("123123"), _T("!unknown")),
			clSocket(Socket::FAMILY_INET, _inetType, Socket::PROTO_DEFAULT)
		{
			bException = false;
			int reuse_addr = 1;
			lSocket.set_option(SOL_SOCKET , SO_REUSEADDR, &reuse_addr, sizeof(int));
			lSocket.bind(SocketAddressInet(HostResolver("127.0.0.1"), PortInet(55123)));
		}

		~MiniEchoServer()
		{
            lSocket.shutdown();
            lSocket = Socket();
            join(MT::Infinity);
		}

		virtual void thread_routine()
		{	lSocket.listen(1000);
			bRunning = true;

			try
			{
				while(1)
				{
					clSocket = lSocket.accept();

					while(1)
					{
						try
						{
							// Wait for data
							BinaryData data = clSocket.receive(1000);

							// Send back
							clSocket.send(data);

							// Raise semaphore
							semArrived.post();
						}
						catch(Exception & e)
						{	break;	}
					}
				}
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
			clSocket.shutdown(); clSocket = Socket();
		}
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

	bool TestSocket::TestTCPCopyConstructor::OnExecute()
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

		Socket DuppedSocket(TCPSocket);

		DuppedSocket.send(msg);
		EchoServer.semArrived.wait(1000);
		reply = TCPSocket.receive(1000);
		if (reply != msg)
			return false;

		// Close server
		EchoServer.StopS();

		return true;
	}

	bool TestSocket::TestTCPCopyOperator::OnExecute()
	{	Socket TCPSocket(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
		Socket DuppedSocket(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
		BinaryData msg1("Mess 1 -!");
		BinaryData msg2("Mess 2 -   !");

		// Start a tcp echo server
		MiniEchoServer EchoServer(Socket::TYPE_STREAM);
		EchoServer.start();
		MT::Thread::sleep(1500);
		if (EchoServer.bException)
			throw(EchoServer.LastExc);
		// Connect to server and send smthing
		TCPSocket.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(55123)));

		// Send some shit
		TCPSocket.send(msg1);
		EchoServer.semArrived.wait(1000);
		BinaryData reply = TCPSocket.receive(1000);
		if (reply != msg1)
			return false;

		DuppedSocket = TCPSocket;

		DuppedSocket.send(msg2);
		EchoServer.semArrived.wait(1000);
		reply = TCPSocket.receive(1000);
		if (reply !=msg2)
			return false;

		// Close server
		EchoServer.StopS();

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
		SocketAddressInet realb_addr = TCPSocket.get_local_address();

		if (realb_addr != bind_addr)
			return false;
		return true;
	}

	bool TestSocket::TestStressConnect::OnExecute()
	{	BinaryData msg("LOULOU'm!");
		Socket TCPSocket(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
		// Start a tcp echo server
		MiniEchoServer EchoServer(Socket::TYPE_STREAM);
		EchoServer.start();
		MT::Thread::sleep(1500);

		if (EchoServer.bException)
			throw(EchoServer.LastExc);

		for (int i = 0; i < 1000;i++)
		{	//printf("%d\n", i );
			TCPSocket = Socket(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);

			// Connect to server and send smthing
			TCPSocket.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(55123)));



			// Send some shit
			TCPSocket.send(msg);
			EchoServer.semArrived.wait(1000);
			BinaryData reply = TCPSocket.receive(1000);
			if (reply != msg)
			{	EchoServer.StopS();
				return false;
			}

		}

		// Close server
		EchoServer.StopS();
		return true;
	}

	bool TestSocket::TestBrutalConnect::OnExecute()
	{	BinaryData msg("LOULOU'm!");
		Socket TCPSocket(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
		// Start a tcp echo server
		MiniEchoServer EchoServer(Socket::TYPE_STREAM);
		EchoServer.start();
		MT::Thread::sleep(1500);

		if (EchoServer.bException)
			throw(EchoServer.LastExc);

		for (int i = 0; i < 1000;i++)
		{
			TCPSocket = Socket(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);

			// Connect to server and send smthing
			TCPSocket.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(55123)));

			// Send some shit
			TCPSocket.send(msg);
			//EchoServer.semArrived.wait(1000);

			TCPSocket.shutdown();
			TCPSocket = Socket();

		}

		// Close server
		EchoServer.StopS();
		return true;
	}
};	 // !OONet namespace
