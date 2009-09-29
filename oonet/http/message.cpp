/**
@file message.cpp
@brief Implementation of http::message class
*/
#include "./message.hpp"

namespace oonet
{
	namespace http
	{
		const binary_data message::const_http_ver1_1 = binary_data("HTTP/1.1");
		const binary_data message::const_http_ver1_0 = binary_data("HTTP/1.0");
		const binary_data message::const_content_length = binary_data("Content-Length");

		message::message(void)
			:b_has_body(true)
		{
		}

		message::~message(void)
		{
		}

		// Copy constructor
		message::message(const message &r)
		{
			*this = r;
		}

		// Update headers
		void message::_update_headers()
		{
			if (b_has_body)
			{
				char cstr_tmp[30];
				_snprintf(cstr_tmp, 30, "%d", m_body.size());
				m_headers.erase_all_by_name(const_content_length.to_string());
				m_headers.add(const_content_length.to_string(), cstr_tmp);
			}
			else
				m_headers.erase(m_headers.find(const_content_length.to_string()));
		}

		// Copy operator
		message & message::operator=(const message & r)
		{
			m_body = r.m_body;
			m_headers = r.m_headers;
			m_title = r.m_title;
			return *this;
		}

		// Render a message from data
		binary_data message::render(const binary_data & nl_delimiter)
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

		// Parse data and save to message
		bool message::parse(const binary_data & dt_in, binary_data * dt_remain)
		{	binary_data dt_headers_and_below, nl_delimiter;
			binary_data dt_clear = dt_in;	// Clear packet data without leading new lines
			
			long body_size;
			size_t title_end_pos;			// Position where title ends
			size_t body_start_pos;			// Position where body starts
			size_t leading_garbagenl = 0;	// Leading garbage new lines

			// Clean up leading new lines that should be ignored
			while(1)
			{	if (dt_clear.sub_data(0,2) == const_crlf)
				{
					leading_garbagenl += const_crlf.size();
					dt_clear = dt_clear.get_from(const_crlf.size());
					continue;
				}
				else if (dt_clear.sub_data(0, 1) == const_lf)
				{
					leading_garbagenl += const_lf.size();
					dt_clear = dt_clear.get_from(const_lf.size());
					continue;
				}
				break;
			}

			// Get title
			if ((title_end_pos = _smart_find_new_line(dt_clear, nl_delimiter)) == binary_data::npos)
				return false;	// Not even title is here
			m_title =  dt_clear.get_until(title_end_pos);
			dt_headers_and_below = dt_clear.get_from(title_end_pos + nl_delimiter.size());

			// Get headers
			if ((body_start_pos = m_headers.parse(dt_headers_and_below)) == binary_data::npos)
				return false;	// Incomplete Head!
			body_start_pos += title_end_pos + nl_delimiter.size();

			// Get content-length header
			if (m_headers.find_first_integer(const_content_length.to_string(), body_size))
			{	if (body_size  < 0)
					OONET_THROW_EXCEPTION(ExceptionWrongFormat,
						"HTTP Packet says that contains body with size less than 0!?!"
					);

				// Validate if we have body
				if ((dt_clear.size() - body_start_pos) < (size_t)body_size)
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
			m_body = dt_clear.sub_data(body_start_pos, body_size);

			// Calculate remaining data
			if (dt_remain)
				*dt_remain = dt_in.get_from(leading_garbagenl + body_start_pos + body_size);

			return true;
		}
	};	// !http namespace
};	// !oonet namespace
