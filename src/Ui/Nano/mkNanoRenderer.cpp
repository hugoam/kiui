//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Nano/mkNanoRenderer.h>

#include <Object/Util/mkColour.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>
#include <Ui/Widget/mkWidget.h>

#include <Ui/Nano/mkNanoWindow.h>

#include <Ui/Nano/nanovg/nanovg.h>

#include <cmath>

namespace mk
{

	inline float clamp(float v, float mn, float mx)
	{
		return (v > mx) ? mx : (v < mn) ? mn : v;
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

	void NanoRenderer::initImage(Image& image, bool tile)
	{
		string path = m_window.resourcePath() + "interface/uisprites/" + image.d_name + ".png";
		image.d_index = nvgCreateImage(ctx(), path.c_str(), tile ? (NVG_IMAGE_REPEATX | NVG_IMAGE_REPEATY) : 0);
		nvgImageSize(ctx(), image.d_index, &image.d_width, &image.d_height);

		ImageRect* rect = atlas().findSpriteRect(image.d_name + ".png");
		if(rect)
		{
			image.d_left = rect->x;
			image.d_top = rect->y;
			image.d_atlas = atlas().image();
		}
	}

	void NanoRenderer::clipRect(const BoxFloat& rect)
	{
		nvgIntersectScissor(ctx(), rect.x(), rect.y(), rect.w(), rect.h());
	}

	void NanoRenderer::unclipRect()
	{
		nvgResetScissor(ctx());
	}

	void NanoRenderer::clipFrame(const BoxFloat& rect, const BoxFloat& corners)
	{
		nvgIntersectRoundedScissor(ctx(), rect.x(), rect.y(), rect.w(), rect.h(), corners.v0(), corners.v1(), corners.v2(), corners.v3());
	}

	void NanoRenderer::unclipFrame()
	{
		nvgResetScissor(ctx());
	}

	void NanoRenderer::pathBezier(float x1, float y1, float c1x, float c1y, float c2x, float c2y, float x2, float y2)
	{
		nvgBeginPath(ctx());
		nvgMoveTo(ctx(), x1, y1);
		nvgBezierTo(ctx(), c1x, c1y, c2x, c2y, x2, y2);
	}

	void NanoRenderer::pathRect(const BoxFloat& rect, const BoxFloat& corners, float border)
	{
		float halfborder = border * 0.5f;

		// Path
		if(corners.null())
			nvgRect(ctx(), rect.x() + halfborder, rect.y() + halfborder, rect.w() - border, rect.h() - border);
		else
			nvgRoundedRectVarying(ctx(), rect.x() + halfborder, rect.y() + halfborder, rect.w() - border, rect.h() - border, corners.xx(), corners.xy(), corners.yx(), corners.yy());
	}

	void NanoRenderer::drawShadow(const BoxFloat& rect, const BoxFloat& corners, const Shadow& shadow)
	{
		NVGpaint shadowPaint = nvgBoxGradient(ctx(), rect.x() + shadow.d_xpos - shadow.d_spread, rect.y() + shadow.d_ypos - shadow.d_spread, rect.w() + shadow.d_spread * 2.f, rect.h() + shadow.d_spread * 2.f, corners.xy() + shadow.d_spread, shadow.d_blur, nvgRGBA(0, 0, 0, 128), nvgRGBA(0, 0, 0, 0));
		nvgBeginPath(ctx());
		nvgRect(ctx(), rect.x() + shadow.d_xpos - shadow.d_radius, rect.y() + shadow.d_ypos - shadow.d_radius, rect.w() + shadow.d_radius * 2.f, rect.h() + shadow.d_radius * 2.f);
		if(corners.null())
			nvgRect(ctx(), rect.x(), rect.y(), rect.w(), rect.h());
		else
			nvgRoundedRectVarying(ctx(), rect.x(), rect.y(), rect.w(), rect.h(), corners.xx(), corners.xy(), corners.yx(), corners.yy());
		nvgPathWinding(ctx(), NVG_HOLE);
		nvgFillPaint(ctx(), shadowPaint);
		nvgFill(ctx());
	}

	void NanoRenderer::drawRect(const BoxFloat& rect, const BoxFloat& corners, InkStyle& skin)
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

	void NanoRenderer::debugRect(const BoxFloat& rect, const Colour& colour)
	{
		static InkStyle debugStyle("debugRectStyle");
		debugStyle.m_borderWidth = 1.f;
		debugStyle.m_borderColour = colour;

		this->drawRect(rect, BoxFloat(), debugStyle);
	}

	void NanoRenderer::fill(InkStyle& skin, const BoxFloat& rect)
	{
		if(skin.linearGradient().null())
		{
			nvgFillColor(ctx(), nvgColour(skin.m_backgroundColour));
		}
		else
		{
			NVGcolor first = nvgOffsetColour(skin.backgroundColour(), skin.linearGradient().x());
			NVGcolor second = nvgOffsetColour(skin.backgroundColour(), skin.linearGradient().y());
			if(skin.linearGradientDim() == DIM_X)
				nvgFillPaint(ctx(), nvgLinearGradient(ctx(), rect.x(), rect.y(), rect.x() + rect.w(), rect.y(), first, second));
			else
				nvgFillPaint(ctx(), nvgLinearGradient(ctx(), rect.x(), rect.y(), rect.x(), rect.y() + rect.h(), first, second));
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

	void NanoRenderer::drawImage(int image, const BoxFloat& rect, const BoxFloat& imageRect)
	{
		NVGpaint imgPaint = nvgImagePattern(ctx(), imageRect.x(), imageRect.y(), imageRect.w(), imageRect.h(), 0.0f / 180.0f*NVG_PI, image, 1.f);
		nvgBeginPath(ctx());
		nvgRect(ctx(), rect.x(), rect.y(), rect.w(), rect.h());
		nvgFillPaint(ctx(), imgPaint);
		nvgFill(ctx());
	}

	void NanoRenderer::drawImage(const Image& image, const BoxFloat& rect)
	{
		if(image.d_atlas)
		{
			BoxFloat imageRect(rect.x() - image.d_left, rect.y() - image.d_top, atlas().width(), atlas().height());
			this->drawImage(image.d_atlas, rect, imageRect);
		}
		else
		{
			this->drawImage(image.d_index, rect, rect);
		}
	}

	void NanoRenderer::drawImageStretch(const Image& image, const BoxFloat& rect, float xstretch, float ystretch)
	{
		if(image.d_atlas)
		{
			BoxFloat imageRect(rect.x() - image.d_left * xstretch, rect.y() - image.d_top * ystretch, atlas().width() * xstretch, atlas().height() * ystretch);
			this->drawImage(atlas().image(), rect, imageRect);
		}
		else
		{
			BoxFloat imageRect(rect.x(), rect.y(), image.d_width * xstretch, image.d_height * ystretch);
			this->drawImage(image.d_index, rect, imageRect);
		}
	}


	void NanoRenderer::setupText(InkStyle& skin)
	{
		m_alignH = NVG_ALIGN_LEFT;
		if(skin.align()[DIM_X] == CENTER)
			m_alignH = NVG_ALIGN_CENTER;
		else if(skin.align()[DIM_X] == RIGHT)
			m_alignH = NVG_ALIGN_RIGHT;

		nvgFontSize(ctx(), skin.textSize());
		nvgFontFace(ctx(), skin.textFont().c_str());
		nvgTextAlign(ctx(), m_alignH | NVG_ALIGN_TOP);

		m_lineHeight = 0.f;
		nvgTextMetrics(ctx(), nullptr, nullptr, &m_lineHeight);
	}

	void NanoRenderer::fillText(const string& text, const BoxFloat& rect, InkStyle& skin, TextRow& row)
	{
		this->setupText(skin);

		row.start = text.c_str();
		row.end = text.c_str() + text.size();
		row.rect.assign(rect.x(), rect.y(), this->textSize(text, DIM_X, skin), m_lineHeight);

		this->breakTextLine(rect, row);
	}


	void NanoRenderer::breakTextWidth(const char* first, const char* end, const BoxFloat& rect, InkStyle& skin, TextRow& row)
	{
		UNUSED(skin);

		NVGtextRow nvgTextRow;
		nvgTextBreakLines(ctx(), first, end, rect.w(), &nvgTextRow, 1);

		row.start = nvgTextRow.start;
		row.end = nvgTextRow.end;
		row.rect.assign(rect.x(), rect.y(), nvgTextRow.width, m_lineHeight);

		if(row.start != row.end)
			this->breakTextLine(rect, row);
	}

	void NanoRenderer::breakTextReturns(const char* first, const char* end, const BoxFloat& rect, InkStyle& skin, TextRow& row)
	{
		const char* iter = first;
		
		do
			++iter;
		while(*iter != '\n' && iter < end);

		row.start = first;
		row.end = iter;
		row.rect.assign(rect.x(), rect.y(), this->textSize(string(first, iter - first), DIM_X, skin), m_lineHeight);

		this->breakTextLine(rect, row);
	}

	void NanoRenderer::breakText(const string& text, const DimFloat& space, InkStyle& skin, std::vector<TextRow>& textRows)
	{
		this->setupText(skin);

		const char* first = text.c_str();
		const char* end = first + text.size();

		textRows.clear();
	
		if(!skin.textBreak())
		{
			textRows.resize(1);

			BoxFloat rect(0.f, 0.f, space.x(), m_lineHeight);
			this->fillText(text, rect, skin, textRows[0]);
			return;
		}

		while(first < end)
		{
			size_t index = textRows.size();
			textRows.resize(index + 1);
			TextRow& row = textRows.back();

			BoxFloat rect(0.f, index * m_lineHeight, space.x(), 0.f);
			if(skin.textWrap())
				this->breakTextWidth(first, end, rect, skin, row);
			else
				this->breakTextReturns(first, end, rect, skin, row);

			row.startIndex = row.start - text.c_str();
			row.endIndex = row.end - text.c_str();
			first = row.end + 1;
		}
	}

	void NanoRenderer::breakTextLine(const BoxFloat& rect, TextRow& textRow)
	{
		size_t numGlyphs = textRow.end - textRow.start;
		std::vector<NVGglyphPosition> positions;
		positions.resize(numGlyphs);
		textRow.glyphs.resize(numGlyphs);

		nvgTextGlyphPositions(ctx(), rect.x(), rect.y(), textRow.start, textRow.end, &positions.front(), positions.size());

		for(size_t i = 0; i < positions.size(); ++i)
		{
			NVGglyphPosition& glyph = positions[i];
			TextGlyph& out = textRow.glyphs[i];
			out.position = textRow.start + i;
			out.rect.assign(glyph.minx, textRow.rect.y(), glyph.maxx - glyph.minx, textRow.rect.h());
		}
	}

	void NanoRenderer::drawText(float x, float y, const char* start, const char* end, InkStyle& skin)
	{
		this->setupText(skin);

		nvgFillColor(ctx(), nvgColour(skin.m_textColour));
		nvgText(ctx(), x, y, start, end);
	}

#ifdef KIUI_DRAW_CACHE
	void NanoRenderer::layerCache(Layer& layer, void*& cache)
	{
		if(m_layers.find(&layer) == m_layers.end())
			m_layers[&layer] = nvgCreateDisplayList(-1);

		cache = m_layers[&layer];
	}

	void NanoRenderer::drawLayer(void* layerCache, float x, float y, float scale)
	{
		nvgSave(ctx());
		nvgTranslate(ctx(), x, y);
		nvgScale(ctx(), scale, scale);
		nvgDrawDisplayList(ctx(), (NVGdisplayList*)layerCache);
		nvgRestore(ctx());
	}

	void NanoRenderer::beginLayer(void* layerCache, float x, float y, float scale)
	{
		nvgResetDisplayList((NVGdisplayList*)layerCache);
		nvgBindDisplayList(ctx(), (NVGdisplayList*)layerCache);
		nvgSave(ctx());
		nvgTranslate(ctx(), x, y);
		//nvgResetTransform(ctx());
		nvgScale(ctx(), scale, scale);
		//nvgResetScissor(ctx());
		// we don't want to reset the scissor here but keep the previous scissor
		// however resetTransform doesn't modify the scissor accordingly so we need to do that
	}

	void NanoRenderer::endLayer()
	{

	}

	void NanoRenderer::beginUpdate(void* layerCache, float x, float y, float scale)
	{
		nvgBindDisplayList(ctx(), (NVGdisplayList*)layerCache);
		nvgSave(ctx());
		nvgTranslate(ctx(), x, y);
		nvgScale(ctx(), scale, scale);
	}

	void NanoRenderer::endUpdate()
	{
		nvgRestore(ctx());
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

	float NanoRenderer::textLineHeight(InkStyle& skin)
	{
		this->setupText(skin);
		return m_lineHeight;
	}

	float NanoRenderer::textSize(const string& text, Dimension dim, InkStyle& skin)
	{
		this->setupText(skin);

		float bounds[4];
		nvgTextBounds(ctx(), 0.f, 0.f, text.c_str(), nullptr, bounds);

		return dim == DIM_X ? bounds[2] - bounds[0] : m_lineHeight;
	}
}
