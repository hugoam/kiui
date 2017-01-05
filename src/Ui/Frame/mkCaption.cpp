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

#include <iostream>

using namespace std::placeholders;

namespace mk
{
	Caption::Caption(DrawFrame& frame)
		: m_frame(frame)
		, m_caret(-1)
		, m_selectStart(-1)
		, m_selectEnd(-1)
	{}

	Caption::~Caption()
	{}

	float Caption::textSize(Dimension dim)
	{
		float result = 0.f;

		if(dim == DIM_X)
			for(TextRow& row : m_textRows)
				result = std::max(result, row.rect.w());
		else if(dim == DIM_Y)
			result = m_textRows.back().rect.y() + m_textRows.back().rect.h();

		return result;
	}

	void Caption::redraw(Renderer& target, const BoxFloat& rect, const BoxFloat& paddedRect, const BoxFloat& contentRect)
	{
		static InkStyle textSelectionStyle("TextSelection");
		textSelectionStyle.m_backgroundColour = Colour(0/255.f, 55/255.f, 255/255.f, 124/255.f);

		static InkStyle caretStyle("Caret");
		caretStyle.m_backgroundColour = Colour::White;

		if(paddedRect.w() <= 0.f || paddedRect.h() <= 0.f)
			return;

		if(!m_frame.image() && m_frame.text().empty())
			return;

		target.clipRect(rect);

		if(m_frame.image())
			target.drawImage(*m_frame.image(), contentRect);

		if(!m_frame.text().empty())
			for(TextRow& row : m_textRows)
			{
				if(!row.selected.null())
					target.drawRect(BoxFloat(paddedRect.x() + row.selected.x(), paddedRect.y() + row.selected.y(), row.selected.w(), row.selected.h()), BoxFloat(), textSelectionStyle);

				target.drawText(paddedRect.x() + row.rect.x(), paddedRect.y() + row.rect.y(), row.start, row.end, m_frame.inkstyle());

				if(!row.caret.null())
					target.drawRect(BoxFloat(paddedRect.x() + row.caret.x(), paddedRect.y() + row.caret.y(), row.caret.w(), row.caret.h()), BoxFloat(), caretStyle);
			}
	}

	void Caption::updateTextRows(Renderer& target, const DimFloat& space)
	{
		std::vector<TextRow> textRows = m_textRows;

		if(!m_frame.text().empty())
			target.breakText(m_frame.text(), space, m_frame.inkstyle(), m_textRows);
		else
			m_textRows.clear();

		this->updateSelection();
	}

	void Caption::updateSelection()
	{
		if(m_textRows.empty())
			return;

		const char* start = m_textRows[0].start;

		for(TextRow& row : m_textRows)
		{
			row.selected.clear();
			row.caret.clear();

			int indexStart = row.start - start;
			int indexEnd = row.end - start - 1;

			if(m_caret >= indexStart && m_caret <= indexEnd + 1)
			{
				float x, y;
				this->caretCoords(x, y);
				row.caret.assign(x, y, 2.f, row.rect.h());
			}

			if(m_selectStart != m_selectEnd && indexEnd > m_selectStart && indexStart < m_selectEnd)
			{
				int lineSelectStart = std::max(indexStart, m_selectStart);
				int lineSelectEnd = std::min(indexEnd, m_selectEnd);

				if(row.glyphs.size() == 0)
				{
					row.selected.assign(row.rect.x(), row.rect.y(), 5.f, row.rect.h());
					continue;
				}

				TextGlyph& startGlyph = row.glyphs[lineSelectStart - indexStart];
				TextGlyph& endGlyph = row.glyphs[lineSelectEnd - indexStart];

				row.selected.assign(startGlyph.rect.x(), row.rect.y(), endGlyph.rect.x() + endGlyph.rect.w() - startGlyph.rect.x(), row.rect.h());
			}
		}
	}

	size_t Caption::caretIndex(float posX, float posY)
	{
		const char* start = m_frame.text().c_str();
		const char* end = start + m_frame.text().size();

		for(TextRow& row : m_textRows)
			if(posY >= row.rect.y() && posY < row.rect.y() + row.rect.h())
			{
				for(TextGlyph& glyph : row.glyphs)
					if(posX >= glyph.rect.x() && posX < glyph.rect.x() + glyph.rect.w())
						return glyph.position - start;

				return row.end - start;
			}

		return end - start;
	}

	void Caption::caretCoords(float& x, float& y)
	{
		const char* start = m_frame.text().c_str();

		TextRow& row = textRow(m_caret);
				
		if(m_caret != row.end - start)
		{
			size_t offset = row.start - start;
			TextGlyph& glyph = row.glyphs[m_caret - offset];
			x = glyph.rect.x();
			y = glyph.rect.y();
		}
		else
		{
			x = row.rect.x() + row.rect.w();
			y = row.rect.y();
		}
	}

	TextRow& Caption::textRow(size_t index)
	{
		const char* start = m_frame.text().c_str();

		for(TextRow& row : m_textRows)
			if(index <= row.end - start)
				return row;

		return m_textRows.back();
	}
}
