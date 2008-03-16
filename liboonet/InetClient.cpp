/**
@file InetClient.cpp
@brief Implementation of the InetClient class.
*/
#include "./InetClient.h"

namespace OONet
{
    // Default constructor
    InetClient::InetClient()
    {	}

    // Default destructor
    InetClient::~InetClient()
    {
		initialize_destruction();
    }

	bool InetClient::isConnected() const
	{	return InetPeer::connected();	}

    // Connect at a server
    void InetClient::connect(const SocketAddressInet & serv_addr) throw(Exception)
    {
		// Check if it is connected
        if (isConnected())
        {
            // Throw exception if already connected
			OONET_THROW_EXCEPTION(ExceptionAlreadyConnected,
				"InetClient is already connected!"
				);
        }

        // Create a new socket and connect
		Socket sock = Socket(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);
        sock.connect(serv_addr);

        // Connected, let the InetPeer to handle the rest
		handle_connection(sock);
    }

    void InetClient::disconnect()
	{	return InetPeer::disconnect();	}

};  // !OONet namespace
