#ifndef HTTPHEADERS_TEST_H_DEFINED
#define HTTPHEADERS_TEST_H_DEFINED

#include "Test.h"

namespace oonet
{
	class TestHTTPHeaders
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		OONET_DECLARESUBTEST(TestSmartNewLineQuality, _T("_smart_nl() Quality"));
		OONET_DECLARESUBTEST(TestSmartNewLineSpeedCRLF, _T("_smart_nl() \\r\\n 10k Speed"));
		OONET_DECLARESUBTEST(TestSmartNewLineSpeedLF, _T("_smart_nl() \\n 10k Speed"));
		OONET_DECLARESUBTEST(TestCtor, _T("ctor() default"));
		OONET_DECLARESUBTEST(TestCopyCtor, _T("ctor() copy constructor"));
		OONET_DECLARESUBTEST(TestCopyOperator, _T("operator= quality"));
		OONET_DECLARESUBTESTEXC(TestSetHeaderWrong1, _T("set() wrong"), _T("ExceptionAssertationFailed"));
		OONET_DECLARESUBTEST(TestSetHeader, _T("set() quality"));
		OONET_DECLARESUBTEST(TestSetHeaderSpeed, _T("set() 100k speed"));
		OONET_DECLARESUBTEST(TestRemoveHeader, _T("erase() quality"));
		OONET_DECLARESUBTESTEXC(TestRemoveHeaderWrong1, _T("erase() wrong"), _T("ExceptionNotFound"));
		OONET_DECLARESUBTESTEXC(TestRemoveHeaderWrong2, _T("erase() wrong"), _T("ExceptionNotFound"));
		OONET_DECLARESUBTEST(TestRemoveHeaderSpeed, _T("erase() 100k Speed"));
		OONET_DECLARESUBTEST(TestRender, _T("render() quality"));
		OONET_DECLARESUBTEST(TestRenderSpeed100k_2, _T("render() 100k/2H speed"));
		OONET_DECLARESUBTEST(TestRenderSpeed100k_100, _T("render() 100k/100h speed"));
		OONET_DECLARESUBTEST(TestParse, _T("parse() quality"));
		OONET_DECLARESUBTESTEXC(TestParseWrong1, _T("parse() wrong"), _T("ExceptionWrongFormat"));
		OONET_DECLARESUBTEST(TestParseSpeed100k, _T("parse() 100k speed"));
	public:
		// Constructor
		TestHTTPHeaders()
			:Test(_T("http::headers_list"))
		{
			OONET_REGISTERSUBTEST(TestSmartNewLineQuality);
			OONET_REGISTERSUBTEST(TestSmartNewLineSpeedCRLF);
			OONET_REGISTERSUBTEST(TestSmartNewLineSpeedLF);
			OONET_REGISTERSUBTEST(TestCtor);
			OONET_REGISTERSUBTEST(TestCopyCtor);
			OONET_REGISTERSUBTEST(TestCopyOperator);
			OONET_REGISTERSUBTEST(TestSetHeaderWrong1);
			OONET_REGISTERSUBTEST(TestSetHeader);
			OONET_REGISTERSUBTEST(TestSetHeaderSpeed);
			OONET_REGISTERSUBTEST(TestRemoveHeader);
			OONET_REGISTERSUBTEST(TestRemoveHeaderWrong1);
			OONET_REGISTERSUBTEST(TestRemoveHeaderWrong2);
			OONET_REGISTERSUBTEST(TestRemoveHeaderSpeed);
			OONET_REGISTERSUBTEST(TestRender);
			OONET_REGISTERSUBTEST(TestRenderSpeed100k_2);
			OONET_REGISTERSUBTEST(TestRenderSpeed100k_100);
			OONET_REGISTERSUBTEST(TestParse);
			OONET_REGISTERSUBTEST(TestParseWrong1);
			OONET_REGISTERSUBTEST(TestParseSpeed100k);
		}

	} ;	// !TestHTTPHeaders class
};	// !oonet namespace

#endif // HTTPHEADERS_TEST_H_DEFINED
