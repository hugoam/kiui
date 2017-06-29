//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Widget/RootSheet.h>

#include <toyui/Frame/Layer.h>
#include <toyui/Render/Renderer.h>

#include <toyui/Controller/Controller.h>

#include <toyui/UiWindow.h>

namespace toy
{
	RootSheet::RootSheet(UiWindow& window, Type& type, Wedge* parent)
		: Wedge(type, MASTER_LAYER, parent)
		, m_window(window)
		, m_rootController(make_unique<ControlSwitch>(*this))
		, m_mouse(*this)
		, m_keyboard(*this)
		, m_cursor(*this)
	{
		if(!parent)
		{
			m_target = window.renderer().createRenderTarget(m_frame->as<Layer>());
			this->updateStyle();
		}
	}

	RootSheet::~RootSheet()
	{}

	void RootSheet::nextFrame(size_t tick, size_t delta)
	{
		m_cursor.nextFrame(tick, delta);
		m_frame->relayout();
	}

	void RootSheet::handleDestroyWidget(Widget& widget)
	{
		m_rootController->yieldControl(widget);

		m_cursor.unhover(widget);
		m_mouse.handleDestroyWidget(widget);
	}
}
