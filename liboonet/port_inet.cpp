/**
@file port_inet.cpp
@brief Implementation of port_inet class
*/
#include "./port_inet.hpp"

#include <sstream>

namespace oonet
{
	// Default constructor
	port_inet::port_inet() : in_port(0) {}

	// Construct with a specified port
	port_inet::port_inet(ushort p) :	in_port(p) {}

	// Copy constructor
	port_inet::port_inet(const port_inet &r) :	in_port(r.in_port) {}

	// Copy operator
	port_inet & port_inet::operator=(const port_inet &r)
	{   in_port=r.in_port; return *this;  }

	// Get string representing the port
	string port_inet::to_string() const
	{   char cTmp[100];
		_snprintf(cTmp, 100, "%u", in_port);
		return cTmp;
	}
};  // !oonet namespace
