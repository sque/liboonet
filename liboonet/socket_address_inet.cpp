/**
 @file socket_address_inet.cpp
 @brief Implementation of the socket_address_inet class.
 */

#include "./socket_address_inet.hpp"

namespace oonet
{

    // Constructor with host and port
    socket_address_inet::socket_address_inet(const host_inet & host, const port_inet & port):
        socket_address(FAMILY_INET)
    {
        // Point to storage
		set_port(port);
        set_host(host);
    }


    // Constructor from an already SocketAddress
    socket_address_inet::socket_address_inet(const socket_address & r):
        socket_address(FAMILY_INET)
    {
    	// Check that family is inet
        OONET_ASSERT(r.family() == FAMILY_INET);

        // Copy data
		socket_address::operator=(r);
    }
};  // !oonet namespace
