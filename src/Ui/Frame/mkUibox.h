//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_BOX_H_INCLUDED
#define MK_BOX_H_INCLUDED

/* mk */
#include <Object/mkId.h>
#include <Object/String/mkString.h>
#include <Object/mkTyped.h>
#include <Object/mkIndexer.h>
#include <Ui/mkUiForward.h>
#include <Ui/Style/mkStyle.h>

/* Standards */
#include <array>

namespace mk
{
	class MK_UI_EXPORT Uibox
	{
	public:
		Uibox();
		~Uibox();

		LayoutStyle* layout() { return d_layout; }

		inline DimFloat position() { return d_position; }

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
		inline bool opaque() { return d_opacity <= GLASSY; }

		inline void setOpacity(Opacity opacity) { d_opacity = opacity; }

	protected:
		DimFloat d_position;
		DimFloat d_size;
		DimFloat d_span;
		Space d_space;
		DimSizing d_sizing;
		Opacity d_opacity;
		LayoutStyle* d_layout;
	};
}

#endif // MK_BOX_H_INCLUDED
