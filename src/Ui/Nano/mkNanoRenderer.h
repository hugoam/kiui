//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_NANORENDERER_H
#define MK_NANORENDERER_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Frame/mkRenderer.h>
#include <Ui/Nano/mkNanoWindow.h>

#include <Ui/Nano/nanovg/nanovg.h>

namespace mk
{
	class NanoRenderer : public Renderer
	{
	public:
		NanoRenderer(NanoWindow& window);

		NVGcontext* ctx() { return m_window.ctx(); }
		NanoAtlas& atlas() { return m_window.atlas(); }

#ifdef KIUI_DRAW_CACHE
		virtual void layerCache(Layer& layer, void*& layerCache);
		virtual void drawLayer(void* layerCache, float x, float y);

		virtual void beginLayer(void* layerCache);
		virtual void endLayer();

		virtual void beginUpdate(void* layerCache, float x, float y);
		virtual void endUpdate();
#else
		virtual void beginUpdate(float x, float y);
		virtual void endUpdate();
#endif

		virtual void clipRect(BoxFloat& rect);
		virtual void unclipRect();

		virtual void clipFrame(BoxFloat& rect, BoxFloat& corners);
		virtual void clipShape();
		virtual void unclipShape();

		virtual void pathBezier(float x1, float y1, float c1x, float c1y, float c2x, float c2y, float x2, float y2);

		virtual void pathRect(BoxFloat& rect, BoxFloat& corners, float border);

		virtual void drawShadow(BoxFloat& rect, BoxFloat& corner, Shadow& shadows);
		virtual void drawRect(BoxFloat& rect, BoxFloat& corners, InkStyle& skin);
		virtual void drawRectClipped(BoxFloat& rect, BoxFloat& corners, InkStyle& skin, BoxFloat& clipRect, BoxFloat& clipCorners);
		virtual void drawImage(const Image& image, BoxFloat& rect);
		virtual void drawImageStretch(const Image& image, BoxFloat& rect, float xstretch = 1.f, float ystretch = 1.f);
		virtual void drawText(float x, float y, const char* start, const char* end, InkStyle& skin);

		virtual void fill(InkStyle& skin, BoxFloat& rect);
		virtual void stroke(InkStyle& skin);

		virtual void initImage(Image& image, bool tile);

		virtual float textSize(const string& text, Dimension dim, InkStyle& skin);

		virtual void fillText(const string& text, BoxFloat& paddedRect, InkStyle& skin, TextRow& row);
		virtual void breakText(const string& text, BoxFloat& paddedRect, InkStyle& skin, std::vector<TextRow>& textRows);
		virtual void breakTextLine(BoxFloat& paddedRect, TextRow& textRow);

	private:
		void setupText(InkStyle& skin);

		void drawImage(int image, BoxFloat& rect, BoxFloat& imageRect);

	protected:
		NanoWindow& m_window;
		NanoAtlas& m_atlas;
		NVGcontext* m_ctx;

		std::map<Layer*, NVGdisplayList*> m_layers;
	};
}

#endif
