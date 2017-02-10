//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Widget/TypeIn.h>

#include <toyobj/Ref.h>

#include <toyobj/String/StringConvert.h>

#include <toyui/Widget/Widgets.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>

namespace toy
{
	TypeIn::TypeIn(string& string, StyleType& type)
		: Widget(type)
		, m_input(nullptr)
		, m_string(string)
		, m_hasPeriod(false)
	{
		this->content().setText(string);
		this->content().setTextLines(1);
	}

	TypeIn::TypeIn(WValue& input, StyleType& type)
		: TypeIn(m_valueString, type)
	{
		m_input = &input;
		m_valueString = m_input->value()->getString();
		this->content().setText(m_valueString);
	}

	void TypeIn::nextFrame(size_t tick, size_t delta)
	{
		Widget::nextFrame(tick, delta);
	}

	void TypeIn::focused()
	{
	}

	void TypeIn::unfocused()
	{
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

		this->content().setText(m_string);
	}

	void TypeIn::insert(char c)
	{
		m_string.insert(m_string.begin() + this->content().caption().caret(), c);
		this->content().setText(m_string);
		this->moveCaretRight();
	}

	void TypeIn::updateString()
	{
		m_string = m_input->value()->getString();
		this->content().setText(m_string);
		this->markDirty();
	}

	void TypeIn::leftClick(MouseEvent& mouseEvent)
	{
		size_t index = this->content().caption().caretIndex(mouseEvent.posX - m_frame->dabsolute(DIM_X), mouseEvent.posY - m_frame->dabsolute(DIM_Y));
		this->moveCaretTo(index);
		if(!(m_state & CONTROL))
			this->takeControl(CM_CONTROL, InputEvent::DEVICE_KEYBOARD);
	}

	void TypeIn::leftDragStart(MouseEvent& mouseEvent)
	{
		size_t index = this->content().caption().caretIndex(mouseEvent.posX - m_frame->dabsolute(DIM_X), mouseEvent.posY - m_frame->dabsolute(DIM_Y));
		this->selectFirst(index);
		if(!(m_state & CONTROL))
			this->takeControl(CM_CONTROL, InputEvent::DEVICE_KEYBOARD);
	}

	void TypeIn::leftDrag(MouseEvent& mouseEvent)
	{
		size_t index = this->content().caption().caretIndex(mouseEvent.posX - m_frame->dabsolute(DIM_X), mouseEvent.posY - m_frame->dabsolute(DIM_Y));
		this->selectSecond(index);
	}

	void TypeIn::leftDragEnd(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
	}

	void TypeIn::keyDown(KeyEvent& keyEvent)
	{
		keyEvent.abort = true;

		if(keyEvent.code == KC_LEFT)
		{
			this->moveCaretLeft();
		}
		else if(keyEvent.code == KC_RIGHT)
		{
			this->moveCaretRight();
		}
		else if(keyEvent.code == KC_RETURN && (m_allowedChars.size() == 0 || m_allowedChars.find('\n') != string::npos))
		{
			this->insert('\n');
		}
		else if(keyEvent.code == KC_ESCAPE)
		{
			this->yieldControl();
		}
		else if(keyEvent.code == KC_BACK)
		{
			this->erase();
		}
		else if(keyEvent.c != 0 && (m_allowedChars.size() == 0 || m_allowedChars.find(keyEvent.c) != string::npos))
		{
			if(keyEvent.c == '.' && m_string.find('.') != string::npos)
				return;

			this->insert(keyEvent.c);
		}

		if(m_input)
			m_input->setString(m_string);
		this->markDirty();
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
