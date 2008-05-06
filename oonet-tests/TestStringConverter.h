#ifndef STRINGCONVERTER_TEST_H_DEFINED
#define STRINGCONVERTER_TEST_H_DEFINED

#include "oonet-tests.h"

namespace oonet
{
	namespace test
	{
		class TestStringConverter
			:public test_set
		{
		protected:
			////////////////////////////
			// SUB TESTS
			OONET_DECLARESUBTEST(TestCtor, "Ctor() default");
			OONET_DECLARESUBTEST(TestConvWideEnglish, "toUnicode (English)");
			OONET_DECLARESUBTEST(TestConvWideGreek, "toUnicode (Greek)");
			OONET_DECLARESUBTEST(TestConvWideFrench, "toUnicode (French)");
			OONET_DECLARESUBTEST(TestConvAnsiEnglish, "toAnsi from (English)");
			OONET_DECLARESUBTEST(TestConvAnsiGreek, "toAnsi from (Greek)");
			OONET_DECLARESUBTEST(TestConvAnsiFrench, "toAnsi from (French)");

		public:
			// Constructor
			TestStringConverter()
				:test_set("StringConverter")
			{
				OONET_REGISTERSUBTEST(TestCtor);
				OONET_REGISTERSUBTEST(TestConvWideEnglish);
				OONET_REGISTERSUBTEST(TestConvWideGreek);
				OONET_REGISTERSUBTEST(TestConvWideFrench);
				OONET_REGISTERSUBTEST(TestConvAnsiEnglish);
				OONET_REGISTERSUBTEST(TestConvAnsiGreek);
				OONET_REGISTERSUBTEST(TestConvAnsiFrench);

				register_test(this);
			}

		} ;	// !TestStringConverter class
	}	// !test namespace
};	// !oonet namespace

#endif // STRINGCONVERTER_TEST_H_DEFINED
