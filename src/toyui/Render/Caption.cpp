//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Render/Caption.h>

#include <toyui/Widget/Widget.h>
#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Layer.h>

#include <toyui/UiWindow.h>
#include <toyui/Widget/RootSheet.h>

namespace toy
{
	Caption::Caption(DrawFrame& frame)
		: m_frame(frame)
		, m_caret(-1)
		, m_selectStart(-1)
		, m_selectEnd(-1)
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

				if(row.glyphs.empty())
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
			if(index <= size_t(row.end - start))
				return row;

		return m_textRows.back();
	}
}
