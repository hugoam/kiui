//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Object/mkObjectConfig.h>
#include <Object/Util/mkColour.h>

namespace mk
{
	Colour::Colour(float r, float g, float b, float a)
		: mR(r)
		, mG(g)
		, mB(b)
		, mA(a)
	{}

	Colour::Colour(const Colour& col)
		: mR(col.mR)
		, mG(col.mG)
		, mB(col.mB)
		, mA(col.mA)
	{}

	Colour& Colour::operator=(const Colour& rhs)
	{
		mR = rhs.mR;
		mG = rhs.mG;
		mB = rhs.mB;
		mA = rhs.mA;
		return *this;
	}
}
