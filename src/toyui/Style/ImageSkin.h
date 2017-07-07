//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_IMAGESKIN_H
#define TOY_IMAGESKIN_H

/* toy */
#include <toyobj/Type.h>
#include <toyobj/String/String.h>
#include <toyui/Forward.h>
#include <toyui/Style/Dim.h>
#include <toyui/Image.h>

/* std */
#include <vector>

namespace toy
{
	class _refl_ ImageSkin : public Struct
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
		ImageSkin(Image& image, int left, int top, int right, int bottom, int margin = 0, Dimension stretch = DIM_NULL)
			: d_image(&image)
			, d_left(left), d_top(top), d_right(right), d_bottom(bottom)
			, d_margin(margin)
			, d_stretch(stretch)
			, d_width(image.d_width)
			, d_height(image.d_height)
			, d_fillWidth(image.d_width - d_left - d_right)
			, d_fillHeight(image.d_height - d_top - d_bottom)
			, d_solidWidth(image.d_width - d_margin - d_margin)
			, d_solidHeight(image.d_height - d_margin - d_margin)
			, d_images(9)
		{
			for(Image& subimage : d_images)
				subimage = *d_image;

			d_size.x = d_stretch == DIM_X ? float(d_solidHeight) : 0.f;
			d_size.y = d_stretch == DIM_Y ? float(d_solidWidth) : 0.f;

			this->stretchCoords(0, 0, image.d_width, image.d_height, [this](Section s, const BoxFloat& rect) {
				this->d_images[s].d_left = this->d_image->d_left + int(rect.x);
				this->d_images[s].d_top = this->d_image->d_top + int(rect.y);
				this->d_images[s].d_width = int(rect.w);
				this->d_images[s].d_height = int(rect.h);
			});
		}

		ImageSkin(Image& image, const ImageSkin& ref)
			: ImageSkin(image, ref.d_left, ref.d_top, ref.d_right, ref.d_bottom, ref.d_margin, ref.d_stretch)
		{}

		ImageSkin()
			: d_image(nullptr)
		{}

		bool null() const { return d_image == nullptr; }

		void stretchCoords(int x, int y, int width, int height, std::function<void(Section, const BoxFloat&)> filler) const
		{
			int fillWidth = width - d_left - d_right;
			int fillHeight = height - d_top - d_bottom;

			filler(TOP_LEFT, BoxFloat(x, y, d_left, d_top));
			filler(TOP_RIGHT, BoxFloat(x + fillWidth + d_left, y, d_right, d_top));
			filler(BOTTOM_RIGHT, BoxFloat(x + fillWidth + d_left, y + fillHeight + d_top, d_right, d_bottom));
			filler(BOTTOM_LEFT, BoxFloat(x, y + fillHeight + d_top, d_left, d_bottom));

			filler(TOP, BoxFloat(x + d_left, y, fillWidth, d_top));
			filler(RIGHT, BoxFloat(x + fillWidth + d_left, y + d_top, d_right, fillHeight));
			filler(BOTTOM, BoxFloat(x + d_left, y + fillHeight + d_top, fillWidth, d_bottom));
			filler(LEFT, BoxFloat(x, y + d_top, d_left, fillHeight));

			filler(FILL, BoxFloat(x + d_left, y + d_top, fillWidth, fillHeight));
		}

		_attr_ _mut_ Image* d_image;

		_attr_ _mut_ int d_left;
		_attr_ _mut_ int d_top;
		_attr_ _mut_ int d_right;
		_attr_ _mut_ int d_bottom;
		_attr_ _mut_ int d_margin;
		_attr_ _mut_ Dimension d_stretch;

		int d_width;
		int d_height;

		int d_solidWidth;
		int d_solidHeight;

		int d_fillWidth;
		int d_fillHeight;

		DimFloat d_size;

		std::vector<Image> d_images;

		static Type& cls() { static Type ty; return ty; }
	};
}

#endif // TOY_IMAGESKIN_H
