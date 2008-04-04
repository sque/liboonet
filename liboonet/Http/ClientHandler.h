#ifndef OONET_HTTP_CLIENTHANDLER_H
#define OONET_HTTP_CLIENTHANDLER_H

#include "../OONet.h"
#include "../InetPeer.h"
#include "../netserver.hpp"
#include "Response.h"
#include "Request.h"

namespace OONet
{
	namespace HTTP
	{
		class Server;

		/**
		* The handler of client for the Server
		*/
		class ClientHandler
			:public netserver_clienthandler<Server>
		{
		private:
			// A buffer with the data
			BinaryData streamData;

		protected:
			// When data arrives
			virtual void on_data_received(const BinaryData & data);

			// Get request
			bool get_request(Request & req);
		public:

			// Constructor
			ClientHandler(void * _s)
				:netserver_clienthandler<Server>(_s)
			{}

			// Destructor
			virtual ~ClientHandler(void){}


		};
	};	// !HTTP namespace
};	// !OONet namespace

#endif // !OONET_HTTP_CLIENTHANDLER_H
