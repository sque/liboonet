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
		{	disconnect();		}
	};


	//! Server templarized class
	template <class W>
	class netserver
		: private mt::thread
	{
	public:

		// Public type definitions
		typedef typename boost::shared_ptr<W> handler_shared_ptr;
		typedef typename std::list<handler_shared_ptr> handlers_pool_type;
		typedef typename handlers_pool_type::iterator handlers_pool_iterator;

	private:

		// NonCopyable
		netserver(const netserver &);
		netserver & operator=(const netserver &);

		// Private data
		socket l_socket;					// Listen socket
		bool b_zombie;						// Flag if we are in zombie mode
		handlers_pool_type m_handlers_pool;	// The pool of stream handlers

		// Thread routine
		void operator()()
		{	socket cl_socket;

			try
			{
				while(1)
				{
					// Wait for connection
					cl_socket = l_socket.accept();

					// Assign a handler
					assign_handler(cl_socket);

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

		//! Parametrize listen socket at creation time
		virtual void parametrize_listen_socket(socket & l_sock)	{}

		//! Control over handler pool management
		/**	Implementation of new client allocation, this may be overloaded
			and populated with code that recycles disconnected handlers.
			By default it creates a new one and adds it to the list.
		*/
		virtual void assign_handler(socket & cl_socket)
		{
			// Create a new handler
			handler_shared_ptr p_streamhandler(new W(this));
			m_handlers_pool.push_back(p_streamhandler);

			// Assign socket to it
			p_streamhandler->assign_socket(cl_socket);
		}

		//! Must be called at derived destructor
		void initialize_destruction()
		{
			// Enter zombie
			b_zombie = true;

			// Stop listening
			stop_listen();

			// Delete all clients
			m_handlers_pool.clear();
		}

		//! Get the pool of handlers (const)
		const handlers_pool_type & handlers_pool() const
		{	return m_handlers_pool;	}

		//! Get the pool of handlers
		handlers_pool_type & handlers_pool()
		{	return m_handlers_pool;	}

	public:

		//! Constructor
		/**
		@remarks Doesn't start the server
		*/
		netserver()
			:b_zombie(false)
		{}

		//! Destructor
		/**
			It will stop listening, and abandon all handlers.
		*/
		virtual ~netserver()
		{
			/*
				If this assertation failed
				you propably forgot to call initialize_destruction()
				from the last derived class destructor
			*/
			OONET_ASSERT(b_zombie);
		}

		//! Start listen
		void start_listen(const socket_address & l_addr, ulong back_log)
		{
			// Skip starting if we are in zombie mode
			if (b_zombie)
				return;

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

		//! Stop listen
		/**
			Already connected clients will not get disconnected.
		*/
		void stop_listen()
		{
			// Close socket and join
			l_socket = socket();
			join();
		}

		//! Check if server is listening
		inline bool listening() const
		{	return running();	}


	};
};

#endif // !OONET_NETSERVER_HPP_INCLUDED
