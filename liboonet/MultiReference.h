#ifndef OONET_MULTIREFERENCE_H_DEFINED
#define OONET_MULTIREFERENCE_H_DEFINED

#include <map>
#include <vector>
#include <algorithm>
#include "OONet.h"
#include "Mutex.h"

namespace OONet
{

	#define MULTIREFERNCE_OBJECTFILE(_ObjectType, _HandleType) \
		template<> OONet::MultiReference<_ObjectType, _HandleType>::HandlesList_t * OONet::MultiReference<_ObjectType, _HandleType>::pHandlesList = NULL;\
        template<> OONet::MT::Mutex * OONet::MultiReference<_ObjectType, _HandleType>::pHandlesListMutex = NULL;

	template<
		class ObjectType,
		class HandleType
	>
	/**
	* A class for objects that handle the same refernce and must be destroyed when no refernce is left*/
	class MultiReference
	{
	private:
		// Type definitions
		// A list with pointer of objects
		typedef std::vector< ObjectType *>	        ObjectsList_t;
		typedef typename ObjectsList_t::iterator    ObjectsListIt_t;

		// A map with objects that use each handle
		typedef std::map< HandleType,  ObjectsList_t *>	HandlesList_t;
		typedef typename HandlesList_t::iterator		HandlesListIt_t;

		void _use_handle( HandleType &h)
		{
			HandlesListIt_t hIt;
			ObjectsListIt_t pIt;
			ObjectsList_t * pObjectsList;

			// Find pointers vector
			if ((hIt = pHandlesList->find(h)) == pHandlesList->end())
			{
				// New handle, allocate space for new pointer List
				pObjectsList = new ObjectsList_t;
				(*pHandlesList)[h] = pObjectsList;
				hIt = pHandlesList->find(h);
			}
			else
			{   // Old knonwn handle
				pObjectsList = hIt->second;
			}

			// Register Object's pointer
			pObjectsList->push_back((ObjectType*)this);
		}

		void _abandon_handle(HandleType &h)
		{
			HandlesListIt_t hIt;
			ObjectsListIt_t pIt;
			ObjectsList_t * pObjectsList;

			// Find handle map
			hIt = pHandlesList->find(h);
			OONET_ASSERT(hIt != pHandlesList->end());
			pObjectsList = hIt->second;

			// Find pointer and erase it
			pIt = find(pObjectsList->begin(), pObjectsList->end(), this);
			OONET_ASSERT(pIt != pObjectsList->end());
			pObjectsList->erase(pIt);

			// Check if it was the last object that used this handle
			if (pObjectsList->size() == 0)
			{
				// It was lost object so, erase handle, and remove it from map
				// Raise event
				OnAbandonedHandle(hIt->first);
				// Delete instance from map
				delete hIt->second;
				pHandlesList->erase(hIt);

			}
		}

		// Internal data
		HandleType mHandle;						// The local handle
		static HandlesList_t * pHandlesList;	// The global static handle list
		static MT::Mutex * pHandlesListMutex;	// Handles list lock
		bool bZombie;							// If this instance is zombie

	public:
		// Constructor with initialization of handle
		MultiReference(const HandleType & rHandle)
			:bZombie(false)
		{	// Initialize static
			if (pHandlesListMutex == NULL)
				pHandlesListMutex = new MT::Mutex();
			if (pHandlesList == NULL)
				pHandlesList = new HandlesList_t;

			pHandlesListMutex->lock();
			mHandle = rHandle;
			_use_handle(mHandle);
			pHandlesListMutex->unlock();
		}

		// Destructor
		virtual ~MultiReference()
		{
			if (!bZombie)
				OONET_THROW_EXCEPTION(Exception, "This class has not been initialize to destruct!");
		}

		// Copy constructor
		MultiReference(const MultiReference & r)
			:bZombie(false)
		{
			// We dont copy, because we have garbage
			pHandlesListMutex->lock();
			mHandle = r.mHandle;
			_use_handle(mHandle);
			pHandlesListMutex->unlock();
		}

		// Copy operator
		MultiReference & operator=(const MultiReference & r)
		{
			SafeCopy(r);
			return *this;
		}


	protected:

		// Get handle
		inline HandleType GetHandle() const
		{	return mHandle;		}

		// Safe Copy from another object
		void SafeCopy(const MultiReference & r)
		{
			pHandlesListMutex->lock();
			_abandon_handle(mHandle);	// Abandon this handle
			mHandle = r.mHandle;		// Copy the new one and declare usage
			_use_handle(mHandle);
			pHandlesListMutex->unlock();
		}

		// Set Handle
		HandleType SetHandle(const HandleType & r)
		{
			pHandlesListMutex->lock();
			_abandon_handle(mHandle);	// Abandon this handle
			mHandle = r;				// Copy the new one and declare usage
			_use_handle(mHandle);
			pHandlesListMutex->unlock();
			return mHandle;
		}

		// It should be called on destructor of child classes
		void StartDestruction()
		{
			pHandlesListMutex->lock();
			_abandon_handle(mHandle);
			pHandlesListMutex->unlock();
			bZombie = true;
		}

		// Virtual functions to be overloaded
		virtual void OnAbandonedHandle(const HandleType & pHandle) = 0;
	};	// !MultiReference class
};	// !OONet namespace
#endif // !OONET_MULTIREFERENCE_H_DEFINED
