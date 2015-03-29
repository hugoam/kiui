//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_DIM_H_INCLUDED
#define MK_DIM_H_INCLUDED

/* mk */
#include <Object/mkId.h>
#include <Object/String/mkString.h>
#include <Object/mkTyped.h>
#include <Object/mkIndexer.h>
#include <Object/Util/mkGlobalType.h>
#include <Object/Util/mkColour.h>
#include <Ui/mkUiForward.h>

/* Standards */
#include <array>
#include <map>

namespace mk
{
	enum _I_ Dimension : unsigned int
	{
		DIM_X = 0,
		DIM_Y = 1
	};

	enum _I_ Pivot : unsigned int
	{
		FORWARD = 0,
		REVERSE = 1
	};

	enum _I_ FrameType : unsigned int
	{
		FRAME = 0,
		STRIPE = 1,
		LAYER = 2,
		LAYER3D = 3
	};

	enum _I_ Flow : unsigned int
	{
		FLOW = 0,
		MANUAL = 1
	};

	enum _I_ Sizing : unsigned int
	{
		FIXED = 0,
		SHRINK = 1,
		EXPAND = 2,
		WRAP = 3,
		CAPPED = 4
	};

	enum _I_ Overflow : unsigned int
	{
		CLIP = 0,
		SCROLL = 1
	};

	enum _I_ Opacity : unsigned int
	{
		_OPAQUE = 0,
		_VOID = 1
	};

	enum _I_ Weight : unsigned int
	{
		NONE = 0,
		LIST = 1,
		TABLE = 2
	};

	template <class T>
	class _I_ Dim
	{
	public:
#ifndef _MSC_VER
		Dim(T x, T y) : d_values{{ x, y }} {}
#else
		Dim(T x, T y) : d_values(std::array<T, 2>{ x, y }) {}
#endif
		Dim() : Dim(T(), T()) {}

		T operator [](size_t i) const { return d_values[i]; }
		T& operator [](size_t i) { return d_values[i]; }

	protected:
		std::array<T, 2> d_values;
	};

	class _I_ DimFloat : public Struct, public Dim<float>, public Typed<DimFloat>
	{
	public:
		_C_ DimFloat(float x, float y) : Dim(x, y) {}
		DimFloat() : Dim() {}

		_A_ _M_ float x() { return d_values[0]; }
		_A_ _M_ float y() { return d_values[1]; }

		void setX(float x) { d_values[0] = x; }
		void setY(float y) { d_values[1] = y; }
	};

	class _I_ BoxFloat : public Struct, public Typed<BoxFloat>
	{
	public:
#ifndef _MSC_VER
		_C_ BoxFloat(float x, float y, float z, float w) : d_values{{ x, y, z, w }}, d_uniform(false), d_null(false) {}
#else
		_C_ BoxFloat(float x, float y, float z, float w) : d_values(std::array<float, 4>{ x, y, z, w }), d_uniform(false), d_null(false) {}
#endif
		BoxFloat(int x, int y, int z, int w) : BoxFloat(float(x), float(y), float(z), float(w)) {}
		BoxFloat(float uniform) : BoxFloat(uniform, uniform, uniform, uniform) {}
		BoxFloat() : BoxFloat(0.f) {}

		float operator [](size_t i) const { return d_values[i]; }
		float& operator [](size_t i) { return d_values[i]; }

		_A_ _M_ float x() { return d_values[0]; }
		_A_ _M_ float y() { return d_values[1]; }
		_A_ _M_ float z() { return d_values[2]; }
		_A_ _M_ float w() { return d_values[3]; }

		bool uniform() { return d_uniform; }
		bool null() { return d_null; }

		void setX(float x) { d_values[0] = x; }
		void setY(float y) { d_values[1] = y; }
		void setZ(float z) { d_values[2] = z; }
		void setW(float w) { d_values[3] = w; }

	protected:
		std::array<float, 4> d_values;
		bool d_uniform;
		bool d_null;
	};

	class _I_ DimSizing : public Struct, public Dim<Sizing>, public Typed<DimSizing>
	{
	public:
		_C_ DimSizing(Sizing x, Sizing y) : Dim(x, y) {}
		DimSizing() : Dim() {}

		_A_ _M_ Sizing x() { return d_values[0]; }
		_A_ _M_ Sizing y() { return d_values[1]; }

		void setX(Sizing x) { d_values[0] = x; }
		void setY(Sizing y) { d_values[0] = y; }
	};

	class _I_ DimPivot : public Struct, public Dim<Pivot>, public Typed<DimPivot>
	{
	public:
		_C_ DimPivot(Pivot x, Pivot y) : Dim(x, y) {}
		DimPivot() : Dim() {}

		_A_ _M_ Pivot x() { return d_values[0]; }
		_A_ _M_ Pivot y() { return d_values[1]; }

		void setX(Pivot x) { d_values[0] = x; }
		void setY(Pivot y) { d_values[0] = y; }
	};
}

#endif // MK_DIM_H_INCLUDED
