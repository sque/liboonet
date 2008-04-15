#include "./socket.hpp"

namespace oonet
{
	//! System specific throw last error
	void socket::_throw_last_error(const string & ErrorMessage) const
	{
		// Throw the exception specific to this error
		switch(errno)
		{
		case EISCONN:
			OONET_THROW_EXCEPTION(ExceptionAlreadyConnected, ErrorMessage);
		case EACCES:
			OONET_THROW_EXCEPTION(ExceptionAccessDenied, ErrorMessage);
		case ENOTSOCK:
			OONET_THROW_EXCEPTION(ExceptionInvalidSocket, ErrorMessage);
		case EADDRINUSE:
			OONET_THROW_EXCEPTION(ExceptionAddressInUse, ErrorMessage);
		case ECONNABORTED:
			OONET_THROW_EXCEPTION(ExceptionConnectionAborted, ErrorMessage);
		case EINVAL:
			OONET_THROW_EXCEPTION(ExceptionWrongArgument, ErrorMessage);
        case ECONNREFUSED:
            OONET_THROW_EXCEPTION(ExceptionConnectionRefused, ErrorMessage);
        case EAFNOSUPPORT:
        case EPROTONOSUPPORT:
            OONET_THROW_EXCEPTION(ExceptionNotSupported, ErrorMessage);
        case EADDRNOTAVAIL:
            OONET_THROW_EXCEPTION(ExceptionAddressNotAvailable, ErrorMessage);
		};

		// Generic exception default
		OONET_THROW_EXCEPTION(ExceptionSystemError, ErrorMessage);
	}
};	// !oonet namespace