#ifndef OONET_HTTP_RESPONSE_H_DEFINED
#define OONET_HTTP_RESPONSE_H_DEFINED

#include "../oonet.hpp"
#include "./headers_list.hpp"
#include "./message.hpp"

namespace oonet
{
	namespace http
	{
		//! A general class for handling HTTP response Packets.
		/**
			Comes from http::Packet and will give more resolution
			on parsing and rendering. Except of 3 major parts, you
			can now parse the title too. This is done transperantly
			as render() and parse() are overloaded to implement additional
			functionality.
		*/
		class response:
			public message
		{
		protected:
			ushort m_status_code;
			binary_data m_reason_phrase;
		public:
			//! Default constructor
			response(void);

			//! Copy constructor
			response(const response &r);

			//! Copy operator
			response & operator=(const response & r);

			//! Default destructor
			virtual ~response(void);

			//! Render message with specific HTTP response parameters
			/**
				This is overloaded from http::Packet::render() and before renderning
				the message, it will render the title from variables: response::ErrorCode and response::ErrorMsg.
			@see http::Packet::render() for further explanation.
			*/
			virtual binary_data render(const binary_data & nl_delimiter = const_crlf);

			//! Parse an HTTP response message
			/**
				This is overloaded function from http::Packet::parse() and after
				parsing its major componments it will parse the title and
				populate the variables response::ErrorCode and response::ErrorMsg.
				Additionally to the exceptions tha may be thrown from http::Packet::parse()
				this overloaded function will throw too:
			@throw ExceptionWrongFormat if the title of HTTP message is not an HTTP reponse's title.
			@see http::Packet::parse() for further explanation.
			*/
			virtual bool parse(const binary_data & dt_in, binary_data * dt_remain = NULL);

			//! Reference at error code (const)
			inline const ushort & status_code() const
			{	return m_status_code;	}

			//! Reference at error code
			inline ushort & status_code()
			{	return m_status_code;	}

			//! Reference at error message (const)
			inline const binary_data & reason_phrase() const
			{	return m_reason_phrase;	}

			//! Reference at error message
			inline binary_data & reason_phrase()
			{	return m_reason_phrase;	}
		};	// !response class
	};	// !http namespace
};	// !oonet namespace
#endif // OONET_HTTP_RESPONSE_H_DEFINED
