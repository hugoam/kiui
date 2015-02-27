//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_MEMPOOL_H_INCLUDED
#define MK_MEMPOOL_H_INCLUDED

/* mk headers */
#include <Object/mkObjectForward.h>
#include <Object/mkTyped.h>

#include <unordered_map>
#include <memory>

#include <boost/pool/object_pool.hpp>

namespace mk
{
	class MK_OBJECT_EXPORT _I_ AbstractPool : public Object, public Typed<AbstractPool>
	{
	public:
		virtual ~AbstractPool() {}
		virtual void reset() = 0;
		virtual void free(void* mem) = 0;
	};

	template <class T>
	class Pool : public AbstractPool, public Typed<Pool<T>>
	{
	public:
		Pool() : mPool(std::make_unique<boost::object_pool<T>>()) {}

		T* alloc()	{ return mPool->malloc(); }
		void free(T* mem) { mPool->free(mem); }
		void free(void* mem) { mPool->free((T*) mem); }
		void reset() { mPool.reset(); mPool = std::make_unique<boost::object_pool<T>>(); }

		using Typed<Pool<T>>::cls;

	protected:
		std::unique_ptr<boost::object_pool<T>> mPool;
	};
}


#endif // MK_MEMPOOL_H_INCLUDED
