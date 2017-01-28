//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_WNODE_H
#define TOY_WNODE_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Widget/Cursor.h>
#include <toyui/Widget/Button.h>

namespace toy
{
	class TOY_UI_EXPORT Plan : public Sheet
	{
	public:
		Plan();

		void updateBounds();

		static StyleType& cls() { static StyleType ty("Plan", Sheet::cls()); return ty; }
	
	protected:
		BoxFloat m_bounds;
	};

	class TOY_UI_EXPORT Canvas : public ScrollSheet
	{
	public:
		Canvas(const string& title, Trigger contextTrigger = Trigger());

		const string& name();

		void nextFrame(size_t tick, size_t delta);

		Widget& vappend(unique_ptr<Widget> widget);

		void rightClick(MouseEvent& mouseEvent);
		void mouseWheel(MouseEvent& mouseEvent);

		static StyleType& cls() { static StyleType ty("Canvas", Sheet::cls()); return ty; }

	protected:
		string m_name;
		Trigger m_contextTrigger;
		Plan& m_plan;
	};

	class TOY_UI_EXPORT NodePlugKnob : public Widget
	{
	public:
		NodePlugKnob();

		static StyleType& cls() { static StyleType ty("NodePlugKnob", Sheet::cls()); return ty; }
	};

	class TOY_UI_EXPORT NodePlug : public Sheet
	{
	public:
		typedef std::function<void(NodePlug&, NodePlug&)> ConnectTrigger;

	public:
		NodePlug(const string& name, bool input, ConnectTrigger onConnect = ConnectTrigger());

		const string& tooltip() { return m_tooltip; }

		bool input() { return m_input; }

		void setTooltip(const string& tooltip) { m_tooltip = tooltip; }

		Sheet& canvas();

		void leftDragStart(MouseEvent& mouseEvent);
		void leftDrag(MouseEvent& mouseEvent);
		void leftDragEnd(MouseEvent& mouseEvent);

		void connect(NodePlug& plug);
		void disconnect(NodePlug& plug);

		void disconnectOut(NodePlug& plugOut);
		void connectOut(NodePlug& plugOut);

		static StyleType& cls() { static StyleType ty("NodePlug", Sheet::cls()); return ty; }

	protected:
		string m_name;
		string m_tooltip;
		bool m_input;
		Label& m_title;
		NodePlugKnob& m_knob;

		ConnectTrigger m_onConnect;

		NodeCable* m_cableProxy;

		std::vector<NodeCable*> m_cables;
	};

	class TOY_UI_EXPORT NodeInPlug : public NodePlug
	{
	public:
		NodeInPlug(const string& name);
	};

	class TOY_UI_EXPORT NodeOutPlug : public NodePlug
	{
	public:
		NodeOutPlug(const string& name, ConnectTrigger onConnect = ConnectTrigger());
	};

	class TOY_UI_EXPORT NodeCable : public Widget
	{
	public:
		NodeCable(Widget& plugOut, Widget& plugIn);

		Widget& plugOut() { return m_plugOut; }
		Widget& plugIn() { return m_plugIn; }

		void customDraw(Renderer& renderer);

		static StyleType& cls() { static StyleType ty("NodeCable", Sheet::cls()); return ty; }

	protected:
		Widget& m_plugOut;
		Widget& m_plugIn;
	};

	class TOY_UI_EXPORT NodeBody : public Sheet
	{
	public:
		NodeBody(Node& node);

		static StyleType& cls() { static StyleType ty("NodeBody", Sheet::cls()); return ty; }

	protected:
		Node& m_node;
		Label& m_title;
	};

	class TOY_UI_EXPORT NodeIn : public Sheet
	{
	public:
		NodeIn();

		static StyleType& cls() { static StyleType ty("NodeIn", Sheet::cls()); return ty; }
	};

	class TOY_UI_EXPORT NodeOut : public Sheet
	{
	public:
		NodeOut();

		static StyleType& cls() { static StyleType ty("NodeOut", Sheet::cls()); return ty; }
	};

	class TOY_UI_EXPORT Node : public LayerSheet
	{
	public:
		Node(const string& title);
		~Node();

		const string& name();

		NodeIn& inputs() { return m_inputs; }
		NodeOut& outputs() { return m_outputs; }
		NodeBody& body() { return m_body; }

		void leftClick(MouseEvent& mouseEvent);
		void rightClick(MouseEvent& mouseEvent);

		void leftDragStart(MouseEvent& mouseEvent);
		void leftDrag(MouseEvent& mouseEvent);
		void leftDragEnd(MouseEvent& mouseEvent);

		NodePlug& addInput(const string& name);
		NodePlug& addOutput(const string& name);

		Widget& vappend(unique_ptr<Widget> widget);
		//unique_ptr<Widget> vrelease(Widget& widget);

		static StyleType& cls() { static StyleType ty("Node", LayerSheet::cls()); return ty; }

	protected:
		string m_name;
		Widget* m_content;
		NodeIn& m_inputs;
		NodeBody& m_body;
		NodeOut& m_outputs;
	};
}

#endif
