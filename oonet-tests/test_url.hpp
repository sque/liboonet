#ifndef URL_TEST_H_DEFINED
#define URL_TEST_H_DEFINED

#include "oonet-tests.h"

namespace oonet
{
	namespace test
	{
		class test_url
			:public test_set
		{
		protected:
			////////////////////////////
			// SUB TESTS
			OONET_DECLARE_SUBTEST(TestUrlParamCtor, "UrlParam() default");
			OONET_DECLARE_SUBTEST(TestUrlParamParseCtor, "UrlParam Ctor() parse");
			OONET_DECLARE_SUBTEST(TestUrlParamCopyCtor, "UrlParam copy Ctor()");
			OONET_DECLARE_SUBTEST(TestUrlParamParse, "UrlParam 100k Parse()");
			OONET_DECLARE_SUBTEST(TestUrlParamCopyOperator, "UrlParam operator=");
			OONET_DECLARE_SUBTEST(TestUrlCtor, "Ctor() default");
			OONET_DECLARE_SUBTEST(TestUrlCtorString, "Ctor() from string");
			OONET_DECLARE_SUBTEST(TestCopyCtor, "Ctor() copy");
			OONET_DECLARE_SUBTEST(TestCopyOperatorUrl, "operator= (Url)");
			OONET_DECLARE_SUBTEST(TestFind, "find() ");
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestSplit3Wrong1, "Split3() wrong", "ExceptionWrongUrl");
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestSplit3Wrong2, "Split3() wrong", "ExceptionWrongUrl");
			OONET_DECLARE_SUBTEST_SPEED(TestSplit3Speed, "Split3() speed 10K");
			OONET_DECLARE_SUBTEST(TestSplit3Quality, "Split3() quality");
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestSplit4Wrong1, "Split4() wrong", "ExceptionWrongUrl");
			OONET_DECLARE_SUBTEST(TestSplit4Quality, "Split4() quality");
			OONET_DECLARE_SUBTEST_SPEED(TestSplit4Speed, "Split4() speed 10K");
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestSplit5Wrong1, "Split5() wrong", "ExceptionWrongUrl");
			OONET_DECLARE_SUBTEST(TestSplit5Quality, "Split5() quality");
			OONET_DECLARE_SUBTEST_SPEED(TestSplit5Speed, "Split5() speed 10K");
		public:
			// Constructor
			test_url()
				:test_set("http::url")
			{
				OONET_EXECUTE_SUBTEST(TestUrlParamCtor);
				OONET_EXECUTE_SUBTEST(TestUrlParamParseCtor);
				OONET_EXECUTE_SUBTEST(TestUrlParamCopyCtor);
				OONET_EXECUTE_SUBTEST(TestUrlParamParse);
				OONET_EXECUTE_SUBTEST(TestUrlParamCopyOperator);
				OONET_EXECUTE_SUBTEST(TestUrlCtor);
				OONET_EXECUTE_SUBTEST(TestUrlCtorString);
				OONET_EXECUTE_SUBTEST(TestCopyCtor);
				OONET_EXECUTE_SUBTEST(TestCopyOperatorUrl);
				OONET_EXECUTE_SUBTEST(TestFind);
				OONET_EXECUTE_SUBTEST(TestSplit3Wrong1);
				OONET_EXECUTE_SUBTEST(TestSplit3Wrong2);
				OONET_EXECUTE_SUBTEST(TestSplit3Speed);
				OONET_EXECUTE_SUBTEST(TestSplit3Quality);
				/* Must reade the full specification to make proper tests OONET_EXECUTE_SUBTEST(TestSplit4Wrong1);*/
				OONET_EXECUTE_SUBTEST(TestSplit4Quality);
				OONET_EXECUTE_SUBTEST(TestSplit4Speed);
				OONET_EXECUTE_SUBTEST(TestSplit5Wrong1);
				OONET_EXECUTE_SUBTEST(TestSplit5Quality);
				OONET_EXECUTE_SUBTEST(TestSplit5Speed);

				register_test(this);
			}

		} ;	// !test_url class
	}	// !test namespace
};	// !oonet namespace

#endif // URL_TEST_H_DEFINED
