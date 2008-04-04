#ifndef OONET_HTTP_CLIENTHANDLER_H
#define OONET_HTTP_CLIENTHANDLER_H

#include "../oonet.hpp"
#include "../netserver.hpp"
#include "./Response.h"
#include "./Request.h"

namespace oonet
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
			binary_data streamData;

		protected:
			// When data arrives
			virtual void on_data_received(const binary_data & data);

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
};	// !oonet namespace

#endif // !OONET_HTTP_CLIENTHANDLER_H
