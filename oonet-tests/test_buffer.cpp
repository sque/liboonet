#include "test_buffer.hpp"
#include <oonet/buffer.hpp>

namespace oonet
{
	static TestBuffer theBufferTest;

	const byte Char_M = (byte) 'm';
	const byte Char_A = (byte) 'a';
	const byte Char_NULL = (byte) NULL;

	bool TestBuffer::TestCtor::OnExecute()
	{	buffer myBuff;

		if (myBuff.size() != 0 )
			return false;
		return true;
	}

	bool TestBuffer::TestSize::OnExecute()
	{	buffer myBuff;

		if (myBuff.size() != 0 )
			return false;

		myBuff.pushBack(binary_data(Char_M, 1));

		if (myBuff.size() != 1 )
			return false;

		myBuff.pushBack(binary_data(Char_M, 2));

		if (myBuff.size() != 3 )
			return false;

		myBuff.pushFront(binary_data(Char_M, 1));

		if (myBuff.size() != 4 )
			return false;

		myBuff.pushBack(binary_data(Char_M, 2));

		if (myBuff.size() != 6 )
			return false;
		return true;
	}

	bool TestBuffer::TestSizeSpeed::OnExecute()
	{	buffer myBuff;
		size_t outSize;

		myBuff.pushBack(binary_data(Char_M, 10000));
		myBuff.pushBack(binary_data(Char_M, 10000));

		ResetTimer();
		for(long i = 0;i < 1000000;i++)
			outSize = myBuff.size();

		if (outSize != 20000)
			return false;
		return true;
	}

	bool TestBuffer::TestFlush::OnExecute()
	{	buffer myBuff;

		if (myBuff.size() != 0)
			return false;

		myBuff.flush();

		if (myBuff.size() != 0)
			return false;

		myBuff.pushBack(binary_data(Char_M, 10000));
		myBuff.pushBack(binary_data(Char_M, 10000));

		if (myBuff.size() != 20000)
			return false;

		myBuff.flush();

		if (myBuff.size() != 0)
			return false;

		myBuff.pushBack(binary_data(Char_M, 5000));

		if (myBuff.size() != 5000)
			return false;

		myBuff.flush();

		if (myBuff.size() != 0)
			return false;

		return true;
	}

	bool TestBuffer::TestFlushSpeed::OnExecute()
	{
		buffer myBuff;

		if (myBuff.size() != 0)
			return false;

		myBuff.flush();

		if (myBuff.size() != 0)
			return false;

		myBuff.pushBack(binary_data(Char_M, 10000));
		myBuff.pushBack(binary_data(Char_M, 10000));

		ResetTimer();
		for(long i = 0;i < 100000;i++)
			myBuff.flush();

		return true;
	}

	bool TestBuffer::TestByteOrder::OnExecute()
	{	buffer myBuff;
		binary_data smallPattern("1234");
		binary_data bigPattern("12341234");
		binary_data orderedPattern("12345678");
		binary_data revorderedPattern("8765431");

		// From back in two pieces
		myBuff.pushBack(smallPattern);
		myBuff.pushBack(smallPattern);

		if (myBuff.peekBack(40) != bigPattern)
			return false;

		if (myBuff.peekFront(40) != bigPattern)
			return false;
		myBuff.flush();

		// From back in one piece
		myBuff.pushBack(bigPattern);

		if (myBuff.peekBack(40) != bigPattern)
			return false;

		if (myBuff.peekFront(40) != bigPattern)
			return false;
		myBuff.flush();

		// Front in two pieces
		myBuff.pushFront(smallPattern);
		myBuff.pushFront(smallPattern);

		if (myBuff.peekBack(40) != bigPattern)
			return false;

		if (myBuff.peekFront(40) != bigPattern)
			return false;
		myBuff.flush();

		// Front in one piece
		myBuff.pushFront(bigPattern);

		if (myBuff.peekBack(40) != bigPattern)
			return false;

		if (myBuff.peekFront(40) != bigPattern)
			return false;
		myBuff.flush();


		// One by one char from front
		myBuff.pushFront(binary_data('1', 1));
		myBuff.pushFront(binary_data('2', 1));
		myBuff.pushFront(binary_data('3', 1));
		myBuff.pushFront(binary_data('4', 1));
		myBuff.pushFront(binary_data('5', 1));
		myBuff.pushFront(binary_data('6', 1));
		myBuff.pushFront(binary_data('7', 1));
		myBuff.pushFront(binary_data('8', 1));

		if (myBuff.peekFront(4) != binary_data("8765"))
			return false;

		if (myBuff.peekBack(4) != binary_data("4321"))
			return false;

		myBuff.flush();

		// One by one char from back
		myBuff.pushBack(binary_data('1', 1));
		myBuff.pushBack(binary_data('2', 1));
		myBuff.pushBack(binary_data('3', 1));
		myBuff.pushBack(binary_data('4', 1));
		myBuff.pushBack(binary_data('5', 1));
		myBuff.pushBack(binary_data('6', 1));
		myBuff.pushBack(binary_data('7', 1));
		myBuff.pushBack(binary_data('8', 1));

		if (myBuff.peekFront(4) != binary_data("1234"))
			return false;

		if (myBuff.peekBack(4) != binary_data("5678"))
			return false;
		return true;
	}

	bool TestBuffer::TestPeekPopCompability::OnExecute()
	{	buffer myBuff;
		binary_data peekD, popD;

		myBuff.flush();
		myBuff.pushBack(binary_data("1234123"));
		peekD = myBuff.peekBack(3);
		popD = myBuff.popBack(3);
		if (peekD != popD)
			return false;

		myBuff.flush();
		myBuff.pushBack(binary_data("1234123"));
		peekD = myBuff.peekFront(3);
		popD = myBuff.popFront(3);
		if (peekD != popD)
			return false;

		return true;

	}

	bool TestBuffer::TestPushFrontSpeed::OnExecute()
	{	buffer myBuff;
		binary_data data = binary_data('a', 10000);

		ResetTimer();
		for(long i = 0; i < 1000;i++)
		{
			myBuff.pushFront(data);
		}

		return true;
	}

	bool TestBuffer::TestPopFrontSpeed::OnExecute()
	{	buffer myBuff;
		binary_data data = binary_data('a', 100000000);

		ResetTimer();
		for(long i = 0; i < 100000;i++)
		{
			myBuff.popFront(10000);
		}

		return true;
	}

	bool TestBuffer::TestPeekFrontSpeed::OnExecute()
	{	buffer myBuff;
		binary_data data = binary_data('a', 10000000);

		ResetTimer();
		for(long i = 0; i < 100000;i++)
		{
			myBuff.peekFront(10000);
		}

		return true;
	}

	bool TestBuffer::TestPushBackSpeed::OnExecute()
	{	buffer myBuff;
		binary_data data = binary_data('a', 10000);

		ResetTimer();
		for(long i = 0; i < 1000;i++)
		{
			myBuff.pushBack(data);
		}

		return true;
	}

	bool TestBuffer::TestPopBackSpeed::OnExecute()
	{	buffer myBuff;
		binary_data data = binary_data('a', 100000000);

		ResetTimer();
		for(long i = 0; i < 100000;i++)
		{
			myBuff.popBack(10000);
		}

		return true;
	}

	bool TestBuffer::TestPeekBackSpeed::OnExecute()
	{	buffer myBuff;
		binary_data data = binary_data('a', 10000000);

		ResetTimer();
		for(long i = 0; i < 100000;i++)
		{
			myBuff.peekBack(10000);
		}

		return true;
	}
};	// !oonet namespace
