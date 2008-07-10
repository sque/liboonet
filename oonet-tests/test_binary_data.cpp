#include "test_binary_data.hpp"
#include <oonet/binary_data.hpp>

namespace oonet
{
	namespace test
	{
		static test_binary_data theBinaryTest;

		const byte Char_M = (byte) 'm';
		const byte Char_A = (byte) 'a';
		const byte Char_NULL = (byte) NULL;

		// Sub tests implementation
		bool test_binary_data::TestStringConstructor::operator()()
		{	binary_data b1, b2;

			b1 = cmem_ref("malaka!!");
			b2 = cmem_ref("lolo");

			// Check if they are different
			if ((b1 == b2) || (! (b1 != b2)))
				return false;

			// Create a new one with same string
			b1 = cmem_ref("lolo");
			if (b1 != b2)
				return false;
			return true;
		}

		bool test_binary_data::TestEqOperator::operator()()
		{	binary_data b1, b2;

			b1 = cmem_ref("lola");
			b2 = cmem_ref("lola");
			if (b1 != b2)
				return false;

			// test operator== with same sizes
			b1 = cmem_ref("1234");
			b2 = cmem_ref("qwer");
			if (b1 == b2)
				return false;
			return true;
		}

		bool test_binary_data::TestEnormousAlloc::operator()()
		{	binary_data * pb = new binary_data(Char_A, 3000000000u);
			delete pb;
			return false;
		}

		bool test_binary_data::TestEnormousReAlloc::operator()()
		{	binary_data b1, bigSafeBlock;

			bigSafeBlock = binary_data(Char_A, 100000000);

			// 10 GB memmory realloc
			for(long i = 0;i < 10000;i++)
				b1 += bigSafeBlock;
			return false;
		}

		bool test_binary_data::TestAssertNullPointer::operator()()
		{	binary_data * pb = new binary_data(cmem_ref(NULL, 1));
			delete pb;
			return false;
		}

		bool test_binary_data::TestAddCompare::operator()()
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
			b1 = cmem_ref(Array_A, 30);
			b2 = cmem_ref(Array_B, 30);
			b3 = cmem_ref(Array_Sum, 60);
			b4 = b1 + b2;   // Create a new from adition

			// Check if it is the same with a new created from the sum array
			if (b3 != b4)
				return false;

			// Check data in low level
			if (b4.size() != 60)
				return false;

			// Check data in low level
			if (memcmp(b4.c_array(), Array_Sum, 60) != 0)
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

		bool test_binary_data::TestAddByte::operator()()
		{	binary_data b1, b2;
			int i;

			// byte operator+=
			b2 = binary_data(Char_M, 30) + binary_data(Char_A, 30);
			b1 = binary_data::nothing;
			for(i = 0;i < 30;i++)
				b1 += cmem_ref(Char_M);

			for(i = 0;i < 30;i++)
				b1 += cmem_ref(Char_A);

			if (b1 != b2)
				return false;

			// byte operator +
			b1 = binary_data::nothing;
			for(i = 0;i < 30;i++)
				b1 = b1 + cmem_ref(Char_M);
			for(i = 0;i < 30;i++)
				b1 = b1 + cmem_ref(Char_A);

			if (b1 != b2)
				return false;
			return true;
		}

		bool test_binary_data::TestFillCtor::operator()()
		{	byte Array_M[30], Array_A[30];
			binary_data b1, b2, b3;

			for (int i = 0;i < 30;i++)
			{
				Array_M[i] = Char_M;
				Array_A[i] = Char_A;
			}

			b1 = binary_data(Char_M, 30);
			b2 = cmem_ref(Array_M, 30);
			b3 = cmem_ref(Array_A, 30);
			if (b1 != b2)
				return false;

			if (b1 == b3)
				return false;

			return true;
		}

		bool test_binary_data::TestNotFoundEmpty::operator()()
		{	binary_data b1;

			if (b1.find(binary_data(Char_M, 1)) != binary_data::npos)
				return false;
			return true;
		}

		bool test_binary_data::TestNotFound::operator()()
		{	binary_data b1;

			b1 = binary_data(Char_A, 30);
			if (b1.find(binary_data(Char_M, 1)) != binary_data::npos)
				return false;
			return true;
		}

		bool test_binary_data::TestFindEmptyPattern::operator()()
		{	binary_data b1;

			b1 = binary_data(Char_A, 30);
			b1.find(binary_data(Char_M, 0));
			return false;
		}

		bool test_binary_data::TestFindGeneral::operator()()
		{	binary_data b1;
			size_t pos;

			b1 = binary_data(Char_A, 30) + binary_data(Char_M, 30);

			// Simple test
			pos = b1.find(binary_data(Char_M, 1));
			if (pos != 30)
				return false;
			pos = b1.find(binary_data(Char_M, 2));
			if (pos != 30)
				return false;
			pos = b1.find(binary_data(Char_M, 30));
			if (pos != 30)
				return false;

			// Simple test with offset
			pos = b1.find(binary_data(Char_M, 1), 0);
			if (pos != 30)
				return false;
			pos = b1.find(binary_data(Char_A, 1), 0);
			if (pos != 0)
				return false;
			pos = b1.find(binary_data(Char_M, 1), 31);
			if (pos != 31)
				return false;
			pos = b1.find(binary_data(Char_M, 10), 32);
			if (pos != 32)
				return false;

			// We will create a string in memory kikikokoko but the size will be 4!
			b1 = cmem_ref("kokokokoko");
			b1 = cmem_ref("kiki");
			if (binary_data::npos != b1.find(cmem_ref("ko")))
				return false;
			if (binary_data::npos != b1.find(cmem_ref("ko"), 3))
				return false;
			if (binary_data::npos != b1.find(cmem_ref("ko"), 4))
				return false;
			if (binary_data::npos != b1.find(cmem_ref("ko"), 5))
				return false;

			// We will try to find for last character of a string
			b1 = cmem_ref("kokoa           ");
			b1 = cmem_ref("kokoa");
			if (binary_data::npos == b1.find(cmem_ref("a")))
				return false;


			// We will try to find a string starting from the last character
			b1 = cmem_ref("kokoalb           ");
			b1 = cmem_ref("kokoa");
			if (binary_data::npos != b1.find(cmem_ref("ala")))
				return false;

			// We will try to find a string starting from the last character
			b1 = cmem_ref("kokoala           ");
			b1 = cmem_ref("kokoa");
			if (binary_data::npos != b1.find(cmem_ref("ala")))
				return false;

			// We will try to find a character at the begining
			b1 = cmem_ref("akokoal           ");
			if (binary_data::npos == b1.find(cmem_ref("a")))
				return false;


			return true;
		}

		bool test_binary_data::TestFindByteIn100MBlock::operator()()
		{	binary_data b1;
			size_t pos;

			b1 = binary_data(Char_A, 100000000);
			b1 += binary_data(Char_M, 1);
			b1 += binary_data(Char_A, 10000000);

			reset_timer();	// This is the part we want
			pos = b1.find(binary_data(Char_M, 1));
			if (pos != 100000000)
				return false;

			return true;
		}

		bool test_binary_data::TestFindBlockIn100MBlock::operator()()
		{	binary_data b1;
			size_t pos;

			b1 = binary_data(Char_A, 100000000);
			b1 += binary_data(Char_M, 10000);
			b1 += binary_data(Char_A, 10000000);

			reset_timer();	// This is the part we want
			pos = b1.find(binary_data(Char_M, 10000));
			if (pos != 100000000)
				return false;

			return true;
		}

		bool test_binary_data::TestFindBlockDifficult::operator()()
		{	binary_data b1;
			size_t pos;

			b1 = binary_data(Char_M, 1) + binary_data(Char_A, 1);
			for(long i = 0;i < 26; i++)
			{	b1 += b1;		}

			b1 = b1.get_until(100000000);
			b1 += binary_data(Char_M, 10000);
			b1 += binary_data(Char_A, 10000000);

			reset_timer();	// This is the part we want
			pos = b1.find(binary_data(Char_M, 10000));
			if (pos != 100000000)
				return false;

			return true;
		}

		bool test_binary_data::TestGetFromWrong::operator()()
		{	binary_data b1(Char_M, 30);

			if (b1.get_from(31) != binary_data::nothing)
				return false;
			return true;
		}

		bool test_binary_data::TestGetFromGeneral::operator()()
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

		bool test_binary_data::TestGetUntilWrong::operator()()
		{	binary_data b1(Char_M, 30);

			if (b1.get_until(31) != b1)
				return false;
			return true;
		}

		bool test_binary_data::TestGetUntilGeneral::operator()()
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
			if (b1.get_until(0) != binary_data::nothing)
				return false;

			// We must be able to get 1 byte
			if (b1.get_until(1) != binary_data(Char_M, 1))
				return false;

			return true;
		}

		bool test_binary_data::TestSliceWrongOffset::operator()()
		{	binary_data b1;

			b1 = binary_data(Char_M, 1000);
			if (b1.sub_data(1001, 0) != binary_data::nothing)
				return false;
			return true;
		}

		bool test_binary_data::TestSliceWrongBoundries::operator()()
		{	binary_data b1;

			b1 = binary_data(Char_M, 1000);
			if (b1.sub_data(999, 2) != b1.get_from(999))
				return false;
			return true;
		}

		bool test_binary_data::TestSliceGeneral::operator()()
		{	binary_data b1;

			b1 = binary_data(Char_A, 1000);
			b1 += binary_data(Char_M, 1000);
			b1 += binary_data(Char_A, 1000);

			// A general test
			if (b1.sub_data(1000,1000) != binary_data(Char_M, 1000))
				return false;

			// In limits tests
			if (b1.sub_data(0, 1000) != binary_data(Char_A, 1000))
				return false;
			if (b1.sub_data(2000, 1000) != binary_data(Char_A, 1000))
				return false;
			if (b1.sub_data(0, binary_data::npos) != b1)
				return false;
			if (b1.sub_data(2000, binary_data::npos) != binary_data(Char_A, 1000))
				return false;

			// zero size results
			if (b1.sub_data(3000, 0) != binary_data::nothing)
				return false;
			if (b1.sub_data(0, 0) != binary_data::nothing)
				return false;
			if (b1.sub_data(10, 0) != binary_data::nothing)
				return false;
			return true;

		}
		bool test_binary_data::TestManualSlice::operator()()
		{	binary_data b1, b2, body;

			body = binary_data(Char_M, 1000000);
			b1 = cmem_ref(_T("askdfja klsdjf;lakshdfjash ajdshf kjadshfkj ahsdfkjha skjdfhakjsdhf START"));
			b1 += body;
			b1 += cmem_ref(_T("STOP askdfja klsdjf;lakshdfjash ajdshf kjadshfkj ahsdfkjha skjdfhakjsdhf"));

			reset_timer();
			for (int i = 0; i < 1000; i ++)
			{
				b2 = b1.get_from(b1.find(cmem_ref(_T("START"))) + (sizeof(TCHAR) * 5) );
				b2 = b2.get_until(b2.find(cmem_ref(_T("STOP"))));
			}

			if (b2 != body)
				return false;
			return true;
		}


		bool test_binary_data::TestRealSlice::operator()()
		{	binary_data b1, b2, body;
			size_t offset, sz;

			body = binary_data(Char_M, 1000000);
			b1 = cmem_ref(_T("askdfja klsdjf;lakshdfjash ajdshf kjadshfkj ahsdfkjha skjdfhakjsdhf START"));
			b1 += body;
			b1 += cmem_ref(_T("STOP askdfja klsdjf;lakshdfjash ajdshf kjadshfkj ahsdfkjha skjdfhakjsdhf"));

			reset_timer();
			for (int i = 0; i < 1000; i ++)
			{
				offset = b1.find(cmem_ref(_T("START"))) + (sizeof(TCHAR) * 5);
				sz = b1.find(cmem_ref(_T("STOP"))) - offset;
				b2 = b1.sub_data(offset, sz);
			}

			if (b2 != body)
				return false;
			return true;
		}

		bool test_binary_data::TestElementWrongOffeset::operator()()
		{	binary_data b1(Char_M, 1000);
			byte b;

			b = b1[1001];
			return true;

		}

		bool test_binary_data::TestElementGeneral::operator()()
		{	binary_data b1;

			b1 = cmem_ref("lolalilolalo");
			if (b1[0] != 'l')
				return false;
			if (b1[1] != 'o')
				return false;
			if (b1[b1.size()-1] != 'o')
				return false;

			return true;
		}
		
		bool test_binary_data::TestAtElementWrongOffeset::operator()()
		{	binary_data b1(Char_M, 1000);
			byte b;

			b = b1[1001];
			return false;

		}

		bool test_binary_data::TestAtElementGeneral::operator()()
		{	binary_data b1;

			b1 = cmem_ref("lolalilolalo");
			if (b1[0] != 'l')
				return false;
			if (b1[1] != 'o')
				return false;
			if (b1[b1.size()-1] != 'o')
				return false;

			return true;
		}

		bool test_binary_data::TestLessGeneral::operator()()
		{	binary_data a(cmem_ref("A"));
			binary_data b(cmem_ref("B"));
			binary_data ab(cmem_ref("AB"));
			binary_data ac(cmem_ref("AC"));
			binary_data bb(cmem_ref("BB"));

			// Empty must return false
			if (binary_data::nothing < binary_data::nothing)
				return false;

			// 1 character comparison
			if (b < a)
				return false;
			if (!(a < b))
				return false;

			// Check multibyte
			if (ac < ab)
				return false;
			if (!(ab < ac))
				return false;

			// Check equality test
			if (!(a<b||b<a))
				return false;

			// Check not equal test
			if (a<a||a<a)
				return false;

			// Check different size
			if (!(a < ab))
				return false;
			if (ab < a)
				return false;

			// Check smaller size that must be bigger as character
			if (b < ac)
				return false;
			if (!(ac < b))
				return false;

			return true;
		}

		bool test_binary_data::TestLessSpeed::operator()()
		{	binary_data a((byte)'a', 50000);
			binary_data b((byte)'a', 50000);
			a += cmem_ref("1");
			b += cmem_ref("2");

			// 1 character comparison
			if (b < a)
				return false;

			bool res;
			for(int i = 0;i < 5000; i++)
				res = b < a;

			return true;
		}

		bool test_binary_data::TestAStringExporter::operator()()
		{	binary_data b1 = cmem_ref("koukouroukou1");

			//printf("%s\n", b1.GetStringA().c_str());
			if (b1.to_string() != "koukouroukou1")
				return false;

			b1 = cmem_ref("kiki");
			if (b1.to_string() != "kiki")
				return false;

			return true;
		}

		bool test_binary_data::TestWStringExporter::operator()()
		{	binary_data b1 = cmem_ref(L"koukouroukou1");

			//printf("TEST: -%s-\n", StringConverter(b1.GetStringW()).toAnsi().c_str());
			if (b1.to_wstring() != L"koukouroukou1")
				return false;

			b1 = cmem_ref(L"kiki");
			if (b1.to_wstring() != L"kiki")
				return false;

			return true;
		}

		bool test_binary_data::TestCoW::operator()()
		{	binary_data b1 = cmem_ref(L"koukouroukou1");
			binary_data b2(b1);
			binary_data b3;
			b3 = b2;

			if (b1.c_array() != b2.c_array())
				return false;

			if (b2.c_array() != b3.c_array())
				return false;
			return true;
		}

		bool test_binary_data::TestCoWExtend::operator()()
		{	binary_data b1 = cmem_ref(L"koukouroukou1");
			binary_data b2(b1);
			binary_data b3;
			b3 = b2;
			const void * p_old_pos;

			if (b1.c_array() != b2.c_array())
				return false;

			if (b2.c_array() != b3.c_array())
				return false;

			// Change b2
			b2 += cmem_ref("test");
			if (b2.c_array() == b3.c_array())
				return false;

			if (b3.c_array() != b1.c_array())
				return false;

			// Change b2 and check if a new allocation has been done
			p_old_pos = b2.c_array();
			b2 += cmem_ref("1");
			if (b2.c_array() != p_old_pos)
				return false;

			// Assign b3 equal to b2
			b3 = b2;
			if (b3.c_array() != b2.c_array())
				return false;

			if (b1.c_array() == b3.c_array())
				return false;

			// Change b2 and check if a new allocation has been done
			p_old_pos = b2.c_array();
			b2 += cmem_ref("1");
			if (b2.c_array() == p_old_pos)
				return false;

			return true;
		}
	}	// !test namespace
};	// !oonet namespace
