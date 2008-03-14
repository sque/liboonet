#ifndef OONET_INETSERVER_H_DEFINED
#define OONET_INETSERVER_H_DEFINED

#include "OONet.h"
#include "Thread.h"
#include "SocketAddressInet.h"
#include "InetPeer.h"
#include <deque>

namespace OONet
{
	//! Abstract class for creating a server for TCP/IP family
	/**
		To create a server you must first implement a client handler
		which must be derived from InetPeer. Server will listen for
		incoming connections and each connection will be dispatched
		at a unique instance of client handler.
	@remarks This is not a templated class of a custom client handler,
		so <b>YOU</b> need to create a new instance of your client handler
		every time OnAccept() is executed and pass back its pointer to
		server 
	*/
	class InetServer
		:protected MT::Thread
	{
	private:
		// Internal Data
		bool bRunning;						//!< Flag if server is running
		Socket lSocket;						//!< Listen socket
		SocketAddressInet serv_addr;		//!< The address of the server socket
		std::vector<InetPeer *> mClList;	//!< List of clients

		// Thread routine waiting for incoming connections
		void thread_routine();

		//! Free all clients
		void _freeAllHandlers();

	protected:

		//! Initialize destruction
		void initializeDestruction() throw();

		//! @name Exported Events
		//! @{

		//! Called when a new connection arrives
		/**
			This is called by server when a new connection arrives, you must
			return true if you want to accept connection. You are responsible
			to allocate an instance of your client handler and pass back its
			pointer
		@param remote_addr The address of the client that connected.
		@param pDstHandler This is a by reference pointer that you must set it to the
			instance of client handler that you created for this arrived connection.
		@return The desicion if we accept or not this connection. Passing false the
			connection will be closed
		@remarks
			Returning false will discard pointer to handler without freeing it, so don't
			allocate new handler if you don't want to accept the connection.

			After accepting connection, server will be responsible for deallocating
			space of your client handler, so there is no need for you to keep pointer
			just for cleaning up them at the end of execution.
		@see free() freeAllDisconnected()
		*/
		virtual bool OnAccept(const SocketAddressInet & remote_addr, InetPeer *& pDstHandler) = 0;

		//! Called before starting server.
		/**
			This is called exactly after the creation of socket, and before
			binding it, or starting listen thread.
		@param listen_socket A by reference pointer to the socket that will be used
			to listen for connections, here you can parametrize socket options.
		*/
		virtual void OnPreStart(Socket & listen_socket) = 0;

		//! Called after requesting to stop server and before actually stopping it
		virtual void OnPreStop(){}

		//! Called after requesting to stop server and the process has finished succesfully
		virtual void OnPostStop(){}

		//! @}
	public:

		//! Constructor
		InetServer();

		//! Destructor
		virtual ~InetServer();

		//! Start server
		/**
			This will start the server and it will listen for incoming
			connections.
		@param listen_addr The local address that the socket will listen for
			incoming connections
		@param BackLog The maximum unservered connection request that the socket
			internal stack will hold.
		@throw ExceptionAlreadyConnected If the server is already running
		*/
		void start(const SocketAddressInet & listen_addr, int BackLog);		// Listen address

		//! Stop server
		/**
			It will shutdown server, and no more new connections will be possible.
			All the existing connections will be closed, client handlers will be
			disconnected and freed.
		@throw ExceptionNotConnected If the server is not running
		*/
		void stop();

		//! Check if serveri is running
		bool isRunning() const;

		//! Free a specific disconnected handler
		/**
			This asks from server to free this handler. We
			mustn't free it by manualy deleting its pointer because
			it will remain in serves list and will cause problems.
		@note To free a handler it must first be disconnected!
		@throw ExceptionAccessDenied The pointer was NULL
		@throw ExceptionAccessDenied Handler is still running, it must be disconnected to be removed
		@throw ExceptionNotFound This handler is not a registered one in this server.
		*/
		void freeHandler(InetPeer * pToBeRemoved);

		//! Free all disconnected handlers
		/**
			This is similar to freeHandler() but it will use server's
			internal list and free all disconnected ones.
		*/
		void freeAllDisconnectedHandlers();

		//! Get list of clients
		/**
			It will return the list with client handlers
			registered in this server. This is not the list with
			the currently connected clients. This is the list with
			<b>ALL</b> clients that haven't be freed yet.
		*/
		const std::vector<InetPeer *> & getClients() const
		{	return mClList;	}

	};	// !InetServer class
};	// !OONet namespace

#endif // !OONET_INETSERVER_H_DEFINED
