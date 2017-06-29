//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Window/Node.h>

#include <toyui/Frame/Layer.h>
#include <toyui/Widget/RootSheet.h>

#include <toyui/Render/Renderer.h>

namespace toy
{
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

		/*object_ptr<Stripe> line = make_object<Stripe>(*this, m_plan.frame());
		std::vector<object_ptr<Stripe>> columns;

		for(int i = 0; i < maxIndex+shift+1; ++i)
			columns.emplace_back(make_object<Stripe>(*this, *line));

		for(Node* node : nodes)
			columns[node->order() + shift]->append(node->frame());

		Style& nodeStyle = this->fetchStyle(Node::cls());

		nodeStyle.layout().d_flow = FLOW;
		line->relayout();
		nodeStyle.layout().d_flow = FREE;

		for(Node* node : nodes)
			node->updateCables();

		m_plan.frame().remove(*line);
		
		
		*/
	}

	/*
		//this->styledef(CanvasLine::cls()).layout().d_space = ITEM;

		//this->styledef(CanvasColumn::cls()).layout().d_space = BLOCK;

		/*this->styledef(CanvasLine::cls()).layout().d_padding = BoxFloat(20.f);
		this->styledef(CanvasLine::cls()).layout().d_spacing = DimFloat(100.f);

		this->styledef(CanvasColumn::cls()).layout().d_padding = BoxFloat(20.f);
		this->styledef(CanvasColumn::cls()).layout().d_spacing = DimFloat(20.f);
		*/

	bool Canvas::leftDragStart(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		return true;
	}

	bool Canvas::leftDrag(MouseEvent& mouseEvent)
	{
		for(Node* node : m_selection.store())
			node->moveNode(mouseEvent.delta);
		return true;
	}

	bool Canvas::leftDragEnd(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		return true;
	}

	NodeKnob::NodeKnob(Wedge& parent, const Colour& colour, Type& type)
		: Item(parent, type)
		, m_colour(colour)
	{}

	bool NodeKnob::customDraw(Renderer& renderer)
	{
		InkStyle inkstyle;
		inkstyle.m_backgroundColour = m_colour;

		float radius = 5.f;
		renderer.pathCircle(m_frame->d_size.x() / 2.f, m_frame->d_size.y() / 2.f, radius);
		renderer.fill(inkstyle, BoxFloat());

		return true;
	}

	NodePlug::NodePlug(Wedge& parent, Node& node, const string& name, const string& icon, const Colour& colour, bool input, ConnectTrigger onConnect)
		: Wedge(parent, cls())
		, m_node(node)
		, m_input(input)
		, m_title(*this, name)
		, m_icon(*this, icon)
		, m_knob(*this, colour)
		, m_onConnect(onConnect)
		, m_cableProxy(nullptr)
	{
		if(input)
			this->swap(0, 2);
	}

	bool NodePlug::leftDragStart(MouseEvent& mouseEvent)
	{
		m_connectionProxy = &m_node.plan().emplace<NodeKnob>(Colour::None, NodeKnob::Proxy());
		m_cableProxy = &m_node.plan().emplace<NodeCable>((m_input ? *m_connectionProxy : m_knob), (m_input ? m_knob : *m_connectionProxy));
		return true;
	}

	bool NodePlug::leftDrag(MouseEvent& mouseEvent)
	{
		DimFloat local = m_node.plan().frame().localPosition(mouseEvent.pos);
		m_connectionProxy->frame().setPosition(local);
		m_cableProxy->updateCable();
		return true;
	}

	bool NodePlug::leftDragEnd(MouseEvent& mouseEvent)
	{
		Widget* target = this->rootSheet().pinpoint(mouseEvent.pos);
		NodePlug* plug = target->findContainer<NodePlug>();

		if(plug && plug->m_input != m_input)
			m_input ? plug->connect(*this) : this->connect(*plug);

		m_connectionProxy->extract();
		m_cableProxy->extract();
		return true;
	}

	NodeCable& NodePlug::connect(NodePlug& plugIn, bool notify)
	{
		NodeCable& cable = m_node.plan().emplace<NodeCable>(m_knob, plugIn.knob());
		m_cables.push_back(&cable);
		plugIn.m_cables.push_back(&cable);

		if(notify && m_onConnect)
			m_onConnect(*this, plugIn);

		return cable;
	}

	void NodePlug::disconnect(NodePlug& plugIn)
	{
		for(NodeCable* cable : m_cables)
			if(&cable->knobIn() == &plugIn.knob())
			{
				vector_remove(m_cables, cable);
				cable->extract();
				return;
			}
	}

	NodeCable::NodeCable(Wedge& parent, NodeKnob& knobOut, NodeKnob& knobIn)
		: Wedge(parent, cls())
		, m_knobOut(knobOut)
		, m_knobIn(knobIn)
	{
		this->updateCable();
	}

	void NodeCable::updateCable()
	{
		Frame& frameCanvas = this->parent()->frame();

		DimFloat relativeOut = m_knobOut.frame().derivePosition(DimFloat(), frameCanvas);
		DimFloat relativeIn = m_knobIn.frame().derivePosition(DimFloat(), frameCanvas);

		float x0 = relativeOut.x() + m_knobOut.frame().d_size.x();
		float y0 = relativeOut.y() + m_knobOut.frame().d_size.y() / 2;
		float x1 = relativeIn.x();
		float y1 = relativeIn.y() + m_knobIn.frame().d_size.y() / 2;

		m_flipX = x1 > x0;
		m_flipY = y1 > y0;

		m_frame->setPosition({ m_flipX ? x0 : x1, m_flipY ? y0 : y1 });
		m_frame->setSize({ m_flipX ? x1 - x0 : x0 - x1, m_flipY ? y1 - y0 : y0 - y1 });
	}

	bool NodeCable::customDraw(Renderer& renderer)
	{
		float x0 = m_flipX ? 0.f : m_frame->d_size.x();
		float y0 = m_flipY ? 0.f : m_frame->d_size.y();
		float x1 = m_flipX ? m_frame->d_size.x() : 0.f;
		float y1 = m_flipY ? m_frame->d_size.y() : 0.f;

		Paint paint(m_knobOut.colour(), m_knobIn.colour());
		paint.m_width = 1.f;
		renderer.pathBezier(x0, y0, x0 + 100.f, y0, x1 - 100.f, y1, x1, y1);
		renderer.strokeGradient(paint, DimFloat(m_flipX ? x0 : x1, m_flipY ? y0 : y1), DimFloat(m_flipX ? x1 : x0,  m_flipY ? y1 : y0));

		return true;
	}

	NodeHeader::NodeHeader(Wedge& parent, Node& node)
		: Wedge(parent, cls())
		, m_title(*this, node.name())
		, m_spacer(*this, Item::Spacer())
	{}

	Node::Node(Wedge& parent, const string& title, int order)
		: Wedge(parent, cls(), LAYER)
		, m_name(title)
		, m_order(order)
		, m_inputs(*this, Node::Inputs())
		, m_body(*this, Node::Body())
		, m_header(m_body, *this)
		, m_outputs(*this, Node::Outputs())
	{}

	Canvas& Node::canvas()
	{
		return *this->findContainer<Canvas>();
	}

	Wedge& Node::plan()
	{
		return this->canvas().plan();
	}

	void Node::moveNode(const DimFloat& delta)
	{
		DimFloat position = m_frame->d_position + delta / m_frame->absoluteScale();
		m_frame->setPosition(position);
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

	NodePlug& Node::addInput(const string& name, const string& icon, const Colour& colour)
	{
		return m_inputs.emplace<NodePlug>(*this, name, icon, colour, true);
	}

	NodePlug& Node::addOutput(const string& name, const string& icon, const Colour& colour)
	{
		return m_outputs.emplace<NodePlug>(*this, name, icon, colour, false);
	}

	NodePlug& Node::addPlug(const string& name, const string& icon, const Colour& colour, bool input, NodePlug::ConnectTrigger onConnect)
	{
		if(input)
			return m_inputs.emplace<NodePlug>(*this, name, icon, colour, true, onConnect);
		else
			return m_outputs.emplace<NodePlug>(*this, name, icon, colour, false, onConnect);
	}
}
