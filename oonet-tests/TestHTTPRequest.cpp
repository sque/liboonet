#include "TestHTTPRequest.h"
#include "http/request.hpp"

namespace oonet
{
	TestHTTPRequest theTestHTTPRequest;

	bool TestHTTPRequest::TestCtor::OnExecute()
	{	http::Request a;

		if (! a.body().empty())
			return false;
		if (a.headers().size() != 0)
			return false;
		if (! a.title().empty())
			return false;
		if (a.http_type != http::Request::REQUEST_GET)
			return false;
		if ((string)a.url != "/")
			return false;
		return true;
	}

	bool TestHTTPRequest::TestCopyCtor::OnExecute()
	{	http::Request a;

		a.body() = binary_data("koukouroukou");
		a.headers().set("a", "123");
		a.title() = "GET / HTTP/1.1";
		a.http_type = http::Request::REQUEST_POST;
		a.url = "/index.html";

		if (a.body()  != binary_data("koukouroukou"))
			return false;
		if (a.headers().size() != 1)
			return false;
		if (a.headers().get("a") != "123")
			return false;
		if (a.title() != "GET / HTTP/1.1")
			return false;
		if (a.http_type != http::Request::REQUEST_POST)
			return false;
		if ((string)a.url != "/index.html")
			return false;

		http::Request b(a);
		if (b.body()  != binary_data("koukouroukou"))
			return false;
		if (b.headers().size() != 1)
			return false;
		if (b.headers().get("a") != "123")
			return false;
		if (b.title() != "GET / HTTP/1.1")
			return false;
		if (b.http_type != http::Request::REQUEST_POST)
			return false;
		if ((string)b.url != "/index.html")
			return false;
		return true;
	}
	bool TestHTTPRequest::TestCopyOperator::OnExecute()
	{	http::Request a, b;

		a.body() = binary_data("koukouroukou");
		a.headers().set("a", "123");
		a.title() = "GET / HTTP/1.1";
		a.http_type = http::Request::REQUEST_POST;
		a.url = "/index.html";

		if (a.body()  != binary_data("koukouroukou"))
			return false;
		if (a.headers().size() != 1)
			return false;
		if (a.headers().get("a") != "123")
			return false;
		if (a.title() != "GET / HTTP/1.1")
			return false;
		if (a.http_type != http::Request::REQUEST_POST)
			return false;
		if ((string)a.url != "/index.html")
			return false;

		b = a;
		if (b.body()  != binary_data("koukouroukou"))
			return false;
		if (b.headers().size() != 1)
			return false;
		if (b.headers().get("a") != "123")
			return false;
		if (b.title() != "GET / HTTP/1.1")
			return false;
		if (b.http_type != http::Request::REQUEST_POST)
			return false;
		if ((string)b.url != "/index.html")
			return false;
		return true;
	}

	bool TestHTTPRequest::TestRender::OnExecute()
	{	http::Request a;
		string shouldbeLF = "POST /index.html HTTP/1.1\nContent-Length: 12\na: 123\n\nkoukouroukou";
		string shouldbeCRLF = "POST /index.html HTTP/1.1\r\nContent-Length: 12\r\na: 123\r\n\r\nkoukouroukou";
		string out;

		a.body() = binary_data("koukouroukou");
		a.headers().set("a", "123");
		a.http_type = http::Request::REQUEST_POST;
		a.url = "/index.html";

		out = a.render(http::LF).to_string();
		if (out != shouldbeLF)
			return false;

		out = a.render(http::CRLF).to_string();
		if (out != shouldbeCRLF)
			return false;

		return true;
	}

	bool TestHTTPRequest::TestRenderSpeed::OnExecute()
	{	http::Request a;
		string shouldbeLF = "POST /index.html HTTP/1.1\nContent-Length: 12\na: 123\n\nkoukouroukou";
		string out;

		a.body() = binary_data("koukouroukou");
		a.headers().set("a", "123");
		a.http_type = http::Request::REQUEST_POST;
		a.url = "/index.html";

		ResetTimer();
		for(long i = 0;i < 10000;i++)
			out = a.render(http::LF).to_string();
		if (out != shouldbeLF)
			return false;

		return true;
	}

	bool TestHTTPRequest::TestParse::OnExecute()
	{	http::Request a;
		bool b_parsed;
		binary_data trail("1234");
		binary_data remaining;
		binary_data renderedLF = binary_data("POST /index.html HTTP/1.1\nContent-Length: 12\na: 123\n\nkoukouroukou") + trail;
		binary_data renderedCRLF = binary_data("POST /index.html HTTP/1.1\r\nContent-Length: 12\r\na: 123\r\n\r\nkoukouroukou") + trail;
		binary_data renderedGETCRLF = binary_data("GET /index.html HTTP/1.1\r\nContent-Length: 12\r\na: 123\r\n\r\nkoukouroukou") + trail;

		// Post LF
		b_parsed = a.parse(renderedLF, &remaining);
		if ((!b_parsed) || (remaining != trail))
			return false;
		if (a.headers().size() != 2)
			return false;
		if (a.headers().get("a") != "123")
			return false;
		if (a.headers().get("Content-Length") != "12")
			return false;
		if (a.title() != "POST /index.html HTTP/1.1")
			return false;
		if (a.body() != binary_data("koukouroukou"))
			return false;
		if (a.http_type != http::Request::REQUEST_POST)
			return false;
		if ((string)a.url != "/index.html")
			return false;

		// Post CRLF
		b_parsed = a.parse(renderedCRLF, &remaining);
		if ((!b_parsed) || (remaining != trail))
			return false;
		if (a.headers().size() != 2)
			return false;
		if (a.headers().get("a") != "123")
			return false;
		if (a.headers().get("Content-Length") != "12")
			return false;
		if (a.title() != "POST /index.html HTTP/1.1")
			return false;
		if (a.body() != binary_data("koukouroukou"))
			return false;
		if (a.http_type != http::Request::REQUEST_POST)
			return false;
		if ((string)a.url != "/index.html")
			return false;

		// GET CRLF
		b_parsed = a.parse(renderedGETCRLF, &remaining);
		if ((!b_parsed) || (remaining != trail))
			return false;
		if (a.headers().size() != 2)
			return false;
		if (a.headers().get("a") != "123")
			return false;
		if (a.headers().get("Content-Length") != "12")
			return false;
		if (a.title() != "GET /index.html HTTP/1.1")
			return false;
		if (a.body() != binary_data("koukouroukou"))
			return false;
		if (a.http_type != http::Request::REQUEST_GET)
			return false;
		if ((string)a.url != "/index.html")
			return false;
		return true;
	}

	bool TestHTTPRequest::TestParseWrong1::OnExecute()
	{	http::Request a;
		string renderedGETCRLF = "GET  HTTP/1.1\r\nContent-Length: 12\r\na: 123\r\n\r\nkoukouroukou";
		binary_data rendered(renderedGETCRLF);

		a.parse(rendered);
		return false;
	}

	bool TestHTTPRequest::TestParseWrong2::OnExecute()
	{	http::Request a;
		string renderedGETCRLF = "GET / \r\nContent-Length: 12\r\na: 123\r\n\r\nkoukouroukou";
		binary_data rendered(renderedGETCRLF);

		a.parse(rendered);
		return false;
	}

	bool TestHTTPRequest::TestParseSpeed::OnExecute()
	{	http::Request a;
		string renderedGETCRLF = "GET /index.html HTTP/1.1\r\nContent-Length: 12\r\na: 123\r\n\r\nkoukouroukou";
		binary_data rendered(renderedGETCRLF);

		ResetTimer();
		// Post LF
		for(long i = 0;i < 10000;i++)
			a.parse(rendered);
		if (a.headers().size() != 2)
			return false;
		if (a.headers().get("a") != "123")
			return false;
		if (a.headers().get("Content-Length") != "12")
			return false;
		if (a.title() != "GET /index.html HTTP/1.1")
			return false;
		if (a.body() != binary_data("koukouroukou"))
			return false;
		if (a.http_type != http::Request::REQUEST_GET)
			return false;
		if ((string)a.url != "/index.html")
			return false;
		return true;
	}

};	// !oonet namespace
