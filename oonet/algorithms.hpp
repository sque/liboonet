#ifndef OONET_ALGORITHMS_INCLUDED
#define OONET_ALGORITHMS_INCLUDED

#include "./oonet.hpp"
#include "./binary_data.hpp"

namespace oonet
{
    //! The namespace that all oonet algorithms reside
    namespace algorithms
    {
        //! Remove preceding white space
        inline std::string trim_left_copy(const std::string & _str, const char & _white_char = ' ')
        {   size_t cit;
            if ((cit = _str.find_first_not_of(_white_char)) == std::string::npos)
                return std::string();
            return _str.substr(cit);
        }
        
        //! Remove trailing white space
        inline std::string trim_right_copy(const std::string & _str, const char & _white_char = ' ')
        {   size_t cit;
            if ((cit = _str.find_last_not_of(_white_char)) == std::string::npos)
                return _str;
            return _str.substr(0, cit);
        }

        //! Remove preceding and trailing white space
        inline std::string trim_copy(const std::string & _str, const char & _white_char = ' ')
        {   size_t off_end, off_start;
            if ((off_start = _str.find_first_not_of(_white_char)) == std::string::npos)
                return _str.substr(off_start);
            if ((off_end = _str.find_last_not_of(_white_char)) == std::string::npos)
                return _str;
            return _str.substr(off_start, off_end - off_start);
        }
    };
};
#endif

