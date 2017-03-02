//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_NANORENDERER_H
#define TOY_NANORENDERER_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Render/Renderer.h>

namespace toy
{
	class TOY_UI_EXPORT NanoRenderer : public Renderer
	{
	public:
		NanoRenderer(const string& resourcePath);
		~NanoRenderer();

		// targets
		virtual unique_ptr<RenderTarget> createRenderTarget(MasterLayer& masterLayer);

		// setup
		virtual void loadFont();
		virtual void loadImageRGBA(Image& image, const unsigned char* data);
		virtual void loadImage(Image& image);
		virtual void unloadImage(Image& image);

		// rendering
		virtual void render(RenderTarget& target);

		// drawing
		virtual void beginTarget();
		virtual void endTarget();

#ifdef TOYUI_DRAW_CACHE
		virtual void layerCache(Layer& layer, void*& layerCache);
		virtual void clearLayer(void* layerCache);
		virtual void drawLayer(void* layerCache, float x, float y, float scale);

		virtual void beginUpdate(void* layerCache, float x, float y, float scale);
		virtual void endUpdate();
#else
		virtual void beginUpdate(float x, float y);
		virtual void endUpdate();
#endif

		virtual bool clipTest(const BoxFloat& rect);
		virtual void clipRect(const BoxFloat& rect);
		virtual void unclipRect();

		virtual void pathLine(float x1, float y1, float x2, float y2);

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
		NVGcontext* m_ctx;

		float m_lineHeight;

		std::map<Layer*, NVGdisplayList*> m_layers;
	};
}

#endif
