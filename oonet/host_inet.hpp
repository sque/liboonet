#ifndef OONET_HOSTINET_H_INCLUDED
#define OONET_HOSTINET_H_INCLUDED

#include "./oonet.hpp"

namespace oonet
{
	//! Class representing the address of host on Inet protocol
	class host_inet
	{
	private:
		//! The ip of the host in host-byte-order
		ulong host_ip;

	public:
		//! Constant address of localhost (127.0.0.1)
		static const host_inet LOCALHOST;

		//! Constant address of any host (0.0.0.0)
		static const host_inet ANY;

		//! Default constructor
		/**
			Creates a HostInet object with address 0.0.0.0
		*/
		host_inet();

		//! Construct from a specified ip
		/**
		@param ip Ip is given in host-byte-order.
		*/
		explicit host_inet(ulong ip);

		//! Copy constructor
		host_inet(const host_inet &r);

		//! Copy operator
		host_inet & operator=(const host_inet &r);

		//! Equal comparison operator
		bool operator==(const host_inet &r) const;

		//! Not equal comparison operator
		bool operator!=(const host_inet &r) const;

		//! Get a std::string with the address in dotted humman format
		string to_string() const;

		//! Get the ip in Network-byte-Order
		ulong get_nbo() const;
	};  // ! HostInet class

};	// !oonet namespace
#endif // !OONET_HOSTINET_H_INCLUDED
