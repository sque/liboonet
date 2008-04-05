#ifndef OONET_HTTP_REQUEST_H_DEFINED
#define OONET_HTTP_REQUEST_H_DEFINED

#include "../oonet.hpp"
#include "./Packet.h"
#include "./Url.h"

namespace oonet
{
	namespace http
	{
		//! A general class for handling HTTP Request Packets.
		/**
			Comes from http::Packet and will give more resolution
			on parsing and rendering. Except of 3 major parts, you
			can now parse the title too. This is done transperantly
			as render() and parse() are overloaded to implement additional
			functionality.
		*/
		class Request :
			public Packet
		{
		public:
			//! Enumerate the request type
			enum EN_REQUEST_TYPE
			{
				REQUEST_GET,		//! GET request
				REQUEST_POST,		//! POST request
				REQUEST_UNKNOWN		//! The rest here..
			};

			EN_REQUEST_TYPE http_type;	//!< HTTP command (GET/POST)
			string http_version;		//!< HTTP version
			Url url;					//!< Requested url

			//! Constructor
			Request(void);

			//! Copy constructor
			Request(const Request & r);

			//! Destructor
			virtual ~Request(void);

			//! Copy Operator
			Request & operator=(const Request & r);

			//! Render packet with specific title componments
			/**
				This is overloaded from http::Packet::render() and before renderning
				the packet, it will render the title from variables: Request::http_type, Request::url and Request::http_version.
			@see http::Packet::render() for further explanation.
			*/
			virtual binary_data render(const string & new_line = OONET_DEFAULT_HTTP_NEWLINE);

			//! Parse an HTTP Request packet
			/**
				This is overloaded function from http::Packet::parse() and after
				parsing its major componments it will parse the title and
				populate the variables Request::http_type, Request::url and Request::http_version.
				Additionally to the exceptions tha may be thrown from http::Packet::parse()
				this overloaded function will throw too:
			@throw ExceptionWrongFormat if the title of HTTP packet is not an HTTP request's title.
			@see http::Packet::parse() for further explanation.
			*/
			virtual bool parse(const binary_data & dt_in, binary_data * dt_remain = NULL);
		};	// !Request class
	};	// !http namespace
};	// !oonet namespace

#endif // !OONET_HTTP_REQUEST_H_DEFINED
