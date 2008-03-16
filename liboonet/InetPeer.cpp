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
	    initialize_destruction();
    }

	// Handle a connected socket
	void InetPeer::handle_connection(const Socket & _AssignedSocket)
	{
	    // Skip it if we are zombie class
	    if (bZombie)
            return;

		// Throw exception if we are alrdey connected
		if (bConnected)
			OONET_THROW_EXCEPTION(ExceptionAlreadyConnected,
				"InetPeer already connected");

		// Assure termination of any previous
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
	bool InetPeer::connected() const
	{	return bConnected;	};


	size_t InetPeer::send(const BinaryData & r)
	{	return mSock.send(r);	}

	// Initialize destruction
	void InetPeer::initialize_destruction() throw()
	{   bZombie = true;

		// Disconnect if it is connected
	    bConnected = false;
		mSock.shutdown();
		mSock = Socket();
		join(MT::Infinity);

	    // Assure that has finished
	    if (MT::Thread::running())
        {   OONET_DEBUG_L1(_T("InetPeer::InitializeDestruction() although DCed, thread is running!\n"));
            join(MT::Infinity);
        }
	}

};	// !OONet namespace
