//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_COLOUR_H_INCLUDED
#define MK_COLOUR_H_INCLUDED

/* mk headers */
#include <Object/mkTyped.h>

namespace mk
{
	class MK_OBJECT_EXPORT _I_ _S_ Colour : public Struct, public Typed<Colour>
	{
	public:
		_C_ Colour(float r = 0.f, float g = 0.f, float b = 0.f, float a = 1.f);
		Colour(const Colour& col);

		Colour& operator=(const Colour&);

		_A_ _M_ float r() const { return mR; }
		_A_ _M_ float g() const { return mG; }
		_A_ _M_ float b() const { return mB; }
		_A_ _M_ float a() const { return mA; }

		void setR(float r) { mR = r; }
		void setG(float g) { mG = g; }
		void setB(float b) { mB = b; }
		void setA(float a) { mA = a; }

	protected:
		float mR;
		float mG;
		float mB;
		float mA;
	};
}

#endif // MK_COLOUR_H_INCLUDED
