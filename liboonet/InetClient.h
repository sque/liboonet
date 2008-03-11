#ifndef OONET_INETCLIENT_H_INCLUDED
#define OONET_INETCLIENT_H_INCLUDED

#include "OONet.h"
#include "InetPeer.h"

namespace OONet
{
	//! Abstract class for creating a client for TCP/IP family
	/**
		To create a client you need to implement OnDataArrived(), OnConnect()
		and optionally OnError() and OnDisconnect. This class is similar to InetPeer
		with the addition of functions connect() and disconnect().
	*/
    class InetClient :protected InetPeer
    {
	public:
		//! Default constructor
        InetClient();

        //! Destructor
        virtual ~InetClient();

        //! Connect at a server
        /**
			It will try to connect to the specified server, and start
			data collecting thread. This function may throw various
			exceptions depending on your system. Take a look at Socket::connect()
		@param serv_addr The socket address of server that we want to connect.
		@throw ExceptionAlreadyConnected If the client is already connected.
		*/
        void connect(const SocketAddressInet & serv_addr) throw(Exception);

		//! Check if it is connected
		bool isConnected() const;

		//! Disconnect from server
		/**
			It will disconnect from connected server and stop
			the thread that collects data.
		@throw ExceptionNotConnected If the InetClient is not connected anywhere.
		*/
		void disconnect();

	protected:

		//! @name Exported Events
		//! @{
		// When a connection is accomplished
		virtual void OnConnect(Socket & con_socket){};

		// When data arrives
		virtual void OnDataArrived(const BinaryData & data) = 0;

		// When error occurs
		virtual void OnError(const std::exception & e){};

		// When client is disconnected
		virtual void OnDisconnect(){};

		//! @}
    };  // !InetClient class
};  // !OONet namespace

#endif // !OONET_INETCLIENT_H_INCLUDED
