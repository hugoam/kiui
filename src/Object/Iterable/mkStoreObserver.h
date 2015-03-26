//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_STOREOBSERVER_H_INCLUDED
#define MK_STOREOBSERVER_H_INCLUDED

/* mk */
#include <Object/Iterable/mkStoreObserver.h>
#include <Object/mkObject.h>

#include <memory>

namespace mk
{
	template <class T>
	class StoreObserver
	{
	public:
		virtual bool handleClear() { return false; }
		virtual void handleAdd(T* object) = 0;
		virtual void handleRemove(T* object) = 0;
	};

	template <>
	class StoreObserver<Object>
	{
	public:
		virtual bool handleClear() { return false; }
		virtual void handleAdd(Object* object, Type* type) = 0;
		virtual void handleRemove(Object* object, Type* type) = 0;
	};

	template <class T>
	class GenericObserver : public StoreObserver<T>
	{
	public:
		GenericObserver(Store<T>* store, StoreObserver<Object>* observer) : mObserver(observer) { store->addObserver(this); }

		virtual bool handleClear() { return mObserver->handleClear(); }
		virtual void handleAdd(T* object) { mObserver->handleAdd(object, T::cls()); }
		virtual void handleRemove(T* object) { mObserver->handleRemove(object, T::cls()); }

	protected:
		StoreObserver<Object>* mObserver;
	};

	template class MK_OBJECT_EXPORT StoreObserver<Object>;
}

#endif // MK_STOREOBSERVER_H_INCLUDED
