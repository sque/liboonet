#ifndef SLIB_HTTP_CLIENTHANDLER_H
#define SLIB_HTTP_CLIENTHANDLER_H

#include "../platform.h"
#include "../InetPeer.h"
#include "Response.h"
#include "Request.h"

namespace Slib
{
	namespace HTTP
	{
		class Server;

		/**
		* The handler of client for the Server
		*/
		class ClientHandler
			:public InetPeer
		{
		private:
			// A buffer with the data
			BinaryData streamData;
			HTTP::Server * pServer;

		public:
			// Constructor
			ClientHandler(HTTP::Server * _pServer);

			// Copy Constructor
			ClientHandler(const ClientHandler &r);

			// Destructor
			virtual ~ClientHandler(void);

			// Copy operator
			ClientHandler & operator=(const ClientHandler &r);

			// Get request
			bool GetRequest(Request & req);

		protected:

			virtual void OnConnect(Socket & con_socket){};

			// When data arrives
			virtual void OnDataArrived(const BinaryData & data);

			// When error occurs
			virtual void OnError(const Exception & e)
			{	printf("error %s\n", e.getReport().c_str());};

			// When client is disconnected
			virtual void OnDisconnect(){};
		};
	};	//! HTTP namespace
};	//! Slib namespace

#endif //! SLIB_HTTP_CLIENTHANDLER_H
