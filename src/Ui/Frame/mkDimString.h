//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_DIMSTRING_H
#define MK_DIMSTRING_H

/* Basic headers */
#include <Ui/Frame/mkUibox.h>
#include <Object/String/mkStringConvert.h>

namespace mk
{
	template <> inline void fromString(const string& str, DimFloat& vec) { string_to_fixed_vector<DimFloat, float>(str, vec); }
}

#endif
