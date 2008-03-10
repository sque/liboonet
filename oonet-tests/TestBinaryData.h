#ifndef BINARYDATA_TEST_H_INCLUDED
#define BINARYDATA_TEST_H_INCLUDED

#include "BinaryData.h"
#include "Test.h"

namespace Slib
{
	class TestBinaryData
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		SLIB_DECLARESUBTEST(TestStringConstructor,  _T("Constructor (String)") );
		SLIB_DECLARESUBTEST(TestEqOperator,  _T("Operator==()") );
		SLIB_DECLARESUBTESTEXC(TestEnormousAlloc,  _T("Enormous allocation"), _T("ExceptionBadAllocation"));
		SLIB_DECLARESUBTESTEXC(TestEnormousReAlloc,  _T("Enormous reallocation"), _T("ExceptionBadAllocation"));
		SLIB_DECLARESUBTESTEXC(TestAssertNullPointer, _T("Assert on Null pointer"), _T("ExceptionAssertationFailed"));
		SLIB_DECLARESUBTEST(TestAddCompare, _T("Add and compare"));
		SLIB_DECLARESUBTEST(TestAddByte, _T("Addition of Byte"));
		SLIB_DECLARESUBTEST(TestFillCtor, _T("Fill constructors"));
		SLIB_DECLARESUBTEST(TestNotFoundEmpty, _T("Find() on empty string"));
		SLIB_DECLARESUBTEST(TestNotFound, _T("Find() for missing"));
		SLIB_DECLARESUBTESTEXC(TestFindEmptyPattern, _T("Find() with empty pattern"), _T("ExceptionWrongArgument"));
		SLIB_DECLARESUBTEST(TestFindGeneral, _T("Find() general quality"));
		SLIB_DECLARESUBTEST(TestFindByteIn100MBlock, _T("Find() 1B in 100M block"));
		SLIB_DECLARESUBTEST(TestFindBlockIn100MBlock, _T("Find() 10K in 100M fast"));
		SLIB_DECLARESUBTEST(TestFindBlockDifficult, _T("Find() 10K in 100M hard"));
		SLIB_DECLARESUBTESTEXC(TestGetFromWrong, _T("GetFrom() wrong offset"), _T("ExceptionNotFound"));
		SLIB_DECLARESUBTEST(TestGetFromGeneral, _T("GetFrom() general quality"));
		SLIB_DECLARESUBTESTEXC(TestGetUntilWrong, _T("GetUntil() wrong offset"), _T("ExceptionNotFound"));
		SLIB_DECLARESUBTEST(TestGetUntilGeneral, _T("GetUntil() general quality"));
		SLIB_DECLARESUBTESTEXC(TestSliceWrongOffset, _T("Slice() wrong offset"), _T("ExceptionNotFound"));
		SLIB_DECLARESUBTESTEXC(TestSliceWrongBoundries, _T("Slice() wrong boundries"), _T("ExceptionNotFound"));
		SLIB_DECLARESUBTEST(TestSliceGeneral, _T("Slice() general quality"));
		SLIB_DECLARESUBTEST(TestManualSlice, _T("Manual slice experiment"));
		SLIB_DECLARESUBTEST(TestRealSlice, _T("Same with Slice()"));
		SLIB_DECLARESUBTESTEXC(TestElementWrongOffeset, _T("operator[] wrong offset"), _T("ExceptionNotFound"));
		SLIB_DECLARESUBTEST(TestElementGeneral, _T("operator[] general quality"));
		SLIB_DECLARESUBTEST(TestAStringExporter, _T("Test exporting to AString"));
		SLIB_DECLARESUBTEST(TestWStringExporter, _T("Test exporting to WString"));

	public:
		// Constructor
		TestBinaryData()
			:Test(_T("BinaryData"))
		{
			SLIB_REGISTERSUBTEST(TestStringConstructor);
			SLIB_REGISTERSUBTEST(TestEqOperator);
			SLIB_REGISTERSUBTEST(TestEnormousAlloc);
			// Ta pinei sto vmware...  SLIB_REGISTERSUBTEST(TestEnormousReAlloc);
			SLIB_REGISTERSUBTEST(TestAssertNullPointer);
			SLIB_REGISTERSUBTEST(TestAddCompare);
			SLIB_REGISTERSUBTEST(TestAddByte);
			SLIB_REGISTERSUBTEST(TestFillCtor);
			SLIB_REGISTERSUBTEST(TestNotFoundEmpty);
			SLIB_REGISTERSUBTEST(TestNotFound);
			SLIB_REGISTERSUBTEST(TestFindEmptyPattern);
			SLIB_REGISTERSUBTEST(TestFindGeneral);
			SLIB_REGISTERSUBTEST(TestFindByteIn100MBlock);
			SLIB_REGISTERSUBTEST(TestFindBlockIn100MBlock);
			SLIB_REGISTERSUBTEST(TestFindBlockDifficult);
			SLIB_REGISTERSUBTEST(TestGetFromWrong);
			SLIB_REGISTERSUBTEST(TestGetFromGeneral);
			SLIB_REGISTERSUBTEST(TestGetUntilWrong);
			SLIB_REGISTERSUBTEST(TestGetUntilGeneral);
			SLIB_REGISTERSUBTEST(TestSliceWrongOffset);
			SLIB_REGISTERSUBTEST(TestSliceWrongBoundries);
			SLIB_REGISTERSUBTEST(TestSliceGeneral);
			SLIB_REGISTERSUBTEST(TestManualSlice);
			SLIB_REGISTERSUBTEST(TestRealSlice);
			SLIB_REGISTERSUBTEST(TestElementWrongOffeset);
			SLIB_REGISTERSUBTEST(TestElementGeneral);
			SLIB_REGISTERSUBTEST(TestAStringExporter);
			SLIB_REGISTERSUBTEST(TestWStringExporter);
		}

	} ;	//! BinaryData test
};	//! Slib namespace

#endif // BINARYDATA_TEST_H_INCLUDED
