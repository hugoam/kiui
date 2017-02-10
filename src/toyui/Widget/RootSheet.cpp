//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Widget/RootSheet.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>
#include <toyui/Frame/Layer.h>

#include <toyui/Widget/Scrollbar.h>

#include <toyui/Controller/Controller.h>

#include <toyui/UiWindow.h>
#include <toyui/UiLayout.h>

#include <toyobj/Iterable/Reverse.h>

#include <assert.h>

namespace toy
{
	RootSheet::RootSheet(UiWindow& window, StyleType& type, bool absolute)
		: Sheet(type, LAYER)
		, m_window(window)
		, m_mouse(make_unique<Mouse>(*this))
		, m_keyboard(make_unique<Keyboard>(*this))
	{
		if(absolute)
		{
			m_frame = make_unique<MasterLayer>(*this);
			this->updateStyle();
			m_layer = &m_frame->as<MasterLayer>();
			m_state = static_cast<WidgetState>(m_state ^ BOUND);
		}

		m_cursor = &this->makeappend<Cursor>(*this);
	}

	RootSheet::~RootSheet()
	{}

	void RootSheet::nextFrame(size_t tick, size_t delta)
	{
		m_frame->measure();
		m_frame->layout();

		m_mouse->nextFrame();
		m_keyboard->nextFrame();

		Sheet::nextFrame(tick, delta);
	}

	InputReceiver* RootSheet::dispatchEvent(InputEvent& inputEvent)
	{
		return InputFrame::dispatchEvent(inputEvent);
	}

	void RootSheet::handleUnbindWidget(Widget& widget)
	{
		m_mouse->handleUnbindWidget(widget);
	}

	void RootSheet::handleBindWidget(Widget& widget)
	{
		m_mouse->handleBindWidget(widget);
	}
}
