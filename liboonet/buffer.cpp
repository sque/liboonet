/**
@file Buffer.cpp
@brief Implementation of the Buffer class.
*/

#include "./buffer.hpp"
#include "./scoped_lock.hpp"

namespace oonet
{
	// Push at front
	void buffer::pushFront(const binary_data & r)
	{	mt::scoped_lock fun_lock(*this);

		binary_data tmp(r);

		tmp += bd_data;

		bd_data = tmp;
	}

	// Push at end
	void buffer::pushBack(const binary_data & r)
	{	mt::scoped_lock fun_lock(*this);

		bd_data += r;
	}

	// Pop at front
	binary_data buffer::popFront(size_t MaxSize, bool only_peek)
	{	binary_data res;
		size_t _finalSize = MaxSize;

		if (MaxSize == 0)
			return binary_data::nothing;

		mt::scoped_lock fun_lock(*this);

		// Fix maxsize
		if (MaxSize > bd_data.size())
			_finalSize = bd_data.size();

		res = bd_data.get_until(_finalSize);
		if (!only_peek)
			bd_data = (bd_data.get_from(res.size()));

		return res;
	}

	// Pop from the back
	binary_data buffer::popBack(size_t MaxSize, bool only_peek)
	{	binary_data res;
		size_t ReversePosition;
		size_t _finalSize = MaxSize;

		if (MaxSize == 0)
			return binary_data::nothing;

		mt::scoped_lock fun_lock(*this);

		// Fix maxsize
		if (MaxSize > bd_data.size())
			_finalSize = bd_data.size();

		ReversePosition = bd_data.size() - _finalSize;
		res = bd_data.get_from(ReversePosition);
		if (!only_peek)
		{
			ReversePosition = bd_data.size() - res.size();
			bd_data = (bd_data.get_until(ReversePosition));
		}

		return res;
	}

	// Flush buffer
	void buffer::flush()
	{	mt::scoped_lock fun_lock(*this);

		bd_data.clear();
	}
};	// !oonet namespace
