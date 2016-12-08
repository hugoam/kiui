//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WNODE_H
#define MK_WNODE_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkButton.h>

namespace mk
{
	class MK_UI_EXPORT Canvas : public Sheet
	{
	public:
		Canvas(Trigger contextTrigger = Trigger());

		void rightClick(MouseEvent& mouseEvent);
		void mouseWheel(MouseEvent& mouseEvent);

		static StyleType& cls() { static StyleType ty("Canvas", Sheet::cls()); return ty; }

	protected:
		Trigger m_contextTrigger;
	};

	class MK_UI_EXPORT NodePlugKnob : public Widget
	{
	public:
		NodePlugKnob();

		static StyleType& cls() { static StyleType ty("NodePlugKnob", Sheet::cls()); return ty; }
	};

	class MK_UI_EXPORT NodePlug : public Sheet
	{
	public:
		typedef std::function<void(NodePlug&, NodePlug&)> ConnectTrigger;

	public:
		NodePlug(const string& name, bool input, ConnectTrigger onConnect = ConnectTrigger());

		bool input() { return m_input; }

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
		bool m_input;
		Label& m_title;
		NodePlugKnob& m_knob;

		ConnectTrigger m_onConnect;

		NodePlug* m_connectProxy;

		std::vector<NodeCable*> m_cables;
	};

	class MK_UI_EXPORT NodeInPlug : public NodePlug
	{
	public:
		NodeInPlug(const string& name);
	};

	class MK_UI_EXPORT NodeOutPlug : public NodePlug
	{
	public:
		NodeOutPlug(const string& name, ConnectTrigger onConnect = ConnectTrigger());
	};

	class MK_UI_EXPORT NodeCable : public Widget
	{
	public:
		NodeCable(NodePlug& plugOut, NodePlug& plugIn);

		NodePlug& plugOut() { return m_plugOut; }
		NodePlug& plugIn() { return m_plugIn; }

		void customDraw(Renderer& renderer);

		static StyleType& cls() { static StyleType ty("NodeCable", Sheet::cls()); return ty; }

	protected:
		NodePlug& m_plugOut;
		NodePlug& m_plugIn;
	};

	class MK_UI_EXPORT NodeBody : public Sheet
	{
	public:
		NodeBody(Node& node);

		static StyleType& cls() { static StyleType ty("NodeBody", Sheet::cls()); return ty; }

	protected:
		Node& m_node;
		Label& m_title;
	};

	class MK_UI_EXPORT NodeIn : public Sheet
	{
	public:
		NodeIn();

		static StyleType& cls() { static StyleType ty("NodeIn", Sheet::cls()); return ty; }
	};

	class MK_UI_EXPORT NodeOut : public Sheet
	{
	public:
		NodeOut();

		static StyleType& cls() { static StyleType ty("NodeOut", Sheet::cls()); return ty; }
	};

	class MK_UI_EXPORT Node : public LayerSheet
	{
	public:
		Node(const string& title, bool position = false, float x = 0.f, float y = 0.f);
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
