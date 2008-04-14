#ifndef OONET_NETSERVER_HPP_INCLUDED
#define OONET_NETSERVER_HPP_INCLUDED

#include "./oonet.hpp"
#include "./netstream_threaded.hpp"

#include <list>
#include <boost/shared_ptr.hpp>

namespace oonet
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
		{	disconnect();
			get_server_ptr()->_remove_handler(this);
		}
	};


	/**
		Server templarized class
	*/
	template <class W>
	class netserver
		: private mt::thread
	{
	public:
		typedef typename boost::shared_ptr<W> handler_shared_ptr;
		template<class S>friend class netserver_clienthandler;

	private:
		void _remove_handler(void * _byebye_handler)
		{	client_iterator it;
			for(it = v_pclients.begin();it != v_pclients.end();it++)
			{
				if (it->get() == _byebye_handler)
				{
					v_pclients.erase(it);
					return;
				}
			}
		};

		// NonCopyable
		netserver(const netserver &);
		netserver & operator=(const netserver &);

		// Private data
		socket l_socket;			// Listen socket
		bool b_zombie;				// Flag if we are in zombie mode

		// Thread routine
		void operator()()
		{	socket cl_socket;

			try
			{
				while(1)
				{
					// Wait for connection
					cl_socket = l_socket.accept();

					// Allocate new handler
					handler_shared_ptr p_netstream_client = impl_new_handler(cl_socket);

					// Start handling
					p_netstream_client->assign_socket(cl_socket);

					// Abandon client socket
					cl_socket = socket();
				}
			}
			catch(exception)
			{
				// Abandon sockets
				l_socket = socket();
				cl_socket = socket();
			}
		}


	protected:
		// Parametrize listen socket at creation time
		virtual void parametrize_listen_socket(socket & l_sock)	{}

		/*	Implementation of new client allocation, this may be overloaded
			and populated with code that recycles disconnected handlers.
			By default it creates a new one and adds it to the list.
		*/
		virtual handler_shared_ptr impl_new_handler(socket & cl_socket)
		{
			// Create a new handler
			handler_shared_ptr p_streamhandler(new W(this));
			v_pclients.push_back(p_streamhandler);

			return p_streamhandler;
		}

		// Clients list
		typedef typename std::list<handler_shared_ptr>::iterator client_iterator;
		std::list<handler_shared_ptr> v_pclients;

		// Must be called to enter zombie mode
		void initialize_destruction()
		{	client_iterator it;

			// Enter zombie
			b_zombie = true;

			// Stop listening
			if (listening())
				stop_listen();

			// Delete all clients
			v_pclients.clear();
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
		void start_listen(const socket_address & l_addr, ulong back_log)
		{
			if(listening())
				OONET_THROW_EXCEPTION(ExceptionAlreadyConnected,
					"Server is already started!!!");

			// Create socket
			l_socket = socket(socket::FAMILY_INET, socket::TYPE_STREAM, socket::PROTO_DEFAULT);

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
			l_socket = socket();
			join();
		}

		// Check if server is listening
		inline bool listening() const
		{	return running();	}

		// Get the list of all clients
		const std::list<handler_shared_ptr> & get_clients() const
		{	return v_pclients;	}
	};
};


#endif // !OONET_NETSERVER_HPP_INCLUDED
