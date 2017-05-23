//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Window/Node.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>
#include <toyui/Frame/Layer.h>

#include <toyui/Widget/RootSheet.h>
#include <toyui/Input/InputDevice.h>

namespace toy
{
	CanvasLine::CanvasLine(Widget& widget, Stripe& parent)
		: Stripe(widget.fetchStyle(cls()), parent)
	{}

	CanvasColumn::CanvasColumn(Widget& widget, Stripe& parent)
		: Stripe(widget.fetchStyle(cls()), parent)
	{}


	Canvas::Canvas(Wedge& parent, const string& title, const Callback& contextTrigger)
		: ScrollPlan(parent, cls())
		, m_name(title)
		, m_contextTrigger(contextTrigger)
	{
		m_selection.observe(*this);
	}

	void Canvas::handleAdd(Node& node)
	{
		node.select();
	}

	void Canvas::handleRemove(Node& node)
	{
		node.unselect();
	}

	bool Canvas::leftClick(MouseEvent& mouseEvent)
	{
		m_selection.clear();
		return true;
	}

	bool Canvas::rightClick(MouseEvent& mouseEvent)
	{
		if(m_contextTrigger)
			m_contextTrigger(*this);
		return true;
	}

	void Canvas::autoLayout()
	{
		std::vector<Node*> nodes;
		this->collectNodes(nodes);
		this->layoutNodes(nodes);
	}

	void Canvas::collectNodes(std::vector<Node*>& nodes)
	{
		m_plan.visit([&nodes](Widget& widget) {
			if(&widget.type() == &Node::cls())
				nodes.push_back(&widget.as<Node>());
			return true;
		});
	}

	void Canvas::layoutNodes(const std::vector<Node*>& nodes)
	{
		int minIndex = 0;
		int maxIndex = 0;
		for(Node* node : nodes)
		{
			minIndex = std::min(minIndex, node->order());
			maxIndex = std::max(maxIndex, node->order());
		}

		int shift = -std::min(0, minIndex);

		unique_ptr<CanvasLine> line = make_unique<CanvasLine>(*this, m_plan.stripe());
		std::vector<unique_ptr<CanvasColumn>> columns;

		for(int i = 0; i < maxIndex+shift+1; ++i)
			columns.emplace_back(make_unique<CanvasColumn>(*this, *line));

		for(Node* node : nodes)
			columns[node->order() + shift]->append(node->frame());

		Style& nodeStyle = this->fetchStyle(Node::cls());

		nodeStyle.layout().d_flow = FLOW;
		line->relayout();
		nodeStyle.layout().d_flow = FREE;

		for(Node* node : nodes)
			node->updateCables();

		m_plan.stripe().remove(*line);
	}

	bool Canvas::leftDragStart(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		return true;
	}

	bool Canvas::leftDrag(MouseEvent& mouseEvent)
	{
		for(Node* node : m_selection.store())
			node->moveNode(DimFloat(mouseEvent.deltaX, mouseEvent.deltaY));
		return true;
	}

	bool Canvas::leftDragEnd(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		return true;
	}

	NodeKnob::NodeKnob(Wedge& parent, const Colour& colour)
		: Item(parent, cls())
		, m_colour(0.f,1.f,0.2f)
	{}

	bool NodeKnob::customDraw(Renderer& renderer)
	{
		InkStyle inkstyle;
		inkstyle.m_backgroundColour = m_colour;

		float radius = 5.f;
		renderer.pathCircle(m_frame->size().x() / 2.f, m_frame->size().y() / 2.f, radius);
		renderer.fill(inkstyle, BoxFloat());

		return true;
	}

	NodeConnectionProxy::NodeConnectionProxy(Wedge& parent)
		: Decal(parent, cls())
	{}

	NodePlug::NodePlug(Wedge& parent, Node& node, const string& name, const string& icon, bool input, ConnectTrigger onConnect)
		: WrapControl(parent, cls())
		, m_node(node)
		, m_input(input)
		, m_title(*this, name)
		, m_icon(*this, icon)
		, m_knob(*this)
		, m_onConnect(onConnect)
		, m_cableProxy(nullptr)
	{
		if(input)
			this->swap(0, 2);
	}

	bool NodePlug::leftDragStart(MouseEvent& mouseEvent)
	{
		DimFloat local = m_node.plan().frame().localPosition(mouseEvent.posX, mouseEvent.posY);

		m_connectionProxy = &m_node.plan().emplace<NodeConnectionProxy>();
		m_connectionProxy->frame().setPosition(local.x(), local.y());

		if(m_input)
			m_cableProxy = &m_node.plan().emplace<NodeCable>(*m_connectionProxy, *this);
		else
			m_cableProxy = &m_node.plan().emplace<NodeCable>(*this, *m_connectionProxy);

		return true;
	}

	bool NodePlug::leftDrag(MouseEvent& mouseEvent)
	{
		DimFloat local = m_node.plan().frame().localPosition(mouseEvent.posX, mouseEvent.posY);
		m_connectionProxy->frame().setPosition(local.x(), local.y());
		m_cableProxy->updateCable();
		return true;
	}

	bool NodePlug::leftDragEnd(MouseEvent& mouseEvent)
	{
		Widget* widget = this->rootSheet().pinpoint(mouseEvent.posX, mouseEvent.posY);
		while(widget && &widget->type() != &NodePlug::cls())
			widget = widget->parent();

		if(widget)
		{
			NodePlug& plug = widget->as<NodePlug>();
			if(plug.m_input != m_input)
				m_input ? plug.connect(*this) : this->connect(plug);
		}

		m_connectionProxy->destroy();
		m_cableProxy->destroy();

		return true;
	}

	NodeCable& NodePlug::connect(NodePlug& plugIn, bool notify)
	{
		NodeCable& cable = m_node.plan().emplace<NodeCable>(*this, plugIn);
		m_cables.push_back(&cable);
		plugIn.m_cables.push_back(&cable);

		if(notify && m_onConnect)
			m_onConnect(*this, plugIn);

		return cable;
	}

	void NodePlug::disconnect(NodePlug& plugIn)
	{
		for(NodeCable* cable : m_cables)
			if(&cable->plugIn() == &plugIn)
			{
				m_cables.erase(std::find(m_cables.begin(), m_cables.end(), cable));
				cable->destroy();
				return;
			}
	}

	NodeCable::NodeCable(Wedge& parent, Widget& plugOut, Widget& plugIn)
		: Decal(parent, cls())
		, m_plugOut(plugOut)
		, m_plugIn(plugIn)
	{
		this->updateCable();
	}

	void NodeCable::updateCable()
	{
		Frame& frameCanvas = this->parent()->frame();

		DimFloat relativeOut = m_plugOut.frame().relativePosition(frameCanvas);
		DimFloat relativeIn = m_plugIn.frame().relativePosition(frameCanvas);

		float x0 = relativeOut.x() + m_plugOut.frame().width();
		float y0 = relativeOut.y() + m_plugOut.frame().height() / 2;
		float x1 = relativeIn.x();
		float y1 = relativeIn.y() + m_plugIn.frame().height() / 2;

		m_flipX = x1 > x0;
		m_flipY = y1 > y0;

		m_frame->setPosition(m_flipX ? x0 : x1, m_flipY ? y0 : y1);
		m_frame->setSize(m_flipX ? x1 - x0 : x0 - x1, m_flipY ? y1 - y0 : y0 - y1);
	}

	bool NodeCable::customDraw(Renderer& renderer)
	{
		float x0 = m_flipX ? 0.f : m_frame->size().x();
		float y0 = m_flipY ? 0.f : m_frame->size().y();
		float x1 = m_flipX ? m_frame->size().x() : 0.f;
		float y1 = m_flipY ? m_frame->size().y() : 0.f;

		Paint paint(m_plugOut.as<NodePlug>().knob().colour(), m_plugIn.as<NodePlug>().knob().colour());
		paint.m_width = 1.f;
		renderer.pathBezier(x0, y0, x0 + 100.f, y0, x1 - 100.f, y1, x1, y1);
		renderer.strokeGradient(paint, DimFloat(m_flipX ? x0 : x1, m_flipY ? y0 : y1), DimFloat(m_flipX ? x1 : x0,  m_flipY ? y1 : y0));

		return true;
	}

	NodeBody::NodeBody(Node& node)
		: Sheet(node, cls())
		, m_header(*this, node)
	{}

	NodeIn::NodeIn(Wedge& parent)
		: Div(parent, cls())
	{}

	NodeOut::NodeOut(Wedge& parent)
		: Div(parent, cls())
	{}

	NodeHeader::NodeHeader(Wedge& parent, Node& node)
		: Row(parent, cls())
		, m_title(*this, node.name())
		, m_spacer(*this)
	{}

	Node::Node(Wedge& parent, const string& title, int order)
		: Overlay(parent, cls())
		, m_name(title)
		, m_order(order)
		, m_inputs(*this)
		, m_body(*this)
		, m_outputs(*this)
	{
		m_containerTarget = &m_body;
	}

	Canvas& Node::canvas()
	{
		return *this->findContainer<Canvas>();
	}

	Container& Node::plan()
	{
		return this->canvas().plan();
	}

	void Node::moveNode(const DimFloat& delta)
	{
		float scale = m_frame->absoluteScale();
		m_frame->setPosition(m_frame->position().x() + delta.x() / scale, m_frame->position().y() + delta.y() / scale);

		this->updateCables();
	}

	void Node::updateCables()
	{
		for(Widget* widget : m_inputs.contents())
			for(NodeCable* cable : widget->as<NodePlug>().cables())
				cable->updateCable();

		for(Widget* widget : m_outputs.contents())
			for(NodeCable* cable : widget->as<NodePlug>().cables())
				cable->updateCable();
	}

	void Node::select()
	{
		m_frame->as<Layer>().moveToTop();
		this->enableState(SELECTED);
	}

	void Node::unselect()
	{
		this->disableState(SELECTED);
	}

	bool Node::leftClick(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		if(this->rootSheet().keyboard().shiftPressed())
			this->canvas().selection().swap(*this);
		else
			this->canvas().selection().select(*this);
		return true;
	}

	bool Node::rightClick(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		this->canvas().selection().select(*this);
		return true;
	}

	bool Node::leftDragStart(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		if(!this->canvas().selection().has(*this))
			this->canvas().selection().select(*this);
		return true;
	}

	NodePlug& Node::addInput(const string& name)
	{
		return m_inputs.emplace<NodePlug>(*this, name, "", true);
	}

	NodePlug& Node::addOutput(const string& name)
	{
		return m_outputs.emplace<NodePlug>(*this, name, "", false);
	}
}
