/**
@file host_inet.cpp
@brief Implementation of the host_inet class.
*/
#include "./host_inet.hpp"

namespace oonet
{
	const host_inet host_inet::LOCALHOST = host_inet(0x7f000001);
	const host_inet host_inet::ANY = host_inet(0);

	// Constructor
	host_inet::host_inet() : host_ip(0)
	{}

	// Construct from HostInet
	host_inet::host_inet(ulong ip)	: host_ip(ip)
	{}

	// Copy constructor
	host_inet::host_inet(const host_inet &r)
	{   host_ip = r.host_ip;    }

	// Copy operator
	host_inet & host_inet::operator=(const host_inet &r)
	{   host_ip = r.host_ip; return (*this);    }

	// Comparison
	bool host_inet::operator==(const host_inet &r) const
	{   return (host_ip == r.host_ip);  }

	// Not equal comparison operator
	bool host_inet::operator!=(const host_inet &r) const
	{   return(host_ip != r.host_ip);   }

	// Get in dotted human readable
	string host_inet::to_string() const
	{
		string temp;
		struct in_addr temp_addr;
		temp_addr.s_addr = htonl(host_ip);
		temp = inet_ntoa(temp_addr);
		return temp;
	}

	ulong host_inet::get_nbo() const
	{   return htonl(host_ip);  }
};	// !oonet namespace
