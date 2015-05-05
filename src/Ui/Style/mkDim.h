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

#if defined _WIN32
#undef OPAQUE
#undef VOID
#endif

namespace mk
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
		LAYER = 2,
		LAYER3D = 3
	};

	enum _I_ Flow : unsigned int
	{
		FLOW = 0,
		FREE = 1,
		FREE_FILL = 2,
		ALIGN = 3,
		OVERLAY = 4,
		FLOAT_DEPTH = 5,
		FLOAT_LENGTH = 6
	};

	enum _I_ Space : unsigned int
	{
		AUTO = 0,
		BLOCK = 1,
		FIT = 2,
		DIV = 3,
		SPACE = 4,
		BOARD = 5
	};

	enum _I_ Sizing : unsigned int
	{
		FIXED = 0,
		SHRINK = 1,
		WRAP = 2,
		EXPAND = 3,
		MANUAL = 4
	};

	enum _I_ Clipping : unsigned int
	{
		NOCLIP = 0,
		CLIP = 1
	};

	enum _I_ Opacity : unsigned int
	{
		OPAQUE = 0,
		GLASSY = 1,
		VOID = 2
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

		bool null() const { return d_values[0] == T() && d_values[1] == T(); }

		T operator [](size_t i) const { return d_values[i]; }
		T& operator [](size_t i) { return d_values[i]; }

	protected:
		std::array<T, 2> d_values;
	};

	class _I_ DimFloat : public Struct, public Dim<float>
	{
	public:
		_C_ DimFloat(float x, float y) : Dim(x, y) {}
		DimFloat() : Dim() {}

		_A_ _M_ float x() const { return d_values[0]; }
		_A_ _M_ float y() const { return d_values[1]; }

		void setX(float x) { d_values[0] = x; }
		void setY(float y) { d_values[1] = y; }

		static Type& cls() { static Type ty; return ty; }
	};

	class _I_ BoxFloat : public Struct
	{
	public:
#ifndef _MSC_VER
		_C_ BoxFloat(float x0, float y0, float x1, float y1) : d_values{{ x0, y0, x1, y1 }}, d_uniform(false), d_null(cnull()) {}
#else
		_C_ BoxFloat(float x0, float y0, float x1, float y1) : d_values(std::array<float, 4>{ x0, y0, x1, y1 }), d_uniform(false), d_null(cnull()) {}
#endif
		BoxFloat(int x0, int y0, int x1, int y1) : BoxFloat(float(x0), float(y0), float(x1), float(y1)) {}
		BoxFloat(float uniform) : BoxFloat(uniform, uniform, uniform, uniform) {}
		BoxFloat() : BoxFloat(0.f) { d_null = true; }

		float operator [](size_t i) const { return d_values[i]; }
		float& operator [](size_t i) { d_null = false; return d_values[i]; }

		_A_ _M_ float x0() const { return d_values[0]; }
		_A_ _M_ float y0() const { return d_values[1]; }
		_A_ _M_ float x1() const { return d_values[2]; }
		_A_ _M_ float y1() const { return d_values[3]; }

		bool uniform() const { return d_uniform; }
		bool null() const { return d_null; }
		bool cnull() const { return (d_values[0] == 0.f && d_values[1] == 0.f && d_values[2] == 0.f && d_values[3] == 0.f); }

		void assign(float x0, float y0, float x1, float y1) { d_values[0] = x0; d_values[1] = y0; d_values[2] = x1; d_values[3] = y1; }
		void assign(float val) { d_values[0] = val; d_values[1] = val; d_values[2] = val; d_values[3] = val; }

		void setX0(float x0) { d_values[0] = x0; d_null = cnull(); }
		void setY0(float y0) { d_values[1] = y0; d_null = cnull(); }
		void setX1(float x1) { d_values[2] = x1; d_null = cnull(); }
		void setY1(float y1) { d_values[3] = y1; d_null = cnull(); }

		static Type& cls() { static Type ty; return ty; }

	protected:
		std::array<float, 4> d_values;
		bool d_uniform;
		bool d_null;
	};

	class _I_ DimSizing : public Struct, public Dim<Sizing>
	{
	public:
		_C_ DimSizing(Sizing x, Sizing y) : Dim(x, y) {}
		DimSizing() : Dim() {}

		_A_ _M_ Sizing x() { return d_values[0]; }
		_A_ _M_ Sizing y() { return d_values[1]; }

		void setX(Sizing x) { d_values[0] = x; }
		void setY(Sizing y) { d_values[0] = y; }

		static Type& cls() { static Type ty; return ty; }
	};

	class _I_ DimAlign : public Struct, public Dim<Align>
	{
	public:
		_C_ DimAlign(Align x, Align y) : Dim(x, y) {}
		DimAlign() : Dim() {}

		_A_ _M_ Align x() { return d_values[0]; }
		_A_ _M_ Align y() { return d_values[1]; }

		void setX(Align x) { d_values[0] = x; }
		void setY(Align y) { d_values[0] = y; }

		static Type& cls() { static Type ty; return ty; }
	};

	class _I_ DimPivot : public Struct, public Dim<Pivot>
	{
	public:
		_C_ DimPivot(Pivot x, Pivot y) : Dim(x, y) {}
		DimPivot() : Dim() {}

		_A_ _M_ Pivot x() { return d_values[0]; }
		_A_ _M_ Pivot y() { return d_values[1]; }

		void setX(Pivot x) { d_values[0] = x; }
		void setY(Pivot y) { d_values[0] = y; }

		static Type& cls() { static Type ty; return ty; }
	};
}

#endif // MK_DIM_H_INCLUDED
