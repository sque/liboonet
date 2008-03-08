/**
@file Server.cpp
@brief Implementation of HTTP::Server class
*/
#include "Http/Server.h"

namespace Slib
{
	namespace HTTP
	{
		Server::Server(void)
		{
		}

		Server::~Server(void)
		{
			initializeDestruction();
		}


		// When a new client is connected
		bool Server::OnAccept(const SocketAddressInet & remote_addr, InetPeer *& pDstHandler)
		{	ClientHandler * pHandler;

			// Create a new handler
			pHandler = new ClientHandler(this);
			pDstHandler = pHandler;

			// Free all disconnected clients
			freeAllDisconnectedHandlers();

			// Return true, we always accept
			return true;
		}

	};	//! HTTP namespace
};	//! Slib namespace
