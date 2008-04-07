#include "test_http_response.hpp"
#include "http/response.hpp"

namespace oonet
{
	TestHTTPResponse theTestHTTPResponse;

	bool TestHTTPResponse::TestCtor::OnExecute()
	{	http::response a;

		if (! a.body().empty())
			return false;
		if (a.headers().size() != 0)
			return false;
		if (! a.title().empty())
			return false;
		if (a.error_code() != binary_data("200"))
			return false;
		if (a.error_message() != binary_data("OK"))
			return false;
		return true;
	}

	bool TestHTTPResponse::TestCopyCtor::OnExecute()
	{	http::response a;

		a.body() = binary_data("koukouroukou");
		a.headers().set("a", "123");
		a.title() = "200 OK";
		a.error_code() = "404";
		a.error_message() = "Not Found";

		if (a.body()  != binary_data("koukouroukou"))
			return false;
		if (a.headers().size() != 1)
			return false;
		if (a.headers().get("a") != "123")
			return false;
		if (a.title() != binary_data("200 OK"))
			return false;
		if (a.error_code() != binary_data("404"))
			return false;
		if (a.error_message() != binary_data("Not Found"))
			return false;

		http::response b(a);
		if (b.body()  != binary_data("koukouroukou"))
			return false;
		if (b.headers().size() != 1)
			return false;
		if (b.headers().get("a") != "123")
			return false;
		if (b.title() != binary_data("200 OK"))
			return false;
		if (b.error_code() != binary_data("404"))
			return false;
		if (b.error_message() != binary_data("Not Found"))
			return false;
		return true;
	}
	bool TestHTTPResponse::TestCopyOperator::OnExecute()
	{	http::response a, b;

		a.body() = binary_data("koukouroukou");
		a.headers().set("a", "123");
		a.title() = "200 OK";
		a.error_code() = "404";
		a.error_message() = "Not Found";

		if (a.body()  != binary_data("koukouroukou"))
			return false;
		if (a.headers().size() != 1)
			return false;
		if (a.headers().get("a") != "123")
			return false;
		if (a.title() != binary_data("200 OK"))
			return false;
		if (a.error_code() != binary_data("404"))
			return false;
		if (a.error_message() != binary_data("Not Found"))
			return false;

		b = a;
		if (b.body()  != binary_data("koukouroukou"))
			return false;
		if (b.headers().size() != 1)
			return false;
		if (b.headers().get("a") != "123")
			return false;
		if (b.title() != binary_data("200 OK"))
			return false;
		if (b.error_code() != binary_data("404"))
			return false;
		if (b.error_message() != binary_data("Not Found"))
			return false;
		return true;
	}

	bool TestHTTPResponse::TestRender::OnExecute()
	{	http::response a;
		string shouldbeLF = "HTTP/1.1 202 Created\nContent-Length: 12\na: 123\n\nkoukouroukou";
		string shouldbeCRLF = "HTTP/1.1 202 Created\r\nContent-Length: 12\r\na: 123\r\n\r\nkoukouroukou";
		string out;

		a.body() = binary_data("koukouroukou");
		a.headers().set("a", "123");
		a.error_code() = binary_data("202");
		a.error_message() = binary_data("Created");

		out = a.render(http::const_lf).to_string();
		if (out != shouldbeLF)
			return false;

		out = a.render(http::const_crlf).to_string();
		if (out != shouldbeCRLF)
			return false;

		return true;
	}

	bool TestHTTPResponse::TestRenderSpeed::OnExecute()
	{	http::response a;
		binary_data shouldbeLF = binary_data("HTTP/1.1 202 Created\nContent-Length: 12\na: 123\n\nkoukouroukou");
		binary_data out;

		a.body() = binary_data("koukouroukou");
		a.headers().set("a", "123");
		a.error_code() = binary_data("202");
		a.error_message() = binary_data("Created");

		ResetTimer();
		for(long i = 0;i < 10000;i++)
			out = a.render(http::const_lf);
		if (out != shouldbeLF)
			return false;

		return true;
	}

	bool TestHTTPResponse::TestParse::OnExecute()
	{	http::response a;
		bool b_parsed;
		binary_data trail("1234");
		binary_data remaining;
		binary_data renderedLF = binary_data("HTTP/1.1 202 Created\nContent-Length: 12\na: 123\n\nkoukouroukou") + trail;
		binary_data renderedCRLF = binary_data("HTTP/1.1 202 Created\r\nContent-Length: 12\r\na: 123\r\n\r\nkoukouroukou") + trail;
		binary_data renderedNoCodeCRLF = binary_data("HTTP/1.1 404\r\nContent-Length: 12\r\na: 123\r\n\r\nkoukouroukou") +trail;

		// response LF
		b_parsed = a.parse(renderedLF, &remaining);
		if ((!b_parsed) || (remaining != trail))
			return false;
		if (a.headers().size() != 2)
			return false;
		if (a.headers().get("a") != "123")
			return false;
		if (a.headers().get("Content-Length") != "12")
			return false;
		if (a.title() != binary_data("HTTP/1.1 202 Created"))
			return false;
		if (a.body() != binary_data("koukouroukou"))
			return false;
		if (a.error_code() != binary_data("202"))
			return false;
		if (a.error_message() != binary_data("Created"))
			return false;

		// response CRLF
		b_parsed = a.parse(renderedCRLF, &remaining);
		if ((!b_parsed) || (remaining != trail))
			return false;
		if (a.headers().size() != 2)
			return false;
		if (a.headers().get("a") != "123")
			return false;
		if (a.headers().get("Content-Length") != "12")
			return false;
		if (a.title() != binary_data("HTTP/1.1 202 Created"))
			return false;
		if (a.body() != binary_data("koukouroukou"))
			return false;
		if (a.error_code() != binary_data("202"))
			return false;
		if (a.error_message() != binary_data("Created"))
			return false;

		// response without message CRLF
		b_parsed = a.parse(renderedNoCodeCRLF, &remaining);
		if ((!b_parsed) || (remaining != trail))
			return false;
		if (a.headers().size() != 2)
			return false;
		if (a.headers().get("a") != "123")
			return false;
		if (a.headers().get("Content-Length") != "12")
			return false;
		if (a.title() != binary_data("HTTP/1.1 404"))
			return false;
		if (a.body() != binary_data("koukouroukou"))
			return false;
		if (a.error_code() != binary_data("404"))
			return false;
		if (a.error_message() != binary_data(""))
			return false;
		return true;
	}

	bool TestHTTPResponse::TestParseWrong1::OnExecute()
	{	http::response a;
		a.parse(binary_data("HTTP/1.1\r\nContent-Length: 12\r\na: 123\r\n\r\nkoukouroukou"));
		return false;
	}

	bool TestHTTPResponse::TestParseWrong2::OnExecute()
	{	http::response a;
		a.parse(binary_data("HTTP/1.1  \r\nContent-Length: 12\r\na: 123\r\n\r\nkoukouroukou"));
		return false;
	}

	bool TestHTTPResponse::TestParseSpeed::OnExecute()
	{	http::response a;
		binary_data rendered("HTTP/1.1 202 Created\nContent-Length: 12\na: 123\n\nkoukouroukou");
		bool b_parsed;

		// response LF
		ResetTimer();
		for(long i = 0;i < 10000;i++)
			b_parsed = a.parse(rendered);
		if (!b_parsed)
			return false;
		if (a.headers().size() != 2)
			return false;
		if (a.headers().get("a") != "123")
			return false;
		if (a.headers().get("Content-Length") != "12")
			return false;
		if (a.title() != binary_data("HTTP/1.1 202 Created"))
			return false;
		if (a.body() != binary_data("koukouroukou"))
			return false;
		if (a.error_code() != binary_data("202"))
			return false;
		if (a.error_message() != binary_data("Created"))
			return false;
		return true;
	}
};	// !oonet namespace
