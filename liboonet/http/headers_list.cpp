/**
@file Headers.cpp
@brief Implementation of http::Headers class
*/
#include "./headers_list.hpp"

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
		headers_list::headers_list(void)
		{}

		// Destructor
		headers_list::~headers_list(void)
		{}

		// Copy constructor
		headers_list::headers_list(const headers_list &r)
		{	headers_map = r.headers_map;	}

		// Copy operator
		headers_list & headers_list::operator=(const headers_list & r)
		{
			headers_map = r.headers_map;
			return *this;
		}

		// Add a new header
		void headers_list::set(const string & name, const string &value)
		{	OONET_ASSERT(name != "");
			headers_map[name] = value;
		}

		// Remove a header
		void headers_list::erase(const string & name)
		{	headers_map_type::iterator It;

			It = headers_map.find(name);
			if (It == headers_map.end())
				OONET_THROW_EXCEPTION(ExceptionNotFound, "Cannot remove a header that doesnot exist!");

			// Erase it finally
			headers_map.erase(It);
		}

		// Get value of header
		const string & headers_list::get(const string & name) const throw(ExceptionNotFound)
		{	headers_map_type::const_iterator It;

			It = headers_map.find(name);
			if (It == headers_map.end())
				OONET_THROW_EXCEPTION(ExceptionNotFound, "Header doesn't exist!");

			return It->second;
		}

		// Check if a header exists
		bool headers_list::exist(const string & name)
		{	if(headers_map.find(name) == headers_map.end())
				return false;
			return true;
		}

		// Render headers in HTTP Format
		string headers_list::render(const string & new_line)
		{	headers_map_type::iterator it;
			string _formated_field;
			bool isFirst = true;

			// Loop around all headers
			for(it = headers_map.begin();it != headers_map.end(); it++)
			{
				if (!isFirst)
					_formated_field += new_line;
				else
					isFirst = false;

				_formated_field += it->first + ": " + it->second;
			}

			return _formated_field;
		}

		// Parse headers
		void headers_list::parse(const string & data)
		{	string Name, Value, StrData, StrLine, nl_str;
			size_t nl_pos;	// Position of new line
			size_t sep_pos;	// Value/Name separator

			// Initialize data
			StrData = data;

			// Delete old values
			headers_map.clear();

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
				headers_map[Name] = Value;
			}
		}

		// Trim front
		string headers_list::_trim_front(const string & r)
		{	size_t cpos;
			for(cpos = 0;cpos != r.size();cpos ++)
				if (r[cpos] != ' ')
					break;
			return string(r, cpos);
		}

		// Trim front from whitespaces
		string headers_list::_trim_back(const string & r)
		{   size_t len;
			for(len = r.size();len != 0;len--)
				if (r[len - 1] != ' ')
					break;

			return string(r, 0, len);
		}
	};	// !http namespace
};	// !oonet namespace
