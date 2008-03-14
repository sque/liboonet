/**
@file InetServer.cpp
@brief Implementation of the InetServer class.
*/
#include "./InetServer.h"
#include <algorithm>

namespace OONet
{
	// Constructor
	InetServer::InetServer()
		:bRunning(false),
		lSocket(INVALID_SOCKET)
	{}

	// Destructor
	InetServer::~InetServer()
	{
		initializeDestruction();
	}

	// Thread routine
	void InetServer::ThreadRoutine()
	{	Socket clSocket(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);	// client socket
		InetPeer * pDstHandler;					// Destination client handler

		// Loop to accept new connections
		while (1)
		{
			try
			{
				// Wait to accept a new connection
				clSocket = lSocket.accept();

				// Raise event
				pDstHandler = NULL;
				if (OnAccept(clSocket.get_peer_address(), pDstHandler))
				{
					if (pDstHandler != NULL)
					{
						// Register him
						mClList.push_back(pDstHandler);
						// Start serving
						pDstHandler->handleSocket(clSocket);
					}
					else
						clSocket = Socket();
				}
				else
				{
					// If not accepted, close connection
					clSocket = Socket();
				}
			}
			catch(std::exception)
			{
				// Exception on accept, exit gracefully
				bRunning = false;

				// Disconnect listen socket
				lSocket = Socket();

				// Free all clients
				_freeAllHandlers();
				return ;
			}
		}
	}

	// Start server
	void InetServer::start(const SocketAddressInet & listen_addr, int BackLog)
	{
		// Check if it is already started
		if (bRunning)
			OONET_THROW_EXCEPTION(ExceptionAlreadyConnected,
				"Server is already started!!!");

		// Save address
		serv_addr = listen_addr;

		// Create a new socket
		lSocket = Socket(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);

		// Call pre start event
		OnPreStart(lSocket);

		// Bind it on the selected address
		lSocket.bind(serv_addr);

		// Turn it on listen mode
		lSocket.listen(BackLog);

		// Mark it as running
		bRunning = true;

		// Start thread
		Thread::start();
	}

	// Stop server
	void InetServer::stop()
	{	if (! bRunning)
			OONET_THROW_EXCEPTION(ExceptionNotConnected,
				"Cannot stop server while it is not started!");

		// Call prestop event
		OnPreStop();

		// Disconnect listen socket so we don't have any new
		// and the thread server will cleanup
		lSocket.shutdown();
		lSocket = Socket();

		// And join with master thread
		join(MT::Infinity);

		// Call poststop event
		OnPostStop();
	}

	// Free any client connected
	void InetServer::_freeAllHandlers()
	{	std::vector<InetPeer *>::iterator it;
		InetPeer * pPeer;

		// We delete all clients without desconnecting them
		// so they get in zombie mode and don't raise events
		while((it = mClList.begin()) != mClList.end())
		{	pPeer = *it;
			delete pPeer;
			mClList.erase(it);
		}
	}

	// Remove and free a disconnected client from server
	void InetServer::freeHandler(InetPeer * pToBeRemoved)
	{	std::vector<InetPeer *>::iterator it;

		// Check if it is null
		if (pToBeRemoved == NULL)
			OONET_THROW_EXCEPTION(ExceptionAccessDenied,
				"Cannot free a NULL pointer!");

		if (pToBeRemoved->isConnected())
			OONET_THROW_EXCEPTION(ExceptionResourceBusy,
				"Peer is connected, cannot remove him"
				);

		it= std::find(mClList.begin(), mClList.end(), pToBeRemoved);
		if (it == mClList.end())
			OONET_THROW_EXCEPTION(ExceptionNotFound,
				"Cannot find peer in clients list!"
				);

		// Erase from the list
		mClList.erase(it);

		// Free peer
		delete pToBeRemoved;
	}

	// Remove and free all disconnected clients
	void InetServer::freeAllDisconnectedHandlers()
	{	std::vector<InetPeer *>::iterator it;
		InetPeer * pPeer;

		// Start from the begining
		//! @todo optimize this!!! As the number of clients increases, the loops are increased expo
		it = mClList.begin();
		while(it != mClList.end())
		{	pPeer = *it;

			// Try to remove disconnected
			if (!pPeer->isConnected())
			{
				freeHandler(pPeer);
				it = mClList.begin();	// Back at start
			}
			else
				it++;
		}
	}

	bool InetServer::isRunning() const
	{	return bRunning;	};

	// Initialize destruction
	void InetServer::initializeDestruction() throw()
	{	// We assure that server is stopped to prevent pure virtuals calls
		try
		{
			if (bRunning)
				stop();
		}
		catch(std::exception)
		{}
	}
};	// !OONet namespace
