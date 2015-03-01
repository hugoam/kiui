//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_ARRAY_H_INCLUDED
#define MK_ARRAY_H_INCLUDED

/* mk */
#include <Object/mkObjectForward.h>
#include <Object/Store/mkStore.h>
#include <Object/Store/mkStoreObserver.h>

/* Standard */
#include <vector>
#include <algorithm>

namespace mk
{
	template <class T>
	class Array : public StoreBase<Array<T>, T, T*>
	{
	public:
		Array()
			: mStore()
		{}

		Array(std::vector<T*> vec)
			: mStore()
		{
			for(T* obj : vec)
				mStore.push_back(obj);
		}

		~Array()
		{
			for(T* obj : mStore)
				for(StoreObserver<T>* obs : this->mObservers)
					obs->handleRemove(obj);
		}

		inline T* deref(T* const & ref) const { return ref; }

		inline const std::vector<T*>& store() const { return mStore; }
		inline std::vector<T*>& store() { return mStore; }


		void safeAdd(T* object)
		{
			if(!has(object))
				add(object);
		}

		//void push(Object* object);
		void add(T* object)
		{
			mStore.push_back(object);

			for(StoreObserver<T>* obs : this->mObservers)
				obs->handleAdd(object);
		}

		void insert(T* object, size_t index)
		{
			mStore.insert(mStore.begin() + index, object);

			for(StoreObserver<T>* obs : this->mObservers)
				obs->handleAdd(object);
		}

		void remove(size_t pos)
		{
			T* object = mStore[pos];
			mStore.erase(mStore.begin() + pos);

			for(StoreObserver<T>* obs : this->mObservers)
				obs->handleRemove(object);
		}

		void remove(T* object)
		{
			mStore.erase(std::remove(mStore.begin(), mStore.end(), object), mStore.end());

			for(StoreObserver<T>* obs : this->mObservers)
				obs->handleRemove(object);
		}

		void move(size_t from, size_t to)
		{
			T* object = mStore[from];
			mStore.erase(mStore.begin() + from);
			mStore.insert(mStore.begin() + to, object);
		}

		T* pop()
		{
			if(empty())
				return 0;

			T* object = mStore.back();
			remove(mStore.size());

			return object;
		}

		T* unqueue()
		{
			if(empty())
				return 0;

			T* object = mStore.front();
			remove(size_t(0));

			return object;
		}

		void select(T* object)
		{
			this->clear();
			add(object);
		}

		void swap(T* object)
		{
			if(!has(object))
				add(object);
			else
				remove(object);
		}

		size_t size() const { return mStore.size(); }

		bool has(T* object) const
		{
			return (std::find(mStore.begin(), mStore.end(), object) != mStore.end());
		}

		T* at(size_t pos) { return mStore[pos]; }
		size_t index(T* object) { for(size_t i = 0; i < mStore.size(); ++i) if(mStore[i] == object) return i; return size_t(-1); }

		bool empty() const { return (mStore.size() == 0); }

	protected:
		std::vector<T*> mStore;
	};

	template <class T_Array>
	class Named : public T_Array
	{
	public:
		typedef typename T_Array::T T;

	public:
		Named() : T_Array() {}

		T* findNamed(const string& name) { return T_Array::find([name](T* obj){ return obj->name() == name; }); }

		void removeNamed(const string& name) { remove(T_Array::find([name](T* obj){ return obj->name() == name; })); }
	};

	template <class T_Array>
	class TypeIndexed : public T_Array
	{
	public:
		typedef typename T_Array::T T;

	public:
		TypeIndexed() : T_Array() {}

		T* findTyped(Type* type) { return T_Array::find([type](T* obj){ return obj->type() == type; }); }

		void removeTyped(Type* type) { remove(T_Array::find([type](T* obj){ return obj->type() == type; })); }
	};

	template <class T_Array>
	class Chained : public T_Array, public StoreObserver<typename T_Array::T>
	{
	public:
		typedef typename T_Array::T T;

	public:
		Chained() : T_Array() {}

		void handleAdd(T* object) { add(object); }
		void handleRemove(T* object) { remove(object); }
	};
}

#endif // MK_ARRAY_H_INCLUDED
