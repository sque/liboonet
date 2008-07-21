#ifndef OONET_HTTP_PACKET_HPP_INCLUDED
#define OONET_HTTP_PACKET_HPP_INCLUDED

#include "../oonet.hpp"
#include "./headers_list.hpp"

namespace oonet
{
	namespace http
	{
		//! Exception raised when http traffic is incomplete
		OONET_DECLARE_EXCEPTION(ExceptionIncomplete);

		//! A general class for handling HTTP Packets
		/**
			It can render or parse HTTP packets from/to its major parts (Title, Headers, Body)
		*/
		class message
		{
		protected:
			// Update headers
			void _update_headers();

			binary_data		m_title;	//!< The title of the message
			headers_list	m_headers;	//!< The headers of the message
			binary_data		m_body;		//!< The Body of the document
			bool			b_has_body;	//!< A flag if message includes body

		public:

			//! Default Constructor
			inline message()
                :b_has_body(true){}

			//! Copy constructor. Creates an object based on another instance.
			/**
				@param r The source object to copy data.
			*/
			inline message(const message &r)
            {   *this = r;  }

			//! Destructor
			inline virtual ~message(){}

			//! Copy operator
			/**
				@param r The right part of the assignment.
			*/
			message & operator=(const message & r);

			//! Render a message in HTTP format
			/**
				It will use all the internal data (title, headers, body) and create
				a right formated HTTP/1.1 message.
			@param nl_str The string to use for new lines.
			@return The rendered message, ready for transmition
			*/
			virtual binary_data render(const constants::static_constant & nl_delimiter = constants::crlf);

			//! Parse HTTP traffic and extract the leading HTTP message
			/**
				If a message is found it will be splitted it in major parts
				and internal variables will be populated with its parts.
				HTTP message must start from the begining of data.
			@param data The data block to find an HTTP message
			@return The size of datablock that the message was found.
			@throw ExceptionIncomplete If the traffic seems to be valid HTTP traffic
				but there is no complete message inside, data are missing.
			@throw ExceptionWrongFormat If the traffic doesn't meet the specification
				of HTTP.
			*/
			virtual bool parse(const binary_data & dt_in, binary_data * dt_remain = NULL);

			//! Reference at title (const)
			inline const binary_data & title() const
			{	return m_title;		}

			//! Reference at title
			inline binary_data & title()
			{	return m_title;	}

			//! Reference at headers (const)
			inline const headers_list & headers() const
			{	return m_headers;	}

			//! Reference at headers
			inline headers_list & headers()
			{	return m_headers;	}

			//! Reference at body (const)
			inline const binary_data & body() const
			{	return m_body;	}

			//! Reference at body (const)
			inline binary_data & body()
			{	return m_body;	}

		};	// !Packet Class
	};	// !http namespace
};	// !oonet namespace

#endif // !OONET_HTTP_PACKET_HPP_INCLUDED
