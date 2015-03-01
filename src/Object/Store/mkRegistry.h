//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_UNIQUESTORE_H_INCLUDED
#define MK_UNIQUESTORE_H_INCLUDED

/* mk */
#include <Object/mkObjectForward.h>
#include <Object/mkTyped.h>
#include <Object/Util/mkNonCopy.h>
#include <Object/Store/mkStoreObserver.h>
#include <Object/Store/mkStore.h>

/* Standard */
#include <vector>
#include <memory>
#include <functional>

namespace mk
{
	template <class T>
	class Registry : public StoreBase<Registry<T>, T, unique_ptr<T>>
	{
	public:
		typedef std::vector<unique_ptr<T>> StoreContainer;

	public:
		Registry() {}
		~Registry() {}

		inline T* deref(const unique_ptr<T>& pointer) const { return pointer.get(); }

		inline const StoreContainer& store() const { return mStore; }
		inline StoreContainer& store() { return mStore; }

		void add(unique_ptr<T> pt)
		{
			for(auto obs : this->mObservers)
				obs->handleAdd(pt.get());

			mStore.emplace_back(std::move(pt));
		}

		void insert(unique_ptr<T> pt, size_t index)
		{
			for(auto obs : this->mObservers)
				obs->handleAdd(pt.get());

			mStore.emplace(mStore.begin() + index, std::move(pt));
		}

		void remove(T* object)
		{
			for(auto obs : this->mObservers)
				obs->handleRemove(object);

			mStore.erase(std::remove_if(mStore.begin(), mStore.end(), [object](const unique_ptr<T>& p) { return p.get() == object; }), mStore.end());
		}

		void remove(size_t pos)
		{
			T* object = mStore[pos].get();
			for(auto obs : this->mObservers)
				obs->handleRemove(object);

			mStore.erase(mStore.begin() + pos);
		}

		unique_ptr<T> release(size_t pos)
		{
			unique_ptr<T> pointer = std::move(mStore[pos]);
			mStore.erase(mStore.begin() + pos);
			return pointer;
		}

		unique_ptr<T> release(T* object)
		{
			auto it = std::find_if(mStore.begin(), mStore.end(), [object](const unique_ptr<T>& p) { return p.get() == object; });
			return std::move(*it);
		}

		void move(size_t from, size_t to)
		{
			unique_ptr<T> ptr = std::move(mStore[from]);
			mStore.insert(mStore.begin() + to, std::move(ptr)); // emplace doesn't work, don't know why // orig is "it" here.
			mStore.erase(from < to ? mStore.begin() + from : mStore.begin() + from + 1);
		}

		void transfer(T* object, Registry<T>* other)
		{
			auto& it = std::find_if(mStore.begin(), mStore.end(), [object](const unique_ptr<T>& p) { return p.get() == object; });
			other->add(std::move((*it)));
			mStore.erase(it);
		}

		unique_ptr<T> pop()
		{
			unique_ptr<T> object(std::move(mStore.back()));
			mStore.pop_back();
			return object;
		}

		bool has(Object* object) const
		{
			return (std::find_if(mStore.begin(), mStore.end(), [object](const unique_ptr<T>& p) { return p.get() == object; }) != mStore.end());
		}

		bool empty() const { return (mStore.size() == 0); }
		
		T* at(size_t pos) { return mStore[pos].get(); }
		size_t index(T* object) { for(size_t i = 0; i < mStore.size(); ++i) if(mStore[i].get() == object) return i; return size_t(-1); }

		size_t size() const { return mStore.size(); }

	protected:
		StoreContainer mStore;

	};
}

#endif // MK_UNIQUESTORE_H_INCLUDED
