/**
@file Response.cpp
@brief Implementation of HTTP::Response class
*/
#include "Http/Response.h"

namespace oonet
{
	namespace HTTP
	{
		Response::Response(void):
			Packet(),
			ErrorCode("200"),
			ErrorMsg("OK")
		{
		}

		Response::~Response(void)
		{
		}

		// Copy constructor
		Response::Response(const Response &r):
			Packet(r),
			ErrorCode(r.ErrorCode),
			ErrorMsg(r.ErrorMsg)
		{
		}

		// Copy operator
		Response & Response::operator=(const Response & r)
		{	Packet::operator =(r);
			ErrorCode = r.ErrorCode;
			ErrorMsg = r.ErrorMsg;
			return *this;
		}

		// Render a packet from data
		BinaryData Response::render(const string & new_line)
		{
			// Prepare Title
			_Title = "HTTP/1.1 ";
			_Title += ErrorCode + " " + ErrorMsg;

			// Return rendered packet
			return Packet::render(new_line);
		}

		// Parse data and save to packet
		size_t Response::parse(const BinaryData & data)
		{	size_t BlockSize;
			size_t httpversionend_pos, errorcodeend_pos;
			string _httpversion_str;

			// Parse basic packet
			BlockSize = Packet::parse(data);

			// Get version of HTTP
			if ((httpversionend_pos = _Title.find(' ')) == string::npos)
				OONET_THROW_EXCEPTION(ExceptionWrongFormat,
					"Wrong formated header!");
			_httpversion_str = _Title.substr(0, httpversionend_pos);
			if ((_httpversion_str != "HTTP/1.0") && (_httpversion_str != "HTTP/1.1"))
				OONET_THROW_EXCEPTION(ExceptionWrongFormat,
					"Unknown version of HTTP packet!");

			// Get error code
			httpversionend_pos++;
			errorcodeend_pos = _Title.find(' ', httpversionend_pos);
			if ((ErrorCode = _Title.substr(httpversionend_pos, errorcodeend_pos - httpversionend_pos)) == "")
				OONET_THROW_EXCEPTION(ExceptionWrongFormat,
					"HTTP Response without error code!");

			// Get error message
			if (errorcodeend_pos == string::npos)
			{
				ErrorMsg = "";
			}
			else
			{
				errorcodeend_pos ++;
				ErrorMsg = _Title.substr(errorcodeend_pos);
			}


			// Return packet
			return BlockSize;
		}
	};	// !HTTP namespace
};	// !oonet namespace
