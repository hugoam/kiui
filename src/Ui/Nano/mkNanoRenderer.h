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
		virtual void drawLayer(void* layerCache, float x, float y, float scale);

		virtual void beginLayer(void* layerCache, float x, float y, float scale);
		virtual void endLayer();

		virtual void beginUpdate(void* layerCache, float x, float y, float scale);
		virtual void endUpdate();
#else
		virtual void beginUpdate(float x, float y);
		virtual void endUpdate();
#endif

		virtual void clipRect(const BoxFloat& rect);
		virtual void unclipRect();

		virtual void clipFrame(const BoxFloat& rect, const BoxFloat& corners);
		virtual void unclipFrame();

		virtual void pathBezier(float x1, float y1, float c1x, float c1y, float c2x, float c2y, float x2, float y2);

		virtual void pathRect(const BoxFloat& rect, const BoxFloat& corners, float border);

		virtual void drawShadow(const BoxFloat& rect, const BoxFloat& corner, const Shadow& shadows);
		virtual void drawRect(const BoxFloat& rect, const BoxFloat& corners, InkStyle& skin);
		virtual void drawImage(const Image& image, const BoxFloat& rect);
		virtual void drawImageStretch(const Image& image, const BoxFloat& rect, float xstretch = 1.f, float ystretch = 1.f);
		virtual void drawText(float x, float y, const char* start, const char* end, InkStyle& skin);

		virtual void debugRect(const BoxFloat& rect, const Colour& colour);

		virtual void fill(InkStyle& skin, const BoxFloat& rect);
		virtual void stroke(InkStyle& skin);

		virtual void initImage(Image& image, bool tile);

		virtual void fillText(const string& text, const BoxFloat& rect, InkStyle& skin, TextRow& row);

		virtual void breakText(const string& text, const DimFloat& space, InkStyle& skin, std::vector<TextRow>& textRows);
		virtual void breakTextLine(const BoxFloat& rect, TextRow& textRow);

		virtual void breakTextWidth(const char* string, const char* end, const BoxFloat& rect, InkStyle& skin, TextRow& textRow);
		virtual void breakTextReturns(const char* string, const char* end, const BoxFloat& rect, InkStyle& skin, TextRow& textRow);

		virtual float textLineHeight(InkStyle& skin);
		virtual float textSize(const string& text, Dimension dim, InkStyle& skin);

	private:
		void setupText(InkStyle& skin);

		void drawImage(int image, const BoxFloat& rect, const BoxFloat& imageRect);

	protected:
		NanoWindow& m_window;
		NanoAtlas& m_atlas;
		NVGcontext* m_ctx;

		NVGalign m_alignH;
		float m_lineHeight;

		std::map<Layer*, NVGdisplayList*> m_layers;
	};
}

#endif
