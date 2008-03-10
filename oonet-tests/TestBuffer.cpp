#include "TestBuffer.h"
#include "Buffer.h"

namespace Slib
{
	static TestBuffer theBufferTest;

	const Byte Char_M = (Byte) 'm';
	const Byte Char_A = (Byte) 'a';
	const Byte Char_NULL = (Byte) NULL;

	bool TestBuffer::TestCtor::OnExecute()
	{	Buffer myBuff;

		if (myBuff.size() != 0 )
			return false;
		return true;
	}

	bool TestBuffer::TestSize::OnExecute()
	{	Buffer myBuff;

		if (myBuff.size() != 0 )
			return false;

		myBuff.pushBack(BinaryData(Char_M, 1));

		if (myBuff.size() != 1 )
			return false;

		myBuff.pushBack(BinaryData(Char_M, 2));

		if (myBuff.size() != 3 )
			return false;

		myBuff.pushFront(BinaryData(Char_M, 1));

		if (myBuff.size() != 4 )
			return false;

		myBuff.pushBack(BinaryData(Char_M, 2));

		if (myBuff.size() != 6 )
			return false;
		return true;
	}

	bool TestBuffer::TestSizeSpeed::OnExecute()
	{	Buffer myBuff;
		size_t outSize;

		myBuff.pushBack(BinaryData(Char_M, 10000));
		myBuff.pushBack(BinaryData(Char_M, 10000));

		ResetTimer();
		for(long i = 0;i < 1000000;i++)
			outSize = myBuff.size();

		if (outSize != 20000)
			return false;
		return true;
	}

	bool TestBuffer::TestFlush::OnExecute()
	{	Buffer myBuff;

		if (myBuff.size() != 0)
			return false;

		myBuff.flush();

		if (myBuff.size() != 0)
			return false;

		myBuff.pushBack(BinaryData(Char_M, 10000));
		myBuff.pushBack(BinaryData(Char_M, 10000));

		if (myBuff.size() != 20000)
			return false;

		myBuff.flush();

		if (myBuff.size() != 0)
			return false;

		myBuff.pushBack(BinaryData(Char_M, 5000));

		if (myBuff.size() != 5000)
			return false;

		myBuff.flush();

		if (myBuff.size() != 0)
			return false;

		return true;
	}

	bool TestBuffer::TestFlushSpeed::OnExecute()
	{
		Buffer myBuff;

		if (myBuff.size() != 0)
			return false;

		myBuff.flush();

		if (myBuff.size() != 0)
			return false;

		myBuff.pushBack(BinaryData(Char_M, 10000));
		myBuff.pushBack(BinaryData(Char_M, 10000));

		ResetTimer();
		for(long i = 0;i < 100000;i++)
			myBuff.flush();

		return true;
	}

	bool TestBuffer::TestByteOrder::OnExecute()
	{	Buffer myBuff;
		BinaryData smallPattern("1234");
		BinaryData bigPattern("12341234");
		BinaryData orderedPattern("12345678");
		BinaryData revorderedPattern("8765431");

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
		myBuff.pushFront(BinaryData('1', 1));
		myBuff.pushFront(BinaryData('2', 1));
		myBuff.pushFront(BinaryData('3', 1));
		myBuff.pushFront(BinaryData('4', 1));
		myBuff.pushFront(BinaryData('5', 1));
		myBuff.pushFront(BinaryData('6', 1));
		myBuff.pushFront(BinaryData('7', 1));
		myBuff.pushFront(BinaryData('8', 1));

		if (myBuff.peekFront(4) != BinaryData("8765"))
			return false;

		if (myBuff.peekBack(4) != BinaryData("4321"))
			return false;

		myBuff.flush();

		// One by one char from back
		myBuff.pushBack(BinaryData('1', 1));
		myBuff.pushBack(BinaryData('2', 1));
		myBuff.pushBack(BinaryData('3', 1));
		myBuff.pushBack(BinaryData('4', 1));
		myBuff.pushBack(BinaryData('5', 1));
		myBuff.pushBack(BinaryData('6', 1));
		myBuff.pushBack(BinaryData('7', 1));
		myBuff.pushBack(BinaryData('8', 1));

		if (myBuff.peekFront(4) != BinaryData("1234"))
			return false;

		if (myBuff.peekBack(4) != BinaryData("5678"))
			return false;
		return true;
	}

	bool TestBuffer::TestPeekPopCompability::OnExecute()
	{	Buffer myBuff;
		BinaryData peekD, popD;

		myBuff.flush();
		myBuff.pushBack(BinaryData("1234123"));
		peekD = myBuff.peekBack(3);
		popD = myBuff.popBack(3);
		if (peekD != popD)
			return false;

		myBuff.flush();
		myBuff.pushBack(BinaryData("1234123"));
		peekD = myBuff.peekFront(3);
		popD = myBuff.popFront(3);
		if (peekD != popD)
			return false;

		return true;

	}

	bool TestBuffer::TestPushFrontSpeed::OnExecute()
	{	Buffer myBuff;
		BinaryData data = BinaryData('a', 10000);

		ResetTimer();
		for(long i = 0; i < 1000;i++)
		{
			myBuff.pushFront(data);
		}

		return true;
	}

	bool TestBuffer::TestPopFrontSpeed::OnExecute()
	{	Buffer myBuff;
		BinaryData data = BinaryData('a', 100000000);

		ResetTimer();
		for(long i = 0; i < 100000;i++)
		{
			myBuff.popFront(10000);
		}

		return true;
	}

	bool TestBuffer::TestPeekFrontSpeed::OnExecute()
	{	Buffer myBuff;
		BinaryData data = BinaryData('a', 10000000);

		ResetTimer();
		for(long i = 0; i < 100000;i++)
		{
			myBuff.peekFront(10000);
		}

		return true;
	}

	bool TestBuffer::TestPushBackSpeed::OnExecute()
	{	Buffer myBuff;
		BinaryData data = BinaryData('a', 10000);

		ResetTimer();
		for(long i = 0; i < 1000;i++)
		{
			myBuff.pushBack(data);
		}

		return true;
	}

	bool TestBuffer::TestPopBackSpeed::OnExecute()
	{	Buffer myBuff;
		BinaryData data = BinaryData('a', 100000000);

		ResetTimer();
		for(long i = 0; i < 100000;i++)
		{
			myBuff.popBack(10000);
		}

		return true;
	}

	bool TestBuffer::TestPeekBackSpeed::OnExecute()
	{	Buffer myBuff;
		BinaryData data = BinaryData('a', 10000000);

		ResetTimer();
		for(long i = 0; i < 100000;i++)
		{
			myBuff.peekBack(10000);
		}

		return true;
	}
};	//! Slib namespace
