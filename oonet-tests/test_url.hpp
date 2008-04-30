#ifndef URL_TEST_H_DEFINED
#define URL_TEST_H_DEFINED

#include "Test.h"

namespace oonet
{
	class TestUrl
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		OONET_DECLARESUBTEST(TestUrlParamCtor, _T("UrlParam() default"));
		OONET_DECLARESUBTEST(TestUrlParamParseCtor, _T("UrlParam Ctor() parse"));
		OONET_DECLARESUBTEST(TestUrlParamCopyCtor, _T("UrlParam copy Ctor()"));
		OONET_DECLARESUBTEST(TestUrlParamParse,  _T("UrlParam 100k Parse()"));
		OONET_DECLARESUBTEST(TestUrlParamCopyOperator, _T("UrlParam operator="));
		OONET_DECLARESUBTEST(TestUrlCtor, _T("Ctor() default"));
		OONET_DECLARESUBTEST(TestUrlCtorString, _T("Ctor() from string"));
		OONET_DECLARESUBTEST(TestCopyCtor, _T("Ctor() copy"));
		OONET_DECLARESUBTEST(TestCopyOperatorUrl, _T("operator= (Url)"));
		OONET_DECLARESUBTEST(TestFind, _T("find() "));
		OONET_DECLARESUBTESTEXC(TestSplit3Wrong1, _T("Split3() wrong"), _T("ExceptionWrongUrl"));
		OONET_DECLARESUBTESTEXC(TestSplit3Wrong2, _T("Split3() wrong"), _T("ExceptionWrongUrl"));
		OONET_DECLARESUBTEST(TestSplit3Speed, _T("Split3() speed 10K"));
		OONET_DECLARESUBTEST(TestSplit3Quality, _T("Split3() quality"));
		OONET_DECLARESUBTESTEXC(TestSplit4Wrong1, _T("Split4() wrong"), _T("ExceptionWrongUrl"));
		OONET_DECLARESUBTEST(TestSplit4Quality, _T("Split4() quality"));
		OONET_DECLARESUBTEST(TestSplit4Speed, _T("Split4() speed 10K"));
		OONET_DECLARESUBTESTEXC(TestSplit5Wrong1, _T("Split5() wrong"), _T("ExceptionWrongUrl"));
		OONET_DECLARESUBTEST(TestSplit5Quality, _T("Split5() quality"));
		OONET_DECLARESUBTEST(TestSplit5Speed, _T("Split5() speed 10K"));
	public:
		// Constructor
		TestUrl()
			:Test(_T("http::url"))
		{
			OONET_REGISTERSUBTEST(TestUrlParamCtor);
			OONET_REGISTERSUBTEST(TestUrlParamParseCtor);
			OONET_REGISTERSUBTEST(TestUrlParamCopyCtor);
			OONET_REGISTERSUBTEST(TestUrlParamParse);
			OONET_REGISTERSUBTEST(TestUrlParamCopyOperator);
			OONET_REGISTERSUBTEST(TestUrlCtor);
			OONET_REGISTERSUBTEST(TestUrlCtorString);
			OONET_REGISTERSUBTEST(TestCopyCtor);
			OONET_REGISTERSUBTEST(TestCopyOperatorUrl);
			OONET_REGISTERSUBTEST(TestFind);
			OONET_REGISTERSUBTEST(TestSplit3Wrong1);
			OONET_REGISTERSUBTEST(TestSplit3Wrong2);
			OONET_REGISTERSUBTEST(TestSplit3Speed);
			OONET_REGISTERSUBTEST(TestSplit3Quality);
			/* Must reade the full specification to make proper tests OONET_REGISTERSUBTEST(TestSplit4Wrong1);*/
			OONET_REGISTERSUBTEST(TestSplit4Quality);
			OONET_REGISTERSUBTEST(TestSplit4Speed);
			OONET_REGISTERSUBTEST(TestSplit5Wrong1);
			OONET_REGISTERSUBTEST(TestSplit5Quality);
			OONET_REGISTERSUBTEST(TestSplit5Speed);
		}

	} ;	// !TestUrl class
};	// !oonet namespace

#endif // URL_TEST_H_DEFINED
