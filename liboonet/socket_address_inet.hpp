#ifndef OONET_SOCKETADDRESSINET_H_INCLUDED
#define OONET_SOCKETADDRESSINET_H_INCLUDED

#include "./oonet.hpp"
#include "./socket_address.hpp"
#include "./host_resolver.hpp"
#include "./port_inet.hpp"

namespace oonet
{
	//! A Handler for socket's address for TCP/IP protocols
    class SocketAddressInet : public SocketAddress
    {
    private:
        //! Cast local data to sockaddrin structure
		inline sockaddr_in * _cast_at_sockaddrin()
		{	return (sockaddr_in*)&mSockAddr;	}

		//! Cast local data to const sockaddrin structure
		inline const sockaddr_in * _cast_at_sockaddrin() const
		{	return (sockaddr_in*)&mSockAddr;	}
    public:
        //! Default constructor
        /**
			Creates a SocketAddress with family set to
			FAMILY_INET. All other parameters of SocketAddress
			are set to zero.
		*/
        inline SocketAddressInet()
			: SocketAddress(FAMILY_INET)
        {}

        //! Constructor with specified HostInet and PortInet
        SocketAddressInet(const HostInet & host, const PortInet & port);

        //! Copy constructor
        SocketAddressInet(const SocketAddress & r);

        //! Destructor
        inline virtual ~SocketAddressInet(){}

        //! Set the port of inet socket's address
        /**
			Port is given through PortInet objects.
		*/
        inline void setPortInet(const PortInet & port)
		{   _cast_at_sockaddrin()->sin_port = port.getNBOPort();   }

        //! Get the port of inet socket's address
        /**
		@return A PortInet object holding the selected port.
		*/
        inline PortInet getPortInet() const
        {   return PortInet(ntohs(_cast_at_sockaddrin()->sin_port));   }

        //! Set the host of inet socket's address
        /**
			Host is given through HostInet objects.
		*/
        inline void setHostInet(const HostInet & host)
		{   _cast_at_sockaddrin()->sin_addr.s_addr = host.getNBOAddress(); }

        //! Get the host of inet socket's address
        /**
		@return a HostInet object holding the selected host.
		*/
        inline HostInet getHostInet() const
        {   return HostInet(ntohl(_cast_at_sockaddrin()->sin_addr.s_addr)); }

    };  // !SocketAddressInet
};  // !oonet namespace

#endif // !OONET_SOCKETADDRESSINET_H_INCLUDED
