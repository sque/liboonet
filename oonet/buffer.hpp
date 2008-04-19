#ifndef OONET_BUFFER_HPP_INCLUDED
#define OONET_BUFFER_HPP_INCLUDED

#include "./oonet.hpp"
#include "./mutex.hpp"
#include "./binary_data.hpp"

namespace oonet
{
	//! A flexible multi-thread buffer object
	/**
		A buffer object that can be used as a queue or
		a stack. It is also multi-thread safe.
	*/
	class buffer:
		private mt::mutex
	{
	private:
		binary_data bd_data;

	public:
		//! Default constructor
		inline buffer(){};

		//! Destructor
		inline ~buffer(){};

		//! Push data at the end of buffer
		void push_back(const binary_data & r);

		//! Push data in front of buffer
		void push_front(const binary_data & r);

		//! Pop data from the end of buffer
		/**
		@param sz_max The size of data to pop from the end. If sz_max
			is bigger than the size of current data in buffer, all the
			data are popped silently.
		@param only_peek When set to true, data will not be removed from
			buffer, they will be only copied.
		*/
		binary_data pop_back(size_t sz_max, bool only_peek = false);

		//! Pop data from the begining of buffer
		/**
		@param sz_max The size of data to pop from the start of buffer.
			If it is bigger than the size of current stored data in buffer, then
			all the data are popped silently.
		@param only_peek When set to true, data will not be removed from
			buffer, they will be only copied.
		*/
		binary_data pop_front(size_t sz_max, bool only_peek = false);

		//! Peek data from the end of buffer
		/**
		@deprecated Use Buffer::pop_back instead
		*/
		inline binary_data peek_back(size_t sz_max)
		{	return pop_back(sz_max, true);	}

		//! Peek data from the begining of buffer
		/**
		@deprecated Use Buffer::pop_front instead
		*/
		inline binary_data peek_front(size_t sz_max)
		{	return pop_front(sz_max, true);	}

		//! Flush buffer
		void flush();

		//! Get size of data in buffer
		inline size_t size()
		{	return bd_data.size();	}

	};	// buffer class
};	// !oonet namespace

#endif // !OONET_BUFFER_HPP_INCLUDED
