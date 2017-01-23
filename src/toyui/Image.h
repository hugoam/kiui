//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_IMAGE_H
#define TOY_IMAGE_H

/* toy Og */
#include <toyobj/Object.h>
#include <toyobj/String/String.h>
#include <toyui/Forward.h>

namespace toy
{
	class _I_ TOY_UI_EXPORT Image : public IdStruct
	{
	public:
		Image(const string& name, const string& path, int width = 0, int height = 0)
			: IdStruct(cls())
			, d_name(name), d_path(path), d_left(0), d_top(0), d_width(width), d_height(height), d_index(0), d_atlas(nullptr), d_tile(false)
		{}

		Image()
			: IdStruct(cls())
			, d_name(), d_path(), d_left(0), d_top(0), d_width(0), d_height(0), d_index(0), d_atlas(nullptr), d_tile(false)
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
		string d_path;
		int d_left;
		int d_top;
		int d_width;
		int d_height;

		int d_index;
		ImageAtlas* d_atlas;

		bool d_tile;
		bool d_stretch;

		static Type& cls() { static Type ty(INDEXED); return ty; }
	};

}

#endif
