#ifndef OONET_HTTP_REQUEST_H_DEFINED
#define OONET_HTTP_REQUEST_H_DEFINED

#include "../oonet.hpp"
#include "./message.hpp"
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
			public message
		{
		public:
			//! Enumerate the request type
			enum E_REQUEST_METHOD
			{
				REQUEST_OPTIONS,	//! OPTIONS request
				REQUEST_GET,		//! GET request
				REQUEST_POST,		//! POST request
				REQUEST_HEAD,		//! HEAD request
				REQUEST_PUT,		//! PUT request
				REQUEST_DELETE,		//! DELETE request
				REQUEST_TRACE,		//! TRACE request
				REQUEST_CONNECT,	//! CONNECT request
				REQUEST_UNKNOWN		//! The rest here..
			};

		protected:
			const static binary_data const_get;
			const static binary_data const_post;

			E_REQUEST_METHOD m_req_method;	//!< HTTP request method
			binary_data m_http_version;		//!< HTTP version
			Url m_uri;						//!< Requested url

		public:

			//! Constructor
			request(void);

			//! Copy constructor
			request(const request & r);

			//! Destructor
			virtual ~request(void);

			//! Copy Operator
			request & operator=(const request & r);

			//! Render message with specific title componments
			/**
				This is overloaded from http::Packet::render() and before renderning
				the message, it will render the title from variables: request::http_type, request::url and request::http_version.
			@see http::Packet::render() for further explanation.
			*/
			virtual binary_data render(const binary_data & nl_delimiter = const_crlf);

			//! Parse an HTTP request message
			/**
				This is overloaded function from http::Packet::parse() and after
				parsing its major componments it will parse the title and
				populate the variables request::http_type, request::url and request::http_version.
				Additionally to the exceptions tha may be thrown from http::Packet::parse()
				this overloaded function will throw too:
			@throw ExceptionWrongFormat if the title of HTTP message is not an HTTP request's title.
			@see http::Packet::parse() for further explanation.
			*/
			virtual bool parse(const binary_data & dt_in, binary_data * dt_remain = NULL);

			//! Reference at HTTP version (const)
			inline const binary_data & http_version() const
			{	return m_http_version;	}

			//! Reference at HTTP version
			inline binary_data & http_version()
			{	return m_http_version;	}

			//! Reference at uri (const)
			inline const Url & uri() const
			{	return m_uri;	}

			//! Reference at uri
			inline Url & uri()
			{	return m_uri;	}

			//! Reference at request method
			inline E_REQUEST_METHOD & request_method()
			{	return m_req_method;	}

			//! Reference at request method (const)
			inline const E_REQUEST_METHOD & request_method() const
			{	return m_req_method;	}
		};	// !request class
	};	// !http namespace
};	// !oonet namespace

#endif // !OONET_HTTP_REQUEST_H_DEFINED
