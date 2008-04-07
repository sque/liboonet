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
		a.set("a", "1");
		a.set("b", "2");
		a.set("c", "3");

		http::headers_list b(a);

		if (b.size() != 3)
			return false;

		return true;
	}

	bool TestHTTPHeaders::TestCopyOperator::OnExecute()
	{	http::headers_list a;

		// Populate headers
		a.set("a", "1");
		a.set("b", "2");
		a.set("c", "3");

		http::headers_list b;
		b = a;

		if (b.size() != 3)
			return false;

		return true;
	}

	bool TestHTTPHeaders::TestSetHeaderWrong1::OnExecute()
	{	http::headers_list a;

		// Add empty header
		a.set("", "1");

		return false;
	}

	bool TestHTTPHeaders::TestSetHeader::OnExecute()
	{	http::headers_list a;

		// Add some headers
		a.set("a", "1");
		a.set("b", "2");
		a.set("c", "3");

		if (a.size() != 3)

		// Redefine a headers
		a.set("a", "123");

		if (a.size() != 3)
			return false;

		return true;
	}

	bool TestHTTPHeaders::TestSetHeaderSpeed::OnExecute()
	{	http::headers_list a;

		// Add some headers
		for(long i = 0;i < 100000;i++)
			a.set("a", "1");

		if (a.size() != 1)
			return false;

		return true;
	}

	bool TestHTTPHeaders::TestRemoveHeader::OnExecute()
	{	http::headers_list a;

		// Set some headers
		a.set("a", "1");
		a.set("b", "2");
		a.set("c", "3");

		if (a.size() != 3)
			return false;

		// Remove a header
		a.erase("a");

		// Check what headers are
		if (a.size() != 2)
			return false;

		// Remove a header
		a.erase("c");

		// Check what headers are
		if (a.size() != 1)
			return false;


		// Remove a header
		a.erase("b");

		// Check what headers are
		if (a.size() != 0)
			return false;

		return true;
	}

	bool TestHTTPHeaders::TestRemoveHeaderWrong1::OnExecute()
	{	http::headers_list a;

		a.erase("a");
		return false;
	}

	bool TestHTTPHeaders::TestRemoveHeaderWrong2::OnExecute()
	{	http::headers_list a;
		a.set("a", "1");
		a.erase("a");
		a.erase("a");
		return false;
	}

	bool TestHTTPHeaders::TestRemoveHeaderSpeed::OnExecute()
	{	http::headers_list a;
		string rendered;
		char cTmp[1024];
		for(long int i = 0; i < 100000;i++)
		{	sprintf(cTmp, "Longgggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg   header name - %ld", i);
			a.set(cTmp, "empty asdfad a");
		}

		ResetTimer();
		for(long i = 0;i < 100000;i++)
		{	sprintf(cTmp, "Longgggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg   header name - %ld", i);
			a.erase(cTmp);
		}

		return true;
	}

	bool TestHTTPHeaders::TestRender::OnExecute()
	{	http::headers_list a;
		binary_data rendered, shouldbe;

		a.set("a", "1");
		a.set("b", "2");
		a.set("b", "3");
		rendered = a.render();

		if (rendered != binary_data("a: 1\r\nb: 3"))
			return false;

		a.set("a", "1");
		a.set("b", "2");
		a.set("b", "3");
		rendered = a.render(http::const_lf);

		if (rendered != binary_data("a: 1\nb: 3"))
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

		a.set("a", "1");
		a.set("b", "3");

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
			a.set(cTmp, "empty asdfad a");
		}

		ResetTimer();
		for(long i = 0;i < 100000;i++)
			rendered = a.render(http::const_lf);

		return true;
	}

	bool TestHTTPHeaders::TestParse::OnExecute()
	{	string rendered = "a: 1\r\nbabalokos: 123123\r\nkoko: asd\r\n";
		string rendered2 = "mimikos: d\r\nvagelis: qwe\r\nolalola:123\r\n";
		string rendered3 = "mimikos : d\r\nvagelis   : qwe\r\nolalola :123\r\n";
		string renderedLF = "mimikos: d\nvagelis: qwe\nolalola: 123\r\n";
		string renderedMixed1 = "mimikos: d\r\nvagelis: qwe\nolalola: 123\r\n";
		string renderedMixed2 = "mimikos: d\nvagelis: qwe\r\nolalola: 123\r\n";
		string renderedMixedComplete = "mimikos: d\nvagelis: qwe\r\nolalola: 123\r\n\n";
		http::headers_list a;
		size_t ret_value;

		// Test with CRLF
		ret_value =a.parse(rendered);
		if (a.size() != 3)
			return false;
		if (a.get("a") != "1")
			return false;
		if (a.get("babalokos") != "123123")
			return false;
		if (a.get("koko") != "asd")
			return false;
		if (ret_value != binary_data::npos)
			return false;

		// Test with CRLF in same object
		ret_value = a.parse(rendered2);
		if (a.size() != 3)
			return false;
		if (a.get("mimikos") != "d")
			return false;
		if (a.get("vagelis") != "qwe")
			return false;
		if (a.get("olalola") != "123")
			return false;
		if (ret_value != binary_data::npos)
			return false;

		// Test with CRLF in same object
		ret_value = a.parse(rendered3);
		if (a.size() != 3)
			return false;
		if (a.get("mimikos") != "d")
			return false;
		if (a.get("vagelis") != "qwe")
			return false;
		if (a.get("olalola") != "123")
			return false;
		if (ret_value != binary_data::npos)
			return false;

		// Test with LF in same object
		ret_value = a.parse(renderedLF);
		if (a.size() != 3)
			return false;
		if (a.get("mimikos") != "d")
			return false;
		if (a.get("vagelis") != "qwe")
			return false;
		if (a.get("olalola") != "123")
			return false;
		if (ret_value != binary_data::npos)
			return false;

		// Test with mixed in same object
		ret_value = a.parse(renderedMixed1);
		if (a.size() != 3)
			return false;
		if (a.get("mimikos") != "d")
			return false;
		if (a.get("vagelis") != "qwe")
			return false;
		if (a.get("olalola") != "123")
			return false;
		if (ret_value != binary_data::npos)
			return false;

		// Test with mixed in same object
		ret_value = a.parse(renderedMixed2);
		if (a.size() != 3)
			return false;
		if (a.get("mimikos") != "d")
			return false;
		if (a.get("vagelis") != "qwe")
			return false;
		if (a.get("olalola") != "123")
			return false;
		if (ret_value != binary_data::npos)
			return false;

		// Test with mixed and complete
		ret_value = a.parse(renderedMixedComplete);
		if (a.size() != 3)
			return false;
		if (a.get("mimikos") != "d")
			return false;
		if (a.get("vagelis") != "qwe")
			return false;
		if (a.get("olalola") != "123")
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
	{	string rendered = "asdkfalsdkfasdf\nsadf";
		http::headers_list a;

		a.parse(rendered);
		return false;
	}

	bool TestHTTPHeaders::TestParseSpeed100k::OnExecute()
	{	http::headers_list a;
		string rendered;

		rendered = "a: 1\r\nbabalokos:    123123\r\nkoko: asd";

		ResetTimer();
		for(long i = 0;i < 100000; i++)
			a.parse(rendered);

		return true;
	}

	bool TestHTTPHeaders::TestSmartNewLineQuality::OnExecute()
	{	/*string text_splitted_1 = "lalala\r\nadfad\nasdfadsf\r";
		string text_splitted_2 = "koukouroukou\r\r\nadfs\ntest";
		string text_splitted_3 = "\r\ntest\r\n";
		string text_splitted_4 = "\ntest\r\n";
		string text_splitted_5 = "\n\n";
		string text_splitted_6 = "\r\n";
		string text_splitted_7 = "test\r\n";
		string text_splitted_8 = "test\n";
		string text_splitted_9 = "test\r";
		string nl;
		size_t offset;

		offset = http::_find_smart_new_line(text_splitted_1, nl);
		if ((offset != 6) || (nl != "\r\n"))
			return false;

		offset = http::_find_smart_new_line(text_splitted_2, nl);
		if ((offset != 13) || (nl != "\r\n"))
			return false;

		offset = http::_find_smart_new_line(text_splitted_3, nl);
		if ((offset != 0) || (nl != "\r\n"))
			return false;

		offset = http::_find_smart_new_line(text_splitted_4, nl);
		if ((offset != 0) || (nl != "\n"))
			return false;

		offset = http::_find_smart_new_line(text_splitted_5, nl);
		if ((offset != 0) || (nl != "\n"))
			return false;

		offset = http::_find_smart_new_line(text_splitted_6, nl);
		if ((offset != 0) || (nl != "\r\n"))
			return false;

		offset = http::_find_smart_new_line(text_splitted_7, nl);
		if ((offset != 4) || (nl != "\r\n"))

			return false;

		offset = http::_find_smart_new_line(text_splitted_8, nl);
		if ((offset != 4) || (nl != "\n"))
			return false;

		offset = http::_find_smart_new_line(text_splitted_9, nl);
		if (offset != string::npos)
			return false;*/

		return true;
	}

	bool TestHTTPHeaders::TestSmartNewLineSpeedCRLF::OnExecute()
	{	/*string text_splitted;
		string nl;
		size_t offset;

		// Create text
		for (long i = 0; i < 100; i++)
			text_splitted += "looooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooong";
		text_splitted += "\r\n";

		// Measure
		ResetTimer();
		for(long i = 0; i < 10000; i ++)
		{
			offset = http::_find_smart_new_line(text_splitted, nl);
		}

		if ((offset != 9200) || (nl != "\r\n"))
			return false;*/

		return true;
	}

	bool TestHTTPHeaders::TestSmartNewLineSpeedLF::OnExecute()
	{	/*string text_splitted;
		string nl;
		size_t offset;

		// Create text
		for (long i = 0; i < 100; i++)
			text_splitted += "looooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooong";
		text_splitted += "\n";

		// Measure
		ResetTimer();
		for(long i = 0; i < 10000; i ++)
		{
			offset = http::_find_smart_new_line(text_splitted, nl);
		}

		if ((offset != 9200) || (nl != "\n"))
			return false;*/

		return true;
	}
};	// !oonet namespace
