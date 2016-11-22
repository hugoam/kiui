//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_NANOINK_H
#define MK_NANOINK_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Nano/mkNanoWindow.h>

#ifdef KIUI_DRAW_CACHE
#include <Ui/Nano/nanovg_cache/nanovg.h>
#else
#include <Ui/Nano/nanovg/nanovg.h>
#endif


namespace mk
{
	class NanoRenderer : public Renderer
	{
	public:
		NanoRenderer(NanoWindow& window);

		NVGcontext* ctx() { return m_window.ctx(); }
		NanoAtlas& atlas() { return m_window.atlas(); }

#ifdef KIUI_DRAW_CACHE
		void createCache(void*& cache, size_t size);
		void drawCache(void* cache, float x, float y);
		void destroyCache(void* cache);

		void beginUpdate(void* cache);
		void endUpdate(void* cache);
#else
		void beginUpdate(float x, float y);
		void endUpdate();
#endif

		void clipRect(BoxFloat& rect);
		void unclipRect();

		void clipFrame(BoxFloat& rect, BoxFloat& corners);
		void clipShape();
		void unclipShape();

		void pathBezier(float x1, float y1, float c1x, float c1y, float c2x, float c2y, float x2, float y2);

		void pathRect(BoxFloat& rect, BoxFloat& corners, float border);

		void drawShadow(BoxFloat& rect, BoxFloat& corner, Shadow& shadows);
		void drawRect(BoxFloat& rect, BoxFloat& corners, InkStyle& skin);
		void drawRectClipped(BoxFloat& rect, BoxFloat& corners, InkStyle& skin, BoxFloat& clipRect, BoxFloat& clipCorners);
		void drawImage(const Image& image, BoxFloat& rect);
		void drawImageStretch(const Image& image, BoxFloat& rect, float xstretch = 1.f, float ystretch = 1.f);
		void drawText(float x, float y, const char* start, const char* end, InkStyle& skin);

		void fill(InkStyle& skin, BoxFloat& rect);
		void stroke(InkStyle& skin);

		void initImage(Image& image, bool tile);

		float textSize(const string& text, Dimension dim, InkStyle& skin);

		void fillText(const string& text, BoxFloat& paddedRect, InkStyle& skin, TextRow& row);
		void breakText(const string& text, BoxFloat& paddedRect, InkStyle& skin, std::vector<TextRow>& textRows);
		void breakTextLine(BoxFloat& paddedRect, TextRow& textRow);

	private:
		void setupText(InkStyle& skin);


		void drawImage(int image, BoxFloat& rect, BoxFloat& imageRect);

	protected:
		NanoWindow& m_window;
		NanoAtlas& m_atlas;
		NVGcontext* m_ctx;
	};
}

#endif
