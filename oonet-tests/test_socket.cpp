#include "test_socket.hpp"
#include "socket.hpp"
#include "socket_address_inet.hpp"
#include "thread.hpp"

namespace oonet
{
	TestSocket theSocket;

	// Mini echo server
	class MiniEchoServer
		: public mt::thread
	{
	public:
		binary_data ReceivedData;
		mt::semaphore semArrived;
		socket lSocket;
		bool bRunning;
		exception LastExc;
		bool bException;
		socket clSocket;

		MiniEchoServer(int _inetType)
			:lSocket(socket::FAMILY_INET, _inetType, socket::PROTO_DEFAULT),
			bRunning(false),
			LastExc(_T("no fike"), -1, _T("123123"), _T("!unknown")),
			clSocket(socket::FAMILY_INET, _inetType, socket::PROTO_DEFAULT)
		{
			bException = false;
			int reuse_addr = 1;
			lSocket.set_option(SOL_SOCKET , SO_REUSEADDR, &reuse_addr, sizeof(int));
			lSocket.bind(socket_address_inet(host_resolver("127.0.0.1"), port_inet(55123)));
		}

		~MiniEchoServer()
		{
            lSocket.shutdown();
            lSocket = socket();
            join(mt::Infinity);
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
							binary_data data = clSocket.receive(1000);

							// Send back
							clSocket.send(data);

							// Raise semaphore
							semArrived.post();
						}
						catch(exception & e)
						{	break;	}
					}
				}
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
			clSocket.shutdown(); clSocket = socket();
		}
	};

	bool TestSocket::TestTCPCtor::OnExecute()
	{	socket TCPSocket(socket::FAMILY_INET, socket::TYPE_STREAM, socket::PROTO_DEFAULT);
		return true;
	}

	bool TestSocket::TestUDPCtor::OnExecute()
	{	socket UDPSocket(socket::FAMILY_INET, socket::TYPE_DGRAM, socket::PROTO_DEFAULT);
		return true;
	}

	bool TestSocket::TestRAWCtor::OnExecute()
	{	socket RAWSocket(socket::FAMILY_INET, socket::TYPE_RAW, socket::PROTO_DEFAULT);
		return true;
	}

	bool TestSocket::TestWhateverCtor::OnExecute()
	{	socket InvalidSocket(socket::FAMILY_INET, 342894, socket::PROTO_DEFAULT);
		return true;
	}

	bool TestSocket::TestTCPCopyConstructor::OnExecute()
	{	socket TCPSocket(socket::FAMILY_INET, socket::TYPE_STREAM, socket::PROTO_DEFAULT);
		binary_data msg("LOULOU'm!");

		// Start a tcp echo server
		MiniEchoServer EchoServer(socket::TYPE_STREAM);
		EchoServer.start();
		mt::thread::sleep(1500);
		if (EchoServer.bException)
			throw(EchoServer.LastExc);
		// Connect to server and send smthing
		TCPSocket.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(55123)));

		// Send some shit
		TCPSocket.send(msg);
		EchoServer.semArrived.wait(1000);
		binary_data reply = TCPSocket.receive(1000);
		if (reply != msg)
			return false;

		socket DuppedSocket(TCPSocket);

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
	{	socket TCPSocket(socket::FAMILY_INET, socket::TYPE_STREAM, socket::PROTO_DEFAULT);
		socket DuppedSocket(socket::FAMILY_INET, socket::TYPE_STREAM, socket::PROTO_DEFAULT);
		binary_data msg1("Mess 1 -!");
		binary_data msg2("Mess 2 -   !");

		// Start a tcp echo server
		MiniEchoServer EchoServer(socket::TYPE_STREAM);
		EchoServer.start();
		mt::thread::sleep(1500);
		if (EchoServer.bException)
			throw(EchoServer.LastExc);
		// Connect to server and send smthing
		TCPSocket.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(55123)));

		// Send some shit
		TCPSocket.send(msg1);
		EchoServer.semArrived.wait(1000);
		binary_data reply = TCPSocket.receive(1000);
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
	{	socket TCPSocket(socket::FAMILY_INET, socket::TYPE_STREAM, socket::PROTO_DEFAULT);
		binary_data msg("LOULOU'm!");

		// Start a tcp echo server
		MiniEchoServer EchoServer(socket::TYPE_STREAM);
		EchoServer.start();
		mt::thread::sleep(1500);
		if (EchoServer.bException)
			throw(EchoServer.LastExc);

		// Connect to server and send smthing
		TCPSocket.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(55123)));

		// Send some shit
		TCPSocket.send(msg);
		EchoServer.semArrived.wait(1000);
		binary_data reply = TCPSocket.receive(1000);
		if (reply != msg)
			return false;

		// Close server
		EchoServer.StopS();
		return true;
	}

	bool TestSocket::TestTCPConnectWrong::OnExecute()
	{	socket TCPSocket(socket::FAMILY_INET, socket::TYPE_STREAM, socket::PROTO_DEFAULT);

		// connect on a fake address
		TCPSocket.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(39456)));
		return false;
	}

	bool TestSocket::TestBindWrong::OnExecute()
	{	socket TCPSocket(socket::FAMILY_INET, socket::TYPE_STREAM, socket::PROTO_DEFAULT);

		TCPSocket.bind(socket_address_inet(host_resolver("123.1.1.1"), port_inet(1)));
		return false;
	}

	bool TestSocket::TestBindRebind::OnExecute()
	{	socket TCPSocket(socket::FAMILY_INET, socket::TYPE_STREAM, socket::PROTO_DEFAULT);

		// Bind in an address
		TCPSocket.bind(socket_address_inet(host_resolver("127.0.0.1"), port_inet(59123)));
		// Bind in same address
		TCPSocket.bind(socket_address_inet(host_resolver("127.0.0.1"), port_inet(59123)));
		return false;
	}

	bool TestSocket::TestBind::OnExecute()
	{	socket TCPSocket(socket::FAMILY_INET, socket::TYPE_STREAM, socket::PROTO_DEFAULT);
		socket_address_inet bind_addr(host_inet::LOCALHOST, port_inet(59123));

		// Bind in an address
		TCPSocket.bind(bind_addr);

		// Get local peer
		socket_address_inet realb_addr = TCPSocket.get_local_address();

		if (realb_addr != bind_addr)
			return false;
		return true;
	}

	bool TestSocket::TestStressConnect::OnExecute()
	{	binary_data msg("LOULOU'm!");
		socket TCPSocket(socket::FAMILY_INET, socket::TYPE_STREAM, socket::PROTO_DEFAULT);
		// Start a tcp echo server
		MiniEchoServer EchoServer(socket::TYPE_STREAM);
		EchoServer.start();
		mt::thread::sleep(1500);

		if (EchoServer.bException)
			throw(EchoServer.LastExc);

		for (int i = 0; i < 1000;i++)
		{	//printf("%d\n", i );
			TCPSocket = socket(socket::FAMILY_INET, socket::TYPE_STREAM, socket::PROTO_DEFAULT);

			// Connect to server and send smthing
			TCPSocket.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(55123)));



			// Send some shit
			TCPSocket.send(msg);
			EchoServer.semArrived.wait(1000);
			binary_data reply = TCPSocket.receive(1000);
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
	{	binary_data msg("LOULOU'm!");
		socket TCPSocket(socket::FAMILY_INET, socket::TYPE_STREAM, socket::PROTO_DEFAULT);
		// Start a tcp echo server
		MiniEchoServer EchoServer(socket::TYPE_STREAM);
		EchoServer.start();
		mt::thread::sleep(1500);

		if (EchoServer.bException)
			throw(EchoServer.LastExc);

		for (int i = 0; i < 1000;i++)
		{
			TCPSocket = socket(socket::FAMILY_INET, socket::TYPE_STREAM, socket::PROTO_DEFAULT);

			// Connect to server and send smthing
			TCPSocket.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(55123)));

			// Send some shit
			TCPSocket.send(msg);
			//EchoServer.semArrived.wait(1000);

			TCPSocket.shutdown();
			TCPSocket = socket();

		}

		// Close server
		EchoServer.StopS();
		return true;
	}
};	 // !oonet namespace
