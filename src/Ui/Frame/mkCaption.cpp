//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Frame/mkCaption.h>

#include <Ui/Widget/mkWidget.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkLayer.h>

#include <Ui/mkUiWindow.h>
#include <Ui/Widget/mkRootSheet.h>

using namespace std::placeholders;

namespace mk
{
	Caption::Caption(Frame& drawFrame)
		: RenderFrame(drawFrame)
		, m_selectFirst(0)
		, m_selectSecond(0)
	{}

	Caption::~Caption()
	{}

	void Caption::redraw(Renderer& target, BoxFloat& rect, BoxFloat& paddedRect, BoxFloat& contentRect)
	{
		static InkStyle textSelectionStyle("TextSelection");
		textSelectionStyle.m_backgroundColour = Colour(0/255.f, 55/255.f, 255/255.f, 124/255.f);

		if(paddedRect.w() <= 0.f || paddedRect.h() <= 0.f)
			return;

		if(m_frame.dirty() > Frame::DIRTY_FRAME)
			this->updateTextRows(target, paddedRect);

		target.clipRect(rect);

		if(m_drawFrame.image())
			target.drawImage(*m_drawFrame.image(), contentRect);

		if(!m_drawFrame.text().empty())
			for(TextRow& row : m_textRows)
			{
				if(!row.selected.null())
					target.drawRect(row.selected, BoxFloat(), textSelectionStyle);

				target.drawText(row.rect.x(), row.rect.y(), row.start, row.end, m_frame.inkstyle());
			}
	}

	void Caption::updateTextRows(Renderer& target, BoxFloat& paddedRect)
	{
		if(!m_drawFrame.text().empty() && m_frame.inkstyle().textWrap())
		{
			target.breakText(m_drawFrame.text(), paddedRect, m_frame.inkstyle(), m_textRows);
		}
		else if(!m_drawFrame.text().empty())
		{
			m_textRows.resize(1);
			target.fillText(m_drawFrame.text(), paddedRect, m_frame.inkstyle(), m_textRows[0]);
		}
		else
		{
			m_textRows.clear();
		}
	}

	void Caption::updateSelection()
	{
		if(m_textRows.empty())
			return;

		const char* start = m_textRows[0].start;

		for(TextRow& row : m_textRows)
		{
			row.selected.clear();

			if(selectStart() != selectEnd())
			{
				size_t indexStart = row.start - start;
				size_t indexEnd = row.end - start - 1;

				if(indexEnd > selectStart() && indexStart < selectEnd())
				{
					size_t lineSelectStart = std::max(indexStart, selectStart());
					size_t lineSelectEnd = std::min(indexEnd, selectEnd());

					TextGlyph& startGlyph = row.glyphs[lineSelectStart - indexStart];
					TextGlyph& endGlyph = row.glyphs[lineSelectEnd - indexStart];

					row.selected.assign(startGlyph.rect.x(), row.rect.y(), endGlyph.rect.x() + endGlyph.rect.w() - startGlyph.rect.x(), row.rect.h());
				}
			}
		}
	}

	size_t Caption::caretIndex(float posX, float posY)
	{
		const char* start = m_drawFrame.text().c_str();
		const char* end = start + m_drawFrame.text().size();

		for(TextRow& row : m_textRows)
			if(posY > row.rect.y() && posY < row.rect.y() + row.rect.h())
				for(TextGlyph& glyph : row.glyphs)
					if(posX > glyph.rect.x() && posX <= glyph.rect.x() + glyph.rect.w())
						return glyph.position - start;

		return end - start;
	}

	void Caption::caretCoords(size_t index, float& caretX, float& caretY, float& caretHeight)
	{
		const char* start = m_drawFrame.text().c_str();

		for(TextRow& row : m_textRows)
			if(index <= row.end - start)
				for(TextGlyph& glyph : row.glyphs)
					if(index == glyph.position - start)
					{
						caretX = glyph.rect.x();
						caretY = glyph.rect.y();
						return;
					}

		caretX = m_frame.inkstyle().padding().x0();
		caretY = m_frame.inkstyle().padding().x1();
		return;
	}
}
