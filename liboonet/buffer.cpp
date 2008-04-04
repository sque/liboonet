/**
@file Buffer.cpp
@brief Implementation of the Buffer class.
*/

#include "./buffer.hpp"
#include "./scoped_lock.hpp"

namespace oonet
{
	// Push at front
	void Buffer::pushFront(const binary_data & r)
	{	scoped_lock fun_lock(*this);

		/*// scale memory to it all data
		_scale_mem(s_data + r.size());

		// move current data at end
		memmove(p_data + r.size(), p_data, s_data);

		// and copy at the begining of new buf
		memcpy(p_data, r.get_data_ptr(), r.size());

		// Save data size
		s_data += r.size();*/
	}

	// Push at end
	void Buffer::pushBack(const binary_data & r)
	{	scoped_lock fun_lock(*this);

		binary_data::operator +=(r);

	}

	// Pop at front
	binary_data Buffer::popFront(size_t MaxSize, bool only_peek)
	{	binary_data res;
		size_t _finalSize = MaxSize;

		if (MaxSize == 0)
			return binary_data::EMPTY;

		/*scoped_lock fun_lock(*this);

		// Fix maxsize
		if (MaxSize > size())
			_finalSize = size();

		res = get_until(_finalSize);
		if (!only_peek)
			binary_data::operator=(get_from(res.size()));
*/
		return res;
	}

	// Pop from the back
	binary_data Buffer::popBack(size_t MaxSize, bool only_peek)
	{	binary_data res;
		size_t ReversePosition;
		size_t _finalSize = MaxSize;

		if (MaxSize == 0)
			return binary_data::EMPTY;

		/*scoped_lock fun_lock(*this);

		// Fix maxsize
		if (MaxSize > size())
			_finalSize = size();

		ReversePosition = size() - _finalSize;
		res = get_from(ReversePosition);
		if (!only_peek)
		{
			ReversePosition = size() - res.size();
			binary_data::operator=( get_until(ReversePosition));
		}
*/
		return res;
	}

	// Flush buffer
	void Buffer::flush()
	{	scoped_lock fun_lock(*this);

		clear();
	}
};	// !oonet namespace
