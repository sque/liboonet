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
			OONET_DECLARESUBTEST(TestUrlParamCtor, "UrlParam() default");
			OONET_DECLARESUBTEST(TestUrlParamParseCtor, "UrlParam Ctor() parse");
			OONET_DECLARESUBTEST(TestUrlParamCopyCtor, "UrlParam copy Ctor()");
			OONET_DECLARESUBTEST(TestUrlParamParse, "UrlParam 100k Parse()");
			OONET_DECLARESUBTEST(TestUrlParamCopyOperator, "UrlParam operator=");
			OONET_DECLARESUBTEST(TestUrlCtor, "Ctor() default");
			OONET_DECLARESUBTEST(TestUrlCtorString, "Ctor() from string");
			OONET_DECLARESUBTEST(TestCopyCtor, "Ctor() copy");
			OONET_DECLARESUBTEST(TestCopyOperatorUrl, "operator= (Url)");
			OONET_DECLARESUBTEST(TestFind, "find() ");
			OONET_DECLARESUBTESTEXC(TestSplit3Wrong1, "Split3() wrong", "ExceptionWrongUrl");
			OONET_DECLARESUBTESTEXC(TestSplit3Wrong2, "Split3() wrong", "ExceptionWrongUrl");
			OONET_DECLARESUBTEST_SPEED(TestSplit3Speed, "Split3() speed 10K");
			OONET_DECLARESUBTEST(TestSplit3Quality, "Split3() quality");
			OONET_DECLARESUBTESTEXC(TestSplit4Wrong1, "Split4() wrong", "ExceptionWrongUrl");
			OONET_DECLARESUBTEST(TestSplit4Quality, "Split4() quality");
			OONET_DECLARESUBTEST_SPEED(TestSplit4Speed, "Split4() speed 10K");
			OONET_DECLARESUBTESTEXC(TestSplit5Wrong1, "Split5() wrong", "ExceptionWrongUrl");
			OONET_DECLARESUBTEST(TestSplit5Quality, "Split5() quality");
			OONET_DECLARESUBTEST_SPEED(TestSplit5Speed, "Split5() speed 10K");
		public:
			// Constructor
			test_url()
				:test_set("http::url")
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

				register_test(this);
			}

		} ;	// !test_url class
	}	// !test namespace
};	// !oonet namespace

#endif // URL_TEST_H_DEFINED
