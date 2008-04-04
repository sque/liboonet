#include "netstream_threaded.hpp"

namespace OONet
{

	netstream_threaded::netstream_threaded()
		:b_connected(false)
	{}


	netstream_threaded::~netstream_threaded()
	{	// Assure that we are disconnected
		disconnect();
		join();
	}


	void netstream_threaded::thread_routine()
	{	BinaryData tmp_data;

		// We must be connected
		b_connected = true;
		on_connected();
		sem_connect.post();

		try{

			while(1)
			{
				tmp_data = netstream::receive(1024);
				on_data_received(tmp_data);
			}
		}
		catch(std::exception &){}

		b_connected = false;
		netstream::disconnect();	// Disconnect for sure
		on_disconnected();
	}

	void netstream_threaded::pre_newsocket_impl(Socket & n_sock)
	{
		// Disconnect if needed
		if (b_connected)
		{
			disconnect();
			join();
		}
	}

	void netstream_threaded::post_newsocket_impl()
	{
		// Start gathering thread
		start();
		sem_connect.wait();
	}

};	// !OOnet
