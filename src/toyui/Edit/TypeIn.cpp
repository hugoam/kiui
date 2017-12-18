//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Edit/TypeIn.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Caption.h>

namespace toy
{
	TypeIn::TypeIn(const Params& params, const string& text, Callback callback, bool wrap)
		: Wedge({ params, &cls<TypeIn>() })
		, m_string(text)
		, m_label({ this }, text)
		, m_caption(*m_label.frame().d_caption)
		, m_callback(callback ? callback : [](const string& val) { return val; })
	{
		m_caption.setTextLines(1);

		if(wrap)
			m_label.setStyle(styles().text);
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

	void TypeIn::activate()
	{
		this->makeActive();
	}

	void TypeIn::setString(const string& value)
	{
		m_string = value;
		this->update();
	}

	void TypeIn::setAllowedChars(const string& chars)
	{
		m_allowedChars = chars;
	}

	void TypeIn::erase()
	{
		if(m_caption.m_caret == 0 && m_caption.m_selectStart == m_caption.m_selectEnd)
			return;

		if(m_caption.m_selectStart == m_caption.m_selectEnd)
		{
			m_string.erase(m_string.begin() + m_caption.m_selectStart - 1);
			this->moveCaretLeft();
		}
		else
		{
			m_string.erase(m_string.begin() + m_caption.m_selectStart, m_string.begin() + m_caption.m_selectEnd);
			this->selectCaret(m_caption.m_selectStart);
		}

		this->changed();
	}

	void TypeIn::insert(char c)
	{
		m_string.insert(m_string.begin() + m_caption.m_caret, c);
		this->changed();
		this->moveCaretRight();
	}

	void TypeIn::update()
	{
		m_caption.setText(m_string);
	}

	void TypeIn::changed()
	{
		if(m_callback)
			m_string = m_callback(m_string);
		m_caption.setText(m_string);
	}

	bool TypeIn::leftClick(MouseEvent& mouseEvent)
	{
		size_t index = m_caption.caretIndex(mouseEvent.relative);
		this->selectCaret(index);
		this->activate();
		return true;
	}

	bool TypeIn::leftDragStart(MouseEvent& mouseEvent)
	{
		size_t index = m_caption.caretIndex(mouseEvent.relative);
		this->selectFirst(index);
		this->activate();
		return true;
	}

	bool TypeIn::leftDrag(MouseEvent& mouseEvent)
	{
		size_t index = m_caption.caretIndex(mouseEvent.relative);
		this->selectSecond(index);
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
		size_t index = std::min(int(m_caption.m_text.size()), m_caption.m_caret + 1);
		this->selectCaret(index);
	}

	void TypeIn::moveCaretLeft()
	{
		size_t index = std::max(0, m_caption.m_caret - 1);
		this->selectCaret(index);
	}
}
