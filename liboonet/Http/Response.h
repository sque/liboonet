#ifndef OONET_HTTP_RESPONSE_H_DEFINED
#define OONET_HTTP_RESPONSE_H_DEFINED

#include "../oonet.hpp"
#include "Headers.h"
#include "Packet.h"

namespace oonet
{
	namespace HTTP
	{
		//! A general class for handling HTTP Response Packets.
		/**
			Comes from HTTP::Packet and will give more resolution
			on parsing and rendering. Except of 3 major parts, you
			can now parse the title too. This is done transperantly
			as render() and parse() are overloaded to implement additional
			functionality.
		*/
		class Response:
			public Packet
		{
		public:
			string ErrorCode;		//!< The error code of the response
			string ErrorMsg;		//!< The error message of the response

			//! Default constructor
			Response(void);

			//! Copy constructor
			Response(const Response &r);

			//! Copy operator
			Response & operator=(const Response & r);

			//! Default destructor
			virtual ~Response(void);

			//! Render packet with specific HTTP response parameters
			/**
				This is overloaded from HTTP::Packet::render() and before renderning
				the packet, it will render the title from variables: Response::ErrorCode and Response::ErrorMsg.
			@see HTTP::Packet::render() for further explanation.
			*/
			virtual binary_data render(const string & new_line = OONET_DEFAULT_HTTP_NEWLINE);

			//! Parse an HTTP Response packet
			/**
				This is overloaded function from HTTP::Packet::parse() and after
				parsing its major componments it will parse the title and
				populate the variables Response::ErrorCode and Response::ErrorMsg.
				Additionally to the exceptions tha may be thrown from HTTP::Packet::parse()
				this overloaded function will throw too:
			@throw ExceptionWrongFormat if the title of HTTP packet is not an HTTP reponse's title.
			@see HTTP::Packet::parse() for further explanation.
			*/
			virtual size_t parse(const binary_data & data);
		};	// !Response class
	};	// !HTTP namespace
};	// !oonet namespace
#endif // OONET_HTTP_RESPONSE_H_DEFINED
