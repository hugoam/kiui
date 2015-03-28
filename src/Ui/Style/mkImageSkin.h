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
#include <Ui/Style/mkDim.h>
#include <Ui/mkUiForward.h>

/* Standards */
#include <array>
#include <map>

namespace mk
{
	class _I_ ImageSkin : public Struct, public Typed < ImageSkin >
	{
	public:
		enum Section
		{
			TOP = 0, // Borders
			RIGHT = 1,
			BOTTOM = 2,
			LEFT = 3,
			TOP_LEFT = 4, // Corners
			TOP_RIGHT = 5,
			BOTTOM_RIGHT = 6,
			BOTTOM_LEFT = 7,
			FILL = 8 // Fill
		};

	public:
		ImageSkin(string image, int leftIn, int topIn, int fillWidth, int fillHeight, int rightIn, int bottomIn)
			: d_image(image)
			, d_topIn(topIn), d_rightIn(rightIn), d_fillWidth(fillWidth), d_fillHeight(fillHeight), d_bottomIn(bottomIn), d_leftIn(leftIn)
			, d_topOut(0), d_rightOut(0), d_bottomOut(0), d_leftOut(0)
			, d_prepared(false)
			, d_images(9)
			, d_coords(9)
		{
			d_images[TOP] = d_image + "_top";
			d_images[RIGHT] = d_image + "_right";
			d_images[BOTTOM] = d_image + "_bottom";
			d_images[LEFT] = d_image + "_left";

			d_images[TOP_LEFT] = d_image + "_topleft";
			d_images[TOP_RIGHT] = d_image + "_topright";
			d_images[BOTTOM_RIGHT] = d_image + "_bottomright";
			d_images[BOTTOM_LEFT] = d_image + "_bottomleft";

			d_images[FILL] = d_image + "_fill";

			d_coords[TOP] = BoxFloat(d_leftIn, 0, d_fillWidth, d_topIn);
			d_coords[RIGHT] = BoxFloat(d_fillWidth + d_leftIn, d_topIn, d_rightIn, d_fillHeight);
			d_coords[BOTTOM] = BoxFloat(d_leftIn, d_fillHeight + d_topIn, d_fillWidth, d_bottomIn);
			d_coords[LEFT] = BoxFloat(0, d_topIn, d_leftIn, d_fillHeight);

			d_coords[TOP_LEFT] = BoxFloat(0, 0, d_leftIn, d_topIn);
			d_coords[TOP_RIGHT] = BoxFloat(d_fillWidth + d_leftIn, 0, d_rightIn, d_topIn);
			d_coords[BOTTOM_RIGHT] = BoxFloat(d_fillWidth + d_leftIn, d_fillHeight + d_topIn, d_rightIn, d_bottomIn);
			d_coords[BOTTOM_LEFT] = BoxFloat(0, d_fillHeight + d_topIn, d_leftIn, d_bottomIn);

			d_coords[FILL] = BoxFloat(d_leftIn, d_topIn, d_fillWidth, d_fillHeight);
		}

		ImageSkin()
		{}

		bool null() { return d_image.empty(); }

		_A_ _M_ string d_image;
		_A_ _M_ string d_filetype;

		_A_ _M_ int d_topIn;
		_A_ _M_ int d_rightIn;
		_A_ _M_ int d_bottomIn;
		_A_ _M_ int d_leftIn;

		std::vector<string> d_images;
		std::vector<BoxFloat> d_coords;

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
