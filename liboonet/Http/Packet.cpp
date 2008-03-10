/**
@file Packet.cpp
@brief Implementation of HTTP::Packet class
*/
#include "Http/Packet.h"
#include "platform.h"

namespace OONet
{
	namespace HTTP
	{
		Packet::Packet(void):
			HasBody(true)
		{
		}

		Packet::~Packet(void)
		{
		}

		// Copy constructor
		Packet::Packet(const Packet &r)
		{
			*this = r;
		}

		// Update headers
		void Packet::_UpdateHeaders()
		{
		if (HasBody)
			{
				char tmpS[30];
				_snprintf(tmpS, 30, "%d", _Body.size());
				_Headers.setHeader("Content-Length", tmpS);
			}
			else
			{
				if (_Headers.headerExists("Content-Length"))
					_Headers.removeHeader("Content-Length");
			}
		}

		// Copy operator
		Packet & Packet::operator=(const Packet & r)
		{
			_Body = r._Body;
			_Headers = r._Headers;
			_Title = r._Title;
			return *this;
		}

		// Render a packet from data
		BinaryData Packet::render(const string & nl_str)
		{	BinaryData TmpPacket;

			// Update Headers
			_UpdateHeaders();

			// Construct Packet
			// Title
			TmpPacket = BinaryData(_Title) + BinaryData(nl_str);

			// Headers
			TmpPacket += BinaryData(_Headers.render(nl_str)) + BinaryData(nl_str + nl_str);

			// Body
			if (HasBody)
				TmpPacket += _Body;

			return TmpPacket;
		}

		// Parse data and save to packet
		size_t Packet::parse(const BinaryData & data)
		{	string Head, _StrBodySize, nl_str;
			long _BodySize;
			size_t HeadEnd_pos;		// Position where head stops
			size_t BodyStart_pos;	// Position where body starts
			size_t nl_pos;			// Position of new line

			// Find two new lines that mention end of heads (CRLF and LF)
			if ((HeadEnd_pos = data.find(BinaryData(CRLF+CRLF))) != BinaryData::npos)
			{	BodyStart_pos = HeadEnd_pos + 4;
			}
			else
			{
				if ((HeadEnd_pos = data.find(BinaryData(LF+LF))) != BinaryData::npos)
				{	BodyStart_pos = HeadEnd_pos + 2;
				}
				else
				{	OONET_THROW_EXCEPTION(ExceptionIncomplete,
						"Incomplete HTTP packet"
					);
				}
			}

			// Get head
			Head = data.slice(0, HeadEnd_pos).toString();

			// Get title
			if ((nl_pos = _find_smart_new_line(Head, nl_str)) == string::npos)
				OONET_THROW_EXCEPTION(ExceptionWrongFormat,
					"This is not an HTTP packet!");
			_Title = Head.substr(0, nl_pos);					// Extract Title
			Head = Head.substr(nl_pos + nl_str.size());			// Cat rest of head.

			// Get Headers
			_Headers.parse(Head);

			// Get content-length header
			try
			{	_StrBodySize = _Headers.getHeader("Content-Length");
				// Validate length
				if ((_BodySize = atol(_StrBodySize.c_str())) < 0)
					OONET_THROW_EXCEPTION(ExceptionWrongFormat,
						"HTTP Packet says that contains body with size less than 0!?!"
					);
				// Validate if we have body
				if ((data.size() - BodyStart_pos) < (size_t)_BodySize)
					OONET_THROW_EXCEPTION(ExceptionIncomplete,
						"Headers arrived, but not all the body..."
					);
				HasBody = true;
			}
			catch(ExceptionNotFound)
			{
				// We dont have a body
				HasBody = false;
				_BodySize = 0;
				_Body.clear();
			}

			// Get body
			_Body = data.slice(BodyStart_pos, _BodySize);

			return BodyStart_pos + _BodySize;
		}
	};	// !HTTP namespace
};	// !OONet namespace
