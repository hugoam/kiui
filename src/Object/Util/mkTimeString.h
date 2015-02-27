//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_TIMESTRING_H_INCLUDED
#define MK_TIMESTRING_H_INCLUDED

/* Basic headers */
#include <Object/Util/mkTimer.h>
#include <Object/String/mkStringConvert.h>

namespace mk
{
	template <> inline void fromString(const string& str, TimeSpan& vec) { string_to_fixed_vector<TimeSpan, float>(str, vec); }
	template <> inline string toString(const TimeSpan& val) { return fixed_vector_to_string<TimeSpan, 2>(val); }
}

#endif // MK_TIMESTRING_H_INCLUDED
