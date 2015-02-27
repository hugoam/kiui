//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_OBJECTFORWARD_H_INCLUDED
#define MK_OBJECTFORWARD_H_INCLUDED

#include <string>
#include <type_traits>

#ifdef MK_STD_PROXIES
namespace std
{
	template<class _Ty>
	struct allocator;

	template<class _Ty>
	struct default_delete;

	template<class _Ty, class _Dx = default_delete<_Ty>>
	class unique_ptr;

	template <class _Ty, class _Alloc = allocator<_Ty>>
	class vector;
}
#endif

#ifdef MK_TYPE_PROXIES
namespace mk
{
	template <class T, class S, class... Parts>
	class TPrototype;

	template <class T>
	class TObject;

	template <class T, class S>
	class TPart;

	template <class T>
	class TStem;
}
#endif

namespace mk
{
	typedef std::string string;
	typedef uintptr_t Id;

	class Modular;
	class Proto;

	class Type;
	class Imprint;

	class Object;
	class Stem;
	class Part;
	class Part;

	class NonCopy;

	class None;
	class Ref;
	class Lref;

	template <class T, class S, class I>
	class Typed;

	template <class T>
	class StoreObserver;

	template <class T>
	class Store;

	template <class T>
	class Array;

	template <class T>
	class Registry;

	template <class T>
	class CountStore;

	template <class T>
	class QuickStore;

	template <class T>
	class Index;

	template <class T>
	class Named;

	template <class T>
	class Pool;

	template <class T>
	class Memory;

	class AbstractPool;
	class MultiPool;

	class Stock;
	class UniqueStock;
	class ObjectStock;

	class Indexer;

	template <class T>
	class Library;

	class Image256;
}

#endif // mkOBJECTFORWARD_H_INCLUDED
