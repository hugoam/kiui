//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Window/ContextMenu.h>

#include <toyui/Widget/Layout.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>

#include <toyui/Input/InputDevice.h>
#include <toyui/Widget/RootSheet.h>

namespace toy
{
	ContextMenu::ContextMenu(Wedge& parent, Trigger onClose)
		: Overlay(parent, cls())
	{
		this->frame().setPosition(this->rootSheet().mouse().lastX(), this->rootSheet().mouse().lastY());
		this->takeControl(CM_MODAL);
	}

	void ContextMenu::clear()
	{
		this->yieldControl();
		this->as<Widget>().remove();
	}

	void ContextMenu::leftClick(MouseEvent& mouseEvent)
	{
		mouseEvent.abort = true;
		this->clear();
	}

	void ContextMenu::rightClick(MouseEvent& mouseEvent)
	{
		mouseEvent.abort = true;
		this->clear();
	}

	void ContextMenu::middleClick(MouseEvent& mouseEvent)
	{
		mouseEvent.abort = true;
		this->clear();
	}
}
