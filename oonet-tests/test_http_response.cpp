#include "test_http_response.hpp"
#include <oonet/http/response.hpp>

namespace oonet
{
	namespace test
	{
		test_http_response test_http_response_inst;

		bool test_http_response::TestCtor::operator()()
		{	http::response a;

			if (! a.body().empty())
				return false;
			if (a.headers().size() != 0)
				return false;
			if (! a.title().empty())
				return false;
			if (a.status_code() != 200)
				return false;
			if (a.reason_phrase() != binary_data("OK"))
				return false;
			return true;
		}

		bool test_http_response::TestCopyCtor::operator()()
		{	http::response a;
			string header_value;

			a.body() = binary_data("koukouroukou");
			a.headers().insert("a", "123");
			a.title() = binary_data("200 OK");
			a.status_code() = 404;
			a.reason_phrase() = binary_data("Not Found");

			if (a.body()  != binary_data("koukouroukou"))
				return false;
			if (a.headers().size() != 1)
				return false;
			if (!(a.headers().find_first("a", header_value) && (header_value == "123")))
				return false;
			if (a.title() != binary_data("200 OK"))
				return false;
			if (a.status_code() != 404)
				return false;
			if (a.reason_phrase() != binary_data("Not Found"))
				return false;

			http::response b(a);
			if (b.body()  != binary_data("koukouroukou"))
				return false;
			if (b.headers().size() != 1)
				return false;
			if (!(a.headers().find_first("a", header_value) && (header_value == "123")))
				return false;
			if (b.title() != binary_data("200 OK"))
				return false;
			if (b.status_code() != 404)
				return false;
			if (b.reason_phrase() != binary_data("Not Found"))
				return false;
			return true;
		}
		bool test_http_response::TestCopyOperator::operator()()
		{	http::response a, b;
			string header_value;

			a.body() = binary_data("koukouroukou");
			a.headers().insert("a", "123");
			a.title() = binary_data("200 OK");
			a.status_code() = 404;
			a.reason_phrase() = binary_data("Not Found");

			if (a.body()  != binary_data("koukouroukou"))
				return false;
			if (a.headers().size() != 1)
				return false;
			if (!(a.headers().find_first("a", header_value) && (header_value == "123")))
				return false;
			if (a.title() != binary_data("200 OK"))
				return false;
			if (a.status_code() != 404)
				return false;
			if (a.reason_phrase() != binary_data("Not Found"))
				return false;

			b = a;
			if (b.body()  != binary_data("koukouroukou"))
				return false;
			if (b.headers().size() != 1)
				return false;
			if (!(a.headers().find_first("a", header_value) && (header_value == "123")))
				return false;
			if (b.title() != binary_data("200 OK"))
				return false;
			if (b.status_code() != 404)
				return false;
			if (b.reason_phrase() != binary_data("Not Found"))
				return false;
			return true;
		}

		bool test_http_response::TestRender::operator()()
		{	http::response a;
			string shouldbeLF = "HTTP/1.1 202 Created\na: 123\nContent-Length: 12\n\nkoukouroukou";
			string shouldbeCRLF = "HTTP/1.1 202 Created\r\na: 123\r\nContent-Length: 12\r\n\r\nkoukouroukou";
			string out;

			a.body() = binary_data("koukouroukou");
			a.headers().insert("a", "123");
			a.status_code() = 202;
			a.reason_phrase() = binary_data("Created");

			out = to_string(a.render(http::constants::lf));
			if (out != shouldbeLF)
				return false;

			out = to_string(a.render(http::constants::crlf));
			if (out != shouldbeCRLF)
				return false;

			return true;
		}

		bool test_http_response::TestRenderSpeed::operator()()
		{	http::response a;
			binary_data shouldbeLF = binary_data("HTTP/1.1 202 Created\na: 123\nContent-Length: 12\n\nkoukouroukou");
			binary_data out;

			a.body() = binary_data("koukouroukou");
			a.headers().insert("a", "123");
			a.status_code() = 202;
			a.reason_phrase() = binary_data("Created");

			reset_timer();
			for(long i = 0;i < 10000;i++)
				out = a.render(http::constants::lf);
			if (out != shouldbeLF)
				return false;

			return true;
		}

		bool test_http_response::TestParse::operator()()
		{	http::response a;
			bool b_parsed;
			binary_data trail("1234");
			binary_data remaining;
			binary_data renderedLF = binary_data("HTTP/1.1 202 Created\nContent-Length: 12\na: 123\n\nkoukouroukou") + trail;
			binary_data renderedCRLF = binary_data("HTTP/1.1 202 Created\r\nContent-Length: 12\r\na: 123\r\n\r\nkoukouroukou") + trail;
			binary_data renderedNoCodeCRLF = binary_data("HTTP/1.1 404\r\nContent-Length: 12\r\na: 123\r\n\r\nkoukouroukou") +trail;
			string header_value;

			// response LF
			b_parsed = a.parse(renderedLF, &remaining);
			if ((!b_parsed) || (remaining != trail))
				return false;
			if (a.headers().size() != 2)
				return false;
			if (!(a.headers().find_first("a", header_value) && (header_value == "123")))
				return false;
			if (!(a.headers().find_first("Content-Length", header_value) && (header_value == "12")))
				return false;
			if (a.title() != binary_data("HTTP/1.1 202 Created"))
				return false;
			if (a.body() != binary_data("koukouroukou"))
				return false;
			if (a.status_code() != 202)
				return false;
			if (a.reason_phrase() != binary_data("Created"))
				return false;

			// response CRLF
			b_parsed = a.parse(renderedCRLF, &remaining);
			if ((!b_parsed) || (remaining != trail))
				return false;
			if (a.headers().size() != 2)
				return false;
			if (!(a.headers().find_first("a", header_value) && (header_value == "123")))
				return false;
			if (!(a.headers().find_first("Content-Length", header_value) && (header_value == "12")))
				return false;
			if (a.title() != binary_data("HTTP/1.1 202 Created"))
				return false;
			if (a.body() != binary_data("koukouroukou"))
				return false;
			if (a.status_code() != 202)
				return false;
			if (a.reason_phrase() != binary_data("Created"))
				return false;

			// response without message CRLF
			b_parsed = a.parse(renderedNoCodeCRLF, &remaining);
			if ((!b_parsed) || (remaining != trail))
				return false;
			if (a.headers().size() != 2)
				return false;
			if (!(a.headers().find_first("a", header_value) && (header_value == "123")))
				return false;
			if (!(a.headers().find_first("Content-Length", header_value) && (header_value == "12")))
				return false;
			if (a.title() != binary_data("HTTP/1.1 404"))
				return false;
			if (a.body() != binary_data("koukouroukou"))
				return false;
			if (a.status_code() != 404)
				return false;
			if (a.reason_phrase() != binary_data(""))
				return false;
			return true;
		}

		bool test_http_response::TestParseWrong1::operator()()
		{	http::response a;
			a.parse(binary_data("HTTP/1.1\r\nContent-Length: 12\r\na: 123\r\n\r\nkoukouroukou"));
			return false;
		}

		bool test_http_response::TestParseWrong2::operator()()
		{	http::response a;
			a.parse(binary_data("HTTP/1.1  \r\nContent-Length: 12\r\na: 123\r\n\r\nkoukouroukou"));
			return false;
		}

		bool test_http_response::TestParseSpeed::operator()()
		{	http::response a;
			binary_data rendered("HTTP/1.1 202 Created\nContent-Length: 12\na: 123\n\nkoukouroukou");
			bool b_parsed;
			string header_value;

			// response LF
			reset_timer();
			for(long i = 0;i < 10000;i++)
				b_parsed = a.parse(rendered);
			if (!b_parsed)
				return false;
			if (a.headers().size() != 2)
				return false;
			if (!(a.headers().find_first("a", header_value) && (header_value == "123")))
				return false;
			if (!(a.headers().find_first("Content-Length", header_value) && (header_value == "12")))
				return false;
			if (a.title() != binary_data("HTTP/1.1 202 Created"))
				return false;
			if (a.body() != binary_data("koukouroukou"))
				return false;
			if (a.status_code() != 202)
				return false;
			if (a.reason_phrase() != binary_data("Created"))
				return false;
			return true;
		}
	};	// !test namespace
};	// !oonet namespace
