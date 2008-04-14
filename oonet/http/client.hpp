#ifndef OONET_HTTP_CLIENT_HPP_INCLUDED
#define OONET_HTTP_CLIENT_HPP_INCLUDED

#include "../oonet.hpp"
#include "../binary_data.hpp"
#include "../socket_address_inet.hpp"
#include "../netstream_threaded.hpp"
#include "./response.hpp"
#include "./request.hpp"

namespace oonet
{
	namespace http
	{
		//! HTTP client implemantation over tcp/ip protocol
		/**
			It will create a full working http client, that
			can send http::request packets and receive http::response
			packets. Client has the ability to connect to any tcp listening
			server and send any type of http::Requests. It can detect
			errors from receiving packets and report them.
		*/
		class Client:
			private netstream_threaded
		{
		private:
			// NonCopyable
			Client(const Client &);
			Client & operator=(const Client &);

			// Private data
			mt::semaphore sem_anwser_arrived;	//!< Semaphore triggered when an answer arrives
			binary_data WaitingToProcessData;	//!< Unprocessed received data
			mt::mutex mux_access_data;			//!< Mutex for synchronization on stack
			bool b_waiting_anwser;				//!< If someone is waiting for a server answer
		public:
			//! Default constructor
			/**
				Creates a client ready to perform a connection
			*/
			Client();

			Client(const socket_address & dst_addr);

			//! Destructor
			virtual ~Client();

			//! Make an http request and wait for response
			/**
				It will sent the specified request to a server
				and wait for the answer to arrive in a specied
				maximum time.
			@param req The http::request to sent at the server
			@param tm_timeoutms The maximum time to wait for answer in milliseconds
			@return An http::response object holding the answer from the server.
			@throw ExceptionTimeOut If maximum time reached without receiving any answer
			@throw ExceptionNotConnected If http::Client is not connected in any server yet, or connection was closed
			@remarks In case that a wrong formated message
				arrives, then the client is automatically disconnected
				from server.
			*/
			response send(request & req, long tm_timeoutms);

			//! Connect at a host
			void connect(const socket_address_inet & dest_addr);

			//! Disconnect from host
			inline void disconnect()
			{	netstream_threaded::disconnect();	}

			//! Check if it is connected
			bool connected()
			{	return netstream_threaded::connected();	}

		private:
			// When data arrives
			virtual void on_data_received(const binary_data &);

			// Raised when we loose conenction from server
		    virtual void on_disconnected();

		};	// !Client class
	};	// !http namespace
};	// !oonet namespace
#endif // !OONET_HTTP_CLIENT_HPP_INCLUDED
