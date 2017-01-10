//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkRootSheet.h>

#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>
#include <Ui/Frame/mkLayer.h>

#include <Ui/Widget/mkScrollbar.h>

#include <Ui/Controller/mkController.h>

#include <Ui/mkUiWindow.h>
#include <Ui/mkUiLayout.h>

#include <Object/Iterable/mkReverse.h>

#include <assert.h>

#include <iostream>

namespace mk
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
