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
		virtual ~netserver_clienthandler(){}
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
		std::list<C *> v_pclients;	// Pointer to clients list
		typedef typename std::list<C *>::iterator client_iterator;

		// Thread routine
		void thread_routine()
		{	Socket cl_socket;

			try
			{
				while(1)
				{
					// Wait for connection
					cl_socket = l_socket.accept();

					// Create a new handler
					C * p_netstream_client = new C(this);
					v_pclients.push_back(p_netstream_client);

					// Start handling
					p_netstream_client->assign_socket(cl_socket);

					// Abandon client socket
					cl_socket = Socket();
				}
			}
			catch(Exception & e)
			{
				printf("ERROR!!! %s", e.getReport().c_str());

				// Abandon sockets
				l_socket = Socket();
				cl_socket = Socket();
			}
		}


	protected:
		// Parametrize listen socket at creation time
		virtual void parametrize_listen_socket(Socket & l_sock)	{}

	public:
		// Constructor
		netserver()
		{}

		// Destructor
		virtual ~netserver()
		{	client_iterator it;

			// Stop listening
			if (listening())
				stop_listen();

			// Close all clients
			for(it = v_pclients.begin();it != v_pclients.end();it++)
			{	delete (*it);	}
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
