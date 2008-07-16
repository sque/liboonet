/**
@file buffer.cpp
@brief Implementation of the buffer class.
*/

#include "./buffer.hpp"
#include "./scoped_lock.hpp"

namespace oonet
{
	// Push at front
	void buffer::push_front(const binary_data & r)
	{	mt::scoped_lock fun_lock(*this);

		bd_data.prepend(r);
	}

	// Push at end
	void buffer::push_back(const binary_data & r)
	{	mt::scoped_lock fun_lock(*this);

		bd_data.append(r);
	}

	// Pop at front
	binary_data buffer::pop_front(size_t sz_max, bool only_peek)
	{	binary_data res;
		size_t _finalSize = sz_max;

		if (sz_max == 0)
			return binary_data::nothing;

		mt::scoped_lock fun_lock(*this);

		// Fix maxsize
		if (sz_max > bd_data.size())
			_finalSize = bd_data.size();

		res = bd_data.get_until(_finalSize);
		if (!only_peek)
			bd_data = (bd_data.get_from(res.size()));

		return res;
	}

	// Pop from the back
	binary_data buffer::pop_back(size_t sz_max, bool only_peek)
	{	binary_data res;
		size_t ReversePosition;
		size_t _finalSize = sz_max;

		if (sz_max == 0)
			return binary_data::nothing;

		mt::scoped_lock fun_lock(*this);

		// Fix maxsize
		if (sz_max > bd_data.size())
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
