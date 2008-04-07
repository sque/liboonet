#ifndef OONET_HTTP_SERVER_H_DEFINED
#define OONET_HTTP_SERVER_H_DEFINED

#include "../oonet.hpp"
#include "../socket_address_inet.hpp"
#include "../netserver.hpp"
#include "./response.hpp"
#include "./request.hpp"
#include "./server_clienthandler.hpp"


namespace oonet
{
	namespace http
	{
		//! A general HTTP server
		/**
			This based on Server to implement an HTTP server on top of
			it. The final exported interface is one virtual event OnURLRequest()
			which can be used to identify the request done by user and return
			its response. To start/stop the server use Server::start() and Server::stop().
		*/
		class server :
			public netserver<server_clienthandler>
		{
		friend class server_clienthandler;
		private:
			// NonCopyable
			server(const server &);
			server & operator=(const server &);

			/*
				Overide default behavior and recycle disconnected handlers
			*/
			virtual server_clienthandler * impl_new_handler(socket & cl_socket);
		protected:
			//! @name Exported events
			//! @{
			//! Event raised when a request has be done from a connected client.
			/**
				In HTTP protocol each request must have a respones. This class is the
				way to controll all the HTTP traffic. Requests are made and based on the
				request type the derived class is responsible to return appropriate http::response to
				client.
			@param Uri The uri of the request
			@param full_request Is the full packet of the request done by client
			@param client_addr Is the address of client that does the request.
			@return The http::response that will be sent back to client.
			*/
			virtual response on_url_request(const Url & Uri, const request & full_request, const socket_address_inet & client_addr) = 0;
			//! @}

		public:
			//! Constructor
			server(void);

			//! Destructor
			virtual ~server(void);

		};
	};	// !http namespace
};	// !oonet namespace

#endif // !OONET_HTTP_SERVER_H_DEFINED
