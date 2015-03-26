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
		ImageSkin(string image, int leftIn, int topIn, int fillWidth, int fillHeight, int rightIn, int bottomIn)
			: d_image(image)
			, d_topIn(topIn), d_rightIn(rightIn), d_fillWidth(fillWidth), d_fillHeight(fillHeight), d_bottomIn(bottomIn), d_leftIn(leftIn)
			, d_topOut(0), d_rightOut(0), d_bottomOut(0), d_leftOut(0)
			, d_prepared(false)
		{}

		ImageSkin()
		{}

		bool null() { return d_image.empty(); }

		_A_ _M_ string d_image;
		_A_ _M_ string d_filetype;

		_A_ _M_ int d_topIn;
		_A_ _M_ int d_rightIn;
		_A_ _M_ int d_bottomIn;
		_A_ _M_ int d_leftIn;

		int d_topOut;
		int d_rightOut;
		int d_bottomOut;
		int d_leftOut;

		int d_fillWidth;
		int d_fillHeight;

		bool d_prepared;
	};
}

#endif // MK_IMAGESKIN_H_INCLUDED
