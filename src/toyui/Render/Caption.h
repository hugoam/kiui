//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_CAPTION_H
#define TOY_CAPTION_H

/* toy Front */
#include <toyobj/Indexer.h>
#include <toyobj/Util/NonCopy.h>
#include <toyui/Forward.h>
#include <toyui/Style/Dim.h>

namespace toy
{
	struct TextGlyph
	{
		const char* position;
		BoxFloat rect;
	};

	struct TextRow
	{
		const char* start;
		const char* end;
		size_t startIndex;
		size_t endIndex;
		BoxFloat rect;
		BoxFloat caret;
		BoxFloat selected;

		std::vector<TextGlyph> glyphs;
	};

	class TOY_UI_EXPORT Caption
	{
	public:
		Caption(DrawFrame& frame);
		Caption(const Caption&) = default;

		std::vector<TextRow>& textRows() { return m_textRows; }

		int caret() { return m_caret; }
		int selectStart() { return m_selectStart; }
		int selectEnd() { return m_selectEnd; }

		void selectStart(int value) { m_selectStart = value; }
		void selectEnd(int value) { m_selectEnd = value; }
		void caret(int value) { m_caret = value; }

		float textSize(Dimension dim);

		void updateTextRows(Renderer& target, const DimFloat& space);
		void updateSelection();

		TextRow& textRow(size_t index);

		size_t caretIndex(float x, float y);
		void caretCoords(float& x, float& y);

	protected:
		DrawFrame& m_frame;

		int m_caret;
		int m_selectStart;
		int m_selectEnd;

		std::vector<TextRow> m_textRows;
	};
}

#endif
