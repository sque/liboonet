/**
@file Socket.cpp
@brief Implementation of Socket class
*/
#include "./Socket.h"
#include <algorithm>

namespace OONet
{
	MULTIREFERNCE_OBJECTFILE(Socket, SOCKET);

    // Constructor to create new socket
    Socket::Socket(int s_family, int s_type, int s_proto) throw(Exception)
		:MultiReference<Socket, SOCKET>(INVALID_SOCKET)
    {	SOCKET tmp_sock_handl;

		// We try to create socket
        if ((tmp_sock_handl = socket(s_family, s_type, s_proto)) == INVALID_SOCKET)
		{
			// We Declare start destruction so that MultiReferences constructur works smoothly
			StartDestruction();

			// then we throw exception
			_throw_last_error("Cannot create Socket()");
		};
        // Save handle
		SetHandle(tmp_sock_handl);
    }

    // Copy constructor
    Socket::Socket(const Socket &r)
		:MultiReference<Socket, SOCKET>(r)
    { }

    // Destructor
    Socket::~Socket()
	{
		StartDestruction();
	}

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


    // Assignment operator
    Socket &Socket::operator=(const Socket &r)
    {
		// Safe copy handle
		SafeCopy(r);
        return (*this);
    }

    // Receive action
    BinaryData Socket::receive(size_t max) throw(Exception)
    {   // Allocate space for incoming data
        Byte * pTemp = new Byte[max];
        int szReceived;
        BinaryData received;

        // Get data
		szReceived = ::recv(GetHandle(), (char *)pTemp, max, 0);

        // Create a binary data block
        if ((szReceived != INVALID_SOCKET) && (szReceived > 0))
        {
            received = BinaryData(pTemp, szReceived);
            delete [] pTemp;
        }
        else
        {
			// Free memory
            delete [] pTemp;
			// Throw exception
			_throw_last_error("Cannot Socket::Receive()");
        }
        return received;
    }

    // Send
    size_t Socket::send(const BinaryData & trans_data) throw (Exception)
    {
        int sent = ::send(GetHandle(),(char *) trans_data.getDataPtr(), trans_data.size(), 0);
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
        if (0 != ::connect(GetHandle(), (sockaddr *) serv_addr.getSockaddrPtr(), serv_addr.size()) )
        {
			// Throw exception
			_throw_last_error("Cannot Socket::Connect()");
        }
    }

    // Bind at an addres
    void Socket::bind(const SocketAddress & local_addr) throw(Exception)
    {
        if(0 != ::bind(GetHandle(), (sockaddr *) local_addr.getSockaddrPtr(), local_addr.size()))
        {	// Throw exception
			_throw_last_error("Cannot Socket::Bind()");
        }
    }

    // Change socket in listen mode
    void Socket:: listen(int max_connections) throw(Exception)
    {
        if (0 != ::listen(GetHandle(), max_connections))
        {
			// Throw exception
			_throw_last_error("Cannot Socket::Listen()");
        }
    }

    // Wait for incoming connection and return socket of client
    Socket Socket::accept() throw(Exception)
    {
        SOCKET temp_sock_handler;

        // Try to accept
        temp_sock_handler = ::accept(GetHandle(), NULL, 0);

        if (temp_sock_handler == INVALID_SOCKET)
        {
			// Throw exception
			_throw_last_error("Cannot Socket::Accept()");
        }

        // Return a Socket object representing this handler
        return Socket(temp_sock_handler);
    }

    // Get the local address of the socket
    SocketAddress Socket::getLocalAddress() const throw(Exception)
    {
        // Ask from system the address of the local socket
        struct sockaddr l_addr;
        SOCKLEN addr_len = sizeof(sockaddr);

        getsockname(GetHandle(),  &l_addr, &addr_len);

        // Create a SocketAddress and return it
        return SocketAddress(l_addr);
    }

    // Get the address of the peer socket
    SocketAddress Socket::getPeerAddress() const throw(Exception)
    {
        // Ask from system the address of the other-end socket
        struct sockaddr p_addr;
        SOCKLEN addr_len = sizeof(sockaddr);

        getpeername(GetHandle(),  &p_addr, &addr_len);

        // Create a SocketAddress and return it
        return SocketAddress(p_addr);
    }

    // Shutdown socket
    void Socket::shutdown() throw(Exception)
    {
#if (OONET_OS == OONET_OS_LINUX)
        ::shutdown(GetHandle(), SHUT_RDWR);
#elif (OONET_OS == OONET_OS_WIN32)
		::shutdown(GetHandle(), SD_BOTH);
#endif
    }

	// Close socket
	void Socket::close()
	{
		// Close previous socket
		CLOSESOCKET(GetHandle());

		// Abandon socket
		if (GetHandle() != INVALID_SOCKET)
			SetHandle(INVALID_SOCKET);
	}

	// Set option on socket
    void Socket::setOption(int level, int opt_name, const void * opt_val, int opt_size)
    {
#if (OONET_OS == OONET_OS_LINUX)
        if (0 != setsockopt(GetHandle(), level, opt_name, opt_val, opt_size))
            _throw_last_error("Error on setting socket option SetOption()");
#elif (OONET_OS == OONET_OS_WIN32)
		if (0 != setsockopt(GetHandle(), level, opt_name, (char*)opt_val, opt_size))
            _throw_last_error("Error on setting socket option SetOption()");
#endif
    }

};  // !OONet namespace
