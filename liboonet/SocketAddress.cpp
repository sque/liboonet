/**
@file SocketAddress.cpp
@brief Implementation of SocketAddress class
*/
#include "SocketAddress.h"

namespace OONet
{
	// Construct with family
	SocketAddress::SocketAddress(int addr_family) throw()
	{   // Initialize array
		memset(&mSockAddr, 0, sizeof(sockaddr));

		// Set family
		mSockAddr.sa_family = addr_family;
	}

	// Construct from a berkley sockaddr structure
	SocketAddress::SocketAddress(const struct sockaddr &mAddr) throw()
	{	memcpy(&mSockAddr, &mAddr, sizeof(sockaddr));	}

	// Copy constructor
	SocketAddress::SocketAddress(const SocketAddress &r) throw()
	{   memcpy(&mSockAddr, &r.mSockAddr, sizeof(struct sockaddr));  }

	// Copy operator
	SocketAddress & SocketAddress::operator=(const SocketAddress &r) throw()
	{
		memcpy(&mSockAddr, &r.mSockAddr, sizeof(struct sockaddr));
		return *this;
	}

	// Equal comparison operator
	bool SocketAddress::operator==(const SocketAddress &r) throw()
	{   return (0 == memcmp(&mSockAddr, &r.mSockAddr, size()));   }

	// Not equal comparison operator
	bool SocketAddress::operator!=(const SocketAddress &r) throw()
	{   return !(*this == r);   }

	// Get a pointer to berkley sockaddr structure
	const struct sockaddr * SocketAddress::getSockaddrPtr() const throw()
	{   return &mSockAddr;        }
};	// !OONet namespace
