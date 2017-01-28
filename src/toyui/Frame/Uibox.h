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
		~Uibox();

		LayoutStyle& layout() { return *d_layout; }

		inline DimFloat position() { return d_position; }
		inline DimFloat size() { return d_size; }

		inline float dposition(Dimension dim) { return d_position[dim]; }
		inline float dsize(Dimension dim) { return d_size[dim]; }
		inline float dspan(Dimension dim) { return d_span[dim]; }

		inline float dpadding(Dimension dim) { return d_layout->padding()[dim]; }
		inline float dbackpadding(Dimension dim) { return d_layout->padding()[dim + 2]; }
		inline float dmargin(Dimension dim) { return d_layout->margin()[dim]; }

		inline Align dalign(Dimension dim) { return d_layout->align()[dim]; }

		inline bool dexpand(Dimension dim) { return d_sizing[dim] == EXPAND; }
		inline bool dshrink(Dimension dim) { return d_sizing[dim] == SHRINK; }
		inline bool dmanual(Dimension dim) { return d_sizing[dim] == MANUAL; }
		inline bool dfixed(Dimension dim) { return d_sizing[dim] == FIXED; }

		inline bool unflow() { return d_layout->d_flow == FREE || d_layout->d_flow == FREE_FILL; }
		inline bool floats() { return d_layout->d_flow == FLOAT_DEPTH || d_layout->d_flow == FLOAT_LENGTH; }
		inline bool clip() { return d_layout->d_clipping == CLIP; }
		inline bool opaque() { return d_opacity == OPAQUE; }
		inline bool hollow() { return d_opacity == HOLLOW; }

		inline float scale() { return d_scale; }

		inline void setOpacity(Opacity opacity) { d_opacity = opacity; }
		inline void setScale(float scale) { d_scale = scale; }

	protected:
		DimFloat d_position;
		DimFloat d_size;
		DimFloat d_span;
		Space d_space;
		DimSizing d_sizing;
		Opacity d_opacity;
		float d_scale;
		LayoutStyle* d_layout;
	};
}

#endif // TOY_BOX_H
