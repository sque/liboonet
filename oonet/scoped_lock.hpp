#ifndef OONET_MT_SCOPED_LOCK_HPP_INCLUDED
#define OONET_MT_SCOPED_LOCK_HPP_INCLUDED

#include "./oonet.hpp"
#include "./mutex.hpp"

namespace oonet
{
	namespace mt
	{
		class scoped_lock
		{
		private:
			// NonCopyable
			scoped_lock(const scoped_lock&);
			scoped_lock & operator=(const scoped_lock&);

			mutex & m;
		public:
			// Constructor
			scoped_lock(mutex & _m)
				:m(_m)
			{	m.lock();	}

			// Destructor
			~scoped_lock()
			{	m.unlock();	}

		};	// !scoped_lock class
	};	// !mt namespace
};

#endif // !OONET_MT_SCOPED_LOCK_HPP_INCLUDED
