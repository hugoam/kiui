//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_CAPTION_H
#define TOY_CAPTION_H

/* toy */
#include <toyobj/Indexer.h>
#include <toyobj/Util/NonCopy.h>
#include <toyui/Forward.h>
#include <toyui/Style/Dim.h>
#include <toyui/Frame/Content.h>

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

	class TOY_UI_EXPORT Caption : public Object
	{
	public:
		Caption(Frame& frame);

		void select(int caret, int start, int end);

		DimFloat contentSize() { return{ width(), height() }; }
		float height();
		float width();

		void setText(const string& text);
		void setTextLines(size_t lines);

		DimFloat updateTextSize();

		void updateTextRows(Renderer& target, const DimFloat& space);
		void updateSelection();

		TextRow& textRow(size_t index);

		size_t caretIndex(const DimFloat& pos);
		void caretCoords(DimFloat& pos);

		static Type& cls() { static Type ty; return ty; }

	public:
		Frame& d_frame;
		string m_text;
		size_t m_textLines;

		int m_caret;
		int m_selectStart;
		int m_selectEnd;

		std::vector<TextRow> m_textRows;

	public:
		static Renderer* s_renderer;
	};
}

#endif
