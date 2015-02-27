//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Object/mkObjectConfig.h>
#include <Object/Image/mkImage.h>

#include <Object/Util/mkColour.h>

namespace mk
{
	Palette::Palette()
	{}

	void Palette::load(string file)
	{
		FILE* fpalette = fopen(file.c_str(), "r");
		for(int i = 0; i < 256; i++)  //15; i++)
		{
			uint8_t cl1, cl2, cl3;
			fread(&cl1, sizeof(uint8_t), 1, fpalette);
			fread(&cl2, sizeof(uint8_t), 1, fpalette);
			fread(&cl3, sizeof(uint8_t), 1, fpalette);
			colours[i] = Colour(cl3, cl2, cl1);
		}
		fclose(fpalette);
	}

	Image256::Image256(size_t width, size_t height, const Palette& palette)
		: mWidth(width)
		, mHeight(height)
		, mPalette(palette)
	{
		mPixels = new size_t[mWidth * mHeight];
	}

	Image256::~Image256()
	{
		delete [] mPixels;
	}

	void Image256::write(uint8_t* data)
	{
		size_t index = 0;
		for(size_t y = 0; y < mHeight; ++y)
			for(size_t x = 0; x < mWidth; ++x, ++index)
			{
				int colid = mPixels[index];
				Colour color = colid == 16 ? Colour() : mPalette.colours[colid];

				// PF_A8R8G8B8 // Little-Endian
				*data++ = static_cast<uint8_t>(color.b() * 255);
				*data++ = static_cast<uint8_t>(color.g() * 255);
				*data++ = static_cast<uint8_t>(color.r() * 255);
				*data++ = 255;
			}
	}
}
