#include "./http_utils.hpp"

namespace oonet
{
    namespace http
    {
        namespace constants
        {
            const static_constant crlf("\r\n");
            const static_constant lf("\n");
            const static_constant crlfcrlf("\r\n");
            const static_constant lflf("\n\n");
            const static_constant http_ver1_1("HTTP/1.1");
            const static_constant http_ver1_0("HTTP/1.0");
            const static_constant content_length("Content-Length");
        }   // !constants
    }   // !http
}   // !oonet