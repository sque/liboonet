/**
@file HostInet.cpp
@brief Implementation of the HostInet class.
*/
#include "./HostInet.h"

namespace Slib
{
	const HostInet HostInet::LOCALHOST = HostInet(0x7f000001);
	const HostInet HostInet::ANY = HostInet(0);

	// Constructor
	HostInet::HostInet() : host_ip(0)
	{}

	// Construct from HostInet
	HostInet::HostInet(ulong ip)	: host_ip(ip)
	{}

	// Copy constructor
	HostInet::HostInet(const HostInet &r)
	{   host_ip = r.host_ip;    }

	// Copy operator
	HostInet & HostInet::operator=(const HostInet &r)
	{   host_ip = r.host_ip; return (*this);    }

	// Comparison
	bool HostInet::operator==(const HostInet &r) const
	{   return (host_ip == r.host_ip);  }

	//! Not equal comparison operator
	bool HostInet::operator!=(const HostInet &r) const
	{   return(host_ip != r.host_ip);   }

	// Get in dotted human readable
	string HostInet::toString() const
	{
		string temp;
		struct in_addr temp_addr;
		temp_addr.s_addr = htonl(host_ip);
		temp = inet_ntoa(temp_addr);
		return temp;
	}

	ulong HostInet::getNBOAddress() const
	{   return htonl(host_ip);  }
};	//! Slib namespace
