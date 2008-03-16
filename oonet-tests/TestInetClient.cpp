#include "TestInetClient.h"
#include "InetClient.h"

namespace OONet
{
	TestInetClient theTestInetClient;

	// Mini server
	class MiniServer
		: public MT::Thread
	{
	public:
		Socket lSocket;
		Socket * clSocket[1000];
		int i;

		MiniServer(int _inetType)
			:lSocket(Socket::FAMILY_INET, _inetType, Socket::PROTO_DEFAULT)
		{
		    int reuse = 1;
		    lSocket.set_option(SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
			lSocket.bind(SocketAddressInet(HostResolver("127.0.0.1"), PortInet(55123)));
			lSocket.listen(1000);
			for(int i = 0;i < 1000;i++)
				clSocket[i] = NULL;

		}

		~MiniServer()
		{
			lSocket.shutdown();
			lSocket = Socket();
			join(MT::Infinity);

			for(int i = 0;i < 1000;i++)
			{
                if (clSocket[i])
                    delete clSocket[i];
                clSocket[i] = NULL;
			}
		}

		virtual void thread_routine()
		{	i = 0;
			try
			{
				clSocket[i] = new Socket(lSocket.accept());
				i++;
			}
			catch(Exception)
			{}
		}

		// Exit server
		void StopS()
		{
		    lSocket.shutdown();
			lSocket = Socket();
			join(MT::Infinity);

			for(int i = 0;i < 1000;i++)
			{
                if (clSocket[i])
                    delete clSocket[i];
                clSocket[i] = NULL;
			}
		}
	};

	// Custom client
	class MyClient
		:public InetClient
	{
	public:
	MyClient()
		:InetClient()
	{   OONET_DEBUG_L2(_T("MyClient()_\n"));  }

	~MyClient()
    {   OONET_DEBUG_L2(_T("~MyClient()_\n"));
        initialize_destruction();
        OONET_DEBUG_L2(_T("~MyClient()^\n"));
    }


	protected:
        virtual void OnDataArrived(const BinaryData & data)
        {	send(data);	}


	// An event when client is disconnected
	virtual void OnDisconnect(){}

	// An event when client is connected
    virtual void OnConnect(){}

	// An event when an error is raised when collecting data
	virtual void OnError(Exception &e){}
	};

	bool TestInetClient::TestTCPCtor::OnExecute()
	{	MyClient mClient;
		return true;
	}

	bool TestInetClient::TestUDPCtor::OnExecute()
	{	MyClient mClient;
		return true;
	}

	bool TestInetClient::TestConnectWrong::OnExecute()
	{	MyClient mClient;

		mClient.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(34782)));
		return false;
	}

	bool TestInetClient::TestFastConnect::OnExecute()
	{	MiniServer theServer(Socket::TYPE_STREAM);
		MyClient * pClient;

		for(long i = 0;i < 100; i++)
		{
		    // debug printf(" %d...", i);
			pClient = new MyClient;
			pClient->connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(55123)));
			delete pClient;
			// debug  printf("OK \n");
		}
		return true;
	}

	bool TestInetClient::TestReconnect::OnExecute()
	{	MiniServer theServer(Socket::TYPE_STREAM);
		MyClient mClient;

		// Check if it is connected
		if (mClient.isConnected())
			return false;

		// Connect to miniserver
		mClient.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(55123)));

		// Check if it is connected
		if (!mClient.isConnected())
			return false;

		// Disconnect
		mClient.disconnect();

		// Check if it is connected
		if (mClient.isConnected())
			return false;

		// Reconnect
		mClient.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(55123)));

		// Check if it is connected
		if (!mClient.isConnected())
			return false;

		// And same in fast mode
		for(long i = 0;i < 100;i++)
		{
			mClient.disconnect();
			// Reconnect
			mClient.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(55123)));
		}

		return true;
	}

	bool TestInetClient::TestReconnectWrong::OnExecute()
	{	MiniServer theServer(Socket::TYPE_STREAM);
		MyClient mClient;

		// Check if it is connected
		if (mClient.isConnected())
			return false;

		// Connect to miniserver
		mClient.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(55123)));

		// Connect again
		mClient.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(55123)));

		return false;
	}

};	// !OONet namespace
