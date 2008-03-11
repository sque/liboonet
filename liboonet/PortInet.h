#ifndef OONET_PORTINET_H_INCLUDED
#define OONET_PORTINET_H_INCLUDED

#include "OONet.h"

namespace OONet
{
	//! Class representing the port of a host on Inet protocol
	class PortInet
	{
	private:
		//! The port in host-byte-order
		ushort in_port;
	public:

		//! Default constructor
		/**
			It will create an object that corresponds to port 0.
		*/
		PortInet();

		//! Construct with a specified port
		/**
		@param p The desired port, it must be given in host-byte-order
		*/
		PortInet(ushort p);

		//! Copy constructor
		PortInet(const PortInet &r);

		//! Copy operator
		PortInet &operator=(const PortInet &r);

		//! Equal comparison operator
		inline bool operator==(const PortInet &r)
		{   return in_port==r.in_port;  }

		//! Not equal operator
		inline bool operator!=(const PortInet &r)
		{   return in_port!=r.in_port;  }

		//! Convert port to a string
		string toString() const;

		//! Get port in network-byte-order
		ushort getNBOPort() const
		{   return htons(in_port);  }

	};  // !PortInet class
};	// !OONet namespace

#endif // !OONET_PORTINET_H_INCLUDED
