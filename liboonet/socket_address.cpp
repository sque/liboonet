/**
@file SocketAddress.cpp
@brief Implementation of SocketAddress class
*/
#include "./socket_address.hpp"

namespace oonet
{
	// Construct with family
	socket_address::socket_address(int addr_family) throw()
	{   // Initialize array
		memset(&m_sockaddr, 0, sizeof(sockaddr));

		// Set family
		m_sockaddr.sa_family = addr_family;
	}

	// Construct from a berkley sockaddr structure
	socket_address::socket_address(const struct sockaddr &_m_sock_addr) throw()
	{	memcpy(&m_sockaddr, &_m_sock_addr, sizeof(sockaddr));	}

	// Copy constructor
	socket_address::socket_address(const socket_address &r) throw()
	{   memcpy(&m_sockaddr, &r.m_sockaddr, sizeof(struct sockaddr));  }

	// Copy operator
	socket_address & socket_address::operator=(const socket_address &r) throw()
	{
		memcpy(&m_sockaddr, &r.m_sockaddr, sizeof(struct sockaddr));
		return *this;
	}

	// Equal comparison operator
	bool socket_address::operator==(const socket_address &r) throw()
	{   return (0 == memcmp(&m_sockaddr, &r.m_sockaddr, size()));   }

	// Not equal comparison operator
	bool socket_address::operator!=(const socket_address &r) throw()
	{   return !(*this == r);   }

	// Get a pointer to berkley sockaddr structure
	const struct sockaddr * socket_address::sockaddr_ptr() const throw()
	{   return &m_sockaddr;        }
};	// !oonet namespace
