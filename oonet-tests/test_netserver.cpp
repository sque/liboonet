#include "test_netserver.hpp"
#include <oonet/netserver.hpp>
#include <oonet/socket_address_inet.hpp>

namespace oonet
{
	namespace test
	{
		test_netserver test_netserver_inst;
		class EchoServer;

		class EchoClient:
			public netstream_threaded
		{
		public:
			EchoClient()
			{}

			~EchoClient()
			{}
		protected:

			virtual void on_data_received(const binary_data & data)
			{	send(data);	}
		};

		// A Simple echo server
		class EchoServer
			:public netserver<EchoClient>
		{
		protected:

			virtual void parametrize_listen_socket(socket & listen_socket)
			{
				int reuse = 1;
				listen_socket.set_option(SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
			};

			void assign_handler(socket & cl_sock)
			{
				// Create a new handler
				handler_shared_ptr p_streamhandler(new EchoClient);
				handlers_pool().push_back(p_streamhandler);

				// Assign socket to it
				p_streamhandler->assign_socket(cl_sock);
			}
		public:
			virtual ~EchoServer()
			{	initialize_destruction();	}

			handlers_pool_type & pool()
			{	return handlers_pool();	}
		};

		bool test_netserver::TestCtor::operator()()
		{	EchoServer mEchoServer;

			if (mEchoServer.listening())
				return false;
			return true;
		}

		bool test_netserver::TestStart::operator()()
		{	EchoServer mEchoServer;

			if (mEchoServer.listening())
				return false;

			mEchoServer.start_listen(socket_address_inet(host_inet::LOCALHOST, port_inet(44230)), 10);

			if (!mEchoServer.listening())
				return false;

			return true;
		}

		bool test_netserver::TestDoubleStart::operator()()
		{	EchoServer mEchoServer;

			if (mEchoServer.listening())
				return false;

			mEchoServer.start_listen(socket_address_inet(host_inet::LOCALHOST, port_inet(44231)), 10);

			if (!mEchoServer.listening())
				return false;

			mEchoServer.start_listen(socket_address_inet(host_inet::LOCALHOST, port_inet(44232)), 10);

			return true;
		}

		bool test_netserver::TestStartRecovery::operator()()
		{	EchoServer mEchoServer;

			if (mEchoServer.listening())
				return false;

			mEchoServer.start_listen(socket_address_inet(host_inet::LOCALHOST, port_inet(44233)), 10);

			if (!mEchoServer.listening())
				return false;

			try
			{mEchoServer.start_listen(socket_address_inet(host_inet::LOCALHOST, port_inet(44234)), 10);}
			catch(ExceptionAlreadyConnected & e){ e = e; }

			if (!mEchoServer.listening())
				return false;

			if (mEchoServer.pool().size() != 0)
				return false;

			return true;
		}

		bool test_netserver::TestStop::operator()()
		{	EchoServer mEchoServer;

			if (mEchoServer.listening())
				return false;

			mEchoServer.start_listen(socket_address_inet(host_inet::LOCALHOST, port_inet(44235)), 10);

			if (!mEchoServer.listening())
				return false;

			try
			{mEchoServer.start_listen(socket_address_inet(host_inet::LOCALHOST, port_inet(44236)), 10);}
			catch(ExceptionAlreadyConnected & e){ e = e; }

			if (!mEchoServer.listening())
				return false;

			if (mEchoServer.pool().size() != 0)
				return false;

			// Stop server
			mEchoServer.stop_listen();

			if (mEchoServer.listening())
			return false;

			// Start again
			mEchoServer.start_listen(socket_address_inet(host_inet::LOCALHOST, port_inet(44237)), 10);

			if (!mEchoServer.listening())
				return false;

			return true;
		}

		bool test_netserver::TestStopWrong1::operator()()
		{	EchoServer mEchoServer;

			if (mEchoServer.listening())
				return false;

			mEchoServer.start_listen(socket_address_inet(host_inet::LOCALHOST, port_inet(44238)), 10);

			if (!mEchoServer.listening())
				return false;

			if (mEchoServer.pool().size() != 0)
				return false;

			// Stop server
			mEchoServer.stop_listen();

			if (mEchoServer.listening())
			return false;

			// Stop again
			mEchoServer.stop_listen();

			if (mEchoServer.listening())
			return false;

			return true;
		}

		bool test_netserver::TestStopWrong2::operator()()
		{	EchoServer mEchoServer;

			if (mEchoServer.listening())
				return false;

			// Stop immediatly
			mEchoServer.stop_listen();

			if (mEchoServer.listening())
				return false;

			return true;
		}

		bool test_netserver::TestStopCleanup::operator()()
		{	EchoServer mEchoServer;
			socket mClient(socket::FAMILY_INET, socket::TYPE_STREAM, socket::PROTO_DEFAULT);
			binary_data toBeSent("axaxaxaxxolxa");
			if (mEchoServer.listening())
				return false;

			mEchoServer.start_listen(socket_address_inet(host_inet::LOCALHOST, port_inet(44239)), 10);

			if (!mEchoServer.listening())
				return false;

			// Connect client
			mClient.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(44239)));

			// Send some data
			mClient.send(toBeSent);

			// Wait to get back same data
			if (mClient.receive(1000) != toBeSent)
				return false;

			// Get count of clients
			if (mEchoServer.pool().size() != 1)
				return false;

			// Check if client is connected
			if (! mEchoServer.pool().front()->connected())
				return false;

			// Stop server
			mEchoServer.stop_listen();

			if (mEchoServer.listening())
				return false;

			// Get count of clients ( clients are not affected)
			if (mEchoServer.pool().size() != 1)
				return false;
			return true;
		}

		/*bool test_netserver::TestFree::operator()()
		{	EchoServer mEchoServer;
			Socket mClient(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
			binary_data toBeSent("axaxaxaxxolxa");

			if (mEchoServer.listening())
				return false;


			mEchoServer.start_listen(socket_address_inet(HostInet::LOCALHOST, PortInet(44240)), 10);

			if (!mEchoServer.listening())
				return false;

			// Connect client
			mClient.connect(socket_address_inet(HostInet::LOCALHOST, PortInet(44240)));

			// Send some data
			mClient.send(toBeSent);

			// Wait to get back same data
			if (mClient.receive(1000) != toBeSent)
				return false;

			// Check the remote peer address of handler
			if (mEchoServer.get_clients().size() != 1)
				return false;

			// Debug shit
			//socket_address_inet l, r;
			//l = mEchoServer.GetClients()[0]->GetRemotePeerAddress();
			//r = mClient.GetLocalAddress();
			//printf("%s:%s -> %s:%s", l.GetHostInet().toString().c_str(), l.GetPortInet().toString().c_str(), r.GetHostInet().toString().c_str(),r.GetPortInet().toString().c_str());
			// Check if client is connected
			if ((SocketAddress)mEchoServer.get_clients().front()->get_connection_socket().get_peer_address() != mClient.get_local_address())
				return false;


			EchoClient * pPeer = mEchoServer.get_clients().front();

			// Try to free before disconnecting him
			try{
				mEchoServer.freeHandler(pPeer);
			}catch(ExceptionResourceBusy & e){ e = e;}

			// On a failed free the client must remain
			if (mEchoServer.get_clients().size() != 1)
				return false;

			// Disconnect client
			pPeer->disconnect();

			// When disconnecting peer must stay slotted
			if (mEchoServer.get_clients().size() != 1)
				return false;

			// Free peer
			mEchoServer.freeHandler(pPeer);

			// When freeing, client must go go away
			if (mEchoServer.get_clients().size() != 0)
				return false;
			return true;
		}

		bool test_netserver::TestFreeWrong1::operator()()
		{	EchoServer mEchoServer;
			Socket mClient(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
			binary_data toBeSent("axaxaxaxxolxa");

			if (mEchoServer.listening())
				return false;


			mEchoServer.start_listen(socket_address_inet(HostInet::LOCALHOST, PortInet(44241)), 10);

			if (!mEchoServer.listening())
				return false;

			// Connect client
			mClient.connect(socket_address_inet(HostInet::LOCALHOST, PortInet(44241)));

			// Send some data
			mClient.send(toBeSent);

			// Wait to get back same data
			if (mClient.receive(1000) != toBeSent)
				return false;

			// Check the remote peer address of handler
			if (mEchoServer.get_clients().size() != 1)
				return false;

			// Check if client is connected
			if ((SocketAddress)mEchoServer.get_clients().front()->get_connection_socket().get_peer_address() != mClient.get_local_address())
				return false;

			// Free peer while not disconnected
			EchoClient * pPeer = mEchoServer.get_clients().front();
			// Try to free before disconnecting him
			mEchoServer.freeHandler(pPeer);

			// When disconnecting peer must stay slotted
			if (mEchoServer.get_clients().size() != 1)
				return false;

			// When freeing, client must go go away
			if (mEchoServer.get_clients().size() != 0)
				return false;
			return true;
		}

		bool test_netserver::TestFreeWrong2::operator()()
		{	EchoServer mEchoServer;
			Socket mClient(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
			binary_data toBeSent("axaxaxaxxolxa");

			if (mEchoServer.listening())
				return false;

			mEchoServer.start_listen(socket_address_inet(HostInet::LOCALHOST, PortInet(44242)), 10);

			if (!mEchoServer.listening())
				return false;

			// Connect client
			mClient.connect(socket_address_inet(HostInet::LOCALHOST, PortInet(44242)));

			// Send some data
			mClient.send(toBeSent);

			// Wait to get back same data
			if (mClient.receive(1000) != toBeSent)
				return false;

			// Check the remote peer address of handler
			if (mEchoServer.get_clients().size() != 1)
				return false;

			// Check if client is connected
			if ((SocketAddress)mEchoServer.get_clients().front()->get_connection_socket().get_peer_address() != mClient.get_local_address())
				return false;

			// Free peer while not disconnected
			EchoClient * pPeer = mEchoServer.get_clients().front();

			// Try to free a wrong peer
			mEchoServer.freeHandler((EchoClient *)NULL);
			return false;
		}

		bool test_netserver::TestFreeDisconnected::operator()()
		{	EchoServer mEchoServer;
			Socket mClient(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
			binary_data toBeSent("axaxaxaxxolxa");

			if (mEchoServer.listening())
				return false;

			mEchoServer.start_listen(socket_address_inet(HostInet::LOCALHOST, PortInet(44243)), 10);

			if (!mEchoServer.listening())
				return false;

			// Connect client
			mClient.connect(socket_address_inet(HostInet::LOCALHOST, PortInet(44243)));

			// Send some data
			mClient.send(toBeSent);

			// Wait to get back same data
			if (mClient.receive(1000) != toBeSent)
				return false;

			// Check the remote peer address of handler
			if (mEchoServer.get_clients().size() != 1)
				return false;

			// Check if client is connected
			if ((SocketAddress)mEchoServer.get_clients().front()->get_connection_socket().get_peer_address() != mClient.get_local_address())
				return false;

			// Try to free all disconnected
			mEchoServer.freeAllDisconnectedHandlers();

			// Check if it was disconnected
			if (mEchoServer.get_clients().size() != 1)
				return false;

			// Disconnect and try again
			EchoClient * pPeer = mEchoServer.get_clients().front();
			pPeer->disconnect();

			// Try to free all disconnected
			mEchoServer.freeAllDisconnectedHandlers();

			// Check if it was disconnected
			if (mEchoServer.get_clients().size() != 0)
				return false;

			// Stop previous server
			mEchoServer.stop_listen();
			// Start a server with none connected
			EchoServer mEchoServer2;
			mEchoServer2.start_listen(socket_address_inet(HostInet::LOCALHOST, PortInet(44244)), 10);

			// Try to free all
			mEchoServer2.freeAllDisconnectedHandlers();
			return true;
		}*/
	}	// !test namespace
};	// !oonet namespace
