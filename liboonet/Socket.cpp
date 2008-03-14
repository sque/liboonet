/**
@file Socket.cpp
@brief Implementation of Socket class
*/
#include "./Socket.h"
#include <boost/scoped_ptr.hpp>
#include <algorithm>

namespace OONet
{
	// Internal implementation of socket
	class Socket::impl
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
			_handle = socket(s_family, s_type, s_proto);
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
    Socket::Socket(int s_family, int s_type, int s_proto) throw(Exception)
		:pimpl_(new impl(s_family, s_type, s_proto))
    {
    	// Check construction
    	if (pimpl_->get_socket() == INVALID_SOCKET)
			// then we throw exception
			_throw_last_error("Cannot create Socket()");
	}

	// Constructor that creates an invalid socket
	Socket::Socket()
		:pimpl_(new impl(INVALID_SOCKET))
	{}

	// Constructor to create new socket
    Socket::Socket(SOCKET _handle)
		:pimpl_(new impl(_handle))
    {}

	////////////////////////////////////////
	// OS Specific implementations
#if (OONET_OS == OONET_OS_WIN32)
	int Socket::_win32_get_last_error()
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
	int Socket::_linux_get_last_error()
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

	int Socket::_get_last_error()
	{
#if (OONET_OS == OONET_OS_WIN32)
		return _win32_get_last_error();
#elif (OONET_OS == OONET_OS_LINUX)
		return _linux_get_last_error();
#endif
	}

	void Socket::_throw_last_error(const string & ErrorMessage)
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
    BinaryData Socket::receive(size_t max_data) throw(Exception)
    {   // Allocate space for incoming data
        boost::scoped_ptr<Byte> tmp_data(new Byte[max_data]);
        int received_size;
        BinaryData received_data;

        // Get data
		received_size = ::recv(pimpl_->get_socket(), (char *)tmp_data.get(), max_data, 0);

        // Create a binary data block
        if ((received_size == INVALID_SOCKET) || (received_size <= 0))
			_throw_last_error("Cannot Socket::Receive()");

		// Return data
		received_data = BinaryData(tmp_data.get(), received_size);
		return received_data;
    }

    // Send
    size_t Socket::send(const BinaryData & trans_data) throw (Exception)
    {
        int sent = ::send(pimpl_->get_socket(),(char *) trans_data.getDataPtr(), trans_data.size(), 0);
        if (sent <= 0)
        {
			// Throw exception
			_throw_last_error("Cannot Socket::Send()");
        }
        return sent;
    }

    // Connect
    void Socket::connect(const SocketAddress & serv_addr) throw(Exception)
    {
        if (0 != ::connect(pimpl_->get_socket(), (sockaddr *) serv_addr.getSockaddrPtr(), serv_addr.size()) )
        {
			// Throw exception
			_throw_last_error("Cannot Socket::Connect()");
        }
    }

    // Bind at an addres
    void Socket::bind(const SocketAddress & local_addr) throw(Exception)
    {
        if(0 != ::bind(pimpl_->get_socket(), (sockaddr *) local_addr.getSockaddrPtr(), local_addr.size()))
        {	// Throw exception
			_throw_last_error("Cannot Socket::Bind()");
        }
    }

    // Change socket in listen mode
    void Socket:: listen(int max_connections) throw(Exception)
    {
        if (0 != ::listen(pimpl_->get_socket(), max_connections))
        {
			// Throw exception
			_throw_last_error("Cannot Socket::Listen()");
        }
    }

    // Wait for incoming connection and return socket of client
    Socket Socket::accept() throw(Exception)
    {	SOCKET temp_sock_handler;

        // Try to accept
        temp_sock_handler = ::accept(pimpl_->get_socket(), NULL, 0);

        if (temp_sock_handler == INVALID_SOCKET)
        {
			// Throw exception
			_throw_last_error("Cannot Socket::Accept()");
        }

        // Return a Socket object representing this handler
        return Socket(temp_sock_handler);
    }

    // Get the local address of the socket
    SocketAddress Socket::get_local_address() const throw(Exception)
    {
        // Ask from system the address of the local socket
        struct sockaddr l_addr;
        SOCKLEN addr_len = sizeof(sockaddr);

        getsockname(pimpl_->get_socket(),  &l_addr, &addr_len);

        // Create a SocketAddress and return it
        return SocketAddress(l_addr);
    }

    // Get the address of the peer socket
    SocketAddress Socket::get_peer_address() const throw(Exception)
    {
        // Ask from system the address of the other-end socket
        struct sockaddr p_addr;
        SOCKLEN addr_len = sizeof(sockaddr);

        getpeername(pimpl_->get_socket(),  &p_addr, &addr_len);

        // Create a SocketAddress and return it
        return SocketAddress(p_addr);
    }

    // Shutdown socket
    void Socket::shutdown() throw(Exception)
    {
    	pimpl_->shutdown();
    }

	// Set option on socket
    void Socket::set_option(int level, int opt_name, const void * opt_val, int opt_size)
    {
#if (OONET_OS == OONET_OS_LINUX)
        if (0 != setsockopt(pimpl_->get_socket(), level, opt_name, opt_val, opt_size))
            _throw_last_error("Error on setting socket option SetOption()");
#elif (OONET_OS == OONET_OS_WIN32)
		if (0 != setsockopt(pimpl_->get_socket(), level, opt_name, (char*)opt_val, opt_size))
            _throw_last_error("Error on setting socket option SetOption()");
#endif
    }

};  // !OONet namespace
