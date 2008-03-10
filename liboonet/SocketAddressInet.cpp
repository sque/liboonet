/**
 @file SocketAddressInet.cpp
 @brief Implementation of the SocketAddressInet class.
 */

#include "./SocketAddressInet.h"

namespace OONet
{

    // Constructor with host and port
    SocketAddressInet::SocketAddressInet(const HostInet & host, const PortInet & port):
        SocketAddress(FAMILY_INET)
    {
        // Point to storage
		setPortInet(port);
        setHostInet(host);
    }


    // Constructor from an already SocketAddress
    SocketAddressInet::SocketAddressInet(const SocketAddress & r):
        SocketAddress(FAMILY_INET)
    {   // Check that family is inet
        OONET_ASSERT(r.getAddressFamily() == FAMILY_INET);
        // Copy data
		SocketAddress::operator=(r);
    }
};  // !OONet namespace
