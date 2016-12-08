//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_CAPTION_H
#define MK_CAPTION_H

/* mk Front */
#include <Object/mkIndexer.h>
#include <Object/Util/mkNonCopy.h>
#include <Ui/mkUiForward.h>
#include <Ui/Frame/mkRenderFrame.h>
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
		BoxFloat rect;
		BoxFloat selected;

		std::vector<TextGlyph> glyphs;
	};

	class MK_UI_EXPORT Caption : public RenderFrame
	{
	public:
		Caption(Frame& frame);
		~Caption();

		size_t selectStart() { return m_selectFirst < m_selectSecond ? m_selectFirst : m_selectSecond; }
		size_t selectEnd() { return m_selectSecond > m_selectFirst ? m_selectSecond : m_selectFirst; }

		void redraw(Renderer& target, BoxFloat& rect, BoxFloat& paddedRect, BoxFloat& contentRect);

		void selectCaret(size_t index) { m_selectFirst = index; m_selectSecond = index; this->updateSelection(); }
		void selectFirst(size_t start) { m_selectFirst = start; m_selectSecond = start; this->updateSelection(); }
		void selectSecond(size_t end) { m_selectSecond = end; this->updateSelection(); }

		void updateTextRows(Renderer& target, BoxFloat& paddedRect);
		void updateSelection();

		size_t caretIndex(float x, float y);
		void caretCoords(size_t index, float& caretX, float& caretY, float& caretHeight);

	protected:
		size_t m_selectFirst;
		size_t m_selectSecond;

		std::vector<TextRow> m_textRows;
	};
}

#endif
