/**
@file response.cpp
@brief Implementation of http::response class
*/
#include "./response.hpp"

namespace oonet
{
	namespace http
	{
		// Copy constructor
		response::response(const response &r):
			message(r),
			m_status_code(r.m_status_code),
			m_reason_phrase(r.m_reason_phrase)
		{
		}

		// Copy operator
		response & response::operator=(const response & r)
		{	message::operator =(r);
			m_status_code = r.m_status_code;
			m_reason_phrase = r.m_reason_phrase;
			return *this;
		}

		// Render a message from data
		binary_data response::render(const constants::static_constant & nl_delimiter)
		{	char _s_title[1024];

			// Prepare title
			_snprintf(_s_title, 1024, "%s %03d %s",
				constants::http_ver1_1.as_string.c_str(),
				m_status_code,
				to_string(m_reason_phrase).c_str());

			// Prepare Title
			m_title = cmem_ref((const char *)_s_title);

			// Return rendered message
			return message::render(nl_delimiter);
		}

		// Parse data and save to message
		bool response::parse(const binary_data & dt_in, binary_data * dt_remain)
		{	size_t httpversionend_pos, status_code_end_pos;
			binary_data _httpversion, bt_status_code;

			// Parse basic message
			if(!message::parse(dt_in, dt_remain))
				return false;

			// Get version of HTTP
			if ((httpversionend_pos = m_title.find(constants::space_char)) == binary_data::npos)
				OONET_THROW_EXCEPTION(ExceptionWrongFormat,
					"Wrong formated header!");
			_httpversion = m_title.sub_data(0, httpversionend_pos);
			if ((_httpversion != constants::http_ver1_0.as_binary_data) && (_httpversion != constants::http_ver1_1.as_binary_data))
				OONET_THROW_EXCEPTION(ExceptionWrongFormat,
					"Unknown version of HTTP message!");

			// Get status code
			httpversionend_pos++;
			status_code_end_pos = m_title.find(constants::space_char, httpversionend_pos);
			if (((bt_status_code = m_title.sub_data(httpversionend_pos, status_code_end_pos - httpversionend_pos)) == binary_data::nothing)
				|| (bt_status_code.size() != 3))
				OONET_THROW_EXCEPTION(ExceptionWrongFormat,
					"HTTP response without error code!");
			m_status_code = (ushort)atol(to_string(bt_status_code).c_str());

			// Get reason phrase
			if (status_code_end_pos == string::npos)
			{
				m_reason_phrase.clear();
			}
			else
			{
				status_code_end_pos ++;
				m_reason_phrase = m_title.get_from(status_code_end_pos);
			}


			// Return message
			return true;
		}
	};	// !http namespace
};	// !oonet namespace
