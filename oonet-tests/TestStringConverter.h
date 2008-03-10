#ifndef STRINGCONVERTER_TEST_H_DEFINED
#define STRINGCONVERTER_TEST_H_DEFINED

#include "Test.h"

namespace OONet
{
	class TestStringConverter
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		OONET_DECLARESUBTEST(TestCtor, _T("Ctor() default"));
		OONET_DECLARESUBTEST(TestConvWideEnglish, _T("toUnicode (English)"));
		OONET_DECLARESUBTEST(TestConvWideGreek, _T("toUnicode (Greek)"));
		OONET_DECLARESUBTEST(TestConvWideFrench, _T("toUnicode (French)"));
		OONET_DECLARESUBTEST(TestConvAnsiEnglish, _T("toAnsi from (English)"));
		OONET_DECLARESUBTEST(TestConvAnsiGreek, _T("toAnsi from (Greek)"));
		OONET_DECLARESUBTEST(TestConvAnsiFrench, _T("toAnsi from (French)"));

	public:
		// Constructor
		TestStringConverter()
			:Test(_T("StringConverter"))
		{
			OONET_REGISTERSUBTEST(TestCtor);
			OONET_REGISTERSUBTEST(TestConvWideEnglish);
			OONET_REGISTERSUBTEST(TestConvWideGreek);
			OONET_REGISTERSUBTEST(TestConvWideFrench);
			OONET_REGISTERSUBTEST(TestConvAnsiEnglish);
			OONET_REGISTERSUBTEST(TestConvAnsiGreek);
			OONET_REGISTERSUBTEST(TestConvAnsiFrench);

		}

	} ;	// !TestStringConverter class
};	// !OONet namespace

#endif // STRINGCONVERTER_TEST_H_DEFINED
