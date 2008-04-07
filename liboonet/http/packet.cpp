/**
@file Packet.cpp
@brief Implementation of http::Packet class
*/
#include "./packet.hpp"

namespace oonet
{
	namespace http
	{
		const binary_data packet::const_http_ver1_1 = binary_data("HTTP/1.1");
		const binary_data packet::const_http_ver1_0 = binary_data("HTTP/1.0");
		const binary_data packet::const_content_length = binary_data("Content-Length");

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
				m_headers.set(const_content_length, binary_data(cstr_tmp));
			}
			else
			{
				if (m_headers.exist(const_content_length))
					m_headers.erase(const_content_length);
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
		binary_data packet::render(const binary_data & nl_delimiter)
		{	binary_data tmp_packet;

			// Update Headers
			_update_headers();

			// Construct Packet
			// Title
			tmp_packet = m_title;
			tmp_packet += nl_delimiter;

			// Headers
			tmp_packet += m_headers.render(nl_delimiter);
			tmp_packet += nl_delimiter;
			tmp_packet += nl_delimiter;

			// Body
			if (b_has_body)
				tmp_packet += m_body;

			return tmp_packet;
		}

		// Parse data and save to packet
		bool packet::parse(const binary_data & dt_in, binary_data * dt_remain)
		{	binary_data str_body_size;
			binary_data start_line, head, nl_delimiter;
			long body_size;
			size_t head_end_pos;	// Position where head stops
			size_t body_start_pos;	// Position where body starts
			size_t nl_pos;			// Position of new line

			// Find two new lines that mention end of heads (CRLF and LF)
			if ((head_end_pos = dt_in.find(const_crlfcrlf)) != binary_data::npos)
			{	body_start_pos = head_end_pos + 4;
			}
			else
			{
				if ((head_end_pos = dt_in.find(const_lflf)) != binary_data::npos)
				{	body_start_pos = head_end_pos + 2;
				}
				else
				{	return false;	// Incomplete data stream
				}
			}

			// Get all the message head
			head = dt_in.get_until(head_end_pos);

			// Get title
			if ((nl_pos = _find_smart_new_line(head, nl_delimiter)) == binary_data::npos)
				OONET_THROW_EXCEPTION(ExceptionWrongFormat,
					"This is not an HTTP packet!");
			m_title = head.sub_data(0, nl_pos);					// Extract Title


			// Get Headers
			head = head.get_from(nl_pos + nl_delimiter.size());	// Cat rest of head.
			m_headers.parse(head);

			// Get content-length header
			if (m_headers.exist(const_content_length))
			{	str_body_size = m_headers.get(const_content_length);
				// Validate length
				if ((body_size = atol(str_body_size.to_string().c_str())) < 0)
					OONET_THROW_EXCEPTION(ExceptionWrongFormat,
						"HTTP Packet says that contains body with size less than 0!?!"
					);
				// Validate if we have body
				if ((dt_in.size() - body_start_pos) < (size_t)body_size)
					return false;	// Incomplete data stream
				b_has_body = true;
			}
			else
			{
				// We dont have a body
				b_has_body = false;
				body_size = 0;
				m_body.clear();
			}

			// Get body
			m_body = dt_in.sub_data(body_start_pos, body_size);

			// Calculate remaining data
			if (dt_remain)
			{
				*dt_remain = dt_in.get_from(body_start_pos + body_size);
			}
			return true;
		}
	};	// !http namespace
};	// !oonet namespace
