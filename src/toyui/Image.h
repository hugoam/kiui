//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_IMAGE_H
#define TOY_IMAGE_H

/* toy */
#include <toyobj/Object.h>
#include <toyobj/String/String.h>
#include <toyui/Types.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT Image : public Struct
	{
	public:
		Image(const string& name = "", const string& path = "", int width = 0, int height = 0)
			: d_name(name), d_path(path), d_left(0), d_top(0), d_width(width), d_height(height)
			, d_index(0), d_atlas(nullptr), d_tile(false), d_stretch(true), d_filtering(true)
		{}

		_attr_ string d_name;
		_attr_ string d_path;
		int d_left;
		int d_top;
		int d_width;
		int d_height;

		int d_index;
		ImageAtlas* d_atlas;

		bool d_tile;
		bool d_stretch;
		bool d_filtering;
	};

}

#endif
