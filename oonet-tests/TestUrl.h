#ifndef URL_TEST_H_DEFINED
#define URL_TEST_H_DEFINED

#include "Test.h"

namespace Slib
{
	class TestUrl
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		SLIB_DECLARESUBTEST(TestUrlParamCtor, _T("UrlParam() default"));
		SLIB_DECLARESUBTEST(TestUrlParamParseCtor, _T("UrlParam Ctor() parse"));
		SLIB_DECLARESUBTEST(TestUrlParamCopyCtor, _T("UrlParam copy Ctor()"));
		SLIB_DECLARESUBTEST(TestUrlParamParse,  _T("UrlParam 100k Parse()"));
		SLIB_DECLARESUBTEST(TestUrlParamCopyOperator, _T("UrlParam operator="));
		SLIB_DECLARESUBTEST(TestUrlCtor, _T("Ctor() default"));
		SLIB_DECLARESUBTEST(TestUrlCtorString, _T("Ctor() from string"));
		SLIB_DECLARESUBTEST(TestCopyCtor, _T("Ctor() copy"));
		SLIB_DECLARESUBTEST(TestCopyOperatorUrl, _T("operator= (Url)"));
		SLIB_DECLARESUBTEST(TestCopyOperatorString, _T("operator= (string)"));
		SLIB_DECLARESUBTESTEXC(TestSplit3Wrong1, _T("Split3() wrong"), _T("ExceptionWrongUrl"));
		SLIB_DECLARESUBTESTEXC(TestSplit3Wrong2, _T("Split3() wrong"), _T("ExceptionWrongUrl"));
		SLIB_DECLARESUBTEST(TestSplit3Speed, _T("Split3() speed 10K"));
		SLIB_DECLARESUBTEST(TestSplit3Quality, _T("Split3() quality"));
		SLIB_DECLARESUBTESTEXC(TestSplit4Wrong1, _T("Split4() wrong"), _T("ExceptionWrongUrl"));
		SLIB_DECLARESUBTEST(TestSplit4Quality, _T("Split4() quality"));
		SLIB_DECLARESUBTEST(TestSplit4Speed, _T("Split4() speed 10K"));
		SLIB_DECLARESUBTESTEXC(TestSplit5Wrong1, _T("Split5() wrong"), _T("ExceptionWrongUrl"));
		SLIB_DECLARESUBTEST(TestSplit5Quality, _T("Split5() quality"));
		SLIB_DECLARESUBTEST(TestSplit5Speed, _T("Split5() speed 10K"));
	public:
		// Constructor
		TestUrl()
			:Test(_T("HTTP::Url"))
		{
			SLIB_REGISTERSUBTEST(TestUrlParamCtor);
			SLIB_REGISTERSUBTEST(TestUrlParamParseCtor);
			SLIB_REGISTERSUBTEST(TestUrlParamCopyCtor);
			SLIB_REGISTERSUBTEST(TestUrlParamParse);
			SLIB_REGISTERSUBTEST(TestUrlParamCopyOperator);
			SLIB_REGISTERSUBTEST(TestUrlCtor);
			SLIB_REGISTERSUBTEST(TestUrlCtorString);
			SLIB_REGISTERSUBTEST(TestCopyCtor);
			SLIB_REGISTERSUBTEST(TestCopyOperatorUrl);
			SLIB_REGISTERSUBTEST(TestCopyOperatorString);
			SLIB_REGISTERSUBTEST(TestSplit3Wrong1);
			SLIB_REGISTERSUBTEST(TestSplit3Wrong2);
			SLIB_REGISTERSUBTEST(TestSplit3Speed);
			SLIB_REGISTERSUBTEST(TestSplit3Quality);
			// Must reade the full specification to make proper tests SLIB_REGISTERSUBTEST(TestSplit4Wrong1);
			SLIB_REGISTERSUBTEST(TestSplit4Quality);
			SLIB_REGISTERSUBTEST(TestSplit4Speed);
			SLIB_REGISTERSUBTEST(TestSplit5Wrong1);
			SLIB_REGISTERSUBTEST(TestSplit5Quality);
			SLIB_REGISTERSUBTEST(TestSplit5Speed);
		}

	} ;	//! TestThread test
};	//! Slib namespace

#endif // URL_TEST_H_DEFINED
