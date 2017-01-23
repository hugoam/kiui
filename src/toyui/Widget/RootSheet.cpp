//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
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

#include <iostream>

namespace toy
{
	RootSheet::RootSheet(UiWindow& window, StyleType& type, bool absolute)
		: Sheet(type, LAYER)
		, m_window(window)
	{
		if(absolute)
		{
			m_frame = make_unique<MasterLayer>(*this);
			m_frame->as<Layer>().bind();
			m_layer = &m_frame->as<MasterLayer>();
			m_state = static_cast<WidgetState>(m_state ^ BOUND);
		}

		m_cursor = &this->makeappend<Cursor>(*this);
	}

	RootSheet::~RootSheet()
	{
		this->cleanup();
	}

	void RootSheet::nextFrame(size_t tick, size_t delta)
	{
		//m_layer->nextFrame(tick, delta);
		m_cursor->nextFrame();
	}

	InputReceiver* RootSheet::dispatchEvent(InputEvent& inputEvent)
	{
		return InputFrame::dispatchEvent(inputEvent);
	}
}
