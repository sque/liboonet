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
		void pushBack(const binary_data & r);

		//! Push data in front of buffer
		void pushFront(const binary_data & r);

		//! Pop data from the end of buffer
		/**
		@param MaxSize The size of data to pop from the end. If MaxSize
			is bigger than the size of current data in buffer, all the
			data are popped silently.
		@param only_peek When set to true, data will not be removed from
			buffer, they will be only copied.
		*/
		binary_data popBack(size_t MaxSize, bool only_peek = false);

		//! Pop data from the begining of buffer
		/**
		@param MaxSize The size of data to pop from the start of buffer.
			If it is bigger than the size of current stored data in buffer, then
			all the data are popped silently.
		@param only_peek When set to true, data will not be removed from
			buffer, they will be only copied.
		*/
		binary_data popFront(size_t MaxSize, bool only_peek = false);

		//! Peek data from the end of buffer
		/**
		@deprecated Use Buffer::popBack instead
		*/
		inline binary_data peekBack(size_t MaxSize)
		{	return popBack(MaxSize, true);	}

		//! Peek data from the begining of buffer
		/**
		@deprecated Use Buffer::peekFront instead
		*/
		inline binary_data peekFront(size_t MaxSize)
		{	return popFront(MaxSize, true);	}

		//! Flush buffer
		void flush();

		//! Get size of data in buffer
		inline size_t size()
		{	return bd_data.size();	}

	};	// buffer class
};	// !oonet namespace

#endif // !OONET_BUFFER_HPP_INCLUDED
