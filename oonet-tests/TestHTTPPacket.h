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
		OONET_DECLARESUBTEST(TestCtor, _T("ctor() default"));
		OONET_DECLARESUBTEST(TestCopyCtor, _T("ctor() copy constructor"));
		OONET_DECLARESUBTEST(TestCopyOperator, _T("operator= quality"));
		OONET_DECLARESUBTEST(TestGetBody, _T("body() quality"));
		OONET_DECLARESUBTEST(TestGetTitle, _T("title() quality"));
		OONET_DECLARESUBTEST(TestRender, _T("render() quality"));
		OONET_DECLARESUBTEST(TestRenderSpeed, _T("render() speed 10K"));
		OONET_DECLARESUBTEST(TestParse, _T("parse() quality"));
		OONET_DECLARESUBTESTEXC(TestParseWrong1, _T("parse() wrong length"), _T("ExceptionWrongFormat"));
		OONET_DECLARESUBTEST(TestParseIncomplete1, _T("parse() incomplete"));
		OONET_DECLARESUBTEST(TestParseIncomplete2, _T("parse() incomplete"));
		OONET_DECLARESUBTEST(TestParseSpeedLF, _T("parse()\'\\n\' speed 10k"));
		OONET_DECLARESUBTEST(TestParseSpeedCRLF, _T("parse()\'\\r\\n\' speed 10k"));
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
			OONET_REGISTERSUBTEST(TestParseSpeedLF);
			OONET_REGISTERSUBTEST(TestParseSpeedCRLF);
			OONET_REGISTERSUBTEST(TestParseWrong1);
			OONET_REGISTERSUBTEST(TestParseIncomplete1);
			OONET_REGISTERSUBTEST(TestParseIncomplete2);
		}

	} ;	// !TestHTTPPacket class
};	// !oonet namespace

#endif // HTTPPACKET_TEST_H_DEFINED
