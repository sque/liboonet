#ifndef HTTPRESPONSE_TEST_H_DEFINED
#define HTTPRESPONSE_TEST_H_DEFINED

#include "Test.h"

namespace Slib
{
	class TestHTTPResponse
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		SLIB_DECLARESUBTEST(TestCtor, _T("Ctor() default"));
		SLIB_DECLARESUBTEST(TestCopyCtor, _T("Ctor() copy constructor"));
		SLIB_DECLARESUBTEST(TestCopyOperator, _T("operator= quality"));
		SLIB_DECLARESUBTEST(TestRender, _T("Render() quality"));
		SLIB_DECLARESUBTEST(TestRenderSpeed, _T("Render() speed 10k"));
		SLIB_DECLARESUBTEST(TestParse, _T("Parse() quality"));
		SLIB_DECLARESUBTESTEXC(TestParseWrong1, _T("Parse() wrong"), _T("ExceptionWrongFormat"));
		SLIB_DECLARESUBTESTEXC(TestParseWrong2, _T("Parse() wrong"), _T("ExceptionWrongFormat"));
		SLIB_DECLARESUBTEST(TestParseSpeed, _T("Parse() speed 10k"))
	public:
		// Constructor
		TestHTTPResponse()
			:Test(_T("HTTP::Response"))
		{
			SLIB_REGISTERSUBTEST(TestCtor);
			SLIB_REGISTERSUBTEST(TestCopyCtor);
			SLIB_REGISTERSUBTEST(TestCopyOperator);
			SLIB_REGISTERSUBTEST(TestRender);
			SLIB_REGISTERSUBTEST(TestRenderSpeed);
			SLIB_REGISTERSUBTEST(TestParse);
			SLIB_REGISTERSUBTEST(TestParseWrong1);
			SLIB_REGISTERSUBTEST(TestParseWrong2);
			SLIB_REGISTERSUBTEST(TestParseSpeed);
		}

	} ;	//! TestHTTPResponse test
};	//! Slib namespace

#endif // HTTPRESPONSE_TEST_H_DEFINED
