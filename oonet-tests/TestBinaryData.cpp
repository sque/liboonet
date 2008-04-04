#include "TestBinaryData.h"

namespace oonet
{
	static TestBinaryData theBinaryTest;

	const byte Char_M = (byte) 'm';
	const byte Char_A = (byte) 'a';
	const byte Char_NULL = (byte) NULL;

	// Sub tests implementation
	bool TestBinaryData::TestStringConstructor::OnExecute()
	{	binary_data b1, b2;

		b1 = binary_data("malaka!!");
		b2 = binary_data("lolo");

		// Check if they are different
		if ((b1 == b2) || (! (b1 != b2)))
			return false;

		// Create a new one with same string
		b1 = binary_data("lolo");
		if (b1 != b2)
			return false;
		return true;
	}

	bool TestBinaryData::TestEqOperator::OnExecute()
	{	binary_data b1, b2;

		b1 = binary_data("lola");
		b2 = binary_data("lola");
		if (b1 != b2)
			return false;

		// test operator== with same sizes
		b1 = binary_data("1234");
		b2 = binary_data("qwer");
		if (b1 == b2)
			return false;
		return true;
	}

	bool TestBinaryData::TestEnormousAlloc::OnExecute()
	{	binary_data * pb = new binary_data(Char_A, 3000000000);
		delete pb;
		return false;
	}

	bool TestBinaryData::TestEnormousReAlloc::OnExecute()
	{	binary_data b1, bigSafeBlock;

		bigSafeBlock = binary_data(Char_A, 100000000);

		// 10 GB memmory realloc
		for(long i = 0;i < 10000;i++)
			b1 += bigSafeBlock;
		return false;
	}

	bool TestBinaryData::TestAssertNullPointer::OnExecute()
	{	binary_data * pb = new binary_data((byte *)NULL, 1);
		delete pb;
		return false;
	}

	bool TestBinaryData::TestAddCompare::OnExecute()
	{	byte Array_A[30], Array_B[30], Array_Sum[60];
		binary_data b1, b2, b3, b4;
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
		b1 = binary_data(Array_A, 30);
		b2 = binary_data(Array_B, 30);
		b3 = binary_data(Array_Sum, 60);
		b4 = b1 + b2;   // Create a new from adition

		// Check if it is the same with a new created from the sum array
		if (b3 != b4)
			return false;

		// Check data in low level
		if (b4.size() != 60)
			return false;

		// Check data in low level
		if (memcmp(b4.get_data_ptr(), Array_Sum, 60) != 0)
			return false;

		// Check += with self
		b1 = binary_data(Char_A, 2) + binary_data(Char_M, 2);
		b2 = b1;
		b2 += b1;
		b1 += b1;
		if (b1 != b2)
			return false;
		return true;
	}

	bool TestBinaryData::TestAddByte::OnExecute()
	{	binary_data b1, b2;
		int i;

		// byte operator+=
		b2 = binary_data(Char_M, 30) + binary_data(Char_A, 30);
	    b1 = binary_data::EMPTY;
		for(i = 0;i < 30;i++)
			b1 += Char_M;

		for(i = 0;i < 30;i++)
			b1 += Char_A;

		if (b1 != b2)
			return false;

		// byte operator +
        b1 = binary_data::EMPTY;
		for(i = 0;i < 30;i++)
			b1 = b1 + Char_M;
		for(i = 0;i < 30;i++)
			b1 = b1 + Char_A;

		if (b1 != b2)
			return false;
		return true;
	}

	bool TestBinaryData::TestFillCtor::OnExecute()
	{	byte Array_M[30], Array_A[30];
		binary_data b1, b2, b3;

		for (int i = 0;i < 30;i++)
		{
			Array_M[i] = Char_M;
			Array_A[i] = Char_A;
		}

		b1 = binary_data(Char_M, 30);
		b2 = binary_data(Array_M, 30);
		b3 = binary_data(Array_A, 30);
	    if (b1 != b2)
		    return false;

		if (b1 == b3)
			return false;

		return true;
	}

	bool TestBinaryData::TestNotFoundEmpty::OnExecute()
	{	binary_data b1;

		if (b1.find(binary_data(Char_M, 1)) != binary_data::npos)
			return false;
		return true;
	}

	bool TestBinaryData::TestNotFound::OnExecute()
	{	binary_data b1;

		b1 = binary_data(Char_A, 30);
		if (b1.find(binary_data(Char_M, 1)) != binary_data::npos)
			return false;
		return true;
	}

	bool TestBinaryData::TestFindEmptyPattern::OnExecute()
	{	binary_data b1;

		b1 = binary_data(Char_A, 30);
		b1.find(binary_data(Char_M, 0));
		return false;
	}

	bool TestBinaryData::TestFindGeneral::OnExecute()
	{	binary_data b1;
		size_t pos;

		b1 = binary_data(Char_A, 30) + binary_data(Char_M, 30);

		pos = b1.find(binary_data(Char_M, 1));
		if (pos != 30)
			return false;
		pos = b1.find(binary_data(Char_M, 2));
		if (pos != 30)
			return false;
		pos = b1.find(binary_data(Char_M, 30));
		if (pos != 30)
			return false;

        // We will create a string in memory kikikokoko but the size will be 4!
        b1 = binary_data(string("kokokokoko"));
        b1 = binary_data(string("kiki"));
        if (binary_data::npos != b1.find(binary_data(string("ko"))))
            return false;

        // We will try to find for last character of a string
        b1 = binary_data(string("kokoa           "));
        b1 = binary_data(string("kokoa"));
        if (binary_data::npos == b1.find(binary_data(string("a"))))
            return false;


        // We will try to find a string starting from the last character
        b1 = binary_data(string("kokoalb           "));
        b1 = binary_data(string("kokoa"));
        if (binary_data::npos != b1.find(binary_data(string("ala"))))
            return false;

        // We will try to find a string starting from the last character
        b1 = binary_data(string("kokoala           "));
        b1 = binary_data(string("kokoa"));
        if (binary_data::npos != b1.find(binary_data(string("ala"))))
            return false;

        // We will try to find a character at the begining
        b1 = binary_data(string("akokoal           "));
        if (binary_data::npos == b1.find(binary_data(string("a"))))
            return false;


		return true;
	}

	bool TestBinaryData::TestFindByteIn100MBlock::OnExecute()
	{	binary_data b1;
		size_t pos;

		b1 = binary_data(Char_A, 100000000);
		b1 += binary_data(Char_M, 1);
		b1 += binary_data(Char_A, 10000000);

		ResetTimer();	// This is the part we want
		pos = b1.find(binary_data(Char_M, 1));
		if (pos != 100000000)
			return false;

		return true;
	}

	bool TestBinaryData::TestFindBlockIn100MBlock::OnExecute()
	{	binary_data b1;
		size_t pos;

		b1 = binary_data(Char_A, 100000000);
		b1 += binary_data(Char_M, 10000);
		b1 += binary_data(Char_A, 10000000);

		ResetTimer();	// This is the part we want
		pos = b1.find(binary_data(Char_M, 10000));
		if (pos != 100000000)
			return false;

		return true;
	}

	bool TestBinaryData::TestFindBlockDifficult::OnExecute()
	{	binary_data b1;
		size_t pos;

		b1 = binary_data(Char_M, 1) + binary_data(Char_A, 1);
		for(long i = 0;i < 26; i++)
		{	b1 += b1;		}

		b1 = b1.get_until(100000000);
		b1 += binary_data(Char_M, 10000);
		b1 += binary_data(Char_A, 10000000);

		ResetTimer();	// This is the part we want
		pos = b1.find(binary_data(Char_M, 10000));
		if (pos != 100000000)
			return false;

		return true;
	}

	bool TestBinaryData::TestGetFromWrong::OnExecute()
	{	binary_data b1(Char_M, 30);

		b1.get_from(31);
		return false;
	}

	bool TestBinaryData::TestGetFromGeneral::OnExecute()
	{	binary_data b1, b2;

		b1 = binary_data(Char_M, 30);

		// > We must be able to get the last offset and return empty without exception
		b1.get_from(30);

		b1 += binary_data(Char_A, 30);
		b2 = binary_data(Char_A, 30);

		// Test right offset
		if (b1.get_from(30) != b2)
			return false;

		// Test offset from find with various size of patters
		if (b1.get_from(b1.find(binary_data(Char_A, 1))) != b2)
			return false;

		if (b1.get_from(b1.find(binary_data(Char_A, 2))) != b2)
			return false;

		if (b1.get_from(b1.find(binary_data(Char_A, 10))) != b2)
			return false;

		// Test to get for disambiguation of zero-based
		if (b1.get_from(0) != b1)
			return false;

		if (b1.get_from(1) == b1)
			return false;

		return true;
	}

	bool TestBinaryData::TestGetUntilWrong::OnExecute()
	{	binary_data b1(Char_M, 30);

		b1.get_until(31);
		return false;
	}

	bool TestBinaryData::TestGetUntilGeneral::OnExecute()
	{	binary_data b1, b2;

		b1 = binary_data(Char_M, 30);

		// > We must be able to get all the data with get until
		b1.get_until(30);

		b1 += binary_data(Char_A, 30);
		b2 = binary_data(Char_M, 30);

		// Test right offset
		if (b1.get_until(30) != b2)
			return false;

		// Test offset from find with various size of patters
		if (b1.get_until(b1.find(binary_data(Char_A, 1))) != b2)
			return false;

		if (b1.get_until(b1.find(binary_data(Char_A, 2))) != b2)
			return false;

		if (b1.get_until(b1.find(binary_data(Char_A, 10))) != b2)
			return false;

		// We must be able to get from start and get empty string without exception
		if (b1.get_until(0) != binary_data::EMPTY)
			return false;

		// We must be able to get 1 byte
		if (b1.get_until(1) != binary_data(Char_M, 1))
			return false;

		return true;
	}

	bool TestBinaryData::TestSliceWrongOffset::OnExecute()
	{	binary_data b1;

		b1 = binary_data(Char_M, 1000);
		b1.slice(1001, 0);

		return false;
	}

	bool TestBinaryData::TestSliceWrongBoundries::OnExecute()
	{	binary_data b1;

		b1 = binary_data(Char_M, 1000);
		b1.slice(999, 2);

		return false;
	}

	bool TestBinaryData::TestSliceGeneral::OnExecute()
	{	binary_data b1;

		b1 = binary_data(Char_A, 1000);
		b1 += binary_data(Char_M, 1000);
		b1 += binary_data(Char_A, 1000);

		// A general test
		if (b1.slice(1000,1000) != binary_data(Char_M, 1000))
			return false;

		// In limits tests
		if (b1.slice(0, 1000) != binary_data(Char_A, 1000))
			return false;
		if (b1.slice(2000, 1000) != binary_data(Char_A, 1000))
			return false;

		// zero size results
		if (b1.slice(3000, 0) != binary_data::EMPTY)
			return false;
		if (b1.slice(0, 0) != binary_data::EMPTY)
			return false;
		if (b1.slice(10, 0) != binary_data::EMPTY)
			return false;
		return true;

	}
	bool TestBinaryData::TestManualSlice::OnExecute()
	{	binary_data b1, b2, body;

		body = binary_data(Char_M, 1000000);
		b1 = binary_data(_T("askdfja klsdjf;lakshdfjash ajdshf kjadshfkj ahsdfkjha skjdfhakjsdhf START"));
		b1 += body;
		b1 += binary_data(_T("STOP askdfja klsdjf;lakshdfjash ajdshf kjadshfkj ahsdfkjha skjdfhakjsdhf"));

		ResetTimer();
		for (int i = 0; i < 1000; i ++)
		{
			b2 = b1.get_from(b1.find(binary_data(_T("START"))) + (sizeof(TCHAR) * 5) );
			b2 = b2.get_until(b2.find(binary_data(_T("STOP"))));
		}

		if (b2 != body)
			return false;
		return true;
	}


	bool TestBinaryData::TestRealSlice::OnExecute()
	{	binary_data b1, b2, body;
		size_t offset, sz;

		body = binary_data(Char_M, 1000000);
		b1 = binary_data(_T("askdfja klsdjf;lakshdfjash ajdshf kjadshfkj ahsdfkjha skjdfhakjsdhf START"));
		b1 += body;
		b1 += binary_data(_T("STOP askdfja klsdjf;lakshdfjash ajdshf kjadshfkj ahsdfkjha skjdfhakjsdhf"));

		ResetTimer();
		for (int i = 0; i < 1000; i ++)
		{
			offset = b1.find(binary_data(_T("START"))) + (sizeof(TCHAR) * 5);
			sz = b1.find(binary_data(_T("STOP"))) - offset;
			b2 = b1.slice(offset, sz);
		}

		if (b2 != body)
			return false;
		return true;
	}

	bool TestBinaryData::TestElementWrongOffeset::OnExecute()
	{	binary_data b1(Char_M, 1000);
		byte b;

		b = b1[1001];
		return false;

	}

	bool TestBinaryData::TestElementGeneral::OnExecute()
	{	binary_data b1;

		b1 = binary_data("lolalilolalo");
		if (b1[0] != 'l')
			return false;
		if (b1[1] != 'o')
			return false;
		if (b1[b1.size()-1] != 'o')
			return false;

		return true;
	}

	bool TestBinaryData::TestAStringExporter::OnExecute()
	{	binary_data b1 = binary_data(string("koukouroukou1"));

        //printf("%s\n", b1.GetStringA().c_str());
        if (b1.to_string() != "koukouroukou1")
            return false;

        b1 = binary_data(string("kiki"));
        if (b1.to_string() != "kiki")
            return false;

		return true;
	}

	bool TestBinaryData::TestWStringExporter::OnExecute()
	{	binary_data b1 = binary_data(wstring(L"koukouroukou1"));

        //printf("TEST: -%s-\n", StringConverter(b1.GetStringW()).toAnsi().c_str());
        if (b1.to_wstring() != L"koukouroukou1")
            return false;

        b1 = binary_data(wstring(L"kiki"));
        if (b1.to_wstring() != L"kiki")
            return false;

		return true;
	}
};	// !oonet namespace
