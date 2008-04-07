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
			binary_data dt_headers_and_below, nl_delimiter;
			long body_size;
			size_t title_end_pos;	// Position where title ends
			size_t body_start_pos;	// Position where body starts
			size_t nl_pos;			// Position of new line

			// Get title
			if ((title_end_pos = _find_smart_new_line(dt_in, nl_delimiter)) == binary_data::npos)
				return false;	// Not even title is here
			m_title =  dt_in.get_until(title_end_pos);
			dt_headers_and_below = dt_in.get_from(title_end_pos + nl_delimiter.size());

			// Get headers
			if ((body_start_pos = m_headers.parse(dt_headers_and_below)) == binary_data::npos)
				return false;	// Incomplete Head!
			body_start_pos += title_end_pos + nl_delimiter.size();

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
				*dt_remain = dt_in.get_from(body_start_pos + body_size);

			return true;
		}
	};	// !http namespace
};	// !oonet namespace
