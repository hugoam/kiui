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
#include <toyui/Button/Button.h>

namespace toy
{
	class TOY_UI_EXPORT NodeKnob : public Item
	{
	public:
		NodeKnob(Wedge& parent, const Colour& colour = Colour::NeonGreen, Type& type = cls());

		const Colour& colour() { return m_colour; }
		void setColour(const Colour& colour) { m_colour = colour; }

		bool customDraw(Renderer& renderer);

		static Type& cls() { static Type ty("NodeKnob", Item::cls()); return ty; }

		static Type& Proxy() { static Type ty("NodeKnobProxy", NodeKnob::cls()); return ty; }

	protected:
		Colour m_colour;
	};

	class TOY_UI_EXPORT NodePlug : public Wedge
	{
	public:
		using ConnectTrigger = std::function<void(NodePlug&, NodePlug&)>;

	public:
		NodePlug(Wedge& parent, Node& node, const string& name, const string& icon, const Colour& colour, bool input, ConnectTrigger onConnect = ConnectTrigger());
	
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

		static Type& cls() { static Type ty("NodePlug", Wedge::WrapControl()); return ty; }

	protected:
		Node& m_node;
		string m_tooltip;
		bool m_input;
		Label m_title;
		Item m_icon;
		NodeKnob m_knob;

		ConnectTrigger m_onConnect;

		NodeKnob* m_connectionProxy;
		NodeCable* m_cableProxy;

		std::vector<NodeCable*> m_cables;
	};

	class TOY_UI_EXPORT NodeCable : public Wedge
	{
	public:
		NodeCable(Wedge& parent, NodeKnob& plugOut, NodeKnob& plugIn);

		NodeKnob& knobOut() { return m_knobOut; }
		NodeKnob& knobIn() { return m_knobIn; }

		void updateCable();

		bool customDraw(Renderer& renderer);

		static Type& cls() { static Type ty("NodeCable", Wedge::Decal()); return ty; }

	protected:
		NodeKnob& m_knobOut;
		NodeKnob& m_knobIn;
		bool m_flipX;
		bool m_flipY;
	};

	class TOY_UI_EXPORT NodeHeader : public Wedge
	{
	public:
		NodeHeader(Wedge& parent, Node& node);

		static Type& cls() { static Type ty("NodeHeader", Wedge::Row()); return ty; }

	protected:
		Label m_title;
		Item m_spacer;
	};

	class TOY_UI_EXPORT Node : public Wedge
	{
	public:
		Node(Wedge& parent, const string& title, int order = 0);

		Canvas& canvas();
		Wedge& plan();

		void moveNode(const DimFloat& delta);
		void updateCables();

		void select();
		void unselect();

		virtual bool leftClick(MouseEvent& mouseEvent);
		virtual bool rightClick(MouseEvent& mouseEvent);

		virtual bool leftDragStart(MouseEvent& mouseEvent);

		NodePlug& addInput(const string& name, const string& icon = "", const Colour& colour = Colour::NeonGreen);
		NodePlug& addOutput(const string& name, const string& icon = "", const Colour& colour = Colour::NeonGreen);

		NodePlug& addPlug(const string& name, const string& icon, const Colour& colour, bool input, NodePlug::ConnectTrigger onConnect = {});
		
		static Type& cls() { static Type ty("Node", Wedge::Overlay()); return ty; }

		static Type& Inputs() { static Type ty("NodeIn", Wedge::Div()); return ty; }
		static Type& Body() { static Type ty("NodeBody", Wedge::Sheet()); return ty; }
		static Type& Outputs() { static Type ty("NodeOut", Wedge::Div()); return ty; }

	public:
		string m_name;
		int m_order;

	public:
		Wedge m_inputs;
		Wedge m_body;
		NodeHeader m_header;
		Wedge m_outputs;
	};

	class TOY_UI_EXPORT Canvas : public ScrollPlan, public StoreObserver<Node>
	{
	public:
		Canvas(Wedge& parent, const string& title, const Callback& contextTrigger = nullptr);

		Array<Node>& selection() { return m_selection; }

		virtual bool leftClick(MouseEvent& mouseEvent);
		virtual bool rightClick(MouseEvent& mouseEvent);

		virtual bool leftDrag(MouseEvent& mouseEvent);

		void autoLayout();
		void autoLayoutSelected();

		void collectNodes(std::vector<Node*>& nodes);
		void layoutNodes(const std::vector<Node*>& nodes);

		void handleAdd(Node& node);
		void handleRemove(Node& node);

		static Type& cls() { static Type ty("Canvas", ScrollSheet::cls()); return ty; }

		static Type& LayoutLine() { static Type ty("CanvasLine", Item::cls()); return ty; }
		static Type& LayoutColumn() { static Type ty("CanvasColumn", Item::cls()); return ty; }
		static Type& LayoutNode() { static Type ty("CanvasNode", Item::cls()); return ty; }

	protected:
		string m_name;
		Callback m_contextTrigger;

		Array<Node> m_selection;
	};
}

#endif
