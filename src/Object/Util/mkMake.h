//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_MKUNIQUE_H_INCLUDED
#define MK_MKUNIQUE_H_INCLUDED

#include <memory>
#include <type_traits>

namespace mk
{
	using std::unique_ptr;

#ifdef STD_NO_MAKE_UNIQUE
	template<class T, class... Types>
	inline typename std::enable_if<!std::is_array<T>::value, unique_ptr<T>>::type make_unique(Types&&... Args)
	{
		return (unique_ptr<T>(new T(std::forward<Types>(Args)...)));
	}
#else
	using std::make_unique;
#endif
}

#endif // MK_MKUNIQUE_H_INCLUDED
