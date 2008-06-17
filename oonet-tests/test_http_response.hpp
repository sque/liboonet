#ifndef HTTPRESPONSE_TEST_H_DEFINED
#define HTTPRESPONSE_TEST_H_DEFINED

#include "oonet-tests.h"

namespace oonet
{
	namespace test
	{
		class test_http_response
			:public test_set
		{
		protected:
			////////////////////////////
			// SUB TESTS
			OONET_DECLARESUBTEST(TestCtor, "Ctor() default");
			OONET_DECLARESUBTEST(TestCopyCtor, "Ctor() copy constructor");
			OONET_DECLARESUBTEST(TestCopyOperator, "operator= quality");
			OONET_DECLARESUBTEST(TestRender, "Render() quality");
			OONET_DECLARESUBTEST_SPEED(TestRenderSpeed, "Render() speed 10k");
			OONET_DECLARESUBTEST(TestParse, "Parse() quality");
			OONET_DECLARESUBTESTEXC(TestParseWrong1, "Parse() wrong", "ExceptionWrongFormat");
			OONET_DECLARESUBTESTEXC(TestParseWrong2, "Parse() wrong", "ExceptionWrongFormat");
			OONET_DECLARESUBTEST_SPEED(TestParseSpeed, "Parse() speed 10k")
		public:
			// Constructor
			test_http_response()
				:test_set("http::response")
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

				register_test(this);
			}

		} ;	// !test_http_response class
	}	// !test namespace
};	// !oonet namespace

#endif // HTTPRESPONSE_TEST_H_DEFINED
