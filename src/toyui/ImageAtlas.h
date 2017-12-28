//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_NANOATLAS_H
#define TOY_NANOATLAS_H

/* toy */
#include <toyui/Types.h>
#include <toyui/Image.h>

#include <memory>

class GuillotineBinPack;

namespace toy
{
	class TOY_UI_EXPORT ImageAtlas
	{
	public:
		ImageAtlas(size_t width, size_t height);
		~ImageAtlas();

		void createAtlas();
		void generateAtlas(std::vector<object_ptr<Image>>& images);

		void setupAtlas(int index);

		void addSprite(Image& image);
		void placeSprite(Image& sprite);
		void blitSprite(Image& sprite);

	public:
		size_t m_width;
		size_t m_height;

		unsigned char* m_data;
		Image m_image;

		std::vector<Image*> m_sprites;

	protected:
		unique_ptr<GuillotineBinPack> m_rectPacker;
	};
}

#endif
