#ifndef OONET_INETPEER_H_DEFINED
#define OONET_INETPEER_H_DEFINED

#include "OONet.h"
#include "Thread.h"
#include "Socket.h"
#include "SocketAddressInet.h"

namespace OONet
{
	//! Class handling an established connection
	/**
		It is used to handle a connected inet socket. It will
		start a thread that waits for incoming data and raise
		appropriate events. This is an abstract class for creating
		your network protocol implementation, input/ouput is kept
		in protected security scope and its responsibility of derived
		class to provide the appropriate API for its protocol implementation.
	@remarks
		Because of the error-prone nature of threads, don't forget to call
		initializeDestruction() at each destructor of derived class. This
		will help to avoid calls to pure virtual calls
	*/
	class InetPeer
		:private MT::Thread
	{
	public:
		//! Constructor
		InetPeer();

		//! Destructor
		virtual ~InetPeer();

		//! Disconnect client
		/**
			It will close this connection and every
			following connection will be refused.
		*/
		void disconnect();

		//! Handle a connected socket
		/**
			When this is called, the InetPeer initializes
			its mechanisms, starts receiving thread
			and calls appropriate events
		*/
		void handleSocket(const Socket & _AssignedSocket);

        //! Check if InetPeer is connected
		bool isConnected() const;

		//! Get address of remote peer
		/**
		@throw ExceptionNotConnected If the InetPeer is not hanlding any connection.
		*/
		const SocketAddressInet getRemotePeerAddress() const;

		//! Get local address
		/**
		@throw ExceptionNotConnected If the InetPeer is not hanlding any connection.
		*/
		const SocketAddressInet getLocalAddress() const;
	private:
		Socket mSock;			//!< The connection socket
		bool bConnected;		//!< If peer is connected
		bool bZombie;           //!< If peer is a zombie

		virtual void ThreadRoutine();
	protected:

		//! Send data to the other end
		/**
			It will transmit binary data to the other end
			of connection.
		@return The size of data that actually has been transmited.
		@throw ExceptionNotConnected if the InetPeer is not handling any connection
			at moment
		*/
		size_t send(const BinaryData & r);

		//! Initialize destruction
		/**
			This must be called by derived classes at their destructors
			so that InetPeer enters <i>zombie mode</i> and avoid of calling
			of pure virtual functions.
		*/
		void initializeDestruction() throw();

		//! @name Exported Events
		//! @{

		//! When a connection is accomplished
		/**
			It will give an opportunity to child class
			to initialize its state and even parametrize socket's options
		@param con_socket A by reference pointer to the socket of connection
		*/
		virtual void OnConnect(Socket & con_socket) = 0;

		//! When data arrives from remote peer
		/**
			It will called every time data arrives with data.
			Its the responsibility of derived class to gather data
			from multiple calls of OnDataArrived() if he needs them.
			When event is called InetPeer will discard data.
		*/
		virtual void OnDataArrived(const BinaryData & data) = 0;

		//! When error occurs
		virtual void OnError(const std::exception & e){};

		//! When client is disconnected
		virtual void OnDisconnect(){};

		//! @}
	};	// !InetPeer class
};	// !OONet namespace

#endif // !OONET_INETPEER_H_DEFINED
