#ifndef OONET_HTTP_REQUEST_H_DEFINED
#define OONET_HTTP_REQUEST_H_DEFINED

#include "../oonet.hpp"
#include "./packet.hpp"
#include "./url.hpp"

namespace oonet
{
	namespace http
	{
		//! A general class for handling HTTP request Packets.
		/**
			Comes from http::Packet and will give more resolution
			on parsing and rendering. Except of 3 major parts, you
			can now parse the title too. This is done transperantly
			as render() and parse() are overloaded to implement additional
			functionality.
		*/
		class request :
			public packet
		{
		protected:
			const static binary_data const_get;
			const static binary_data const_post;

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
			request(void);

			//! Copy constructor
			request(const request & r);

			//! Destructor
			virtual ~request(void);

			//! Copy Operator
			request & operator=(const request & r);

			//! Render packet with specific title componments
			/**
				This is overloaded from http::Packet::render() and before renderning
				the packet, it will render the title from variables: request::http_type, request::url and request::http_version.
			@see http::Packet::render() for further explanation.
			*/
			virtual binary_data render(const binary_data & nl_delimiter = const_crlf);

			//! Parse an HTTP request packet
			/**
				This is overloaded function from http::Packet::parse() and after
				parsing its major componments it will parse the title and
				populate the variables request::http_type, request::url and request::http_version.
				Additionally to the exceptions tha may be thrown from http::Packet::parse()
				this overloaded function will throw too:
			@throw ExceptionWrongFormat if the title of HTTP packet is not an HTTP request's title.
			@see http::Packet::parse() for further explanation.
			*/
			virtual bool parse(const binary_data & dt_in, binary_data * dt_remain = NULL);
		};	// !request class
	};	// !http namespace
};	// !oonet namespace

#endif // !OONET_HTTP_REQUEST_H_DEFINED
