//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_NODE_H
#define TOY_NODE_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Widget/ScrollSheet.h>
#include <toyui/Widget/Cursor.h>
#include <toyui/Widget/Layout.h>
#include <toyui/Button/Button.h>

/* std */
#include <set>

namespace toy
{
	class TOY_UI_EXPORT NodePlugKnob : public Item
	{
	public:
		NodePlugKnob(Wedge& parent);

		static Type& cls() { static Type ty("NodePlugKnob", Item::cls()); return ty; }
	};

	class TOY_UI_EXPORT NodeConnectionProxy : public Decal
	{
	public:
		NodeConnectionProxy(Wedge& parent);

		static Type& cls() { static Type ty("NodeConnectionProxy", Decal::cls()); return ty; }
	};

	class TOY_UI_EXPORT NodePlug : public WrapControl
	{
	public:
		typedef std::function<void(NodePlug&, NodePlug&)> ConnectTrigger;

	public:
		NodePlug(Wedge& parent, Node& node, const string& name, bool input, ConnectTrigger onConnect = ConnectTrigger());
	
		Node& node() { return m_node; }
		const string& tooltip() { return m_tooltip; }
		bool input() { return m_input; }

		std::vector<NodeCable*>& cables() { return m_cables; }

		void setTooltip(const string& tooltip) { m_tooltip = tooltip; }

		virtual void leftDragStart(MouseEvent& mouseEvent);
		virtual void leftDrag(MouseEvent& mouseEvent);
		virtual void leftDragEnd(MouseEvent& mouseEvent);

		NodeCable& connect(NodePlug& plugOut, bool notify = true);
		void disconnect(NodePlug& plugOut);

		static Type& cls() { static Type ty("NodePlug", WrapControl::cls()); return ty; }

	protected:
		Node& m_node;
		string m_name;
		string m_tooltip;
		bool m_input;
		Label m_title;
		NodePlugKnob m_knob;

		ConnectTrigger m_onConnect;

		NodeConnectionProxy* m_connectionProxy;
		NodeCable* m_cableProxy;

		std::vector<NodeCable*> m_cables;
	};

	class TOY_UI_EXPORT NodeInPlug : public NodePlug
	{
	public:
		NodeInPlug(Wedge& parent, Node& node, const string& name);
	};

	class TOY_UI_EXPORT NodeOutPlug : public NodePlug
	{
	public:
		NodeOutPlug(Wedge& parent, Node& node, const string& name, ConnectTrigger onConnect = ConnectTrigger());
	};

	class TOY_UI_EXPORT NodeCable : public Decal
	{
	public:
		NodeCable(Wedge& parent, Widget& plugOut, Widget& plugIn);

		void nextFrame(size_t tick, size_t delta);

		Widget& plugOut() { return m_plugOut; }
		Widget& plugIn() { return m_plugIn; }

		bool customDraw(Renderer& renderer);

		static Type& cls() { static Type ty("NodeCable", Decal::cls()); return ty; }

	protected:
		Widget& m_plugOut;
		Widget& m_plugIn;
	};

	class TOY_UI_EXPORT NodeHeader : public Row
	{
	public:
		NodeHeader(Wedge& parent, Node& node);

		static Type& cls() { static Type ty("NodeHeader", Row::cls()); return ty; }

	protected:
		Label m_title;
		Spacer m_spacer;
	};

	class TOY_UI_EXPORT NodeBody : public Sheet
	{
	public:
		NodeBody(Node& parent);

		NodeHeader& header() { return m_header; }

		static Type& cls() { static Type ty("NodeBody", Sheet::cls()); return ty; }

	protected:
		NodeHeader m_header;
	};

	class TOY_UI_EXPORT NodeIn : public Div
	{
	public:
		NodeIn(Wedge& parent);

		static Type& cls() { static Type ty("NodeIn", Div::cls()); return ty; }
	};

	class TOY_UI_EXPORT NodeOut : public Div
	{
	public:
		NodeOut(Wedge& parent);

		static Type& cls() { static Type ty("NodeOut", Div::cls()); return ty; }
	};

	class TOY_UI_EXPORT Node : public Overlay
	{
	public:
		Node(Wedge& parent, const string& title, int order = 0);
		~Node();

		Canvas& canvas();
		Container& plan();

		const string& name() { return m_name; }
		int order() { return m_order; }

		NodeIn& inputs() { return m_inputs; }
		NodeOut& outputs() { return m_outputs; }
		NodeBody& body() { return m_body; }

		std::vector<Node*> inputNodes();
		std::vector<Node*> outputNodes();

		virtual void leftClick(MouseEvent& mouseEvent);
		virtual void rightClick(MouseEvent& mouseEvent);

		virtual void leftDragStart(MouseEvent& mouseEvent);
		virtual void leftDrag(MouseEvent& mouseEvent);
		virtual void leftDragEnd(MouseEvent& mouseEvent);

		NodePlug& addInput(const string& name);
		NodePlug& addOutput(const string& name);

		static Type& cls() { static Type ty("Node", Overlay::cls()); return ty; }

	protected:
		string m_name;
		int m_order;

		NodeIn m_inputs;
		NodeBody m_body;
		NodeOut m_outputs;
	};
	class TOY_UI_EXPORT CanvasLine : public Stripe
	{
	public:
		CanvasLine(Widget& widget, Stripe& parent);

		static Type& cls() { static Type ty("CanvasLine"); return ty; }
	};

	class TOY_UI_EXPORT CanvasColumn : public Stripe
	{
	public:
		CanvasColumn(Widget& widget, Stripe& parent);

		static Type& cls() { static Type ty("CanvasColumn"); return ty; }
	};

	class TOY_UI_EXPORT Canvas : public ScrollPlan
	{
	public:
		Canvas(Wedge& parent, const string& title, const Callback& contextTrigger = nullptr);

		void rightClick(MouseEvent& mouseEvent);

		void autoLayout();

		typedef std::vector<std::vector<Node*>> NodeTable;

		void collectNodes(NodeTable& nodes);
		void layoutNodes(const NodeTable& nodes);

		static Type& cls() { static Type ty("Canvas", ScrollSheet::cls()); return ty; }

	protected:
		string m_name;
		Callback m_contextTrigger;
	};
}

#endif
