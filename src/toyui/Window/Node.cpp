//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Window/Node.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>
#include <toyui/Frame/Layer.h>

#include <toyui/Widget/RootSheet.h>

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
	{}

	void Canvas::rightClick(MouseEvent& mouseEvent)
	{
		m_contextTrigger(*this);
	}

	void Canvas::autoLayout()
	{
		NodeTable nodeTable;
		this->collectNodes(nodeTable);
		this->layoutNodes(nodeTable);
	}

	void Canvas::collectNodes(NodeTable& nodeTable)
	{
		std::vector<Node*> nodeVector;

		m_plan.visit([&nodeVector](Widget& widget) {
			if(&widget.type() == &Node::cls())
				nodeVector.push_back(&widget.as<Node>());
			return true;
		});

		int minIndex = 0;
		int maxIndex = 0;
		for(Node* node : nodeVector)
		{
			minIndex = std::min(minIndex, node->order());
			maxIndex = std::max(maxIndex, node->order());
		}

		int shift = -std::min(0, minIndex);

		nodeTable.resize(maxIndex + shift + 1);
		for(Node* node : nodeVector)
			nodeTable[node->order() + shift].push_back(node);
	}

	void Canvas::layoutNodes(const NodeTable& nodeTable)
	{
		unique_ptr<CanvasLine> line = make_unique<CanvasLine>(*this, m_plan.stripe());
		std::vector<unique_ptr<CanvasColumn>> columns;
		for(size_t i = 0; i < nodeTable.size(); ++i)
		{
			columns.emplace_back(make_unique<CanvasColumn>(*this, *line));
			for(Node* node : nodeTable[i])
				columns[i]->append(node->frame());
		}

		Style& nodeStyle = this->fetchStyle(Node::cls());

		nodeStyle.layout().d_flow = FLOW;
		line->relayout();
		nodeStyle.layout().d_flow = FREE;

		m_plan.stripe().remove(*line);
	}

	NodePlugKnob::NodePlugKnob(Wedge& parent)
		: Item(parent, cls())
	{}
	
	NodeConnectionProxy::NodeConnectionProxy(Wedge& parent)
		: Decal(parent, cls())
	{}

	NodePlug::NodePlug(Wedge& parent, Node& node, const string& name, bool input, ConnectTrigger onConnect)
		: WrapControl(parent, cls())
		, m_node(node)
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

	void NodePlug::leftDragStart(MouseEvent& mouseEvent)
	{
		DimFloat local = m_node.plan().frame().localPosition(mouseEvent.posX, mouseEvent.posY);

		m_connectionProxy = &m_node.plan().emplace<NodeConnectionProxy>();
		m_connectionProxy->frame().setPosition(local.x(), local.y());

		if(m_input)
			m_cableProxy = &m_node.plan().emplace<NodeCable>(*m_connectionProxy, *this);
		else
			m_cableProxy = &m_node.plan().emplace<NodeCable>(*this, *m_connectionProxy);
	}

	void NodePlug::leftDrag(MouseEvent& mouseEvent)
	{
		DimFloat local = m_node.plan().frame().localPosition(mouseEvent.posX, mouseEvent.posY);
		m_connectionProxy->frame().setPosition(local.x(), local.y());
	}

	void NodePlug::leftDragEnd(MouseEvent& mouseEvent)
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

		m_node.plan().release(*m_connectionProxy);
		m_node.plan().release(*m_cableProxy);
	}

	NodeCable& NodePlug::connect(NodePlug& plugIn, bool notify)
	{
		NodeCable& cable = m_node.plan().emplace<NodeCable>(*this, plugIn);
		m_cables.push_back(&cable);

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
				m_node.plan().release(*cable);
				return;
			}
	}

	NodeInPlug::NodeInPlug(Wedge& parent, Node& node, const string& name)
		: NodePlug(parent, node, name, true)
	{}

	NodeOutPlug::NodeOutPlug(Wedge& parent, Node& node, const string& name, ConnectTrigger onConnect)
		: NodePlug(parent, node, name, false, onConnect)
	{}

	NodeCable::NodeCable(Wedge& parent, Widget& plugOut, Widget& plugIn)
		: Decal(parent, cls())
		, m_plugOut(plugOut)
		, m_plugIn(plugIn)
	{}

	void NodeCable::nextFrame(size_t tick, size_t delta)
	{
		if(m_plugOut.frame().layer().redraw() || m_plugIn.frame().layer().redraw())
			m_frame->setDirty(Frame::DIRTY_POSITION);

		Widget::nextFrame(tick, delta);
	}

	bool NodeCable::customDraw(Renderer& renderer)
	{
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

	Node::~Node()
	{}

	Canvas& Node::canvas()
	{
		return *this->findContainer<Canvas>();
	}

	Container& Node::plan()
	{
		return this->canvas().plan();
	}

	std::vector<Node*> Node::inputNodes()
	{
		std::vector<Node*> inputs;
		for(Widget* widget : m_inputs.contents())
			for(NodeCable* cable : widget->as<NodePlug>().cables())
				inputs.push_back(&cable->plugOut().as<NodePlug>().node());
		return inputs;
	}

	std::vector<Node*> Node::outputNodes()
	{
		std::vector<Node*> outputs;
		for(Widget* widget : m_outputs.contents())
			for(NodeCable* cable : widget->as<NodePlug>().cables())
				outputs.push_back(&cable->plugIn().as<NodePlug>().node());
		return outputs;
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
		return m_inputs.emplace<NodeInPlug>(*this, name);
	}

	NodePlug& Node::addOutput(const string& name)
	{
		return m_outputs.emplace<NodeOutPlug>(*this, name);
	}
}
