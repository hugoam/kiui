//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Frame/Caption.h>

#include <toyui/Frame/Layer.h>

#include <toyui/Render/Renderer.h>

namespace toy
{
	Renderer* Caption::s_renderer = nullptr;

	Caption::Caption(Frame& frame)
		: d_frame(frame)
		, m_text()
		, m_textLines(1)
		, m_caret(-1)
		, m_selectStart(-1)
		, m_selectEnd(-1)
	{}

	void Caption::setText(const string& text)
	{
		m_text = text;
		d_frame.markDirty(DIRTY_LAYOUT);
	}

	void Caption::setTextLines(size_t lines)
	{
		m_textLines = lines;
		d_frame.markDirty(DIRTY_LAYOUT);
	}

	DimFloat Caption::updateTextSize()
	{
		//DimFloat paddedSize = d_frame.d_size - d_frame.d_inkstyle->m_padding.val - d_frame.d_inkstyle->m_padding.val;
		float paddedWidth = floor(d_frame.d_size.x - d_frame.d_inkstyle->m_padding.val.x0 - d_frame.d_inkstyle->m_padding.val.x1);
		float paddedHeight = floor(d_frame.d_size.y - d_frame.d_inkstyle->m_padding.val.y0 - d_frame.d_inkstyle->m_padding.val.y1);

		DimFloat paddedSize(paddedWidth, paddedHeight);

		this->updateTextRows(*s_renderer, paddedSize);

		return this->contentSize();
	}

	float Caption::height()
	{
		if(m_text.empty())
			return s_renderer->textLineHeight(*d_frame.d_inkstyle) * m_textLines;
		else if(!m_textRows.empty())
			return m_textRows.back().rect.y + m_textRows.back().rect.h;
		else
			return 0.f;
	}

	float Caption::width()
	{
		float result = 0.f;
		for(TextRow& row : m_textRows)
			result = std::max(result, row.rect.w);
		return result;
	}

	void Caption::updateTextRows(Renderer& target, const DimFloat& space)
	{
		if(!m_text.empty())
			target.breakText(m_text, space, *d_frame.d_inkstyle, m_textRows);
		else
			m_textRows.clear();

		this->updateSelection();
	}

	void Caption::select(int caret, int start, int end)
	{
		m_caret = caret;
		m_selectStart = start;
		m_selectEnd = end;

		this->updateSelection();
		d_frame.markDirty(DIRTY_REDRAW);
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
				DimFloat pos;
				this->caretCoords(pos);
				row.caret.assign(pos.x, pos.y, 2.f, row.rect.h);
			}

			if(m_selectStart != m_selectEnd && indexEnd > m_selectStart && indexStart < m_selectEnd)
			{
				int lineSelectStart = std::max(indexStart, m_selectStart);
				int lineSelectEnd = std::min(indexEnd, m_selectEnd);

				if(row.glyphs.empty())
				{
					row.selected.assign(row.rect.x, row.rect.y, 5.f, row.rect.h);
					continue;
				}

				TextGlyph& startGlyph = row.glyphs[lineSelectStart - indexStart];
				TextGlyph& endGlyph = row.glyphs[lineSelectEnd - indexStart];

				row.selected.assign(startGlyph.rect.x, row.rect.y, endGlyph.rect.x + endGlyph.rect.w - startGlyph.rect.x, row.rect.h);
			}
		}
	}

	size_t Caption::caretIndex(const DimFloat& pos)
	{
		const char* start = m_text.c_str();
		const char* end = start + m_text.size();

		for(TextRow& row : m_textRows)
			if(pos.y >= row.rect.y && pos.y < row.rect.y + row.rect.h)
			{
				for(TextGlyph& glyph : row.glyphs)
					if(pos.x >= glyph.rect.x && pos.x < glyph.rect.x + glyph.rect.w)
						return glyph.position - start;

				return row.end - start;
			}

		return end - start;
	}

	void Caption::caretCoords(DimFloat& pos)
	{
		TextRow& row = textRow(m_caret);
				
		if(m_caret != row.end - m_text.c_str())
		{
			size_t offset = row.start - m_text.c_str();
			TextGlyph& glyph = row.glyphs[m_caret - offset];
			pos.x = glyph.rect.x;
			pos.y = glyph.rect.y;
		}
		else
		{
			pos.x = row.rect.x + row.rect.w;
			pos.y = row.rect.y;
		}
	}

	TextRow& Caption::textRow(size_t index)
	{
		for(TextRow& row : m_textRows)
			if(index <= size_t(row.end - m_text.c_str()))
				return row;

		return m_textRows.back();
	}
}
