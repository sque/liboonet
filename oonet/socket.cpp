/**
@file socket.cpp
@brief Implementation of socket class
*/
#include "./socket.hpp"

#include <boost/scoped_array.hpp>
#include <algorithm>

namespace oonet
{
	// Internal implementation of socket
	class socket::impl
	{
	private:
		impl(const impl & );
		impl & operator=(const impl &);

		// Handle to socket
		native_handle_type _handle;
	public:

		// Construct a new socket
		impl(int s_family, int s_type, int s_proto)
		{
			_handle = ::socket(s_family, s_type, s_proto);
		}

		// Assign an existing socket handle
		explicit impl(native_handle_type _assigned_handle)
			:_handle(_assigned_handle)
		{}

		// Destructor
		~impl()
		{
			if (_handle != INVALID_SOCKET)
			{
				shutdown();
				CLOSESOCKET(_handle);
			}
		}

		// Implementation of shutdown
		void shutdown()
		{
#if (OONET_OS_API == OONET_OS_API_WIN32)
			::shutdown(_handle, SD_BOTH);
#else
			::shutdown(_handle, SHUT_RDWR);
#endif
		}

		// Get socket that we are refereeing to
		native_handle_type get_socket()
		{	return _handle;	}

	};	// !impl class


    // Constructor to create new socket
    socket::socket(int s_family, int s_type, int s_proto) throw(exception)
		:pimpl_(new impl(s_family, s_type, s_proto))
    {
    	// Check construction
    	if (pimpl_->get_socket() == INVALID_SOCKET)
			// then we throw exception
			_throw_last_error("Cannot create socket(int, int, int)");
	}

	// Constructor that creates an invalid socket
	socket::socket() throw()
		:pimpl_(new impl(INVALID_SOCKET))
	{}

	// Constructor to create new socket
    socket::socket(native_handle_type _handle) throw()
		:pimpl_(new impl(_handle))
    {}

    // Receive action
    binary_data socket::receive(size_t max_data) throw(exception)
    {	int received_size;

        // Allocate space for incoming data
        binary_data received_data(max_data);

        // Get data
		received_size = ::recv(pimpl_->get_socket(), (char *)received_data.c_array(), max_data, 0);

        // Create a binary data block
        if ((received_size == INVALID_SOCKET) || (received_size <= 0))
			_throw_last_error("Cannot socket::receive()");

		// Return data
		return received_data.get_until(received_size);
    }

    // Send
    size_t socket::send(const binary_data & trans_data) throw (exception)
    {
        int sent = ::send(pimpl_->get_socket(),(char *) trans_data.c_array(), trans_data.size(), 0);
        if (sent <= 0)
        {
			// Throw exception
			_throw_last_error("Cannot socket::send()");
        }
        return sent;
    }

    // Connect
    void socket::connect(const socket_address & serv_addr) throw(exception)
    {
        if (0 != ::connect(pimpl_->get_socket(), (sockaddr *) serv_addr.sockaddr_ptr(), serv_addr.size()) )
        {
			// Throw exception
			_throw_last_error("Cannot socket::connect()");
        }
    }

    // Bind at an addres
    void socket::bind(const socket_address & local_addr) throw(exception)
    {
        if(0 != ::bind(pimpl_->get_socket(), (sockaddr *) local_addr.sockaddr_ptr(), local_addr.size()))
        {	// Throw exception
			_throw_last_error("Cannot socket::bind()");
        }
    }

    // Change socket in listen mode
    void socket:: listen(int max_connections) throw(exception)
    {
        if (0 != ::listen(pimpl_->get_socket(), max_connections))
        {
			// Throw exception
			_throw_last_error("Cannot socket::listen()");
        }
    }

    // Wait for incoming connection and return socket of client
    socket socket::accept() throw(exception)
    {	native_handle_type temp_sock_handler;

        // Try to accept
        temp_sock_handler = ::accept(pimpl_->get_socket(), NULL, 0);

        if (temp_sock_handler == INVALID_SOCKET)
        {
			// Throw exception
			_throw_last_error("Cannot socket::accept()");
        }

        // Return a Socket object representing this handler
        return socket(temp_sock_handler);
    }

    // Get the local address of the socket
    socket_address socket::get_local_address() const throw(exception)
    {
        // Ask from system the address of the local socket
        struct sockaddr l_addr;
        SOCKLEN addr_len = sizeof(sockaddr);

        if (0 != ::getsockname(pimpl_->get_socket(),  &l_addr, &addr_len))
			_throw_last_error("Cannot socket::get_local_address()");

        // Create a SocketAddress and return it
        return socket_address(l_addr);
    }

    // Get the address of the peer socket
    socket_address socket::get_peer_address() const throw(exception)
    {
        // Ask from system the address of the other-end socket
        struct sockaddr p_addr;
        SOCKLEN addr_len = sizeof(sockaddr);

        if (0 != ::getpeername(pimpl_->get_socket(),  &p_addr, &addr_len))
			_throw_last_error("Cannot socket::get_peer_address()");

        // Create a SocketAddress and return it
        return socket_address(p_addr);
    }

    // Shutdown socket
    void socket::shutdown() throw()
    {
    	pimpl_->shutdown();
    }

	// Set option on socket
    void socket::set_option(int level, int opt_name, const void * opt_val, int opt_size) throw(exception)
    {
        if (0 != setsockopt(pimpl_->get_socket(), level, opt_name, (char*)opt_val, opt_size))
			_throw_last_error("Error on setting socket option socket::set_option()");
    }

};  // !oonet namespace
