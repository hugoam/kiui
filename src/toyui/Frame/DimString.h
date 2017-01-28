//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_DIMSTRING_H
#define TOY_DIMSTRING_H

/* Basic headers */
#include <toyui/Frame/Uibox.h>
#include <toyobj/String/StringConvert.h>

namespace toy
{
	template <> inline void fromString(const string& str, DimFloat& vec) { string_to_fixed_vector<DimFloat, float>(str, vec); }
}

#endif
