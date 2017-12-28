//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_NANORENDERER_H
#define TOY_NANORENDERER_H

/* toy */
#include <toyui/Types.h>
#include <toyui/Render/Renderer.h>

namespace toy
{
	class TOY_UI_NANO_EXPORT NanoRenderer : public Renderer
	{
	public:
		NanoRenderer(const string& resourcePath);

		// targets
		virtual object_ptr<RenderTarget> createRenderTarget(Layer& layer);

		// setup
		virtual void loadFont() final;
		virtual void loadImageRGBA(Image& image, const unsigned char* data) final;
		virtual void loadImage(Image& image) final;
		virtual void unloadImage(Image& image) final;

		// rendering
		virtual void beginFrame(RenderTarget& target) final;
		virtual void endFrame() final;

		// drawing
		virtual void beginTarget() final;
		virtual void endTarget() final;

#ifdef TOYUI_DRAW_CACHE
		virtual void layerCache(Layer& layer, void*& layerCache) final;
		virtual void clearLayer(void* layerCache) final;
		virtual void drawLayer(void* layerCache, float x, float y, float scale) final;

		virtual void beginUpdate(void* layerCache, float x, float y, float scale) final;
		virtual void endUpdate() final;
#else
		virtual void beginUpdate(float x, float y) final;
		virtual void endUpdate() final;
#endif

		virtual bool clipTest(const BoxFloat& rect) final;
		virtual void clipRect(const BoxFloat& rect) final;
		virtual void unclipRect() final;

		virtual void pathLine(float x1, float y1, float x2, float y2) final;
		virtual void pathBezier(float x1, float y1, float c1x, float c1y, float c2x, float c2y, float x2, float y2) final;
		virtual void pathRect(const BoxFloat& rect, const BoxFloat& corners, float border) final;
		virtual void pathCircle(float x, float y, float r) final;

		virtual void drawShadow(const BoxFloat& rect, const BoxFloat& corner, const Shadow& shadows) final;
		virtual void drawRect(const BoxFloat& rect, const BoxFloat& corners, InkStyle& skin) final;
		virtual void drawImage(const Image& image, const BoxFloat& rect) final;
		virtual void drawImageStretch(const Image& image, const BoxFloat& rect, float xstretch = 1.f, float ystretch = 1.f) final;
		virtual void drawText(float x, float y, const char* start, const char* end, InkStyle& skin) final;

		virtual void debugRect(const BoxFloat& rect, const Colour& colour) final;

		virtual void fill(InkStyle& skin, const BoxFloat& rect) final;
		virtual void stroke(InkStyle& skin) final;

		virtual void strokeGradient(const Paint& paint, const DimFloat& start, const DimFloat& end) final;

		virtual void fillText(const string& text, const BoxFloat& rect, InkStyle& skin, TextRow& row) final;
		virtual void breakText(const string& text, const DimFloat& space, InkStyle& skin, std::vector<TextRow>& textRows) final;

		void breakTextLine(const BoxFloat& rect, TextRow& textRow);
		void breakTextWidth(const char* string, const char* end, const BoxFloat& rect, InkStyle& skin, TextRow& textRow);
		void breakTextReturns(const char* string, const char* end, const BoxFloat& rect, InkStyle& skin, TextRow& textRow);

		virtual float textLineHeight(InkStyle& skin) final;
		virtual float textSize(const string& text, Dimension dim, InkStyle& skin) final;

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
