//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_NANOATLAS_H
#define TOY_NANOATLAS_H

/* toy Og */
#include <toyui/Forward.h>
#include <toyui/Image.h>
#include <toyui/Nano/RectPacking/Rect.h>
#include <toyui/Nano/RectPacking/GuillotineBinPack.h>

#include <memory>

namespace toy
{
	class TOY_UI_EXPORT ImageAtlas
	{
	public:
		ImageAtlas(size_t width, size_t height);

		size_t width() const { return m_width; }
		size_t height() const { return m_height; }

		const unsigned char* data() const { return m_data; }

		Image& image() { return m_image; }

		const std::vector<Image*>& sprites() const { return m_sprites; }

		void createAtlas();
		void generateAtlas(std::vector<Image>& images);

		void setupAtlas(int index);

		void addSprite(Image& image);
		void placeSprite(Image& sprite);
		void blitSprite(Image& sprite);

	protected:
		size_t m_width;
		size_t m_height;

		std::vector<Image*> m_sprites;
		unsigned char* m_data;
		Image m_image;

		GuillotineBinPack m_rectPacker;
	};
}

#endif
