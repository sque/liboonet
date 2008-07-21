/**
@file headers_list.cpp
@brief Implementation of http::headers_list class
*/
#include "./headers_list.hpp"
#include "./http_utils.hpp"

namespace oonet
{
	namespace http
	{
		bool headers_list::find_first_integer(const string & _field_name, long & _field_value_int) const
		{	string _field_value;

			if (find_first(_field_name, _field_value))
			{	_field_value_int = atol(_field_value.c_str());
				return true;
			}

			return false;
		}

		// Render headers in HTTP Format
		binary_data headers_list::render(const constants::static_constant & nl_delimiter)
		{	const_iterator it;
			binary_data _formated_field;
			bool is_first = true;

			// Loop around all headers
			for(it = fields_set.begin();it != fields_set.end(); it++)
			{
				if (!is_first)
					_formated_field += nl_delimiter;
				else
					is_first = false;

				_formated_field += it->first;
				_formated_field += ": ";
				_formated_field += it->second;
			}

			return _formated_field;
		}

		// Parse headers
		size_t headers_list::parse(const binary_data & _data)
		{	binary_data dt_remain;
			string field_name;
			size_t start_dst = 0;		// Current distance from the start of block
			size_t off_endline;		// Position at end of line
			size_t off_colon;			// Value/Name separator
            size_t newline_size;        // New line size

			// In case of empty we return not found
			if (_data.empty())
				return binary_data::npos;

			// Initialize data
			dt_remain = _data;

			// Delete old values
			fields_set.clear();

			// Loop around lines
			while(!dt_remain.empty())
			{
				// Check if we found empty line
				if (dt_remain[0] == '\n')
					return start_dst + 1;
				else if ((dt_remain[0] == '\r') && (dt_remain.size() >= 2) && (dt_remain[1] == '\n'))
					return start_dst + 2;

				// find colon
				if ((off_colon = dt_remain.find(constants::colon_char)) == binary_data::npos)
					if (algorithms::find_new_line(dt_remain, newline_size) == binary_data::npos)
                        return binary_data::npos;
                    else
                        OONET_THROW_EXCEPTION(ExceptionWrongFormat, "Wrong formated http::Headers!");

				// find terminating new line
				if ((off_endline = algorithms::find_new_line(dt_remain, newline_size, off_colon)) == binary_data::npos)
					return binary_data::npos;	// Incomplete data

				// Grab field
				field_name = std::string((char *)dt_remain.c_array(), off_colon);
				fields_set.insert(value_type(field_name, algorithms::trim_left_copy(
                    std::string((char *)(dt_remain.c_array() + off_colon + 1), off_endline - off_colon - 1))));

				start_dst += off_endline + newline_size;
				dt_remain = dt_remain.get_from(off_endline + newline_size);
			}

			return binary_data::npos;	//Incomplete data
		}

	};	// !http namespace
};	// !oonet namespace
