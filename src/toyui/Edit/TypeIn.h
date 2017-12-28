//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_TYPEIN_H
#define TOY_TYPEIN_H

/* toy */
#include <toyui/Types.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Button/Button.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT TypeIn : public Wedge
	{
	public:
		using Callback = std::function<string(const string&)>;

	public:
		TypeIn(const Params& params, string& text, Callback callback = nullptr, bool wrap = false);

		string& m_text;

		virtual void active();
		virtual void inactive();

		void setText(const string& value);
		void setAllowedChars(const string& chars);

		void erase();
		void insert(char c);
		void update();
		void changed();

		void activate();

		virtual bool leftClick(MouseEvent& mouseEvent);
		virtual bool keyDown(KeyEvent& keyEvent);

		virtual bool leftDragStart(MouseEvent& mouseEvent);
		virtual bool leftDrag(MouseEvent& mouseEvent);

		void selectCaret(int index);
		void selectFirst(size_t start);
		void selectSecond(size_t end);

		void moveCaretRight();
		void moveCaretLeft();

	protected:
		string m_allowedChars;

		size_t m_selectFirst;
		size_t m_selectSecond;

		Label m_label;
		Caption& m_caption;

		Callback m_callback;
	};
}

#endif
