#ifndef HTTPHEADERS_TEST_H_DEFINED
#define HTTPHEADERS_TEST_H_DEFINED

#include "Test.h"

namespace Slib
{
	class TestHTTPHeaders
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		SLIB_DECLARESUBTEST(TestSmartNewLineQuality, _T("_smart_nl() Quality"));
		SLIB_DECLARESUBTEST(TestSmartNewLineSpeedCRLF, _T("_smart_nl() \\r\\n 10k Speed"));
		SLIB_DECLARESUBTEST(TestSmartNewLineSpeedLF, _T("_smart_nl() \\n 10k Speed"));
		SLIB_DECLARESUBTEST(TestCtor, _T("Ctor() default"));
		SLIB_DECLARESUBTEST(TestCopyCtor, _T("Ctor() copy constructor"));
		SLIB_DECLARESUBTEST(TestCopyOperator, _T("operator= quality"));
		SLIB_DECLARESUBTESTEXC(TestSetHeaderWrong1, _T("SetHeader() wrong"), _T("ExceptionAssertationFailed"));
		SLIB_DECLARESUBTEST(TestSetHeader, _T("SetHeader() quality"));
		SLIB_DECLARESUBTEST(TestSetHeaderSpeed, _T("SetHeader() 100k speed"));
		SLIB_DECLARESUBTEST(TestRemoveHeader, _T("RemoveHeader() quality"));
		SLIB_DECLARESUBTESTEXC(TestRemoveHeaderWrong1, _T("RemoveHeader() wrong"), _T("ExceptionNotFound"));
		SLIB_DECLARESUBTESTEXC(TestRemoveHeaderWrong2, _T("RemoveHeader() wrong"), _T("ExceptionNotFound"));
		SLIB_DECLARESUBTEST(TestRemoveHeaderSpeed, _T("RemoveHeader() 100k Speed"));
		SLIB_DECLARESUBTEST(TestRender, _T("Render() quality"));
		SLIB_DECLARESUBTEST(TestRenderSpeed100k_2, _T("Render() 100k/2H speed"));
		SLIB_DECLARESUBTEST(TestRenderSpeed100k_100, _T("Render() 100k/100h speed"));
		SLIB_DECLARESUBTEST(TestParse, _T("Parse() quality"));
		SLIB_DECLARESUBTESTEXC(TestParseWrong1, _T("Parse() wrong"), _T("ExceptionWrongFormat"));
		SLIB_DECLARESUBTESTEXC(TestParseWrong2, _T("Parse() wrong"), _T("ExceptionWrongFormat"));
		SLIB_DECLARESUBTEST(TestParseSpeed100k, _T("Parse() 100k speed"));
	public:
		// Constructor
		TestHTTPHeaders()
			:Test(_T("HTTP::Headers"))
		{
			SLIB_REGISTERSUBTEST(TestSmartNewLineQuality);
			SLIB_REGISTERSUBTEST(TestSmartNewLineSpeedCRLF);
			SLIB_REGISTERSUBTEST(TestSmartNewLineSpeedLF);
			SLIB_REGISTERSUBTEST(TestCtor);
			SLIB_REGISTERSUBTEST(TestCopyCtor);
			SLIB_REGISTERSUBTEST(TestCopyOperator);
			SLIB_REGISTERSUBTEST(TestSetHeaderWrong1);
			SLIB_REGISTERSUBTEST(TestSetHeader);
			SLIB_REGISTERSUBTEST(TestSetHeaderSpeed);
			SLIB_REGISTERSUBTEST(TestRemoveHeader);
			SLIB_REGISTERSUBTEST(TestRemoveHeaderWrong1);
			SLIB_REGISTERSUBTEST(TestRemoveHeaderWrong2);
			SLIB_REGISTERSUBTEST(TestRemoveHeaderSpeed);
			SLIB_REGISTERSUBTEST(TestRender);
			SLIB_REGISTERSUBTEST(TestRenderSpeed100k_2);
			SLIB_REGISTERSUBTEST(TestRenderSpeed100k_100);
			SLIB_REGISTERSUBTEST(TestParse);
			SLIB_REGISTERSUBTEST(TestParseWrong1);
			SLIB_REGISTERSUBTEST(TestParseWrong2);
			SLIB_REGISTERSUBTEST(TestParseSpeed100k);
		}

	} ;	//! TestThread test
};	//! Slib namespace

#endif // HTTPHEADERS_TEST_H_DEFINED
