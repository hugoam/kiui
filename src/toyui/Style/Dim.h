//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_DIM_H
#define TOY_DIM_H

/* toy */
#include <toyobj/String/String.h>
#include <toyobj/Type.h>
#include <toyobj/Util/Colour.h>
#include <toyui/Forward.h>

/* std */
#include <array>

#if defined _WIN32
#undef OPAQUE
#endif

namespace toy
{
	enum _refl_ Dimension : unsigned int
	{
		DIM_X = 0,
		DIM_Y = 1,
		DIM_XX = 2,
		DIM_YY = 3,
		DIM_NULL = 4
	};

	enum _refl_ Direction : unsigned int
	{
		DIRECTION_NONE = 4,
		READING = 0,
		PARAGRAPH = 1,
		PARALLEL = 2,
		ORTHOGONAL = 3,
	};

	enum _refl_ Pivot : unsigned int
	{
		FORWARD = 0,
		REVERSE = 1
	};

	enum _refl_ Align : unsigned int
	{
		LEFT = 0,
		CENTER = 1,
		RIGHT = 2,
		OUT_LEFT = 3,
		OUT_RIGHT = 4
	};

	extern float AlignExtent[5];
	extern float AlignSpace[5];

	enum _refl_ FrameType : unsigned int
	{
		FRAME = 0,
		LAYER = 2,
		MASTER_LAYER = 3,
		SPACE_LAYER = 4
	};

	enum _refl_ LayoutSolver : unsigned int
	{
		FRAME_SOLVER = 0,
		ROW_SOLVER = 1,
		GRID_SOLVER = 2,
		TABLE_SOLVER = 3,
	};

	enum _refl_ AutoLayout : unsigned int
	{
		NO_LAYOUT = 0,
		AUTO_SIZE = 1,
		AUTO_LAYOUT = 2
	};

	enum _refl_ Flow : unsigned int
	{
		FLOW = 0,			// AUTO_LAYOUT
		OVERLAY = 1,		// AUTO_SIZE
		ALIGN = 2,			// AUTO_POSITION
		FREE = 3			// NO_LAYOUT
	};

	enum _refl_ Sizing : unsigned int
	{
		FIXED,
		SHRINK,
		WRAP,
		EXPAND
	};

	struct TOY_UI_EXPORT Space
	{
		//Space(Direction dir, Sizing len, Sizing dep) : direction(dir), sizingLength(len), sizingDepth(dep) {}
		//Space(SpacePreset preset) { *this = preset; }
		void operator=(SpacePreset preset) { *this = Space::preset(preset); }

		Direction direction;
		Sizing sizingLength;
		Sizing sizingDepth;

		static Space preset(SpacePreset preset);
	};

	enum _refl_ SpacePreset : unsigned int
	{
		SHEET,               // PARAGRAPH   direction, WRAP   length, WRAP   depth
		FLEX,			     // PARALLEL    direction, WRAP   length, WRAP   depth
		ITEM,                // READING     direction, SHRINK length, SHRINK depth
		UNIT,                // PARAGRAPH   direction, SHRINK length, SHRINK depth
		BLOCK,               // PARAGRAPH   direction, FIXED  length, FIXED  depth
		LINE,	             // READING     direction, WRAP   length, SHRINK depth
		STACK,               // PARAGRAPH   direction, SHRINK length, WRAP   depth 
		DIV,	             // ORTHOGONAL  direction, WRAP   length, SHRINK depth
		SPACER,              // PARALLEL    direction, WRAP   length, SHRINK depth
		BOARD                // PARAGRAPH   direction, EXPAND length, EXPAND depth
	};

	extern Space SpacePresets[11];

	enum _refl_ Clipping : unsigned int
	{
		NOCLIP = 0,
		CLIP = 1
	};

	enum _refl_ Opacity : unsigned int
	{
		OPAQUE = 0,
		CLEAR = 1,
		HOLLOW = 2
	};

	template <class T>
	class _refl_ Dim
	{
	public:
		Dim(T x, T y) : d_values{{ x, y }} {}
		Dim(T val) : Dim(val, val) {}
		Dim() : Dim(T(), T()) {}

		bool null() const { return d_values[0] == T() && d_values[1] == T(); }

		T operator[](size_t i) const { return d_values[i]; }
		T& operator[](size_t i) { return d_values[i]; }

		Dim operator+(const Dim& rhs) const { return Dim(this->x + rhs.x, this->y + rhs.y); }
		Dim operator-(const Dim& rhs) const { return Dim(this->x - rhs.x, this->y - rhs.y); }
		Dim operator*(const Dim& rhs) const { return Dim(this->x * rhs.x, this->y * rhs.y); }
		Dim operator/(const Dim& rhs) const { return Dim(this->x / rhs.x, this->y / rhs.y); }

	public:
		union {
			std::array<T, 2> d_values;
			struct { T x, y; };
			struct { T w, h; };
		};
	};

	// @todo add template reflection mechanism for these
	using DimIndex = Dim<size_t>;
	using DimFloat = Dim<float>;
	using DimLayout = Dim<AutoLayout>;
	using DimSizing = Dim<Sizing>;
	using DimAlign = Dim<Align>;
	using DimPivot = Dim<Pivot>;

	class _refl_ BoxFloat : public Struct
	{
	public:
		/*_constr_*/ BoxFloat(float x0, float y0, float x1, float y1) : d_values{{ x0, y0, x1, y1 }}, d_uniform(false), d_null(cnull()) {}

		BoxFloat(int x0, int y0, int x1, int y1) : BoxFloat(float(x0), float(y0), float(x1), float(y1)) {}
		BoxFloat(float uniform) : BoxFloat(uniform, uniform, uniform, uniform) {}
		BoxFloat() : BoxFloat(0.f) { d_null = true; }

		float operator[](size_t i) const { return d_values[i]; }
		float& operator[](size_t i) { d_null = false; return d_values[i]; }

		void clear() { this->assign(0.f); d_null = true; }

		bool uniform() const { return d_uniform; }
		bool null() const { return d_null; }
		bool cnull() const { return (x == 0.f && y == 0.f && w == 0.f && h == 0.f); }

		void assign(float a, float b, float c, float d) { x = a; y = b; w = c; h = d; d_null = cnull(); }
		void assign(float val) { x = val; y = val; w = val; h = val; d_null = cnull(); }

		bool intersects(const BoxFloat& other) const
		{
			return !(other.x > x + w || other.y > y + h || other.x + other.w < x || other.y + other.h < y);
		}

		float* pointer() { return &d_values[0]; }

		DimFloat offset() const { return DimFloat{ this->x0, this->y0 }; }
		DimFloat size() const { return DimFloat{ this->x0, this->y0 } + DimFloat{ this->x1, this->y1 }; }

		static Type& cls() { static Type ty; return ty; }

	public:
		union {
			std::array<float, 4> d_values;
			struct { float x0, y0, x1, y1; };
			struct { float x, y, w, h; };
		};
		bool d_uniform;
		bool d_null;
	};
}

#endif // TOY_DIM_H
