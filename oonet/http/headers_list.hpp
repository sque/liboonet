#ifndef OONET_HTTP_HEADERS_HPP_INCLUDED
#define OONET_HTTP_HEADERS_HPP_INCLUDED

#include "../oonet.hpp"
#include "../binary_data.hpp"
#include "./http_utils.hpp"

#include <utility>
#include <map>

namespace oonet
{
	namespace http
	{
		//! Exception raised when the parsed item is not in proper format.
		OONET_DECLARE_EXCEPTION(ExceptionWrongFormat);

		//! Class for managing HTTP headers.
		/**
			It can parse a sting of headers and create an std::map<string, string>
			with all headers, but it can also create a raw string in HTTP format
			from an std::map<string, string>
		*/
		class headers_list
		{
		public:
			//! The header's map type definition
            typedef std::multimap<string, string> set_type;
            
			// Type defs
			typedef set_type::iterator iterator;
			typedef set_type::const_iterator const_iterator;
            typedef set_type::value_type value_type;
            typedef set_type::reference reference;
            typedef set_type::const_reference const_reference;

		private:
			//! Headers map
			set_type fields_set;

		public:
			inline headers_list(){}

			//! Copy constructor
			inline headers_list(const headers_list &r)
                :fields_set(r.fields_set) {}

			//! Destructor
			inline ~headers_list(void){}

			//! Copy operator
			inline headers_list & operator=(const headers_list & r)
            {   fields_set = r.fields_set; return *this;    }

			inline iterator find(const string & _field_name)
            {   return fields_set.find(_field_name);    }

			inline const_iterator find(const string & _field_name) const
            {   return fields_set.find(_field_name);    }
            
			/* STL COMPATIBLE INTERAFACE */
			inline void insert(const value_type & _field)
			{	fields_set.insert(_field);		}

			inline void insert(const string & _field_name, const string & _field_value)
			{	fields_set.insert(value_type(_field_name, _field_value));	}

			inline bool find_first(const string & _field_name, string & _field_value) const
            {	const_iterator it;

                if ((it = find(_field_name)) != end())
                {   _field_value = it->second; return true;  }
                return false;
            }

			bool find_first_integer(const string & _field_name, long & _field_value_int) const;

			inline void erase(iterator _it)
			{	if (_it != end()) fields_set.erase(_it);	}

			inline size_t erase_all_by_name(const string & _field_name)
            {   return fields_set.erase(_field_name);   }

			inline size_t size() const
			{	return fields_set.size();	}

			inline void clear()
			{	fields_set.clear();	}

			inline iterator begin()
			{	return fields_set.begin();	}

			inline const_iterator begin() const
			{	return fields_set.begin();	}

			inline iterator end()
			{	return fields_set.end();	}

			inline const_iterator end() const
			{	return fields_set.end();	}

			//! Render headers in HTTP Format
			/**
				It will create a string with headers as they must
				appear in HTTP traffic.
			@param nl_delimiter The new line sequence to use for indicating new line
			@remarks The output string will not have a leading or trailing new line.
			*/
			binary_data render(const constants::static_constant & nl_delimiter = constants::crlf);

			//! Parse headers from HTTP format
			/**
				It will parse the chunk of HTTP traffic that has
				the headers and populate the internal list with
				headers' names and values.
			@param data The string with headers, which must not have any leading or
				trailing new line.
			@return The position that headers ended
			@throw ExceptionWrongFormat If the supplied string is not a valid HTTP
				formatted headers.
			*/
			size_t parse(const binary_data & _data);
		}; // !Headers class
	};	// !http namespace
};	// !oonet namespace

#endif // !OONET_HTTP_HEADERS_HPP_INCLUDED
