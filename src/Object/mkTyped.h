//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_TYPED_H_INCLUDED
#define MK_TYPED_H_INCLUDED

/* mk */
#include <Object/mkObjectForward.h>
#include <Object/mkType.h>
#include <Object/mkObject.h>

namespace mk
{
	template <class T>
	inline Type& typecls()
	{
		return T::cls();
	}

	template <> inline Type& typecls<void>() { static Type ty; return ty; }

	template <> MK_OBJECT_EXPORT inline Type& typecls<bool>() { static Type ty; return ty; }
	template <> MK_OBJECT_EXPORT inline Type& typecls<int>() { static Type ty; return ty; }
	template <> MK_OBJECT_EXPORT inline Type& typecls<unsigned int>() { static Type ty; return ty; }
	template <> MK_OBJECT_EXPORT inline Type& typecls<float>() { static Type ty; return ty; }
	template <> MK_OBJECT_EXPORT inline Type& typecls<double>() { static Type ty; return ty; }
	template <> MK_OBJECT_EXPORT inline Type& typecls<string>() { static Type ty; return ty; }
	
	template <> MK_OBJECT_EXPORT inline Type& typecls<std::vector<float>>() { static Type ty; return ty; }
	template <> MK_OBJECT_EXPORT inline Type& typecls<std::vector<string>>() { static Type ty; return ty; }

	template <> MK_OBJECT_EXPORT inline Type& typecls<std::vector<Type*>>() { static Type ty; return ty; }
	template <> MK_OBJECT_EXPORT inline Type& typecls<std::vector<Object*>>() { static Type ty; return ty; }
}

#endif // MK_TYPED_INCLUDED
