//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Scheme/Node.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>
#include <toyui/Frame/Layer.h>

#include <toyui/Widget/RootSheet.h>

#include <iostream>

using namespace std::placeholders;

namespace toy
{
	Plan::Plan()
		: Sheet(cls())
	{}

	void Plan::updateBounds()
	{
		float margin = 50.f;

		m_bounds.clear();

		for(Frame* frame : m_frame->as<Stripe>().contents())
		{
			m_bounds[DIM_X] = std::min(frame->dposition(DIM_X) - margin, m_bounds[DIM_X]);
			m_bounds[DIM_Y] = std::min(frame->dposition(DIM_Y) - margin, m_bounds[DIM_Y]);
			m_bounds[DIM_XX] = std::max(frame->dposition(DIM_X) + frame->dsize(DIM_X) + margin, m_bounds[DIM_XX]);
			m_bounds[DIM_YY] = std::max(frame->dposition(DIM_Y) + frame->dsize(DIM_Y) + margin, m_bounds[DIM_YY]);
		}

		//m_frame->setPosition(m_bounds.x(), m_bounds.y());
		m_frame->setSize(m_bounds.x1() - m_bounds.x0(), m_bounds.y1() - m_bounds.y0());
	}

	Canvas::Canvas(const string& title, Trigger contextTrigger)
		: ScrollSheet(cls())
		, m_name(title)
		, m_contextTrigger(contextTrigger)
		, m_plan(this->makeappend<Plan>())
	{}

	const string& Canvas::name()
	{
		return m_name;
	}

	void Canvas::nextFrame(size_t tick, size_t delta)
	{
		m_plan.updateBounds();

		ScrollSheet::nextFrame(tick, delta);
	}

	Widget& Canvas::vappend(unique_ptr<Widget> widget)
	{
		return m_plan.append(std::move(widget));
	}

	void Canvas::rightClick(MouseEvent& mouseEvent)
	{
		m_contextTrigger(*this);
	}

	void Canvas::mouseWheel(MouseEvent& mouseEvent)
	{
		return;
		 
		DimFloat position = m_plan.frame().position();
		float scale = m_plan.frame().scale();
		float deltaScale = mouseEvent.deltaZ * 0.01f * scale;
		scale += deltaScale;
		m_plan.frame().setScale(scale);

		DimFloat deltaSize = m_plan.frame().size();
		deltaSize[DIM_X] *= deltaScale;
		deltaSize[DIM_Y] *= deltaScale;

		DimFloat mousePos(mouseEvent.posX - m_plan.frame().dabsolute(DIM_X), mouseEvent.posY - m_plan.frame().dabsolute(DIM_Y));
		DimFloat halfSize(m_plan.frame().dsize(DIM_X) * 0.5f, m_plan.frame().dsize(DIM_Y) * 0.5f);

		DimFloat deltaCenter((mousePos[DIM_X] - halfSize[DIM_X]) / halfSize[DIM_X], (mousePos[DIM_Y] - halfSize[DIM_Y]) / halfSize[DIM_Y]);

		std::cerr << "Mouse Pos : " << mousePos[DIM_X] << ", " << mousePos[DIM_Y] << std::endl;
		std::cerr << "Half Size : " << halfSize[DIM_X] << ", " << halfSize[DIM_Y] << std::endl;
		std::cerr << "Delta Center: " << deltaCenter[DIM_X] << ", " << deltaCenter[DIM_Y] << std::endl;

		m_plan.frame().setPosition(position[DIM_X] - deltaSize[DIM_X] * 0.5f * deltaCenter[DIM_X], position[DIM_Y] - deltaSize[DIM_Y] * 0.5f * deltaCenter[DIM_Y]);
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
		, m_cableProxy(nullptr)
	{
		if(input)
			this->swap(0, 1);
	}

	Sheet& NodePlug::canvas()
	{
		Sheet& node = *this->parent()->parent();
		Sheet& canvas = *node.parent();
		return canvas;
	}

	void NodePlug::leftDragStart(MouseEvent& mouseEvent)
	{
		mouseEvent.abort = true;

		Cursor& cursor = this->rootSheet().cursor();

		if(m_input)
			m_cableProxy = &this->canvas().emplace<NodeCable>(cursor, *this);
		else
			m_cableProxy = &this->canvas().emplace<NodeCable>(*this, cursor);
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
		Sheet& node = *this->parent()->parent();
		Sheet& canvas = *node.parent();
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
				Sheet& node = *this->parent()->parent();
				Sheet& canvas = *node.parent();
				canvas.release(*cable);
				return;
			}
	}

	NodeInPlug::NodeInPlug(const string& name)
		: NodePlug(name, true)
	{}

	NodeOutPlug::NodeOutPlug(const string& name, ConnectTrigger onConnect)
		: NodePlug(name, false, onConnect)
	{}

	NodeCable::NodeCable(Widget& plugOut, Widget& plugIn)
		: Widget(cls())
		, m_plugOut(plugOut)
		, m_plugIn(plugIn)
	{}

	void NodeCable::customDraw(Renderer& renderer)
	{
		Sheet& canvas = *this->parent();

		Frame& frameCanvas = canvas.frame();
		Frame& frameOut = m_plugOut.frame();
		Frame& frameIn = m_plugIn.frame();

		float x1 = frameOut.right() - frameCanvas.left();
		float y1 = frameOut.top() + frameOut.height() / 2 - frameCanvas.top();

		float c1x = x1 + 100.f;
		float c1y = y1;

		float x2 = frameIn.left() - frameCanvas.left();
		float y2 = frameIn.top() + frameIn.height() / 2 - frameCanvas.top();

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

	Node::Node(const string& title)
		: LayerSheet(cls())
		, m_name(title)
		, m_content(nullptr)
		, m_inputs(this->makeappend<NodeIn>())
		, m_body(this->makeappend<NodeBody>(*this))
		, m_outputs(this->makeappend<NodeOut>())
	{}

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
