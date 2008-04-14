#ifndef OONET_HTTP_HEADERS_HPP_INCLUDED
#define OONET_HTTP_HEADERS_HPP_INCLUDED

#include "../oonet.hpp"
#include "../binary_data.hpp"

#include <utility>
#include <list>

namespace oonet
{
	namespace http
	{
		//! Exception raised when the parsed item is not in proper format.
		OONET_DECLARE_EXCEPTION(ExceptionWrongFormat);

		// Constant values
		const extern binary_data const_crlfcrlf;	//!< Constant CRLF CRLF
		const extern binary_data const_crlf;		//!< Constant CRLF
		const extern binary_data const_lflf;		//!< Constant LF LF
		const extern binary_data const_lf;			//!< Constant LF
		const extern binary_data const_space;		//!< Space constant
		const extern binary_data const_colon;		//!< Colon character constant

		//! Smart find of new line, can work with LF and CRLF
		/**
			Searches in a text for the first occurance of a new line character.
			It works with LF and CRLF new lines. When new line is found, it returns
			the offset where is found or std::string::npos if not found.
		@param str [IN] The string to search for first occurance of new line.
		@param nl_str [OUT] It saves the type of new line character that was found. If
			nothing is found then the value of nl_str is undefined.
		@return The offset where new line character was found
		*/
		size_t _smart_find_new_line(const binary_data & dt_in, binary_data & nl_delimiter, size_t offset = 0);

		//! Class for managing HTTP headers.
		/**
			It can parse a sting of headers and create an std::map<string, string>
			with all headers, but it can also create a raw string in HTTP format
			from an std::map<string, string>
		*/
		class headers_list
		{
		public:
			//! Field type
			typedef std::pair<string, string> field_type;

			//! The header's map type definition
			typedef std::list<field_type> fields_set_type;

			// Iterators
			typedef fields_set_type::iterator iterator;
			typedef fields_set_type::const_iterator const_iterator;

			// References
			typedef field_type & reference;
			typedef const field_type & const_reference;
		private:
			//! Headers map
			fields_set_type fields_set;

			//! Trim a string from whitespaces at the begining
			string _trim_front(const string & r);

			//! Trim  a string from whitespaces at the end
			string _trim_back(const string & r);

		public:
			//! Default constructor
			/**
				Creates an empty list of headers
			*/
			headers_list(void);

			//! Copy constructor
			headers_list(const headers_list &r);

			//! Destructor
			~headers_list(void);

			//! Copy operator
			headers_list & operator=(const headers_list & r);


			/* STL COMPATIBLE INTERAFACE */
			inline void add(const field_type & _field)
			{	OONET_ASSERT(!_field.first.empty());
				fields_set.push_back(_field);
			}

			inline void add(const string & _field_name, const string & _field_value)
			{	add(field_type(_field_name, _field_value));	}


			iterator find(const string & _field_name);

			const_iterator find(const string & _field_name) const;

			bool find_first(const string & _field_name, string & _field_value) const;

			bool find_first_integer(const string & _field_name, long & _field_value_int) const;

			inline void erase(iterator _it)
			{	if (_it != end()) fields_set.erase(_it);	}

			size_t erase_all_by_name(const string & _field_name);

			size_t size() const
			{	return fields_set.size();	}

			void clear()
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
			binary_data render(const binary_data & nl_delimiter = const_crlf);

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
			size_t parse(const binary_data & dt_in);
		}; // !Headers class
	};	// !http namespace
};	// !oonet namespace

#endif // !OONET_HTTP_HEADERS_HPP_INCLUDED
