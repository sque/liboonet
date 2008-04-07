#ifndef OONET_HTTP_HEADERS_H_DEFINED
#define OONET_HTTP_HEADERS_H_DEFINED

#include "../oonet.hpp"
#include "../binary_data.hpp"

#include <map>

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
		size_t _find_smart_new_line(const binary_data & dt_in, binary_data & nl_delimiter);

		//! Class for managing HTTP headers.
		/**
			It can parse a sting of headers and create an std::map<string, string>
			with all headers, but it can also create a raw string in HTTP format
			from an std::map<string, string>
		*/
		class headers_list
		{
		private:
			//! The header's map type definition
			typedef std::map<binary_data, binary_data> headers_map_type;

			//! Headers map
			headers_map_type headers_map;

			//! Trim a string from whitespaces at the begining
			binary_data _trim_front(const binary_data & r);

			//! Trim  a string from whitespaces at the end
			binary_data _trim_back(const binary_data & r);

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

			//! Add or set a header
			/**
				If there is already a header with this name, then its value
				is altered with new one, else the header is added.
			*/
			void set(const binary_data & field_name,const binary_data & field_value);

			inline void set(const string & field_name,const string & field_value)
			{	set(binary_data(field_name), binary_data(field_value));	}

			//! Get value of header
			/**
				It will try to retrieve headers value.
			@param name The name of the header that we want to get value.
			@throw ExceptionNotFound If the header does not exist in the list.
			*/
			const binary_data & get(const binary_data & field_name) const throw(ExceptionNotFound);

			inline const string get(const string & field_name) const throw(ExceptionNotFound)
			{	return get(binary_data(field_name)).to_string();	}

			//! Count fields
			size_t size() const
			{	return headers_map.size();	}

			//! Remove a header
			/**
				It will remove a header from the list.
			@throw ExceptionNotFound If the header is not in the list
			*/
			void erase(const binary_data & field_name);

			inline void erase(const string & field_name)
			{	erase(binary_data(field_name));	}

			//! Check if a header exists
			bool exist(const binary_data & name);

			//! Render headers in HTTP Format
			/**
				It will create a string with headers as they must
				appear in HTTP traffic.
			@param new_line The string to use for indicating new line
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
			@throw ExceptionWrongFormat If the supplied string is not a valid HTTP
				formatted headers.
			*/
			void parse(const binary_data & dt_in);
		}; // !Headers class
	};	// !http namespace
};	// !oonet namespace

#endif // !OONET_HTTP_HEADERS_H_DEFINED
