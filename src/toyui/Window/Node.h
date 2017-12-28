//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_NODE_H
#define TOY_NODE_H

/* toy */
#include <toyobj/Reflect/Member.h>
#include <toyobj/Store/Array.h>
#include <toyui/Types.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Container/ScrollSheet.h>
#include <toyui/Button/Button.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT NodeKnob : public Widget
	{
	public:
		NodeKnob(const Params& params, const Colour& colour = Colour::NeonGreen);

		bool customDraw(Renderer& renderer);

		Colour m_colour;
	};

	class _refl_ TOY_UI_EXPORT NodePlug : public Wedge
	{
	public:
		using ConnectTrigger = std::function<void(NodePlug&, NodePlug&)>;

	public:
		NodePlug(const Params& params, Node& node, const string& name, const string& icon, const Colour& colour, bool input, ConnectTrigger onConnect = ConnectTrigger());
	
		virtual const string& tooltip() { return m_tooltip; }

		virtual bool leftDragStart(MouseEvent& mouseEvent);
		virtual bool leftDrag(MouseEvent& mouseEvent);
		virtual bool leftDragEnd(MouseEvent& mouseEvent);

		NodeCable& connect(NodePlug& plugOut, bool notify = true);
		void disconnect(NodePlug& plugOut);

	public:
		Node& m_node;
		string m_tooltip;
		bool m_input;
		Label m_title;
		Widget m_icon;
		NodeKnob m_knob;

		std::vector<NodeCable*> m_cables;

		const ConnectTrigger m_onConnect;

	protected:
		NodeKnob* m_connectionProxy;
		NodeCable* m_cableProxy;
	};

	class _refl_ TOY_UI_EXPORT NodeCable : public Wedge
	{
	public:
		NodeCable(const Params& params, NodeKnob& plugOut, NodeKnob& plugIn);

		void updateCable();

		bool customDraw(Renderer& renderer);

	public:
		NodeKnob& m_knobOut;
		NodeKnob& m_knobIn;

	protected:
		bool m_flipX;
		bool m_flipY;
	};

	class _refl_ TOY_UI_EXPORT NodeHeader : public Wedge
	{
	public:
		NodeHeader(const Params& params, Node& node);

		Label m_title;
		Widget m_spacer;
	};

	class _refl_ TOY_UI_EXPORT Node : public Wedge
	{
	public:
		Node(const Params& params, const string& title, int order = 0);

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

		struct Styles
		{
			Style node = { cls<Node>(), Widget::styles().overlay, Args{ { &Layout::m_space, Space{ PARAGRAPH, SHRINK, SHRINK } } } };
			Style body = { "NodeBody", Widget::styles().sheet };
			Style plugs = { "NodePlugs", Widget::styles().sheet, Args{ { &Layout::m_space, Space{ READING, WRAP, WRAP } } } };
			Style inputs = { "NodeInputs", Widget::styles().div };
			Style outputs = { "NodeOutputs", Widget::styles().div, Args{ { &Layout::m_align, Dim<Align>{ RIGHT, CENTER } } } };
			Style knob = { cls<NodeKnob>(), Widget::styles().item, Args{ { &Layout::m_size, DimFloat{ 10.f, 22.f } }, { &InkStyle::m_background_colour, Colour::White } } };
			Style knob_output = { "NodeKnobOutput", knob, Args{ { &Layout::m_align, Dim<Align>{ RIGHT, CENTER } }, { &InkStyle::m_background_colour, Colour::White } } };
			Style knob_proxy = { "NodeKnobProxy", knob, Args{ { &Layout::m_flow, FREE } } };
			Style plug = { cls<NodePlug>(), Widget::styles().wrap_control };
			Style cable = { cls<NodeCable>(), Widget::styles().decal, Args{ { &Layout::m_space, BLOCK }, { &InkStyle::m_background_colour, Colour::White } } };
			Style header = { cls<NodeHeader>(), Widget::styles().row };

		}; static Styles& styles() { static Styles styles; return styles; }

	public:
		string m_name;
		int m_order;

	public:
		NodeHeader m_header;
		//Wedge m_body;
		Wedge m_plugs;
		Wedge m_inputs;
		Wedge m_outputs;
	};

	class _refl_ TOY_UI_EXPORT Canvas : public ScrollPlan, public StoreObserver<Node>
	{
	public:
		Canvas(const Params& params, const string& title, const Callback& contextTrigger = nullptr);

		Array<Node> m_selection;

		virtual bool leftClick(MouseEvent& mouseEvent);
		virtual bool rightClick(MouseEvent& mouseEvent);
		virtual bool middleClick(MouseEvent& mouseEvent);

		virtual bool leftDrag(MouseEvent& mouseEvent);

		void autoLayout();
		void autoLayoutSelected();

		void collectNodes(std::vector<Node*>& nodes);
		void layoutNodes(const std::vector<Node*>& nodes);

		void handleAdd(Node& node);
		void handleRemove(Node& node);

		struct Styles
		{
			Style canvas = { cls<Canvas>(), Widget::styles().scrollplan, Args{ { &Layout::m_space, LAYOUT }, { &Layout::m_opacity, OPAQUE }, { &Layout::m_clipping, CLIP } } };

			Style layout_line = { "CanvasLayoutLine", Widget::styles().item, Args{ { &Layout::m_space, ITEM }, { &Layout::m_padding, BoxFloat(20.f) }, { &Layout::m_spacing, DimFloat(100.f) } } };
			Style layout_column = { "CanvasLayoutColumn", Widget::styles().item, Args{ { &Layout::m_space, UNIT }, { &Layout::m_padding, BoxFloat(20.f) }, { &Layout::m_spacing, DimFloat(20.f) } } };
			Style layout_node = { "CanvasLayoutNode", Widget::styles().item };
		};
		static Styles& styles() { static Styles styles; return styles; }

	protected:
		string m_name;
		Callback m_contextTrigger;
	};
}

#endif
