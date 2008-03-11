#ifndef OONET_HTTP_CLIENT_H_INCLUDED
#define OONET_HTTP_CLIENT_H_INCLUDED

#include "../OONet.h"
#include "../BinaryData.h"
#include "../Exception.h"
#include "../SocketAddressInet.h"
#include "../Semaphore.h"
#include "../InetClient.h"
#include "Response.h"
#include "Request.h"

namespace OONet
{
	namespace HTTP
	{
		//! HTTP client implemantation over tcp/ip protocol
		/**
			It will create a full working http client, that
			can send HTTP::Request packets and receive HTTP::Response
			packets. Client has the ability to connect to any tcp listening
			server and send any type of HTTP::Requests. It can detect
			errors from receiving packets and report them.
		*/
		class Client:
			private InetClient
		{
		private:
			SocketAddressInet serv_addr;		//!< The Server address
			MT::Semaphore SemAnswerArrived;		//!< Semaphore triggered when an answer arrives
			BinaryData WaitingToProcessData;	//!< Unprocessed received data

			//! Internal implemenation of connect to new server
			void _ConnectToServer();
		public:
			//! Default constructor
			/**
				Creates a client ready to perform a connection
			*/
			Client();

			//! Construct and connect
			/**
				Creates a client and connects it on a specific
				address.
			@remarks
				Check InetClient::connect() for exceptions tha may be thrown.
			*/
			Client(const SocketAddressInet & _s_addr);

			//! Destructor
			~Client();

			//! Copy constructor
			/**
			@throw ExceptionUnimplemented As this feature is not implemented and there is no
				reason to do this now
			*/
			Client(const Client & r);

			//! Copy operator
			/**
			@throw ExceptionUnimplemented As this feature is not implemented and there is no
				reason to do this now
			*/
			Client & operator=(const Client &r);

			//! Make an http request and wait for response
			/**
				It will sent the specified request to a server
				and wait for the answer to arrive in a specied
				maximum time.
			@param req The HTTP::Request to sent at the server
			@param tm_timeoutms The maximum time to wait for answer in milliseconds
			@return An HTTP::Response object holding the answer from the server.
			@throw ExceptionTimeOut If maximum time reached without receiving any answer
			@throw ExceptionNotConnected If HTTP::Client is not connected in any server yet.
			@remarks In case that a wrong formated packet
				arrives, then the client is automatically disconnected
				from server.
			*/
			Response send(Request & req, long tm_timeoutms);

			//! Ask to reconnect at previous server
			void reconnect();

			//! Change host and connect to a new one
			void changeHost(const SocketAddressInet & _s_addr);

			//! Check if it is connected
			bool isConnected()
			{	return InetClient::isConnected();	}

		protected:
			//! An event raised when client is disconnected
		    virtual void OnDisconnect(){}

		private:
			//* Functions derived from InetClient */
			virtual void OnConnect(Socket & con_socket){};

			// When data arrives
			virtual void OnDataArrived(const BinaryData & data);

			// An event when client is connected
		    virtual void OnConnect(){}

			// An event when an error is raised when collecting data
			virtual void OnError(Exception &e){}
		};	// !Client class
	};	// !HTTP namespace
};	// !OONet namespace
#endif // !OONET_HTTP_CLIENT_H_INCLUDED
