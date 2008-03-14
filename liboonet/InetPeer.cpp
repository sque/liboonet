/**
@file InetPeer.cpp
@brief Implementation of the InetPeer class.
*/
#include "./InetPeer.h"

namespace OONet
{
	// Constructor
	InetPeer::InetPeer()
		:mSock(INVALID_SOCKET),
		bConnected(false),
		bZombie(false)
	{}

	// Destructor
	InetPeer::~InetPeer()
	{	OONET_DEBUG_L2(_T("~InetPeer()_\n"));

	    // Initialize destruction of Peer
	    initializeDestruction();
    }

	// Handle a connected socket
	void InetPeer::handle_connection(const Socket & _AssignedSocket)
	{   OONET_DEBUG_L2(_T("InetClient::handle_connection()_\n"));

	    // Skip it if we are zombie class
	    if (bZombie)
            return;

		// Throw exception if we are alrdey connected
		if (bConnected)
			OONET_THROW_EXCEPTION(ExceptionAlreadyConnected,
				"InetPeer already connected");

		// Assure termination of any previous
		mSock.shutdown();
		mSock = Socket();
		join(MT::Infinity);

		// Assign new socket
		mSock = _AssignedSocket;

		// Flag as connected
		bConnected = true;

		// Start thread
		start();
	}

	// Thread routine
	void InetPeer::thread_routine()
	{	OONET_DEBUG_L2(_T("InetClient::ThreadRoutine()_\n"));
	    BinaryData data_Received;

        // On connect event
        if (!bZombie)
            OnConnect(mSock);

        // Start looping
        try{
            while(1)
            {
                data_Received = mSock.receive(1000);
                // Raise event in safe mode!
                if (!bZombie) OnDataArrived(data_Received);
            }
        }
        catch(std::exception & e)
        {	OONET_DEBUG_L1(_T("InetClient::ThreadRoutine() Exception thrown!\n"));
            if (!bZombie) OnError(e);
        }

        bConnected = false;

        // Call disconnect
        if (!bZombie)
            OnDisconnect();

        OONET_DEBUG_L2(_T("InetClient::ThreadRoutine()^\n"));
	}

	// Disconnect client
	void InetPeer::disconnect()
	{	OONET_DEBUG_L2(_T("InetClient::Disconnect()_\n"));

	    // Skip if we are zombie
	    if (bZombie)
            return;

	    // Check if connected
		if (!bConnected)
		{
		    OONET_DEBUG_L1(_T("InetClient::Disconnect() Calling disconnect while disconnected already\n"));
			OONET_THROW_EXCEPTION(ExceptionNotConnected,
				"Cannot InetClient::Disconnect() on not connected client"
			);
		}

		// Close socket
		OONET_DEBUG_L2(_T("InetClient::Disconnect() Closing sockets\n"));
		bConnected = false;		// Turn flag off so that it wont spawn errors
		mSock.shutdown();
		mSock = Socket();

		// We don't wait for thread to stop,
		// so that this function is callable by OnDataArrived
	}

	// Check if it is connected
	bool InetPeer::is_connected() const
	{	return bConnected;	};

	// Get address of remote peer
	const SocketAddressInet InetPeer::get_peer_address() const
	{	if (!bConnected)
			OONET_THROW_EXCEPTION(ExceptionNotConnected,
				"Not connected");
		return mSock.get_peer_address();
	}

	// Get local address
	const SocketAddressInet InetPeer::get_local_address() const
	{	if (!bConnected)
			OONET_THROW_EXCEPTION(ExceptionNotConnected,
				"Not connected");
		return mSock.get_local_address();
	}

	size_t InetPeer::send(const BinaryData & r)
	{	return mSock.send(r);	}

	// Initialize destruction
	void InetPeer::initializeDestruction() throw()
	{   bZombie = true;
	    OONET_DEBUG_L2(_T("InetPeer::InitializeDestruction()_\n"));

		// Disconnect if it is connected
	    bConnected = false;
		mSock.shutdown();
		OONET_DEBUG_L1(_T("InetPeer::InitializeDestruction() found connected, must shutdown 1/3\n"));
		mSock = Socket();
		OONET_DEBUG_L1(_T("InetPeer::InitializeDestruction() found connected, must shutdown 2/3\n"));
		join(MT::Infinity);
		OONET_DEBUG_L1(_T("InetPeer::InitializeDestruction() found connected, must shutdown OK\n"));

	    // Assure that has finished
	    if (MT::Thread::is_running())
        {   OONET_DEBUG_L1(_T("InetPeer::InitializeDestruction() although DCed, thread is running!\n"));
            join(MT::Infinity);
        }
	}

};	// !OONet namespace
