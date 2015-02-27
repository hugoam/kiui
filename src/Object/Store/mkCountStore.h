//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_COUNTSTORE_H_INCLUDED
#define MK_COUNTSTORE_H_INCLUDED

/* mk */
#include <Object/mkObjectForward.h>
#include <Object/mkTyped.h>
#include <Object/Store/mkArray.h>
#include <Object/Store/mkStoreObserver.h>
#include <Object/Store/mkStore.h>

/* Standard */
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace mk
{
	template <class T>
	class CountStore : public StoreBase<CountStore<T>, T, T*>
	{
	public:
		typedef std::unordered_map<T*, size_t> StoreContainer;

	public:
		CountStore() {}
		~CountStore() {}

		inline T* deref(typename StoreContainer::value_type& kv) const { return kv.first; }

		inline const StoreContainer& store() const { return mStore; }
		inline StoreContainer& store() { return mStore; }

		inline void add(T* object)
		{
			size_t& count = mStore[object];
			count++;
			if(count == 1)
			{
				for(auto& observer : mObservers)
					observer->handleAdd(object);
			}
		}

		inline void remove(T* object)
		{
			size_t& count = mStore[object];
			count--;
			if(count == 0)
			{
				mStore.erase(object);
				for(auto& observer : mObservers)
					observer->handleRemove(object);
			}
		}

		size_t size() const { return mStore.size(); }
		size_t count(Object* object) const { return mStore.at(object); }
		bool has(Object* object) const	{ return (mStore.find(object) != mStore.end()); }
		bool empty() const { return (mStore.size() == 0); }

		T* at(size_t pos) { return nullptr; }
		size_t index(T* object) { return 0; }

	protected:
		StoreContainer mStore;
	};
}

#endif // MK_UNIQUESTORE_H_INCLUDED
