/**
@file headers_list.cpp
@brief Implementation of http::headers_list class
*/
#include "./headers_list.hpp"

namespace oonet
{
	namespace http
	{
		// Static constants
		const string LF = "\n";
		const string CRLF = "\r\n";

		const binary_data const_lf = cmem_ref("\n");
		const binary_data const_crlf = cmem_ref("\r\n");
		const binary_data const_lflf = const_lf + const_lf;
		const binary_data const_crlfcrlf = const_crlf + const_crlf;
		const binary_data const_space = cmem_ref(" ");
		const binary_data const_colon = cmem_ref(":");

		size_t _smart_find_new_line(const binary_data & dt_in, binary_data & nl_delimiter, size_t offset)
		{	size_t nl_pos;

			// Find LF
			if ((nl_pos = dt_in.find(const_lf, offset)) == binary_data::npos)
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

		// Remove preceding LWS
		string headers_list::_trim_front(const string & r)
		{	size_t cpos;
			for(cpos = 0;cpos != r.size();cpos ++)
				if (r[cpos] != ' ')
					break;
			return r.substr(cpos);
		}

		// Remove trailing LWS
		string headers_list::_trim_back(const string & r)
		{   size_t len;
			for(len = r.size();len != 0;len--)
				if (r[len - 1] != ' ')
					break;

			return r.substr(0, len);
		}

		// Constructor
		headers_list::headers_list(void)
		{}

		// Destructor
		headers_list::~headers_list(void)
		{}

		// Copy constructor
		headers_list::headers_list(const headers_list &r)
		{	fields_set = r.fields_set;	}

		// Copy operator
		headers_list & headers_list::operator=(const headers_list & r)
		{
			fields_set = r.fields_set;
			return *this;
		}

		headers_list::iterator headers_list::find(const string & _field_name)
		{	iterator it;

			for(it = fields_set.begin();it != fields_set.end(); it++)
				if (it->first == _field_name)
					return it;
			return end();
		}

		headers_list::const_iterator headers_list::find(const string & _field_name) const
		{	const_iterator it;

			for(it = fields_set.begin();it != fields_set.end(); it++)
				if (it->first == _field_name)
					return it;
			return end();
		}

		bool headers_list::find_first(const string & _field_name, string & _field_value) const
		{	const_iterator it;

			if ((it = find(_field_name)) != end())
			{
				_field_value = it->second;
				return true;
			}
			return false;
		}

		bool headers_list::find_first_integer(const string & _field_name, long & _field_value_int) const
		{	string _field_value;

			if (find_first(_field_name, _field_value))
			{	_field_value_int = atol(_field_value.c_str());
				return true;
			}

			return false;
		}

		// Remove a header
		size_t headers_list::erase_all_by_name(const string & _field_name)
		{	iterator it, erase_it;
			size_t count = 0;

			it = fields_set.begin();
			while(it != fields_set.end())
			{
				if (it->first == _field_name)
				{	erase_it = it;
					it++;
					count++;
					fields_set.erase(erase_it);
					continue;
				}
				it ++;
			}

			return count;
		}

		// Render headers in HTTP Format
		binary_data headers_list::render(const binary_data & new_line)
		{	const_iterator it;;
			string _formated_field;
			bool is_first = true;

			// Loop around all headers
			for(it = fields_set.begin();it != fields_set.end(); it++)
			{
				if (!is_first)
					_formated_field += to_string(new_line);
				else
					is_first = false;

				_formated_field += it->first;
				_formated_field += ": ";
				_formated_field += it->second;
			}

			return cmem_ref(_formated_field);
		}

		// Parse headers
		size_t headers_list::parse(const binary_data & dt_in)
		{	binary_data dt_remain, nl_delimiter;
			string field_name;
			size_t start_dst = 0;		// Current distance from the start of block
			size_t end_line_pos;		// Position at end of line
			size_t sep_pos;				// Value/Name separator

			// In case of empty we return not found
			if (dt_in.empty())
				return binary_data::npos;

			// Initialize data
			dt_remain = dt_in;

			// Delete old values
			fields_set.clear();

			// Loop around lines
			while(!dt_remain.empty())
			{
				// Check if we found empty line
				if (dt_remain[0] == '\n')
					return start_dst + 1;
				else if ((dt_remain.size() >= 2) && (dt_remain[0] == '\r') && (dt_remain[1] == '\n'))
					return start_dst + 2;

				// find colon
				if ((sep_pos = dt_remain.find(const_colon)) == binary_data::npos)
					if (_smart_find_new_line(dt_remain, nl_delimiter) != binary_data::npos)
						OONET_THROW_EXCEPTION(ExceptionWrongFormat, "Wrong formated http::Headers!");
					else
						return binary_data::npos;	// Not found

				// find terminating new line
				if ((end_line_pos = _smart_find_new_line(dt_remain, nl_delimiter, sep_pos)) == binary_data::npos)
					return binary_data::npos;	// Incomplete data

				// Grab field
				field_name = to_string(dt_remain.get_until(sep_pos));
				fields_set.push_back(field_type(field_name, _trim_front(to_string(dt_remain.sub_data(sep_pos + 1, end_line_pos - sep_pos - 1)))));

				start_dst += end_line_pos + nl_delimiter.size();
				dt_remain = dt_remain.get_from(end_line_pos + nl_delimiter.size());
			}

			return binary_data::npos;	//Incomplete data
		}

	};	// !http namespace
};	// !oonet namespace
