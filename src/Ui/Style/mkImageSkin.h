//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_IMAGESKIN_H_INCLUDED
#define MK_IMAGESKIN_H_INCLUDED

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
	class _I_ ImageSkin : public Struct, public Typed < ImageSkin >
	{
	public:
		ImageSkin(string t, string r, string b, string l, string tl, string tr, string br, string bl, string fill)
			: d_topLeft(tl), d_topRight(tr), d_bottomRight(br), d_bottomLeft(bl)
			, d_top(t), d_right(r), d_bottom(b), d_left(l)
			, d_fill(fill)
			, d_images({ tl, tr, br, bl, t, r, b, l, fill })
			, d_size(false)
		{}

		ImageSkin(string basename)
			: ImageSkin(basename + "_top.png", basename + "_right.png", basename + "_bottom.png", basename + "_left.png", basename + "_topleft.png", basename + "_topright.png", basename + "_bottomright.png", basename + "_bottomleft.png", basename + "_fill.png")
		{}

		ImageSkin()
		{}

		bool null() { return d_images.size() == 0; }

		_A_ _M_ string d_topLeft;
		_A_ _M_ string d_topRight;
		_A_ _M_ string d_bottomRight;
		_A_ _M_ string d_bottomLeft;

		_A_ _M_ string d_top;
		_A_ _M_ string d_right;
		_A_ _M_ string d_bottom;
		_A_ _M_ string d_left;

		_A_ _M_ string d_fill;

		int d_topOut;
		int d_rightOut;
		int d_bottomOut;
		int d_leftOut;

		int d_topIn;
		int d_rightIn;
		int d_bottomIn;
		int d_leftIn;

		bool d_size;

		StringVector d_images;
	};
}

#endif // MK_IMAGESKIN_H_INCLUDED
