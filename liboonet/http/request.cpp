/**
@file Request.cpp
@brief Implementation of http::Request class
*/
#include "./request.hpp"

namespace oonet
{
	namespace http
	{
		Request::Request(void)
		{
			// Default options
			http_type = REQUEST_GET;
			url = "/";
		}

		Request::~Request(void)
		{
		}

		// Copy constructor
		Request::Request(const Request & r):
			packet(r)
		{
			// Copy data
			url = r.url;
			http_type = r.http_type;
		}

		// Copy Operator
		Request & Request::operator=(const Request & r)
		{
			// Copy parent
			packet::operator =(r);

			// Copy custom data
			url = r.url;
			http_type = r.http_type;
			return *this;
		}

		// Render packet
		binary_data Request::render(const string & new_line)
		{
			// Make up title
			if (http_type == REQUEST_GET)
			{
				m_title = "GET ";
				b_has_body = false;
			}
			else if (http_type == REQUEST_POST)
			{
				m_title = "POST ";
				b_has_body = true;
			}
			m_title += (string)url + " HTTP/1.1";

			// Render the packet
			return packet::render(new_line);
		}

		// Parse packet
		bool Request::parse(const binary_data & dt_in, binary_data * dt_remain)
		{	size_t commandend_pos, urlend_pos;
			string _command_string, _version_string;

			// Parse packet
			if(!packet::parse(dt_in, dt_remain))
				return false;

			// Get Command
			if ((commandend_pos = m_title.find(' '))== string::npos)
				OONET_THROW_EXCEPTION(ExceptionWrongFormat,
					"This is not an http request packet");
			_command_string = m_title.substr(0, commandend_pos);
			if (_command_string == "GET")
				http_type = REQUEST_GET;
			else if (_command_string == "POST")
				http_type = REQUEST_POST;
			else
			{
				http_type = REQUEST_UNKNOWN;
				OONET_THROW_EXCEPTION(ExceptionUnimplemented,
					"This http request is not implemented!");
			}

			// Get URL
			commandend_pos ++;	// Start one position lower
			if ((urlend_pos =  m_title.find(' ', commandend_pos))== string::npos)
				OONET_THROW_EXCEPTION(ExceptionWrongFormat,
					"This is not an http request packet");
			url = title().substr(commandend_pos, urlend_pos - commandend_pos);
			if ((string)url == "")
				OONET_THROW_EXCEPTION(ExceptionWrongFormat,
					"This is not an http request packet");

			// Get version
			urlend_pos ++;
			_version_string = m_title.substr(urlend_pos);
			if ((_version_string != "HTTP/1.1") && (_version_string != "HTTP/1.0"))
				OONET_THROW_EXCEPTION(ExceptionWrongFormat,
					"This is not an http request packet");
			return true;
		}
	};	// !http namespace
};	// !oonet namespace
