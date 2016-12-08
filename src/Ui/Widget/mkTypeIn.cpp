//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkTypeIn.h>

#include <Object/mkRef.h>

#include <Object/String/mkStringConvert.h>

#include <Ui/Widget/mkWidgets.h>

#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>

#include <iostream>

namespace mk
{
	TypeIn::TypeIn(string& string, StyleType& type)
		: Sheet(type)
		, m_input(nullptr)
		, m_string(string)
		, m_hasPeriod(false)
		, m_caret(this->makeappend<Caret>(m_frame.get()))
	{
		m_frame->setText(string);
		m_caret.hide();
	}

	TypeIn::TypeIn(WValue& input, StyleType& type)
		: TypeIn(m_valueString, type)
	{
		m_input = &input;
		m_valueString = m_input->value()->getString();
		m_caret.hide();
	}

	void TypeIn::nextFrame(size_t tick, size_t delta)
	{
		//Sheet::nextFrame(tick, delta);

		if(m_state & CONTROL)
		{
			bool odd = (tick / 25) % 2;
			if(odd && m_caret.frame().hidden())
				m_caret.show();
			else if(!odd && !m_caret.frame().hidden())
				m_caret.hide();
		}
	}

	void TypeIn::focused()
	{
		if(m_caret.frame().hidden())
			m_caret.show();
	}

	void TypeIn::unfocused()
	{
		m_frame->caption().selectFirst(0);
		m_frame->caption().selectSecond(0);

		if(!m_caret.frame().hidden())
			m_caret.hide();
	}

	void TypeIn::setAllowedChars(const string& chars)
	{
		m_allowedChars = chars;
	}

	void TypeIn::erase()
	{
		if(m_caret.index() == 0 && m_frame->caption().selectStart() == m_frame->caption().selectEnd())
			return;

		if(m_frame->caption().selectStart() == m_frame->caption().selectEnd())
		{
			m_string.erase(m_string.begin() + m_frame->caption().selectStart() - 1);
			this->setCaret(m_caret.index() - 1);
		}
		else
		{
			m_string.erase(m_string.begin() + m_frame->caption().selectStart(), m_string.begin() + m_frame->caption().selectEnd());
			this->setCaret(m_frame->caption().selectStart());
		}
	}

	void TypeIn::insert(char c)
	{
		m_string.insert(m_string.begin() + m_caret.index(), c);
		this->setCaret(m_caret.index() + 1);
	}

	void TypeIn::updateString()
	{
		m_string = m_input->value()->getString();
		this->markDirty();
	}

	void TypeIn::leftClick(MouseEvent& mouseEvent)
	{
		size_t index = m_frame->caption().caretIndex(mouseEvent.posX - m_frame->dabsolute(DIM_X), mouseEvent.posY - m_frame->dabsolute(DIM_Y));
		this->setCaret(index);
		if(!(m_state & CONTROL))
			this->takeControl(CM_CONTROL, InputEvent::DEVICE_KEYBOARD);
	}

	void TypeIn::leftDragStart(MouseEvent& mouseEvent)
	{
		size_t index = m_frame->caption().caretIndex(mouseEvent.posX - m_frame->dabsolute(DIM_X), mouseEvent.posY - m_frame->dabsolute(DIM_Y));
		m_caret.setIndex(index);
		m_frame->caption().selectFirst(index);
		if(!(m_state & CONTROL))
			this->takeControl(CM_CONTROL, InputEvent::DEVICE_KEYBOARD);
	}

	void TypeIn::leftDrag(MouseEvent& mouseEvent)
	{
		size_t index = m_frame->caption().caretIndex(mouseEvent.posX - m_frame->dabsolute(DIM_X), mouseEvent.posY - m_frame->dabsolute(DIM_Y));
		m_frame->caption().selectSecond(index);
		m_caret.setIndex(index);
	}

	void TypeIn::leftDragEnd(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
	}

	void TypeIn::keyDown(KeyEvent& keyEvent)
	{
		keyEvent.abort = true;

		if(keyEvent.code == KC_LEFT && m_caret.index() > 0)
		{
			m_caret.moveLeft();
		}
		else if(keyEvent.code == KC_RIGHT && m_caret.index() < m_string.size())
		{
			m_caret.moveRight();
		}
		else if(keyEvent.code == KC_RETURN)
		{
			this->insert('\n');
			//this->unfocus();
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

	void TypeIn::setCaret(size_t index)
	{
		m_caret.setIndex(index);
		m_frame->caption().selectFirst(index);
	}
}
