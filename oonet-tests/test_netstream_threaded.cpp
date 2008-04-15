#include "./test_netstream_threaded.h"
#include <oonet/netstream_threaded.hpp>
#include <oonet/host_resolver.hpp>
#include <oonet/socket_address_inet.hpp>

namespace oonet
{
	test_netstream_threaded test_netstream_threaded_inst;

	// Mini server
	class MiniServer
		: public mt::thread
	{
	public:
		socket lSocket;
		socket * clSocket[1000];
		int i;
		bool b_send;

		MiniServer(bool _b_send = false)
			:lSocket(socket::FAMILY_INET, socket::TYPE_STREAM, socket::PROTO_DEFAULT),
			b_send(_b_send)
		{
		    int reuse = 1;
		    lSocket.set_option(SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
			lSocket.bind(socket_address_inet(host_resolver("127.0.0.1"), port_inet(55123)));
			lSocket.listen(1000);
			for(int i = 0;i < 1000;i++)
				clSocket[i] = NULL;
			start();

		}

		~MiniServer()
		{
			StopS();
		}

		virtual void operator()()
		{	i = 0;
			try
			{
				while(1)
				{
					clSocket[i] = new socket(lSocket.accept());
					if (b_send)
						clSocket[i]->send(binary_data("Malakas"));
					i++;
				}
			}
			catch(exception)
			{ }
		}

		// Exit server
		void StopS()
		{
		    lSocket.shutdown();
			lSocket = socket();
			join(mt::Infinity);

			for(int i = 0;i < 1000;i++)
			{
                if (clSocket[i])
                    delete clSocket[i];
                clSocket[i] = NULL;
			}
		}
	};

	int g_on_data, g_on_connected, g_on_disconnect;
	// Custom client
	class MyClient
		:public netstream_threaded
	{
	public:
	MyClient()
		:netstream_threaded()
	{}

	~MyClient()
    {	initialize_destruction();
    }


	protected:
		virtual void on_data_received(const binary_data & data)
		{	g_on_data ++;	}

		virtual void on_connected()
		{	g_on_connected ++; }

		virtual void on_disconnected()
		{	g_on_disconnect++;	}

	};

	bool test_netstream_threaded::TestCtor::OnExecute()
	{	g_on_data = g_on_connected = g_on_disconnect = 0;

		{MyClient mClient;

			if (g_on_data  != 0)
				return false;
			if (g_on_connected  != 0)
				return false;
			if (g_on_disconnect  != 0)
				return false;
		}
			if (g_on_data  != 0)
				return false;
			if (g_on_connected  != 0)
				return false;
			if (g_on_disconnect  != 0)
				return false;
		return true;
	}

	bool test_netstream_threaded::TestConnectWrong::OnExecute()
	{	g_on_data = g_on_connected = g_on_disconnect = 0;

		try
		{
			MyClient mClient;
			try{
				mClient.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(34782)));
			}
			catch(oonet::exception)
			{
				if (g_on_data  != 0)
					return false;
				if (g_on_connected  != 0)
					return false;
				if (g_on_disconnect  != 0)
					return false;
				throw;
			}
		}
		catch(oonet::exception)
		{
			if (g_on_data  != 0)
				return false;
			if (g_on_connected  != 0)
				return false;
			if (g_on_disconnect  != 0)
				return false;
			throw;
		}
		return false;
	}

	bool test_netstream_threaded::TestFastConnect::OnExecute()
	{	g_on_data = g_on_connected = g_on_disconnect = 0;
		MiniServer theServer;
		MyClient * pClient;

		for(long i = 0;i < 100; i++)
		{
		    // debug printf(" %d...", i);

			// CREATE
			pClient = new MyClient;
			if (g_on_data  != 0) return false;
			if (g_on_connected  != i) return false;
			if (g_on_disconnect  != i) return false;
			
			// CONNECT
			pClient->connect(socket_address_inet(host_inet::LOCALHOST, port_inet(55123)));
			if (g_on_data  != 0)return false;
			if (g_on_connected  != i + 1)return false;
			if (g_on_disconnect  != i)return false;

			// DESTROY
			delete pClient;

			if (g_on_data  != 0) return false;
			if (g_on_connected  != i + 1) return false;
			if (g_on_disconnect  != i + 1) return false;
			// debug  printf("OK \n");
		}
		return true;
	}

	bool test_netstream_threaded::TestConDCCon::OnExecute()
	{	g_on_data = g_on_connected = g_on_disconnect = 0;
		MiniServer theServer;
		MyClient mClient;

		// Check if it is connected
		if (mClient.connected())
			return false;

		// Connect to miniserver
		mClient.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(55123)));
		if (g_on_data  != 0) return false;
		if (g_on_connected  != 1) return false;
		if (g_on_disconnect  != 0) return false;

		// Check if it is connected
		if (!mClient.connected())
			return false;

		// Disconnect
		mClient.disconnect();
		mt::thread::sleep(1000);
		if (g_on_data  != 0) return false;
		if (g_on_connected  != 1) return false;
		if (g_on_disconnect  != 1) return false;
		

		// Check if it is connected
		if (mClient.connected())
			return false;

		// Reconnect
		mClient.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(55123)));
		if (g_on_data  != 0) return false;
		if (g_on_connected  != 2) return false;
		if (g_on_disconnect  != 1) return false;

		// Check if it is connected
		if (!mClient.connected())
			return false;

		// And same in fast mode
		for(long i = 0;i < 100;i++)
		{
			mClient.disconnect();
			// Reconnect
			mClient.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(55123)));
			if (g_on_data  != 0) return false;
			if (g_on_connected  != i+3) return false;
			if (g_on_disconnect  != i+2) return false;
		}

		return true;
	}

	bool test_netstream_threaded::TestReconnect::OnExecute()
	{	g_on_data = g_on_connected = g_on_disconnect = 0;
		MiniServer theServer;
		MyClient mClient;

		// Check if it is connected
		if (mClient.connected())
			return false;

		// Connect to miniserver
		mClient.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(55123)));
		if (g_on_data  != 0) return false;
		if (g_on_connected  != 1) return false;
		if (g_on_disconnect  != 0) return false;

		// Connect again
		mClient.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(55123)));
		if (g_on_data  != 0) return false;
		if (g_on_connected  != 2) return false;
		if (g_on_disconnect  != 1) return false;

		return true;
	}

	bool test_netstream_threaded::TestEventQuality::OnExecute()
	{	
		{g_on_data = g_on_connected = g_on_disconnect = 0;
			MiniServer theServer;
			MyClient mClient;

			// Check if it is connected
			if (mClient.connected())
				return false;

			// Connect to miniserver
			mClient.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(55123)));
			mt::thread::sleep(500);
			if (g_on_data  != 0) return false;
			if (g_on_connected  != 1) return false;
			if (g_on_disconnect  != 0) return false;

			// Connect again
			mClient.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(55123)));
			if (g_on_data  != 0) return false;
			if (g_on_connected  != 2) return false;
			if (g_on_disconnect  != 1) return false;
		}

		{g_on_data = g_on_connected = g_on_disconnect = 0;
			MiniServer theServer(true);
			MyClient mClient;

			// Check if it is connected
			if (mClient.connected())
				return false;

			// Connect to miniserver
			mClient.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(55123)));
			mt::thread::sleep(500);
			if (g_on_data  != 1) return false;
			if (g_on_connected  != 1) return false;
			if (g_on_disconnect  != 0) return false;

			// Connect again
			mClient.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(55123)));
			mt::thread::sleep(500);
			if (g_on_data  != 2) return false;
			if (g_on_connected  != 2) return false;
			if (g_on_disconnect  != 1) return false;

			mClient.disconnect();
			mt::thread::sleep(500);
			if (g_on_data  != 2) return false;
			if (g_on_connected  != 2) return false;
			if (g_on_disconnect  != 2) return false;
		}

		{g_on_data = g_on_connected = g_on_disconnect = 0;
			MiniServer theServer;
			MyClient mClient;

			// Check if it is connected
			if (mClient.connected())
				return false;

			// Connect to miniserver
			mClient.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(55123)));
			mt::thread::sleep(500);
			if (g_on_data  != 0) return false;
			if (g_on_connected  != 1) return false;
			if (g_on_disconnect  != 0) return false;

			// Stop server
			theServer.StopS();
			mt::thread::sleep(500);
			if (g_on_data  != 0) return false;
			if (g_on_connected  != 1) return false;
			if (g_on_disconnect  != 1) return false;
		}

		{g_on_data = g_on_connected = g_on_disconnect = 0;
			MiniServer theServer(true);
			MyClient mClient;

			// Check if it is connected
			if (mClient.connected())
				return false;

			// Connect to miniserver
			mClient.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(55123)));
			mt::thread::sleep(500);
			if (g_on_data  != 1) return false;
			if (g_on_connected  != 1) return false;
			if (g_on_disconnect  != 0) return false;

			// Stop server
			theServer.StopS();
			mt::thread::sleep(500);
			if (g_on_data  != 1) return false;
			if (g_on_connected  != 1) return false;
			if (g_on_disconnect  != 1) return false;
		}
		return true;
	}
};	// !oonet namespace
