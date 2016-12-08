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
	class MK_UI_EXPORT Renderer
	{
	public:
		virtual ~Renderer() {}

#ifdef KIUI_DRAW_CACHE
		virtual void layerCache(Layer& layer, void*& layerCache) = 0;
		virtual void drawLayer(void* layerCache, float x, float y) = 0;

		virtual void beginLayer(void* layerCache) = 0;
		virtual void endLayer() = 0;

		virtual void beginUpdate(void* layerCache, float x, float y) = 0;
		virtual void endUpdate() = 0;
#else
		virtual void beginUpdate(float x, float y) = 0;
		virtual void endUpdate() = 0;
#endif

		virtual void clipRect(BoxFloat& rect) = 0;
		virtual void unclipRect() = 0;

		virtual void clipFrame(BoxFloat& rect, BoxFloat& corners) = 0;
		virtual void clipShape() = 0;
		virtual void unclipShape() = 0;

		virtual void pathBezier(float x1, float y1, float c1x, float c1y, float c2x, float c2y, float x2, float y2) = 0;
		virtual void pathRect(BoxFloat& rect, BoxFloat& corners, float border) = 0;

		virtual void fill(InkStyle& skin, BoxFloat& rect) = 0;
		virtual void stroke(InkStyle& skin) = 0;

		virtual void drawShadow(BoxFloat& rect, BoxFloat& corner, Shadow& shadows) = 0;
		virtual void drawRect(BoxFloat& rect, BoxFloat& corners, InkStyle& skin) = 0;
		virtual void drawRectClipped(BoxFloat& rect, BoxFloat& corners, InkStyle& skin, BoxFloat& clipRect, BoxFloat& clipCorners) = 0;
		virtual void drawText(float x, float y, const char* start, const char* end, InkStyle& skin) = 0;

		virtual void drawImage(const Image& image, BoxFloat& rect) = 0;
		virtual void drawImageStretch(const Image& image, BoxFloat& rect, float xstretch = 1.f, float ystretch = 1.f) = 0;

		virtual void fillText(const string& text, BoxFloat& paddedRect, InkStyle& skin, TextRow& row) = 0;
		virtual void breakText(const string& text, BoxFloat& paddedRect, InkStyle& skin, std::vector<TextRow>& rows) = 0;

		virtual float textSize(const string& text, Dimension dim, InkStyle& skin) = 0;
	};
}

#endif
