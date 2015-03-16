//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Object/mkObjectConfig.h>
#include <Object/Util/mkColour.h>

namespace mk
{
	Colour Colour::Black(0.f, 0.f, 0.f);
	Colour Colour::Red(1.f, 0.f, 0.f);
	Colour Colour::Green(0.f, 1.f, 0.f);
	Colour Colour::Blue(0.f, 0.f, 1.f);
	Colour Colour::Pink(1.f, 0.f, 1.f);
	Colour Colour::Cyan(0.f, 1.f, 1.f);
	Colour Colour::Yellow(1.f, 1.f, 0.f);
	Colour Colour::White(1.f, 1.f, 1.f);
	Colour Colour::LightGrey(0.6f, 0.6f, 0.6f);
	Colour Colour::MidGrey(0.45f, 0.45f, 0.45f);
	Colour Colour::DarkGrey(0.3f, 0.3f, 0.3f);
	Colour Colour::AlphaGrey(0.45f, 0.45f, 0.45f, 0.5f);
	Colour Colour::Transparent(0.f, 0.f, 0.f, 0.f);

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
