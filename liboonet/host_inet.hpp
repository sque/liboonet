#ifndef OONET_HOSTINET_H_INCLUDED
#define OONET_HOSTINET_H_INCLUDED

#include "./oonet.hpp"

namespace oonet
{
	//! Class representing the address of host on Inet protocol
	class HostInet
	{
	private:
		//! The ip of the host in host-byte-order
		ulong host_ip;

	public:
		//! Constant address of localhost (127.0.0.1)
		static const HostInet LOCALHOST;
		//! Constant address of any host (0.0.0.0)
		static const HostInet ANY;

		//! Default constructor
		/**
			Creates a HostInet object with address 0.0.0.0
		*/
		HostInet();

		//! Construct from a specified ip
		/**
		@param ip Ip is given in host-byte-order.
		*/
		explicit HostInet(ulong ip);

		//! Copy constructor
		HostInet(const HostInet &r);

		//! Copy operator
		HostInet & operator=(const HostInet &r);

		//! Equal comparison operator
		bool operator==(const HostInet &r) const;

		//! Not equal comparison operator
		bool operator!=(const HostInet &r) const;

		//! Get a std::string with the address in dotted humman format
		string toString() const;

		//! Get the ip in Network-Byte-Order
		ulong getNBOAddress() const;
	};  // ! HostInet class

};	// !oonet namespace
#endif // !OONET_HOSTINET_H_INCLUDED
