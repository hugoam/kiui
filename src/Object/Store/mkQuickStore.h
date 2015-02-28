//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_QUICKSTORE_H_INCLUDED
#define MK_QUICKSTORE_H_INCLUDED

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
	class QuickStore : public StoreBase<QuickStore<T>, T, T*> // TObject<QuickStore>
	{
	public:
		typedef std::unordered_set<T*> StoreContainer;

	public:
		QuickStore() {}
		~QuickStore() {}

		inline T* deref(T* const & ref) const { return ref; }

		const StoreContainer& store() const { return mStore; }
		StoreContainer& store() { return mStore; }

		void add(T* object)
		{
			mStore.insert(object);
			//mStore.push_back(object);
			for(auto& observer : mObservers)
				observer->handleAdd(object);
		}

		void remove(T* object)
		{
			mStore.erase(object);
			//mStore.erase(std::remove(mStore.begin(), mStore.end(), object), mStore.end());
			for(auto& observer : mObservers)
				observer->handleRemove(object);
		}

		size_t count(T* object) const { UNUSED(object); return 0; }
		bool has(T* object) const { return (std::find(mStore.begin(), mStore.end(), object) != mStore.end()); }
		bool empty() const { return (mStore.size() == 0); }
		size_t size() const { return mStore.size(); }

		T* at(size_t pos) { UNUSED(pos); return nullptr; }
		size_t index(T* object) { UNUSED(object); return 0; }

		T* pop()
		{
			T* obj = *mStore.end();
			mStore.erase(mStore.end());
			return obj;
		}

	protected:
		StoreContainer mStore;
	};
}

#endif // MK_UNIQUESTORE_H_INCLUDED
