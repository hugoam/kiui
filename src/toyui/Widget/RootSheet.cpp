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
	RootSheet::RootSheet(UiWindow& window, const Params& params)
		: Wedge({ params, &cls<RootSheet>(), MASTER_LAYER })
		, m_window(window)
		, m_controller(*this)
		, m_mouse(*this)
		, m_keyboard(*this)
		, m_cursor(*this)
		, m_active(nullptr)
	{
		if(!params.m_parent)
		{
			m_target = window.m_renderer->createRenderTarget(as<Layer>(*m_frame));
			this->updateStyle();
		}
	}

	RootSheet::~RootSheet()
	{}

	void RootSheet::nextFrame(size_t tick, size_t delta)
	{
		UNUSED(tick); UNUSED(delta);
		m_cursor.update();
		m_frame->relayout();
	}

	void RootSheet::handleDestroyWidget(Widget& widget)
	{
		if(m_active == &widget)
			m_active = nullptr;

		m_controller.yieldControl(widget);

		m_cursor.unhover(widget);
		m_mouse.handleDestroyWidget(widget);
	}

	void RootSheet::makeActive(Widget& widget)
	{
		if(m_active == &widget) return;
		if(m_active)
			m_active->inactive();
		m_active = &widget;
		m_active->active();
	}
}
