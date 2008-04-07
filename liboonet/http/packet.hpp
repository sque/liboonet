#ifndef OONET_HTTP_PACKET_H
#define OONET_HTTP_PACKET_H

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
		class packet
		{
		protected:
			// Update headers
			void _update_headers();

			binary_data		m_title;	//!< The title of the packet
			headers_list	m_headers;	//!< The headers of the packet
			binary_data		m_body;		//!< The Body of the document
			bool			b_has_body;	//!< A flag if packet includes body

			const static binary_data const_http_ver1_1;
			const static binary_data const_http_ver1_0;
			const static binary_data const_content_length;
		public:

			//! Default Constructor
			packet(void);

			//! Copy constructor. Creates an object based on another instance.
			/**
				@param r The source object to copy data.
			*/
			packet(const packet &r);

			//! Destructor
			virtual ~packet(void);

			//! Copy operator
			/**
				@param r The right part of the assignment.
			*/
			packet & operator=(const packet & r);

			//! Render a packet in HTTP format
			/**
				It will use all the internal data (title, headers, body) and create
				a right formated HTTP/1.1 packet.
			@param nl_str The string to use for new lines.
			@return The rendered packet, ready for transmition
			*/
			virtual binary_data render(const binary_data & nl_delimiter = const_crlf);

			//! Parse HTTP traffic and extract the leading HTTP packet
			/**
				If a packet is found it will be splitted it in major parts
				and internal variables will be populated with its parts.
				HTTP packet must start from the begining of data.
			@param data The data block to find an HTTP packet
			@return The size of datablock that the packet was found.
			@throw ExceptionIncomplete If the traffic seems to be valid HTTP traffic
				but there is no complete packet inside, data are missing.
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

#endif // !OONET_HTTP_PACKET_H
