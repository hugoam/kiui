//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_ITERABLE_H_INCLUDED
#define MK_ITERABLE_H_INCLUDED

/* mk */
#include <Object/mkObjectForward.h>
#include <Object/mkTyped.h>
#include <Object/Store/mkStoreObserver.h>

/* Standard */
#include <iterator>
#include <list>
#include <memory>
#include <functional>

namespace mk
{
	template <class T>
	class Iterable
	{
	public:
		virtual size_t vsize() const = 0;
		virtual void viterate(const std::function<void(T*)>& callback) = 0;
		virtual void vclear() = 0;

		virtual T* vat(size_t pos) = 0;
		virtual size_t vindex(T* object) = 0;

		virtual Type* sequenceType() const = 0;

		virtual void vadd(T*) {}
	};

	template <>
	class Iterable<Object>
	{
	public:
		virtual size_t vsize() const = 0;
		virtual void viterateobj(const std::function<void(Object*, Type*)>& callback) = 0;
		virtual void vclear() = 0;

		virtual Object* vobjectat(size_t pos) = 0;
		virtual size_t vindex(Object* object) = 0;

		virtual Type* sequenceType() const = 0;

		virtual void vadd(Object* object) { UNUSED(object); }
	};

	template <class T>
	class Store : public Iterable<T>
	{
	public:
		virtual void addObserver(StoreObserver<T>* observer) = 0;
		virtual void removeObserver(StoreObserver<T>* observer) = 0;
	};

	class MK_OBJECT_EXPORT Stock : public Object, public Typed<Stock>, public Iterable<Object>
	{
	public:
		//virtual void vremoveobj(Object* object) = 0;
		//virtual void vaddobj(unique_ptr<Object>) = 0;
	};
}

#endif // MK_ITERABLE_INCLUDED
