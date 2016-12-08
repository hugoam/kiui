//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_NANOWINDOW_H
#define MK_NANOWINDOW_H

/* mk Og */
#include <Ui/mkUiForward.h>
#include <Ui/Frame/mkDrawFrame.h>
#include <Ui/Nano/RectPacking/Rect.h>
#include <Ui/Nano/RectPacking/GuillotineBinPack.h>

#include <memory>

namespace mk
{
	struct ImageRect : public BPRect
	{
		string subfolder;
		string image;
	};

	class MK_UI_EXPORT NanoAtlas
	{
	public:
		NanoAtlas(NanoWindow& window, const string& path, size_t width, size_t height);

		const string& path() { return m_path; }
		size_t width() { return m_width; }
		size_t height() { return m_height; }
		int image() { return m_image; }

		void createAtlas();
		void generateAtlas();
		void loadAtlas();

		void fitImage(ImageRect& image);
		void blitImage(ImageRect& image);

		ImageRect& findSpriteRect(const string& image);
		void appendSprite(const string& image, const string& group);
		void defineSprite(const string& image, float left, float top, float width, float height);

		std::vector<ImageRect>& sprites() { return m_sprites; }

	protected:
		NanoWindow& m_window;
		NVGcontext* m_ctx;
		string m_path;
		size_t m_width;
		size_t m_height;
		GuillotineBinPack m_rectPacker;
		std::vector<ImageRect> m_sprites;
		unsigned char* m_data;
		int m_image;
	};

	class MK_UI_EXPORT NanoWindow : public InkWindow
	{
	public:
		NanoWindow(UiWindow& uiWindow, string resourcePath);
		~NanoWindow();

		void nextFrame(double time, double delta);

		InkTarget& screenTarget();

		string resourcePath() { return m_resourcePath; }
		NVGcontext* ctx() { return m_ctx; }
		NanoAtlas& atlas() { return *m_atlas; }

	protected:
		NanoRenderer& m_nanorenderer;

		string m_resourcePath;

		NVGcontext* m_ctx;
		unique_ptr<NanoAtlas> m_atlas;
	};

}

#endif
