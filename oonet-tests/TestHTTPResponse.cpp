#include "TestHTTPResponse.h"
#include "Http/Response.h"

namespace Slib
{
	TestHTTPResponse theTestHTTPResponse;

	bool TestHTTPResponse::TestCtor::OnExecute()
	{	HTTP::Response a;

		if (! a.getBody().empty())
			return false;
		if (a.getHeaders().getSTLMap().size() != 0)
			return false;
		if (! a.getTitle().empty())
			return false;
		if (a.ErrorCode != "200")
			return false;
		if (a.ErrorMsg != "OK")
			return false;
		return true;
	}

	bool TestHTTPResponse::TestCopyCtor::OnExecute()
	{	HTTP::Response a;

		a.setBody(BinaryData("koukouroukou"));
		a.getHeaders().setHeader("a", "123");
		a.setTitle("200 OK");
		a.ErrorCode = "404";
		a.ErrorMsg = "Not Found";

		if (a.getBody()  != BinaryData("koukouroukou"))
			return false;
		if (a.getHeaders().getSTLMap().size() != 1)
			return false;
		if (a.getHeaders().getSTLMap().find("a")->second != "123")
			return false;
		if (a.getTitle() != "200 OK")
			return false;
		if (a.ErrorCode != "404")
			return false;
		if (a.ErrorMsg != "Not Found")
			return false;

		HTTP::Response b(a);
		if (b.getBody()  != BinaryData("koukouroukou"))
			return false;
		if (b.getHeaders().getSTLMap().size() != 1)
			return false;
		if (b.getHeaders().getSTLMap().find("a")->second != "123")
			return false;
		if (b.getTitle() != "200 OK")
			return false;
		if (b.ErrorCode != "404")
			return false;
		if (b.ErrorMsg != "Not Found")
			return false;
		return true;
	}
	bool TestHTTPResponse::TestCopyOperator::OnExecute()
	{	HTTP::Response a, b;

		a.setBody(BinaryData("koukouroukou"));
		a.getHeaders().setHeader("a", "123");
		a.setTitle("200 OK");
		a.ErrorCode = "404";
		a.ErrorMsg = "Not Found";

		if (a.getBody()  != BinaryData("koukouroukou"))
			return false;
		if (a.getHeaders().getSTLMap().size() != 1)
			return false;
		if (a.getHeaders().getSTLMap().find("a")->second != "123")
			return false;
		if (a.getTitle() != "200 OK")
			return false;
		if (a.ErrorCode != "404")
			return false;
		if (a.ErrorMsg != "Not Found")
			return false;

		b = a;
		if (b.getBody()  != BinaryData("koukouroukou"))
			return false;
		if (b.getHeaders().getSTLMap().size() != 1)
			return false;
		if (b.getHeaders().getSTLMap().find("a")->second != "123")
			return false;
		if (b.getTitle() != "200 OK")
			return false;
		if (b.ErrorCode != "404")
			return false;
		if (b.ErrorMsg != "Not Found")
			return false;
		return true;
	}

	bool TestHTTPResponse::TestRender::OnExecute()
	{	HTTP::Response a;
		string shouldbeLF = "HTTP/1.1 202 Created\nContent-Length: 12\na: 123\n\nkoukouroukou";
		string shouldbeCRLF = "HTTP/1.1 202 Created\r\nContent-Length: 12\r\na: 123\r\n\r\nkoukouroukou";
		string out;

		a.setBody(BinaryData("koukouroukou"));
		a.getHeaders().setHeader("a", "123");
		a.ErrorCode = "202";
		a.ErrorMsg = "Created";

		out = a.render(HTTP::LF).toString();
		if (out != shouldbeLF)
			return false;

		out = a.render(HTTP::CRLF).toString();
		if (out != shouldbeCRLF)
			return false;

		return true;
	}

	bool TestHTTPResponse::TestRenderSpeed::OnExecute()
	{	HTTP::Response a;
		string shouldbeLF = "HTTP/1.1 202 Created\nContent-Length: 12\na: 123\n\nkoukouroukou";
		string out;

		a.setBody(BinaryData("koukouroukou"));
		a.getHeaders().setHeader("a", "123");
		a.ErrorCode = "202";
		a.ErrorMsg = "Created";

		ResetTimer();
		for(long i = 0;i < 10000;i++)
			out = a.render(HTTP::LF).toString();
		if (out != shouldbeLF)
			return false;

		return true;
	}

	bool TestHTTPResponse::TestParse::OnExecute()
	{	HTTP::Response a;
		string renderedLF = "HTTP/1.1 202 Created\nContent-Length: 12\na: 123\n\nkoukouroukou";
		string renderedCRLF = "HTTP/1.1 202 Created\r\nContent-Length: 12\r\na: 123\r\n\r\nkoukouroukou";
		string renderedNoCodeCRLF = "HTTP/1.1 404\r\nContent-Length: 12\r\na: 123\r\n\r\nkoukouroukou";

		// Response LF
		if (a.parse(BinaryData(renderedLF)) != renderedLF.size())
			return false;
		if (a.getHeaders().getSTLMap().size() != 2)
			return false;
		if (a.getHeaders().getSTLMap().find("a")->second != "123")
			return false;
		if (a.getHeaders().getSTLMap().find("Content-Length")->second != "12")
			return false;
		if (a.getTitle() != "HTTP/1.1 202 Created")
			return false;
		if (a.getBody() != BinaryData("koukouroukou"))
			return false;
		if (a.ErrorCode != "202")
			return false;
		if (a.ErrorMsg != "Created")
			return false;

		// Response CRLF
		if (a.parse(BinaryData(renderedCRLF)) != renderedCRLF.size())
			return false;
		if (a.getHeaders().getSTLMap().size() != 2)
			return false;
		if (a.getHeaders().getSTLMap().find("a")->second != "123")
			return false;
		if (a.getHeaders().getSTLMap().find("Content-Length")->second != "12")
			return false;
		if (a.getTitle() != "HTTP/1.1 202 Created")
			return false;
		if (a.getBody() != BinaryData("koukouroukou"))
			return false;
		if (a.ErrorCode != "202")
			return false;
		if (a.ErrorMsg != "Created")
			return false;

		// Response without message CRLF
		if (a.parse(BinaryData(renderedNoCodeCRLF)) != renderedNoCodeCRLF.size())
			return false;
		if (a.getHeaders().getSTLMap().size() != 2)
			return false;
		if (a.getHeaders().getSTLMap().find("a")->second != "123")
			return false;
		if (a.getHeaders().getSTLMap().find("Content-Length")->second != "12")
			return false;
		if (a.getTitle() != "HTTP/1.1 404")
			return false;
		if (a.getBody() != BinaryData("koukouroukou"))
			return false;
		if (a.ErrorCode != "404")
			return false;
		if (a.ErrorMsg != "")
			return false;
		return true;
	}

	bool TestHTTPResponse::TestParseWrong1::OnExecute()
	{	HTTP::Response a;
		a.parse(BinaryData("HTTP/1.1\r\nContent-Length: 12\r\na: 123\r\n\r\nkoukouroukou"));
		return false;
	}

	bool TestHTTPResponse::TestParseWrong2::OnExecute()
	{	HTTP::Response a;
		a.parse(BinaryData("HTTP/1.1  \r\nContent-Length: 12\r\na: 123\r\n\r\nkoukouroukou"));
		return false;
	}

	bool TestHTTPResponse::TestParseSpeed::OnExecute()
	{	HTTP::Response a;
		BinaryData rendered("HTTP/1.1 202 Created\nContent-Length: 12\na: 123\n\nkoukouroukou");
		size_t out;

		// Response LF
		ResetTimer();
		for(long i = 0;i < 10000;i++)
			out = a.parse(rendered);
		if (out != rendered.size())
			return false;
		if (a.getHeaders().getSTLMap().size() != 2)
			return false;
		if (a.getHeaders().getSTLMap().find("a")->second != "123")
			return false;
		if (a.getHeaders().getSTLMap().find("Content-Length")->second != "12")
			return false;
		if (a.getTitle() != "HTTP/1.1 202 Created")
			return false;
		if (a.getBody() != BinaryData("koukouroukou"))
			return false;
		if (a.ErrorCode != "202")
			return false;
		if (a.ErrorMsg != "Created")
			return false;
		return true;
	}
};	//! Slib namespace
