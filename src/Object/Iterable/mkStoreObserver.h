//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_STOREOBSERVER_H_INCLUDED
#define MK_STOREOBSERVER_H_INCLUDED

#include <Object/mkObjectForward.h>

namespace mk
{
	template <class T>
	class StoreObserver
	{
	public:
		virtual bool handleClear() { return false; }
		virtual void handleAdd(T& object) = 0;
		virtual void handleRemove(T& object) = 0;
	};

	class Observer
	{
	public:
		virtual ~Observer() {}
	};

	template <class T>
	class GenericObserver : public Observer, public StoreObserver<T>
	{
	public:
		GenericObserver(Store<T>& store, StoreObserver<Object>& observer) : m_observer(observer) { store.observe(*this); }

		virtual bool handleClear() { return m_observer.handleClear(); }
		virtual void handleAdd(T& object) { m_observer.handleAdd(object); }
		virtual void handleRemove(T& object) { m_observer.handleRemove(object); }

	protected:
		StoreObserver<Object>& m_observer;
	};

	template class MK_OBJECT_EXPORT StoreObserver<Object>;
}

#endif // MK_STOREOBSERVER_H_INCLUDED
