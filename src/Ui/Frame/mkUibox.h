//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_BOX_H_INCLUDED
#define MK_BOX_H_INCLUDED

/* mk */
#include <Object/mkId.h>
#include <Object/String/mkString.h>
#include <Object/mkTyped.h>
#include <Ui/mkUiForward.h>

/* Standards */
#include <array>

#include <stdio.h>

namespace mk
{
	enum _I_ Pivot : unsigned int
	{
		FORWARD = 0,
		REVERSE = 1
	};

	enum _I_ Dimension : unsigned int
	{
		DIM_X = 0,
		DIM_Y = 1
	};

	enum _I_ FrameType : unsigned int
	{
		FRAME = 0,
		STRIPE = 1,
		//GRID = 2
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
		CAPPED = 3
	};

	enum _I_ Overflow : unsigned int
	{
		CLIP = 0,
		SCROLL = 1
	};

	enum _I_ BoxLayer : unsigned int
	{
		FLAT = 0,
		LAYER = 1
	};

	enum _I_ Opacity : unsigned int
	{
		_OPAQUE = 0,
		_VOID = 1
	};

	template <class T>
	class _I_ Dim
	{
	public:
		Dim(T x, T y) : d_values({ x, y }) {}
		Dim() : d_values({ T(), T() }) {}

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
		void setY(float y) { d_values[0] = y; }
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

	class MK_UI_EXPORT _I_ LayoutStyle : public Struct, public Typed<LayoutStyle>
	{
	public:
		LayoutStyle(const string& name, Flow flow, BoxLayer layer, Opacity opacity, bool div, DimSizing sizing = DimSizing(SHRINK, SHRINK), DimFloat span = DimFloat(0.f, 0.f), Dimension layoutDim = DIM_X, Overflow overflow = CLIP)
			: d_name(name), d_flow(flow), d_layer(layer), d_opacity(opacity), d_div(div), d_layoutDim(layoutDim), d_overflow(overflow), d_span(span), d_size(0.f, 0.f), d_frontpadding(0.f, 0.f), d_backpadding(0.f, 0.f), d_margin(0.f, 0.f), d_spacing(0.f, 0.f), d_pivot(FORWARD, FORWARD), d_updated(0)
		{}

		LayoutStyle()
		{}

		LayoutStyle& operator=(const LayoutStyle&) = default;
		void copy(LayoutStyle* other) { string name = d_name; *this = *other; d_name = name; }

		const string& name() { return d_name; }

		_A_ _M_ string d_name;
		_A_ _M_ Flow d_flow;
		_A_ _M_ Overflow d_overflow;
		_A_ _M_ BoxLayer d_layer;
		_A_ _M_ Opacity d_opacity;
		_A_ _M_ bool d_div;
		_A_ _M_ Dimension d_layoutDim;
		_A_ _M_ DimSizing d_sizing;
		_A_ _M_ DimFloat d_span;
		_A_ _M_ DimFloat d_size;
		_A_ _M_ DimFloat d_frontpadding;
		_A_ _M_ DimFloat d_backpadding;
		_A_ _M_ DimFloat d_margin;
		_A_ _M_ DimFloat d_spacing;
		_A_ _M_ DimPivot d_pivot;
		_A_ _M_ std::vector<float> d_weightTable;

		_A_ _M_ size_t d_updated;
	};

	class MK_UI_EXPORT Uibox
	{
	public:
		Uibox(LayoutStyle* style);
		Uibox();
		~Uibox();

		LayoutStyle* style() { return d_style; }
		void setStyle(LayoutStyle* style);

		inline DimFloat position() { return d_position; }

		inline float dposition(Dimension dim) { return d_position[dim]; }
		inline float dsize(Dimension dim) { return d_size[dim]; }
		inline bool dexpand(Dimension dim) { return d_sizing[dim] >= EXPAND; }
		inline bool dshrink(Dimension dim) { return d_sizing[dim] == SHRINK; }
		inline bool dfixed(Dimension dim) { return d_sizing[dim] == FIXED; }
		inline float dmargin(Dimension dim) { return d_style->d_margin[dim]; }
		inline float dspan(Dimension dim) { return d_span[dim]; }

		inline float doffset(Dimension dim) { return dsize(dim) + dmargin(dim); }

		inline bool container() { return d_frameType > FRAME; }
		
		inline bool flow() { return d_style->d_flow == FLOW; }
		inline bool layer() { return d_style->d_layer == LAYER; }
		inline bool relative() { return flow() || layer(); }
		inline bool opaque() { return d_opacity == _OPAQUE; }

		inline void setOpacity(Opacity opacity) { d_opacity = opacity; }

	protected:
		DimFloat d_position;
		DimFloat d_size;
		DimFloat d_span;
		DimSizing d_sizing;
		Opacity d_opacity;
		FrameType d_frameType;
		LayoutStyle* d_style;
	};
}

#endif // MK_BOX_H_INCLUDED
