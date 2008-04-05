/**
@file Socket.cpp
@brief Implementation of Socket class
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
		SOCKET _handle;
	public:

		// Construct a new socket
		impl(int s_family, int s_type, int s_proto)
		{
			_handle = ::socket(s_family, s_type, s_proto);
			//printf("new socket %d\n", _handle);
		}

		// Assign an existing socket handle
		explicit impl(SOCKET _assigned_handle)
			:_handle(_assigned_handle)
		{}

		// Destructor
		~impl()
		{
			if (_handle != INVALID_SOCKET)
			{
				//printf("socket abandoned(%d)\n", _handle);
				shutdown();
				CLOSESOCKET(_handle);
			}
		}

		// Implementation of shutdown
		void shutdown()
		{
#if (OONET_OS == OONET_OS_LINUX)
			::shutdown(_handle, SHUT_RDWR);
#elif (OONET_OS == OONET_OS_WIN32)
			::shutdown(_handle, SD_BOTH);
#endif
		}

		// Get socket that we are refereeing to
		SOCKET get_socket()
		{	return _handle;	}

	};	// !impl class


    // Constructor to create new socket
    socket::socket(int s_family, int s_type, int s_proto) throw(exception)
		:pimpl_(new impl(s_family, s_type, s_proto))
    {
    	// Check construction
    	if (pimpl_->get_socket() == INVALID_SOCKET)
			// then we throw exception
			_throw_last_error("Cannot create Socket()");
	}

	// Constructor that creates an invalid socket
	socket::socket() throw()
		:pimpl_(new impl(INVALID_SOCKET))
	{}

	// Constructor to create new socket
    socket::socket(SOCKET _handle) throw()
		:pimpl_(new impl(_handle))
    {}

	// Internal errors enumeration
	enum InternalErrrors
	{
		ERR_UNKNWON,			//!< Unknown error
		ERR_ALREADY_CONNECTED,	//!< Already connected error
		ERR_NOT_CONNECTED,		//!< This operation requires a connected socket
		ERR_ACCESS_DENIED,		//!< Access denied
		ERR_NOT_A_SOCKET,		//!< Error this is not a socket
		ERR_ADDRESS_IN_USE,		//!< Address is already in use
		ERR_ADDRESS_NOT_AVAIL,	//!< Address is not available
		ERR_NOT_SUPPORTED,		//!< Operation not supported
		ERR_CONNECTION_ABORTED,	//!< Connection aborted
		ERR_CONNECTION_REFUSED, //!< Connection Refused
		ERR_CONNECTION_RESET,	//!< Connection reset by peer
		ERR_INVALID_ARGUMENT,	//!< Invalid argument
	};

	////////////////////////////////////////
	// OS Specific implementations
#if (OONET_OS == OONET_OS_WIN32)
	int socket::_win32_get_last_error() const
	{
		int errorNum;
		errorNum = WSAGetLastError();
		switch(errorNum)
		{
		case WSAEISCONN:
			return ERR_ALREADY_CONNECTED;
		case WSAEACCES:
			return ERR_ACCESS_DENIED;
		case WSAENOTCONN:
			return ERR_NOT_CONNECTED;
		case WSAENOTSOCK:
			return ERR_NOT_A_SOCKET;
		case WSAEADDRINUSE:
			return ERR_ADDRESS_IN_USE;
		case WSAEOPNOTSUPP:
		case WSAESOCKTNOSUPPORT:
			return ERR_NOT_SUPPORTED;
		case WSAECONNABORTED:
			return ERR_CONNECTION_ABORTED;
		case WSAEINVAL:
			return ERR_INVALID_ARGUMENT;
		case WSAEADDRNOTAVAIL:
			return ERR_ADDRESS_NOT_AVAIL;
		case WSAECONNREFUSED:
			return ERR_CONNECTION_REFUSED;
		case WSAECONNRESET:
			return ERR_CONNECTION_RESET;
		default:
			return ERR_UNKNWON;
		}
	}
#elif (OONET_OS == OONET_OS_LINUX)
	int socket::_linux_get_last_error() const
	{
		switch(errno)
		{
		case EISCONN:
			return ERR_ALREADY_CONNECTED;
		case EACCES:
			return ERR_ACCESS_DENIED;
		case ENOTSOCK:
			return ERR_NOT_A_SOCKET;
		case EADDRINUSE:
			return ERR_ADDRESS_IN_USE;
		case EOPNOTSUPP:
			return ERR_NOT_SUPPORTED;
		case ECONNABORTED:
			return ERR_CONNECTION_ABORTED;
		case EINVAL:
			return ERR_INVALID_ARGUMENT;
        case ECONNREFUSED:
            return ERR_CONNECTION_REFUSED;
        case EAFNOSUPPORT:
        case EPROTONOSUPPORT:
            return ERR_NOT_SUPPORTED;
        case EADDRNOTAVAIL:
            return ERR_ADDRESS_NOT_AVAIL;
		default:
			return ERR_UNKNWON;
		}
	}
#endif

	int socket::_get_last_error() const
	{
#if (OONET_OS == OONET_OS_WIN32)
		return _win32_get_last_error();
#elif (OONET_OS == OONET_OS_LINUX)
		return _linux_get_last_error();
#endif
	}

	void socket::_throw_last_error(const string & ErrorMessage) const
	{	int errcode = _get_last_error();

		switch(errcode)
		{
		case ERR_ALREADY_CONNECTED:
			OONET_THROW_EXCEPTION(ExceptionAlreadyConnected, ErrorMessage);
		case ERR_ACCESS_DENIED:
			OONET_THROW_EXCEPTION(ExceptionAccessDenied, ErrorMessage);
		case ERR_NOT_A_SOCKET:
			OONET_THROW_EXCEPTION(ExceptionInvalidSocket, ErrorMessage);
		case ERR_ADDRESS_IN_USE:
			OONET_THROW_EXCEPTION(ExceptionAddressInUse, ErrorMessage);
		case ERR_NOT_SUPPORTED:
			OONET_THROW_EXCEPTION(ExceptionNotSupported, ErrorMessage);
		case ERR_CONNECTION_ABORTED:
			OONET_THROW_EXCEPTION(ExceptionConnectionAborted, ErrorMessage);
		case ERR_INVALID_ARGUMENT:
			OONET_THROW_EXCEPTION(ExceptionWrongArgument, ErrorMessage);
		case ERR_NOT_CONNECTED:
			OONET_THROW_EXCEPTION(ExceptionNotConnected, ErrorMessage);
		case ERR_ADDRESS_NOT_AVAIL:
			OONET_THROW_EXCEPTION(ExceptionAddressNotAvailable, ErrorMessage);
		case ERR_CONNECTION_REFUSED:
			OONET_THROW_EXCEPTION(ExceptionConnectionRefused, ErrorMessage);
		case ERR_CONNECTION_RESET:
			OONET_THROW_EXCEPTION(ExceptionConnectionReset, ErrorMessage);
		}

		// Default
		OONET_THROW_EXCEPTION(ExceptionSystemError, ErrorMessage);
	}


    // Receive action
    binary_data socket::receive(size_t max_data) throw(exception)
    {	int received_size;

        // Allocate space for incoming data
        binary_data received_data((byte)'\0', max_data);

        // Get data
		received_size = ::recv(pimpl_->get_socket(), (char *)received_data.get_data_ptr(), max_data, 0);

        // Create a binary data block
        if ((received_size == INVALID_SOCKET) || (received_size <= 0))
			_throw_last_error("Cannot Socket::receive()");

		// Return data
		return received_data.get_until(received_size);
    }

    // Send
    size_t socket::send(const binary_data & trans_data) throw (exception)
    {
        int sent = ::send(pimpl_->get_socket(),(char *) trans_data.get_data_ptr(), trans_data.size(), 0);
        if (sent <= 0)
        {
			// Throw exception
			_throw_last_error("Cannot Socket::send()");
        }
        return sent;
    }

    // Connect
    void socket::connect(const socket_address & serv_addr) throw(exception)
    {
        if (0 != ::connect(pimpl_->get_socket(), (sockaddr *) serv_addr.sockaddr_ptr(), serv_addr.size()) )
        {
			// Throw exception
			_throw_last_error("Cannot Socket::connect()");
        }
    }

    // Bind at an addres
    void socket::bind(const socket_address & local_addr) throw(exception)
    {
        if(0 != ::bind(pimpl_->get_socket(), (sockaddr *) local_addr.sockaddr_ptr(), local_addr.size()))
        {	// Throw exception
			_throw_last_error("Cannot Socket::bind()");
        }
    }

    // Change socket in listen mode
    void socket:: listen(int max_connections) throw(exception)
    {
        if (0 != ::listen(pimpl_->get_socket(), max_connections))
        {
			// Throw exception
			_throw_last_error("Cannot Socket::listen()");
        }
    }

    // Wait for incoming connection and return socket of client
    socket socket::accept() throw(exception)
    {	SOCKET temp_sock_handler;

        // Try to accept
        temp_sock_handler = ::accept(pimpl_->get_socket(), NULL, 0);

        if (temp_sock_handler == INVALID_SOCKET)
        {
			// Throw exception
			_throw_last_error("Cannot Socket::accept()");
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
			_throw_last_error("Cannot Socket::get_local_address()");

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
			_throw_last_error("Cannot Socket::get_peer_address()");

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
            _throw_last_error("Error on setting socket option set_option()");
    }

};  // !oonet namespace
