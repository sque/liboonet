/**
@file response.cpp
@brief Implementation of http::response class
*/
#include "./response.hpp"

namespace oonet
{
	namespace http
	{
		response::response(void):
			message(),
			m_status_code(200),
			m_reason_phrase("OK")
		{
		}

		response::~response(void)
		{
		}

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
		binary_data response::render(const binary_data & nl_delimiter)
		{	char _s_title[1024];

			// Prepare title
			_snprintf(_s_title, 1024, "%s %03d %s",
				const_http_ver1_1.to_string().c_str(),
				m_status_code,
				m_reason_phrase.to_string().c_str());

			// Prepare Title
			m_title = binary_data(_s_title);

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
			if ((httpversionend_pos = m_title.find(const_space)) == binary_data::npos)
				OONET_THROW_EXCEPTION(ExceptionWrongFormat,
					"Wrong formated header!");
			_httpversion = m_title.sub_data(0, httpversionend_pos);
			if ((_httpversion != const_http_ver1_0) && (_httpversion != const_http_ver1_1))
				OONET_THROW_EXCEPTION(ExceptionWrongFormat,
					"Unknown version of HTTP message!");

			// Get status code
			httpversionend_pos++;
			status_code_end_pos = m_title.find(const_space, httpversionend_pos);
			if (((bt_status_code = m_title.sub_data(httpversionend_pos, status_code_end_pos - httpversionend_pos)) == binary_data::nothing)
				|| (bt_status_code.size() != 3))
				OONET_THROW_EXCEPTION(ExceptionWrongFormat,
					"HTTP response without error code!");
			m_status_code = (ushort)atol(bt_status_code.to_string().c_str());

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
