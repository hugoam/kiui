//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_GLOBALTYPE_H
#define MK_GLOBALTYPE_H

#include <Object/mkObjectForward.h>
#include <Object/Util/mkUnique.h>

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

	template <class T>
	class GlobalType
	{
	public:
		static T& me() { static T instance; return instance; }
	};
}

#endif
