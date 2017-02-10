//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_DIM_H
#define TOY_DIM_H

/* toy */
#include <toyobj/Id.h>
#include <toyobj/String/String.h>
#include <toyobj/Typed.h>
#include <toyobj/Indexer.h>
#include <toyobj/Util/GlobalType.h>
#include <toyobj/Util/Colour.h>
#include <toyui/Forward.h>

/* std */
#include <array>
#include <map>

#if defined _WIN32
#undef OPAQUE
#endif

namespace toy
{
	enum _I_ Dimension : unsigned int
	{
		DIM_X = 0,
		DIM_Y = 1,
		DIM_XX = 2,
		DIM_YY = 3,
		DIM_NULL = 4
	};

	enum _I_ Pivot : unsigned int
	{
		FORWARD = 0,
		REVERSE = 1
	};

	enum _I_ Align : unsigned int
	{
		LEFT = 0,
		CENTER = 1,
		RIGHT = 2,
		OUT_LEFT = 3,
		OUT_RIGHT = 4
	};

	extern float AlignExtent[5];
	extern float AlignSpace[5];

	enum _I_ FrameType : unsigned int
	{
		FRAME = 0,
		STRIPE = 1,
		GRID = 2,
		TABLE = 3,
		LAYER = 4,
		MASTER_LAYER = 5,
		SPACE_LAYER = 6
	};

	enum _I_ Layout : unsigned int
	{
		NOLAYOUT = 0,
		AUTOSIZE = 1,
		AUTOLAYOUT = 2,
	};

	enum _I_ Flow : unsigned int
	{
		FLOW = 0,
		FREE = 1,
		FREE_FILL = 2,
		ALIGN = 3,
		OVERLAY = 4
	};

	enum _I_ Space : unsigned int
	{
		AUTO = 0,
		FLEX = 1,
		BLOCK = 2,
		DIV = 3,
		SPACE = 4,
		BOARD = 5
	};

	enum _I_ Sizing : unsigned int
	{
		FIXED = 0,
		MANUAL = 1,
		SHRINK = 2,
		WRAP = 3,
		EXPAND = 4
	};

	enum _I_ Clipping : unsigned int
	{
		NOCLIP = 0,
		CLIP = 1
	};

	enum _I_ Opacity : unsigned int
	{
		OPAQUE = 0,
		CLEAR = 1,
		HOLLOW = 2
	};

	template <class T>
	class _I_ Dim
	{
	public:
		Dim(T x, T y) : d_values{{ x, y }} {}
		Dim(T val) : Dim(val, val) {}
		Dim() : Dim(T(), T()) {}

		T x() const { return d_values[0]; }
		T y() const { return d_values[1]; }

		void setX(T x) { d_values[0] = x; }
		void setY(T y) { d_values[1] = y; }

		bool null() const { return d_values[0] == T() && d_values[1] == T(); }

		T operator [](size_t i) const { return d_values[i]; }
		T& operator [](size_t i) { return d_values[i]; }

	protected:
		std::array<T, 2> d_values;
	};

	class _I_ BoxFloat : public Struct
	{
	public:
		_C_ BoxFloat(float x0, float y0, float x1, float y1) : d_values{{ x0, y0, x1, y1 }}, d_uniform(false), d_null(cnull()) {}

		BoxFloat(int x0, int y0, int x1, int y1) : BoxFloat(float(x0), float(y0), float(x1), float(y1)) {}
		BoxFloat(float uniform) : BoxFloat(uniform, uniform, uniform, uniform) {}
		BoxFloat() : BoxFloat(0.f) { d_null = true; }

		BoxFloat& operator=(const BoxFloat& other) { this->assign(other.v0(), other.v1(), other.v2(), other.v3()); return *this; }

		float operator [](size_t i) const { return d_values[i]; }
		float& operator [](size_t i) { d_null = false; return d_values[i]; }

		_A_ _M_ float x0() const { return d_values[0]; }
		_A_ _M_ float y0() const { return d_values[1]; }
		_A_ _M_ float x1() const { return d_values[2]; }
		_A_ _M_ float y1() const { return d_values[3]; }

		_A_ float x() const { return d_values[0]; }
		_A_ float y() const { return d_values[1]; }
		_A_ float w() const { return d_values[2]; }
		_A_ float h() const { return d_values[3]; }

		_A_ float xx() const { return d_values[0]; }
		_A_ float xy() const { return d_values[1]; }
		_A_ float yx() const { return d_values[2]; }
		_A_ float yy() const { return d_values[3]; }

		_A_ float v0() const { return d_values[0]; }
		_A_ float v1() const { return d_values[1]; }
		_A_ float v2() const { return d_values[2]; }
		_A_ float v3() const { return d_values[3]; }

		void clear() { this->assign(0.f); d_null = true; }

		bool uniform() const { return d_uniform; }
		bool null() const { return d_null; }
		bool cnull() const { return (d_values[0] == 0.f && d_values[1] == 0.f && d_values[2] == 0.f && d_values[3] == 0.f); }

		void assign(float x0, float y0, float x1, float y1) { d_values[0] = x0; d_values[1] = y0; d_values[2] = x1; d_values[3] = y1; d_null = cnull(); }
		void assign(float val) { d_values[0] = val; d_values[1] = val; d_values[2] = val; d_values[3] = val; d_null = cnull(); }

		void setX0(float x0) { d_values[0] = x0; d_null = cnull(); }
		void setY0(float y0) { d_values[1] = y0; d_null = cnull(); }
		void setX1(float x1) { d_values[2] = x1; d_null = cnull(); }
		void setY1(float y1) { d_values[3] = y1; d_null = cnull(); }

		bool intersects(const BoxFloat& other) const
		{
			return !(other.x() > x() + w() || other.y() > y() + h() || other.x() + other.w() < x() || other.y() + other.h() < y());
		}

		float* pointer() { return &d_values[0]; }

		static Type& cls() { static Type ty; return ty; }

	protected:
		std::array<float, 4> d_values;
		bool d_uniform;
		bool d_null;
	};

	// @todo add template reflection mechanism for these
	typedef Dim<size_t> Index;
	typedef Dim<float> DimFloat;
	typedef Dim<Layout> DimLayout;
	typedef Dim<Sizing> DimSizing;
	typedef Dim<Align> DimAlign;
	typedef Dim<Pivot> DimPivot;
}

#endif // TOY_DIM_H
