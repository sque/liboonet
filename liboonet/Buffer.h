#ifndef OONET_BUFFER_H_DEFINED
#define OONET_BUFFER_H_DEFINED

#include "./platform.h"
#include "./Mutex.h"
#include "./BinaryData.h"

namespace OONet
{
	//! A flexible multi-thread buffer object
	/**
		A buffer object that can be used as a queue or
		a stack. It is also multi-thread safe.
	*/
	class Buffer:
		private MT::Mutex, private BinaryData
	{
	public:
		//! Default constructor
		inline Buffer(){};

		//! Destructor
		inline ~Buffer(){};

		//! Push data at the end of buffer
		void pushBack(const BinaryData & r);

		//! Push data in front of buffer
		void pushFront(const BinaryData & r);

		//! Pop data from the end of buffer
		/**
		@param MaxSize The size of data to pop from the end. If MaxSize
			is bigger than the size of current data in buffer, all the
			data are popped silently.
		@param only_peek When set to true, data will not be removed from
			buffer, they will be only copied.
		*/
		BinaryData popBack(size_t MaxSize, bool only_peek = false);

		//! Pop data from the begining of buffer
		/**
		@param MaxSize The size of data to pop from the start of buffer.
			If it is bigger than the size of current stored data in buffer, then
			all the data are popped silently.
		@param only_peek When set to true, data will not be removed from
			buffer, they will be only copied.
		*/
		BinaryData popFront(size_t MaxSize, bool only_peek = false);

		//! Peek data from the end of buffer
		/**
		@deprecated Use Buffer::popBack instead
		*/
		inline BinaryData peekBack(size_t MaxSize)
		{	return popBack(MaxSize, true);	}

		//! Peek data from the begining of buffer
		/**
		@deprecated Use Buffer::peekFront instead
		*/
		inline BinaryData peekFront(size_t MaxSize)
		{	return popFront(MaxSize, true);	}

		//! Flush buffer
		void flush();

		//! Get size of data in buffer
		inline size_t size()
		{	return BinaryData::size();	}

	};	// Buffer class
};	// !OONet namespace

#endif // !OONET_BUFFER_H_DEFINED
