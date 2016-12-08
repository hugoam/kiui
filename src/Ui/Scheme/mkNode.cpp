//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Scheme/mkNode.h>

#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>
#include <Ui/Frame/mkLayer.h>

#include <Ui/Widget/mkRootSheet.h>

using namespace std::placeholders;

namespace mk
{
	Canvas::Canvas(Trigger contextTrigger)
		: Sheet(cls())
		, m_contextTrigger(contextTrigger)
	{}

	void Canvas::rightClick(MouseEvent& mouseEvent)
	{
		m_contextTrigger(*this);
	}

	void Canvas::mouseWheel(MouseEvent& mouseEvent)
	{

	}

	NodePlugKnob::NodePlugKnob()
		: Widget(cls())
	{}

	NodePlug::NodePlug(const string& name, bool input, ConnectTrigger onConnect)
		: Sheet(cls())
		, m_name(name)
		, m_input(input)
		, m_title(this->makeappend<Label>(m_name))
		, m_knob(this->makeappend<NodePlugKnob>())
		, m_onConnect(onConnect)
		, m_connectProxy(nullptr)
	{
		if(input)
			this->swap(0, 1);
	}

	void NodePlug::leftDragStart(MouseEvent& mouseEvent)
	{
		mouseEvent.abort = true;

		m_connectProxy = &this->rootSheet().cursor().emplace<NodePlug>("ProxyPlug", !m_input);
		m_connectProxy->hide();

		this->connect(*m_connectProxy);
	}

	void NodePlug::leftDrag(MouseEvent& mouseEvent)
	{
		mouseEvent.abort = true;
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

		this->disconnect(*m_connectProxy);
		this->rootSheet().cursor().release(*m_connectProxy);
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
		m_cables.push_back(&this->makeappend<NodeCable>(*this, plugIn));

		if(&plugIn != m_connectProxy && m_onConnect)
			m_onConnect(*this, plugIn);
	}

	void NodePlug::disconnectOut(NodePlug& plugIn)
	{
		for(NodeCable* cable : m_cables)
			if(&cable->plugIn() == &plugIn)
			{
				m_cables.erase(std::find(m_cables.begin(), m_cables.end(), cable));
				this->release(*cable);
				return;
			}
	}

	NodeInPlug::NodeInPlug(const string& name)
		: NodePlug(name, true)
	{}

	NodeOutPlug::NodeOutPlug(const string& name, ConnectTrigger onConnect)
		: NodePlug(name, false, onConnect)
	{}

	NodeCable::NodeCable(NodePlug& plugOut, NodePlug& plugIn)
		: Widget(cls())
		, m_plugOut(plugOut)
		, m_plugIn(plugIn)
	{}

	void NodeCable::customDraw(Renderer& renderer)
	{
		Frame& frameOut = m_plugOut.frame();
		Frame& frameIn = m_plugIn.frame();

		float x1 = frameOut.right();
		float y1 = frameOut.top() + frameOut.height() / 2;

		float c1x = x1 + 100.f;
		float c1y = y1;

		float x2 = frameIn.left();
		float y2 = frameIn.top() + frameIn.height() / 2;

		float c2x = x2 - 100.f;
		float c2y = y2;

		renderer.pathBezier(x1, y1, c1x, c1y, c2x, c2y, x2, y2);
		renderer.stroke(m_frame->inkstyle());
	}

	NodeBody::NodeBody(Node& node)
		: Sheet(cls())
		, m_node(node)
		, m_title(this->makeappend<Label>(m_node.name()))
	{}

	NodeIn::NodeIn()
		: Sheet(cls())
	{}

	NodeOut::NodeOut()
		: Sheet(cls())
	{}

	Node::Node(const string& title, bool position, float x, float y)
		: LayerSheet(cls())
		, m_name(title)
		, m_content(nullptr)
		, m_inputs(this->makeappend<NodeIn>())
		, m_body(this->makeappend<NodeBody>(*this))
		, m_outputs(this->makeappend<NodeOut>())
	{
		if(position)
			m_frame->setPosition(x, y);
	}

	Node::~Node()
	{}

	const string& Node::name()
	{
		return m_content ? m_content->name() : m_name;
	}

	Widget& Node::vappend(unique_ptr<Widget> widget)
	{
		//m_header.title().setLabel(widget->name());
		m_content = widget.get();
		return m_body.append(std::move(widget));
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
		m_frame->setPosition(m_frame->dposition(DIM_X) + mouseEvent.deltaX, m_frame->dposition(DIM_Y) + mouseEvent.deltaY);
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
