//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_STRING_H
#define MK_STRING_H

/* Basic headers */
#include <Object/mkObjectForward.h>
#include <Object/mkTypeUtils.h>

#include <string>
#include <vector>
#include <type_traits>

namespace mk
{
	template <class T, bool isobject = std::is_base_of<Object, typename BareType<T>::type>::value, bool isenum = std::is_enum<T>::value>
	struct StringConverter
	{};

	template <class T>
	inline void fromString(const string& str, T& val) { StringConverter<T>::from(str, val); }

	template <class T>
	inline T fromString(const string& str) { T val; fromString<T>(str, val); return val; }

	template <class T>
	inline void toString(const T& val, string& str) { return StringConverter<T>::to(val, str); }

	template <class T>
	inline string toString(const T& val) { string str; toString<T>(val, str); return str; }

	// string - string conversion
	template <> inline string fromString<string>(const string& str) { return str; }
	template <> inline void fromString<string>(const string& str, string& val) { val = str; }

	template <> inline string toString<string>(const string& val){ return val; }
	template <> inline void toString<string>(const string& val, string& str){ str = val; }

	typedef std::vector<string> StringVector;

	MK_OBJECT_EXPORT StringVector splitString(const string& str, const string& separator);

	MK_OBJECT_EXPORT string replaceAll(string const& original, string const& before, string const& after);
}

#endif
