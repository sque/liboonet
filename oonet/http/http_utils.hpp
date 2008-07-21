#ifndef OONET_HTTP_UTILS_INCLUDED
#define OONET_HTTP_UTILS_INCLUDED

#include "../oonet.hpp"
#include "../binary_data.hpp"
#include "../algorithms.hpp"

namespace oonet
{
    namespace http
    {
        // Constants
        namespace constants
        {
            // Type definition of static constants
            struct static_constant
            {   binary_data as_binary_data;
                std::string as_string;
                cmem_ref as_cmem_ref;
                
                static_constant(const char * _str)
                    :as_binary_data(cmem_ref(_str)),
                    as_string(_str),
                    as_cmem_ref(as_string)
                {}
            
            private:
                // Uncopyable
                static_constant(const static_constant & r);
                static_constant & operator=(const static_constant & r);
            };
            
            inline std::string & operator+=(std::string & _str, const static_constant & r)
            {   return _str += r.as_string;     }
            inline binary_data & operator+=(binary_data & _data, const static_constant & r)
            {   return _data += r.as_binary_data;     }
            
            const extern static_constant crlf;
            const extern static_constant lf;
            const extern static_constant crlfcrlf;
            const extern static_constant lflf;
            const extern static_constant http_ver1_1;
            const extern static_constant http_ver1_0;
            const extern static_constant content_length;
            const char space_char = ' ';
            const char colon_char = ':';
        }   // ! constants
        
   
    }   // ! http
    
    namespace algorithms
    {
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
        inline size_t find_new_line(const binary_data & _data, size_t & _delimiter_size, size_t offset = 0)
		{	size_t nl_pos;  // Position of new line

			// Find LF
			if ((nl_pos = _data.find(http::constants::lf.as_binary_data, offset)) == binary_data::npos)
				return string::npos;	// Nothing found

			// Check if previous letter was CR
			if ((nl_pos > 0) && (_data[nl_pos -1] == '\r'))
			{	// Found CRLF
				_delimiter_size = 2;
				return nl_pos -1;
			}
			_delimiter_size = 1;
			return nl_pos;
		}
    }
}   // ! oonet
#endif