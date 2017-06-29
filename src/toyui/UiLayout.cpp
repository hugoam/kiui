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

		m_uiWindow.rootSheet().visit([](Widget& widget) {
			widget.frame().updateStyle(true);
			return true;
		});
	}

	Style& Styler::styledef(const string& name)
	{
		if(m_styledefs[name] == nullptr)
			m_styledefs[name] = std::move(make_object<Style>(name));
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
		if(style.base())
			this->prepareStyle(*style.base());

		style.prepare(m_styledefs[style.name()].get());
	}

	void Styler::defaultLayout()
	{
		this->styledef(Widget::cls()).layout().d_solver = FRAME_SOLVER;
		this->styledef(Wedge::cls()).layout().d_solver = ROW_SOLVER;
		this->styledef(ScrollSheet::cls()).layout().d_solver = GRID_SOLVER;
		this->styledef(Table::cls()).layout().d_solver = TABLE_SOLVER;
		
		this->styledef(RootSheet::cls()).layout().d_space = BOARD;
		this->styledef(RootSheet::cls()).layout().d_clipping = CLIP;
		this->styledef(RootSheet::cls()).layout().d_opacity = OPAQUE;

		this->styledef(Cursor::cls()).layout().d_zorder = -1;
		this->styledef(Tooltip::cls()).layout().d_zorder = -2;

		// LAYOUT
		this->styledef(Wedge::Board()).layout().d_space = { READING, EXPAND, EXPAND };
		this->styledef(Wedge::Board()).layout().d_clipping = CLIP;
		this->styledef(Tab::cls()).layout().d_clipping = CLIP;
		this->styledef(Window::Body()).layout().d_clipping = CLIP;

		this->styledef(Wedge::Layout()).layout().d_space = { PARAGRAPH, EXPAND, EXPAND };

		this->styledef(GridSheet::cls()).layout().d_opacity = OPAQUE;

		// SHEET
		this->styledef(Wedge::Sheet()).layout().d_space = SHEET;

		// OVERLAYS
		this->styledef(Wedge::Decal()).layout().d_flow = FREE;
		this->styledef(Wedge::Decal()).layout().d_space = BLOCK;

		this->styledef(NodeKnob::Proxy()).layout().d_flow = FREE;

		this->styledef(Wedge::Overlay()).layout().d_flow = FREE;
		this->styledef(Wedge::Overlay()).layout().d_space = UNIT;
		this->styledef(Wedge::Overlay()).layout().d_opacity = OPAQUE;

		this->styledef(Rectangle::cls()).layout().d_space = BLOCK;
		this->styledef(NodeCable::cls()).layout().d_space = BLOCK;

		this->styledef(Node::cls()).layout().d_space = { READING, SHRINK, SHRINK };

		// LAYERS
		this->styledef(Slider::Display()).layout().d_flow = OVERLAY;
		this->styledef(Slider::Knob()).layout().d_flow = OVERLAY;

		this->styledef(Scrollbar::Knob()).layout().d_flow = FLOW;

		// CONTAINERS
		this->styledef(Wedge::cls()).layout().d_space = SHEET;

		this->styledef(ScrollSheet::cls()).layout().d_opacity = OPAQUE;
		this->styledef(ScrollPlan::cls()).layout().d_opacity = OPAQUE;

		this->styledef(Window::cls()).layout().d_space = BLOCK;

		this->styledef(Dockbox::cls()).layout().d_space = { PARAGRAPH, WRAP, FIXED };
		this->styledef(Window::DockWindow()).layout().d_flow = FLOW;
		this->styledef(Window::DockWindow()).layout().d_space = SHEET;

		// BLOCKS
		this->styledef(Window::WrapWindow()).layout().d_space = UNIT;
		
		// SPACER
		this->styledef(Item::Spacer()).layout().d_space = SPACER;

		this->styledef(Scrollbar::Scroller()).layout().d_space = FLEX;

		this->styledef(Item::Filler()).layout().d_space = FLEX;
		this->styledef(Slider::cls()).layout().d_space = FLEX;

		this->styledef(Slider::Knob()).layout().d_space = FLEX;

		// LINE
		this->styledef(Wedge::Row()).layout().d_space = LINE;

		// ALIGNED
		this->styledef(Dropdown::List()).layout().d_flow = ALIGN;
		this->styledef(Dropdown::List()).layout().d_align = { LEFT, OUT_RIGHT };
		this->styledef(Menu::List()).layout().d_align = { LEFT, OUT_RIGHT };
		this->styledef(Menu::SubList()).layout().d_align = { OUT_RIGHT, LEFT };

		// DIVS
		this->styledef(Wedge::Div()).layout().d_space = DIV;
		this->styledef(Table::Head()).layout().d_space = DIV;
		
		this->styledef(Docker::cls()).layout().d_space = SPACER;

		// STACKS
		this->styledef(Wedge::Stack()).layout().d_space = STACK;
		this->styledef(Text::cls()).layout().d_space = { PARAGRAPH, FIXED, WRAP };

		// CONTROLS
		this->styledef(Item::cls()).layout().d_space = BLOCK;
		this->styledef(Input<bool>::cls()).layout().d_space = ITEM;

		this->styledef(Item::Control()).layout().d_opacity = OPAQUE;
		this->styledef(TypeIn::cls()).layout().d_opacity = OPAQUE;
		
		this->styledef(Wedge::WrapControl()).layout().d_space = LINE;
		this->styledef(Wedge::WrapControl()).layout().d_opacity = OPAQUE;

		this->styledef(Table::ColumnHeader()).layout().d_space = LINE;

		this->styledef(Menu::cls()).layout().d_space = ITEM;

		// EDITORS
		this->styledef(Textbox::cls()).layout().d_space = BOARD;

		this->styledef(Canvas::cls()).layout().d_space = BOARD;
		this->styledef(Canvas::cls()).layout().d_opacity = OPAQUE;
		this->styledef(Canvas::cls()).layout().d_clipping = CLIP;

		this->styledef(ScrollPlan::Plan()).layout().d_space = BLOCK;
		this->styledef(ScrollPlan::Plan()).skin().m_customRenderer = &drawGrid;

		this->styledef(Toolbar::cls()).layout().d_space = ITEM;

		this->styledef(Dockspace::cls()).layout().d_opacity = OPAQUE;

		// GEOMETRY

		//this->styledef(WindowFooter::cls()).layout().d_space = { READING, WRAP, FIXED };
		this->styledef(WindowFooter::SizerLeft()).layout().d_space = { READING, WRAP, FIXED };
		this->styledef(WindowFooter::SizerRight()).layout().d_space = { READING, WRAP, FIXED };

		this->styledef(Dockbar::cls()).layout().d_align = { RIGHT, RIGHT };

		this->styledef(Docker::cls()).layout().d_flow = ALIGN;
		this->styledef(Docker::cls()).layout().d_align = { LEFT, OUT_LEFT };

		this->styledef(Popup::cls()).layout().d_size = { 280.f, 350.f };

		this->styledef(Dockbox::cls()).layout().d_flow = FLOW;
		this->styledef(Dockbox::cls()).layout().d_size = { 300.f, 0.f };
		//this->styledef(Dockbox::cls()).skin().m_base = &this->style(DockWindow::cls());
		// this initializes Window before the styledef is set

		this->styledef(ScrollZone::cls()).layout().d_layout = { AUTO_SIZE, AUTO_SIZE };
		this->styledef(ScrollZone::cls()).layout().d_clipping = CLIP;


		this->styledef(Item::Control()).layout().d_align = { LEFT, CENTER };
		this->styledef(Button::cls()).layout().d_align = { LEFT, CENTER };
		this->styledef(CloseButton::cls()).layout().d_align = { RIGHT, CENTER };

		this->styledef(NodeKnob::cls()).layout().d_size = { 10.f, 10.f };

		this->styledef(Wedge::Header()).layout().d_padding = BoxFloat(6.f);

		this->styledef(WrapButton::cls()).layout().d_spacing = DimFloat(2.f);
		this->styledef(MultiButton::cls()).layout().d_padding = BoxFloat(2.f);

		this->styledef(Dropdown::Head()).layout().d_padding = BoxFloat(2.f);

		this->styledef(Dockbar::cls()).layout().d_padding = BoxFloat(4.f);
		this->styledef(Dockbar::cls()).layout().d_spacing = DimFloat(4.f);

		this->styledef(Toolbar::cls()).layout().d_padding = BoxFloat(6.f);
		this->styledef(Toolbar::cls()).layout().d_spacing = DimFloat(6.f);
		this->styledef(Menubar::cls()).layout().d_spacing = DimFloat(6.f);
		
		this->styledef(GridSheet::cls()).layout().d_spacing = DimFloat(5.f);

		this->styledef(Tab::cls()).layout().d_padding = BoxFloat(6.f);
		this->styledef(Docksection::DockTab()).layout().d_padding = BoxFloat(0.f);

		//this->styledef(GridSubdiv::cls()).layout().d_spacing = DimFloat(6.f);
		this->styledef(Dockspace::cls()).layout().d_spacing = DimFloat(6.f);

		this->styledef(Expandbox::Body()).layout().d_padding = { 12.f, 2.f, 0.f, 2.f };
		this->styledef(Expandbox::Body()).layout().d_spacing = DimFloat(6.f);

		//this->styledef(Surface::cls()).layout().d_margin = DimFloat(1000.f);

		this->styledef(TreeNode::Body()).layout().d_padding = { 18.f, 0.f, 0.f, 0.f };
		this->styledef(TreeNode::Body()).layout().d_spacing = DimFloat(0.f);

		this->styledef(Table::cls()).layout().d_spacing = DimFloat(0.f, 2.f);

		this->styledef(WindowHeader::cls()).skin().m_hoverCursor = &Cursor::Move();
		this->styledef(Dockspace::cls()).skin().m_hoverCursor = &Cursor::ResizeX();
		this->styledef(WindowFooter::SizerLeft()).skin().m_hoverCursor = &Cursor::ResizeDiagLeft();
		this->styledef(WindowFooter::SizerRight()).skin().m_hoverCursor = &Cursor::ResizeDiagRight();

		this->styledef(Cursor::cls()).skin().m_image = &m_uiWindow.findImage("mousepointer");

		this->styledef(Cursor::ResizeX()).skin().m_image = &m_uiWindow.findImage("resize_h_20");
		this->styledef(Cursor::ResizeX()).skin().m_padding = { -10.f, -10.f, +10.f, +10.f };
		this->styledef(Cursor::ResizeY()).skin().m_image = &m_uiWindow.findImage("resize_v_20");
		this->styledef(Cursor::ResizeY()).skin().m_padding = { -10.f, -10.f, +10.f, +10.f };
		this->styledef(Cursor::Move()).skin().m_image = &m_uiWindow.findImage("move_20");
		this->styledef(Cursor::Move()).skin().m_padding = { -10.f, -10.f, +10.f, +10.f };
		this->styledef(Cursor::ResizeDiagLeft()).skin().m_image = &m_uiWindow.findImage("resize_diag_left_20");
		this->styledef(Cursor::ResizeDiagLeft()).skin().m_padding = { -10.f, -10.f, +10.f, +10.f };
		this->styledef(Cursor::ResizeDiagRight()).skin().m_image = &m_uiWindow.findImage("resize_diag_right_20");
		this->styledef(Cursor::ResizeDiagRight()).skin().m_padding = { -10.f, -10.f, +10.f, +10.f };
		this->styledef(Cursor::Caret()).skin().m_image = &m_uiWindow.findImage("caret_white");
		this->styledef(Cursor::Caret()).skin().m_padding = { -4.f, -9.f, +4.f, +9.f };
		
		this->styledef(Toolbar::Mover()).skin().m_image = &m_uiWindow.findImage("mousepointer");

		this->styledef(Text::cls()).skin().m_textWrap = true;
		this->styledef(Textbox::cls()).skin().m_textWrap = true;

		this->styledef(Item::cls()).skin().m_empty = false;
		this->styledef(Item::cls()).skin().m_textColour = Colour::White;
		this->styledef(Item::cls()).skin().m_padding = BoxFloat(2.f);

		this->styledef(Figure::cls()).skin().m_empty = false;

		this->styledef(ScrollPlan::Plan()).skin().m_borderWidth = BoxFloat(2.f);
		this->styledef(ScrollPlan::Plan()).skin().m_borderColour = Colour::AlphaGrey;

		this->styledef(Rectangle::cls()).skin().m_borderWidth = BoxFloat(1.f);
		this->styledef(Rectangle::cls()).skin().m_borderColour = Colour::Cyan;

		this->styledef(Docksection::Placeholder()).skin().m_backgroundColour = Colour::Blue;
	}
}
