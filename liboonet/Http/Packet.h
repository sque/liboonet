#ifndef OONET_HTTP_PACKET_H
#define OONET_HTTP_PACKET_H

#include "../OONet.h"
#include "Headers.h"

namespace OONet
{
	namespace HTTP
	{
		//! Exception raised when http traffic is incomplete
		OONET_DECLARE_EXCEPTION(ExceptionIncomplete);

		//! A general class for handling HTTP Packets
		/**
			It can render or parse HTTP packets from/to its major parts (Title, Headers, Body)
		*/
		class Packet
		{
		protected:
			// Update headers
			void _UpdateHeaders();

			string		_Title;		//!< The title of the packet
			Headers		_Headers;	//!< The headers of the packet
			BinaryData	_Body;		//!< The Body of the document
			bool		HasBody;	//!< A flag if packet includes body

		public:

			//! Default Constructor
			Packet(void);

			//! Copy constructor. Creates an object based on another instance.
			/**
				@param r The source object to copy data.
			*/
			Packet(const Packet &r);

			//! Destructor
			virtual ~Packet(void);

			//! Copy operator
			/**
				@param r The right part of the assignment.
			*/
			Packet & operator=(const Packet & r);

			//! Render a packet in HTTP format
			/**
				It will use all the internal data (title, headers, body) and create
				a right formated HTTP/1.1 packet.
			@param nl_str The string to use for new lines.
			@return The rendered packet, ready for transmition
			*/
			virtual BinaryData render(const string & nl_str = OONET_DEFAULT_HTTP_NEWLINE);

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
			virtual size_t parse(const BinaryData & data);

			//! Get title of packet
			inline const string & getTitle() const
			{	return _Title;		}

			//! Get constant headers of packet
			inline const Headers & getHeaders() const
			{	return _Headers;	}

			//! Get by reference headers to be changable
			inline Headers & getHeaders()
			{	return _Headers;	}

			//! Get bosy of packet
			inline const BinaryData & getBody() const
			{	return _Body;	}

			//! Set title of packet
			inline string & setTitle(const string & r)
			{	return _Title = r;	}

			//! Set headers of packet
			inline Headers & setHeaders(const Headers & r)
			{	return _Headers = r;	}

			//! Set body of packet
			inline BinaryData & setBody(const BinaryData & r)
			{	return _Body = r;	}

		};	// !Packet Class
	};	// !HTTP namespace
};	// !OONet namespace

#endif // !OONET_HTTP_PACKET_H
