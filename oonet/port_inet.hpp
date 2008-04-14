#ifndef OONET_PORTINET_H_INCLUDED
#define OONET_PORTINET_H_INCLUDED

#include "./oonet.hpp"

namespace oonet
{
	//! Class representing the port of a host on Inet protocol
	class port_inet
	{
	private:
		//! The port in host-byte-order
		ushort in_port;
	public:

		//! Default constructor
		/**
			It will create an object that corresponds to port 0.
		*/
		port_inet();

		//! Construct with a specified port
		/**
		@param p The desired port, it must be given in host-byte-order
		*/
		port_inet(ushort p);

		//! Copy constructor
		port_inet(const port_inet &r);

		//! Copy operator
		port_inet &operator=(const port_inet &r);

		//! Equal comparison operator
		inline bool operator==(const port_inet &r)
		{   return in_port==r.in_port;  }

		//! Not equal operator
		inline bool operator!=(const port_inet &r)
		{   return in_port!=r.in_port;  }

		//! Convert port to a string
		string to_string() const;

		//! Get port in network-byte-order
		ushort get_nbo() const
		{   return htons(in_port);  }

	};  // !PortInet class
};	// !oonet namespace

#endif // !OONET_PORTINET_H_INCLUDED
