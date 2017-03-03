//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Window/Node.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>
#include <toyui/Frame/Layer.h>

#include <toyui/Widget/RootSheet.h>

using namespace std::placeholders;

namespace toy
{
	Canvas::Canvas(Wedge& parent, const string& title, Trigger contextTrigger)
		: ScrollPlan(parent, cls())
		, m_name(title)
		, m_contextTrigger(contextTrigger)
	{}

	const string& Canvas::name()
	{
		return m_name;
	}

	void Canvas::rightClick(MouseEvent& mouseEvent)
	{
		m_contextTrigger(*this);
	}

	NodePlugKnob::NodePlugKnob(Wedge& parent)
		: Item(parent, cls())
	{}

	NodeConnectionProxy::NodeConnectionProxy(Wedge& parent)
		: Decal(parent, cls())
	{}

	NodePlug::NodePlug(Wedge& parent, const string& name, bool input, ConnectTrigger onConnect)
		: WrapControl(parent, cls())
		, m_name(name)
		, m_input(input)
		, m_title(*this, m_name)
		, m_knob(*this)
		, m_onConnect(onConnect)
		, m_cableProxy(nullptr)
	{
		if(input)
			this->swap(0, 1);
	}

	Canvas& NodePlug::canvas()
	{
		Wedge& node = *this->parent()->parent();
		Canvas& canvas = node.container()->as<Canvas>();
		return canvas;
	}

	void NodePlug::leftDragStart(MouseEvent& mouseEvent)
	{
		mouseEvent.abort = true;

		DimFloat local = this->canvas().frame().localPosition(mouseEvent.posX, mouseEvent.posY);

		m_connectionProxy = &this->canvas().emplace<NodeConnectionProxy>();
		m_connectionProxy->frame().setPosition(local.x(), local.y());

		if(m_input)
			m_cableProxy = &this->canvas().emplace<NodeCable>(*m_connectionProxy, *this);
		else
			m_cableProxy = &this->canvas().emplace<NodeCable>(*this, *m_connectionProxy);
	}

	void NodePlug::leftDrag(MouseEvent& mouseEvent)
	{
		mouseEvent.abort = true;

		DimFloat local = this->canvas().container().frame().localPosition(mouseEvent.posX, mouseEvent.posY);
		m_connectionProxy->frame().setPosition(local.x(), local.y());
	}

	void NodePlug::leftDragEnd(MouseEvent& mouseEvent)
	{
		mouseEvent.abort = true;

		Widget* widget = this->rootSheet().pinpoint(mouseEvent.posX, mouseEvent.posY);
		while(widget && &widget->type() != &NodePlug::cls())
			widget = widget->parent();

		if(widget)
		{
			NodePlug& plug = widget->as<NodePlug>();
			this->connect(plug);
		}

		this->canvas().release(*m_connectionProxy);
		this->canvas().release(*m_cableProxy);
	}

	void NodePlug::connect(NodePlug& plug)
	{
		if(plug.m_input && !m_input)
			this->connectOut(plug);
		else if(!plug.m_input && m_input)
			plug.connectOut(*this);
	}


	void NodePlug::disconnect(NodePlug& plug)
	{
		if(plug.m_input && !m_input)
			this->disconnectOut(plug);
		else if(!plug.m_input && m_input)
			plug.disconnectOut(*this);
	}

	void NodePlug::connectOut(NodePlug& plugIn)
	{
		Wedge& node = *this->parent()->parent();
		Container& canvas = *node.container();
		m_cables.push_back(&canvas.emplace<NodeCable>(*this, plugIn));

		if(m_onConnect)
			m_onConnect(*this, plugIn);
	}

	void NodePlug::disconnectOut(NodePlug& plugIn)
	{
		for(NodeCable* cable : m_cables)
			if(&cable->plugIn() == &plugIn)
			{
				m_cables.erase(std::find(m_cables.begin(), m_cables.end(), cable));
				Wedge& node = *this->parent()->parent();
				Container& canvas = *node.container();
				canvas.release(*cable);
				return;
			}
	}

	NodeInPlug::NodeInPlug(Wedge& parent, const string& name)
		: NodePlug(parent, name, true)
	{}

	NodeOutPlug::NodeOutPlug(Wedge& parent, const string& name, ConnectTrigger onConnect)
		: NodePlug(parent, name, false, onConnect)
	{}

	NodeCable::NodeCable(Wedge& parent, Widget& plugOut, Widget& plugIn)
		: Decal(parent, cls())
		, m_plugOut(plugOut)
		, m_plugIn(plugIn)
	{}

	void NodeCable::nextFrame(size_t tick, size_t delta)
	{
		m_frame->setDirty(Frame::DIRTY_POSITION);
		Widget::nextFrame(tick, delta);
	}

	bool NodeCable::customDraw(Renderer& renderer)
	{
		//m_frame->debugPrintDepth();
		//printf("Drawing cable\n");
		Wedge& canvas = *this->parent();

		Frame& frameCanvas = canvas.frame();
		Frame& frameOut = m_plugOut.frame();
		Frame& frameIn = m_plugIn.frame();

		DimFloat relativeOut = frameOut.relativePosition(frameCanvas);
		float x1 = relativeOut[DIM_X] + frameOut.width();
		float y1 = relativeOut[DIM_Y] + frameOut.height() / 2;

		float c1x = x1 + 100.f;
		float c1y = y1;

		DimFloat relativeIn = frameIn.relativePosition(frameCanvas);
		float x2 = relativeIn[DIM_X];
		float y2 = relativeIn[DIM_Y] + frameIn.height() / 2;

		float c2x = x2 - 100.f;
		float c2y = y2;

		renderer.pathBezier(x1, y1, c1x, c1y, c2x, c2y, x2, y2);
		renderer.stroke(this->content().inkstyle());

		return true;
	}

	NodeBody::NodeBody(Node& node)
		: Container(node, cls())
		, m_node(node)
		, m_title(*this, m_node.name())
	{}

	NodeIn::NodeIn(Wedge& parent)
		: Container(parent, cls())
	{}

	NodeOut::NodeOut(Wedge& parent)
		: Container(parent, cls())
	{}

	Node::Node(Wedge& parent, const string& title)
		: Overlay(parent, cls())
		, m_name(title)
		, m_inputs(*this)
		, m_body(*this)
		, m_outputs(*this)
	{}

	Node::~Node()
	{}

	Container& Node::emplaceContainer()
	{
		return m_body;
	}

	void Node::leftClick(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		m_frame->as<Layer>().moveToTop();
	}

	void Node::rightClick(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		m_frame->as<Layer>().moveToTop();
	}

	void Node::leftDragStart(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		m_frame->layer().moveToTop();
	}

	void Node::leftDrag(MouseEvent& mouseEvent)
	{
		float scale = m_frame->absoluteScale();
		m_frame->setPosition(m_frame->dposition(DIM_X) + mouseEvent.deltaX / scale, m_frame->dposition(DIM_Y) + mouseEvent.deltaY / scale);
	}

	void Node::leftDragEnd(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
	}

	NodePlug& Node::addInput(const string& name)
	{
		return m_inputs.emplace<NodeInPlug>(name);
	}

	NodePlug& Node::addOutput(const string& name)
	{
		return m_outputs.emplace<NodeOutPlug>(name);
	}
}
