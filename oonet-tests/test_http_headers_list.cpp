#include "test_http_headers_list.hpp"
#include <oonet/http/headers_list.hpp>
namespace oonet
{
	namespace test
	{
		test_http_headers_list theHTTPHeaders;

		bool test_http_headers_list::TestCtor::operator()()
		{	http::headers_list a;

			// Must be empty
			if (a.size() != 0)
				return false;

			return true;
		}

		bool test_http_headers_list::TestCopyCtor::operator()()
		{	http::headers_list a;

			// Populate headers
			a.add("a", "1");
			a.add("b", "2");
			a.add("c", "3");

			http::headers_list b(a);

			if (b.size() != 3)
				return false;

			return true;
		}

		bool test_http_headers_list::TestCopyOperator::operator()()
		{	http::headers_list a;

			// Populate headers
			a.add("a", "1");
			a.add("b", "2");
			a.add("c", "3");

			http::headers_list b;
			b = a;

			if (b.size() != 3)
				return false;

			return true;
		}

		bool test_http_headers_list::TestSetHeaderWrong1::operator()()
		{	http::headers_list a;

			// Add empty header
			a.add("", "1");

			return false;
		}

		bool test_http_headers_list::TestSetHeader::operator()()
		{	http::headers_list a;

			// Add some headers
			a.add("a", "1");
			a.add("b", "2");
			a.add("c", "3");

			if (a.size() != 3)

			// Redefine a headers
			a.add("a", "123");

			if (a.size() != 3)
				return false;

			return true;
		}

		bool test_http_headers_list::TestSetHeaderSpeed::operator()()
		{	http::headers_list a;

			// Add some headers
			for(long i = 0;i < 10000;i++)
				a.add("a", "1");

			if (a.size() != 10000)
				return false;

			return true;
		}

		bool test_http_headers_list::TestRemoveHeader::operator()()
		{	http::headers_list a;

			// Set some headers
			a.add("a", "1");
			a.add("b", "2");
			a.add("c", "3");

			if (a.size() != 3)
				return false;

			// Remove a header
			a.erase(a.find("a"));

			// Check what headers are
			if (a.size() != 2)
				return false;

			// Remove a header
			a.erase(a.find("c"));

			// Check what headers are
			if (a.size() != 1)
				return false;


			// Remove a header
			a.erase(a.find("b"));

			// Check what headers are
			if (a.size() != 0)
				return false;

			return true;
		}

		bool test_http_headers_list::TestRemoveHeaderSpeed::operator()()
		{	http::headers_list a;
			string rendered;
			char cTmp[1024];
			for(long int i = 0; i < 100000;i++)
			{	sprintf(cTmp, "Longgggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg   header name - %ld", i);
				a.add(cTmp, "empty asdfad a");
			}

			reset_timer();
			for(long i = 0;i < 100000;i++)
			{	sprintf(cTmp, "Longgggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg   header name - %ld", i);
				a.erase(a.find(cTmp));
			}

			return true;
		}

		bool test_http_headers_list::TestRender::operator()()
		{	http::headers_list a;
			binary_data rendered, shouldbe;

			a.add("a", "1");
			a.add("b", "2");
			a.add("b", "3");
			rendered = a.render();

			if (rendered != cmem_ref("a: 1\r\nb: 2\r\nb: 3"))
				return false;

			a.add("a", "1");
			a.add("b", "2");
			a.add("b", "3");
			rendered = a.render(http::const_lf);

			//printf("-%s-", rendered.to_string().c_str());
			if (rendered != cmem_ref("a: 1\nb: 2\nb: 3\na: 1\nb: 2\nb: 3"))
				return false;

			a = http::headers_list();
			rendered = a.render(http::const_lf);

			if (rendered != binary_data::nothing)
				return false;

			return true;
		}

		bool test_http_headers_list::TestRenderSpeed100k_2::operator()()
		{	http::headers_list a;
			binary_data rendered;

			a.add("a", "1");
			a.add("b", "3");

			for(long i = 0;i < 100000;i++)
				rendered = a.render(http::const_lf);

			if (rendered != cmem_ref("a: 1\nb: 3"))
				return false;

			return true;
		}

		bool test_http_headers_list::TestRenderSpeed100k_100::operator()()
		{	http::headers_list a;
			binary_data rendered;
			char cTmp[100];
			for(int i = 0; i < 100;i++)
			{	sprintf(cTmp, "header name - %d", i);
				a.add(cTmp, "empty asdfad a");
			}

			reset_timer();
			for(long i = 0;i < 100000;i++)
				rendered = a.render(http::const_lf);

			return true;
		}

		bool test_http_headers_list::TestParse::operator()()
		{	binary_data rendered = cmem_ref("a: 1\r\nbabalokos: 123123\r\nkoko: asd\r\n");
			binary_data rendered2 = cmem_ref("mimikos: d\r\nvagelis: qwe\r\nolalola:123\r\n");
			binary_data rendered3 = cmem_ref("mimikos : d\r\nvagelis   : qwe\r\nolalola :123\r\n");
			binary_data renderedLF = cmem_ref("mimikos: d\nvagelis: qwe\nolalola: 123\r\n");
			binary_data renderedMixed1 = cmem_ref("mimikos: d\r\nvagelis: qwe\nolalola: 123\r\n");
			binary_data renderedMixed2 = cmem_ref("mimikos: d\nvagelis: qwe\r\nolalola: 123\r\n");
			binary_data renderedMixedComplete = cmem_ref("mimikos: d\nvagelis: qwe\r\nolalola: 123\r\n\n");
			string header_value;
			http::headers_list a;
			size_t ret_value;

			// Test with CRLF
			ret_value =a.parse(rendered);
			if (a.size() != 3)
				return false;
			if (!(a.find_first("a", header_value) && (header_value == "1")))
				return false;
			if (!(a.find_first("babalokos", header_value) && (header_value == "123123")))
				return false;
			if (!(a.find_first("koko", header_value) && (header_value == "asd")))
				return false;
			if (ret_value != binary_data::npos)
				return false;

			// Test with CRLF in same object
			ret_value = a.parse(rendered2);
			if (a.size() != 3)
				return false;
			if (!(a.find_first("mimikos", header_value) && (header_value == "d")))
				return false;
			if (!(a.find_first("vagelis", header_value) && (header_value == "qwe")))
				return false;
			if (!(a.find_first("olalola", header_value) && (header_value == "123")))
				return false;
			if (ret_value != binary_data::npos)
				return false;

			// Test with CRLF in same object
			ret_value = a.parse(rendered3);
			if (a.size() != 3)
				return false;
			if (!(a.find_first("mimikos ", header_value) && (header_value == "d")))
				return false;
			if (!(a.find_first("vagelis   ", header_value) && (header_value == "qwe")))
				return false;
			if (!(a.find_first("olalola ", header_value) && (header_value == "123")))
				return false;
			if (ret_value != binary_data::npos)
				return false;

			// Test with LF in same object
			ret_value = a.parse(renderedLF);
			if (a.size() != 3)
			if (!(a.find_first("mimikos", header_value) && (header_value == "d")))
				return false;
			if (!(a.find_first("vagelis", header_value) && (header_value == "qwe")))
				return false;
			if (!(a.find_first("olalola", header_value) && (header_value == "123")))
				return false;
			if (ret_value != binary_data::npos)
				return false;

			// Test with mixed in same object
			ret_value = a.parse(renderedMixed1);
			if (a.size() != 3)
				return false;
			if (!(a.find_first("mimikos", header_value) && (header_value == "d")))
				return false;
			if (!(a.find_first("vagelis", header_value) && (header_value == "qwe")))
				return false;
			if (!(a.find_first("olalola", header_value) && (header_value == "123")))
				return false;
			if (ret_value != binary_data::npos)
				return false;

			// Test with mixed in same object
			ret_value = a.parse(renderedMixed2);
			if (a.size() != 3)
				return false;
			if (!(a.find_first("mimikos", header_value) && (header_value == "d")))
				return false;
			if (!(a.find_first("vagelis", header_value) && (header_value == "qwe")))
				return false;
			if (!(a.find_first("olalola", header_value) && (header_value == "123")))
				return false;
			if (ret_value != binary_data::npos)
				return false;

			// Test with mixed and complete
			ret_value = a.parse(renderedMixedComplete);
			if (a.size() != 3)
				return false;
			if (!(a.find_first("mimikos", header_value) && (header_value == "d")))
				return false;
			if (!(a.find_first("vagelis", header_value) && (header_value == "qwe")))
				return false;
			if (!(a.find_first("olalola", header_value) && (header_value == "123")))
				return false;
			if (ret_value != renderedMixedComplete.size())
				return false;

			// Parse an empty string
			a.clear();
			ret_value = a.parse(binary_data::nothing);
			if (a.size() != 0)
				return false;
			if (ret_value != binary_data::npos)
				return false;

			// As per rfc 2616 http://www.w3.org/Protocols/rfc2616/rfc2616-sec4.html#sec4.2
			// Headers may be zero!
			a.clear();
			if (a.parse(http::const_crlf) != 2)
				return false;
			if (a.size() != 0)
				return false;

			return true;
		}

		bool test_http_headers_list::TestParseWrong1::operator()()
		{	binary_data rendered = cmem_ref("asdkfalsdkfasdf\nsadf");
			http::headers_list a;

			a.parse(rendered);
			return false;
		}

		bool test_http_headers_list::TestParseSpeed100k::operator()()
		{	http::headers_list a;
			binary_data rendered = cmem_ref("a: 1\r\nbabalokos:    123123\r\nkoko: asd");

			reset_timer();
			for(long i = 0;i < 100000; i++)
				a.parse(rendered);

			return true;
		}

		bool test_http_headers_list::TestSmartNewLineQuality::operator()()
		{	binary_data text_splitted_1 = cmem_ref("lalala\r\nadfad\nasdfadsf\r");
			binary_data text_splitted_2 = cmem_ref("koukouroukou\r\r\nadfs\ntest");
			binary_data text_splitted_3 = cmem_ref("\r\ntest\r\n");
			binary_data text_splitted_4 = cmem_ref("\ntest\r\n");
			binary_data text_splitted_5 = cmem_ref("\n\n");
			binary_data text_splitted_6 = cmem_ref("\r\n");
			binary_data text_splitted_7 = cmem_ref("test\r\n");
			binary_data text_splitted_8 = cmem_ref("test\n");
			binary_data text_splitted_9 = cmem_ref("test\r");
			binary_data nl;
			size_t offset;

			offset = http::_smart_find_new_line(text_splitted_1, nl);
			if ((offset != 6) || (nl != http::const_crlf))
				return false;

			offset = http::_smart_find_new_line(text_splitted_2, nl);
			if ((offset != 13) || (nl != http::const_crlf))
				return false;

			offset = http::_smart_find_new_line(text_splitted_3, nl);
			if ((offset != 0) || (nl != http::const_crlf))
				return false;

			offset = http::_smart_find_new_line(text_splitted_4, nl);
			if ((offset != 0) || (nl != http::const_lf))
				return false;

			offset = http::_smart_find_new_line(text_splitted_5, nl);
			if ((offset != 0) || (nl != http::const_lf))
				return false;

			offset = http::_smart_find_new_line(text_splitted_6, nl);
			if ((offset != 0) || (nl != http::const_crlf))
				return false;

			offset = http::_smart_find_new_line(text_splitted_7, nl);
			if ((offset != 4) || (nl != http::const_crlf))

				return false;

			offset = http::_smart_find_new_line(text_splitted_8, nl);
			if ((offset != 4) || (nl != http::const_lf))
				return false;

			offset = http::_smart_find_new_line(text_splitted_9, nl);
			if (offset != string::npos)
				return false;

			return true;
		}

		bool test_http_headers_list::TestSmartNewLineSpeedCRLF::operator()()
		{	binary_data text_splitted;
			binary_data nl;
			size_t offset;

			// Create text
			for (long i = 0; i < 100; i++)
				text_splitted += cmem_ref("looooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooong");
			text_splitted += cmem_ref("\r\n");

			// Measure
			reset_timer();
			for(long i = 0; i < 100000; i ++)
			{
				offset = http::_smart_find_new_line(text_splitted, nl);
			}

			if ((offset != 9200) || (nl != http::const_crlf))
				return false;

			return true;
		}

		bool test_http_headers_list::TestSmartNewLineSpeedLF::operator()()
		{	binary_data text_splitted;
			binary_data nl;
			size_t offset;

			// Create text
			for (long i = 0; i < 100; i++)
				text_splitted += cmem_ref("looooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooong");
			text_splitted += cmem_ref("\n");

			// Measure
			reset_timer();
			for(long i = 0; i < 100000; i ++)
			{
				offset = http::_smart_find_new_line(text_splitted, nl);
			}

			if ((offset != 9200) || (nl != http::const_lf))
				return false;

			return true;
		}
	}	// !test namespace
};	// !oonet namespace
