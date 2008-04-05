#include "TestHTTPRequest.h"
#include "Http/Request.h"

namespace oonet
{
	TestHTTPRequest theTestHTTPRequest;

	bool TestHTTPRequest::TestCtor::OnExecute()
	{	http::Request a;

		if (! a.getBody().empty())
			return false;
		if (a.getHeaders().getSTLMap().size() != 0)
			return false;
		if (! a.getTitle().empty())
			return false;
		if (a.http_type != http::Request::REQUEST_GET)
			return false;
		if ((string)a.url != "/")
			return false;
		return true;
	}

	bool TestHTTPRequest::TestCopyCtor::OnExecute()
	{	http::Request a;

		a.setBody(binary_data("koukouroukou"));
		a.getHeaders().setHeader("a", "123");
		a.setTitle("GET / HTTP/1.1");
		a.http_type = http::Request::REQUEST_POST;
		a.url = "/index.html";

		if (a.getBody()  != binary_data("koukouroukou"))
			return false;
		if (a.getHeaders().getSTLMap().size() != 1)
			return false;
		if (a.getHeaders().getSTLMap().find("a")->second != "123")
			return false;
		if (a.getTitle() != "GET / HTTP/1.1")
			return false;
		if (a.http_type != http::Request::REQUEST_POST)
			return false;
		if ((string)a.url != "/index.html")
			return false;

		http::Request b(a);
		if (b.getBody()  != binary_data("koukouroukou"))
			return false;
		if (b.getHeaders().getSTLMap().size() != 1)
			return false;
		if (b.getHeaders().getSTLMap().find("a")->second != "123")
			return false;
		if (b.getTitle() != "GET / HTTP/1.1")
			return false;
		if (b.http_type != http::Request::REQUEST_POST)
			return false;
		if ((string)b.url != "/index.html")
			return false;
		return true;
	}
	bool TestHTTPRequest::TestCopyOperator::OnExecute()
	{	http::Request a, b;

		a.setBody(binary_data("koukouroukou"));
		a.getHeaders().setHeader("a", "123");
		a.setTitle("GET / HTTP/1.1");
		a.http_type = http::Request::REQUEST_POST;
		a.url = "/index.html";

		if (a.getBody()  != binary_data("koukouroukou"))
			return false;
		if (a.getHeaders().getSTLMap().size() != 1)
			return false;
		if (a.getHeaders().getSTLMap().find("a")->second != "123")
			return false;
		if (a.getTitle() != "GET / HTTP/1.1")
			return false;
		if (a.http_type != http::Request::REQUEST_POST)
			return false;
		if ((string)a.url != "/index.html")
			return false;

		b = a;
		if (b.getBody()  != binary_data("koukouroukou"))
			return false;
		if (b.getHeaders().getSTLMap().size() != 1)
			return false;
		if (b.getHeaders().getSTLMap().find("a")->second != "123")
			return false;
		if (b.getTitle() != "GET / HTTP/1.1")
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

		a.setBody(binary_data("koukouroukou"));
		a.getHeaders().setHeader("a", "123");
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

		a.setBody(binary_data("koukouroukou"));
		a.getHeaders().setHeader("a", "123");
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
		string renderedLF = "POST /index.html HTTP/1.1\nContent-Length: 12\na: 123\n\nkoukouroukou";
		string renderedCRLF = "POST /index.html HTTP/1.1\r\nContent-Length: 12\r\na: 123\r\n\r\nkoukouroukou";
		string renderedGETCRLF = "GET /index.html HTTP/1.1\r\nContent-Length: 12\r\na: 123\r\n\r\nkoukouroukou";

		// Post LF
		if (a.parse(binary_data(renderedLF)) != renderedLF.size())
			return false;
		if (a.getHeaders().getSTLMap().size() != 2)
			return false;
		if (a.getHeaders().getSTLMap().find("a")->second != "123")
			return false;
		if (a.getHeaders().getSTLMap().find("Content-Length")->second != "12")
			return false;
		if (a.getTitle() != "POST /index.html HTTP/1.1")
			return false;
		if (a.getBody() != binary_data("koukouroukou"))
			return false;
		if (a.http_type != http::Request::REQUEST_POST)
			return false;
		if ((string)a.url != "/index.html")
			return false;

		// Post CRLF
		if (a.parse(binary_data(renderedCRLF)) != renderedCRLF.size())
			return false;
		if (a.getHeaders().getSTLMap().size() != 2)
			return false;
		if (a.getHeaders().getSTLMap().find("a")->second != "123")
			return false;
		if (a.getHeaders().getSTLMap().find("Content-Length")->second != "12")
			return false;
		if (a.getTitle() != "POST /index.html HTTP/1.1")
			return false;
		if (a.getBody() != binary_data("koukouroukou"))
			return false;
		if (a.http_type != http::Request::REQUEST_POST)
			return false;
		if ((string)a.url != "/index.html")
			return false;

		// GET CRLF
		if (a.parse(binary_data(renderedGETCRLF)) != renderedGETCRLF.size())
			return false;
		if (a.getHeaders().getSTLMap().size() != 2)
			return false;
		if (a.getHeaders().getSTLMap().find("a")->second != "123")
			return false;
		if (a.getHeaders().getSTLMap().find("Content-Length")->second != "12")
			return false;
		if (a.getTitle() != "GET /index.html HTTP/1.1")
			return false;
		if (a.getBody() != binary_data("koukouroukou"))
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
		if (a.getHeaders().getSTLMap().size() != 2)
			return false;
		if (a.getHeaders().getSTLMap().find("a")->second != "123")
			return false;
		if (a.getHeaders().getSTLMap().find("Content-Length")->second != "12")
			return false;
		if (a.getTitle() != "GET /index.html HTTP/1.1")
			return false;
		if (a.getBody() != binary_data("koukouroukou"))
			return false;
		if (a.http_type != http::Request::REQUEST_GET)
			return false;
		if ((string)a.url != "/index.html")
			return false;
		return true;
	}

};	// !oonet namespace
