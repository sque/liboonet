#include "netstream_threaded.hpp"

namespace oonet
{

	netstream_threaded::netstream_threaded()
		:b_zombie(false),
		b_connected(false)
	{
		// start thread
		start();
	}


	netstream_threaded::~netstream_threaded()
	{
		b_zombie = true;

		// Assure that we are disconnected
		disconnect();

		// post new socket event
		sem_newsocket.post();
		join();
	}


	void netstream_threaded::thread_routine()
	{	binary_data tmp_data;

		// Post disconnect once the disconnect
		sem_disconnect.post();

		while(1)
		{
			// Wait for new socket
			sem_newsocket.wait();

			// On zombie mode exit
			if (b_zombie)
				return;

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
			catch(std::exception){}

			// We got disconnected
			b_connected = false;
			netstream::disconnect();	// Disconnect for sure
			on_disconnected();

			// Post event
			sem_disconnect.post();
		}
	}

	void netstream_threaded::pre_newsocket_impl(Socket & n_sock)
	{
		// Disconnect if needed
		disconnect();
		sem_disconnect.wait();

	}

	void netstream_threaded::post_newsocket_impl()
	{
		// Start gathering thread
		sem_newsocket.post();
		sem_connect.wait();
	}

};	// !OOnet
