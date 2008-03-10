#ifndef OONET_HTTP_HEADERS_H_DEFINED
#define OONET_HTTP_HEADERS_H_DEFINED

#include <map>
#include "../config.h"
#include "../platform.h"
#include "../BinaryData.h"
#include "../Exception.h"

using std::map;

namespace OONet
{
	namespace HTTP
	{
		//! Exception raised when the parsed item is not in proper format.
		OONET_DECLARE_EXCEPTION(ExceptionWrongFormat);

		// Constant values
		const extern string LF;		//!< Constant string of LineFeed
		const extern string CRLF;	//!< Constant string CariageReturn-LineFeed

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
		size_t _find_smart_new_line(const string & str, string & nl_str);

		//! Class for managing HTTP headers.
		/**
			It can parse a sting of headers and create an std::map<string, string>
			with all headers, but it can also create a raw string in HTTP format
			from an std::map<string, string>
		*/
		class Headers
		{
		public:
			//! The header's map type definition
			typedef std::map<string, string> HeadersMap;

			//! The header's map iterator
			typedef HeadersMap::iterator HeadersMapIterator;

		private:
			//! Headers map
			HeadersMap map_headers;

			//! Trim a string from whitespaces at the begining
			string _trim_front(const string & r);

			//! Trim  a string from whitespaces at the end
			string _trim_back(const string & r);

		public:
			//! Default constructor
			/**
				Creates an empty list of headers
			*/
			Headers(void);

			//! Copy constructor
			Headers(const Headers &r);

			//! Destructor
			~Headers(void);

			//! Copy operator
			Headers & operator=(const Headers & r);

			//! Add or set a header
			/**
				If there is already a header with this name, then its value
				is altered with new one, else the header is added.
			*/
			void setHeader(const string & name,const string & value);

			//! Remove a header
			/**
				It will remove a header from the list.
			@throw ExceptionNotFound If the header is not in the list
			*/
			void removeHeader(const string & name);

			//! Check if a header exists
			bool headerExists(const string & name);

			//! Get value of header
			/**
				It will try to retrieve headers value.
			@param name The name of the header that we want to get value.
			@throw ExceptionNotFound If the header does not exist in the list.
			*/
			const string & getHeader(const string & name) const;

			//! Get a copy of STL map containing headers.
			/**
				Get the std::map<string, string> of headers.
			*/
			const HeadersMap & getSTLMap() const;

			//! Render headers in HTTP Format
			/**
				It will create a string with headers as they must
				appear in HTTP traffic.
			@param new_line The string to use for indicating new line
			@remarks The output string will not have a leading or trailing new line.
			*/
			string render(const string & new_line = DEFAULT_HTTP_NEWLINE);

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
			void parse(const string & data);
		}; // !Headers class
	};	// !HTTP namespace
};	// !OONet namespace

#endif // !OONET_HTTP_HEADERS_H_DEFINED
