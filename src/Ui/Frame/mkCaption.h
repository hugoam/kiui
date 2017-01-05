//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_CAPTION_H
#define MK_CAPTION_H

/* mk Front */
#include <Object/mkIndexer.h>
#include <Object/Util/mkNonCopy.h>
#include <Ui/mkUiForward.h>
#include <Ui/Style/mkDim.h>

namespace mk
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

	class MK_UI_EXPORT Caption
	{
	public:
		Caption(DrawFrame& frame);
		~Caption();

		int selectStart() { return m_selectStart; }
		int selectEnd() { return m_selectEnd; }
		int caret() { return m_caret; }

		void selectStart(int value) { m_selectStart = value; }
		void selectEnd(int value) { m_selectEnd = value; }
		void caret(int value) { m_caret = value; }

		float textSize(Dimension dim);

		void redraw(Renderer& target, const BoxFloat& rect, const BoxFloat& paddedRect, const BoxFloat& contentRect);

		void updateTextRows(Renderer& target, const DimFloat& space);
		void updateSelection();

		TextRow& textRow(size_t index);

		size_t caretIndex(float x, float y);
		void caretCoords(float& x, float& y);

	protected:
		DrawFrame& m_frame;

		int m_selectStart;
		int m_selectEnd;
		int m_caret;

		std::vector<TextRow> m_textRows;
	};
}

#endif
