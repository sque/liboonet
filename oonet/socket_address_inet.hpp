#ifndef OONET_SOCKET_ADDRESS_INET_HPP_INCLUDED
#define OONET_SOCKET_ADDRESS_INET_HPP_INCLUDED

#include "./oonet.hpp"
#include "./socket_address.hpp"
#include "./host_resolver.hpp"
#include "./port_inet.hpp"

namespace oonet
{
	//! A Handler for socket's address for TCP/IP protocols
    class socket_address_inet : public socket_address
    {
    private:
        //! Cast local data to sockaddrin structure
		inline sockaddr_in * _cast_at_sockaddrin()
		{	return (sockaddr_in*)&m_sockaddr;	}

		//! Cast local data to const sockaddrin structure
		inline const sockaddr_in * _cast_at_sockaddrin() const
		{	return (sockaddr_in*)&m_sockaddr;	}
    public:

        //! Default constructor
        /**
			Creates a SocketAddress with family set to
			FAMILY_INET. All other parameters of SocketAddress
			are set to zero.
		*/
        inline socket_address_inet()
			: socket_address(FAMILY_INET)
        {}

        //! Constructor with specified HostInet and PortInet
        socket_address_inet(const host_inet & host, const port_inet & port);

        //! Copy constructor
        socket_address_inet(const socket_address & r);

        //! Destructor
        inline virtual ~socket_address_inet(){}

        //! Set the port of inet socket's address
        /**
			Port is given through PortInet objects.
		*/
        inline void set_port(const port_inet & port)
		{   _cast_at_sockaddrin()->sin_port = port.get_nbo();   }

        //! Get the port of inet socket's address
        /**
		@return A PortInet object holding the selected port.
		*/
        inline port_inet get_port() const
        {   return port_inet(ntohs(_cast_at_sockaddrin()->sin_port));   }

        //! Set the host of inet socket's address
        /**
			Host is given through HostInet objects.
		*/
        inline void set_host(const host_inet & host)
		{   _cast_at_sockaddrin()->sin_addr.s_addr = host.get_nbo(); }

        //! Get the host of inet socket's address
        /**
		@return a HostInet object holding the selected host.
		*/
        inline host_inet get_host() const
        {   return host_inet(ntohl(_cast_at_sockaddrin()->sin_addr.s_addr)); }

    };  // !socket_address_inet
};  // !oonet namespace

#endif // !OONET_SOCKET_ADDRESS_INET_HPP_INCLUDED
