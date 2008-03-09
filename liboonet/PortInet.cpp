/**
@file PortInet.cpp
@brief Implementation of PortInet class
*/
#include "./PortInet.h"
#include <sstream>

namespace Slib
{
	// Default constructor
	PortInet::PortInet() : in_port(0) {}

	// Construct with a specified port
	PortInet::PortInet(ushort p) :	in_port(p) {}

	// Copy constructor
	PortInet::PortInet(const PortInet &r) :	in_port(r.in_port) {}

	// Copy operator
	PortInet & PortInet::operator=(const PortInet &r)
	{   in_port=r.in_port; return *this;  }

	// Get string representing the port
	string PortInet::toString() const
	{   char cTmp[100];
		_snprintf(cTmp, 100, "%u", in_port);
		return cTmp;
	}
};  //! Slib namespace
