//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Widget/Widget.h>

#include <toyui/Widget/Sheet.h>
#include <toyui/Widget/RootSheet.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>
#include <toyui/Frame/Grid.h>
#include <toyui/Frame/Layer.h>

#include <toyui/UiLayout.h>

#include <toyobj/Iterable/Reverse.h>

namespace toy
{
	string Widget::sNullString;

	Widget::Widget(StyleType& type, FrameType frameType)
		: TypeObject(type)
		, m_parent(nullptr)
		, m_style(&type)
		, d_styleStamp(type.updated())
		, m_frame()
		, m_state(UNBOUND)
		, m_device(nullptr)
	{
		if(frameType == GRID)
			m_frame = make_unique<Grid>(*this);
		else if(frameType == TABLE)
			m_frame = make_unique<TableGrid>(*this);
		else if(frameType == STRIPE)
			m_frame = make_unique<Stripe>(*this);
		else if(frameType == FRAME)
			m_frame = make_unique<Frame>(*this);
	}

	Widget::~Widget()
	{}

	RootSheet& Widget::rootSheet()
	{
		return m_parent->rootSheet();
	}

	UiWindow& Widget::uiWindow()
	{
		return this->rootSheet().uiWindow();
	}

	Context& Widget::context()
	{
		return this->uiWindow().context();
	}

	DrawFrame& Widget::content()
	{
		return m_frame->content();
	}

	const string& Widget::label()
	{
		return this->content().text();
	}

	void Widget::setLabel(const string& label)
	{
		this->content().setText(label);
	}

	Image* Widget::image()
	{
		return this->content().image();
	}

	void Widget::setImage(Image* image)
	{
		this->content().setImage(image);
	}

	const string& Widget::contentlabel()
	{
		return this->content().text();
	}

	void Widget::bind(Sheet& parent, size_t index)
	{
		m_parent = &parent;
		m_parentFrame = &parent;
		m_index = index;

		m_frame->bind(parent.stripe());
		m_parent->stripe().map(*m_frame);
		this->updateStyle();
		this->enableState(BOUND);
		this->bound();

		this->rootSheet().handleBindWidget(*this);
	}

	void Widget::unbind()
	{
		this->rootSheet().handleUnbindWidget(*this);

		this->disableState(BOUND);
		this->unbound();
		m_frame->unbind();
		m_parent->stripe().unmap(*m_frame);

		m_parent = nullptr;
		m_parentFrame = nullptr;
		m_index = 0;
	}

	unique_ptr<Widget> Widget::detach()
	{
		return m_parent->release(*this);
	}

	unique_ptr<Widget> Widget::extract()
	{
		unique_ptr<Widget> unique = m_parent->release(*this);
		m_parent->destroy();
		return unique;
	}

	void Widget::remove()
	{
		m_parent->vrelease(*this);
	}

	void Widget::destroy()
	{
		m_parent->release(*this);
	}

	void Widget::nextFrame(size_t tick, size_t step)
	{
		m_frame->updateOnce();

		if(m_style->updated() > d_styleStamp)
			this->resetStyle();
	}

	void Widget::render(Renderer& renderer)
	{
		m_frame->content().beginDraw(renderer);
		m_frame->content().draw(renderer);
		m_frame->content().endDraw(renderer);
	}

	void Widget::show()
	{
		m_frame->show();
	}
	
	void Widget::hide()
	{
		m_frame->hide();
	}

	void Widget::updateStyle()
	{
		m_frame->setStyle(this->fetchOverride(*m_style));
	}

	void Widget::resetStyle()
	{
		if(!m_parent)
			return;

		size_t index = m_index;
		Sheet& parent = *m_parent;
		parent.unbindChild(*this);
		parent.bindChild(*this, index);

		d_styleStamp = m_style->updated();

		this->updateStyle();
	}

	void Widget::resetStyle(Style& style)
	{
		m_style = &style;
		this->resetStyle();
	}

	void Widget::resetSkin(Style& style)
	{
		m_style = &style;
		this->updateStyle();
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

	void Widget::markDirty()
	{
		m_frame->setDirty(Frame::DIRTY_CONTENT);
	}

	void Widget::toggleState(WidgetState state)
	{
		m_state = static_cast<WidgetState>(m_state ^ state);
		this->updateState();
	}

	void Widget::enableState(WidgetState state)
	{
		if(!(m_state & state))
			this->toggleState(state);
	}

	void Widget::disableState(WidgetState state)
	{
		if(m_state & state)
			this->toggleState(state);
	}

	void Widget::updateState()
	{
		// @kludge: m_style is our original type and style, but m_frame->style() is the 'transient' override, think about harmonizing that
		if(m_state & BOUND)
			m_frame->content().updateInkstyle(m_frame->style().subskin(m_state));
	}

	Widget* Widget::pinpoint(float x, float y)
	{
		Frame* frame = m_frame->pinpoint(x - m_frame->dabsolute(DIM_X), y - m_frame->dabsolute(DIM_Y), true);
		return frame ? frame->widget() : nullptr;
	}

	InputReceiver* Widget::controlEvent(InputEvent& inputEvent)
	{
		if(m_controller && m_controller->consumes(inputEvent.deviceType))
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

	void Widget::activate()
	{
		this->enableState(ACTIVATED);
	}

	void Widget::deactivate()
	{
		this->disableState(ACTIVATED);
	}
	
	void Widget::modal()
	{
		this->enableState(MODAL);
	}

	void Widget::unmodal()
	{
		this->disableState(MODAL);
	}

	void Widget::control()
	{
		this->enableState(CONTROL);
		this->enableState(FOCUSED);
		this->focused();
	}

	void Widget::uncontrol()
	{
		this->disableState(CONTROL);
		this->disableState(FOCUSED);
		this->unfocused();
	}

	void Widget::mouseEntered(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		this->enableState(HOVERED);
	}

	void Widget::mouseLeaved(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		this->disableState(HOVERED);
	}

	void Widget::mousePressed(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		this->enableState(PRESSED);
	}

	void Widget::mouseReleased(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		this->disableState(PRESSED);
	}
}
