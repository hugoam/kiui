//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_RENDERER_H
#define TOY_RENDERER_H

/* toy Front */
#include <toyobj/Typed.h>
#include <toyui/Forward.h>
#include <toyui/Render/Caption.h>

namespace toy
{
	class TOY_UI_EXPORT RenderTarget
	{
	public:
		RenderTarget(Renderer& renderer, MasterLayer& masterLayer, bool gammaCorrected);
		virtual ~RenderTarget() {}

		MasterLayer& layer() { return m_masterLayer; }

		bool gammaCorrected() { return m_gammaCorrected; }
		void setGammaCorrected(bool enabled) { m_gammaCorrected = enabled; }

		void render();

	protected:
		Renderer& m_renderer;
		MasterLayer& m_masterLayer;

		bool m_gammaCorrected;
	};

	class TOY_UI_EXPORT Renderer
	{
	public:
		Renderer(const string& resourcePath);
		virtual ~Renderer() {}

		// init
		virtual void setupContext() = 0;
		virtual void releaseContext() = 0;

		// targets
		virtual unique_ptr<RenderTarget> createRenderTarget(MasterLayer& masterLayer) = 0;

		// setup
		virtual void loadFont() = 0;
		virtual void loadImageRGBA(Image& image, const unsigned char* data) = 0;
		virtual void loadImage(Image& image) = 0;
		virtual void unloadImage(Image& image) = 0;

		// rendering
		virtual void render(RenderTarget& target) = 0;

		// drawing
		virtual void beginTarget() = 0;
		virtual void endTarget() = 0;

#ifdef TOYUI_DRAW_CACHE
		virtual void layerCache(Layer& layer, void*& layerCache) = 0;
		virtual void clearLayer(void* layerCache) = 0;
		virtual void drawLayer(void* layerCache, float x, float y, float scale = 1.f) = 0;

		virtual void beginUpdate(void* layerCache, float x, float y, float scale = 1.f) = 0;
		virtual void endUpdate() = 0;
#else
		virtual void beginUpdate(float x, float y) = 0;
		virtual void endUpdate() = 0;
#endif

		virtual bool clipTest(const BoxFloat& rect) = 0;
		virtual void clipRect(const BoxFloat& rect) = 0;
		virtual void unclipRect() = 0;

		virtual void pathLine(float x1, float y1, float x2, float y2) = 0;
		virtual void pathBezier(float x1, float y1, float c1x, float c1y, float c2x, float c2y, float x2, float y2) = 0;
		virtual void pathRect(const BoxFloat& rect, const BoxFloat& corners, float border) = 0;
		virtual void pathCircle(float x, float y, float r) = 0;

		virtual void fill(InkStyle& skin, const BoxFloat& rect) = 0;
		virtual void stroke(InkStyle& skin) = 0;

		virtual void strokeGradient(const Paint& paint, const DimFloat& start, const DimFloat& end) = 0;

		virtual void drawShadow(const BoxFloat& rect, const BoxFloat& corner, const Shadow& shadows) = 0;
		virtual void drawRect(const BoxFloat& rect, const BoxFloat& corners, InkStyle& skin) = 0;
		virtual void drawText(float x, float y, const char* start, const char* end, InkStyle& skin) = 0;

		virtual void drawImage(const Image& image, const BoxFloat& rect) = 0;
		virtual void drawImageStretch(const Image& image, const BoxFloat& rect, float xstretch = 1.f, float ystretch = 1.f) = 0;

		virtual void debugRect(const BoxFloat& rect, const Colour& colour) = 0;

		virtual void fillText(const string& text, const BoxFloat& rect, InkStyle& skin, TextRow& row) = 0;
		virtual void breakText(const string& text, const DimFloat& space, InkStyle& skin, std::vector<TextRow>& rows) = 0;

		virtual float textLineHeight(InkStyle& skin) = 0;
		virtual float textSize(const string& text, Dimension dim, InkStyle& skin) = 0;

	protected:
		string m_resourcePath;
		size_t m_debugBatch;
		size_t m_debugDepth;
	};
}

#endif
