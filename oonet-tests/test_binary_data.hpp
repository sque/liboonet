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
			OONET_DECLARE_SUBTEST(TestStringConstructor, "Constructor (String)");
			OONET_DECLARE_SUBTEST(TestEqOperator, "Operator==()");
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestEnormousAlloc, "Enormous allocation", "ExceptionBadAllocation");
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestEnormousReAlloc, "Enormous reallocation", "ExceptionBadAllocation");
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestAssertNullPointer, "Assert on Null pointer", "ExceptionAssertationFailed");
			OONET_DECLARE_SUBTEST(TestAddCompare, "Add and compare");
			OONET_DECLARE_SUBTEST(TestAddByte, "Addition of byte");
			OONET_DECLARE_SUBTEST(TestFillCtor, "Fill constructors");
			OONET_DECLARE_SUBTEST(TestNotFoundEmpty, "find() on empty string");
			OONET_DECLARE_SUBTEST(TestNotFound, "find() for missing");
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestFindEmptyPattern, "find() with empty pattern", "ExceptionWrongArgument");
			OONET_DECLARE_SUBTEST(TestFindGeneral, "find() general quality");
			OONET_DECLARE_SUBTEST_SPEED(TestFindByteIn100MBlock, "find() 1B in 100M block");
			OONET_DECLARE_SUBTEST_SPEED(TestFindBlockIn100MBlock, "find() 10K in 100M fast");
			OONET_DECLARE_SUBTEST_SPEED(TestFindBlockDifficult, "find() 10K in 100M hard");
			OONET_DECLARE_SUBTEST(TestGetFromWrong, "get_from() wrong offset");
			OONET_DECLARE_SUBTEST(TestGetFromGeneral, "get_from() general quality");
			OONET_DECLARE_SUBTEST(TestGetUntilWrong, "get_until() wrong offset");
			OONET_DECLARE_SUBTEST(TestGetUntilGeneral, "get_until() general quality");
			OONET_DECLARE_SUBTEST(TestSliceWrongOffset, "sub_data() wrong offset");
			OONET_DECLARE_SUBTEST(TestSliceWrongBoundries, "sub_data() wrong boundries");
			OONET_DECLARE_SUBTEST(TestSliceGeneral, "sub_data() general quality");
			OONET_DECLARE_SUBTEST(TestManualSlice, "Manual sub_data experiment");
			OONET_DECLARE_SUBTEST(TestRealSlice, "Same with sub_data()");
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestElementWrongOffeset, "operator[] wrong offset", "ExceptionNotFound");
			OONET_DECLARE_SUBTEST(TestElementGeneral, "operator[] general quality");
			OONET_DECLARE_SUBTEST(TestLessGeneral, "operator< general quality");
			OONET_DECLARE_SUBTEST_SPEED(TestLessSpeed, "operator< speed");
			OONET_DECLARE_SUBTEST(TestAStringExporter, "Test exporting to AString");
			OONET_DECLARE_SUBTEST(TestWStringExporter, "Test exporting to WString");
			OONET_DECLARE_SUBTEST(TestCoW, "Test CoW (basic)");
			OONET_DECLARE_SUBTEST(TestCoWExtend, "Test CoW (extended)");

		public:
			// Constructor
			test_binary_data()
				:test_set("binary_data")
			{
				OONET_EXECUTE_SUBTEST(TestStringConstructor);
				OONET_EXECUTE_SUBTEST(TestEqOperator);
				OONET_EXECUTE_SUBTEST(TestEnormousAlloc);
				// Ta pinei sto vmware...  OONET_EXECUTE_SUBTEST(TestEnormousReAlloc);
				OONET_EXECUTE_SUBTEST(TestAssertNullPointer);
				OONET_EXECUTE_SUBTEST(TestAddCompare);
				OONET_EXECUTE_SUBTEST(TestAddByte);
				OONET_EXECUTE_SUBTEST(TestFillCtor);
				OONET_EXECUTE_SUBTEST(TestNotFoundEmpty);
				OONET_EXECUTE_SUBTEST(TestNotFound);
				OONET_EXECUTE_SUBTEST(TestFindEmptyPattern);
				OONET_EXECUTE_SUBTEST(TestFindGeneral);
				OONET_EXECUTE_SUBTEST(TestFindByteIn100MBlock);
				OONET_EXECUTE_SUBTEST(TestFindBlockIn100MBlock);
				OONET_EXECUTE_SUBTEST(TestFindBlockDifficult);
				OONET_EXECUTE_SUBTEST(TestGetFromWrong);
				OONET_EXECUTE_SUBTEST(TestGetFromGeneral);
				OONET_EXECUTE_SUBTEST(TestGetUntilWrong);
				OONET_EXECUTE_SUBTEST(TestGetUntilGeneral);
				OONET_EXECUTE_SUBTEST(TestSliceWrongOffset);
				OONET_EXECUTE_SUBTEST(TestSliceWrongBoundries);
				OONET_EXECUTE_SUBTEST(TestSliceGeneral);
				OONET_EXECUTE_SUBTEST(TestManualSlice);
				OONET_EXECUTE_SUBTEST(TestRealSlice);
				OONET_EXECUTE_SUBTEST(TestElementWrongOffeset);
				OONET_EXECUTE_SUBTEST(TestElementGeneral);
				OONET_EXECUTE_SUBTEST(TestLessGeneral);
				OONET_EXECUTE_SUBTEST(TestLessSpeed);
				OONET_EXECUTE_SUBTEST(TestAStringExporter);
				OONET_EXECUTE_SUBTEST(TestWStringExporter);
				OONET_EXECUTE_SUBTEST(TestCoW);
				OONET_EXECUTE_SUBTEST(TestCoWExtend);

				register_test(this);
			}

		} ;	// !test_binary_data class
	}	// !test namespace
};	// !oonet namespace

#endif // BINARYDATA_TEST_H_INCLUDED

