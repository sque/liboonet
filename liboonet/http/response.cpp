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
			m_error_code("200"),
			m_error_msg("OK")
		{
		}

		response::~response(void)
		{
		}

		// Copy constructor
		response::response(const response &r):
			message(r),
			m_error_code(r.m_error_code),
			m_error_msg(r.m_error_msg)
		{
		}

		// Copy operator
		response & response::operator=(const response & r)
		{	message::operator =(r);
			m_error_code = r.m_error_code;
			m_error_msg = r.m_error_msg;
			return *this;
		}

		// Render a message from data
		binary_data response::render(const binary_data & nl_delimiter)
		{
			// Prepare Title
			m_title = const_http_ver1_1;
			m_title += const_space;
			m_title += m_error_code;
			m_title += const_space;
			m_title += m_error_msg;

			// Return rendered message
			return message::render(nl_delimiter);
		}

		// Parse data and save to message
		bool response::parse(const binary_data & dt_in, binary_data * dt_remain)
		{	size_t httpversionend_pos, errorcodeend_pos;
			binary_data _httpversion;

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

			// Get error code
			httpversionend_pos++;
			errorcodeend_pos = m_title.find(const_space, httpversionend_pos);
			if ((m_error_code = m_title.sub_data(httpversionend_pos, errorcodeend_pos - httpversionend_pos)) == binary_data::nothing)
				OONET_THROW_EXCEPTION(ExceptionWrongFormat,
					"HTTP response without error code!");

			// Get error message
			if (errorcodeend_pos == string::npos)
			{
				m_error_msg = "";
			}
			else
			{
				errorcodeend_pos ++;
				m_error_msg = m_title.get_from(errorcodeend_pos);
			}


			// Return message
			return true;
		}
	};	// !http namespace
};	// !oonet namespace
