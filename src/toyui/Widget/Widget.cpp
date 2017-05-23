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
#include <toyui/UiWindow.h>

#include <toyobj/Iterable/Reverse.h>

#define TOYUI_INSTANT_MAPPING

namespace toy
{
	string Widget::sNullString;

	Widget::Widget(Wedge& parent, Type& type, FrameType frameType)
		: Widget(type, frameType, &parent)
	{
		parent.push(*this);
	}

	Widget::Widget(Type& type, FrameType frameType, Wedge* parent)
		: TypeObject(type)
		, m_parent(parent)
		, m_container(nullptr)
		, m_style(nullptr)
		, m_frame()
		, m_state(NOSTATE)
		, m_device(nullptr)
	{
		if(frameType == MASTER_LAYER)
			m_frame = make_unique<MasterLayer>(*this);
		else if(frameType == LAYER)
			m_frame = make_unique<Layer>(*this);
		else if(frameType == GRID)
			m_frame = make_unique<Grid>(*this);
		else if(frameType == TABLE)
			m_frame = make_unique<TableGrid>(*this);
		else if(frameType == STRIPE)
			m_frame = make_unique<Stripe>(*this);
		else if(frameType == FRAME)
			m_frame = make_unique<Frame>(*this);

		if(m_parent)
			this->updateStyle();
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

	ControlSwitch& Widget::rootController()
	{
		return this->rootSheet().controller();
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

	Image& Widget::findImage(const string& name)
	{
		return this->uiWindow().findImage(name);
	}

	const string& Widget::contentlabel()
	{
		return this->content().text();
	}

	void Widget::bind(Wedge& parent, size_t index)
	{
		m_parent = &parent;
		m_index = index;

		this->propagateTo(&parent);
		
		m_parent->stripe().map(*m_frame);

		RootSheet& rootSheet = this->rootSheet();
		this->visit([&rootSheet](Widget& widget) { rootSheet.handleBindWidget(widget); return true; });
	}

	void Widget::unbind(bool destroy)
	{
		RootSheet& rootSheet = this->rootSheet();
		this->visit([&rootSheet, destroy](Widget& widget) { rootSheet.handleUnbindWidget(widget, destroy); return true; });

		if(m_frame->mapped())
			m_parent->stripe().unmap(*m_frame);

		m_parent = nullptr;
		m_index = 0;
	}

	unique_ptr<Widget> Widget::extract()
	{
		unique_ptr<Widget> unique = m_container->release(*this, false);
		m_parent->destroy();
		return unique;
	}

	void Widget::destroy()
	{
		m_container->release(*this, true);
	}

	Widget* Widget::findContainer(Type& type)
	{
		Widget* widget = this->parent();

		while(widget)
		{
			if(&widget->type() == &type)
				return widget;
			widget = widget->parent();
		}

		return nullptr;
	}

	void Widget::visit(const Visitor& visitor)
	{
		visitor(*this);
	}

	void Widget::nextFrame(size_t tick, size_t step)
	{
		if(m_style->updated() > m_frame->styleStamp())
			m_frame->resetStyle();
	}

	void Widget::render(Renderer& renderer, bool force)
	{
		m_frame->content().beginDraw(renderer, force);
		m_frame->content().draw(renderer, force);
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
		m_style = &this->fetchStyle(m_type);
		m_frame->setStyle(*m_style);
	}

	void Widget::setStyle(Style& style, bool hard)
	{
		m_style = &style;
		m_frame->setStyle(*m_style, hard);
	}

	void Widget::setStyle(Type& type, bool hard)
	{
		this->setStyle(this->fetchStyle(type), hard);
	}

	Style& Widget::fetchStyle(Type& type)
	{
		return this->uiWindow().styler().style(type);
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
		m_frame->content().updateInkstyle(m_style->subskin(m_state));
		m_frame->setDirty(Frame::DIRTY_CONTENT);
	}
	
	Widget* Widget::pinpoint(float x, float y)
	{
		return this->pinpoint(x, y, [](Frame& frame) { return frame.opaque(); });
	}

	Widget* Widget::pinpoint(float x, float y, const Frame::Filter& filter)
	{
		Frame* frame = m_frame->pinpoint(x, y , filter);
		return frame ? frame->widget() : nullptr;
	}

	InputReceiver* Widget::controlEvent(InputEvent& inputEvent)
	{
		if(m_controlGraph)
			return m_controlGraph->controlEvent(inputEvent);

		if(inputEvent.deviceType >= DEVICE_MOUSE)
		{
			MouseEvent& mouseEvent = static_cast<MouseEvent&>(inputEvent);
			DimFloat local = m_frame->localPosition(mouseEvent.posX, mouseEvent.posY);
			Widget* pinned = this->pinpoint(local.x(), local.y());
			return (pinned && pinned != this) ? pinned->controlEvent(inputEvent) : this;
		}

		return this;
	}

	InputReceiver* Widget::receiveEvent(InputEvent& inputEvent)
	{
		if(inputEvent.consumed)
			return this;

		inputEvent.visited.push_back(this);

		if(inputEvent.deviceType >= DEVICE_MOUSE)
		{
			MouseEvent& mouseEvent = static_cast<MouseEvent&>(inputEvent);
			DimFloat local = m_frame->localPosition(mouseEvent.posX, mouseEvent.posY);
			mouseEvent.relativeX = local.x();
			mouseEvent.relativeY = local.y();
		}

		return InputAdapter::receiveEvent(inputEvent);
	}

	void Widget::makeActive()
	{
		this->uiWindow().makeActive(*this);
	}

	void Widget::giveControl(InputReceiver& receiver, ControlMode mode, DeviceType device)
	{
		bool control = this->rootController().takeControl(*this, receiver, mode, device);
		if(!control)
			m_controlGraph = make_unique<ControlNode>(receiver, nullptr, mode, device);
	}

	void Widget::takeControl(ControlMode mode, DeviceType device)
	{
		this->rootController().takeControl(*this, mode, device);
	}

	void Widget::yieldControl()
	{
		this->propagateTo(m_parent);
		this->rootController().yieldControl(*this);

		if(m_controlGraph)
			m_controlGraph = nullptr;
	}

	void Widget::control(bool modal)
	{
		this->enableState(CONTROL);
		if(modal)
			this->enableState(MODAL);
	}

	void Widget::uncontrol(bool modal)
	{
		this->disableState(CONTROL);
		if(modal)
			this->disableState(MODAL);
	}

	bool Widget::mouseEntered(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		this->enableState(FOCUSED);
		return false;
	}

	bool Widget::mouseLeaved(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		this->disableState(FOCUSED);
		return false;
	}

	bool Widget::mousePressed(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		this->enableState(TRIGGERED);
		return true;
	}

	bool Widget::mouseReleased(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		this->disableState(TRIGGERED);
		return true;
	}

	void Widget::dirtyLayout()
	{}

	void Widget::debugPrintDepth()
	{
		Widget* parent = this->parent();
		while(parent)
		{
			printf("  ");
			parent = parent->parent();
		}
	}

	Item::Item(Wedge& parent, Type& type)
		: Widget(parent, type)
	{}

	Control::Control(Wedge& parent, Type& type)
		: Item(parent, type)
	{}
}
