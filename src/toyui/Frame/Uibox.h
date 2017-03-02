//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_BOX_H
#define TOY_BOX_H

/* toy */
#include <toyobj/Id.h>
#include <toyobj/String/String.h>
#include <toyobj/Typed.h>
#include <toyobj/Indexer.h>
#include <toyui/Forward.h>
#include <toyui/Style/Style.h>

/* Standards */
#include <array>

namespace toy
{
	class TOY_UI_EXPORT Uibox
	{
	public:
		Uibox();

		size_t styleStamp() { return d_styleStamp; }

		inline DimFloat position() { return d_position; }
		inline DimFloat size() { return d_size; }

		inline float dposition(Dimension dim) { return d_position[dim]; }
		inline float dsize(Dimension dim) { return d_size[dim]; }
		inline float dcontent(Dimension dim) { return d_content[dim]; }
		inline float dspan(Dimension dim) { return d_span[dim]; }

		inline float dpadding(Dimension dim) { return d_style->layout().padding()[dim]; }
		inline float dbackpadding(Dimension dim) { return d_style->layout().padding()[dim + 2]; }
		inline float dmargin(Dimension dim) { return d_style->layout().margin()[dim]; }

		inline float dbounds(Dimension dim) { return dcontent(dim) + dpadding(dim) + dbackpadding(dim) + dmargin(dim) * 2.f; }
		inline float dmeasure(Dimension dim) { return std::max(dbounds(dim), d_style->layout().size()[dim]); }
		inline float dextent(Dimension dim) { return dsize(dim) + dmargin(dim) * 2.f; }

		inline Align dalign(Dimension dim) { return d_style->layout().align()[dim]; }

		inline Sizing dsizing(Dimension dim) { return d_sizing[dim]; }
		inline bool dexpand(Dimension dim) { return d_sizing[dim] >= WRAP; }
		inline bool dmanual(Dimension dim) { return d_sizing[dim] == MANUAL; }

		inline Dimension length() { return d_length; }
		inline Dimension depth() { return d_depth; }

		inline bool flow() { return d_style->layout().d_flow == FLOW; }
		inline bool posflow() { return d_style->layout().d_flow <= ALIGN; }
		inline bool sizeflow() { return d_style->layout().d_flow <= OVERLAY; }
		inline bool clip() { return d_style->layout().d_clipping == CLIP; }
		inline bool opaque() { return d_style->layout().d_opacity == OPAQUE; }
		inline bool hollow() { return d_style->layout().d_opacity == HOLLOW; }

		inline float scale() { return d_scale; }

		inline float left() { return dposition(DIM_X); }
		inline float right() { return dposition(DIM_X) + dsize(DIM_X); }

		inline float top() { return dposition(DIM_Y); }
		inline float bottom() { return dposition(DIM_Y) + dsize(DIM_Y); }

		inline float width() { return dsize(DIM_X); }
		inline float height() { return dsize(DIM_Y); }

		inline Dimension orthogonal(Dimension dim) { return dim == DIM_X ? DIM_Y : DIM_X; }
		inline Dimension parallel(Dimension dim) { return dim; }

		inline void setLength(Dimension dim) { d_length = dim; }
		inline void setScale(float scale) { d_scale = scale; }
		inline void setContentSize(DimFloat content) { d_content = content; }

	protected:
		DimFloat d_position;
		DimFloat d_size;
		DimFloat d_content;
		DimFloat d_spaceContent;
		bool d_contentExpand;
		DimFloat d_span;
		DimSizing d_sizing;
		float d_scale;
		Dimension d_depth;
		Dimension d_length;

		Style* d_style;
		size_t d_styleStamp;
	};
}

#endif // TOY_BOX_H
