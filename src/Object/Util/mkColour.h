//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_COLOUR_H
#define MK_COLOUR_H

/* mk headers */
#include <Object/mkTyped.h>
#include <Object/String/mkStringConvert.h>

namespace mk
{
	class MK_OBJECT_EXPORT _I_ _S_ Colour : public Struct
	{
	public:
		_C_ Colour(float r = 0.f, float g = 0.f, float b = 0.f, float a = 1.f);
		Colour(const Colour& col);

		Colour& operator=(const Colour&);

		_A_ _M_ float r() const { return m_floats[0]; }
		_A_ _M_ float g() const { return m_floats[1]; }
		_A_ _M_ float b() const { return m_floats[2]; }
		_A_ _M_ float a() const { return m_floats[3]; }

		void setR(float r) { m_floats[0] = r; }
		void setG(float g) { m_floats[1] = g; }
		void setB(float b) { m_floats[2] = b; }
		void setA(float a) { m_floats[3] = a; }

		float operator [](size_t i) const { return m_floats[i]; }
		float& operator [](size_t i) { return m_floats[i]; }

		bool null() { return a() == 0.f; }

		static Type& cls() { static Type ty; return ty; }

	protected:
		float m_floats[4];

	public:
		static Colour Black;
		static Colour Red;
		static Colour Green;
		static Colour Blue;
		static Colour Pink;
		static Colour Cyan;
		static Colour Yellow;
		static Colour White;
		static Colour LightGrey;
		static Colour MidGrey;
		static Colour DarkGrey;
		static Colour AlphaGrey;
		static Colour Transparent;
	};

	template <> inline void fromString<Colour>(const string& str, Colour& vec) { string_to_fixed_vector<Colour, float>(str, vec); }
	template <> inline void toString<Colour>(const Colour& val, string& str) { return fixed_vector_to_string<Colour, 4>(val, str); }
}

#endif // MK_COLOUR_H
