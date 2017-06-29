//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Edit/TypeIn.h>

#include <toyobj/Any.h>
#include <toyobj/String/StringConvert.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Caption.h>

namespace toy
{
	TypeIn::TypeIn(Wedge& parent, string& string, bool wrap, Type& type)
		: Wedge(parent, type)
		, m_input(nullptr)
		, m_string(string)
		, m_hasPeriod(false)
		, m_precision(3)
		, m_label(*this, "")
		, m_caption(*m_label.frame().caption())
	{
		m_caption.setTextLines(1);
		this->updateString();

		if(wrap)
			m_label.setStyle(Text::cls());
	}

	TypeIn::TypeIn(WValue& input, bool wrap, Type& type)
		: TypeIn(input, m_valueString, wrap, type)
	{
		m_input = &input;
		this->updateString();
	}

	void TypeIn::active()
	{
		this->enableState(ACTIVE);
		this->takeControl(CM_MODAL, DEVICE_KEYBOARD);
	}

	void TypeIn::inactive()
	{
		this->disableState(ACTIVE);
		this->yieldControl();
		this->selectCaret(-1);
	}

	void TypeIn::setAllowedChars(const string& chars)
	{
		m_allowedChars = chars;
	}

	void TypeIn::erase()
	{
		if(m_caption.caret() == 0 && m_caption.selectStart() == m_caption.selectEnd())
			return;

		if(m_caption.selectStart() == m_caption.selectEnd())
		{
			m_string.erase(m_string.begin() + m_caption.selectStart() - 1);
			this->moveCaretLeft();
		}
		else
		{
			m_string.erase(m_string.begin() + m_caption.selectStart(), m_string.begin() + m_caption.selectEnd());
			this->selectCaret(m_caption.selectStart());
		}

		this->updateText();
	}

	void TypeIn::insert(char c)
	{
		m_string.insert(m_string.begin() + m_caption.caret(), c);
		this->updateText();
		this->moveCaretRight();
	}

	void TypeIn::updateString()
	{
		if(m_input)
			m_string = m_input->getString();

		m_caption.setText(m_string);
	}

	void TypeIn::updateText()
	{
		if(m_input)
			m_input->setString(m_string);

		m_caption.setText(m_string);
	}

	bool TypeIn::leftClick(MouseEvent& mouseEvent)
	{
		size_t index = m_caption.caretIndex(mouseEvent.relative);
		this->selectCaret(index);
		this->selectFirst(index);
		if(!(m_state & CONTROL))
			this->makeActive();
		return true;
	}

	bool TypeIn::leftDragStart(MouseEvent& mouseEvent)
	{
		size_t index = m_caption.caretIndex(mouseEvent.relative);
		this->selectFirst(index);
		if(!(m_state & CONTROL))
			this->makeActive();
		return true;
	}

	bool TypeIn::leftDrag(MouseEvent& mouseEvent)
	{
		size_t index = m_caption.caretIndex(mouseEvent.relative);
		this->selectSecond(index);
		return true;
	}

	bool TypeIn::leftDragEnd(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		return true;
	}

	bool TypeIn::keyDown(KeyEvent& keyEvent)
	{
		if(keyEvent.code == KC_LEFT)
			this->moveCaretLeft();
		else if(keyEvent.code == KC_RIGHT)
			this->moveCaretRight();
		else if(keyEvent.code == KC_RETURN && (m_allowedChars.empty() || m_allowedChars.find('\n') != string::npos))
			this->insert('\n');
		else if(keyEvent.code == KC_ESCAPE)
			this->yieldControl();
		else if(keyEvent.code == KC_BACK)
			this->erase();
		else if(keyEvent.c != 0 && (m_allowedChars.empty() || m_allowedChars.find(keyEvent.c) != string::npos))
		{
			if(keyEvent.c == '.' && m_string.find('.') != string::npos)
				return true;

			this->insert(keyEvent.c);
		}

		return true;
	}

	void TypeIn::selectCaret(int index)
	{
		m_caption.select(index, index, index);
	}

	void TypeIn::selectFirst(size_t first)
	{
		m_selectFirst = first;
		m_caption.select(first, first, first);
	}

	void TypeIn::selectSecond(size_t second)
	{
		m_selectSecond = second;
		if(m_selectFirst < m_selectSecond)
			m_caption.select(std::min(m_selectSecond + 1, m_caption.textRow(second).endIndex), m_selectFirst, m_selectSecond);
		else
			m_caption.select(m_selectSecond, m_selectSecond, m_selectFirst);
	}

	void TypeIn::moveCaretRight()
	{
		size_t index = std::min(int(m_caption.text().size()), m_caption.caret() + 1);
		this->selectCaret(index);
	}

	void TypeIn::moveCaretLeft()
	{
		size_t index = std::max(0, m_caption.caret() - 1);
		this->selectCaret(index);
	}
}
