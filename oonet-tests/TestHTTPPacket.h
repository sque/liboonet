#ifndef HTTPPACKET_TEST_H_DEFINED
#define HTTPPACKET_TEST_H_DEFINED

#include "Test.h"

namespace Slib
{
	class TestHTTPPacket
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		SLIB_DECLARESUBTEST(TestCtor, _T("Ctor() default"));
		SLIB_DECLARESUBTEST(TestCopyCtor, _T("Ctor() copy constructor"));
		SLIB_DECLARESUBTEST(TestCopyOperator, _T("operator= quality"));
		SLIB_DECLARESUBTEST(TestGetBody, _T("GetBody() quality"));
		SLIB_DECLARESUBTEST(TestGetTitle, _T("GetTitle() quality"));
		SLIB_DECLARESUBTEST(TestRender, _T("Render() quality"));
		SLIB_DECLARESUBTEST(TestRenderSpeed, _T("Render() speed 10K"));
		SLIB_DECLARESUBTEST(TestParse, _T("Parse() quality"));
		SLIB_DECLARESUBTESTEXC(TestParseWrong1, _T("Parse() wrong"), _T("ExceptionWrongFormat"));
		SLIB_DECLARESUBTESTEXC(TestParseWrong2, _T("Parse() wrong"), _T("ExceptionWrongFormat"));
		SLIB_DECLARESUBTESTEXC(TestParseIncomplete1, _T("Parse() incomplete"), _T("ExceptionIncomplete"));
		SLIB_DECLARESUBTESTEXC(TestParseIncomplete2, _T("Parse() incomplete"), _T("ExceptionIncomplete"));
		SLIB_DECLARESUBTEST(TestParseSpeed, _T("Parse() speed 10k"));
	public:
		// Constructor
		TestHTTPPacket()
			:Test(_T("HTTP::Packet"))
		{
			SLIB_REGISTERSUBTEST(TestCtor);
			SLIB_REGISTERSUBTEST(TestCopyCtor);
			SLIB_REGISTERSUBTEST(TestCopyOperator);
			SLIB_REGISTERSUBTEST(TestGetBody);
			SLIB_REGISTERSUBTEST(TestGetTitle);
			SLIB_REGISTERSUBTEST(TestRender);
			SLIB_REGISTERSUBTEST(TestRenderSpeed);
			SLIB_REGISTERSUBTEST(TestParse);
			SLIB_REGISTERSUBTEST(TestParseSpeed);
			SLIB_REGISTERSUBTEST(TestParseWrong1);
			SLIB_REGISTERSUBTEST(TestParseWrong2);
			SLIB_REGISTERSUBTEST(TestParseIncomplete1);
			SLIB_REGISTERSUBTEST(TestParseIncomplete2);
		}

	} ;	//! TestHTTPPacket test
};	//! Slib namespace

#endif // HTTPPACKET_TEST_H_DEFINED
