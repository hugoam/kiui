//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_IMAGESKIN_H
#define MK_IMAGESKIN_H

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
	class MK_UI_EXPORT _I_ Image : public IdStruct
	{
	public:
		Image(const string& name, int width = 0, int height = 0)
			: IdStruct(cls())
			, d_name(name), d_left(0), d_top(0), d_width(width), d_height(height), d_index(0), d_atlas(0)
		{}

		Image()
			: IdStruct(cls())
			, d_name(), d_left(0), d_top(0), d_width(0), d_height(0), d_index(0), d_atlas(0)
		{}

		Image(const Image& other)
			: IdStruct(other)
		{
			*this = other;
		}

		Image(Image&& other)
			: IdStruct(cls())
		{
			*this = other;
		}

		Image& operator=(const Image&) = default;

		bool null() const { return d_name.empty(); }

		string d_name;
		int d_left;
		int d_top;
		int d_width;
		int d_height;
		
		int d_index;
		int d_atlas;

		bool d_stretch;

		static Type& cls() { static Type ty(INDEXED); return ty; }
	};

	inline Image& findImage(const string& name)
	{
		for(Object* object : Image::cls().indexer().objects())
			if(object && object->as<Image>().d_name == name)
				return object->as<Image>();
	}

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
			: d_image(&findImage(image))
			, d_top(top), d_right(right), d_bottom(bottom), d_left(left)
			, d_margin(margin)
			, d_prepared(false)
			, d_images(9)
			, d_stretch(stretch)
		{
			this->setupImage(*d_image);
		}

		ImageSkin()
			: d_image(nullptr)
		{}

		bool null() const { return d_image == nullptr; }

		void setupImage(Image& image)
		{
			d_image = &image;
			d_images[TOP_LEFT].d_name = image.d_name + "_topleft";
			d_images[TOP_RIGHT].d_name = image.d_name + "_topright";
			d_images[BOTTOM_RIGHT].d_name = image.d_name + "_bottomright";
			d_images[BOTTOM_LEFT].d_name = image.d_name + "_bottomleft";

			d_images[TOP].d_name = image.d_name + "_top";
			d_images[RIGHT].d_name = image.d_name + "_right";
			d_images[BOTTOM].d_name = image.d_name + "_bottom";
			d_images[LEFT].d_name = image.d_name + "_left";

			d_images[FILL].d_name = image.d_name + "_fill";

			for(size_t i = 0; i < 9; ++i)
			{
				d_images[i].d_index = d_image->d_index;
				d_images[i].d_atlas = d_image->d_atlas;
			}

			this->setupSize(image.d_width, image.d_height);
		}

		void setupSize(int width, int height)
		{
			d_width = width;
			d_height = height;
			d_fillWidth = width - d_left - d_right;
			d_fillHeight = height - d_top - d_bottom;

			d_solidWidth = width - d_margin - d_margin;
			d_solidHeight = height - d_margin - d_margin;

			this->stretchCoords(0, 0, width, height, [this](Section s, int x, int y, int w, int h) {
				this->d_images[s].d_left = this->d_image->d_left + x;
				this->d_images[s].d_top = this->d_image->d_top + y;
				this->d_images[s].d_width = w;
				this->d_images[s].d_height = h;
			 });
		}

		void stretchCoords(int x, int y, int width, int height, std::function<void(Section, int, int, int, int)> filler) const
		{
			int fillWidth = width - d_left - d_right;
			int fillHeight = height - d_top - d_bottom;

			filler(TOP_LEFT, x, y, d_left, d_top);
			filler(TOP_RIGHT, x + fillWidth + d_left, y, d_right, d_top);
			filler(BOTTOM_RIGHT, x + fillWidth + d_left, y + fillHeight + d_top, d_right, d_bottom);
			filler(BOTTOM_LEFT, x, y + fillHeight + d_top, d_left, d_bottom);

			filler(TOP, x + d_left, y, fillWidth, d_top); // width, 0.f
			filler(RIGHT, x + fillWidth + d_left, y + d_top, d_right, fillHeight); // 0.f, height
			filler(BOTTOM, x + d_left, y + fillHeight + d_top, fillWidth, d_bottom); // width, 0.f
			filler(LEFT, x, y + d_top, d_left, fillHeight); // 0.f, height

			filler(FILL, x + d_left, y + d_top, fillWidth, fillHeight); // width, height
		}

		_A_ _M_ Image* d_image;
		_A_ _M_ string d_filetype;

		_A_ _M_ int d_top;
		_A_ _M_ int d_right;
		_A_ _M_ int d_bottom;
		_A_ _M_ int d_left;
		_A_ _M_ int d_margin;
		_A_ _M_ Dimension d_stretch;

		int d_width;
		int d_height;

		int d_solidWidth;
		int d_solidHeight;

		int d_fillWidth;
		int d_fillHeight;

		std::vector<Image> d_images;

		bool d_prepared;

		static Type& cls() { static Type ty; return ty; }
	};
}

#endif // MK_IMAGESKIN_H
