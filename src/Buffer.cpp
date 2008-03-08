/**
@file Buffer.cpp
@brief Implementation of the Buffer class.
*/

#include "./Buffer.h"

namespace Slib
{
	// Push at front
	void Buffer::pushFront(const BinaryData & r)
	{	lock();

		// scale memory to it all data
		_scale_mem(sData + r.size());

		// move current data at end
		memmove(pData + r.size(), pData, sData);

		// and copy at the begining of new buf
		memcpy(pData, r.getDataPtr(), r.size());

		// Save data size
		sData += r.size();
		unlock();
	}

	// Push at end
	void Buffer::pushBack(const BinaryData & r)
	{	lock();
		BinaryData::operator +=(r);
		unlock();
	}

	// Pop at front
	BinaryData Buffer::popFront(size_t MaxSize, bool only_peek)
	{	BinaryData res;
		size_t _finalSize = MaxSize;

		if (MaxSize == 0)
			return BinaryData::EMPTY;

		lock();

		// Fix maxsize
		if (MaxSize > size())
			_finalSize = size();

		res = getUntil(_finalSize);
		if (!only_peek)
			BinaryData::operator=(getFrom(res.size()));

		unlock();
		return res;
	}

	// Pop from the back
	BinaryData Buffer::popBack(size_t MaxSize, bool only_peek)
	{	BinaryData res;
		size_t ReversePosition;
		size_t _finalSize = MaxSize;

		if (MaxSize == 0)
			return BinaryData::EMPTY;

		lock();

		// Fix maxsize
		if (MaxSize > size())
			_finalSize = size();

		ReversePosition = size() - _finalSize;
		res = getFrom(ReversePosition);
		if (!only_peek)
		{
			ReversePosition = size() - res.size();
			BinaryData::operator=( getUntil(ReversePosition));
		}

		unlock();
		return res;
	}

	// Flush buffer
	void Buffer::flush()
	{
		lock();
			clear();
		unlock();
	}
};	//! Slib namespace
