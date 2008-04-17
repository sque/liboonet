#ifndef OONET_HTTP_CLIENT_HPP_INCLUDED
#define OONET_HTTP_CLIENT_HPP_INCLUDED

#include "../oonet.hpp"
#include "../binary_data.hpp"
#include "../socket_address_inet.hpp"
#include "../netstream_threaded.hpp"
#include "./response.hpp"
#include "./request.hpp"

#include <deque>

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
		class client:
			private netstream_threaded
		{
		private:
			// NonCopyable
			client(const client &);
			client & operator=(const client &);

			// Private data
			mt::semaphore sem_anwser_arrived;			//!< Semaphore triggered when an answer arrives
			binary_data WaitingToProcessData;			//!< Unprocessed received data
			std::deque<response> m_response_queue;		//!< Queue of responses
			mt::mutex mux_access_data;					//!< Mutex for synchronization on queue
			bool b_waiting_anwser;						//!< If someone is waiting for a server answer
		public:
			//! Default constructor
			/**
				Creates a client ready to perform a connection
			*/
			client();

			//! Construct and connect
			/**
			@throw ExceptionConnectionRefused It may be thrown by netstream_threaded::connect()
			@remarks If the connection fails the construction will too.
			*/
			client(const socket_address_inet & dst_addr);

			//! Destructor
			virtual ~client();

			//! Make an http request and wait for response
			/**
				It will sent the specified request to a server
				and wait for the answer to arrive in a specied
				maximum time.
			@param req The request to sent at the server
			@param tm_timeoutms The maximum time to wait for answer in milliseconds
			@return A response object holding the answer from the server.
			@throw ExceptionTimeOut If maximum time reached without receiving any answer
			@throw ExceptionNotConnected If client is not connected in any server yet, or the connection has closed
				before calling send().
			@throw ExceptionWrongFormat If the server sent a response that is not a well-formated http response message.
				After the exception the connection is closed too.
			@throw ExceptionIncomplete This is a special case where the connection was closed without finishing the
				reception of a complete response.
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
			inline bool connected()
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
