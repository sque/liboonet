/**
@file InetClient.cpp
@brief Implementation of the InetClient class.
*/
#include "./InetClient.h"

namespace Slib
{
    // Default constructor
    InetClient::InetClient()
    {	}

    // Default destructor
    InetClient::~InetClient()
    {   SLIB_DEBUG_L2(_T("~InetClient()_\n"));
		initializeDestruction();
    }

	bool InetClient::isConnected() const
	{	return InetPeer::isConnected();	}

    // Connect at a server
    void InetClient::connect(const SocketAddressInet & serv_addr) throw(Exception)
    {   SLIB_DEBUG_L2(_T("InetClient::Connect()_\n"));

		// Check if it is connected
        if (isConnected())
        {
            // Throw exception if already connected
			SLIB_THROW_EXCEPTION(ExceptionAlreadyConnected,
				"InetClient is already connected!"
				);
        }

        // Create a new socket and connect
		Socket sock = Socket(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
        sock.connect(serv_addr);

        // Connected, let the InetPeer to handle the rest
		handleSocket(sock);
    }

    void InetClient::disconnect()
	{	return InetPeer::disconnect();	}

};  // !Slib namespace
