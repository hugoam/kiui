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
#ifndef _MSC_VER
		: mFloats{ r, g, b, a }
#endif
	{
#ifdef _MSC_VER
		mFloats[0] = r;
		mFloats[1] = g;
		mFloats[2] = b;
		mFloats[3] = a;
#endif
	}

	Colour::Colour(const Colour& col)
#ifndef _MSC_VER
		: mFloats{ col.r(), col.g(), col.b(), col.a() }
#endif
	{
#ifdef _MSC_VER
		mFloats[0] = col.r();
		mFloats[1] = col.g();
		mFloats[2] = col.b();
		mFloats[3] = col.a();
#endif
	}

	Colour& Colour::operator=(const Colour& rhs)
	{
		mFloats[0] = rhs.r();
		mFloats[1] = rhs.g();
		mFloats[2] = rhs.b();
		mFloats[3] = rhs.a();
		return *this;
	}
}
