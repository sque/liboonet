#ifndef HTTPPACKET_TEST_H_DEFINED
#define HTTPPACKET_TEST_H_DEFINED

#include "oonet-tests.h"

namespace oonet
{
	namespace test
	{
		class test_http_message
			:public test_set
		{
		protected:
			////////////////////////////
			// SUB TESTS
			OONET_DECLARESUBTEST(TestCtor, "ctor() default");
			OONET_DECLARESUBTEST(TestCopyCtor, "ctor() copy constructor");
			OONET_DECLARESUBTEST(TestCopyOperator, "operator= quality");
			OONET_DECLARESUBTEST(TestGetBody, "body() quality");
			OONET_DECLARESUBTEST(TestGetTitle, "title() quality");
			OONET_DECLARESUBTEST(TestRender, "render() quality");
			OONET_DECLARESUBTEST_SPEED(TestRenderSpeed, "render() speed 10K");
			OONET_DECLARESUBTEST(TestParse, "parse() quality");
			OONET_DECLARESUBTESTEXC(TestParseWrong1, "parse() wrong length", "ExceptionWrongFormat");
			OONET_DECLARESUBTEST(TestParseIncomplete1, "parse() incomplete");
			OONET_DECLARESUBTEST(TestParseIncomplete2, "parse() incomplete");
			OONET_DECLARESUBTEST_SPEED(TestParseSpeedLF, "parse()\'\\n\' speed 10k");
			OONET_DECLARESUBTEST_SPEED(TestParseSpeedCRLF, "parse()\'\\r\\n\' speed 10k");
		public:
			// Constructor
			test_http_message()
				:test_set("http::message")
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

				register_test(this);
			}

		} ;	// !test_http_message class
	}	// !test namespace
};	// !oonet namespace

#endif // HTTPPACKET_TEST_H_DEFINED
