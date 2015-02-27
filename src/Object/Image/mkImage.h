//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_IMAGE_H
#define MK_IMAGE_H

/* mk */
#include <Object/Util/mkColour.h>

namespace mk
{
	class MK_OBJECT_EXPORT Palette
	{
	public:
		Palette();

		void load(string file);

		Colour colours[257];
	};

	class MK_OBJECT_EXPORT Image256
	{
	public:
		Image256(size_t width, size_t height, const Palette& palette);
		~Image256();

		void write(uint8_t* data);

		size_t* mPixels;
		size_t mWidth;
		size_t mHeight;
		Palette mPalette;
	};
}

#endif // MK_IMAGE_H
