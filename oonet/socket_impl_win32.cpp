#include "./socket.hpp"

namespace oonet
{
	//! System specific throw last error
	void socket::_throw_last_error(const string & ErrorMessage) const
	{	
		// Get WSA last error
		int wsa_error = WSAGetLastError();

		// Throw proper exception
		switch(wsa_error)
		{
		case WSAEISCONN:
			OONET_THROW_EXCEPTION(ExceptionAlreadyConnected, ErrorMessage);
		case WSAEACCES:
			OONET_THROW_EXCEPTION(ExceptionAccessDenied, ErrorMessage);
		case WSAENOTCONN:
			OONET_THROW_EXCEPTION(ExceptionNotConnected, ErrorMessage);
		case WSAENOTSOCK:
			OONET_THROW_EXCEPTION(ExceptionInvalidSocket, ErrorMessage);
		case WSAEADDRINUSE:
			OONET_THROW_EXCEPTION(ExceptionAddressInUse, ErrorMessage);
		case WSAEOPNOTSUPP:
		case WSAESOCKTNOSUPPORT:
			OONET_THROW_EXCEPTION(ExceptionNotSupported, ErrorMessage);
		case WSAECONNABORTED:
			OONET_THROW_EXCEPTION(ExceptionConnectionAborted, ErrorMessage);
		case WSAEINVAL:
			OONET_THROW_EXCEPTION(ExceptionWrongArgument, ErrorMessage);
		case WSAEADDRNOTAVAIL:
			OONET_THROW_EXCEPTION(ExceptionAddressNotAvailable, ErrorMessage);
		case WSAECONNREFUSED:
			OONET_THROW_EXCEPTION(ExceptionConnectionRefused, ErrorMessage);
		case WSAECONNRESET:
			OONET_THROW_EXCEPTION(ExceptionConnectionReset, ErrorMessage);
		};

		// Generic exception default
		OONET_THROW_EXCEPTION(ExceptionSystemError, ErrorMessage);
	}

};	// !oonet namespace