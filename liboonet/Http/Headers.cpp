/**
@file Headers.cpp
@brief Implementation of http::Headers class
*/
#include "Http/Headers.h"

namespace oonet
{
	namespace http
	{
		// Static constants
		const string LF = "\n";
		const string CRLF = "\r\n";

		// Smart find of new line, can work with LF and CRLF
		size_t _find_smart_new_line(const string & str, string & nl_str)
		{	size_t lf_pos;

			// Find LF
			if ((lf_pos = str.find(LF)) == string::npos)
				return string::npos;	// Nothing found

			// Check if previous letter was CR
			if ((lf_pos > 0) && (str[lf_pos -1] == '\r'))
			{	// Found CRLF
				nl_str = CRLF;
				return lf_pos -1;
			}
			nl_str = LF;
			return lf_pos;
		}

		// Constructor
		Headers::Headers(void)
		{}

		// Copy constructor
		Headers::Headers(const Headers &r)
		{	map_headers = r.map_headers;	}

		// Destructor
		Headers::~Headers(void)
		{}

		// Copy operator
		Headers & Headers::operator=(const Headers & r)
		{
			map_headers = r.map_headers;
			return *this;
		}

		// Add a new header
		void Headers::setHeader(const string & name, const string &value)
		{	OONET_ASSERT(name != "");
			map_headers[name] = value;
		}

		// Remove a header
		void Headers::removeHeader(const string & name)
		{	HeadersMapIterator It;

			It = map_headers.find(name);
			if (It == map_headers.end())
				OONET_THROW_EXCEPTION(ExceptionNotFound, "Cannot remove a header that doesnot exist!");
			// Erase it finally
			map_headers.erase(It);
		}

		// Get value of header
		const string & Headers::getHeader(const string & name) const
		{	HeadersMap::const_iterator It;

			It = map_headers.find(name);
			if (It == map_headers.end())
				OONET_THROW_EXCEPTION(ExceptionNotFound, "Header doesn't exist!");

			return It->second;
		}

		// Get a copy of STL map containing headers
		const Headers::HeadersMap & Headers::getSTLMap() const
		{	return map_headers;		}

		// Check if a header exists
		bool Headers::headerExists(const string & name)
		{	if(map_headers.find(name) == map_headers.end())
				return false;
			return true;
		}

		// Render headers in HTTP Format
		string Headers::render(const string & new_line)
		{	HeadersMapIterator It;
			string FormatedHeaders;
			bool isFirst = true;

			// Loop around all headers
			for(It = map_headers.begin();It != map_headers.end(); It++)
			{
				if (!isFirst)
					FormatedHeaders += new_line;
				else
					isFirst = false;

				FormatedHeaders += It->first + ": " + It->second;
			}

			return FormatedHeaders;
		}

		// Parse headers
		void Headers::parse(const string & data)
		{	string Name, Value, StrData, StrLine, nl_str;
			size_t nl_pos;	// Position of new line
			size_t sep_pos;	// Value/Name separator

			// Initialize data
			StrData = data;

			// Delete old values
			map_headers.clear();

			while(!StrData.empty())
			{
				// Get a line from headers
				if ((nl_pos = _find_smart_new_line(StrData, nl_str)) != string::npos)
				{
					StrLine = StrData.substr(0, nl_pos);
					StrData = StrData.substr(nl_pos + nl_str.size());
				}
				else
				{
					StrLine = StrData;
					StrData.clear();
				}

				// Parse line
				if ((sep_pos = StrLine.find(":")) == string::npos)
					OONET_THROW_EXCEPTION(ExceptionWrongFormat, "Wrong formated http::Headers!");

				Name = _trim_back(StrLine.substr(0, sep_pos));
				Value = _trim_front(StrLine.substr(sep_pos+1));
				map_headers[Name] = Value;
			}
		}

		// Trim front
		string Headers::_trim_front(const string & r)
		{	size_t cpos;
			for(cpos = 0;cpos != r.size();cpos ++)
				if (r[cpos] != ' ')
					break;
			return string(r, cpos);
		}

		// Trim front from whitespaces
		string Headers::_trim_back(const string & r)
		{   size_t len;
			for(len = r.size();len != 0;len--)
				if (r[len - 1] != ' ')
					break;

			return string(r, 0, len);
		}
	};	// !http namespace
};	// !oonet namespace
