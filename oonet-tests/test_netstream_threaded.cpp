#include "./test_netstream_threaded.h"
#include "netstream_threaded.hpp"
#include "host_resolver.hpp"
#include "socket_address_inet.hpp"

namespace oonet
{
	test_netstream_threaded test_netstream_threaded_inst;

	// Mini server
	class MiniServer
		: public MT::thread
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
		:public netstream_threaded
	{
	public:
	MyClient()
		:netstream_threaded()
	{   OONET_DEBUG_L2(_T("MyClient()_\n"));  }

	~MyClient()
    {   OONET_DEBUG_L2(_T("~MyClient()_\n"));

        OONET_DEBUG_L2(_T("~MyClient()^\n"));
    }


	protected:
        virtual void on_data_arrived(const BinaryData & data)
        {	send(data);	}


	// An event when client is disconnected
	virtual void OnDisconnect(){}

	// An event when client is connected
    virtual void OnConnect(){}

	// An event when an error is raised when collecting data
	virtual void OnError(Exception &e){}
	};

	bool test_netstream_threaded::TestTCPCtor::OnExecute()
	{	MyClient mClient;
		return true;
	}

	bool test_netstream_threaded::TestUDPCtor::OnExecute()
	{	MyClient mClient;
		return true;
	}

	bool test_netstream_threaded::TestConnectWrong::OnExecute()
	{	MyClient mClient;

		mClient.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(34782)));
		return false;
	}

	bool test_netstream_threaded::TestFastConnect::OnExecute()
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

	bool test_netstream_threaded::TestReconnect::OnExecute()
	{	MiniServer theServer(Socket::TYPE_STREAM);
		MyClient mClient;

		// Check if it is connected
		if (mClient.connected())
			return false;

		// Connect to miniserver
		mClient.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(55123)));

		// Check if it is connected
		if (!mClient.connected())
			return false;

		// Disconnect
		mClient.disconnect();
		MT::thread::sleep(1000);

		// Check if it is connected
		if (mClient.connected())
			return false;

		// Reconnect
		mClient.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(55123)));

		// Check if it is connected
		if (!mClient.connected())
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

	bool test_netstream_threaded::TestReconnectWrong::OnExecute()
	{	MiniServer theServer(Socket::TYPE_STREAM);
		MyClient mClient;

		// Check if it is connected
		if (mClient.connected())
			return false;

		// Connect to miniserver
		mClient.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(55123)));

		// Connect again
		mClient.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(55123)));

		return true;
	}

};	// !oonet namespace
