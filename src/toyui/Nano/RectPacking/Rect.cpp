//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.
/** @file BPRect.cpp
	@author Jukka Jyl�nki

	This work is released to Public Domain, do whatever you want with it.
*/
#include <utility>

#include "Rect.h"

bool IsContainedIn(const BPRect &a, const BPRect &b)
{
	return a.x >= b.x && a.y >= b.y 
		&& a.x+a.width <= b.x+b.width 
		&& a.y+a.height <= b.y+b.height;
}
