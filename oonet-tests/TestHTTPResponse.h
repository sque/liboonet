#ifndef HTTPRESPONSE_TEST_H_DEFINED
#define HTTPRESPONSE_TEST_H_DEFINED

#include "Test.h"

namespace OONet
{
	class TestHTTPResponse
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		OONET_DECLARESUBTEST(TestCtor, _T("Ctor() default"));
		OONET_DECLARESUBTEST(TestCopyCtor, _T("Ctor() copy constructor"));
		OONET_DECLARESUBTEST(TestCopyOperator, _T("operator= quality"));
		OONET_DECLARESUBTEST(TestRender, _T("Render() quality"));
		OONET_DECLARESUBTEST(TestRenderSpeed, _T("Render() speed 10k"));
		OONET_DECLARESUBTEST(TestParse, _T("Parse() quality"));
		OONET_DECLARESUBTESTEXC(TestParseWrong1, _T("Parse() wrong"), _T("ExceptionWrongFormat"));
		OONET_DECLARESUBTESTEXC(TestParseWrong2, _T("Parse() wrong"), _T("ExceptionWrongFormat"));
		OONET_DECLARESUBTEST(TestParseSpeed, _T("Parse() speed 10k"))
	public:
		// Constructor
		TestHTTPResponse()
			:Test(_T("HTTP::Response"))
		{
			OONET_REGISTERSUBTEST(TestCtor);
			OONET_REGISTERSUBTEST(TestCopyCtor);
			OONET_REGISTERSUBTEST(TestCopyOperator);
			OONET_REGISTERSUBTEST(TestRender);
			OONET_REGISTERSUBTEST(TestRenderSpeed);
			OONET_REGISTERSUBTEST(TestParse);
			OONET_REGISTERSUBTEST(TestParseWrong1);
			OONET_REGISTERSUBTEST(TestParseWrong2);
			OONET_REGISTERSUBTEST(TestParseSpeed);
		}

	} ;	// !TestHTTPResponse class
};	// !OONet namespace

#endif // HTTPRESPONSE_TEST_H_DEFINED
