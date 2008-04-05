#include "TestHTTPHeaders.h"
#include "Http/Headers.h"
namespace oonet
{
	TestHTTPHeaders theHTTPHeaders;

	bool TestHTTPHeaders::TestCtor::OnExecute()
	{	http::Headers a;

		// Must be empty
		if (a.getSTLMap().size() != 0)
			return false;

		return true;
	}

	bool TestHTTPHeaders::TestCopyCtor::OnExecute()
	{	http::Headers a;

		// Populate headers
		a.setHeader("a", "1");
		a.setHeader("b", "2");
		a.setHeader("c", "3");

		http::Headers b(a);

		if (b.getSTLMap().size() != 3)
			return false;
		if (b.getSTLMap().find("a")->second != "1")
			return false;
		if (b.getSTLMap().find("b")->second != "2")
			return false;
		if (b.getSTLMap().find("c")->second != "3")
			return false;

		return true;
	}

	bool TestHTTPHeaders::TestCopyOperator::OnExecute()
	{	http::Headers a;

		// Populate headers
		a.setHeader("a", "1");
		a.setHeader("b", "2");
		a.setHeader("c", "3");

		http::Headers b;
		b = a;

		if (b.getSTLMap().size() != 3)
			return false;
		if (b.getSTLMap().find("a")->second != "1")
			return false;
		if (b.getSTLMap().find("b")->second != "2")
			return false;
		if (b.getSTLMap().find("c")->second != "3")
			return false;

		return true;
	}

	bool TestHTTPHeaders::TestSetHeaderWrong1::OnExecute()
	{	http::Headers a;

		// Add empty header
		a.setHeader("", "1");

		return false;
	}

	bool TestHTTPHeaders::TestSetHeader::OnExecute()
	{	http::Headers a;

		// Add some headers
		a.setHeader("a", "1");
		a.setHeader("b", "2");
		a.setHeader("c", "3");

		if (a.getSTLMap().size() != 3)
			return false;
		if (a.getSTLMap().find("a")->second != "1")
			return false;
		if (a.getSTLMap().find("b")->second != "2")
			return false;
		if (a.getSTLMap().find("c")->second != "3")
			return false;

		// Redefine a headers
		a.setHeader("a", "123");

		if (a.getSTLMap().size() != 3)
			return false;
		if (a.getSTLMap().find("a")->second != "123")
			return false;
		if (a.getSTLMap().find("b")->second != "2")
			return false;
		if (a.getSTLMap().find("c")->second != "3")
			return false;

		return true;
	}

	bool TestHTTPHeaders::TestSetHeaderSpeed::OnExecute()
	{	http::Headers a;

		// Add some headers
		for(long i = 0;i < 100000;i++)
			a.setHeader("a", "1");

		if (a.getSTLMap().size() != 1)
			return false;
		if (a.getSTLMap().find("a")->second != "1")
			return false;
		return true;
	}

	bool TestHTTPHeaders::TestRemoveHeader::OnExecute()
	{	http::Headers a;

		// Set some headers
		a.setHeader("a", "1");
		a.setHeader("b", "2");
		a.setHeader("c", "3");

		if (a.getSTLMap().size() != 3)
			return false;

		// Remove a header
		a.removeHeader("a");

		// Check what headers are
		if (a.getSTLMap().size() != 2)
			return false;
		if (a.getSTLMap().find("b")->second != "2")
			return false;
		if (a.getSTLMap().find("c")->second != "3")
			return false;

		// Remove a header
		a.removeHeader("c");

		// Check what headers are
		if (a.getSTLMap().size() != 1)
			return false;
		if (a.getSTLMap().find("b")->second != "2")
			return false;

		// Remove a header
		a.removeHeader("b");

		// Check what headers are
		if (a.getSTLMap().size() != 0)
			return false;

		return true;
	}

	bool TestHTTPHeaders::TestRemoveHeaderWrong1::OnExecute()
	{	http::Headers a;

		a.removeHeader("a");
		return false;
	}

	bool TestHTTPHeaders::TestRemoveHeaderWrong2::OnExecute()
	{	http::Headers a;
		a.setHeader("a", "1");
		a.removeHeader("a");
		a.removeHeader("a");
		return false;
	}

	bool TestHTTPHeaders::TestRemoveHeaderSpeed::OnExecute()
	{	http::Headers a;
		string rendered;
		char cTmp[1024];
		for(long int i = 0; i < 100000;i++)
		{	sprintf(cTmp, "Longgggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg   header name - %ld", i);
			a.setHeader(cTmp, "empty asdfad a");
		}

		ResetTimer();
		for(long i = 0;i < 100000;i++)
		{	sprintf(cTmp, "Longgggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg   header name - %ld", i);
			a.removeHeader(cTmp);
		}

		return true;
	}

	bool TestHTTPHeaders::TestRender::OnExecute()
	{	http::Headers a;
		string rendered, shouldbe;

		a.setHeader("a", "1");
		a.setHeader("b", "2");
		a.setHeader("b", "3");
		rendered = a.render();

		if (rendered != "a: 1\r\nb: 3")
			return false;

		a.setHeader("a", "1");
		a.setHeader("b", "2");
		a.setHeader("b", "3");
		rendered = a.render("\n");

		if (rendered != "a: 1\nb: 3")
			return false;

		a = http::Headers();
		rendered = a.render("\n");

		if (rendered != "")
			return false;

		return true;
	}

	bool TestHTTPHeaders::TestRenderSpeed100k_2::OnExecute()
	{	http::Headers a;
		string rendered;

		a.setHeader("a", "1");
		a.setHeader("b", "3");

		for(long i = 0;i < 100000;i++)
			rendered = a.render("\n");

		if (rendered != "a: 1\nb: 3")
			return false;

		return true;
	}

	bool TestHTTPHeaders::TestRenderSpeed100k_100::OnExecute()
	{	http::Headers a;
		string rendered;
		char cTmp[100];
		for(int i = 0; i < 100;i++)
		{	sprintf(cTmp, "header name - %d", i);
			a.setHeader(cTmp, "empty asdfad a");
		}

		ResetTimer();
		for(long i = 0;i < 100000;i++)
			rendered = a.render("\n");

		return true;
	}

	bool TestHTTPHeaders::TestParse::OnExecute()
	{	string rendered = "a: 1\r\nbabalokos: 123123\r\nkoko: asd";
		string rendered2 = "mimikos: d\r\nvagelis: qwe\r\nolalola:123";
		string rendered3 = "mimikos : d\r\nvagelis   : qwe\r\nolalola :123";
		string renderedLF = "mimikos: d\nvagelis: qwe\nolalola: 123";
		string renderedMixed1 = "mimikos: d\r\nvagelis: qwe\nolalola: 123";
		string renderedMixed2 = "mimikos: d\nvagelis: qwe\r\nolalola: 123";
		http::Headers a;

		// Test with CRLF
		a.parse(rendered);
		if (a.getSTLMap().size() != 3)
			return false;
		if (a.getSTLMap().find("a")->second != "1")
			return false;
		if (a.getSTLMap().find("babalokos")->second != "123123")
			return false;
		if (a.getSTLMap().find("koko")->second != "asd")
			return false;

		// Test with CRLF in same object
		a.parse(rendered2);
		if (a.getSTLMap().size() != 3)
			return false;
		if (a.getSTLMap().find("mimikos")->second != "d")
			return false;
		if (a.getSTLMap().find("vagelis")->second != "qwe")
			return false;
		if (a.getSTLMap().find("olalola")->second != "123")
			return false;

		// Test with CRLF in same object
		a.parse(rendered3);
		if (a.getSTLMap().size() != 3)
			return false;
		if (a.getSTLMap().find("mimikos")->second != "d")
			return false;
		if (a.getSTLMap().find("vagelis")->second != "qwe")
			return false;
		if (a.getSTLMap().find("olalola")->second != "123")
			return false;

		// Test with LF in same object
		a.parse(renderedLF);
		if (a.getSTLMap().size() != 3)
			return false;
		if (a.getSTLMap().find("mimikos")->second != "d")
			return false;
		if (a.getSTLMap().find("vagelis")->second != "qwe")
			return false;
		if (a.getSTLMap().find("olalola")->second != "123")
			return false;

		// Test with mixed in same object
		a.parse(renderedMixed1);
		if (a.getSTLMap().size() != 3)
			return false;
		if (a.getSTLMap().find("mimikos")->second != "d")
			return false;
		if (a.getSTLMap().find("vagelis")->second != "qwe")
			return false;
		if (a.getSTLMap().find("olalola")->second != "123")
			return false;

		// Test with mixed in same object
		a.parse(renderedMixed2);
		if (a.getSTLMap().size() != 3)
			return false;
		if (a.getSTLMap().find("mimikos")->second != "d")
			return false;
		if (a.getSTLMap().find("vagelis")->second != "qwe")
			return false;
		if (a.getSTLMap().find("olalola")->second != "123")
			return false;

		// Parse an empty string
		a.parse("");
		if (a.getSTLMap().size() != 0)
			return false;

		return true;
	}

	bool TestHTTPHeaders::TestParseWrong1::OnExecute()
	{	string rendered = "asdkfalsdkfasdf\nsadf";
		http::Headers a;

		a.parse(rendered);
		return false;
	}

	bool TestHTTPHeaders::TestParseWrong2::OnExecute()
	{	http::Headers a;

		// Parse an empty new line (LF)
		a.parse("\n");
		if (a.getSTLMap().size() != 0)
			return false;
		return false;
	}

	bool TestHTTPHeaders::TestParseSpeed100k::OnExecute()
	{	http::Headers a;
		string rendered;

		rendered = "a: 1\r\nbabalokos:    123123\r\nkoko: asd";

		ResetTimer();
		for(long i = 0;i < 100000; i++)
			a.parse(rendered);

		return true;
	}

	bool TestHTTPHeaders::TestSmartNewLineQuality::OnExecute()
	{	string text_splitted_1 = "lalala\r\nadfad\nasdfadsf\r";
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
			return false;

		return true;
	}

	bool TestHTTPHeaders::TestSmartNewLineSpeedCRLF::OnExecute()
	{	string text_splitted;
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
			return false;

		return true;
	}

	bool TestHTTPHeaders::TestSmartNewLineSpeedLF::OnExecute()
	{	string text_splitted;
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
			return false;

		return true;
	}
};	// !oonet namespace
