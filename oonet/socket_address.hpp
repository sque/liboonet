#ifndef OONET_SOCKET_ADDRESS_HPP_INCLUDED
#define OONET_SOCKET_ADDRESS_HPP_INCLUDED

#include "./oonet.hpp"
#include "./exception.hpp"

namespace oonet
{
	//! A Handler for socket's generic address (protocol independant)
    class socket_address
    {
    protected:
		//! Internal structure of socket address
        struct sockaddr m_sockaddr;

    public:
        //! Construct with specified protocol
        /**
			It will reset all parameters of address to zero,
			and set the family field to the specified.
		*/
        explicit socket_address(int addr_family) throw();

		//! Construct from a berkley sockaddr struct
		/**
			It will copy parameters of berkley sockaddr structure
			to its internal data.
		*/
        explicit socket_address(const struct sockaddr &_m_sock_addr) throw();

        //! Copy constructor
        socket_address(const socket_address &r) throw();

        //! Destructor
        virtual ~socket_address(){}


        //! Enumeration of address family
        enum AddressFamily
        {
            FAMILY_INET = AF_INET,  //!< The TCP/IP address family
        };

        //! Copy operator
        socket_address &operator=(const socket_address &r) throw();

        //! Equal comparison operator
        bool operator==(const socket_address &r) throw();

        //! Not equal comparison operator
        bool operator!=(const socket_address &r) throw();

        //! Get the length of the SocketAddress
        inline size_t size() const
        {   return sizeof(m_sockaddr);   }

        //! Get a pointer to berkley sockaddr structure
        const struct sockaddr * sockaddr_ptr() const throw();

        //! Get the address family of this socket address
        inline int family() const throw()
        {   return m_sockaddr.sa_family; }
    };  // !SocketAddress class
};  // !oonet namespace

#endif // !OONET_SOCKET_ADDRESS_HPP_INCLUDED
