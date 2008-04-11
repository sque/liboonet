#include "test_http_headers_list.hpp"
#include "http/headers_list.hpp"
namespace oonet
{
	TestHTTPHeaders theHTTPHeaders;

	bool TestHTTPHeaders::TestCtor::OnExecute()
	{	http::headers_list a;

		// Must be empty
		if (a.size() != 0)
			return false;

		return true;
	}

	bool TestHTTPHeaders::TestCopyCtor::OnExecute()
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

	bool TestHTTPHeaders::TestCopyOperator::OnExecute()
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

	bool TestHTTPHeaders::TestSetHeaderWrong1::OnExecute()
	{	http::headers_list a;

		// Add empty header
		a.add("", "1");

		return false;
	}

	bool TestHTTPHeaders::TestSetHeader::OnExecute()
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

	bool TestHTTPHeaders::TestSetHeaderSpeed::OnExecute()
	{	http::headers_list a;

		// Add some headers
		for(long i = 0;i < 10000;i++)
			a.add("a", "1");

		if (a.size() != 10000)
			return false;

		return true;
	}

	bool TestHTTPHeaders::TestRemoveHeader::OnExecute()
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

	bool TestHTTPHeaders::TestRemoveHeaderSpeed::OnExecute()
	{	http::headers_list a;
		string rendered;
		char cTmp[1024];
		for(long int i = 0; i < 100000;i++)
		{	sprintf(cTmp, "Longgggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg   header name - %ld", i);
			a.add(cTmp, "empty asdfad a");
		}

		ResetTimer();
		for(long i = 0;i < 100000;i++)
		{	sprintf(cTmp, "Longgggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg   header name - %ld", i);
			a.erase(a.find(cTmp));
		}

		return true;
	}

	bool TestHTTPHeaders::TestRender::OnExecute()
	{	http::headers_list a;
		binary_data rendered, shouldbe;

		a.add("a", "1");
		a.add("b", "2");
		a.add("b", "3");
		rendered = a.render();

		if (rendered != binary_data("a: 1\r\nb: 2\r\nb: 3"))
			return false;

		a.add("a", "1");
		a.add("b", "2");
		a.add("b", "3");
		rendered = a.render(http::const_lf);

		//printf("-%s-", rendered.to_string().c_str());
		if (rendered != binary_data("a: 1\nb: 2\nb: 3\na: 1\nb: 2\nb: 3"))
			return false;

		a = http::headers_list();
		rendered = a.render(http::const_lf);

		if (rendered != binary_data::nothing)
			return false;

		return true;
	}

	bool TestHTTPHeaders::TestRenderSpeed100k_2::OnExecute()
	{	http::headers_list a;
		binary_data rendered;

		a.add("a", "1");
		a.add("b", "3");

		for(long i = 0;i < 100000;i++)
			rendered = a.render(http::const_lf);

		if (rendered != binary_data("a: 1\nb: 3"))
			return false;

		return true;
	}

	bool TestHTTPHeaders::TestRenderSpeed100k_100::OnExecute()
	{	http::headers_list a;
		binary_data rendered;
		char cTmp[100];
		for(int i = 0; i < 100;i++)
		{	sprintf(cTmp, "header name - %d", i);
			a.add(cTmp, "empty asdfad a");
		}

		ResetTimer();
		for(long i = 0;i < 100000;i++)
			rendered = a.render(http::const_lf);

		return true;
	}

	bool TestHTTPHeaders::TestParse::OnExecute()
	{	binary_data rendered = binary_data("a: 1\r\nbabalokos: 123123\r\nkoko: asd\r\n");
		binary_data rendered2 = binary_data("mimikos: d\r\nvagelis: qwe\r\nolalola:123\r\n");
		binary_data rendered3 = binary_data("mimikos : d\r\nvagelis   : qwe\r\nolalola :123\r\n");
		binary_data renderedLF = binary_data("mimikos: d\nvagelis: qwe\nolalola: 123\r\n");
		binary_data renderedMixed1 = binary_data("mimikos: d\r\nvagelis: qwe\nolalola: 123\r\n");
		binary_data renderedMixed2 = binary_data("mimikos: d\nvagelis: qwe\r\nolalola: 123\r\n");
		binary_data renderedMixedComplete = binary_data("mimikos: d\nvagelis: qwe\r\nolalola: 123\r\n\n");
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

	bool TestHTTPHeaders::TestParseWrong1::OnExecute()
	{	binary_data rendered = binary_data("asdkfalsdkfasdf\nsadf");
		http::headers_list a;

		a.parse(rendered);
		return false;
	}

	bool TestHTTPHeaders::TestParseSpeed100k::OnExecute()
	{	http::headers_list a;
		binary_data rendered = binary_data("a: 1\r\nbabalokos:    123123\r\nkoko: asd");

		ResetTimer();
		for(long i = 0;i < 100000; i++)
			a.parse(rendered);

		return true;
	}

	bool TestHTTPHeaders::TestSmartNewLineQuality::OnExecute()
	{	binary_data text_splitted_1 = binary_data("lalala\r\nadfad\nasdfadsf\r");
		binary_data text_splitted_2 = binary_data("koukouroukou\r\r\nadfs\ntest");
		binary_data text_splitted_3 = binary_data("\r\ntest\r\n");
		binary_data text_splitted_4 = binary_data("\ntest\r\n");
		binary_data text_splitted_5 = binary_data("\n\n");
		binary_data text_splitted_6 = binary_data("\r\n");
		binary_data text_splitted_7 = binary_data("test\r\n");
		binary_data text_splitted_8 = binary_data("test\n");
		binary_data text_splitted_9 = binary_data("test\r");
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

	bool TestHTTPHeaders::TestSmartNewLineSpeedCRLF::OnExecute()
	{	binary_data text_splitted;
		binary_data nl;
		size_t offset;

		// Create text
		for (long i = 0; i < 100; i++)
			text_splitted += binary_data("looooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooong");
		text_splitted += binary_data("\r\n");

		// Measure
		ResetTimer();
		for(long i = 0; i < 100000; i ++)
		{
			offset = http::_smart_find_new_line(text_splitted, nl);
		}

		if ((offset != 9200) || (nl != http::const_crlf))
			return false;

		return true;
	}

	bool TestHTTPHeaders::TestSmartNewLineSpeedLF::OnExecute()
	{	binary_data text_splitted;
		binary_data nl;
		size_t offset;

		// Create text
		for (long i = 0; i < 100; i++)
			text_splitted += binary_data("looooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooong");
		text_splitted += binary_data("\n");

		// Measure
		ResetTimer();
		for(long i = 0; i < 100000; i ++)
		{
			offset = http::_smart_find_new_line(text_splitted, nl);
		}

		if ((offset != 9200) || (nl != http::const_lf))
			return false;

		return true;
	}
};	// !oonet namespace
