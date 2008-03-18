#ifndef SCOPED_LOCK_HPP_INCLUDED
#define SCOPED_LOCK_HPP_INCLUDED

#include "OONet.h"
#include "Mutex.h"

namespace OONet
{
	class scoped_lock
	{
	private:
		// NonCopyable
		scoped_lock(const scoped_lock&);
		scoped_lock & operator=(const scoped_lock&);

		MT::Mutex & m;
	public:
		// Constructor
		scoped_lock(MT::Mutex & _m)
			:m(_m)
		{	m.lock();	}

		// Destructor
		~scoped_lock()
		{	m.unlock();	}

	};
};

#endif // SCOPED_LOCK_HPP_INCLUDED
