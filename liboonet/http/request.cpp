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
			http_type = REQUEST_GET;
			url = "/";
		}

		request::~request(void)
		{
		}

		// Copy constructor
		request::request(const request & r):
			packet(r)
		{
			// Copy data
			url = r.url;
			http_type = r.http_type;
		}

		// Copy Operator
		request & request::operator=(const request & r)
		{
			// Copy parent
			packet::operator =(r);

			// Copy custom data
			url = r.url;
			http_type = r.http_type;
			return *this;
		}

		// Render packet
		binary_data request::render(const binary_data & nl_delimiter)
		{
			// Make up title
			if (http_type == REQUEST_GET)
			{
				m_title = const_get;
				m_title += const_space;
				b_has_body = false;
			}
			else if (http_type == REQUEST_POST)
			{
				m_title = const_post;
				m_title += const_space;
				b_has_body = true;
			}
			m_title += binary_data((string)url);
			m_title += const_space;
			m_title += const_http_ver1_1;

			// Render the packet
			return packet::render(nl_delimiter);
		}

		// Parse packet
		bool request::parse(const binary_data & dt_in, binary_data * dt_remain)
		{	size_t commandend_pos, urlend_pos;
			binary_data _command_string, _version_string;

			// Parse packet
			if(!packet::parse(dt_in, dt_remain))
				return false;

			// Get Command
			if ((commandend_pos = m_title.find(const_space))== binary_data::npos)
				OONET_THROW_EXCEPTION(ExceptionWrongFormat,
					"This is not an http request packet");
			_command_string = m_title.sub_data(0, commandend_pos);
			if (_command_string == const_get)
				http_type = REQUEST_GET;
			else if (_command_string == const_post)
				http_type = REQUEST_POST;
			else
			{
				http_type = REQUEST_UNKNOWN;
				OONET_THROW_EXCEPTION(ExceptionUnimplemented,
					"This http request is not implemented!");
			}

			// Get URL
			commandend_pos ++;	// Start one position lower
			if ((urlend_pos =  m_title.find(const_space, commandend_pos)) == binary_data::npos)
				OONET_THROW_EXCEPTION(ExceptionWrongFormat,
					"This is not an http request packet");
			url = title().sub_data(commandend_pos, urlend_pos - commandend_pos).to_string();
			if ((string)url == "")
				OONET_THROW_EXCEPTION(ExceptionWrongFormat,
					"This is not an http request packet");

			// Get version
			urlend_pos ++;
			_version_string = m_title.get_from(urlend_pos);
			if ((_version_string != const_http_ver1_1) && (_version_string != const_http_ver1_0))
				OONET_THROW_EXCEPTION(ExceptionWrongFormat,
					"This is not an http request packet");
			return true;
		}
	};	// !http namespace
};	// !oonet namespace
