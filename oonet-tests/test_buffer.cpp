#include "test_buffer.hpp"
#include <oonet/buffer.hpp>

namespace oonet
{
	namespace test
	{
		static test_buffer theBufferTest;

		const byte Char_M = (byte) 'm';
		const byte Char_A = (byte) 'a';
		const byte Char_NULL = (byte) NULL;

		bool test_buffer::TestCtor::operator()()
		{	buffer myBuff;

			if (myBuff.size() != 0 )
				return false;
			return true;
		}

		bool test_buffer::TestSize::operator()()
		{	buffer myBuff;

			if (myBuff.size() != 0 )
				return false;

			myBuff.push_back(binary_data(Char_M, 1));

			if (myBuff.size() != 1 )
				return false;

			myBuff.push_back(binary_data(Char_M, 2));

			if (myBuff.size() != 3 )
				return false;

			myBuff.push_front(binary_data(Char_M, 1));

			if (myBuff.size() != 4 )
				return false;

			myBuff.push_back(binary_data(Char_M, 2));

			if (myBuff.size() != 6 )
				return false;
			return true;
		}

		bool test_buffer::TestSizeSpeed::operator()()
		{	buffer myBuff;
			size_t outSize;

			myBuff.push_back(binary_data(Char_M, 10000));
			myBuff.push_back(binary_data(Char_M, 10000));

			reset_timer();
			for(long i = 0;i < 1000000;i++)
				outSize = myBuff.size();

			if (outSize != 20000)
				return false;
			return true;
		}

		bool test_buffer::TestFlush::operator()()
		{	buffer myBuff;

			if (myBuff.size() != 0)
				return false;

			myBuff.flush();

			if (myBuff.size() != 0)
				return false;

			myBuff.push_back(binary_data(Char_M, 10000));
			myBuff.push_back(binary_data(Char_M, 10000));

			if (myBuff.size() != 20000)
				return false;

			myBuff.flush();

			if (myBuff.size() != 0)
				return false;

			myBuff.push_back(binary_data(Char_M, 5000));

			if (myBuff.size() != 5000)
				return false;

			myBuff.flush();

			if (myBuff.size() != 0)
				return false;

			return true;
		}

		bool test_buffer::TestFlushSpeed::operator()()
		{
			buffer myBuff;

			if (myBuff.size() != 0)
				return false;

			myBuff.flush();

			if (myBuff.size() != 0)
				return false;

			myBuff.push_back(binary_data(Char_M, 10000));
			myBuff.push_back(binary_data(Char_M, 10000));

			reset_timer();
			for(long i = 0;i < 100000;i++)
				myBuff.flush();

			return true;
		}

		bool test_buffer::TestByteOrder::operator()()
		{	buffer myBuff;
			binary_data smallPattern("1234");
			binary_data bigPattern("12341234");
			binary_data orderedPattern("12345678");
			binary_data revorderedPattern("8765431");

			// From back in two pieces
			myBuff.push_back(smallPattern);
			myBuff.push_back(smallPattern);

			if (myBuff.peek_back(40) != bigPattern)
				return false;

			if (myBuff.peek_front(40) != bigPattern)
				return false;
			myBuff.flush();

			// From back in one piece
			myBuff.push_back(bigPattern);

			if (myBuff.peek_back(40) != bigPattern)
				return false;

			if (myBuff.peek_front(40) != bigPattern)
				return false;
			myBuff.flush();

			// Front in two pieces
			myBuff.push_front(smallPattern);
			myBuff.push_front(smallPattern);

			if (myBuff.peek_back(40) != bigPattern)
				return false;

			if (myBuff.peek_front(40) != bigPattern)
				return false;
			myBuff.flush();

			// Front in one piece
			myBuff.push_front(bigPattern);

			if (myBuff.peek_back(40) != bigPattern)
				return false;

			if (myBuff.peek_front(40) != bigPattern)
				return false;
			myBuff.flush();


			// One by one char from front
			myBuff.push_front(binary_data('1', 1));
			myBuff.push_front(binary_data('2', 1));
			myBuff.push_front(binary_data('3', 1));
			myBuff.push_front(binary_data('4', 1));
			myBuff.push_front(binary_data('5', 1));
			myBuff.push_front(binary_data('6', 1));
			myBuff.push_front(binary_data('7', 1));
			myBuff.push_front(binary_data('8', 1));

			if (myBuff.peek_front(4) != binary_data("8765"))
				return false;

			if (myBuff.peek_back(4) != binary_data("4321"))
				return false;

			myBuff.flush();

			// One by one char from back
			myBuff.push_back(binary_data('1', 1));
			myBuff.push_back(binary_data('2', 1));
			myBuff.push_back(binary_data('3', 1));
			myBuff.push_back(binary_data('4', 1));
			myBuff.push_back(binary_data('5', 1));
			myBuff.push_back(binary_data('6', 1));
			myBuff.push_back(binary_data('7', 1));
			myBuff.push_back(binary_data('8', 1));

			if (myBuff.peek_front(4) != binary_data("1234"))
				return false;

			if (myBuff.peek_back(4) != binary_data("5678"))
				return false;
			return true;
		}

		bool test_buffer::TestPeekPopCompability::operator()()
		{	buffer myBuff;
			binary_data peekD, popD;

			myBuff.flush();
			myBuff.push_back(binary_data("1234123"));
			peekD = myBuff.peek_back(3);
			popD = myBuff.pop_back(3);
			if (peekD != popD)
				return false;

			myBuff.flush();
			myBuff.push_back(binary_data("1234123"));
			peekD = myBuff.peek_front(3);
			popD = myBuff.pop_front(3);
			if (peekD != popD)
				return false;

			return true;

		}

		bool test_buffer::TestPushFrontSpeed::operator()()
		{	buffer myBuff;
			binary_data data = binary_data('a', 10000);

			reset_timer();
			for(long i = 0; i < 1000;i++)
			{
				myBuff.push_front(data);
			}

			return true;
		}

		bool test_buffer::TestPopFrontSpeed::operator()()
		{	buffer myBuff;
			binary_data data = binary_data('a', 100000000);

			reset_timer();
			for(long i = 0; i < 100000;i++)
			{
				myBuff.pop_front(10000);
			}

			return true;
		}

		bool test_buffer::TestPeekFrontSpeed::operator()()
		{	buffer myBuff;
			binary_data data = binary_data('a', 10000000);

			reset_timer();
			for(long i = 0; i < 100000;i++)
			{
				myBuff.peek_front(10000);
			}

			return true;
		}

		bool test_buffer::TestPushBackSpeed::operator()()
		{	buffer myBuff;
			binary_data data = binary_data('a', 10000);

			reset_timer();
			for(long i = 0; i < 1000;i++)
			{
				myBuff.push_back(data);
			}

			return true;
		}

		bool test_buffer::TestPopBackSpeed::operator()()
		{	buffer myBuff;
			binary_data data = binary_data('a', 100000000);

			reset_timer();
			for(long i = 0; i < 100000;i++)
			{
				myBuff.pop_back(10000);
			}

			return true;
		}

		bool test_buffer::TestPeekBackSpeed::operator()()
		{	buffer myBuff;
			binary_data data = binary_data('a', 10000000);

			reset_timer();
			for(long i = 0; i < 100000;i++)
			{
				myBuff.peek_back(10000);
			}

			return true;
		}
	}	// !test namespace
};	// !oonet namespace
