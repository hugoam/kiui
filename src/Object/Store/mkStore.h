//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_STORE_H_INCLUDED
#define MK_STORE_H_INCLUDED

/* mk */
#include <Object/mkObjectForward.h>
#include <Object/Store/mkIterable.h>

#include <algorithm>

namespace mk
{
	template <class T>
	inline Type* storetype()
	{
		return T::cls();
	}

	template <> inline Type* storetype<TypeObject>() { return Typed<TypeObject>::cls(); }
	template <> inline Type* storetype<Object>() { return Typed<Object>::cls(); }

	template <class T_Array, class T, class R>
	class StoreBase : public Store<T>, public Stock, public Typed<T_Array, void, Stock>
	{
	public:
		typedef T T;
		typedef R R;

	public:
		StoreBase()
			: mType(storetype<T>())
		{}

		void vadd(R resource) { self()->add(std::forward<R>(resource)); }
		void vremove(T* object) { self()->remove(object); }
		size_t vsize() const { return self()->size(); }
		void vclear() { self()->clear(); }
		T* vat(size_t pos) { return self()->at(pos); }
		Object* vobjectat(size_t pos) { return self()->at(pos); }
		size_t vindex(Object* object) { return self()->index(object->as<T>()); }
		size_t vindex(T* object) { return self()->index(object); }

		std::vector<T*> copy() const
		{
			std::vector<T*> vec;
			for(auto& pt : self()->store())
				vec.push_back(self()->deref(pt));
			return vec;
		}

		void update(const std::vector<R>& content)
		{
			self()->clear();

			for(auto& res : content)
				self()->add(res);
		}

		void viterate(const std::function<void(T*)>& callback)
		{
			for(auto& pt : self()->store())
				callback(self()->deref(pt));
		}

		void viterateobj(const std::function<void(Object*, Type*)>& callback)
		{
			for(auto& pt : self()->store())
				callback(self()->deref(pt), mType);
		}

		void clear()
		{
			for(auto observer : mObservers)
				if(!observer->handleClear())
					for(auto& pt : self()->store())
						observer->handleRemove(self()->deref(pt));

			self()->store().clear();
		}

		T* find(std::function<bool(T*)> predicate)
		{
			for(auto& pt : self()->store())
				if(predicate(self()->deref(pt)))
					return self()->deref(pt);
			return nullptr;
		}

		void addObserver(StoreObserver<T>* observer)
		{
			mObservers.push_back(observer);
			for(auto& pt : self()->store())
				observer->handleAdd(self()->deref(pt));
		}

		void removeObserver(StoreObserver<T>* observer)
		{
			mObservers.erase(std::remove(mObservers.begin(), mObservers.end(), observer), mObservers.end());
		}

		void removeObserverNotify(StoreObserver<T>* observer)
		{
			mObservers.erase(std::remove(mObservers.begin(), mObservers.end(), observer), mObservers.end());
			for(auto& pt : self()->store())
				observer->handleRemove(self()->deref(pt));
		}

		Type* sequenceType() const { return mType; }

		using Typed<T_Array, void, Stock>::cls;

		inline T_Array* self() { return this->as<T_Array>(); }
		inline const T_Array* self() const { return this->as<T_Array>(); }

	protected:
		Type* mType;
		std::vector<StoreObserver<T>*> mObservers;
	};
}

#endif // MK_STORE_INCLUDED
