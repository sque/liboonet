/**
@file Packet.cpp
@brief Implementation of http::Packet class
*/
#include "./packet.hpp"

namespace oonet
{
	namespace http
	{
		packet::packet(void)
			:b_has_body(true)
		{
		}

		packet::~packet(void)
		{
		}

		// Copy constructor
		packet::packet(const packet &r)
		{
			*this = r;
		}

		// Update headers
		void packet::_update_headers()
		{
			if (b_has_body)
			{
				char cstr_tmp[30];
				_snprintf(cstr_tmp, 30, "%d", m_body.size());
				m_headers.set("Content-Length", cstr_tmp);
			}
			else
			{
				if (m_headers.exist("Content-Length"))
					m_headers.erase("Content-Length");
			}
		}

		// Copy operator
		packet & packet::operator=(const packet & r)
		{
			m_body = r.m_body;
			m_headers = r.m_headers;
			m_title = r.m_title;
			return *this;
		}

		// Render a packet from data
		binary_data packet::render(const string & nl_str)
		{	binary_data TmpPacket;

			// Update Headers
			_update_headers();

			// Construct Packet
			// Title
			TmpPacket = binary_data(m_title) + binary_data(nl_str);

			// Headers
			TmpPacket += binary_data(m_headers.render(nl_str)) + binary_data(nl_str + nl_str);

			// Body
			if (b_has_body)
				TmpPacket += m_body;

			return TmpPacket;
		}

		// Parse data and save to packet
		bool packet::parse(const binary_data & dt_in, binary_data * dt_remain)
		{	string Head, _StrBodySize, nl_str;
			long _BodySize;
			size_t HeadEnd_pos;		// Position where head stops
			size_t BodyStart_pos;	// Position where body starts
			size_t nl_pos;			// Position of new line

			// Find two new lines that mention end of heads (CRLF and LF)
			if ((HeadEnd_pos = dt_in.find(binary_data(CRLF+CRLF))) != binary_data::npos)
			{	BodyStart_pos = HeadEnd_pos + 4;
			}
			else
			{
				if ((HeadEnd_pos = dt_in.find(binary_data(LF+LF))) != binary_data::npos)
				{	BodyStart_pos = HeadEnd_pos + 2;
				}
				else
				{	return false;	// Incomplete data stream
				}
			}

			// Get head
			Head = dt_in.slice(0, HeadEnd_pos).to_string();

			// Get title
			if ((nl_pos = _find_smart_new_line(Head, nl_str)) == string::npos)
				OONET_THROW_EXCEPTION(ExceptionWrongFormat,
					"This is not an HTTP packet!");
			m_title = Head.substr(0, nl_pos);					// Extract Title
			Head = Head.substr(nl_pos + nl_str.size());			// Cat rest of head.

			// Get Headers
			m_headers.parse(Head);

			// Get content-length header
			if (m_headers.exist("Content-Length"))
			{	_StrBodySize = m_headers.get("Content-Length");
				// Validate length
				if ((_BodySize = atol(_StrBodySize.c_str())) < 0)
					OONET_THROW_EXCEPTION(ExceptionWrongFormat,
						"HTTP Packet says that contains body with size less than 0!?!"
					);
				// Validate if we have body
				if ((dt_in.size() - BodyStart_pos) < (size_t)_BodySize)
					return false;	// Incomplete data stream
				b_has_body = true;
			}
			else
			{
				// We dont have a body
				b_has_body = false;
				_BodySize = 0;
				m_body.clear();
			}

			// Get body
			m_body = dt_in.slice(BodyStart_pos, _BodySize);

			// Calculate remaining data
			if (dt_remain)
			{
				*dt_remain = dt_in.get_from(BodyStart_pos + _BodySize);
			}
			return true;
		}
	};	// !http namespace
};	// !oonet namespace
