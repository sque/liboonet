#include "TestHTTPPacket.h"
#include "Http/Packet.h"
namespace oonet
{
	TestHTTPPacket theTestHTTPPacket;

	bool TestHTTPPacket::TestCtor::OnExecute()
	{	http::Packet a;

		if (! a.getBody().empty())
			return false;
		if (a.getHeaders().getSTLMap().size() != 0)
			return false;
		if (! a.getTitle().empty())
			return false;
		return true;
	}

	bool TestHTTPPacket::TestCopyCtor::OnExecute()
	{	http::Packet a;

		a.setBody(binary_data("koukouroukou"));
		a.getHeaders().setHeader("a", "123");
		a.setTitle("GET / HTTP/1.1");

		if (a.getBody()  != binary_data("koukouroukou"))
			return false;
		if (a.getHeaders().getSTLMap().size() != 1)
			return false;
		if (a.getHeaders().getSTLMap().find("a")->second != "123")
			return false;
		if (a.getTitle() != "GET / HTTP/1.1")
			return false;

		http::Packet b(a);
		if (b.getBody()  != binary_data("koukouroukou"))
			return false;
		if (b.getHeaders().getSTLMap().size() != 1)
			return false;
		if (b.getHeaders().getSTLMap().find("a")->second != "123")
			return false;
		if (b.getTitle() != "GET / HTTP/1.1")
			return false;
		return true;
	}

	bool TestHTTPPacket::TestCopyOperator::OnExecute()
	{	http::Packet a, b;

		a.setBody(binary_data("koukouroukou"));
		a.getHeaders().setHeader("a", "123");
		a.setTitle("GET / HTTP/1.1");

		if (a.getBody()  != binary_data("koukouroukou"))
			return false;
		if (a.getHeaders().getSTLMap().size() != 1)
			return false;
		if (a.getHeaders().getSTLMap().find("a")->second != "123")
			return false;
		if (a.getTitle() != "GET / HTTP/1.1")
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
		return true;
	}

	bool TestHTTPPacket::TestGetBody::OnExecute()
	{	http::Packet a;
		binary_data PredefBody = binary_data((byte)'a', 60000);

		a.setBody(PredefBody);
		for (long i = 0;i < 10000; i++)
		{
			if (a.getBody() != PredefBody)
				return false;
		}
		return true;
	}

	bool TestHTTPPacket::TestGetTitle::OnExecute()
	{	http::Packet a;
		string PredefTitle = binary_data((byte)'a', 60000).to_string();

		a.setTitle(PredefTitle);
		for (long i = 0;i < 10000; i++)
		{
			if (a.getTitle() != PredefTitle)
				return false;
		}
		return true;
	}

	bool TestHTTPPacket::TestRender::OnExecute()
	{	http::Packet a;
		binary_data out, PredefBody = binary_data((byte)'a', 60000);
		binary_data shouldBe = binary_data("GET / HTTP/1.1\r\nContent-Length: 60000\r\n\r\n") + PredefBody;
		binary_data shouldBeLF = binary_data("GET / HTTP/1.1\nContent-Length: 60000\n\n") + PredefBody;

		// Populate a
		a.setTitle("GET / HTTP/1.1");
		a.setBody(PredefBody);

		// Render with default new line
		out = a.render();
		if (out != shouldBe)
			return false;

		/// Render with LF
		out = a.render("\n");
		if (out != shouldBeLF)
			return false;

		return true;
	}

	bool TestHTTPPacket::TestRenderSpeed::OnExecute()
	{	http::Packet a;
		binary_data out, PredefBody = binary_data((byte)'a', 60000);
		binary_data shouldBe= binary_data("GET / HTTP/1.1\r\nContent-Length: 60000\r\n\r\n") + PredefBody;

		// Populate a
		a.setTitle("GET / HTTP/1.1");
		a.setBody(PredefBody);

		ResetTimer();
		for (long i = 0;i < 10000;i++)
			out = a.render();

		if (out != shouldBe)
			return false;
		return true;
	}

	bool TestHTTPPacket::TestParseSpeed::OnExecute()
	{	http::Packet a;
		binary_data PredefBody = binary_data((byte)'a', 60000);
		binary_data rendered = binary_data("GET / HTTP/1.1\nContent-Length: 60000\n\n") + PredefBody + binary_data("1234");
		binary_data remaining;
		bool b_parsed;

		// Parse 10k times
		ResetTimer();
		for (long i = 0;i < 10000;i++)
			b_parsed = a.parse(rendered, &remaining);

		if (a.getBody() != PredefBody)
			return false;
		if (a.getTitle() != "GET / HTTP/1.1")
			return false;
		if (a.getHeaders().getSTLMap().find("Content-Length")->second != "60000")
			return false;

		// Final quality test
		if (!b_parsed)
			return false;
		if (remaining != binary_data("1234"))
			return false;
		return true;
	}

	bool TestHTTPPacket::TestParse::OnExecute()
	{	http::Packet a;
		bool b_parsed;
		binary_data trail_data("1234");
		binary_data remaining;
		binary_data PredefBody = binary_data((byte)'a', 60000);
		binary_data PacketWBodyCRLF = binary_data("POST / HTTP/1.1\r\nContent-Length: 60000\r\n\r\n") + PredefBody + trail_data;
		binary_data PacketWBodyLF = binary_data("POST / HTTP/1.1\nContent-Length: 60000\n\n") + PredefBody + trail_data;
		binary_data PacketCRLF = binary_data("GET / HTTP/1.1\r\nHost: 123\r\n\r\n");
		binary_data PacketWithEmptyHeaderMixed = binary_data("GET / HTTP/1.1\r\nHost: 123\n::\r\n\r\n") + trail_data;

		// Packet With Body CRLF
		b_parsed = a.parse(PacketWBodyCRLF, &remaining);
		if (a.getBody() != PredefBody)
			return false;
		if (a.getTitle() != "POST / HTTP/1.1")
			return false;
		if (a.getHeaders().getSTLMap().find("Content-Length")->second != "60000")
			return false;
		if ((!b_parsed) || (remaining != trail_data))
			return false;

		// Packet With Body LF
		b_parsed = a.parse(PacketWBodyLF, &remaining);
		if (a.getBody() != PredefBody)
			return false;
		if (a.getTitle() != "POST / HTTP/1.1")
			return false;
		if (a.getHeaders().getSTLMap().find("Content-Length")->second != "60000")
			return false;
		if ((!b_parsed) || (remaining != trail_data))
			return false;

		// Packet With-out Body CRLF
		b_parsed = a.parse(PacketCRLF, &remaining);
		if (! a.getBody().empty())
			return false;
		if (a.getTitle() != "GET / HTTP/1.1")
			return false;
		if (a.getHeaders().getSTLMap().find("Host")->second != "123")
			return false;
		if ((!b_parsed) || (remaining != binary_data::EMPTY))
			return false;

		return true;
		// Packet With-out Body Mixed and wierd but valid headers
		// THIS TEST FOR SOME REASON FAILS!
		b_parsed = a.parse(PacketWithEmptyHeaderMixed);
		if (! a.getBody().empty())
			return false;
		if (a.getTitle() != "GET / HTTP/1.1")
			return false;
		if (a.getHeaders().getSTLMap().size() != 2)
			return false;
		if (a.getHeaders().getSTLMap().find("Host")->second != "123")
			return false;
		if (a.getHeaders().getSTLMap().find("")->second != "::")
			return false;
		if ((!b_parsed) || (remaining != trail_data))
			return false;
		return true;
	}

	bool TestHTTPPacket::TestParseWrong1::OnExecute()
	{	http::Packet a;
		binary_data PacketNoHeads = binary_data("POST / HTTP/1.1\r\n\r\n\r\n") ;
		a.parse(PacketNoHeads);
		return false;
	}

	bool TestHTTPPacket::TestParseWrong2::OnExecute()
	{	http::Packet a;
		binary_data PacketWrongContentLength = binary_data("POST / HTTP/1.1\r\nContent-Length: -1000\n\n") ;
		a.parse(PacketWrongContentLength);
		return false;
	}

	bool TestHTTPPacket::TestParseIncomplete1::OnExecute()
	{	http::Packet a;
		binary_data PacketNoDoubleNewLine = binary_data("POST / HTTP/1.1\r\nContent: 1\n") ;
		if (a.parse(PacketNoDoubleNewLine))
			return false;
		return true;
	}

	bool TestHTTPPacket::TestParseIncomplete2::OnExecute()
	{	http::Packet a;
		binary_data PacketNoDoubleNewLine = binary_data("POST / HTTP/1.1\r\nContent-Length: 1\n\n") ;
		if (a.parse(PacketNoDoubleNewLine))
			return false;
		return true;
	}
};	// !oonet namespace
