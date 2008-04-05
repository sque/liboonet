#include "TestHTTPResponse.h"
#include "http/response.hpp"

namespace oonet
{
	TestHTTPResponse theTestHTTPResponse;

	bool TestHTTPResponse::TestCtor::OnExecute()
	{	http::Response a;

		if (! a.body().empty())
			return false;
		if (a.headers().size() != 0)
			return false;
		if (! a.title().empty())
			return false;
		if (a.ErrorCode != "200")
			return false;
		if (a.ErrorMsg != "OK")
			return false;
		return true;
	}

	bool TestHTTPResponse::TestCopyCtor::OnExecute()
	{	http::Response a;

		a.body() = binary_data("koukouroukou");
		a.headers().set("a", "123");
		a.title() = "200 OK";
		a.ErrorCode = "404";
		a.ErrorMsg = "Not Found";

		if (a.body()  != binary_data("koukouroukou"))
			return false;
		if (a.headers().size() != 1)
			return false;
		if (a.headers().get("a") != "123")
			return false;
		if (a.title() != "200 OK")
			return false;
		if (a.ErrorCode != "404")
			return false;
		if (a.ErrorMsg != "Not Found")
			return false;

		http::Response b(a);
		if (b.body()  != binary_data("koukouroukou"))
			return false;
		if (b.headers().size() != 1)
			return false;
		if (b.headers().get("a") != "123")
			return false;
		if (b.title() != "200 OK")
			return false;
		if (b.ErrorCode != "404")
			return false;
		if (b.ErrorMsg != "Not Found")
			return false;
		return true;
	}
	bool TestHTTPResponse::TestCopyOperator::OnExecute()
	{	http::Response a, b;

		a.body() = binary_data("koukouroukou");
		a.headers().set("a", "123");
		a.title() = "200 OK";
		a.ErrorCode = "404";
		a.ErrorMsg = "Not Found";

		if (a.body()  != binary_data("koukouroukou"))
			return false;
		if (a.headers().size() != 1)
			return false;
		if (a.headers().get("a") != "123")
			return false;
		if (a.title() != "200 OK")
			return false;
		if (a.ErrorCode != "404")
			return false;
		if (a.ErrorMsg != "Not Found")
			return false;

		b = a;
		if (b.body()  != binary_data("koukouroukou"))
			return false;
		if (b.headers().size() != 1)
			return false;
		if (b.headers().get("a") != "123")
			return false;
		if (b.title() != "200 OK")
			return false;
		if (b.ErrorCode != "404")
			return false;
		if (b.ErrorMsg != "Not Found")
			return false;
		return true;
	}

	bool TestHTTPResponse::TestRender::OnExecute()
	{	http::Response a;
		string shouldbeLF = "HTTP/1.1 202 Created\nContent-Length: 12\na: 123\n\nkoukouroukou";
		string shouldbeCRLF = "HTTP/1.1 202 Created\r\nContent-Length: 12\r\na: 123\r\n\r\nkoukouroukou";
		string out;

		a.body() = binary_data("koukouroukou");
		a.headers().set("a", "123");
		a.ErrorCode = "202";
		a.ErrorMsg = "Created";

		out = a.render(http::LF).to_string();
		if (out != shouldbeLF)
			return false;

		out = a.render(http::CRLF).to_string();
		if (out != shouldbeCRLF)
			return false;

		return true;
	}

	bool TestHTTPResponse::TestRenderSpeed::OnExecute()
	{	http::Response a;
		string shouldbeLF = "HTTP/1.1 202 Created\nContent-Length: 12\na: 123\n\nkoukouroukou";
		string out;

		a.body() = binary_data("koukouroukou");
		a.headers().set("a", "123");
		a.ErrorCode = "202";
		a.ErrorMsg = "Created";

		ResetTimer();
		for(long i = 0;i < 10000;i++)
			out = a.render(http::LF).to_string();
		if (out != shouldbeLF)
			return false;

		return true;
	}

	bool TestHTTPResponse::TestParse::OnExecute()
	{	http::Response a;
		bool b_parsed;
		binary_data trail("1234");
		binary_data remaining;
		binary_data renderedLF = binary_data("HTTP/1.1 202 Created\nContent-Length: 12\na: 123\n\nkoukouroukou") + trail;
		binary_data renderedCRLF = binary_data("HTTP/1.1 202 Created\r\nContent-Length: 12\r\na: 123\r\n\r\nkoukouroukou") + trail;
		binary_data renderedNoCodeCRLF = binary_data("HTTP/1.1 404\r\nContent-Length: 12\r\na: 123\r\n\r\nkoukouroukou") +trail;

		// Response LF
		b_parsed = a.parse(renderedLF, &remaining);
		if ((!b_parsed) || (remaining != trail))
			return false;
		if (a.headers().size() != 2)
			return false;
		if (a.headers().get("a") != "123")
			return false;
		if (a.headers().get("Content-Length") != "12")
			return false;
		if (a.title() != "HTTP/1.1 202 Created")
			return false;
		if (a.body() != binary_data("koukouroukou"))
			return false;
		if (a.ErrorCode != "202")
			return false;
		if (a.ErrorMsg != "Created")
			return false;

		// Response CRLF
		b_parsed = a.parse(renderedCRLF, &remaining);
		if ((!b_parsed) || (remaining != trail))
			return false;
		if (a.headers().size() != 2)
			return false;
		if (a.headers().get("a") != "123")
			return false;
		if (a.headers().get("Content-Length") != "12")
			return false;
		if (a.title() != "HTTP/1.1 202 Created")
			return false;
		if (a.body() != binary_data("koukouroukou"))
			return false;
		if (a.ErrorCode != "202")
			return false;
		if (a.ErrorMsg != "Created")
			return false;

		// Response without message CRLF
		b_parsed = a.parse(renderedNoCodeCRLF, &remaining);
		if ((!b_parsed) || (remaining != trail))
			return false;
		if (a.headers().size() != 2)
			return false;
		if (a.headers().get("a") != "123")
			return false;
		if (a.headers().get("Content-Length") != "12")
			return false;
		if (a.title() != "HTTP/1.1 404")
			return false;
		if (a.body() != binary_data("koukouroukou"))
			return false;
		if (a.ErrorCode != "404")
			return false;
		if (a.ErrorMsg != "")
			return false;
		return true;
	}

	bool TestHTTPResponse::TestParseWrong1::OnExecute()
	{	http::Response a;
		a.parse(binary_data("HTTP/1.1\r\nContent-Length: 12\r\na: 123\r\n\r\nkoukouroukou"));
		return false;
	}

	bool TestHTTPResponse::TestParseWrong2::OnExecute()
	{	http::Response a;
		a.parse(binary_data("HTTP/1.1  \r\nContent-Length: 12\r\na: 123\r\n\r\nkoukouroukou"));
		return false;
	}

	bool TestHTTPResponse::TestParseSpeed::OnExecute()
	{	http::Response a;
		binary_data rendered("HTTP/1.1 202 Created\nContent-Length: 12\na: 123\n\nkoukouroukou");
		bool b_parsed;

		// Response LF
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
		if (a.title() != "HTTP/1.1 202 Created")
			return false;
		if (a.body() != binary_data("koukouroukou"))
			return false;
		if (a.ErrorCode != "202")
			return false;
		if (a.ErrorMsg != "Created")
			return false;
		return true;
	}
};	// !oonet namespace
