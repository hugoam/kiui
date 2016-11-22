//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkWidget.h>

#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkRootSheet.h>

#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>
#include <Ui/Frame/mkLayer.h>

#include <Ui/mkUiLayout.h>

#include <Object/Iterable/mkReverse.h>

#include <iostream>

namespace mk
{
	string Widget::sNullString;

	Widget::Widget(StyleType& type, FrameType frameType)
		: TypeObject(type)
		, m_parent(nullptr)
		, m_style(&type)
		, m_frame(nullptr)
		, m_state(UNBOUND)
	{
		if(frameType == STRIPE)
			m_frame = make_unique<Stripe>(*this);
		else if(frameType == FRAME)
			m_frame = make_unique<Frame>(*this);
	}

	Widget::~Widget()
	{
		this->cleanup();
	}

	void Widget::cleanup()
	{
		if(m_state & PRESSED || m_state & HOVERED)
			this->uiWindow().handleDestroyWidget(*this);

		m_state = UNBOUND;
	}

	void Widget::bind(Sheet& parent, size_t index)
	{
		m_parent = &parent;
		m_parentFrame = &parent;

		if(m_frame->frameType() != LAYER3D)
			m_parent->stripe().insert(*m_frame, index);
		else
			m_frame->as<Layer>().bind();

		m_state = static_cast<WidgetState>(m_state ^ BOUND);

		this->bound();
	}

	void Widget::rebind(Sheet& parent, size_t index)
	{
		m_parent = &parent;
		m_parentFrame = &parent;

		m_frame->transfer(m_parent->frame().as<Stripe>(), index);
	}

	unique_ptr<Widget> Widget::unbind()
	{
		//this->cleanup();
		m_state = static_cast<WidgetState>(m_state ^ BOUND);
		return m_parent->as<Sheet>().release(*this);
	}

	unique_ptr<Widget> Widget::extract()
	{
		this->cleanup();
		unique_ptr<Widget> unique = m_parent->as<Sheet>().release(*this);
		m_parent->destroy();
		return unique;
	}

	void Widget::remove()
	{
		this->cleanup();
		m_parent->as<Sheet>().vrelease(*this);
	}

	void Widget::destroy()
	{
		this->cleanup();
		m_parent->as<Sheet>().release(*this);
	}

	void Widget::detach()
	{
		m_frame->remove();
	}

	void Widget::show()
	{
		m_frame->show();
	}
	
	void Widget::hide()
	{
		m_frame->hide();
	}

	void Widget::setStyle(Style& style)
	{
		m_style = &style;
		//this->reset(style);
	}

	void Widget::resetStyle(Style& style)
	{
		m_style = &style;
		m_frame->resetStyle();
	}

	void Widget::resetSkin(Style& style)
	{
		m_style = &style;
		m_frame->updateStyle();
	}

	Style& Widget::fetchOverride(Style& style)
	{
		Style* overrider = this->uiWindow().styler().fetchOverride(style, *m_style);
		if(overrider)
			return *overrider;
		else if(m_parent)
			return m_parent->fetchOverride(style);
		else
			return style;
	}

	Image* Widget::image()
	{
		if(m_frame->inkstyle().image())
			return m_frame->inkstyle().image();
		return nullptr;
	}

	RootSheet& Widget::rootSheet()
	{
		return m_parent->rootSheet();
	}

	bool Widget::contains(Widget& widget)
	{
		Widget* test = &widget;
		while(test && test != this)
			test = test->parent();
		return test == this;
	}

	UiWindow&  Widget::uiWindow()
	{
		return this->rootSheet().uiWindow();
	}

	void Widget::markDirty()
	{
		m_frame->setDirty(Frame::DIRTY_WIDGET);
	}

	void Widget::toggleState(WidgetState state)
	{
		m_state = static_cast<WidgetState>(m_state ^ state);
		if(m_state & BOUND)
			m_frame->updateState(m_state);
	}

	void Widget::nextFrame(size_t tick, size_t delta)
	{
		m_frame->nextFrame(tick, delta);
	}

	Widget* Widget::pinpoint(float x, float y)
	{
		Frame* target = m_frame->pinpoint(x, y, true);
		if(target)
			return &target->widget();
		else
			return nullptr;
	}

	Widget& Widget::prev()
	{
		return m_frame->parent()->contents()[m_frame->index() - 1]->widget();
	}

	Widget& Widget::next()
	{
		return m_frame->parent()->contents()[m_frame->index() + 1]->widget();
	}

	InputReceiver* Widget::controlEvent(InputEvent& inputEvent)
	{
		if(m_controller)
			return m_controller->controlEvent(inputEvent);

		if(inputEvent.deviceType >= InputEvent::DEVICE_MOUSE && m_controlMode < CM_ABSOLUTE)
		{
			MouseEvent& mouseEvent = static_cast<MouseEvent&>(inputEvent);
			Widget* pinned = this->pinpoint(mouseEvent.posX, mouseEvent.posY);
			return pinned ? pinned : this;
		}

		return this;
	}

	InputReceiver* Widget::propagateEvent(InputEvent& inputEvent)
	{
		UNUSED(inputEvent);
		return m_parent;
	}

	void Widget::hover()
	{
		this->toggleState(HOVERED);
	}

	void Widget::unhover()
	{
		this->toggleState(HOVERED);
	}

	void Widget::activate()
	{
		this->toggleState(ACTIVATED);
	}

	void Widget::deactivate()
	{
		this->toggleState(ACTIVATED);
	}
	
	void Widget::modal()
	{
		this->toggleState(MODAL);
	}

	void Widget::unmodal()
	{
		this->toggleState(MODAL);
	}

	void Widget::control()
	{
		this->toggleState(CONTROL);
		this->focused();
	}

	void Widget::uncontrol()
	{
		this->toggleState(CONTROL);
		this->unfocused();
	}

	void Widget::mouseEntered(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		this->hover();
	}

	void Widget::mouseLeaved(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		this->unhover();
	}

	void Widget::mousePressed(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		this->toggleState(PRESSED);
	}

	void Widget::mouseReleased(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		this->toggleState(PRESSED);
	}
}
