//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_STRING_H_INCLUDED
#define MK_STRING_H_INCLUDED

/* Basic headers */
#include <Object/mkObjectForward.h>

#include <string>
#include <vector>

namespace mk
{
	typedef std::vector<string> StringVector;

	MK_OBJECT_EXPORT StringVector splitString(const string& str, const string& separator);

	MK_OBJECT_EXPORT string replaceAll(string const& original, string const& before, string const& after);
}

#endif // mkSTRING_H_INCLUDED
