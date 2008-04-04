#ifndef NETSERVER_HPP_INCLUDED
#define NETSERVER_HPP_INCLUDED

#include "OONet.h"
#include "netstream_threaded.hpp"
#include <list>

namespace OONet
{

	/**
		Server client handler templarized class
	*/
	template<class S>
	class netserver_clienthandler
		: public netstream_threaded
	{
	private:
		// Pointer to server that we belong at
		S * p_server;

		// NonCopyable
		netserver_clienthandler(const netserver_clienthandler &);
		netserver_clienthandler & operator=(const netserver_clienthandler &);

	protected:
		// Get server pointer
		S * get_server_ptr()
		{	return p_server;	}

	public:
		// Default constructor
		netserver_clienthandler(void * _s)
		{	p_server = static_cast<S *>(_s);	}

		// Just a default virtual destructor
		virtual ~netserver_clienthandler()
		{	disconnect();		}
	};


	/**
		Server templarized class
	*/
	template <class C>
	class netserver
		: private MT::thread
	{
	private:
		// NonCopyable
		netserver(const netserver &);
		netserver & operator=(const netserver &);

		// Private data
		Socket l_socket;			// Listen socket
		bool b_zombie;				// Flag if we are in zombie mode

		// Thread routine
		void thread_routine()
		{	Socket cl_socket;

			try
			{
				while(1)
				{
					// Wait for connection
					cl_socket = l_socket.accept();

					// Allocate new handler
					C * p_netstream_client = impl_new_handler(cl_socket);

					// Start handling
					p_netstream_client->assign_socket(cl_socket);

					// Abandon client socket
					cl_socket = Socket();
				}
			}
			catch(Exception & e)
			{
				printf("Error %s\n", e.getReport().c_str());
				// Abandon sockets
				l_socket = Socket();
				cl_socket = Socket();
			}
		}


	protected:
		// Parametrize listen socket at creation time
		virtual void parametrize_listen_socket(Socket & l_sock)	{}

		/*	Implementation of new client allocation, this may be overloaded
			and populated with code that recycles disconnected handlers.
			By default it creates a new one and adds it to the list.
		*/
		virtual C * impl_new_handler(Socket & cl_socket)
		{
			// Create a new handler
			C * p_tmp_server_streamhandler = new C(this);
			v_pclients.push_back(p_tmp_server_streamhandler);

			return p_tmp_server_streamhandler;
		}

		// Clients list
		typedef typename std::list<C *>::iterator client_iterator;
		std::list<C *> v_pclients;

		// Must be called to enter zombie mode
		void initialize_destruction()
		{	client_iterator it;

			// Enter zombie
			b_zombie = true;

			// Stop listening
			if (listening())
				stop_listen();

			// Delete all clients
			while((it = v_pclients.begin()) != v_pclients.end())
			{	delete (*it);
				v_pclients.erase(it);
			}
		}

	public:
		// Constructor
		netserver()
			:b_zombie(false)
		{}

		// Destructor
		virtual ~netserver()
		{
			/*
				If this assertation failed
				you propably forgot to call initialize_destruction()
				from the last derived class destructor
			*/
			OONET_ASSERT(b_zombie);
		}

		// start listen
		void start_listen(const SocketAddress & l_addr, ulong back_log)
		{
			if(listening())
				OONET_THROW_EXCEPTION(ExceptionAlreadyConnected,
					"Server is already started!!!");

			// Create socket
			l_socket = Socket(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);

			// Pass user defined parameters
			parametrize_listen_socket(l_socket);

			// Bind and turn in listen mode
			l_socket.bind(l_addr);
			l_socket.listen(back_log);

			// Start listening thread
			start();
		}

		// stop listen
		void stop_listen()
		{
			// Close socket and join
			l_socket = Socket();
			join();
		}

		// Check if server is listening
		inline bool listening() const
		{	return running();	}

		// Get the list of all clients
		const std::list<C *> & get_clients() const
		{	return v_pclients;	}
	};
};


#endif // NETSERVER_HPP_INCLUDED
