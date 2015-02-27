//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_STATSTRING_H_INCLUDED
#define MK_STATSTRING_H_INCLUDED

/* mk */
#include <Object/Util/mkStat.h>
#include <Object/String/mkStringConvert.h>

namespace mk
{
	template <> inline void fromString<Stat<float>>(const string& str, Stat<float>& val) { val.setValue(fromString<float>(str)); }
	template <> inline string toString<Stat<float>>(const Stat<float>& val){ return toString<float>(val.value()); }

	template <> inline void fromString<Stat<int>>(const string& str, Stat<int>& val) { val.setValue(fromString<int>(str)); }
	template <> inline string toString<Stat<int>>(const Stat<int>& val){ return toString<int>(val.value()); }
}

#endif // MK_STAT_H_INCLUDED
