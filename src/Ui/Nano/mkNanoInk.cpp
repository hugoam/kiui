//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Nano/mkNanoInk.h>

#include <Object/Util/mkColour.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>
#include <Ui/Widget/mkWidget.h>

#include <Ui/Nano/mkNanoWindow.h>

#ifdef KIUI_DRAW_CACHE
#include <Ui/Nano/nanovg_cache/nanovg.h>
#else
#include <Ui/Nano/nanovg/nanovg.h>
#endif

#include <cmath>

#define NANO_ATLAS

namespace mk
{

	inline float clamp(float v, float mn, float mx)
	{
		return (v > mx) ? mx : (v < mn) ? mn : v;
	}

	void nvgRoundedBox(NVGcontext *ctx, float x, float y, float w, float h, float cr0, float cr1, float cr2, float cr3)
	{
#ifdef KIUI_DRAW_CACHE
		nvgRoundedRect4(ctx, x, y, w, h, cr0, cr1, cr2, cr3);
#else
		nvgRoundedRectVarying(ctx, x, y, w, h, cr0, cr1, cr2, cr3);
#endif
	}

	NVGcolor nvgColour(const Colour& colour)
	{
		return nvgRGBAf(colour.r(), colour.g(), colour.b(), colour.a());
	}

	NVGcolor nvgOffsetColour(const Colour& colour, float delta)
	{
		float offset = delta / 255.0f;
		return nvgRGBAf(	clamp(colour.r() + offset, 0, 1),
							clamp(colour.g() + offset, 0, 1),
							clamp(colour.b() + offset, 0, 1),
							colour.a());
	}

	NanoRenderer::NanoRenderer(NanoWindow& window)
		: m_window(window)
		, m_atlas(window.atlas())
		, m_ctx(window.ctx())
	{}

#ifdef KIUI_DRAW_CACHE
	void NanoRenderer::createCache(void*& cache, size_t size)
	{
		if(!cache)
			cache = nvgCreateDisplayList(11);
	}

	void NanoRenderer::drawCache(void* cache, float x, float y)
	{
		nvgSave(ctx());
		nvgTranslate(ctx(), x, y);
		nvgDrawDisplayList(ctx(), (NVGdisplayList*) cache);
		nvgRestore(ctx());
	}

	void NanoRenderer::destroyCache(void* cache)
	{
		nvgDeleteDisplayList((NVGdisplayList*) cache);
	}
#endif

	void NanoRenderer::initImage(Image& image, bool tile)
	{
		if(image.d_index)
			return;

		string path = m_window.resourcePath() + "interface/uisprites/" + image.d_name + ".png";
		image.d_index = nvgCreateImage(ctx(), path.c_str(), tile ? (NVG_IMAGE_REPEATX | NVG_IMAGE_REPEATY) : 0);
		nvgImageSize(ctx(), image.d_index, &image.d_width, &image.d_height);
#ifdef NANO_ATLAS
		ImageRect& rect = atlas().findSpriteRect(image.d_name + ".png");
		image.d_left = rect.x;
		image.d_top = rect.y;
#endif
	}

	void NanoRenderer::clipRect(BoxFloat& rect)
	{
		nvgScissor(ctx(), rect.x(), rect.y(), rect.w(), rect.h());
	}

	void NanoRenderer::unclipRect()
	{
		nvgResetScissor(ctx());
	}

	void NanoRenderer::clipFrame(BoxFloat& rect, BoxFloat& corners)
	{
		nvgGlobalCompositeOperation(ctx(), NVG_SOURCE_IN);

		pathRect(rect, corners, 0.f);

		nvgFillColor(ctx(), nvgColour(Colour::Black));
		nvgFill(ctx());
	}

	void NanoRenderer::clipShape()
	{
		nvgGlobalCompositeOperation(ctx(), NVG_SOURCE_IN);
	}

	void NanoRenderer::unclipShape()
	{
		nvgGlobalCompositeOperation(ctx(), NVG_SOURCE_OVER);
	}

	void NanoRenderer::pathBezier(float x1, float y1, float c1x, float c1y, float c2x, float c2y, float x2, float y2)
	{
		nvgBeginPath(ctx());
		nvgMoveTo(ctx(), x1, y1);
		nvgBezierTo(ctx(), c1x, c1y, c2x, c2y, x2, y2);
	}

	void NanoRenderer::pathRect(BoxFloat& rect, BoxFloat& corners, float border)
	{
		float halfborder = border * 0.5f;

		// Path
		if(corners.null())
			nvgRect(ctx(), rect.x() + halfborder, rect.y() + halfborder, rect.w() - border, rect.h() - border);
		else
			nvgRoundedBox(ctx(), rect.x() + halfborder, rect.y() + halfborder, rect.w() - border, rect.h() - border, corners.xx(), corners.xy(), corners.yx(), corners.yy());
	}

	void NanoRenderer::drawShadow(BoxFloat& rect, BoxFloat& corners, Shadow& shadow)
	{
		NVGpaint shadowPaint = nvgBoxGradient(ctx(), rect.x() + shadow.d_xpos - shadow.d_spread, rect.y() + shadow.d_ypos - shadow.d_spread, rect.w() + shadow.d_spread * 2.f, rect.h() + shadow.d_spread * 2.f, corners.xy() + shadow.d_spread, shadow.d_blur, nvgRGBA(0, 0, 0, 128), nvgRGBA(0, 0, 0, 0));
		nvgBeginPath(ctx());
		nvgRect(ctx(), rect.x() + shadow.d_xpos - shadow.d_radius, rect.y() + shadow.d_ypos - shadow.d_radius, rect.w() + shadow.d_radius * 2.f, rect.h() + shadow.d_radius * 2.f);
		if(corners.null())
			nvgRect(ctx(), rect.x(), rect.y(), rect.w(), rect.h());
		else
			nvgRoundedBox(ctx(), rect.x(), rect.y(), rect.w(), rect.h(), corners.xx(), corners.xy(), corners.yx(), corners.yy());
		nvgPathWinding(ctx(), NVG_HOLE);
		nvgFillPaint(ctx(), shadowPaint);
		nvgFill(ctx());
	}

	void NanoRenderer::drawRect(BoxFloat& rect, BoxFloat& corners, InkStyle& skin)
	{
		float border = skin.borderWidth().x0();

		nvgBeginPath(ctx());
		this->pathRect(rect, corners, border);

		// Fill
		if(skin.backgroundColour().a() > 0.f)
			this->fill(skin, rect);

		// Border
		if(border > 0.f)
			this->stroke(skin);
	}

	void NanoRenderer::drawRectClipped(BoxFloat& rect, BoxFloat& corners, InkStyle& skin, BoxFloat& clipRect, BoxFloat& clipCorners)
	{
		float border = skin.borderWidth().x0();

		nvgBeginPath(ctx());
		this->clipFrame(clipRect, clipCorners);
		this->pathRect(rect, corners, border);

		// Fill
		if(skin.backgroundColour().a() > 0.f)
			this->fill(skin, rect);

		// Border
		if(border > 0.f)
			this->stroke(skin);

		//this->unclipShape();
	}

	void NanoRenderer::fill(InkStyle& skin, BoxFloat& rect)
	{
		if(skin.topdownGradient().null())
		{
			nvgFillColor(ctx(), nvgColour(skin.m_backgroundColour));
		}
		else
		{
			NVGcolor first = nvgOffsetColour(skin.backgroundColour(), skin.topdownGradient().x());
			NVGcolor second = nvgOffsetColour(skin.backgroundColour(), skin.topdownGradient().y());
			nvgFillPaint(ctx(), (rect.h() > rect.w()) ?
				nvgLinearGradient(ctx(), rect.x(), rect.y(), rect.x() + rect.w(), rect.y(), first, second) :
				nvgLinearGradient(ctx(), rect.x(), rect.y(), rect.x(), rect.y() + rect.h(), first, second));
		}
		nvgFill(ctx());
	}

	void NanoRenderer::stroke(InkStyle& skin)
	{
		float border = skin.borderWidth().x0();

		nvgStrokeWidth(ctx(), border);
		nvgStrokeColor(ctx(), nvgColour(skin.borderColour()));
		nvgStroke(ctx());
	}

	void NanoRenderer::drawImage(int image, BoxFloat& rect, BoxFloat& imageRect)
	{
		NVGpaint imgPaint = nvgImagePattern(ctx(), imageRect.x(), imageRect.y(), imageRect.w(), imageRect.h(), 0.0f / 180.0f*NVG_PI, image, 1.f);
		nvgBeginPath(ctx());
		nvgRect(ctx(), rect.x(), rect.y(), rect.w(), rect.h());
		nvgFillPaint(ctx(), imgPaint);
		nvgFill(ctx());
	}

	void NanoRenderer::drawImage(const Image& image, BoxFloat& rect)
	{
#ifdef NANO_ATLAS
		BoxFloat imageRect(rect.x() - image.d_left, rect.y() - image.d_top, atlas().width(), atlas().height());
		this->drawImage(atlas().image(), rect, imageRect);
#else
		this->drawImage(image.d_index, rect, rect);
#endif
	}

	void NanoRenderer::drawImageStretch(const Image& image, BoxFloat& rect, float xstretch, float ystretch)
	{
#ifdef NANO_ATLAS
		BoxFloat imageRect(rect.x() - image.d_left * xstretch, rect.y() - image.d_top * ystretch, atlas().width() * xstretch, atlas().height() * ystretch);
		this->drawImage(atlas().image(), rect, imageRect);
#else
		this->drawImage(image.d_index, rect, left, top, image.d_width * xstretch, image.d_height * ystretch);
#endif
	}


	void NanoRenderer::setupText(InkStyle& skin)
	{
		nvgFontSize(ctx(), skin.textSize());
		nvgFontFace(ctx(), skin.textFont().c_str());
		nvgTextAlign(ctx(), NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
	}

	void NanoRenderer::fillText(const string& text, BoxFloat& paddedRect, InkStyle& skin, TextRow& row)
	{
		this->setupText(skin);

		float lineh = 0.f;
		nvgTextMetrics(ctx(), NULL, NULL, &lineh);

		row.start = text.c_str();
		row.end = text.c_str() + text.size();
		row.rect.assign(paddedRect.x(), paddedRect.y(), this->textSize(text, DIM_X, skin), lineh);

		this->breakTextLine(paddedRect, row);
	}

	void NanoRenderer::breakText(const string& text, BoxFloat& paddedRect, InkStyle& skin, std::vector<TextRow>& textRows)
	{
		float x = paddedRect.x();
		float y = paddedRect.y();

		this->setupText(skin);

		NVGalign halign = NVG_ALIGN_LEFT;
		if(skin.align()[DIM_X] == CENTER)
			halign = NVG_ALIGN_CENTER;
		else if(skin.align()[DIM_X] == RIGHT)
			halign = NVG_ALIGN_RIGHT;

		const char* first = text.c_str();
		const char* end = first + text.size();
		int nrows = 0;

		float lineh = 0.f;
		nvgTextMetrics(ctx(), NULL, NULL, &lineh);

		textRows.clear();

		NVGtextRow nvgTextRow;

		while((nrows = nvgTextBreakLines(ctx(), first, end, paddedRect.w(), &nvgTextRow, 1)))
		{
			if(halign & NVG_ALIGN_LEFT)
				x = paddedRect.x();
			else if(halign & NVG_ALIGN_CENTER)
				x = paddedRect.x() + paddedRect.w()*0.5f - nvgTextRow.width*0.5f;
			else if(halign & NVG_ALIGN_RIGHT)
				x = paddedRect.x() + paddedRect.w() - nvgTextRow.width;

			first = nvgTextRow.next;

			textRows.resize(textRows.size() + 1);
			
			textRows.back().start = nvgTextRow.start;
			textRows.back().end = nvgTextRow.end;
			textRows.back().rect.assign(paddedRect.x(), paddedRect.y() + y, nvgTextRow.maxx, lineh);

			this->breakTextLine(paddedRect, textRows.back());

			y += lineh;
		}
	}

	void NanoRenderer::breakTextLine(BoxFloat& paddedRect, TextRow& textRow)
	{
		size_t numGlyphs = textRow.end - textRow.start;
		std::vector<NVGglyphPosition> positions;
		positions.resize(numGlyphs);
		textRow.glyphs.resize(numGlyphs);

		nvgTextGlyphPositions(ctx(), paddedRect.x(), paddedRect.y(), textRow.start, textRow.end, &positions.front(), positions.size());

		for(size_t i = 0; i < positions.size(); ++i)
		{
			NVGglyphPosition& glyph = positions[i];
			TextGlyph& out = textRow.glyphs[i];
			out.position = textRow.start + i;
			out.rect.assign(paddedRect.x() + glyph.minx, textRow.rect.y(), glyph.maxx - glyph.minx, textRow.rect.h());
		}
	}

	void NanoRenderer::drawText(float x, float y, const char* start, const char* end, InkStyle& skin)
	{
		this->setupText(skin);

		nvgFillColor(ctx(), nvgColour(skin.m_textColour));
		nvgText(ctx(), x, y, start, end);
	}

#ifdef KIUI_DRAW_CACHE
	void NanoRenderer::beginUpdate(void* cache)
	{
		nvgResetDisplayList((NVGdisplayList*) cache);
		nvgBindDisplayList(ctx(), (NVGdisplayList*) cache);
	}

	void NanoRenderer::endUpdate(void* cache)
	{
		nvgBindDisplayList(ctx(), nullptr);
	}
#else
	void NanoRenderer::beginUpdate(float x, float y)
	{
		nvgSave(ctx());
		nvgTranslate(ctx(), x, y);
	}

	void NanoRenderer::endUpdate()
	{
		nvgRestore(ctx());
	}
#endif

	float NanoRenderer::textSize(const string& text, Dimension dim, InkStyle& skin)
	{
		float bounds[4];
		float height;

		this->setupText(skin);
		nvgTextBounds(ctx(), 0.f, 0.f, text.c_str(), nullptr, bounds);
		nvgTextMetrics(ctx(), nullptr, nullptr, &height);

		return dim == DIM_X ? bounds[2] - bounds[0] : height;
	}

}
