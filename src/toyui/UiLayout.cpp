//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/UiLayout.h>

#include <toyui/UiWindow.h>

#include <toyui/Bundle.h>

namespace toy
{
	Styler::Styler(UiWindow& uiWindow)
		: m_uiWindow(uiWindow)
	{}

	Styler::~Styler()
	{}
	
	void Styler::clear()
	{
		m_styledefs.clear();

		for(auto& kv : m_styles)
			kv.second->clear();

		this->defaultLayout();

		for(StyleInitializer& initializer : m_initializers)
			initializer(*this);
	}

	void Styler::reset()
	{
		for(auto& kv : m_styles)
			this->prepareStyle(*kv.second);

		m_uiWindow.m_rootSheet->visit([](Widget& widget, bool&) {
			widget.frame().updateStyle(true);
		});
	}

	Style& Styler::styledef(const string& name)
	{
		if(m_styledefs[name] == nullptr)
			m_styledefs[name] = make_object<Style>(name);
		return *m_styledefs[name];
	}

	Style& Styler::styledef(Type& type)
	{
		return styledef(type.name());
	}

	Style& Styler::style(Type& type)
	{
		if(m_styles[type.name()] == nullptr)
			this->initStyle(type);
		return *m_styles[type.name()];
	}

	void Styler::initStyle(Type& type)
	{
		object_ptr<Style> style = make_object<Style>(type, type.base() ? &this->style(*type.base()) : nullptr);
		this->prepareStyle(*style);

		m_styles[type.name()] = std::move(style);
	}

	void Styler::prepareStyle(Style& style)
	{
		if(style.m_base)
			this->prepareStyle(*style.m_base);

		style.prepare(m_styledefs[style.name()].get());
	}

	void Styler::defaultLayout()
	{
		this->styledef(Widget::cls()).m_layout.d_solver = FRAME_SOLVER;
		this->styledef(Wedge::cls()).m_layout.d_solver = ROW_SOLVER;
		this->styledef(ScrollSheet::cls()).m_layout.d_solver = GRID_SOLVER;
		this->styledef(Table::cls()).m_layout.d_solver = TABLE_SOLVER;
		
		this->styledef(RootSheet::cls()).m_layout.d_space = BOARD;
		this->styledef(RootSheet::cls()).m_layout.d_clipping = CLIP;
		this->styledef(RootSheet::cls()).m_layout.d_opacity = OPAQUE;

		this->styledef(Cursor::cls()).m_layout.d_zorder = -1;
		this->styledef(Tooltip::cls()).m_layout.d_zorder = -2;

		// LAYOUT
		this->styledef(Wedge::Board()).m_layout.d_space = { READING, EXPAND, EXPAND };
		this->styledef(Wedge::Board()).m_layout.d_clipping = CLIP;
		this->styledef(Tab::cls()).m_layout.d_clipping = CLIP;
		this->styledef(Window::Body()).m_layout.d_clipping = CLIP;

		this->styledef(Wedge::Layout()).m_layout.d_space = { PARAGRAPH, EXPAND, EXPAND };

		this->styledef(GridSheet::cls()).m_layout.d_opacity = OPAQUE;

		// SHEET
		this->styledef(Wedge::Sheet()).m_layout.d_space = SHEET;

		// OVERLAYS
		this->styledef(Wedge::Decal()).m_layout.d_flow = FREE;
		this->styledef(Wedge::Decal()).m_layout.d_space = BLOCK;

		this->styledef(NodeKnob::Proxy()).m_layout.d_flow = FREE;

		this->styledef(Wedge::Overlay()).m_layout.d_flow = FREE;
		this->styledef(Wedge::Overlay()).m_layout.d_space = UNIT;
		this->styledef(Wedge::Overlay()).m_layout.d_opacity = OPAQUE;

		this->styledef(Rectangle::cls()).m_layout.d_space = BLOCK;
		this->styledef(NodeCable::cls()).m_layout.d_space = BLOCK;

		this->styledef(Node::cls()).m_layout.d_space = { READING, SHRINK, SHRINK };

		// LAYERS
		this->styledef(Slider::Display()).m_layout.d_flow = OVERLAY;
		this->styledef(Slider::Knob()).m_layout.d_flow = OVERLAY;

		this->styledef(Scrollbar::Knob()).m_layout.d_flow = FLOW;

		// CONTAINERS
		this->styledef(Wedge::cls()).m_layout.d_space = SHEET;

		this->styledef(ScrollSheet::cls()).m_layout.d_opacity = OPAQUE;
		this->styledef(ScrollPlan::cls()).m_layout.d_opacity = OPAQUE;

		this->styledef(Window::cls()).m_layout.d_space = BLOCK;

		this->styledef(Window::DockWindow()).m_layout.d_flow = FLOW;
		this->styledef(Window::DockWindow()).m_layout.d_space = SHEET;

		this->styledef(Dockbox::cls()).m_layout.d_flow = FLOW;
		this->styledef(Dockbox::cls()).m_layout.d_space = { PARAGRAPH, WRAP, FIXED };

		// BLOCKS
		this->styledef(Window::WrapWindow()).m_layout.d_space = UNIT;
		
		// SPACER
		this->styledef(Item::Spacer()).m_layout.d_space = SPACER;

		this->styledef(Scrollbar::Scroller()).m_layout.d_space = FLEX;

		this->styledef(Item::Filler()).m_layout.d_space = FLEX;
		this->styledef(Slider::cls()).m_layout.d_space = FLEX;

		this->styledef(Slider::Knob()).m_layout.d_space = FLEX;

		// LINE
		this->styledef(Wedge::Row()).m_layout.d_space = LINE;

		// ALIGNED
		this->styledef(Dropdown::List()).m_layout.d_flow = ALIGN;
		this->styledef(Dropdown::List()).m_layout.d_align = { LEFT, OUT_RIGHT };
		this->styledef(Menu::List()).m_layout.d_align = { LEFT, OUT_RIGHT };
		this->styledef(Menu::SubList()).m_layout.d_align = { OUT_RIGHT, LEFT };

		// DIVS
		this->styledef(Wedge::Div()).m_layout.d_space = DIV;
		this->styledef(Table::Head()).m_layout.d_space = DIV;
		
		this->styledef(Docker::cls()).m_layout.d_space = SPACER;

		// STACKS
		this->styledef(Wedge::Stack()).m_layout.d_space = STACK;
		this->styledef(Text::cls()).m_layout.d_space = { PARAGRAPH, FIXED, WRAP };

		// CONTROLS
		this->styledef(Item::cls()).m_layout.d_space = BLOCK;
		this->styledef(Input<bool>::cls()).m_layout.d_space = ITEM;

		this->styledef(Item::Control()).m_layout.d_opacity = OPAQUE;
		this->styledef(TypeIn::cls()).m_layout.d_opacity = OPAQUE;
		
		this->styledef(Wedge::WrapControl()).m_layout.d_space = LINE;
		this->styledef(Wedge::WrapControl()).m_layout.d_opacity = OPAQUE;

		this->styledef(Table::ColumnHeader()).m_layout.d_space = LINE;

		this->styledef(Menu::cls()).m_layout.d_space = ITEM;

		// EDITORS
		this->styledef(Textbox::cls()).m_layout.d_space = BOARD;

		this->styledef(Canvas::cls()).m_layout.d_space = BOARD;
		this->styledef(Canvas::cls()).m_layout.d_opacity = OPAQUE;
		this->styledef(Canvas::cls()).m_layout.d_clipping = CLIP;

		this->styledef(ScrollPlan::Plan()).m_layout.d_space = BLOCK;
		this->styledef(ScrollPlan::Plan()).m_skin.m_customRenderer = &drawGrid;

		this->styledef(Toolbar::cls()).m_layout.d_space = ITEM;

		this->styledef(Dockspace::cls()).m_layout.d_opacity = OPAQUE;

		// GEOMETRY

		//this->styledef(WindowFooter::cls()).m_layout.d_space = { READING, WRAP, FIXED };
		this->styledef(WindowFooter::SizerLeft()).m_layout.d_space = { READING, WRAP, FIXED };
		this->styledef(WindowFooter::SizerRight()).m_layout.d_space = { READING, WRAP, FIXED };

		this->styledef(Dockbar::cls()).m_layout.d_align = { RIGHT, RIGHT };

		this->styledef(Docker::cls()).m_layout.d_flow = ALIGN;
		this->styledef(Docker::cls()).m_layout.d_align = { LEFT, OUT_LEFT };

		this->styledef(Popup::cls()).m_layout.d_size = { 280.f, 350.f };

		this->styledef(Dockbox::cls()).m_layout.d_size = { 300.f, 0.f };

		this->styledef(ScrollSheet::ScrollZone()).m_layout.d_layout = { AUTO_SIZE, AUTO_SIZE };
		this->styledef(ScrollSheet::ScrollZone()).m_layout.d_clipping = CLIP;


		this->styledef(Item::Control()).m_layout.d_align = { LEFT, CENTER };
		this->styledef(Button::cls()).m_layout.d_align = { LEFT, CENTER };
		this->styledef(Window::CloseButton()).m_layout.d_align = { RIGHT, CENTER };

		this->styledef(Canvas::LayoutLine()).m_layout.d_space = ITEM;
		this->styledef(Canvas::LayoutColumn()).m_layout.d_space = UNIT;

		this->styledef(Canvas::LayoutLine()).m_layout.d_padding = BoxFloat(20.f);
		this->styledef(Canvas::LayoutLine()).m_layout.d_spacing = DimFloat(100.f);

		this->styledef(Canvas::LayoutColumn()).m_layout.d_padding = BoxFloat(20.f);
		this->styledef(Canvas::LayoutColumn()).m_layout.d_spacing = DimFloat(20.f);

		this->styledef(NodeKnob::cls()).m_layout.d_size = { 10.f, 22.f };

		this->styledef(Wedge::Header()).m_layout.d_padding = BoxFloat(6.f);

		this->styledef(WrapButton::cls()).m_layout.d_spacing = DimFloat(2.f);
		this->styledef(MultiButton::cls()).m_layout.d_padding = BoxFloat(2.f);

		this->styledef(Dropdown::Head()).m_layout.d_padding = BoxFloat(2.f);

		this->styledef(Dockbar::cls()).m_layout.d_padding = BoxFloat(4.f);
		this->styledef(Dockbar::cls()).m_layout.d_spacing = DimFloat(4.f);

		this->styledef(Toolbar::cls()).m_layout.d_padding = BoxFloat(6.f);
		this->styledef(Toolbar::cls()).m_layout.d_spacing = DimFloat(6.f);
		this->styledef(Menubar::cls()).m_layout.d_spacing = DimFloat(6.f);
		
		this->styledef(GridSheet::cls()).m_layout.d_spacing = DimFloat(5.f);

		this->styledef(Tab::cls()).m_layout.d_padding = BoxFloat(6.f);
		this->styledef(Docksection::DockTab()).m_layout.d_padding = BoxFloat(0.f);

		//this->styledef(GridSubdiv::cls()).m_layout.d_spacing = DimFloat(6.f);
		this->styledef(Dockspace::cls()).m_layout.d_spacing = DimFloat(6.f);

		this->styledef(Expandbox::Body()).m_layout.d_padding = { 12.f, 2.f, 0.f, 2.f };
		this->styledef(Expandbox::Body()).m_layout.d_spacing = DimFloat(6.f);

		//this->styledef(Surface::cls()).m_layout.d_margin = DimFloat(1000.f);

		this->styledef(TreeNode::Body()).m_layout.d_padding = { 18.f, 0.f, 0.f, 0.f };
		this->styledef(TreeNode::Body()).m_layout.d_spacing = DimFloat(0.f);

		this->styledef(Table::cls()).m_layout.d_spacing = DimFloat(0.f, 2.f);

		this->styledef(WindowHeader::Movable()).m_skin.m_hoverCursor = &Cursor::Move();
		this->styledef(Dockline::DocklineX()).m_skin.m_hoverCursor = &Cursor::ResizeX();
		this->styledef(Dockline::DocklineY()).m_skin.m_hoverCursor = &Cursor::ResizeY();
		this->styledef(WindowFooter::SizerLeft()).m_skin.m_hoverCursor = &Cursor::ResizeDiagLeft();
		this->styledef(WindowFooter::SizerRight()).m_skin.m_hoverCursor = &Cursor::ResizeDiagRight();

		this->styledef(Cursor::cls()).m_skin.m_image = &m_uiWindow.findImage("mousepointer");

		this->styledef(Cursor::ResizeX()).m_skin.m_image = &m_uiWindow.findImage("resize_h_20");
		this->styledef(Cursor::ResizeX()).m_skin.m_padding = { -10.f, -10.f, +10.f, +10.f };
		this->styledef(Cursor::ResizeY()).m_skin.m_image = &m_uiWindow.findImage("resize_v_20");
		this->styledef(Cursor::ResizeY()).m_skin.m_padding = { -10.f, -10.f, +10.f, +10.f };
		this->styledef(Cursor::Move()).m_skin.m_image = &m_uiWindow.findImage("move_20");
		this->styledef(Cursor::Move()).m_skin.m_padding = { -10.f, -10.f, +10.f, +10.f };
		this->styledef(Cursor::ResizeDiagLeft()).m_skin.m_image = &m_uiWindow.findImage("resize_diag_left_20");
		this->styledef(Cursor::ResizeDiagLeft()).m_skin.m_padding = { -10.f, -10.f, +10.f, +10.f };
		this->styledef(Cursor::ResizeDiagRight()).m_skin.m_image = &m_uiWindow.findImage("resize_diag_right_20");
		this->styledef(Cursor::ResizeDiagRight()).m_skin.m_padding = { -10.f, -10.f, +10.f, +10.f };
		this->styledef(Cursor::Caret()).m_skin.m_image = &m_uiWindow.findImage("caret_white");
		this->styledef(Cursor::Caret()).m_skin.m_padding = { -4.f, -9.f, +4.f, +9.f };

		this->styledef(Toolbar::Mover()).m_skin.m_image = &m_uiWindow.findImage("handle");

		this->styledef(Text::cls()).m_skin.m_textWrap = true;
		this->styledef(Textbox::cls()).m_skin.m_textWrap = true;

		this->styledef(Item::cls()).m_skin.m_empty = false;
		this->styledef(Item::cls()).m_skin.m_textColour = Colour::White;
		this->styledef(Item::cls()).m_skin.m_padding = BoxFloat(2.f);

		this->styledef(Figure::cls()).m_skin.m_empty = false;

		this->styledef(ScrollPlan::Plan()).m_skin.m_borderWidth = BoxFloat(2.f);
		this->styledef(ScrollPlan::Plan()).m_skin.m_borderColour = Colour::AlphaGrey;

		this->styledef(Rectangle::cls()).m_skin.m_borderWidth = BoxFloat(1.f);
		this->styledef(Rectangle::cls()).m_skin.m_borderColour = Colour::Cyan;

		this->styledef(Docksection::Placeholder()).m_skin.m_backgroundColour = Colour::Blue;
	}
}
