#ifndef OONET_SOCKETADDRESS_H_INCLUDED
#define OONET_SOCKETADDRESS_H_INCLUDED

#include "OONet.h"
#include "Exception.h"

namespace OONet
{
	//! A Handler for socket's generic address (protocol independant)
    class SocketAddress
    {
    protected:
		//! Internal structure of socket address
        struct sockaddr mSockAddr;

    public:
        //! Construct with specified protocol
        /**
			It will reset all parameters of address to zero,
			and set the family field to the specified.
		*/
        explicit SocketAddress(int addr_family) throw();

		//! Construct from a berkley sockaddr struct
		/**
			It will copy parameters of berkley sockaddr structure
			to its internal data.
		*/
        explicit SocketAddress(const struct sockaddr &mAddr) throw();

        //! Copy constructor
        SocketAddress(const SocketAddress &r) throw();

        //! Destructor
        virtual ~SocketAddress(){}


        //! Enumeration of address family
        enum AddressFamily
        {
            FAMILY_INET = AF_INET,  //!< The TCP/IP address family
        };

        //! Copy operator
        SocketAddress &operator=(const SocketAddress &r) throw();

        //! Equal comparison operator
        bool operator==(const SocketAddress &r) throw();

        //! Not equal comparison operator
        bool operator!=(const SocketAddress &r) throw();

        //! Get the length of the SocketAddress
        inline size_t size() const
        {   return sizeof(mSockAddr);   }

        //! Get a pointer to berkley sockaddr structure
        const struct sockaddr * getSockaddrPtr() const throw();

        //! Get the address family of this socket address
        inline int getAddressFamily() const throw()
        {   return mSockAddr.sa_family; }
    };  // !SocketAddress class
};  // !OONet namespace

#endif // !OONET_SOCKETADDRESS_H_INCLUDED
