//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_ITERABLE_H_INCLUDED
#define MK_ITERABLE_H_INCLUDED

/* mk headers */
#include <Object/mkObjectForward.h>
#include <Object/Iterable/mkStoreObserver.h>

/* Basic headers */
#include <functional>

namespace mk
{
	template <class T>
	class Iterable
	{
	public:
		virtual size_t size() const = 0;
		virtual Type& elementType() const = 0;
		virtual void iterate(const std::function<void(T&)>& callback) const = 0;
		virtual bool has(T& object) const = 0;
	};

	template <class T>
	class Sequence : public Iterable<T>
	{
	public:
		virtual void add(T& object) = 0;
		virtual void remove(T& object) = 0;
		virtual void clear() = 0;

		void select(T& object) { clear(); add(object); }
		void swap(T& object) { has(object) ? remove(object) : add(object); }

		//virtual T& at(size_t pos) = 0;
		//virtual size_t index(T& object) = 0;
	};

	template <class T>
	class Store : public Sequence<T>
	{
	public:
		virtual void observe(StoreObserver<T>& observer) = 0;
		virtual void unobserve(StoreObserver<T>& observer) = 0;
		virtual void unobserveNotify(StoreObserver<T>& observer) = 0;
	};
}

#endif // MK_ITERABLE_INCLUDED
