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

	void Styler::prepare()
	{
		m_overrides.resize(1000);

		for(Object* object : Style::cls().indexer().objects())
			if(object)
				object->as<Style>().inherit();

		for(Object* object : InkStyle::cls().indexer().objects())
			if(object)
			{
				InkStyle& ink = object->as<InkStyle>();
				if(ink.backgroundColour().a() > 0.f || ink.textColour().a() > 0.f || ink.borderColour().a() > 0.f || ink.image() || !ink.imageSkin().null())
					ink.m_empty = false;
			}
	}

	void Styler::reset()
	{
		m_overrides.clear();

		for(Object* object : Style::cls().indexer().objects())
			if(object)
				object->as<Style>().reset();

		this->defaultLayout();
	}

	Style* Styler::fetchOverride(Style& style, Style& overrider)
	{
		if(m_overrides[overrider.id()].size() > 0)
			for(StyleOverride& override : m_overrides[overrider.id()])
				if(&override.m_style == &style)
					return &override.m_override;

		return nullptr;
	}

	void Styler::override(Style& stem, Style& overrideWhat, Style& overrideWith)
	{
		if(m_overrides.size() <= stem.id())
			m_overrides.resize(stem.id() + 1);

		m_overrides[stem.id()].emplace_back(overrideWhat, overrideWith);
	}

	void Styler::override(const string& stem, const string& style, const string& overrider)
	{
		this->override(*this->fetchStyle(stem), *this->fetchStyle(style), *this->fetchStyle(overrider));
	}

	Style& Styler::dynamicStyle(const string& name)
	{
		if(this->fetchStyle(name) == nullptr)
			m_dynamicStyles.emplace_back(make_unique<Style>(name));
		return *this->fetchStyle(name);
	}

	Style* Styler::fetchStyle(const string& name)
	{
		for(Object* object : Style::cls().indexer().objects())
			if(object && object->as<Style>().name() == name)
				return &object->as<Style>();
		return nullptr;
	}

	void Styler::defaultLayout()
	{
		// Built-in Layouts

		Sheet::cls().layout().d_layoutDim = DIM_Y;
		Board::cls().layout().d_layoutDim = DIM_X;
		Page::cls().layout().d_layoutDim = DIM_Y;
		Canvas::cls().layout().d_layoutDim = DIM_X;

		Cursor::cls().layout().d_flow = FREE;
		Tooltip::cls().layout().d_flow = FREE;
		ContextMenu::cls().layout().d_flow = FREE;

		Control::cls().layout().d_opacity = OPAQUE;

		Dialog::cls().layout().d_layoutDim = DIM_Y;
		Dialog::cls().layout().d_padding = BoxFloat(25.f, 12.f, 25.f, 12.f);
		Dialog::cls().layout().d_spacing = DimFloat(6.f, 6.f);

		Window::cls().layout().d_flow = FREE;
		Window::cls().layout().d_opacity = OPAQUE;
		Window::cls().layout().d_layoutDim = DIM_Y;
		Window::cls().layout().d_size = DimFloat(480.f, 350.f);

		Popup::cls().layout().d_flow = FREE;
		Popup::cls().layout().d_opacity = OPAQUE;
		Popup::cls().layout().d_space = BOARD;
		Popup::cls().layout().d_size = DimFloat(280.f, 350.f);

		Node::cls().layout().d_flow = FREE;
		Node::cls().layout().d_opacity = OPAQUE;
		Node::cls().layout().d_layoutDim = DIM_X;

		NodePlug::cls().layout().d_layoutDim = DIM_X;
		NodePlug::cls().layout().d_opacity = OPAQUE;

		Node::cls().layout().d_space = BLOCK;

		NodeIn::cls().layout().d_space = DIV;
		NodeOut::cls().layout().d_space = DIV;

		NodeBody::cls().layout().d_space = DIV;
		NodePlug::cls().layout().d_space = BLOCK;

		NodePlugKnob::cls().layout().d_space = BLOCK;

		NodeCable::cls().layout().d_flow = FREE;
		NodeCable::cls().layout().d_space = BLOCK;

		Canvas::cls().layout().d_clipping = CLIP;
		Canvas::cls().layout().d_space = BOARD;
		Canvas::cls().layout().d_opacity = OPAQUE;

		DockWindow::cls().layout().d_opacity = OPAQUE;

		// Layouts

		WrapButton::cls().layout().d_opacity = OPAQUE;
		WrapButton::cls().layout().d_layoutDim = DIM_X;

		Window::cls().layout().d_space = BOARD;

		DockWindow::cls().layout().d_space = BOARD;

		ShrinkWindow::cls().layout().d_space = BLOCK;
		ShrinkWindow::cls().layout().d_size = DimFloat();

		WindowBody::cls().layout().d_space = FLEX;

		Board::cls().layout().d_space = BOARD;
		Board::cls().layout().d_clipping = CLIP;

		Dockspace::cls().layout().d_space = BOARD;
		Docksection::cls().layout().d_space = BOARD;
		ScrollSheet::cls().layout().d_space = BOARD;
		LayerSheet::cls().layout().d_space = BOARD;
		Tabber::cls().layout().d_space = BOARD;
		TabberBody::cls().layout().d_space = FLEX;
		Tab::cls().layout().d_space = BOARD;

		Expandbox::cls().layout().d_sizing = DimSizing(WRAP, SHRINK);
		Tree::cls().layout().d_space = FLEX;
		List::cls().layout().d_space = FLEX;
		
		Textbox::cls().layout().d_space = BOARD;
		Text::cls().layout().d_space = DIV;

		Page::cls().layout().d_space = FLEX;

		GridLine::cls().layout().d_space = BOARD;
		GridLine::cls().layout().d_layoutDim = DIM_X;

		GridColumn::cls().layout().d_space = FLEX;
		GridColumn::cls().layout().d_layout = DimLayout(AUTOLAYOUT, NOLAYOUT);
		GridColumn::cls().layout().d_layoutDim = DIM_Y;

		GridOverlay::cls().layout().d_space = BOARD;
		GridOverlay::cls().layout().d_flow = OVERLAY;
		GridOverlay::cls().layout().d_layoutDim = DIM_X;
		GridOverlay::cls().layout().d_opacity = HOLLOW;

		Dockbar::cls().layout().d_align = DimAlign(RIGHT, RIGHT);

		Docker::cls().layout().d_flow = ALIGN;
		Docker::cls().layout().d_clipping = NOCLIP;
		Docker::cls().layout().d_space = DIV;
		Docker::cls().layout().d_align = DimAlign(OUT_LEFT, LEFT);

		Dockbox::cls().layout().d_flow = FLOW;
		Dockbox::cls().layout().d_space = FLEX;
		Dockbox::cls().layout().d_size = DimFloat(300.f, 0.f);
		Dockbox::cls().rebaseSkins(DockWindow::cls());

		Dockbar::cls().layout().d_padding = BoxFloat(4.f);
		Dockbar::cls().layout().d_spacing = DimFloat(4.f, 4.f);


		DockToggle::cls().layout().d_align = DimAlign(CENTER, LEFT);

		ScrollSheet::cls().layout().d_opacity = OPAQUE;

		ScrollbarX::cls().layout().d_space = DIV;
		ScrollbarX::cls().layout().d_align = DimAlign(LEFT, RIGHT);

		ScrollbarY::cls().layout().d_space = SPACE;

		Scroller::cls().layout().d_space = BOARD;

		ScrollZone::cls().layout().d_space = BOARD;
		ScrollZone::cls().layout().d_layout = DimLayout(AUTOSIZE, AUTOSIZE);
		ScrollZone::cls().layout().d_clipping = CLIP;

		Placeholder::cls().layout().d_space = BOARD;
		Placeholder::cls().skin().m_backgroundColour = Colour::Blue;

		DropdownHeader::cls().layout().d_space = SPACE;

		DropdownList::cls().layout().d_space = SPACE;

		Menu::cls().layout().d_space = BLOCK;
		MenuList::cls().layout().d_space = BLOCK;

		SliderDisplay::cls().layout().d_space = BLOCK;

		Input<bool>::cls().layout().d_space = BLOCK;

		TableHead::cls().layout().d_layoutDim = DIM_X;

		RadioSwitch::cls().layout().d_layoutDim = DIM_X;
		RadioChoice::cls();

		Band::cls().layout().d_layoutDim = DIM_X;
		Header::cls().layout().d_layoutDim = DIM_X;
		Dropdown::cls().layout().d_layoutDim = DIM_X;
		Typedown::cls();

		SliderX::cls().layout().d_layoutDim = DIM_X;
		SliderY::cls().layout().d_layoutDim = DIM_Y;

		SliderKnob::cls().layout().d_flow = FREE_FILL;

		ScrollerX::cls().layout().d_layoutDim = DIM_X;
		ScrollerY::cls().layout().d_layoutDim = DIM_Y;

		ScrollbarX::cls().layout().d_layoutDim = DIM_X;
		ScrollbarY::cls().layout().d_layoutDim = DIM_Y;

		//DynamicImage::cls().skin().m_empty = false;
		Icon::cls().skin().m_empty = false;

		Dir::cls().layout().d_layoutDim = DIM_X;
		File::cls().layout().d_layoutDim = DIM_X;

		Directory::cls().layout().d_layoutDim = DIM_Y;

		Dir::cls().layout().d_padding = BoxFloat(2.f, 2.f, 2.f, 2.f);
		Dir::cls().layout().d_spacing = DimFloat(2.f, 2.f);
		File::cls().layout().d_padding = BoxFloat(2.f, 2.f, 2.f, 2.f);
		File::cls().layout().d_spacing = DimFloat(2.f, 2.f);
		TreeNodeHeader::cls().layout().d_padding = BoxFloat(2.f, 2.f, 2.f, 2.f);
		TreeNodeHeader::cls().layout().d_spacing = DimFloat(2.f, 2.f);

		RootSheet::cls().layout().d_opacity = OPAQUE;
		RootSheet::cls().layout().d_clipping = NOCLIP;

		DropdownToggle::cls().layout().d_opacity = OPAQUE;

		WValue::cls().layout().d_layoutDim = DIM_X;

		TypeIn::cls().layout().d_opacity = OPAQUE;
		TypeIn::cls().layout().d_layoutDim = DIM_X;
		TypeIn::cls().layout().d_space = SPACE;

		WindowHeader::cls().layout().d_opacity = OPAQUE;
		WindowSizer::cls().layout().d_opacity = OPAQUE;
		WindowSizerLeft::cls();
		WindowSizerRight::cls();
		WindowFooter::cls().layout().d_layoutDim = DIM_X;

		GridSheet::cls().layout().d_opacity = OPAQUE;

		SpacerX::cls().layout().d_space = SPACE;
		SpacerX::cls().layout().d_layoutDim = DIM_X;
		SpacerY::cls().layout().d_space = SPACE;
		//SpacerY::cls().layout().d_layoutDim = DIM_Y;

		ProgressBarX::cls();
		ProgressBarY::cls();

		ProgressBarX::cls().layout().d_layoutDim = DIM_X;
		//ProgressBarY::cls().layout().d_layoutDim = DIM_Y;

		FillerX::cls().layout().d_size = DimFloat(0.f, 20.f);
		FillerY::cls().layout().d_size = DimFloat(20.f, 0.f);

		SliderDisplay::cls().layout().d_flow = OVERLAY;

		Dockline::cls().layout().d_space = BOARD;
		DocklineY::cls().layout().d_spacing = DimFloat(0.f, 5.f);
		DocklineY::cls().layout().d_layoutDim = DIM_Y;
		DocklineX::cls().layout().d_spacing = DimFloat(5.f, 0.f);
		DocklineX::cls().layout().d_layoutDim = DIM_X;

		ExpandboxBody::cls().layout().d_padding = BoxFloat(12.f, 2.f, 0.f, 2.f);

		TreeNodeBody::cls().layout().d_padding = BoxFloat(24.f, 2.f, 0.f, 2.f);

		Table::cls().layout().d_spacing = DimFloat(0.f, 2.f);
		Table::cls().layout().d_layoutDim = DIM_Y;

		ColumnHeader::cls().layout().d_space = SPACE;

		ExpandboxHeader::cls().layout().d_opacity = OPAQUE;
		TreeNodeHeader::cls().layout().d_opacity = OPAQUE;

		DropdownChoice::cls().layout().d_opacity = OPAQUE;

		DropdownList::cls().layout().d_flow = ALIGN;
		DropdownList::cls().layout().d_align = DimAlign(LEFT, OUT_RIGHT);
		DropdownList::cls().layout().d_clipping = NOCLIP;

		MenuList::cls().layout().d_flow = ALIGN;
		MenuList::cls().layout().d_clipping = NOCLIP;

		ScrollSheet::cls().layout().d_clipping = CLIP;
		RootSheet::cls().layout().d_clipping = CLIP;

		ScrollSheet::cls().layout().d_layoutDim = DIM_Y;
		Scrollbar::cls().layout().d_layoutDim = DIM_Y;

		Tab::cls().layout().d_padding = BoxFloat(0.f, 4.f, 0.f, 0.f);
		TabHeader::cls();

		Header::cls().layout().d_padding = BoxFloat(6.f);

		EmptyStyle::cls().skin().m_empty = true;

		WindowHeader::cls().skin().m_weakCorners = true;
		WindowFooter::cls().skin().m_weakCorners = true;
		FillerX::cls().skin().m_weakCorners = true;
		RadioChoice::cls().skin().m_weakCorners = true;

		Cursor::cls().skin().m_image = &findImage("mousepointer");

		ResizeCursorX::cls().skin().m_image = &findImage("resize_h_20");
		ResizeCursorX::cls().skin().m_padding = BoxFloat(-10.f, -10.f, +10.f, +10.f);
		ResizeCursorY::cls().skin().m_image = &findImage("resize_v_20");
		ResizeCursorY::cls().skin().m_padding = BoxFloat(-10.f, -10.f, +10.f, +10.f);
		MoveCursor::cls().skin().m_image = &findImage("move_20");
		MoveCursor::cls().skin().m_padding = BoxFloat(-10.f, -10.f, +10.f, +10.f);
		ResizeCursorDiagLeft::cls().skin().m_image = &findImage("resize_diag_left_20");
		ResizeCursorDiagLeft::cls().skin().m_padding = BoxFloat(-10.f, -10.f, +10.f, +10.f);
		ResizeCursorDiagRight::cls().skin().m_image = &findImage("resize_diag_right_20");
		ResizeCursorDiagRight::cls().skin().m_padding = BoxFloat(-10.f, -10.f, +10.f, +10.f);
		CaretCursor::cls().skin().m_image = &findImage("caret_white");
		CaretCursor::cls().skin().m_padding = BoxFloat(-4.f, -9.f, +4.f, +9.f);

		Text::cls().skin().m_textWrap = true;
		Textbox::cls().skin().m_textWrap = true;

		Page::cls().layout().d_spacing = DimFloat(4.f, 6.f);
		ExpandboxBody::cls().layout().d_spacing = DimFloat(4.f, 6.f);

		Button::cls().layout().d_align = DimAlign(LEFT, CENTER);
		Toggle::cls().layout().d_align = DimAlign(LEFT, CENTER);
		WrapButton::cls().layout().d_align = DimAlign(LEFT, CENTER);
		CloseButton::cls().layout().d_align = DimAlign(RIGHT, CENTER);

		ScrollerKnobY::cls().layout().d_sizing = DimSizing(FIXED, MANUAL);
		ScrollerKnobX::cls().layout().d_sizing = DimSizing(MANUAL, FIXED);

		FillerX::cls().layout().d_sizing = DimSizing(MANUAL, FIXED);

		Title::cls();
		DropdownToggle::cls();
		ExpandboxToggle::cls();
		ExpandboxHeader::cls();
		ExpandboxBody::cls();
		TreeNodeToggle::cls();
		TreeNodeHeader::cls();
		TreeNodeBody::cls();
		CloseButton::cls();
		Checkbox::cls();

		ScrollUp::cls();
		ScrollDown::cls();
		ScrollLeft::cls();
		ScrollRight::cls();

		Label::cls().skin().m_textColour = Colour::White;
		Label::cls().skin().m_padding = BoxFloat(2.f);

		this->override(ScrollerX::cls(), FillerX::cls(), SpacerX::cls());
		this->override(ScrollerY::cls(), FillerY::cls(), SpacerY::cls());

		this->override(ScrollerX::cls(), SliderKnobX::cls(), ScrollerKnobX::cls());
		this->override(ScrollerY::cls(), SliderKnobY::cls(), ScrollerKnobY::cls());
	}

	void Styler::defaultSkins()
	{
		// Skins

	}
}
