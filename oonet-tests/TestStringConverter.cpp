#include "TestStringConverter.h"
#include <oonet/string_converter.h>

namespace oonet
{
	namespace test
	{
		TestStringConverter theTestStringConverter;

		bool TestStringConverter::TestCtor::operator()()
		{	StringConverter ansitest("Test Ansi");
			StringConverter widetest(L"Test Wide");
			//printf("Size of wchar_t %u\n", sizeof(wchar_t));
			return true;
		}

		bool TestStringConverter::TestConvWideEnglish::operator()()
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

		bool TestStringConverter::TestConvWideGreek::operator()()
		{	StringConverter ansitest("Test ��������");
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

		bool TestStringConverter::TestConvWideFrench::operator()()
		{	StringConverter ansitest("Test Pu�aPeeaioio");
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

		bool TestStringConverter::TestConvAnsiEnglish::operator()()
		{	StringConverter ansitest("Test Ansi");
			string ansitext = ansitest.toMbr();

			if (ansitext != string("Test Ansi"))
				return false;
			return true;
		}

		bool TestStringConverter::TestConvAnsiGreek::operator()()
		{	StringConverter ansitest("Test ��������");
			string ansitext = ansitest.toMbr();

			if (ansitext != string("Test ��������"))
				return false;
			return true;
		}

		bool TestStringConverter::TestConvAnsiFrench::operator()()
		{	StringConverter ansitest("Test Pu�aPeeaioio");
			string ansitext = ansitest.toMbr();

			if (ansitext != string("Test Pu�aPeeaioio"))
				return false;
			return true;
		}
	}	// !test namespace
};	// !oonet namespace
