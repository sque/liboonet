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

		const binary_data const_lf = binary_data("\n");
		const binary_data const_crlf = binary_data("\r\n");
		const binary_data const_lflf = const_lf + const_lf;
		const binary_data const_crlfcrlf = const_crlf + const_crlf;
		const binary_data const_space = binary_data(" ");
		const binary_data const_colon = binary_data(":");

		size_t _find_smart_new_line(const binary_data & dt_in, binary_data & nl_delimiter)
		{	size_t nl_pos;

			// Find LF
			if ((nl_pos = dt_in.find(const_lf)) == binary_data::npos)
				return string::npos;	// Nothing found

			// Check if previous letter was CR
			if ((nl_pos > 0) && (dt_in[nl_pos -1] == '\r'))
			{	// Found CRLF
				nl_delimiter = const_crlf;
				return nl_pos -1;
			}
			nl_delimiter = const_lf;
			return nl_pos;
		}

		// Trim front
		binary_data headers_list::_trim_front(const binary_data & r)
		{	size_t cpos;
			for(cpos = 0;cpos != r.size();cpos ++)
				if (r[cpos] != ' ')
					break;
			return r.get_from(cpos);
		}

		// Trim front from whitespaces
		binary_data headers_list::_trim_back(const binary_data & r)
		{   size_t len;
			for(len = r.size();len != 0;len--)
				if (r[len - 1] != ' ')
					break;

			return r.get_until(len);
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
		void headers_list::set(const binary_data & field_name, const binary_data &field_value)
		{	OONET_ASSERT(field_name != binary_data::nothing);
			headers_map[field_name] = field_value;
		}

		// Remove a header
		void headers_list::erase(const binary_data & field_name)
		{	headers_map_type::iterator It;

			It = headers_map.find(field_name);
			if (It == headers_map.end())
				OONET_THROW_EXCEPTION(ExceptionNotFound, "Cannot remove a header that doesnot exist!");

			// Erase it finally
			headers_map.erase(It);
		}

		// Get value of header
		const binary_data & headers_list::get(const binary_data & field_name) const throw(ExceptionNotFound)
		{	headers_map_type::const_iterator It;

			It = headers_map.find(field_name);
			if (It == headers_map.end())
				OONET_THROW_EXCEPTION(ExceptionNotFound, "Header doesn't exist!");

			return It->second;
		}

		// Check if a header exists
		bool headers_list::exist(const binary_data & name)
		{	if(headers_map.find(name) == headers_map.end())
				return false;
			return true;
		}

		// Render headers in HTTP Format
		binary_data headers_list::render(const binary_data & new_line)
		{	headers_map_type::iterator it;
			binary_data _formated_field;
			bool isFirst = true;

			// Loop around all headers
			for(it = headers_map.begin();it != headers_map.end(); it++)
			{
				if (!isFirst)
					_formated_field += new_line;
				else
					isFirst = false;

				_formated_field += it->first;
				_formated_field += const_colon;
				_formated_field += const_space;
				_formated_field += it->second;
			}

			return _formated_field;
		}

		// Parse headers
		size_t headers_list::parse(const binary_data & dt_in)
		{	binary_data dt_remain, nl_delimiter, field_name, field_value, dt_line;
			size_t start_dst = 0;	// Current distance from the start of block
			size_t nl_pos;			// Position of new line
			size_t sep_pos;			// Value/Name separator

			// In case of empty we return not found
			if (dt_in.empty())
				return binary_data::npos;

			// Initialize data
			dt_remain = dt_in;

			// Delete old values
			headers_map.clear();

			while(!dt_remain.empty())
			{
				// Get a line from headers
				if ((nl_pos = _find_smart_new_line(dt_remain, nl_delimiter)) != binary_data::npos)
				{	start_dst += nl_pos + nl_delimiter.size();
					dt_line = dt_remain.get_until(nl_pos);

					// Check for empty line
					if (dt_line.empty())
						return start_dst;

					// Remaining data for parsing
					dt_remain = dt_remain.get_from(nl_pos + nl_delimiter.size());
				}
				else
					return binary_data::npos;	//Incomplete data

				// Parse line
				if ((sep_pos = dt_line.find(const_colon)) == binary_data::npos)
					OONET_THROW_EXCEPTION(ExceptionWrongFormat, "Wrong formated http::Headers!");

				field_name = _trim_back(dt_line.get_until(sep_pos));
				field_value = _trim_front(dt_line.get_from(sep_pos+1));
				headers_map[field_name] = field_value;
			}

			return binary_data::npos;	//Incomplete data
		}

	};	// !http namespace
};	// !oonet namespace
