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

		inline bool flow() { return d_style->d_flow == FLOW; }
		inline bool opaque() { return d_opacity == _OPAQUE; }

		inline void setOpacity(Opacity opacity) { d_opacity = opacity; }

	protected:
		DimFloat d_position;
		DimFloat d_size;
		DimFloat d_span;
		DimSizing d_sizing;
		Opacity d_opacity;
		LayoutStyle* d_style;
	};
}

#endif // MK_BOX_H_INCLUDED
