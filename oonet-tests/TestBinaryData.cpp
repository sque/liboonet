#include "TestBinaryData.h"

namespace OONet
{
	static TestBinaryData theBinaryTest;

	const Byte Char_M = (Byte) 'm';
	const Byte Char_A = (Byte) 'a';
	const Byte Char_NULL = (Byte) NULL;

	// Sub tests implementation
	bool TestBinaryData::TestStringConstructor::OnExecute()
	{	BinaryData b1, b2;

		b1 = BinaryData("malaka!!");
		b2 = BinaryData("lolo");

		// Check if they are different
		if ((b1 == b2) || (! (b1 != b2)))
			return false;

		// Create a new one with same string
		b1 = BinaryData("lolo");
		if (b1 != b2)
			return false;
		return true;
	}

	bool TestBinaryData::TestEqOperator::OnExecute()
	{	BinaryData b1, b2;

		b1 = BinaryData("lola");
		b2 = BinaryData("lola");
		if (b1 != b2)
			return false;

		// test operator== with same sizes
		b1 = BinaryData("1234");
		b2 = BinaryData("qwer");
		if (b1 == b2)
			return false;
		return true;
	}

	bool TestBinaryData::TestEnormousAlloc::OnExecute()
	{	BinaryData * pb = new BinaryData(Char_A, 3000000000);
		delete pb;
		return false;
	}

	bool TestBinaryData::TestEnormousReAlloc::OnExecute()
	{	BinaryData b1, bigSafeBlock;

		bigSafeBlock = BinaryData(Char_A, 100000000);

		// 10 GB memmory realloc
		for(long i = 0;i < 10000;i++)
			b1 += bigSafeBlock;
		return false;
	}

	bool TestBinaryData::TestAssertNullPointer::OnExecute()
	{	BinaryData * pb = new BinaryData((Byte *)NULL, 1);
		delete pb;
		return false;
	}

	bool TestBinaryData::TestAddCompare::OnExecute()
	{	Byte Array_A[30], Array_B[30], Array_Sum[60];
		BinaryData b1, b2, b3, b4;
		int i;

		for(i =0;i < 30;i++)
		{
			Array_A[i] = Char_M;
			Array_Sum[i] = Char_M;
		}

		for(i=0;i < 30;i++)
		{
			Array_B[i] = Char_A;
			Array_Sum[i+30] = Char_A;
		};

		// Create Binary Objects
		b1 = BinaryData(Array_A, 30);
		b2 = BinaryData(Array_B, 30);
		b3 = BinaryData(Array_Sum, 60);
		b4 = b1 + b2;   // Create a new from adition

		// Check if it is the same with a new created from the sum array
		if (b3 != b4)
			return false;

		// Check data in low level
		if (b4.size() != 60)
			return false;

		// Check data in low level
		if (memcmp(b4.getDataPtr(), Array_Sum, 60) != 0)
			return false;

		// Check += with self
		b1 = BinaryData(Char_A, 2) + BinaryData(Char_M, 2);
		b2 = b1;
		b2 += b1;
		b1 += b1;
		if (b1 != b2)
			return false;
		return true;
	}

	bool TestBinaryData::TestAddByte::OnExecute()
	{	BinaryData b1, b2;
		int i;

		// Byte operator+=
		b2 = BinaryData(Char_M, 30) + BinaryData(Char_A, 30);
	    b1 = BinaryData::EMPTY;
		for(i = 0;i < 30;i++)
			b1 += Char_M;

		for(i = 0;i < 30;i++)
			b1 += Char_A;

		if (b1 != b2)
			return false;

		// Byte operator +
        b1 = BinaryData::EMPTY;
		for(i = 0;i < 30;i++)
			b1 = b1 + Char_M;
		for(i = 0;i < 30;i++)
			b1 = b1 + Char_A;

		if (b1 != b2)
			return false;
		return true;
	}

	bool TestBinaryData::TestFillCtor::OnExecute()
	{	Byte Array_M[30], Array_A[30];
		BinaryData b1, b2, b3;

		for (int i = 0;i < 30;i++)
		{
			Array_M[i] = Char_M;
			Array_A[i] = Char_A;
		}

		b1 = BinaryData(Char_M, 30);
		b2 = BinaryData(Array_M, 30);
		b3 = BinaryData(Array_A, 30);
	    if (b1 != b2)
		    return false;

		if (b1 == b3)
			return false;

		return true;
	}

	bool TestBinaryData::TestNotFoundEmpty::OnExecute()
	{	BinaryData b1;

		if (b1.find(BinaryData(Char_M, 1)) != BinaryData::npos)
			return false;
		return true;
	}

	bool TestBinaryData::TestNotFound::OnExecute()
	{	BinaryData b1;

		b1 = BinaryData(Char_A, 30);
		if (b1.find(BinaryData(Char_M, 1)) != BinaryData::npos)
			return false;
		return true;
	}

	bool TestBinaryData::TestFindEmptyPattern::OnExecute()
	{	BinaryData b1;

		b1 = BinaryData(Char_A, 30);
		b1.find(BinaryData(Char_M, 0));
		return false;
	}

	bool TestBinaryData::TestFindGeneral::OnExecute()
	{	BinaryData b1;
		size_t pos;

		b1 = BinaryData(Char_A, 30) + BinaryData(Char_M, 30);

		pos = b1.find(BinaryData(Char_M, 1));
		if (pos != 30)
			return false;
		pos = b1.find(BinaryData(Char_M, 2));
		if (pos != 30)
			return false;
		pos = b1.find(BinaryData(Char_M, 30));
		if (pos != 30)
			return false;

        // We will create a string in memory kikikokoko but the size will be 4!
        b1 = BinaryData(string("kokokokoko"));
        b1 = BinaryData(string("kiki"));
        if (BinaryData::npos != b1.find(BinaryData(string("ko"))))
            return false;

        // We will try to find for last character of a string
        b1 = BinaryData(string("kokoa           "));
        b1 = BinaryData(string("kokoa"));
        if (BinaryData::npos == b1.find(BinaryData(string("a"))))
            return false;


        // We will try to find a string starting from the last character
        b1 = BinaryData(string("kokoalb           "));
        b1 = BinaryData(string("kokoa"));
        if (BinaryData::npos != b1.find(BinaryData(string("ala"))))
            return false;

        // We will try to find a string starting from the last character
        b1 = BinaryData(string("kokoala           "));
        b1 = BinaryData(string("kokoa"));
        if (BinaryData::npos != b1.find(BinaryData(string("ala"))))
            return false;

        // We will try to find a character at the begining
        b1 = BinaryData(string("akokoal           "));
        if (BinaryData::npos == b1.find(BinaryData(string("a"))))
            return false;


		return true;
	}

	bool TestBinaryData::TestFindByteIn100MBlock::OnExecute()
	{	BinaryData b1;
		size_t pos;

		b1 = BinaryData(Char_A, 100000000);
		b1 += BinaryData(Char_M, 1);
		b1 += BinaryData(Char_A, 10000000);

		ResetTimer();	// This is the part we want
		pos = b1.find(BinaryData(Char_M, 1));
		if (pos != 100000000)
			return false;

		return true;
	}

	bool TestBinaryData::TestFindBlockIn100MBlock::OnExecute()
	{	BinaryData b1;
		size_t pos;

		b1 = BinaryData(Char_A, 100000000);
		b1 += BinaryData(Char_M, 10000);
		b1 += BinaryData(Char_A, 10000000);

		ResetTimer();	// This is the part we want
		pos = b1.find(BinaryData(Char_M, 10000));
		if (pos != 100000000)
			return false;

		return true;
	}

	bool TestBinaryData::TestFindBlockDifficult::OnExecute()
	{	BinaryData b1;
		size_t pos;

		b1 = BinaryData(Char_M, 1) + BinaryData(Char_A, 1);
		for(long i = 0;i < 26; i++)
		{	b1 += b1;		}

		b1 = b1.getUntil(100000000);
		b1 += BinaryData(Char_M, 10000);
		b1 += BinaryData(Char_A, 10000000);

		ResetTimer();	// This is the part we want
		pos = b1.find(BinaryData(Char_M, 10000));
		if (pos != 100000000)
			return false;

		return true;
	}

	bool TestBinaryData::TestGetFromWrong::OnExecute()
	{	BinaryData b1(Char_M, 30);

		b1.getFrom(31);
		return false;
	}

	bool TestBinaryData::TestGetFromGeneral::OnExecute()
	{	BinaryData b1, b2;

		b1 = BinaryData(Char_M, 30);

		// > We must be able to get the last offset and return empty without exception
		b1.getFrom(30);

		b1 += BinaryData(Char_A, 30);
		b2 = BinaryData(Char_A, 30);

		// Test right offset
		if (b1.getFrom(30) != b2)
			return false;

		// Test offset from find with various size of patters
		if (b1.getFrom(b1.find(BinaryData(Char_A, 1))) != b2)
			return false;

		if (b1.getFrom(b1.find(BinaryData(Char_A, 2))) != b2)
			return false;

		if (b1.getFrom(b1.find(BinaryData(Char_A, 10))) != b2)
			return false;

		// Test to get for disambiguation of zero-based
		if (b1.getFrom(0) != b1)
			return false;

		if (b1.getFrom(1) == b1)
			return false;

		return true;
	}

	bool TestBinaryData::TestGetUntilWrong::OnExecute()
	{	BinaryData b1(Char_M, 30);

		b1.getUntil(31);
		return false;
	}

	bool TestBinaryData::TestGetUntilGeneral::OnExecute()
	{	BinaryData b1, b2;

		b1 = BinaryData(Char_M, 30);

		// > We must be able to get all the data with get until
		b1.getUntil(30);

		b1 += BinaryData(Char_A, 30);
		b2 = BinaryData(Char_M, 30);

		// Test right offset
		if (b1.getUntil(30) != b2)
			return false;

		// Test offset from find with various size of patters
		if (b1.getUntil(b1.find(BinaryData(Char_A, 1))) != b2)
			return false;

		if (b1.getUntil(b1.find(BinaryData(Char_A, 2))) != b2)
			return false;

		if (b1.getUntil(b1.find(BinaryData(Char_A, 10))) != b2)
			return false;

		// We must be able to get from start and get empty string without exception
		if (b1.getUntil(0) != BinaryData::EMPTY)
			return false;

		// We must be able to get 1 byte
		if (b1.getUntil(1) != BinaryData(Char_M, 1))
			return false;

		return true;
	}

	bool TestBinaryData::TestSliceWrongOffset::OnExecute()
	{	BinaryData b1;

		b1 = BinaryData(Char_M, 1000);
		b1.slice(1001, 0);

		return false;
	}

	bool TestBinaryData::TestSliceWrongBoundries::OnExecute()
	{	BinaryData b1;

		b1 = BinaryData(Char_M, 1000);
		b1.slice(999, 2);

		return false;
	}

	bool TestBinaryData::TestSliceGeneral::OnExecute()
	{	BinaryData b1;

		b1 = BinaryData(Char_A, 1000);
		b1 += BinaryData(Char_M, 1000);
		b1 += BinaryData(Char_A, 1000);

		// A general test
		if (b1.slice(1000,1000) != BinaryData(Char_M, 1000))
			return false;

		// In limits tests
		if (b1.slice(0, 1000) != BinaryData(Char_A, 1000))
			return false;
		if (b1.slice(2000, 1000) != BinaryData(Char_A, 1000))
			return false;

		// zero size results
		if (b1.slice(3000, 0) != BinaryData::EMPTY)
			return false;
		if (b1.slice(0, 0) != BinaryData::EMPTY)
			return false;
		if (b1.slice(10, 0) != BinaryData::EMPTY)
			return false;
		return true;

	}
	bool TestBinaryData::TestManualSlice::OnExecute()
	{	BinaryData b1, b2, body;

		body = BinaryData(Char_M, 1000000);
		b1 = BinaryData(_T("askdfja klsdjf;lakshdfjash ajdshf kjadshfkj ahsdfkjha skjdfhakjsdhf START"));
		b1 += body;
		b1 += BinaryData(_T("STOP askdfja klsdjf;lakshdfjash ajdshf kjadshfkj ahsdfkjha skjdfhakjsdhf"));

		ResetTimer();
		for (int i = 0; i < 1000; i ++)
		{
			b2 = b1.getFrom(b1.find(BinaryData(_T("START"))) + (sizeof(TCHAR) * 5) );
			b2 = b2.getUntil(b2.find(BinaryData(_T("STOP"))));
		}

		if (b2 != body)
			return false;
		return true;
	}


	bool TestBinaryData::TestRealSlice::OnExecute()
	{	BinaryData b1, b2, body;
		size_t offset, sz;

		body = BinaryData(Char_M, 1000000);
		b1 = BinaryData(_T("askdfja klsdjf;lakshdfjash ajdshf kjadshfkj ahsdfkjha skjdfhakjsdhf START"));
		b1 += body;
		b1 += BinaryData(_T("STOP askdfja klsdjf;lakshdfjash ajdshf kjadshfkj ahsdfkjha skjdfhakjsdhf"));

		ResetTimer();
		for (int i = 0; i < 1000; i ++)
		{
			offset = b1.find(BinaryData(_T("START"))) + (sizeof(TCHAR) * 5);
			sz = b1.find(BinaryData(_T("STOP"))) - offset;
			b2 = b1.slice(offset, sz);
		}

		if (b2 != body)
			return false;
		return true;
	}

	bool TestBinaryData::TestElementWrongOffeset::OnExecute()
	{	BinaryData b1(Char_M, 1000);
		Byte b;

		b = b1[1001];
		return false;

	}

	bool TestBinaryData::TestElementGeneral::OnExecute()
	{	BinaryData b1;

		b1 = BinaryData("lolalilolalo");
		if (b1[0] != 'l')
			return false;
		if (b1[1] != 'o')
			return false;
		if (b1[b1.size()-1] != 'o')
			return false;

		return true;
	}

	bool TestBinaryData::TestAStringExporter::OnExecute()
	{	BinaryData b1 = BinaryData(string("koukouroukou1"));

        //printf("%s\n", b1.GetStringA().c_str());
        if (b1.toString() != "koukouroukou1")
            return false;

        b1 = BinaryData(string("kiki"));
        if (b1.toString() != "kiki")
            return false;

		return true;
	}

	bool TestBinaryData::TestWStringExporter::OnExecute()
	{	BinaryData b1 = BinaryData(wstring(L"koukouroukou1"));

        //printf("TEST: -%s-\n", StringConverter(b1.GetStringW()).toAnsi().c_str());
        if (b1.toWString() != L"koukouroukou1")
            return false;

        b1 = BinaryData(wstring(L"kiki"));
        if (b1.toWString() != L"kiki")
            return false;

		return true;
	}
};	// !OONet namespace
