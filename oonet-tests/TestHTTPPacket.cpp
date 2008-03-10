#include "TestHTTPPacket.h"
#include "Http/Packet.h"
namespace Slib
{
	TestHTTPPacket theTestHTTPPacket;

	bool TestHTTPPacket::TestCtor::OnExecute()
	{	HTTP::Packet a;

		if (! a.getBody().empty())
			return false;
		if (a.getHeaders().getSTLMap().size() != 0)
			return false;
		if (! a.getTitle().empty())
			return false;
		return true;
	}

	bool TestHTTPPacket::TestCopyCtor::OnExecute()
	{	HTTP::Packet a;

		a.setBody(BinaryData("koukouroukou"));
		a.getHeaders().setHeader("a", "123");
		a.setTitle("GET / HTTP/1.1");

		if (a.getBody()  != BinaryData("koukouroukou"))
			return false;
		if (a.getHeaders().getSTLMap().size() != 1)
			return false;
		if (a.getHeaders().getSTLMap().find("a")->second != "123")
			return false;
		if (a.getTitle() != "GET / HTTP/1.1")
			return false;

		HTTP::Packet b(a);
		if (b.getBody()  != BinaryData("koukouroukou"))
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
	{	HTTP::Packet a, b;

		a.setBody(BinaryData("koukouroukou"));
		a.getHeaders().setHeader("a", "123");
		a.setTitle("GET / HTTP/1.1");

		if (a.getBody()  != BinaryData("koukouroukou"))
			return false;
		if (a.getHeaders().getSTLMap().size() != 1)
			return false;
		if (a.getHeaders().getSTLMap().find("a")->second != "123")
			return false;
		if (a.getTitle() != "GET / HTTP/1.1")
			return false;

		b = a;
		if (b.getBody()  != BinaryData("koukouroukou"))
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
	{	HTTP::Packet a;
		BinaryData PredefBody = BinaryData((Byte)'a', 60000);

		a.setBody(PredefBody);
		for (long i = 0;i < 10000; i++)
		{
			if (a.getBody() != PredefBody)
				return false;
		}
		return true;
	}

	bool TestHTTPPacket::TestGetTitle::OnExecute()
	{	HTTP::Packet a;
		string PredefTitle = BinaryData((Byte)'a', 60000).toString();

		a.setTitle(PredefTitle);
		for (long i = 0;i < 10000; i++)
		{
			if (a.getTitle() != PredefTitle)
				return false;
		}
		return true;
	}

	bool TestHTTPPacket::TestRender::OnExecute()
	{	HTTP::Packet a;
		BinaryData out, PredefBody = BinaryData((Byte)'a', 60000);
		BinaryData shouldBe = BinaryData("GET / HTTP/1.1\r\nContent-Length: 60000\r\n\r\n") + PredefBody;
		BinaryData shouldBeLF = BinaryData("GET / HTTP/1.1\nContent-Length: 60000\n\n") + PredefBody;

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
	{	HTTP::Packet a;
		BinaryData out, PredefBody = BinaryData((Byte)'a', 60000);
		BinaryData shouldBe= BinaryData("GET / HTTP/1.1\r\nContent-Length: 60000\r\n\r\n") + PredefBody;

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
	{	HTTP::Packet a;
		size_t parsedSize;
		BinaryData PredefBody = BinaryData((Byte)'a', 60000);
		BinaryData rendered = BinaryData("GET / HTTP/1.1\nContent-Length: 60000\n\n") + PredefBody;

		// Parse 10k times
		ResetTimer();
		for (long i = 0;i < 10000;i++)
			parsedSize = a.parse(rendered);

		if (a.getBody() != PredefBody)
			return false;
		if (a.getTitle() != "GET / HTTP/1.1")
			return false;
		if (a.getHeaders().getSTLMap().find("Content-Length")->second != "60000")
			return false;
		if (parsedSize != rendered.size())
			return false;
		return true;
	}

	bool TestHTTPPacket::TestParse::OnExecute()
	{	HTTP::Packet a;
		size_t parsedSize;
		BinaryData PredefBody = BinaryData((Byte)'a', 60000);
		BinaryData PacketWBodyCRLF = BinaryData("POST / HTTP/1.1\r\nContent-Length: 60000\r\n\r\n") + PredefBody;
		BinaryData PacketWBodyLF = BinaryData("POST / HTTP/1.1\nContent-Length: 60000\n\n") + PredefBody;
		BinaryData PacketCRLF = BinaryData("GET / HTTP/1.1\r\nHost: 123\r\n\r\n");
		BinaryData PacketWithEmptyHeaderMixed = BinaryData("GET / HTTP/1.1\r\nHost: 123\n::\r\n\r\n");

		// Packet With Body CRLF
		parsedSize = a.parse(PacketWBodyCRLF);
		if (a.getBody() != PredefBody)
			return false;
		if (a.getTitle() != "POST / HTTP/1.1")
			return false;
		if (a.getHeaders().getSTLMap().find("Content-Length")->second != "60000")
			return false;
		if (parsedSize != PacketWBodyCRLF.size())
			return false;

		// Packet With Body LF
		parsedSize = a.parse(PacketWBodyLF);
		if (a.getBody() != PredefBody)
			return false;
		if (a.getTitle() != "POST / HTTP/1.1")
			return false;
		if (a.getHeaders().getSTLMap().find("Content-Length")->second != "60000")
			return false;
		if (parsedSize != PacketWBodyLF.size())
			return false;

		// Packet With-out Body CRLF
		parsedSize = a.parse(PacketCRLF);
		if (! a.getBody().empty())
			return false;
		if (a.getTitle() != "GET / HTTP/1.1")
			return false;
		if (a.getHeaders().getSTLMap().find("Host")->second != "123")
			return false;
		if (parsedSize != PacketCRLF.size())
			return false;
		return true;

		// Packet With-out Body Mixed and wierd but valid headers
		parsedSize = a.parse(PacketWithEmptyHeaderMixed);
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
		if (parsedSize != PacketWithEmptyHeaderMixed.size())
			return false;
		return true;
	}

	bool TestHTTPPacket::TestParseWrong1::OnExecute()
	{	HTTP::Packet a;
		BinaryData PacketNoHeads = BinaryData("POST / HTTP/1.1\r\n\r\n\r\n") ;
		a.parse(PacketNoHeads);
		return false;
	}

	bool TestHTTPPacket::TestParseWrong2::OnExecute()
	{	HTTP::Packet a;
		BinaryData PacketWrongContentLength = BinaryData("POST / HTTP/1.1\r\nContent-Length: -1000\n\n") ;
		a.parse(PacketWrongContentLength);
		return false;
	}

	bool TestHTTPPacket::TestParseIncomplete1::OnExecute()
	{	HTTP::Packet a;
		BinaryData PacketNoDoubleNewLine = BinaryData("POST / HTTP/1.1\r\nContent: 1\n") ;
		a.parse(PacketNoDoubleNewLine);
		return false;
	}

	bool TestHTTPPacket::TestParseIncomplete2::OnExecute()
	{	HTTP::Packet a;
		BinaryData PacketNoDoubleNewLine = BinaryData("POST / HTTP/1.1\r\nContent-Length: 1\n\n") ;
		a.parse(PacketNoDoubleNewLine);
		return false;
	}
};	//! Slib namespace
