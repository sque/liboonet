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
			OONET_DECLARE_SUBTEST(TestEmptyConstructor, "quality of ctor()");
			OONET_DECLARE_SUBTEST(TestCopyConstructor, "quality of copy ctor()");
			OONET_DECLARE_SUBTEST(TestMemRefConstructor, "quality of ctor(cmem_ref)");
			OONET_DECLARE_SUBTEST(TestRangeConstructor, "quality of ctor(beg, end)");

			// Operators
			OONET_DECLARE_SUBTEST(TestOperatorEq, "quality of operator==");
			OONET_DECLARE_SUBTEST(TestOperatorLess, "quality of operator<");
			OONET_DECLARE_SUBTEST_SPEED(TestOperatorLessSpeed, "benchmark operator<");
			OONET_DECLARE_SUBTEST(TestOperatorGreater, "quality of operator>");
			OONET_DECLARE_SUBTEST(TestOperatorEqGreater, "quality of operator>=");
			OONET_DECLARE_SUBTEST(TestOperatorEqLess, "quality of operator<=");
			OONET_DECLARE_SUBTEST(TestOperatorElement, "quality of operator[]");
			
			// Element Acccess
			OONET_DECLARE_SUBTEST(TestForwardIterator, "quality of forward iterator");
			OONET_DECLARE_SUBTEST(TestReverseIterator, "quality of reverse iterator");
			OONET_DECLARE_SUBTEST(TestFrontBack, "quality of front() back()");
			OONET_DECLARE_SUBTEST(TestCArray, "quality of c_array()");
			OONET_DECLARE_SUBTEST(TestAtElementWrongOffeset, "at() wrong offset");
			OONET_DECLARE_SUBTEST(TestAtElementGeneral, "quality of at()");
			OONET_DECLARE_SUBTEST(TestFindGeneral, "quality of find()");
			OONET_DECLARE_SUBTEST(TestNotFoundEmpty, "find() on empty string");
			OONET_DECLARE_SUBTEST(TestNotFound, "find() for missing");
			OONET_DECLARE_SUBTEST(TestFindEmptyPattern, "find() with empty pattern");
			
			// Modifiers
			OONET_DECLARE_SUBTEST(TestGetUntilGeneral, "quality of get_until()");
			OONET_DECLARE_SUBTEST(TestGetUntilWrong, "get_until() wrong offset");
			OONET_DECLARE_SUBTEST(TestGetFromGeneral, "quality of get_from()");
			OONET_DECLARE_SUBTEST(TestGetFromWrong, "get_from() wrong offset");
			OONET_DECLARE_SUBTEST(TestSliceGeneral, "quality of sub_data()");
			OONET_DECLARE_SUBTEST(TestSliceWrongOffset, "sub_data() wrong offset");
			OONET_DECLARE_SUBTEST(TestSliceWrongBoundries, "sub_data() wrong boundries");
			OONET_DECLARE_SUBTEST(TestSwap, "quality of swap()");
															
			OONET_DECLARE_SUBTEST(TestEnormousAlloc, "Enormous allocation");
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestEnormousReAlloc, "Enormous reallocation", "ExceptionBadAllocation");
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestAssertNullPointer, "Assert on Null pointer", "ExceptionAssertationFailed");
			OONET_DECLARE_SUBTEST(TestAddCompare, "Add and compare");
			OONET_DECLARE_SUBTEST(TestAddByte, "Addition of byte");
			OONET_DECLARE_SUBTEST(TestFillCtor, "Fill constructors");

			OONET_DECLARE_SUBTEST_SPEED(TestFindByteIn100MBlock, "find() 1B in 100M block");
			OONET_DECLARE_SUBTEST_SPEED(TestFindBlockIn100MBlock, "find() 10K in 100M fast");
			OONET_DECLARE_SUBTEST_SPEED(TestFindBlockDifficult, "find() 10K in 100M hard");
			OONET_DECLARE_SUBTEST_SPEED(TestManualSlice, "benchmark manual sub_data()");
			OONET_DECLARE_SUBTEST_SPEED(TestRealSlice, "benchmark usign sub_data()");

			OONET_DECLARE_SUBTEST(TestAStringExporter, "quality of to_string()");
			OONET_DECLARE_SUBTEST(TestWStringExporter, "quality of to_wstring()");
			OONET_DECLARE_SUBTEST(TestCoW, "quality of CoW (basic)");
			OONET_DECLARE_SUBTEST(TestCoWExtend, "quality of CoW (extended)");


		public:
			// Constructor
			test_binary_data()
				:test_set("binary_data")
			{
				OONET_EXECUTE_SUBTEST(TestEmptyConstructor);
				OONET_EXECUTE_SUBTEST(TestCopyConstructor);
				OONET_EXECUTE_SUBTEST(TestMemRefConstructor);
				OONET_EXECUTE_SUBTEST(TestRangeConstructor);
				
				// Operators
				OONET_EXECUTE_SUBTEST(TestOperatorEq);
				OONET_EXECUTE_SUBTEST(TestOperatorLess);
				OONET_EXECUTE_SUBTEST(TestOperatorLessSpeed);
				OONET_EXECUTE_SUBTEST(TestOperatorGreater);
				OONET_EXECUTE_SUBTEST(TestOperatorEqLess);
				OONET_EXECUTE_SUBTEST(TestOperatorEqGreater);
				OONET_EXECUTE_SUBTEST(TestOperatorElement);
				
				
				// Element Acccess
				OONET_EXECUTE_SUBTEST(TestForwardIterator);
				OONET_EXECUTE_SUBTEST(TestReverseIterator);
				OONET_EXECUTE_SUBTEST(TestFrontBack);
				OONET_EXECUTE_SUBTEST(TestCArray);
				OONET_EXECUTE_SUBTEST(TestAtElementWrongOffeset);
				OONET_EXECUTE_SUBTEST(TestAtElementGeneral);
				OONET_EXECUTE_SUBTEST(TestFindGeneral);
				OONET_EXECUTE_SUBTEST(TestNotFoundEmpty);
				OONET_EXECUTE_SUBTEST(TestNotFound);
				OONET_EXECUTE_SUBTEST(TestFindEmptyPattern);
				
				// Modifiers
				OONET_EXECUTE_SUBTEST(TestGetUntilGeneral);
				OONET_EXECUTE_SUBTEST(TestGetUntilWrong);
				OONET_EXECUTE_SUBTEST(TestGetFromGeneral);
				OONET_EXECUTE_SUBTEST(TestGetFromWrong);
				OONET_EXECUTE_SUBTEST(TestSliceGeneral);
				OONET_EXECUTE_SUBTEST(TestSliceWrongOffset);
				OONET_EXECUTE_SUBTEST(TestSliceWrongBoundries);
				OONET_EXECUTE_SUBTEST(TestSwap);
																
				OONET_EXECUTE_SUBTEST(TestEnormousAlloc);
				//OONET_EXECUTE_SUBTEST(TestEnormousReAlloc);
				OONET_EXECUTE_SUBTEST(TestAssertNullPointer);
				OONET_EXECUTE_SUBTEST(TestAddCompare);
				OONET_EXECUTE_SUBTEST(TestAddByte);
				OONET_EXECUTE_SUBTEST(TestFillCtor);

				OONET_EXECUTE_SUBTEST(TestFindByteIn100MBlock);
				OONET_EXECUTE_SUBTEST(TestFindBlockIn100MBlock);
				OONET_EXECUTE_SUBTEST(TestFindBlockDifficult);
				OONET_EXECUTE_SUBTEST(TestManualSlice);
				OONET_EXECUTE_SUBTEST(TestRealSlice);

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

