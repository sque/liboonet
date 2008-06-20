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
			OONET_DECLARE_SUBTEST(TestCtor, "ctor() default");
			OONET_DECLARE_SUBTEST(TestCopyCtor, "ctor() copy constructor");
			OONET_DECLARE_SUBTEST(TestCopyOperator, "operator= quality");
			OONET_DECLARE_SUBTEST(TestGetBody, "body() quality");
			OONET_DECLARE_SUBTEST(TestGetTitle, "title() quality");
			OONET_DECLARE_SUBTEST(TestRender, "render() quality");
			OONET_DECLARE_SUBTEST_SPEED(TestRenderSpeed, "render() speed 10K");
			OONET_DECLARE_SUBTEST(TestParse, "parse() quality");
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestParseWrong1, "parse() wrong length", "ExceptionWrongFormat");
			OONET_DECLARE_SUBTEST(TestParseIncomplete1, "parse() incomplete");
			OONET_DECLARE_SUBTEST(TestParseIncomplete2, "parse() incomplete");
			OONET_DECLARE_SUBTEST_SPEED(TestParseSpeedLF, "parse()\'\\n\' speed 10k");
			OONET_DECLARE_SUBTEST_SPEED(TestParseSpeedCRLF, "parse()\'\\r\\n\' speed 10k");
		public:
			// Constructor
			test_http_message()
				:test_set("http::message")
			{
				OONET_EXECUTE_SUBTEST(TestCtor);
				OONET_EXECUTE_SUBTEST(TestCopyCtor);
				OONET_EXECUTE_SUBTEST(TestCopyOperator);
				OONET_EXECUTE_SUBTEST(TestGetBody);
				OONET_EXECUTE_SUBTEST(TestGetTitle);
				OONET_EXECUTE_SUBTEST(TestRender);
				OONET_EXECUTE_SUBTEST(TestRenderSpeed);
				OONET_EXECUTE_SUBTEST(TestParse);
				OONET_EXECUTE_SUBTEST(TestParseSpeedLF);
				OONET_EXECUTE_SUBTEST(TestParseSpeedCRLF);
				OONET_EXECUTE_SUBTEST(TestParseWrong1);
				OONET_EXECUTE_SUBTEST(TestParseIncomplete1);
				OONET_EXECUTE_SUBTEST(TestParseIncomplete2);

				register_test(this);
			}

		} ;	// !test_http_message class
	}	// !test namespace
};	// !oonet namespace

#endif // HTTPPACKET_TEST_H_DEFINED
