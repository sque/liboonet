#include "TestStringConverter.h"
#include "string_converter.h"

namespace oonet
{
	TestStringConverter theTestStringConverter;

	bool TestStringConverter::TestCtor::OnExecute()
	{	StringConverter ansitest("Test Ansi");
		StringConverter widetest(L"Test Wide");
		printf("Size of wchar_t %u\n", sizeof(wchar_t));
		return true;
	}

	bool TestStringConverter::TestConvWideEnglish::OnExecute()
	{	StringConverter ansitest("Test Ansi");
		wstring widetext = ansitest.toWide();
		char hextext[1024] = "", hexchunk[10] = "";

		// Convert to binary data and check data
		wstring::iterator it;
		for (it = widetext.begin();it != widetext.end();it++)
		{
			_snprintf(hexchunk, 10, "%04X", *it);
			strcat(hextext,hexchunk);
		}
		//printf("%s", hextext);
		if (string(hextext) != string("005400650073007400200041006E00730069"))
			return false;
		return true;
	}

	bool TestStringConverter::TestConvWideGreek::OnExecute()
	{	StringConverter ansitest("Test ÅëëçíéêÜ");
		wstring widetext = ansitest.toWide();
		char hextext[1024] = "", hexchunk[10] = "";

		// Convert to binary data and check data
		wstring::iterator it;
		for (it = widetext.begin();it != widetext.end();it++)
		{
			_snprintf(hexchunk, 10, "%04X", *it);
			strcat(hextext,hexchunk);
		}
		//printf("%s", hextext);
		if (string(hextext) != string("00540065007300740020253C0388038803CD038A03CE03862584"))
			return false;
		return true;
	}

	bool TestStringConverter::TestConvWideFrench::OnExecute()
	{	StringConverter ansitest("Test Pu£aPeeaioio");
		wstring widetext = ansitest.toWide();
		char hextext[1024] = "", hexchunk[10] = "";

		// Convert to binary data and check data
		wstring::iterator it;
		for (it = widetext.begin();it != widetext.end();it++)
		{
			_snprintf(hexchunk, 10, "%04X", *it);
			strcat(hextext,hexchunk);
		}
		//printf("%s", hextext);
		if (string(hextext) != string("005400650073007400200050007503BC006100500065006500610069006F0069006F"))
			return false;
		return true;
	}

	bool TestStringConverter::TestConvAnsiEnglish::OnExecute()
	{	StringConverter ansitest("Test Ansi");
		string ansitext = ansitest.toMbr();

		if (ansitext != string("Test Ansi"))
			return false;
		return true;
	}

	bool TestStringConverter::TestConvAnsiGreek::OnExecute()
	{	StringConverter ansitest("Test ÅëëçíéêÜ");
		string ansitext = ansitest.toMbr();

		if (ansitext != string("Test ÅëëçíéêÜ"))
			return false;
		return true;
	}

	bool TestStringConverter::TestConvAnsiFrench::OnExecute()
	{	StringConverter ansitest("Test Pu£aPeeaioio");
		string ansitext = ansitest.toMbr();

		if (ansitext != string("Test Pu£aPeeaioio"))
			return false;
		return true;
	}
};	// !oonet namespace
