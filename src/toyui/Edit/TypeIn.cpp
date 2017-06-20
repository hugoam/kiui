//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Edit/TypeIn.h>

#include <toyobj/Any.h>

#include <toyobj/String/StringConvert.h>

#include <toyui/Container/Layout.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>

namespace toy
{
	TypeIn::TypeIn(Wedge& parent, string& string, Type& type)
		: Control(parent, type)
		, m_input(nullptr)
		, m_string(string)
		, m_hasPeriod(false)
		, m_precision(3)
	{
		this->content().setTextLines(1);
		this->updateString();
	}

	TypeIn::TypeIn(WValue& input, Type& type)
		: TypeIn(input, m_valueString, type)
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
		if(this->content().caption().caret() == 0 && this->content().caption().selectStart() == this->content().caption().selectEnd())
			return;

		if(this->content().caption().selectStart() == this->content().caption().selectEnd())
		{
			m_string.erase(m_string.begin() + this->content().caption().selectStart() - 1);
			this->moveCaretLeft();
		}
		else
		{
			m_string.erase(m_string.begin() + this->content().caption().selectStart(), m_string.begin() + this->content().caption().selectEnd());
			this->moveCaretTo(this->content().caption().selectStart());
		}

		this->updateText();
	}

	void TypeIn::insert(char c)
	{
		m_string.insert(m_string.begin() + this->content().caption().caret(), c);
		this->updateText();
		this->moveCaretRight();
	}

	void TypeIn::updateString()
	{
		if(m_input)
			m_string = m_input->getString();

		this->content().setText(m_string);
		this->markDirty();
	}

	void TypeIn::updateText()
	{
		if(m_input)
			m_input->setString(m_string);

		this->content().setText(m_string);
		this->markDirty();
	}

	bool TypeIn::leftClick(MouseEvent& mouseEvent)
	{
		size_t index = this->content().caption().caretIndex(mouseEvent.relativeX, mouseEvent.relativeY);
		this->moveCaretTo(index);
		if(!(m_state & CONTROL))
			this->makeActive();
		return true;
	}

	bool TypeIn::leftDragStart(MouseEvent& mouseEvent)
	{
		size_t index = this->content().caption().caretIndex(mouseEvent.relativeX, mouseEvent.relativeY);
		this->selectFirst(index);
		if(!(m_state & CONTROL))
			this->makeActive();
		return true;
	}

	bool TypeIn::leftDrag(MouseEvent& mouseEvent)
	{
		size_t index = this->content().caption().caretIndex(mouseEvent.relativeX, mouseEvent.relativeY);
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
		this->content().caption().caret(index);
		this->content().caption().selectStart(index);
		this->content().caption().selectEnd(index);
		this->content().caption().updateSelection();
		this->markDirty();
	}

	void TypeIn::selectFirst(size_t first)
	{
		m_selectFirst = first;
		this->content().caption().selectStart(first);
		this->content().caption().selectEnd(first);
		this->content().caption().updateSelection();
		this->markDirty();
	}

	void TypeIn::selectSecond(size_t second)
	{
		m_selectSecond = second;
		
		this->content().caption().selectStart(m_selectFirst < m_selectSecond ? m_selectFirst : m_selectSecond);
		this->content().caption().selectEnd(m_selectFirst < m_selectSecond ? m_selectSecond : m_selectFirst);

		TextRow& secondRow = this->content().caption().textRow(second);
		this->content().caption().caret(m_selectFirst < m_selectSecond ? std::min(m_selectSecond + 1, secondRow.endIndex) : m_selectSecond);
		this->content().caption().updateSelection();
		this->markDirty();
	}

	void TypeIn::moveCaretTo(size_t index)
	{
		this->selectCaret(index);
		this->selectFirst(index);
	}

	void TypeIn::moveCaretRight()
	{
		size_t index = std::min(int(this->content().text().size()), this->content().caption().caret() + 1);
		this->selectCaret(index);
	}

	void TypeIn::moveCaretLeft()
	{
		size_t index = std::max(0, this->content().caption().caret() - 1);
		this->selectCaret(index);
	}
}
