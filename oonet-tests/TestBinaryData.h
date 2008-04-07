#ifndef BINARYDATA_TEST_H_INCLUDED
#define BINARYDATA_TEST_H_INCLUDED

#include "binary_data.hpp"
#include "Test.h"

namespace oonet
{
	class TestBinaryData
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		OONET_DECLARESUBTEST(TestStringConstructor,  _T("Constructor (String)") );
		OONET_DECLARESUBTEST(TestEqOperator,  _T("Operator==()") );
		OONET_DECLARESUBTESTEXC(TestEnormousAlloc,  _T("Enormous allocation"), _T("ExceptionBadAllocation"));
		OONET_DECLARESUBTESTEXC(TestEnormousReAlloc,  _T("Enormous reallocation"), _T("ExceptionBadAllocation"));
		OONET_DECLARESUBTESTEXC(TestAssertNullPointer, _T("Assert on Null pointer"), _T("ExceptionAssertationFailed"));
		OONET_DECLARESUBTEST(TestAddCompare, _T("Add and compare"));
		OONET_DECLARESUBTEST(TestAddByte, _T("Addition of byte"));
		OONET_DECLARESUBTEST(TestFillCtor, _T("Fill constructors"));
		OONET_DECLARESUBTEST(TestNotFoundEmpty, _T("find() on empty string"));
		OONET_DECLARESUBTEST(TestNotFound, _T("find() for missing"));
		OONET_DECLARESUBTESTEXC(TestFindEmptyPattern, _T("find() with empty pattern"), _T("ExceptionWrongArgument"));
		OONET_DECLARESUBTEST(TestFindGeneral, _T("find() general quality"));
		OONET_DECLARESUBTEST(TestFindByteIn100MBlock, _T("find() 1B in 100M block"));
		OONET_DECLARESUBTEST(TestFindBlockIn100MBlock, _T("find() 10K in 100M fast"));
		OONET_DECLARESUBTEST(TestFindBlockDifficult, _T("find() 10K in 100M hard"));
		OONET_DECLARESUBTEST(TestGetFromWrong, _T("GetFrom() wrong offset"));
		OONET_DECLARESUBTEST(TestGetFromGeneral, _T("GetFrom() general quality"));
		OONET_DECLARESUBTEST(TestGetUntilWrong, _T("GetUntil() wrong offset"));
		OONET_DECLARESUBTEST(TestGetUntilGeneral, _T("GetUntil() general quality"));
		OONET_DECLARESUBTEST(TestSliceWrongOffset, _T("sub_data() wrong offset"));
		OONET_DECLARESUBTEST(TestSliceWrongBoundries, _T("sub_data() wrong boundries"));
		OONET_DECLARESUBTEST(TestSliceGeneral, _T("sub_data() general quality"));
		OONET_DECLARESUBTEST(TestManualSlice, _T("Manual sub_data experiment"));
		OONET_DECLARESUBTEST(TestRealSlice, _T("Same with sub_data()"));
		OONET_DECLARESUBTESTEXC(TestElementWrongOffeset, _T("operator[] wrong offset"), _T("ExceptionNotFound"));
		OONET_DECLARESUBTEST(TestElementGeneral, _T("operator[] general quality"));
		OONET_DECLARESUBTEST(TestLessGeneral, _T("operator< general quality"));
		OONET_DECLARESUBTEST(TestLessSpeed, _T("operator< speed"));
		OONET_DECLARESUBTEST(TestAStringExporter, _T("Test exporting to AString"));
		OONET_DECLARESUBTEST(TestWStringExporter, _T("Test exporting to WString"));
		OONET_DECLARESUBTEST(TestCoW, _T("Test CoW (basic)"));
		OONET_DECLARESUBTEST(TestCoWExtend, _T("Test CoW (extended)"));

	public:
		// Constructor
		TestBinaryData()
			:Test(_T("binary_data"))
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
		}

	} ;	// !TestBinaryData class
};	// !oonet namespace

#endif // BINARYDATA_TEST_H_INCLUDED

