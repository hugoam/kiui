//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_RENDERER_H
#define MK_RENDERER_H

/* mk Front */
#include <Object/mkTyped.h>
#include <Ui/mkUiForward.h>
#include <Ui/Frame/mkCaption.h>

#define KIUI_DRAW_CACHE

namespace mk
{
	class MK_UI_EXPORT RenderTarget
	{
	public:
		RenderTarget(Renderer& renderer, MasterLayer& masterLayer, bool gammaCorrected);

		bool gammaCorrected() { return m_gammaCorrected; }
		void setGammaCorrected(bool enabled) { m_gammaCorrected = enabled; }

		void render();

	protected:
		Renderer& m_renderer;
		MasterLayer& m_masterLayer;

		bool m_gammaCorrected;
	};

	class MK_UI_EXPORT Renderer
	{
	public:
		Renderer(const string& resourcePath);
		virtual ~Renderer() {}

		// init
		virtual void setupContext() = 0;
		virtual void releaseContext() = 0;

		// setup
		virtual void loadImageRGBA(Image& image, const unsigned char* data) = 0;
		virtual void loadImage(Image& image) = 0;
		virtual void unloadImage(Image& image) = 0;

		// rendering
		virtual void render(MasterLayer& layer) = 0;

		// drawing
		virtual void beginTarget() = 0;
		virtual void endTarget() = 0;

#ifdef KIUI_DRAW_CACHE
		virtual void layerCache(Layer& layer, void*& layerCache) = 0;
		virtual void drawLayer(void* layerCache, float x, float y, float scale = 1.f) = 0;

		virtual void beginLayer(void* layerCache, float x, float y, float scale = 1.f) = 0;
		virtual void endLayer() = 0;

		virtual void beginUpdate(void* layerCache, float x, float y, float scale = 1.f) = 0;
		virtual void endUpdate() = 0;
#else
		virtual void beginUpdate(float x, float y) = 0;
		virtual void endUpdate() = 0;
#endif

		virtual void clipRect(const BoxFloat& rect) = 0;
		virtual void unclipRect() = 0;

		virtual void clipFrame(const BoxFloat& rect, const BoxFloat& corners) = 0;
		virtual void unclipFrame() = 0;

		virtual void pathBezier(float x1, float y1, float c1x, float c1y, float c2x, float c2y, float x2, float y2) = 0;
		virtual void pathRect(const BoxFloat& rect, const BoxFloat& corners, float border) = 0;

		virtual void fill(InkStyle& skin, const BoxFloat& rect) = 0;
		virtual void stroke(InkStyle& skin) = 0;

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
		int m_debugBatch;
	};
}

#endif
