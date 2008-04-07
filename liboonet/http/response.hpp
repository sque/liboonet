#ifndef OONET_HTTP_RESPONSE_H_DEFINED
#define OONET_HTTP_RESPONSE_H_DEFINED

#include "../oonet.hpp"
#include "./headers_list.hpp"
#include "./packet.hpp"

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
			public packet
		{
		protected:
			binary_data m_error_code;
			binary_data m_error_msg;
		public:
			//! Default constructor
			response(void);

			//! Copy constructor
			response(const response &r);

			//! Copy operator
			response & operator=(const response & r);

			//! Default destructor
			virtual ~response(void);

			//! Render packet with specific HTTP response parameters
			/**
				This is overloaded from http::Packet::render() and before renderning
				the packet, it will render the title from variables: response::ErrorCode and response::ErrorMsg.
			@see http::Packet::render() for further explanation.
			*/
			virtual binary_data render(const string & new_line = OONET_DEFAULT_HTTP_NEWLINE);

			//! Parse an HTTP response packet
			/**
				This is overloaded function from http::Packet::parse() and after
				parsing its major componments it will parse the title and
				populate the variables response::ErrorCode and response::ErrorMsg.
				Additionally to the exceptions tha may be thrown from http::Packet::parse()
				this overloaded function will throw too:
			@throw ExceptionWrongFormat if the title of HTTP packet is not an HTTP reponse's title.
			@see http::Packet::parse() for further explanation.
			*/
			virtual bool parse(const binary_data & dt_in, binary_data * dt_remain = NULL);

			//! Reference at error code (const)
			inline const binary_data & error_code() const
			{	return m_error_code;	}

			//! Reference at error code
			inline binary_data & error_code()
			{	return m_error_code;	}

			//! Reference at error message (const)
			inline const binary_data & error_message() const
			{	return m_error_msg;	}

			//! Reference at error message
			inline binary_data & error_message()
			{	return m_error_msg;	}
		};	// !response class
	};	// !http namespace
};	// !oonet namespace
#endif // OONET_HTTP_RESPONSE_H_DEFINED
