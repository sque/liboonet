#ifndef BINARYDATA_TEST_H_INCLUDED
#define BINARYDATA_TEST_H_INCLUDED

#include "oonet-tests.h"

namespace oonet
{
	namespace test
	{
		class test_binary_data
			:public test_set
		{
		protected:
			////////////////////////////
			// SUB TESTS
			OONET_DECLARESUBTEST(TestStringConstructor, "Constructor (String)");
			OONET_DECLARESUBTEST(TestEqOperator, "Operator==()");
			OONET_DECLARESUBTESTEXC(TestEnormousAlloc, "Enormous allocation", "ExceptionBadAllocation");
			OONET_DECLARESUBTESTEXC(TestEnormousReAlloc, "Enormous reallocation", "ExceptionBadAllocation");
			OONET_DECLARESUBTESTEXC(TestAssertNullPointer, "Assert on Null pointer", "ExceptionAssertationFailed");
			OONET_DECLARESUBTEST(TestAddCompare, "Add and compare");
			OONET_DECLARESUBTEST(TestAddByte, "Addition of byte");
			OONET_DECLARESUBTEST(TestFillCtor, "Fill constructors");
			OONET_DECLARESUBTEST(TestNotFoundEmpty, "find() on empty string");
			OONET_DECLARESUBTEST(TestNotFound, "find() for missing");
			OONET_DECLARESUBTESTEXC(TestFindEmptyPattern, "find() with empty pattern", "ExceptionWrongArgument");
			OONET_DECLARESUBTEST(TestFindGeneral, "find() general quality");
			OONET_DECLARESUBTEST_SPEED(TestFindByteIn100MBlock, "find() 1B in 100M block");
			OONET_DECLARESUBTEST_SPEED(TestFindBlockIn100MBlock, "find() 10K in 100M fast");
			OONET_DECLARESUBTEST_SPEED(TestFindBlockDifficult, "find() 10K in 100M hard");
			OONET_DECLARESUBTEST(TestGetFromWrong, "get_from() wrong offset");
			OONET_DECLARESUBTEST(TestGetFromGeneral, "get_from() general quality");
			OONET_DECLARESUBTEST(TestGetUntilWrong, "get_until() wrong offset");
			OONET_DECLARESUBTEST(TestGetUntilGeneral, "get_until() general quality");
			OONET_DECLARESUBTEST(TestSliceWrongOffset, "sub_data() wrong offset");
			OONET_DECLARESUBTEST(TestSliceWrongBoundries, "sub_data() wrong boundries");
			OONET_DECLARESUBTEST(TestSliceGeneral, "sub_data() general quality");
			OONET_DECLARESUBTEST(TestManualSlice, "Manual sub_data experiment");
			OONET_DECLARESUBTEST(TestRealSlice, "Same with sub_data()");
			OONET_DECLARESUBTESTEXC(TestElementWrongOffeset, "operator[] wrong offset", "ExceptionNotFound");
			OONET_DECLARESUBTEST(TestElementGeneral, "operator[] general quality");
			OONET_DECLARESUBTEST(TestLessGeneral, "operator< general quality");
			OONET_DECLARESUBTEST_SPEED(TestLessSpeed, "operator< speed");
			OONET_DECLARESUBTEST(TestAStringExporter, "Test exporting to AString");
			OONET_DECLARESUBTEST(TestWStringExporter, "Test exporting to WString");
			OONET_DECLARESUBTEST(TestCoW, "Test CoW (basic)");
			OONET_DECLARESUBTEST(TestCoWExtend, "Test CoW (extended)");

		public:
			// Constructor
			test_binary_data()
				:test_set("binary_data")
			{
				OONET_REGISTERSUBTEST(TestStringConstructor);
				OONET_REGISTERSUBTEST(TestEqOperator);
				OONET_REGISTERSUBTEST(TestEnormousAlloc);
				// Ta pinei sto vmware...  OONET_REGISTERSUBTEST(TestEnormousReAlloc);
				OONET_REGISTERSUBTEST(TestAssertNullPointer);
				OONET_REGISTERSUBTEST(TestAddCompare);
				OONET_REGISTERSUBTEST(TestAddByte);
				OONET_REGISTERSUBTEST(TestFillCtor);
				OONET_REGISTERSUBTEST(TestNotFoundEmpty);
				OONET_REGISTERSUBTEST(TestNotFound);
				OONET_REGISTERSUBTEST(TestFindEmptyPattern);
				OONET_REGISTERSUBTEST(TestFindGeneral);
				OONET_REGISTERSUBTEST(TestFindByteIn100MBlock);
				OONET_REGISTERSUBTEST(TestFindBlockIn100MBlock);
				OONET_REGISTERSUBTEST(TestFindBlockDifficult);
				OONET_REGISTERSUBTEST(TestGetFromWrong);
				OONET_REGISTERSUBTEST(TestGetFromGeneral);
				OONET_REGISTERSUBTEST(TestGetUntilWrong);
				OONET_REGISTERSUBTEST(TestGetUntilGeneral);
				OONET_REGISTERSUBTEST(TestSliceWrongOffset);
				OONET_REGISTERSUBTEST(TestSliceWrongBoundries);
				OONET_REGISTERSUBTEST(TestSliceGeneral);
				OONET_REGISTERSUBTEST(TestManualSlice);
				OONET_REGISTERSUBTEST(TestRealSlice);
				OONET_REGISTERSUBTEST(TestElementWrongOffeset);
				OONET_REGISTERSUBTEST(TestElementGeneral);
				OONET_REGISTERSUBTEST(TestLessGeneral);
				OONET_REGISTERSUBTEST(TestLessSpeed);
				OONET_REGISTERSUBTEST(TestAStringExporter);
				OONET_REGISTERSUBTEST(TestWStringExporter);
				OONET_REGISTERSUBTEST(TestCoW);
				OONET_REGISTERSUBTEST(TestCoWExtend);

				register_test(this);
			}

		} ;	// !test_binary_data class
	}	// !test namespace
};	// !oonet namespace

#endif // BINARYDATA_TEST_H_INCLUDED

