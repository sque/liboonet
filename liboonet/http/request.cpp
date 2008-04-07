/**
@file request.cpp
@brief Implementation of http::request class
*/
#include "./request.hpp"

namespace oonet
{
	namespace http
	{
		const binary_data request::const_get = binary_data("GET");
		const binary_data request::const_post = binary_data("POST");

		request::request(void)
		{
			// Default options
			m_req_method = REQUEST_GET;
			m_uri = "/";
			m_http_version = const_http_ver1_1;
		}

		request::~request(void)
		{
		}

		// Copy constructor
		request::request(const request & r):
			message(r)
		{
			// Copy data
			m_uri = r.m_uri;
			m_req_method = r.m_req_method;
			m_http_version = r.m_http_version;
		}

		// Copy Operator
		request & request::operator=(const request & r)
		{
			// Copy parent
			message::operator =(r);

			// Copy data
			m_uri = r.m_uri;
			m_req_method = r.m_req_method;
			m_http_version = r.m_http_version;
			return *this;
		}

		// Render message
		binary_data request::render(const binary_data & nl_delimiter)
		{
			// Make up title
			if (m_req_method == REQUEST_GET)
			{
				m_title = const_get;
				m_title += const_space;
				b_has_body = false;
			}
			else if (m_req_method == REQUEST_POST)
			{
				m_title = const_post;
				m_title += const_space;
				b_has_body = true;
			}
			m_title += binary_data((string)m_uri);
			m_title += const_space;
			m_title += m_http_version;

			// Render the message
			return message::render(nl_delimiter);
		}

		// Parse message
		bool request::parse(const binary_data & dt_in, binary_data * dt_remain)
		{	size_t commandend_pos, urlend_pos;
			binary_data _command_string;

			// Parse message
			if(!message::parse(dt_in, dt_remain))
				return false;

			// Get Command
			if ((commandend_pos = m_title.find(const_space))== binary_data::npos)
				OONET_THROW_EXCEPTION(ExceptionWrongFormat,
					"This is not an http request message");
			_command_string = m_title.sub_data(0, commandend_pos);
			if (_command_string == const_get)
				m_req_method = REQUEST_GET;
			else if (_command_string == const_post)
				m_req_method = REQUEST_POST;
			else
			{
				m_req_method = REQUEST_UNKNOWN;
				OONET_THROW_EXCEPTION(ExceptionUnimplemented,
					"This http request is not implemented!");
			}

			// Get URL
			commandend_pos ++;	// Start one position lower
			if ((urlend_pos =  m_title.find(const_space, commandend_pos)) == binary_data::npos)
				OONET_THROW_EXCEPTION(ExceptionWrongFormat,
					"This is not an http request message");
			m_uri = title().sub_data(commandend_pos, urlend_pos - commandend_pos).to_string();
			if ((string)m_uri == "")
				OONET_THROW_EXCEPTION(ExceptionWrongFormat,
					"This is not an http request message");

			// Get version
			urlend_pos ++;
			m_http_version = m_title.get_from(urlend_pos);
			if ((m_http_version != const_http_ver1_1) && (m_http_version != const_http_ver1_0))
				OONET_THROW_EXCEPTION(ExceptionWrongFormat,
					"This is not an http request message");
			return true;
		}
	};	// !http namespace
};	// !oonet namespace
