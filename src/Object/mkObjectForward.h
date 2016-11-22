//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_OBJECTFORWARD_H_INCLUDED
#define MK_OBJECTFORWARD_H_INCLUDED

#include <string>
#include <type_traits>

#define UNUSED(x) (void)(x)

#ifdef MK_STD_PROXIES
namespace std
{
	class string;

	template<class _Ty>
	class unique_ptr;

	template <class _Ty>
	class vector;
}
#endif

namespace mk
{
	typedef std::string string;
	//using std::string;

	typedef unsigned int Id;

	class Modular;
	class Proto;

	class Type;
	class Imprint;

	class Object;
	class TypeObject;
	class IdObject;
	class Stem;
	class Part;

	class NonCopy;

	class None;
	class Ref;
	class Lref;

	template <class T, class I>
	class Typed;

	template <class T>
	class GlobalType;

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

	template <class T>
	class Stat;

	class AbstractPool;
	class MultiPool;

	class Indexer;

	template <class T>
	class Library;

	class Injector;
	class Maker;

	class Creator;
	class DataSource;
	class DataLoader;
	class LoaderMember;
	class Loader;

	class User;

	class Procedure;
	class ProcedureType;

	class Member;
	class Method;
	class Imprint;

	class Echobject;
	class Echomember;
	class Echomethod;

	class Image256;

	class Module;
}

#endif // mkOBJECTFORWARD_H_INCLUDED
