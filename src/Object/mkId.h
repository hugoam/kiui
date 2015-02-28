//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_ID_H_INCLUDED
#define MK_ID_H_INCLUDED

/** Basic headers **/
#include <vector>
#include <list>
#include <stdint.h>

namespace mk
{
	typedef unsigned int Id;

	typedef std::vector<Id> IdVector;
	typedef std::list<Id> IdList;
}

#endif // mkID_H_INCLUDED
