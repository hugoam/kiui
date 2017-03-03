//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/UiLayout.h>

#include <toyui/UiWindow.h>

#include <toyui/Types.h>

namespace toy
{
	Styler::Styler()
	{}

	Styler::~Styler()
	{}
	
	void Styler::clear()
	{
		m_styledefs.clear();

		for(auto& kv : m_styles)
			kv.second->clear();

		this->defaultLayout();
	}

	void Styler::reset()
	{
		for(auto& kv : m_styles)
			this->prepareStyle(*kv.second);
	}

	Style& Styler::styledef(const string& name)
	{
		if(m_styledefs[name] == nullptr)
			m_styledefs[name] = std::move(make_unique<Style>(name));
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
		//printf("Init style %s\n", type.name().c_str());

		unique_ptr<Style> style = make_unique<Style>(type, type.base() ? &this->style(*type.base()) : nullptr);
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
		this->styledef(RootSheet::cls()).layout().d_space = BOARD;
		this->styledef(RootSheet::cls()).layout().d_clipping = CLIP;
		this->styledef(RootSheet::cls()).layout().d_opacity = OPAQUE;

		this->styledef(Cursor::cls()).layout().d_zorder = -1;
		this->styledef(Tooltip::cls()).layout().d_zorder = -2;

		// LAYOUT
		this->styledef(Board::cls()).layout().d_space = BOARD;
		this->styledef(Board::cls()).layout().d_direction = READING;
		this->styledef(Board::cls()).layout().d_clipping = CLIP;

		this->styledef(Layout::cls()).layout().d_direction = PARAGRAPH;

		this->styledef(GridSheet::cls()).layout().d_opacity = OPAQUE;
		this->styledef(Dockline::cls()).layout().d_space = BOARD;

		// SHEET
		this->styledef(Sheet::cls()).layout().d_space = SHEET;

		// OVERLAYS
		this->styledef(Decal::cls()).layout().d_flow = FREE;
		this->styledef(Decal::cls()).layout().d_space = ITEM;

		this->styledef(Overlay::cls()).layout().d_flow = FREE;
		this->styledef(Overlay::cls()).layout().d_space = BLOCK;
		this->styledef(Overlay::cls()).layout().d_opacity = OPAQUE;

		this->styledef(Node::cls()).layout().d_direction = READING;

		// LAYERS
		this->styledef(SliderDisplay::cls()).layout().d_flow = OVERLAY;
		this->styledef(SliderKnob::cls()).layout().d_flow = OVERLAY;

		this->styledef(ScrollerKnob::cls()).layout().d_flow = FLOW;

		// CONTAINERS
		this->styledef(Container::cls()).layout().d_space = SHEET;

		this->styledef(ScrollSheet::cls()).layout().d_opacity = OPAQUE;
		this->styledef(ScrollPlan::cls()).layout().d_opacity = OPAQUE;

		this->styledef(Window::cls()).layout().d_space = FIXED_BLOCK;

		this->styledef(Dockbox::cls()).layout().d_space = SHEET;
		this->styledef(DockWindow::cls()).layout().d_flow = FLOW;
		this->styledef(DockWindow::cls()).layout().d_space = SHEET;

		// BLOCKS
		this->styledef(WrapWindow::cls()).layout().d_space = BLOCK;

		// SPACER
		this->styledef(Spacer::cls()).layout().d_space = SPACE;

		this->styledef(Scroller::cls()).layout().d_space = PARALLEL_FLEX;

		this->styledef(Filler::cls()).layout().d_space = SHEET;
		this->styledef(Slider::cls()).layout().d_space = SHEET;

		this->styledef(SliderKnob::cls()).layout().d_space = SHEET;

		// LINE
		this->styledef(Line::cls()).layout().d_space = LINE;

		// ALIGNED
		this->styledef(DropdownList::cls()).layout().d_flow = ALIGN;
		this->styledef(DropdownList::cls()).layout().d_align = DimAlign(LEFT, OUT_RIGHT);
		this->styledef(MenuList::cls()).layout().d_align = DimAlign(LEFT, OUT_RIGHT);
		this->styledef(SubMenuList::cls()).layout().d_align = DimAlign(OUT_RIGHT, LEFT);

		// DIVS
		this->styledef(Div::cls()).layout().d_space = DIV;
		this->styledef(TableHead::cls()).layout().d_space = DIV;
		this->styledef(Text::cls()).layout().d_space = DIV;
		
		this->styledef(Docker::cls()).layout().d_space = SPACE;

		// STACKS
		this->styledef(Stack::cls()).layout().d_space = STACK;
		this->styledef(Text::cls()).layout().d_space = STACK;

		// CONTROLS
		this->styledef(Item::cls()).layout().d_space = ITEM;
		this->styledef(Input<bool>::cls()).layout().d_space = ITEM;
		this->styledef(Control::cls()).layout().d_opacity = OPAQUE;
		
		this->styledef(WrapControl::cls()).layout().d_space = LINE;
		this->styledef(WrapControl::cls()).layout().d_opacity = OPAQUE;

		this->styledef(WrapControl::cls()).layout().d_space = LINE;
		this->styledef(TypeIn::cls()).layout().d_space = LINE;
		
		this->styledef(ColumnHeader::cls()).layout().d_space = LINE;

		this->styledef(Menu::cls()).layout().d_space = ITEM;

		// EDITORS
		this->styledef(Textbox::cls()).layout().d_space = BOARD;

		this->styledef(Canvas::cls()).layout().d_space = BOARD;
		this->styledef(Canvas::cls()).layout().d_opacity = OPAQUE;
		this->styledef(Canvas::cls()).layout().d_clipping = CLIP;

		this->styledef(Plan::cls()).layout().d_space = MANUAL_SPACE;

		this->styledef(Plan::cls()).skin().m_customRenderer = &drawGrid;

		this->styledef(Toolbar::cls()).layout().d_space = ITEM;


		// GEOMETRY


		//
		//
		// 

		this->styledef(WindowSizerLeft::cls()).layout().d_space = SHEET;
		this->styledef(WindowSizerRight::cls()).layout().d_space = SHEET;

		this->styledef(NoScrollZone::cls()).layout().d_space = SHEET;

		this->styledef(Slider::cls()).layout().d_direction = DIMENSION;
		this->styledef(Scrollbar::cls()).layout().d_direction = DIMENSION;
		this->styledef(Dockline::cls()).layout().d_direction = DIMENSION;

		this->styledef(GridLine::cls()).layout().d_space = SHEET;
		this->styledef(GridLine::cls()).layout().d_direction = READING;

		this->styledef(GridColumn::cls()).layout().d_space = SHEET;
		this->styledef(GridColumn::cls()).layout().d_layout = DimLayout(AUTO_LAYOUT, NO_LAYOUT);

		this->styledef(GridOverlay::cls()).layout().d_space = BOARD;
		this->styledef(GridOverlay::cls()).layout().d_flow = OVERLAY;
		this->styledef(GridOverlay::cls()).layout().d_direction = READING;
		this->styledef(GridOverlay::cls()).layout().d_opacity = HOLLOW;

		this->styledef(Dockbar::cls()).layout().d_align = DimAlign(RIGHT, RIGHT);

		this->styledef(Docker::cls()).layout().d_flow = ALIGN;
		this->styledef(Docker::cls()).layout().d_align = DimAlign(LEFT, OUT_LEFT);

		this->styledef(Popup::cls()).layout().d_size = DimFloat(280.f, 350.f);

		this->styledef(Dockbox::cls()).layout().d_flow = FLOW;
		this->styledef(Dockbox::cls()).layout().d_size = DimFloat(300.f, 0.f);
		//this->styledef(Dockbox::cls()).skin().m_base = &this->style(DockWindow::cls());
		// this initializes Window before the styledef is set


		this->styledef(ScrollZone::cls()).layout().d_layout = DimLayout(AUTO_SIZE, AUTO_SIZE);
		this->styledef(ScrollZone::cls()).layout().d_clipping = CLIP;



		this->styledef(Button::cls()).layout().d_align = DimAlign(LEFT, CENTER);
		this->styledef(CloseButton::cls()).layout().d_align = DimAlign(RIGHT, CENTER);






		this->styledef(NodeConnectionProxy::cls()).layout().d_size = DimFloat(10.f, 10.f);

		this->styledef(Header::cls()).layout().d_padding = BoxFloat(6.f);

		this->styledef(WrapButton::cls()).layout().d_spacing = DimFloat(2.f);

		this->styledef(Dockbar::cls()).layout().d_padding = BoxFloat(4.f);
		this->styledef(Dockbar::cls()).layout().d_spacing = DimFloat(4.f);

		this->styledef(Page::cls()).layout().d_spacing = DimFloat(6.f);

		this->styledef(Dialog::cls()).layout().d_padding = BoxFloat(25.f, 12.f, 25.f, 12.f);
		this->styledef(Dialog::cls()).layout().d_spacing = DimFloat(6.f);

		this->styledef(Toolbar::cls()).layout().d_padding = BoxFloat(6.f);
		this->styledef(Toolbar::cls()).layout().d_spacing = DimFloat(6.f);

		this->styledef(GridSheet::cls()).layout().d_spacing = DimFloat(5.f);

		this->styledef(Tab::cls()).layout().d_padding = BoxFloat(0.f, 4.f, 0.f, 0.f);

		this->styledef(ExpandboxBody::cls()).layout().d_padding = BoxFloat(12.f, 2.f, 0.f, 2.f);
		this->styledef(ExpandboxBody::cls()).layout().d_spacing = DimFloat(6.f);

		this->styledef(TreeNodeBody::cls()).layout().d_padding = BoxFloat(24.f, 2.f, 0.f, 2.f);

		this->styledef(Table::cls()).layout().d_spacing = DimFloat(0.f, 2.f);

		this->styledef(WindowHeader::cls()).skin().m_hoverCursor = &MoveCursor::cls();
		this->styledef(WindowSizerLeft::cls()).skin().m_hoverCursor = &ResizeCursorDiagLeft::cls();
		this->styledef(WindowSizerRight::cls()).skin().m_hoverCursor = &ResizeCursorDiagRight::cls();

		this->styledef(Cursor::cls()).skin().m_image = &findImage("mousepointer");

		this->styledef(ResizeCursorX::cls()).skin().m_image = &findImage("resize_h_20");
		this->styledef(ResizeCursorX::cls()).skin().m_padding = BoxFloat(-10.f, -10.f, +10.f, +10.f);
		this->styledef(ResizeCursorY::cls()).skin().m_image = &findImage("resize_v_20");
		this->styledef(ResizeCursorY::cls()).skin().m_padding = BoxFloat(-10.f, -10.f, +10.f, +10.f);
		this->styledef(MoveCursor::cls()).skin().m_image = &findImage("move_20");
		this->styledef(MoveCursor::cls()).skin().m_padding = BoxFloat(-10.f, -10.f, +10.f, +10.f);
		this->styledef(ResizeCursorDiagLeft::cls()).skin().m_image = &findImage("resize_diag_left_20");
		this->styledef(ResizeCursorDiagLeft::cls()).skin().m_padding = BoxFloat(-10.f, -10.f, +10.f, +10.f);
		this->styledef(ResizeCursorDiagRight::cls()).skin().m_image = &findImage("resize_diag_right_20");
		this->styledef(ResizeCursorDiagRight::cls()).skin().m_padding = BoxFloat(-10.f, -10.f, +10.f, +10.f);
		this->styledef(CaretCursor::cls()).skin().m_image = &findImage("caret_white");
		this->styledef(CaretCursor::cls()).skin().m_padding = BoxFloat(-4.f, -9.f, +4.f, +9.f);

		this->styledef(Text::cls()).skin().m_textWrap = true;
		this->styledef(Textbox::cls()).skin().m_textWrap = true;

		this->styledef(Label::cls()).skin().m_textColour = Colour::White;
		this->styledef(Label::cls()).skin().m_padding = BoxFloat(2.f);

		this->styledef(Icon::cls()).skin().m_padding = BoxFloat(3.f);
		this->styledef(Icon::cls()).skin().m_empty = false;

		this->styledef(Plan::cls()).skin().m_borderWidth = BoxFloat(2.f);
		this->styledef(Plan::cls()).skin().m_borderColour = Colour::AlphaGrey;

		this->styledef(Placeholder::cls()).skin().m_backgroundColour = Colour::Blue;
	}
}
