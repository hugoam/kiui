//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Widget/ContextMenu.h>

#include <toyui/Widget/Widgets.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>

#include <toyui/Widget/RootSheet.h>

namespace toy
{
	ContextMenu::ContextMenu(Trigger onClose)
		: Sheet(cls())
	{
		//this->rootSheet().contextOn(*this);
	}

	ContextMenu::~ContextMenu()
	{
		//this->clear();
	}

	void ContextMenu::bound()
	{
		this->rootSheet().append(m_parent->release(*this));

		this->frame().setPosition(this->rootSheet().mouse().lastX(), this->rootSheet().mouse().lastY());
		this->takeControl(CM_MODAL);
	}

	void ContextMenu::clear()
	{
		this->yieldControl();
		this->remove();
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
