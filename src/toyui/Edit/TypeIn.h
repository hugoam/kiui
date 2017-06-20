//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_TYPEIN_H
#define TOY_TYPEIN_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Widget/Cursor.h>
#include <toyui/Button/Checkbox.h>
#include <toyui/Edit/Value.h>

#include <toyobj/String/StringConvert.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT TypeIn : public Control
	{
	public:
		TypeIn(Wedge& parent, string& string, Type& type = cls());
		TypeIn(WValue& input, Type& type = cls());

		virtual void active();
		virtual void inactive();

		void setAllowedChars(const string& chars);

		void erase();
		void insert(char c);
		void updateString();
		void updateText();

		virtual bool leftClick(MouseEvent& mouseEvent);
		virtual bool keyDown(KeyEvent& keyEvent);

		virtual bool leftDragStart(MouseEvent& mouseEvent);
		virtual bool leftDrag(MouseEvent& mouseEvent);
		virtual bool leftDragEnd(MouseEvent& mouseEvent);

		void selectCaret(int index);
		void selectFirst(size_t start);
		void selectSecond(size_t end);

		void moveCaretTo(size_t index);
		void moveCaretRight();
		void moveCaretLeft();

		static Type& cls() { static Type ty("TypeIn", Control::cls()); return ty; }

	protected:
		WValue* m_input;
		string& m_string;
		bool m_hasPeriod;
		string m_allowedChars;
		size_t m_precision;

		string m_valueString;

		size_t m_selectFirst;
		size_t m_selectSecond;

		//std::vector<TextSelection*> m_selection;
	};
}

#endif
