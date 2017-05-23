//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Widget/RootSheet.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>
#include <toyui/Frame/Layer.h>

#include <toyui/Button/Scrollbar.h>

#include <toyui/Controller/Controller.h>

#include <toyui/Input/InputDevice.h>

#include <toyui/UiWindow.h>
#include <toyui/UiLayout.h>

#include <toyobj/Iterable/Reverse.h>

#include <assert.h>

namespace toy
{
	RootSheet::RootSheet(UiWindow& window, Type& type)
		: Container(type, MASTER_LAYER)
		, m_window(window)
		, m_rootController(make_unique<ControlSwitch>(*this))
		, m_mouse(make_unique<Mouse>(*this))
		, m_keyboard(make_unique<Keyboard>(*this))
		, m_cursor(*this)
	{
		m_target = window.renderer().createRenderTarget(m_frame->as<MasterLayer>());
		this->updateStyle();
	}

	RootSheet::RootSheet(Wedge& parent, Type& type)
		: Container(parent, type, LAYER)
		, m_window(parent.uiWindow())
		, m_rootController(make_unique<ControlSwitch>(*this))
		, m_mouse(make_unique<Mouse>(*this))
		, m_keyboard(make_unique<Keyboard>(*this))
		, m_cursor(*this)
	{}

	RootSheet::~RootSheet()
	{}

	void RootSheet::nextFrame(size_t tick, size_t delta)
	{
		m_frame->as<MasterLayer>().relayout();
		m_frame->as<MasterLayer>().redraw();

		m_mouse->nextFrame();
		m_keyboard->nextFrame();

		Wedge::nextFrame(tick, delta);
	}

	void RootSheet::handleUnbindWidget(Widget& widget, bool destroy)
	{
		m_rootController->yieldControl(widget);

		m_cursor.unhover(widget);
		m_mouse->handleUnbindWidget(widget, destroy);
	}

	void RootSheet::handleBindWidget(Widget& widget)
	{
		m_mouse->handleBindWidget(widget);
	}
}
