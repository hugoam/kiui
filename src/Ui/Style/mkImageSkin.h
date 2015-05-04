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
#include <functional>

namespace mk
{
	class MK_UI_EXPORT Image
	{
	public:
		Image(const string& name, int width = 0, int height = 0) : d_name(name), d_left(0), d_top(0), d_width(width), d_height(height), d_index(0) {}
		Image() : d_name(), d_left(0), d_top(0), d_width(0), d_height(0), d_index(0) {}

		bool null() const { return d_name.empty(); }

		string d_name;
		int d_left;
		int d_top;
		int d_width;
		int d_height;
		int d_index;

		bool d_stretch;

		static std::map<string, Image> sIcons;
	};

	class _I_ ImageSkin : public Struct
	{
	public:
		enum Section
		{
			TOP_LEFT = 0, // Corners
			TOP_RIGHT = 1,
			BOTTOM_RIGHT = 2,
			BOTTOM_LEFT = 3,
			TOP = 4, // Borders
			RIGHT = 5,
			BOTTOM = 6,
			LEFT = 7,
			FILL = 8 // Fill
		};

	public:
		ImageSkin(const string& image, int left, int top, int right, int bottom, int margin = 0, Dimension stretch = DIM_NULL)
			: d_image(image)
			, d_top(top), d_right(right), d_bottom(bottom), d_left(left)
			, d_margin(margin)
			, d_prepared(false)
			, d_images(9)
			, d_coords(9)
			, d_stretch(stretch)
		{
			this->setImage(image);
		}

		ImageSkin()
		{}

		bool null() const { return d_image.null(); }

		void setImage(const Image& image)
		{
			d_image = image;
			d_images[TOP_LEFT] = d_image.d_name + "_topleft";
			d_images[TOP_RIGHT] = d_image.d_name + "_topright";
			d_images[BOTTOM_RIGHT] = d_image.d_name + "_bottomright";
			d_images[BOTTOM_LEFT] = d_image.d_name + "_bottomleft";

			d_images[TOP] = d_image.d_name + "_top";
			d_images[RIGHT] = d_image.d_name + "_right";
			d_images[BOTTOM] = d_image.d_name + "_bottom";
			d_images[LEFT] = d_image.d_name + "_left";

			d_images[FILL] = d_image.d_name + "_fill";
		}

		void prepare(int width, int height)
		{
			d_width = width;
			d_height = height;
			d_fillWidth = width - d_left - d_right;
			d_fillHeight = height - d_top - d_bottom;

			this->stretchCoords(width, height, [this](Section s, int x, int y, int w, int h){ this->d_coords[s] = BoxFloat(x, y, w, h); });
		}

		void stretchCoords(int width, int height, std::function<void(Section, int, int, int, int)> filler) const
		{
			int fillWidth = width - d_left - d_right;
			int fillHeight = height - d_top - d_bottom;

			filler(TOP_LEFT, 0, 0, d_left, d_top);
			filler(TOP_RIGHT, fillWidth + d_left, 0, d_right, d_top);
			filler(BOTTOM_RIGHT, fillWidth + d_left, fillHeight + d_top, d_right, d_bottom);
			filler(BOTTOM_LEFT, 0, fillHeight + d_top, d_left, d_bottom);

			filler(TOP, d_left, 0, fillWidth, d_top); // width, 0.f
			filler(RIGHT, fillWidth + d_left, d_top, d_right, fillHeight); // 0.f, height
			filler(BOTTOM, d_left, fillHeight + d_top, fillWidth, d_bottom); // width, 0.f
			filler(LEFT, 0, d_top, d_left, fillHeight); // 0.f, height

			filler(FILL, d_left, d_top, fillWidth, fillHeight); // width, height
		}

		_A_ _M_ Image d_image;
		_A_ _M_ string d_filetype;

		_A_ _M_ int d_top;
		_A_ _M_ int d_right;
		_A_ _M_ int d_bottom;
		_A_ _M_ int d_left;
		_A_ _M_ int d_margin;
		_A_ _M_ Dimension d_stretch;

		int d_width;
		int d_height;

		int d_fillWidth;
		int d_fillHeight;

		std::vector<string> d_images;
		std::vector<BoxFloat> d_coords;

		bool d_prepared;

		static Type& cls() { static Type ty; return ty; }
	};
}

#endif // MK_IMAGESKIN_H_INCLUDED
