#include "TestInetServer.h"
#include "InetServer.h"

namespace OONet
{
	TestInetServer theTestInetSErver;

	class EchoClient:
		public InetPeer
	{
	public:
		~EchoClient()
		{	initializeDestruction();	}
	protected:
		// When data arrives
		virtual void OnConnect(Socket & con_socket){}

		virtual void OnDataArrived(const BinaryData & data)
		{	send(data);	}
	};

	// A Simple echo server
	class EchoServer
		:public InetServer
	{
	protected:
		// When a new connection arrives
		virtual bool OnAccept(const SocketAddressInet & remote_addr, InetPeer *& pDstHandler)
		{	pDstHandler = new EchoClient();
			return true;
		}

		virtual void OnPreStart(Socket & listen_socket)
		{
			int reuse = 1;
		    listen_socket.setOption(SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
		};
	};

	bool TestInetServer::TestCtor::OnExecute()
	{	EchoServer mEchoServer;

		if (mEchoServer.isRunning())
			return false;
		return true;
	}

	bool TestInetServer::TestStart::OnExecute()
	{	EchoServer mEchoServer;

		if (mEchoServer.isRunning())
			return false;

		mEchoServer.start(SocketAddressInet(HostInet::LOCALHOST, PortInet(44230)), 10);

		if (!mEchoServer.isRunning())
			return false;

		return true;
	}

	bool TestInetServer::TestDoubleStart::OnExecute()
	{	EchoServer mEchoServer;

		if (mEchoServer.isRunning())
			return false;

		mEchoServer.start(SocketAddressInet(HostInet::LOCALHOST, PortInet(44231)), 10);

		if (!mEchoServer.isRunning())
			return false;

		mEchoServer.start(SocketAddressInet(HostInet::LOCALHOST, PortInet(44232)), 10);

		return true;
	}

	bool TestInetServer::TestStartRecovery::OnExecute()
	{	EchoServer mEchoServer;

		if (mEchoServer.isRunning())
			return false;

		mEchoServer.start(SocketAddressInet(HostInet::LOCALHOST, PortInet(44233)), 10);

		if (!mEchoServer.isRunning())
			return false;

		try
		{mEchoServer.start(SocketAddressInet(HostInet::LOCALHOST, PortInet(44234)), 10);}
		catch(ExceptionAlreadyConnected & e){ e = e; }

		if (!mEchoServer.isRunning())
			return false;

		if (mEchoServer.getClients().size() != 0)
			return false;

		return true;
	}

	bool TestInetServer::TestStop::OnExecute()
	{	EchoServer mEchoServer;

		if (mEchoServer.isRunning())
			return false;

		mEchoServer.start(SocketAddressInet(HostInet::LOCALHOST, PortInet(44235)), 10);

		if (!mEchoServer.isRunning())
			return false;

		try
		{mEchoServer.start(SocketAddressInet(HostInet::LOCALHOST, PortInet(44236)), 10);}
		catch(ExceptionAlreadyConnected & e){ e = e; }

		if (!mEchoServer.isRunning())
			return false;

		if (mEchoServer.getClients().size() != 0)
			return false;

		// Stop server
		mEchoServer.stop();

		if (mEchoServer.isRunning())
		return false;

		// Start again
		mEchoServer.start(SocketAddressInet(HostInet::LOCALHOST, PortInet(44237)), 10);

		if (!mEchoServer.isRunning())
			return false;

		return true;
	}

	bool TestInetServer::TestStopWrong1::OnExecute()
	{	EchoServer mEchoServer;

		if (mEchoServer.isRunning())
			return false;

		mEchoServer.start(SocketAddressInet(HostInet::LOCALHOST, PortInet(44238)), 10);

		if (!mEchoServer.isRunning())
			return false;

		if (mEchoServer.getClients().size() != 0)
			return false;

		// Stop server
		mEchoServer.stop();

		if (mEchoServer.isRunning())
		return false;

		// Stop again
		mEchoServer.stop();

		if (mEchoServer.isRunning())
		return false;

		return true;
	}

	bool TestInetServer::TestStopWrong2::OnExecute()
	{	EchoServer mEchoServer;

		if (mEchoServer.isRunning())
			return false;

		// Stop immediatly
		mEchoServer.stop();

		if (mEchoServer.isRunning())
			return false;

		return true;
	}

	bool TestInetServer::TestStopCleanup::OnExecute()
	{	EchoServer mEchoServer;
		Socket mClient(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
		BinaryData toBeSent("axaxaxaxxolxa");
		if (mEchoServer.isRunning())
			return false;

		mEchoServer.start(SocketAddressInet(HostInet::LOCALHOST, PortInet(44239)), 10);

		if (!mEchoServer.isRunning())
			return false;

		// Connect client
		mClient.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(44239)));

		// Send some data
		mClient.send(toBeSent);

		// Wait to get back same data
		if (mClient.receive(1000) != toBeSent)
			return false;

		// Get count of clients
		if (mEchoServer.getClients().size() != 1)
			return false;

		// Check if client is connected
		if (! mEchoServer.getClients()[0]->isConnected())
			return false;

		// Stop server
		mEchoServer.stop();

		if (mEchoServer.isRunning())
			return false;

		// Get count of clients
		if (mEchoServer.getClients().size() != 0)
			return false;
		return true;
	}

	bool TestInetServer::TestFree::OnExecute()
	{	EchoServer mEchoServer;
		Socket mClient(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
		BinaryData toBeSent("axaxaxaxxolxa");

		if (mEchoServer.isRunning())
			return false;


		mEchoServer.start(SocketAddressInet(HostInet::LOCALHOST, PortInet(44240)), 10);

		if (!mEchoServer.isRunning())
			return false;

		// Connect client
		mClient.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(44240)));

		// Send some data
		mClient.send(toBeSent);

		// Wait to get back same data
		if (mClient.receive(1000) != toBeSent)
			return false;

		// Check the remote peer address of handler
		if (mEchoServer.getClients().size() != 1)
			return false;

		// Debug shit
		//SocketAddressInet l, r;
		//l = mEchoServer.GetClients()[0]->GetRemotePeerAddress();
		//r = mClient.GetLocalAddress();
		//printf("%s:%s -> %s:%s", l.GetHostInet().toString().c_str(), l.GetPortInet().toString().c_str(), r.GetHostInet().toString().c_str(),r.GetPortInet().toString().c_str());
		// Check if client is connected
		if ((SocketAddress)mEchoServer.getClients()[0]->getRemotePeerAddress() != mClient.getLocalAddress())
			return false;


		InetPeer * pPeer = mEchoServer.getClients()[0];

		// Try to free before disconnecting him
		try{
			mEchoServer.freeHandler(pPeer);
		}catch(ExceptionResourceBusy & e){ e = e;}

		// On a failed free the client must remain
		if (mEchoServer.getClients().size() != 1)
			return false;

		// Disconnect client
		pPeer->disconnect();

		// When disconnecting peer must stay slotted
		if (mEchoServer.getClients().size() != 1)
			return false;

		// Free peer
		mEchoServer.freeHandler(pPeer);

		// When freeing, client must go go away
		if (mEchoServer.getClients().size() != 0)
			return false;
		return true;
	}

	bool TestInetServer::TestFreeWrong1::OnExecute()
	{	EchoServer mEchoServer;
		Socket mClient(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
		BinaryData toBeSent("axaxaxaxxolxa");

		if (mEchoServer.isRunning())
			return false;


		mEchoServer.start(SocketAddressInet(HostInet::LOCALHOST, PortInet(44241)), 10);

		if (!mEchoServer.isRunning())
			return false;

		// Connect client
		mClient.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(44241)));

		// Send some data
		mClient.send(toBeSent);

		// Wait to get back same data
		if (mClient.receive(1000) != toBeSent)
			return false;

		// Check the remote peer address of handler
		if (mEchoServer.getClients().size() != 1)
			return false;

		// Check if client is connected
		if ((SocketAddress)mEchoServer.getClients()[0]->getRemotePeerAddress() != mClient.getLocalAddress())
			return false;

		// Free peer while not disconnected
		InetPeer * pPeer = mEchoServer.getClients()[0];
		// Try to free before disconnecting him
		mEchoServer.freeHandler(pPeer);

		// When disconnecting peer must stay slotted
		if (mEchoServer.getClients().size() != 1)
			return false;

		// When freeing, client must go go away
		if (mEchoServer.getClients().size() != 0)
			return false;
		return true;
	}

	bool TestInetServer::TestFreeWrong2::OnExecute()
	{	EchoServer mEchoServer;
		Socket mClient(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
		BinaryData toBeSent("axaxaxaxxolxa");

		if (mEchoServer.isRunning())
			return false;

		mEchoServer.start(SocketAddressInet(HostInet::LOCALHOST, PortInet(44242)), 10);

		if (!mEchoServer.isRunning())
			return false;

		// Connect client
		mClient.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(44242)));

		// Send some data
		mClient.send(toBeSent);

		// Wait to get back same data
		if (mClient.receive(1000) != toBeSent)
			return false;

		// Check the remote peer address of handler
		if (mEchoServer.getClients().size() != 1)
			return false;

		// Check if client is connected
		if ((SocketAddress)mEchoServer.getClients()[0]->getRemotePeerAddress() != mClient.getLocalAddress())
			return false;

		// Free peer while not disconnected
		InetPeer * pPeer = mEchoServer.getClients()[0];

		// Try to free a wrong peer
		mEchoServer.freeHandler((InetPeer *)NULL);
		return false;
	}

	bool TestInetServer::TestFreeDisconnected::OnExecute()
	{	EchoServer mEchoServer;
		Socket mClient(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
		BinaryData toBeSent("axaxaxaxxolxa");

		if (mEchoServer.isRunning())
			return false;

		mEchoServer.start(SocketAddressInet(HostInet::LOCALHOST, PortInet(44243)), 10);

		if (!mEchoServer.isRunning())
			return false;

		// Connect client
		mClient.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(44243)));

		// Send some data
		mClient.send(toBeSent);

		// Wait to get back same data
		if (mClient.receive(1000) != toBeSent)
			return false;

		// Check the remote peer address of handler
		if (mEchoServer.getClients().size() != 1)
			return false;

		// Check if client is connected
		if ((SocketAddress)mEchoServer.getClients()[0]->getRemotePeerAddress() != mClient.getLocalAddress())
			return false;

		// Try to free all disconnected
		mEchoServer.freeAllDisconnectedHandlers();

		// Check if it was disconnected
		if (mEchoServer.getClients().size() != 1)
			return false;

		// Disconnect and try again
		InetPeer * pPeer = mEchoServer.getClients()[0];
		pPeer->disconnect();

		// Try to free all disconnected
		mEchoServer.freeAllDisconnectedHandlers();

		// Check if it was disconnected
		if (mEchoServer.getClients().size() != 0)
			return false;

		// Stop previous server
		mEchoServer.stop();
		// Start a server with none connected
		EchoServer mEchoServer2;
		mEchoServer2.start(SocketAddressInet(HostInet::LOCALHOST, PortInet(44244)), 10);

		// Try to free all
		mEchoServer2.freeAllDisconnectedHandlers();
		return true;
	}
};	// !OONet namespace
