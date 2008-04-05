#ifndef HTTPPACKET_TEST_H_DEFINED
#define HTTPPACKET_TEST_H_DEFINED

#include "Test.h"

namespace oonet
{
	class TestHTTPPacket
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		OONET_DECLARESUBTEST(TestCtor, _T("Ctor() default"));
		OONET_DECLARESUBTEST(TestCopyCtor, _T("Ctor() copy constructor"));
		OONET_DECLARESUBTEST(TestCopyOperator, _T("operator= quality"));
		OONET_DECLARESUBTEST(TestGetBody, _T("GetBody() quality"));
		OONET_DECLARESUBTEST(TestGetTitle, _T("GetTitle() quality"));
		OONET_DECLARESUBTEST(TestRender, _T("Render() quality"));
		OONET_DECLARESUBTEST(TestRenderSpeed, _T("Render() speed 10K"));
		OONET_DECLARESUBTEST(TestParse, _T("Parse() quality"));
		OONET_DECLARESUBTESTEXC(TestParseWrong1, _T("Parse() wrong"), _T("ExceptionWrongFormat"));
		OONET_DECLARESUBTESTEXC(TestParseWrong2, _T("Parse() wrong"), _T("ExceptionWrongFormat"));
		OONET_DECLARESUBTEST(TestParseIncomplete1, _T("Parse() incomplete"));
		OONET_DECLARESUBTEST(TestParseIncomplete2, _T("Parse() incomplete"));
		OONET_DECLARESUBTEST(TestParseSpeed, _T("Parse() speed 10k"));
	public:
		// Constructor
		TestHTTPPacket()
			:Test(_T("http::packet"))
		{
			OONET_REGISTERSUBTEST(TestCtor);
			OONET_REGISTERSUBTEST(TestCopyCtor);
			OONET_REGISTERSUBTEST(TestCopyOperator);
			OONET_REGISTERSUBTEST(TestGetBody);
			OONET_REGISTERSUBTEST(TestGetTitle);
			OONET_REGISTERSUBTEST(TestRender);
			OONET_REGISTERSUBTEST(TestRenderSpeed);
			OONET_REGISTERSUBTEST(TestParse);
			OONET_REGISTERSUBTEST(TestParseSpeed);
			OONET_REGISTERSUBTEST(TestParseWrong1);
			OONET_REGISTERSUBTEST(TestParseWrong2);
			OONET_REGISTERSUBTEST(TestParseIncomplete1);
			OONET_REGISTERSUBTEST(TestParseIncomplete2);
		}

	} ;	// !TestHTTPPacket class
};	// !oonet namespace

#endif // HTTPPACKET_TEST_H_DEFINED
