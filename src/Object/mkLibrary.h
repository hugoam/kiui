//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_LIBRARY_H_INCLUDED
#define MK_LIBRARY_H_INCLUDED

/* mk */
#include <Object/mkObjectForward.h>
#include <Object/Store/mkIterable.h>
#include <Object/mkIndexer.h>
#include <Object/Util/mkPool.h>

/* Standard */
#include <vector>
#include <memory>
#include <algorithm>

namespace mk
{
	template <class T>
	class Library : public Pool<T>
	{
	public:
		Library() : Pool() { T::cls()->setupLibrary(this); }
	};

	template <class T>
	class Librared : public Indexed<T>
	{
	public:
		static inline Library<T>* library() { return &sLibrary; }

		static Library<T> sLibrary;
	};

	template <class T>
	Library<T> Librared<T>::sLibrary = Library<T>();
}

#endif // MK_IDSTORE_H_INCLUDED
