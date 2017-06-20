//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/ImageAtlas.h>

#include <toyobj/Util/Unique.h>
#include <toyobj/String/String.h>

#include <toyui/UiWindow.h>

#include <RectPacking/Rect.h>
#include <RectPacking/GuillotineBinPack.h>

#include <stb_image.h>

namespace toy
{
	ImageAtlas::ImageAtlas(size_t width, size_t height)
		: m_width(width)
		, m_height(height)
		, m_image("ImageAtlas", "", width, height)
		, m_rectPacker(make_unique<GuillotineBinPack>(width, height))
	{}

	ImageAtlas::~ImageAtlas()
	{}

	void ImageAtlas::createAtlas()
	{
		m_data = new unsigned char[m_width*m_height*4];

		unsigned char* in = m_data;
		for(size_t y = 0; y < m_height; ++y)
			for(size_t x = 0; x < m_width; ++x)
			{
				*(in++) = 0;
				*(in++) = 0;
				*(in++) = 0;
				*(in++) = 0;
			}
	}

	void ImageAtlas::generateAtlas(std::vector<object_ptr<Image>>& images)
	{
		this->createAtlas();

		// @todo : sort images

		for(auto& image : images)
			this->addSprite(*image);
	}

	void ImageAtlas::setupAtlas(int index)
	{
		m_image.d_index = index;
		delete [] m_data;
	}

	void ImageAtlas::addSprite(Image& sprite)
	{
		m_sprites.emplace_back(&sprite);

		this->placeSprite(sprite);
		this->blitSprite(sprite);

		sprite.d_atlas = this;
	}

	void ImageAtlas::placeSprite(Image& sprite)
	{
		BPRect rect = m_rectPacker->Insert(sprite.d_width, sprite.d_height, false,
										  GuillotineBinPack::RectBestShortSideFit, GuillotineBinPack::SplitShorterLeftoverAxis);

		sprite.d_left = rect.x;
		sprite.d_top = rect.y;
	}

	void ImageAtlas::blitSprite(Image& sprite)
	{
		string path = sprite.d_path;

		int width, height, n;
		unsigned char* img;
		stbi_set_unpremultiply_on_load(1);
		stbi_convert_iphone_png_to_rgb(1);
		img = stbi_load(path.c_str(), &width, &height, &n, 4);

		unsigned char* out = img;
		for(int y = 0; y < height; ++y)
		{
			size_t offset = sprite.d_left * 4 + (sprite.d_top + y) * m_width * 4;
			unsigned char* in = m_data + offset;
			for(int x = 0; x < width; ++x)
			{
				*(in++) = *(out++);
				*(in++) = *(out++);
				*(in++) = *(out++);
				*(in++) = *(out++);
			}
		}

		stbi_image_free(img);
	}
}
