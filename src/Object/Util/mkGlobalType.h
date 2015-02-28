//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_GLOBALTYPE_H_INCLUDED
#define MK_GLOBALTYPE_H_INCLUDED

#include <Object/Util/mkMake.h>

#include <memory>
#include <vector>

namespace mk
{
	template <class T>
	class Global
	{
	public:
		static T* me() { return &sInstance; }
		static T sInstance;
	};

	template <class T>
	T Global<T>::sInstance;

	class MK_OBJECT_EXPORT LazyGlobal
	{
	public:
		virtual void init() = 0;

		static void initGlobals() { for(LazyGlobal* lazy : sGlobals) lazy->init(); }
		static std::vector<LazyGlobal*> sGlobals;
	};

	template <class T>
	class LazyGlobalInit : public LazyGlobal
	{
	public:
		LazyGlobalInit() { LazyGlobal::sGlobals.push_back(this); }

		void init() { GlobalType<T>::sInstance = make_unique<T>(); }
	};

	template <class T>
	class GlobalType
	{
	public:
		static T* me() { return sInstance.get(); }
		static unique_ptr<T> sInstance;
		static LazyGlobalInit<T> sInit;
	};

	template <class T>
	unique_ptr<T> GlobalType<T>::sInstance;

	template <class T>
	LazyGlobalInit<T> GlobalType<T>::sInit;
}

#endif // mkGLOBALTYPE_H_INCLUDED
