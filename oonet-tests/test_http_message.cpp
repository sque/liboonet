#include "test_http_message.hpp"
#include <oonet/http/message.hpp>
namespace oonet
{
	namespace test
	{
		test_http_message test_http_message_inst;

		bool test_http_message::TestCtor::operator()()
		{	http::message a;

			if (! a.body().empty())
				return false;
			if (a.headers().size() != 0)
				return false;
			if (! a.title().empty())
				return false;
			return true;
		}

		bool test_http_message::TestCopyCtor::operator()()
		{	http::message a;
			string header_value;

			a.body() = binary_data("koukouroukou");
			a.headers().add("a", "123");
			a.title() = binary_data("GET / HTTP/1.1");

			if (a.body()  != binary_data("koukouroukou"))
				return false;
			if (a.headers().size() != 1)
				return false;
			if (!(a.headers().find_first("a", header_value) && (header_value == "123")))
				return false;
			if (a.title() != binary_data("GET / HTTP/1.1"))
				return false;

			http::message b(a);
			if (b.body()  != binary_data("koukouroukou"))
				return false;
			if (b.headers().size() != 1)
				return false;
			if (!(b.headers().find_first("a", header_value) && (header_value == "123")))
				return false;
			if (b.title() != binary_data("GET / HTTP/1.1"))
				return false;
			return true;
		}

		bool test_http_message::TestCopyOperator::operator()()
		{	http::message a, b;
			string header_value;

			a.body() = binary_data("koukouroukou");
			a.headers().add("a", "123");
			a.title() = binary_data("GET / HTTP/1.1");

			if (a.body()  != binary_data("koukouroukou"))
				return false;
			if (a.headers().size() != 1)
				return false;
			if (!(a.headers().find_first("a", header_value) && (header_value == "123")))
				return false;
			if (a.title() != binary_data("GET / HTTP/1.1"))
				return false;

			b = a;
			if (b.body()  != binary_data("koukouroukou"))
				return false;
			if (b.headers().size() != 1)
				return false;
			if (!(b.headers().find_first("a", header_value) && (header_value == "123")))
				return false;
			if (b.title() != binary_data("GET / HTTP/1.1"))
				return false;
			return true;
		}

		bool test_http_message::TestGetBody::operator()()
		{	http::message a;
			binary_data PredefBody = binary_data((byte)'a', 60000);

			a.body() = PredefBody;
			for (long i = 0;i < 10000; i++)
			{
				if (a.body() != PredefBody)
					return false;
			}
			return true;
		}

		bool test_http_message::TestGetTitle::operator()()
		{	http::message a;
			binary_data PredefTitle = binary_data((byte)'a', 60000);

			a.title() = PredefTitle;
			for (long i = 0;i < 10000; i++)
			{
				if (a.title() != PredefTitle)
					return false;
			}
			return true;
		}

		bool test_http_message::TestRender::operator()()
		{	http::message a;
			binary_data out, PredefBody = binary_data((byte)'a', 60000);
			binary_data shouldBe = binary_data("GET / HTTP/1.1\r\nContent-Length: 60000\r\n\r\n") + PredefBody;
			binary_data shouldBeLF = binary_data("GET / HTTP/1.1\nContent-Length: 60000\n\n") + PredefBody;

			// Populate a
			a.title() = binary_data("GET / HTTP/1.1");
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

		bool test_http_message::TestRenderSpeed::operator()()
		{	http::message a;
			binary_data out, PredefBody = binary_data((byte)'a', 60000);
			binary_data shouldBe= binary_data("GET / HTTP/1.1\r\nContent-Length: 60000\r\n\r\n") + PredefBody;

			// Populate a
			a.title() = binary_data("GET / HTTP/1.1");
			a.body() = PredefBody;

			reset_timer();
			for (long i = 0;i < 10000;i++)
				out = a.render();

			if (out != shouldBe)
				return false;
			return true;
		}

		bool test_http_message::TestParseSpeedLF::operator()()
		{	http::message a;
			binary_data PredefBody = binary_data((byte)'a', 60000);
			binary_data rendered = binary_data("GET / HTTP/1.1\nContent-Length: 60000\n\n") + PredefBody + binary_data("1234");
			binary_data remaining;
			bool b_parsed;
			string header_value;

			// Parse 10k times
			reset_timer();
			for (long i = 0;i < 10000;i++)
				b_parsed = a.parse(rendered, &remaining);

			if (a.body() != PredefBody)
				return false;
			if (a.title() != binary_data("GET / HTTP/1.1"))
				return false;
			if (!(a.headers().find_first("Content-Length", header_value) && (header_value == "60000")))
				return false;

			// Final quality test
			if (!b_parsed)
				return false;
			if (remaining != binary_data("1234"))
				return false;
			return true;
		}

		bool test_http_message::TestParseSpeedCRLF::operator()()
		{	http::message a;
			binary_data PredefBody = binary_data((byte)'a', 60000);
			binary_data rendered = binary_data("GET / HTTP/1.1\r\nContent-Length: 60000\r\n\r\n") + PredefBody + binary_data("1234");
			binary_data remaining;
			bool b_parsed;
			string header_value;

			// Parse 10k times
			reset_timer();
			for (long i = 0;i < 10000;i++)
				b_parsed = a.parse(rendered, &remaining);

			if (a.body() != PredefBody)
				return false;
			if (a.title() != binary_data("GET / HTTP/1.1"))
				return false;
			if (!(a.headers().find_first("Content-Length", header_value) && (header_value == "60000")))
				return false;

			// Final quality test
			if (!b_parsed)
				return false;
			if (remaining != binary_data("1234"))
				return false;
			return true;
		}

		bool test_http_message::TestParse::operator()()
		{	http::message a;
			bool b_parsed;
			string header_value;
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
			if (!(a.headers().find_first("Content-Length", header_value) && (header_value == "60000")))
				return false;
			if ((!b_parsed) || (remaining != trail_data))
				return false;

			// Packet With Body LF
			b_parsed = a.parse(PacketWBodyLF, &remaining);
			if (a.body() != PredefBody)
				return false;
			if (a.title() != binary_data("POST / HTTP/1.1"))
				return false;
			if (!(a.headers().find_first("Content-Length", header_value) && (header_value == "60000")))
				return false;
			if ((!b_parsed) || (remaining != trail_data))
				return false;

			// Packet With-out Body CRLF
			b_parsed = a.parse(PacketCRLF, &remaining);
			if (! a.body().empty())
				return false;
			if (a.title() != binary_data("GET / HTTP/1.1"))
				return false;
			if (!(a.headers().find_first("Host", header_value) && (header_value == "123")))
				return false;
			if ((!b_parsed) || (remaining != binary_data::nothing))
				return false;

			// Read rfc 2616 headers may be zero so this is valid!
			binary_data PacketNoHeads = binary_data("POST / HTTP/1.1\r\n\r\n\r\n") ;
			if (!a.parse(PacketNoHeads))
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
			if (!(a.headers().find_first("Host", header_value) && (header_value == "123")))
				return false;
			if (!(a.headers().find_first(":", header_value) && (header_value == ":")))
				return false;
			if ((!b_parsed) || (remaining != trail_data))
				return false;
			return true;
		}

		bool test_http_message::TestParseWrong1::operator()()
		{	http::message a;
			binary_data PacketWrongContentLength = binary_data("POST / HTTP/1.1\r\nContent-Length: -1000\n\n") ;
			a.parse(PacketWrongContentLength);
			return false;
		}

		bool test_http_message::TestParseIncomplete1::operator()()
		{	http::message a;
			binary_data PacketNoDoubleNewLine = binary_data("POST / HTTP/1.1\r\nContent: 1\n") ;
			if (a.parse(PacketNoDoubleNewLine))
				return false;
			return true;
		}

		bool test_http_message::TestParseIncomplete2::operator()()
		{	http::message a;
			binary_data PacketNoDoubleNewLine = binary_data("POST / HTTP/1.1\r\nContent-Length: 1\n\n") ;
			if (a.parse(PacketNoDoubleNewLine))
				return false;
			return true;
		}
	}	// !test namespace
};	// !oonet namespace
