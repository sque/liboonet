#ifndef OONET_HTTP_SERVER_H_DEFINED
#define OONET_HTTP_SERVER_H_DEFINED

#include "../platform.h"
#include "../InetServer.h"
#include "../SocketAddressInet.h"
#include "Response.h"
#include "Request.h"
#include "ClientHandler.h"

namespace OONet
{
	namespace HTTP
	{
		//! A general HTTP server
		/**
			This based on Server to implement an HTTP server on top of
			it. The final exported interface is one virtual event OnURLRequest()
			which can be used to identify the request done by user and return
			its response. To start/stop the server use Server::start() and Server::stop().
		*/
		class Server :
			public InetServer
		{
		friend class ClientHandler;
		public:
			//! Constructor
			Server(void);

			//! Destructor
			virtual ~Server(void);

		private:
			//! When a new connection is accepted
			virtual bool OnAccept(const SocketAddressInet & remote_addr, InetPeer *& pDstHandler);

		protected:
			//! @name Exported events
			//! @{
			//! Event raised when a request has be done from a connected client.
			/**
				In HTTP protocol each request must have a respones. This class is the
				way to controll all the HTTP traffic. Requests are made and based on the
				request type the derived class is responsible to return appropriate HTTP::Response to
				client.
			@param Uri The uri of the request
			@param full_request Is the full packet of the request done by client
			@param client_addr Is the address of client that does the request.
			@return The HTTP::Response that will be sent back to client.
			*/
			virtual Response OnURLRequest(const Url & Uri, const Request & full_request, const SocketAddressInet & client_addr) = 0;
			//! @}

		};
	};	// !HTTP namespace
};	// !OONet namespace

#endif // !OONET_HTTP_SERVER_H_DEFINED
