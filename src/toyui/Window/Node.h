//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_NODE_H
#define TOY_NODE_H

/* toy */
#include <toyobj/Store/Array.h>
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Container/ScrollSheet.h>
#include <toyui/Widget/Cursor.h>
#include <toyui/Container/Layout.h>
#include <toyui/Button/Button.h>

/* std */
#include <set>

namespace toy
{
	class TOY_UI_EXPORT NodeKnob : public Item
	{
	public:
		NodeKnob(Wedge& parent, const Colour& colour = Colour::White);

		const Colour& colour() { return m_colour; }
		void setColour(const Colour& colour) { m_colour = colour; }

		bool customDraw(Renderer& renderer);

		static Type& cls() { static Type ty("NodeKnob", Item::cls()); return ty; }

	protected:
		Colour m_colour;
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
		NodePlug(Wedge& parent, Node& node, const string& name, const string& icon, bool input, ConnectTrigger onConnect = ConnectTrigger());
	
		Node& node() { return m_node; }
		const string& tooltip() { return m_tooltip; }
		bool input() { return m_input; }
		NodeKnob& knob() { return m_knob; }

		std::vector<NodeCable*>& cables() { return m_cables; }

		void setTooltip(const string& tooltip) { m_tooltip = tooltip; }

		virtual bool leftDragStart(MouseEvent& mouseEvent);
		virtual bool leftDrag(MouseEvent& mouseEvent);
		virtual bool leftDragEnd(MouseEvent& mouseEvent);

		NodeCable& connect(NodePlug& plugOut, bool notify = true);
		void disconnect(NodePlug& plugOut);

		static Type& cls() { static Type ty("NodePlug", WrapControl::cls()); return ty; }

	protected:
		Node& m_node;
		string m_tooltip;
		bool m_input;
		Label m_title;
		Icon m_icon;
		NodeKnob m_knob;

		ConnectTrigger m_onConnect;

		NodeConnectionProxy* m_connectionProxy;
		NodeCable* m_cableProxy;

		std::vector<NodeCable*> m_cables;
	};

	class TOY_UI_EXPORT NodeCable : public Decal
	{
	public:
		NodeCable(Wedge& parent, Widget& plugOut, Widget& plugIn);

		Widget& plugOut() { return m_plugOut; }
		Widget& plugIn() { return m_plugIn; }

		void updateCable();

		bool customDraw(Renderer& renderer);

		static Type& cls() { static Type ty("NodeCable", Decal::cls()); return ty; }

	protected:
		Widget& m_plugOut;
		Widget& m_plugIn;
		bool m_flipX;
		bool m_flipY;
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

		Canvas& canvas();
		Container& plan();

		const string& name() { return m_name; }
		int order() { return m_order; }

		NodeIn& inputs() { return m_inputs; }
		NodeOut& outputs() { return m_outputs; }
		NodeBody& body() { return m_body; }

		void moveNode(const DimFloat& delta);
		void updateCables();

		void select();
		void unselect();

		virtual bool leftClick(MouseEvent& mouseEvent);
		virtual bool rightClick(MouseEvent& mouseEvent);

		virtual bool leftDragStart(MouseEvent& mouseEvent);

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

	class TOY_UI_EXPORT Canvas : public ScrollPlan, public StoreObserver<Node>
	{
	public:
		Canvas(Wedge& parent, const string& title, const Callback& contextTrigger = nullptr);

		Array<Node>& selection() { return m_selection; }

		virtual bool leftClick(MouseEvent& mouseEvent);
		virtual bool rightClick(MouseEvent& mouseEvent);

		virtual bool leftDragStart(MouseEvent& mouseEvent);
		virtual bool leftDrag(MouseEvent& mouseEvent);
		virtual bool leftDragEnd(MouseEvent& mouseEvent);

		void autoLayout();

		void collectNodes(std::vector<Node*>& nodes);
		void layoutNodes(const std::vector<Node*>& nodes);

		void handleAdd(Node& node);
		void handleRemove(Node& node);

		static Type& cls() { static Type ty("Canvas", ScrollSheet::cls()); return ty; }

	protected:
		string m_name;
		Callback m_contextTrigger;

		Array<Node> m_selection;
	};
}

#endif
