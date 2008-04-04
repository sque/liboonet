#ifndef OONET_SOCKET_H_DEFINED
#define OONET_SOCKET_H_DEFINED

#include "./oonet.hpp"
#include "./binary_data.hpp"
#include "./socket_address.hpp"

#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace oonet
{

	//! Berkley network socket wrapper
	/**
		A wrapper for berkley sockets, it has all the needed functionality
		and incorporates very well with BinaryData for sending and receiving data,
		and SocketAddress for defining address of sockets.

	 */
	class Socket
	{
	private:

		// Pimpl Idiom
		class impl;
		boost::shared_ptr<impl> pimpl_;

		//! Get last error linux implementation.
		int _linux_get_last_error() const;

		//! Get last error win32 implementation.
		int _win32_get_last_error() const;

		//! General get last error function
		int _get_last_error() const;

		//! Internal function for converting system errors to exceptions
		void _throw_last_error(const string & ErrorMessage) const;
	public:

		//! Exception raised when actions was performed on invalid socket
		OONET_DECLARE_EXCEPTION(ExceptionInvalidSocket);
		//! Exception raised when requested address is used by another socket.
		OONET_DECLARE_EXCEPTION(ExceptionAddressInUse);
		//! Exception raised when desired address is not available in local scope.
		OONET_DECLARE_EXCEPTION(ExceptionAddressNotAvailable);
		//! Exception raised when connection attempt was aborted due to time out
		OONET_DECLARE_EXCEPTION(ExceptionConnectionAborted);
		//! Exception raised when connection attempt was refused by the other end.
		OONET_DECLARE_EXCEPTION(ExceptionConnectionRefused);
		//! Exception raised when action was perform on broken connected socket.
		OONET_DECLARE_EXCEPTION(ExceptionConnectionReset);

        //! Enumeration of socket families
        enum SocketFamily
        {
#if (OONET_OS == OONET_OS_LINUX)
            FAMILY_LOCAL = PF_LOCAL,	    //!<   Local communication              unix(7)
            FAMILY_INET = PF_INET,          //!<   IPv4 Internet protocols          ip(7)
            FAMILY_INET6 = PF_INET6,        //!<   IPv6 Internet protocols
            FAMILY_IPX = PF_IPX,            //!<   IPX - Novell protocols
            FAMILY_NETLINK = PF_NETLINK,    //!<   Kernel user interface device     netlink(7)
            FAMILY_X25 = PF_X25,            //!<   ITU-T X.25 / ISO-8208 protocol   x25(7)
            FAMILY_AX25 = PF_AX25,          //!<   Amateur radio AX.25 protocol
            FAMILY_ATMPVC = PF_ATMPVC,      //!<   Access to raw ATM PVCs
            FAMILY_APPLETALK = PF_APPLETALK,//!<   Appletalk                        ddp(7)
            FAMILY_PACKET = PF_PACKET       //!<   Low level packet interface       packet(7)
#elif (OONET_OS == OONET_OS_WIN32)
			FAMILY_INET = AF_INET			//!<   IPv4 Internet protocols
#endif
        };

        //! Enumeration of socket types
        enum SocketType
        {
            TYPE_STREAM = SOCK_STREAM,      //!< Streamed socket for connection-oriented
            TYPE_DGRAM = SOCK_DGRAM,        //!< Connectionless, unreliable of fixed length
            TYPE_RAW = SOCK_RAW,            //!< Raw packet format
        };

        //! Enumeration of socket protocol
        enum SocketProtocol
        {
            PROTO_DEFAULT = 0,              //!< Default protocol of family
        };


		//! Constructor to create new socket
		/**
			This is used to create a new socket.
		@param s_family The family that the socket will belong to.
		@param s_type The type of socket to create.
		@param s_proto The protocol that socket will follow
		*/
		Socket(int s_family, int s_type, int s_proto) throw(Exception);

		//! Constructor to create an invalid socket
		/**
			This is used to create an object that doesn't really
			handle any socket. This is very usefull for creating
			variables of Socket that may be assigned later.
		*/
		Socket() throw();

        //! Constructor to use an existing handle on a socket
        /**
			This constructor will not create a new socket
			but will use the provided socket handle.
		*/
        explicit Socket(SOCKET h_socket) throw();


		//! Receive data from socket
		/**
			It will pop data from input buffer or block until
			data arrives from the other end. If data in buffer
			is more than the maximum we are requesting, then only
			the maximum that we requested will be popped from buffer.
		@param max The maximum number of bytes that we want to receive
		*/
		BinaryData receive(size_t max) throw(Exception);

        //! Send data through socket
        /**
			It will send data to socket that will be transmitted
			to the other end of communication.
		@param trans_data The data to transmit through socket
		@return The number of data that was actually transmitted.
		*/
        size_t send(const BinaryData &trans_data) throw (Exception);

        //! Ask the socket to connect to another socket
        /**
			This is a must for connection-orient protocols. The socket
			must first be connected to start transmition. With connect
			action, the socket will try to route and handshake with the
			other end. After the execution of function the socket will
			be connected state. In case of fail an exception will be thrown
			describing the problem.
		@param serv_addr The address of the other-end socket.
		*/
        void connect(const SocketAddress & serv_addr) throw(Exception);

        //! Bind socket at a local address
        /**
			It will ask socket to be binded at specific local address.
			Binding must be done when listening for connections on
			connection-oriented protocols, it is usefull also for
			connection-less protocols. When a socket is binded at
			a specific address you cannot rebind it at another address.
		@param local_addr The local address that socket will be bind.
			The address must be valid in the scope of the host that
			its binding.
		*/
        void bind(const SocketAddress & local_addr) throw(Exception);

        //! Switch socket in listen mode
        /**
			It will switch socket in listen mode. For connection-oriented
			protocols socket muts be binded to a local address before
			switching to listen mode.
		@param max_connections The maximum connections it can handle
			at connection state. This is not the maximum established
			connections.
		*/
        void listen(int max_connections) throw(Exception);

        //! Get the local address of the socket
        /**
			It will return the local address that socket is binded, either automatically or
			manual.	If socket is a TCP/IP socket then you can cast safely returned address
			to SocketAddressInet.
		@see get_peer_address
		*/
        SocketAddress get_local_address() const throw(Exception);

        //! Get the address of the peer socket
        /**
			This is valid for connected sockets and will return the address of socket
			at the other end of connection.
		@see get_local_address
		*/
        SocketAddress get_peer_address() const throw(Exception);

        //! Wait for incoming connection and return socket of client
        /**
			Socket will block until a new connection arrives
			and when it does, it will return the socket of the established
			connection. In case that listen socket is closed, it
			will unblock and raise exception.
		*/
        Socket accept() throw(Exception);

        //! Shutdown socket
        /**
			This is the proper way to shutdown a connection, by calling
			shutdown, socket will inform the other end for shutdowning.
			After succesfull shutdown, socket is useless and must be closed.
		*/
        void shutdown() throw(Exception);

        //! Change an option of socket
        /**
			This is the berkley socket options. The parameters
			defined here are the same that are defined in setsockopt()
			See manual of setsockopt() at your systems developping
			library for extended explanation.
		*/
        void set_option(int level, int opt_name, const void * opt_val, int opt_size);
	};  // !Socket class
};  // !oonet namespace

#endif // !OONET_SOCKET_H_DEFINED
