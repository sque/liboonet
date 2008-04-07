#include "TestHTTPPacket.h"
#include "http/packet.hpp"
namespace oonet
{
	TestHTTPPacket theTestHTTPPacket;

	bool TestHTTPPacket::TestCtor::OnExecute()
	{	http::packet a;

		if (! a.body().empty())
			return false;
		if (a.headers().size() != 0)
			return false;
		if (! a.title().empty())
			return false;
		return true;
	}

	bool TestHTTPPacket::TestCopyCtor::OnExecute()
	{	http::packet a;

		a.body() = binary_data("koukouroukou");
		a.headers().set("a", "123");
		a.title() = "GET / HTTP/1.1";

		if (a.body()  != binary_data("koukouroukou"))
			return false;
		if (a.headers().size() != 1)
			return false;
		if (a.headers().get("a") != "123")
			return false;
		if (a.title() != binary_data("GET / HTTP/1.1"))
			return false;

		http::packet b(a);
		if (b.body()  != binary_data("koukouroukou"))
			return false;
		if (b.headers().size() != 1)
			return false;
		if (b.headers().get("a") != "123")
			return false;
		if (b.title() != binary_data("GET / HTTP/1.1"))
			return false;
		return true;
	}

	bool TestHTTPPacket::TestCopyOperator::OnExecute()
	{	http::packet a, b;

		a.body() = binary_data("koukouroukou");
		a.headers().set("a", "123");
		a.title() = "GET / HTTP/1.1";

		if (a.body()  != binary_data("koukouroukou"))
			return false;
		if (a.headers().size() != 1)
			return false;
		if (a.headers().get("a") != "123")
			return false;
		if (a.title() != binary_data("GET / HTTP/1.1"))
			return false;

		b = a;
		if (b.body()  != binary_data("koukouroukou"))
			return false;
		if (b.headers().size() != 1)
			return false;
		if (b.headers().get("a") != "123")
			return false;
		if (b.title() != binary_data("GET / HTTP/1.1"))
			return false;
		return true;
	}

	bool TestHTTPPacket::TestGetBody::OnExecute()
	{	http::packet a;
		binary_data PredefBody = binary_data((byte)'a', 60000);

		a.body() = PredefBody;
		for (long i = 0;i < 10000; i++)
		{
			if (a.body() != PredefBody)
				return false;
		}
		return true;
	}

	bool TestHTTPPacket::TestGetTitle::OnExecute()
	{	http::packet a;
		string PredefTitle = binary_data((byte)'a', 60000).to_string();

		a.title() = PredefTitle;
		for (long i = 0;i < 10000; i++)
		{
			if (a.title() != PredefTitle)
				return false;
		}
		return true;
	}

	bool TestHTTPPacket::TestRender::OnExecute()
	{	http::packet a;
		binary_data out, PredefBody = binary_data((byte)'a', 60000);
		binary_data shouldBe = binary_data("GET / HTTP/1.1\r\nContent-Length: 60000\r\n\r\n") + PredefBody;
		binary_data shouldBeLF = binary_data("GET / HTTP/1.1\nContent-Length: 60000\n\n") + PredefBody;

		// Populate a
		a.title() = "GET / HTTP/1.1";
		a.body() = PredefBody;

		// Render with default new line
		out = a.render();
		if (out != shouldBe)
			return false;

		/// Render with LF
		out = a.render(binary_data("\n"));
		if (out != shouldBeLF)
			return false;

		return true;
	}

	bool TestHTTPPacket::TestRenderSpeed::OnExecute()
	{	http::packet a;
		binary_data out, PredefBody = binary_data((byte)'a', 60000);
		binary_data shouldBe= binary_data("GET / HTTP/1.1\r\nContent-Length: 60000\r\n\r\n") + PredefBody;

		// Populate a
		a.title() = "GET / HTTP/1.1";
		a.body() = PredefBody;

		ResetTimer();
		for (long i = 0;i < 10000;i++)
			out = a.render();

		if (out != shouldBe)
			return false;
		return true;
	}

	bool TestHTTPPacket::TestParseSpeed::OnExecute()
	{	http::packet a;
		binary_data PredefBody = binary_data((byte)'a', 60000);
		binary_data rendered = binary_data("GET / HTTP/1.1\nContent-Length: 60000\n\n") + PredefBody + binary_data("1234");
		binary_data remaining;
		bool b_parsed;

		// Parse 10k times
		ResetTimer();
		for (long i = 0;i < 10000;i++)
			b_parsed = a.parse(rendered, &remaining);

		if (a.body() != PredefBody)
			return false;
		if (a.title() != binary_data("GET / HTTP/1.1"))
			return false;
		if (a.headers().get("Content-Length") != "60000")
			return false;

		// Final quality test
		if (!b_parsed)
			return false;
		if (remaining != binary_data("1234"))
			return false;
		return true;
	}

	bool TestHTTPPacket::TestParse::OnExecute()
	{	http::packet a;
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
		if (a.body() != PredefBody)
			return false;
		if (a.title() != binary_data("POST / HTTP/1.1"))
			return false;
		if (a.headers().get("Content-Length") != "60000")
			return false;
		if ((!b_parsed) || (remaining != trail_data))
			return false;

		// Packet With Body LF
		b_parsed = a.parse(PacketWBodyLF, &remaining);
		if (a.body() != PredefBody)
			return false;
		if (a.title() != binary_data("POST / HTTP/1.1"))
			return false;
		if (a.headers().get("Content-Length") != "60000")
			return false;
		if ((!b_parsed) || (remaining != trail_data))
			return false;

		// Packet With-out Body CRLF
		b_parsed = a.parse(PacketCRLF, &remaining);
		if (! a.body().empty())
			return false;
		if (a.title() != binary_data("GET / HTTP/1.1"))
			return false;
		if (a.headers().get("Host") != "123")
			return false;
		if ((!b_parsed) || (remaining != binary_data::nothing))
			return false;

		return true;
		// Packet With-out Body Mixed and wierd but valid headers
		// THIS TEST FOR SOME REASON FAILS!
		b_parsed = a.parse(PacketWithEmptyHeaderMixed);
		if (! a.body().empty())
			return false;
		if (a.title() != binary_data("GET / HTTP/1.1"))
			return false;
		if (a.headers().size() != 2)
			return false;
		if (a.headers().get("Host") != "123")
			return false;
		if (a.headers().get("") != "::")
			return false;
		if ((!b_parsed) || (remaining != trail_data))
			return false;
		return true;
	}

	bool TestHTTPPacket::TestParseWrong1::OnExecute()
	{	http::packet a;
		binary_data PacketNoHeads = binary_data("POST / HTTP/1.1\r\n\r\n\r\n") ;
		a.parse(PacketNoHeads);
		return false;
	}

	bool TestHTTPPacket::TestParseWrong2::OnExecute()
	{	http::packet a;
		binary_data PacketWrongContentLength = binary_data("POST / HTTP/1.1\r\nContent-Length: -1000\n\n") ;
		a.parse(PacketWrongContentLength);
		return false;
	}

	bool TestHTTPPacket::TestParseIncomplete1::OnExecute()
	{	http::packet a;
		binary_data PacketNoDoubleNewLine = binary_data("POST / HTTP/1.1\r\nContent: 1\n") ;
		if (a.parse(PacketNoDoubleNewLine))
			return false;
		return true;
	}

	bool TestHTTPPacket::TestParseIncomplete2::OnExecute()
	{	http::packet a;
		binary_data PacketNoDoubleNewLine = binary_data("POST / HTTP/1.1\r\nContent-Length: 1\n\n") ;
		if (a.parse(PacketNoDoubleNewLine))
			return false;
		return true;
	}
};	// !oonet namespace
