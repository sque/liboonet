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
		const binary_data request::const_options = binary_data("OPTIONS");
		const binary_data request::const_head = binary_data("HEAD");
		const binary_data request::const_put = binary_data("PUT");
		const binary_data request::const_delete = binary_data("DELETE");
		const binary_data request::const_trace = binary_data("TRACE");
		const binary_data request::const_connect = binary_data("CONNECT");

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
			m_custom_method = r.m_custom_method;
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
			m_custom_method = r.m_custom_method;
			return *this;
		}

		// Render message
		binary_data request::render(const binary_data & nl_delimiter)
		{
			// Make up title
			switch(m_req_method)
			{
			case REQUEST_GET:			// GET
				m_title = const_get;
				m_title += const_space;
				b_has_body = false;
				break;
			case REQUEST_POST:			// POST
				m_title = const_post;
				m_title += const_space;
				b_has_body = true;
				break;
			case REQUEST_OPTIONS:		// OPTIONS
				m_title = const_options;
				m_title += const_space;
				b_has_body = true;
				break;
			case REQUEST_HEAD:			// HEAD
				m_title = const_head;
				m_title += const_space;
				b_has_body = true;
				break;
			case REQUEST_PUT:			// PUT
				m_title = const_put;
				m_title += const_space;
				b_has_body = true;
				break;
			case REQUEST_TRACE:			// TRACE
				m_title = const_trace;
				m_title += const_space;
				b_has_body = true;
				break;
			case REQUEST_DELETE:		// DELETE
				m_title = const_delete;
				m_title += const_space;
				b_has_body = true;
				break;
			case REQUEST_CONNECT:		// CONNECT
				m_title = const_connect;
				m_title += const_space;
				b_has_body = true;
				break;
			case REQUEST_CUSTOM:		// CUSTOM (extended)
				m_title = m_custom_method;
				m_title += const_space;
				b_has_body = true;
				break;
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
			if (_command_string.size() == 0)
				OONET_THROW_EXCEPTION(ExceptionWrongFormat,
					"This is not an http request message");
			else if (_command_string == const_get)		// GET
				m_req_method = REQUEST_GET;
			else if (_command_string == const_post)		// POST
				m_req_method = REQUEST_POST;
			else if (_command_string == const_head)		// HEAD
				m_req_method = REQUEST_HEAD;
			else if (_command_string == const_put)		// PUT
				m_req_method = REQUEST_PUT;
			else if (_command_string == const_delete)	// DELETE
				m_req_method = REQUEST_DELETE;
			else if (_command_string == const_options)	// OPTIONS
				m_req_method = REQUEST_OPTIONS;
			else if (_command_string == const_trace)	// TRACE
				m_req_method = REQUEST_TRACE;
			else if (_command_string == const_connect)	// CONNECT
				m_req_method = REQUEST_CONNECT;
			else										// CUSTOM (extended)
			{
				m_req_method = REQUEST_CUSTOM;
				m_custom_method = _command_string;
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
