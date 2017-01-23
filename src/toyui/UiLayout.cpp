//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/UiLayout.h>

#include <toyui/UiWindow.h>

#include <toyui/Types.h>

#include <iostream>

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

		Cursor::cls().layout().d_flow = FREE;
		Cursor::cls().layout().d_clipping = NOCLIP;

		Tooltip::cls().layout().d_flow = FREE;
		Tooltip::cls().layout().d_clipping = NOCLIP;

		ContextMenu::cls().layout().d_flow = FREE;
		ContextMenu::cls().layout().d_clipping = NOCLIP;

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

		WrapSheet::cls().layout().d_space = FIT;

		Window::cls().layout().d_space = BOARD;

		DockWindow::cls().layout().d_space = BOARD;

		ShrinkWindow::cls().layout().d_space = BLOCK;
		ShrinkWindow::cls().layout().d_size = DimFloat();

		WindowBody::cls().layout().d_space = FIT;

		Board::cls().layout().d_space = BOARD;
		Dockspace::cls().layout().d_space = BOARD;
		Docksection::cls().layout().d_space = BOARD;
		ScrollSheet::cls().layout().d_space = BOARD;
		LayerSheet::cls().layout().d_space = BOARD;
		Tabber::cls().layout().d_space = BOARD;
		TabberBody::cls().layout().d_space = BOARD;
		Tab::cls().layout().d_space = BOARD;
		Tree::cls().layout().d_space = BOARD;
		List::cls().layout().d_space = BOARD;

		Textbox::cls().layout().d_space = BOARD;
		Text::cls().layout().d_space = DIV;

		Page::cls().layout().d_space = FIT;

		Dockbar::cls().layout().d_space = SPACE;
		Dockbar::cls().layout().d_flow = FLOAT_DEPTH;
		Dockbar::cls().layout().d_align = DimAlign(RIGHT, LEFT);

		Docker::cls().layout().d_flow = ALIGN;
		Docker::cls().layout().d_clipping = NOCLIP;
		Docker::cls().layout().d_space = DIV;
		Docker::cls().layout().d_align = DimAlign(OUT_LEFT, LEFT);

		Dockbox::cls().layout().d_flow = FLOW;
		Dockbox::cls().layout().d_space = BLOCK;
		Dockbox::cls().layout().d_size = DimFloat(300.f, 0.f);

		Dockbar::cls().layout().d_padding = BoxFloat(4.f);
		Dockbar::cls().layout().d_spacing = DimFloat(4.f, 4.f);

		Dockbox::cls().rebaseSkins(DockWindow::cls());

		DockToggle::cls().layout().d_align = DimAlign(CENTER, LEFT);

		ScrollArea::cls().layout().d_space = SPACE;
		ScrollArea::cls().layout().d_flow = FLOAT_DEPTH;
		ScrollArea::cls().layout().d_align = DimAlign(RIGHT, LEFT);
		ScrollArea::cls().layout().d_layoutDim = DIM_X;
		ScrollArea::cls().layout().d_pivot = DimPivot(REVERSE, REVERSE);

		ScrollSheet::cls().layout().d_opacity = OPAQUE;

		Scrollbar::cls().layout().d_space = DIV;

		Scroller::cls().layout().d_space = BOARD;

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
		SpacerY::cls().layout().d_layoutDim = DIM_Y;

		ProgressBarX::cls().layout().d_layoutDim = DIM_X;
		ProgressBarY::cls().layout().d_layoutDim = DIM_Y;

		FillerX::cls().layout().d_size = DimFloat(0.f, 20.f);
		FillerY::cls().layout().d_size = DimFloat(20.f, 0.f);

		SliderDisplay::cls().layout().d_flow = OVERLAY;

		Dockline::cls().layout().d_weight = LIST;
		Dockline::cls().layout().d_space = BOARD;
		DocklineY::cls().layout().d_spacing = DimFloat(0.f, 5.f);
		DocklineY::cls().layout().d_layoutDim = DIM_Y;
		DocklineX::cls().layout().d_spacing = DimFloat(5.f, 0.f);
		DocklineX::cls().layout().d_layoutDim = DIM_X;

		ExpandboxBody::cls().layout().d_padding = BoxFloat(12.f, 2.f, 0.f, 2.f);

		TreeNodeBody::cls().layout().d_padding = BoxFloat(24.f, 2.f, 0.f, 2.f);

		Table::cls().layout().d_spacing = DimFloat(0.f, 2.f);
		Table::cls().layout().d_layoutDim = DIM_Y;
		Table::cls().layout().d_weight = TABLE;

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

		//Caret::cls().skin().m_backgroundColour = Colour::White;

		Text::cls().skin().m_textWrap = true;
		Textbox::cls().skin().m_textWrap = true;

		Page::cls().layout().d_spacing = DimFloat(4.f, 6.f);
		ExpandboxBody::cls().layout().d_spacing = DimFloat(4.f, 6.f);

		Button::cls().layout().d_align = DimAlign(LEFT, CENTER);
		Toggle::cls().layout().d_align = DimAlign(LEFT, CENTER);
		WrapButton::cls().layout().d_align = DimAlign(LEFT, CENTER);
		CloseButton::cls().layout().d_align = DimAlign(RIGHT, CENTER);

		ScrollerKnob::cls().layout().d_sizing = DimSizing(FIXED, MANUAL);
		FillerX::cls().layout().d_sizing = DimSizing(MANUAL, FIXED);

		this->override(Scroller::cls(), FillerX::cls(), SpacerX::cls());
		this->override(Scroller::cls(), FillerY::cls(), SpacerY::cls());

		this->override(Scroller::cls(), SliderKnobX::cls(), ScrollerKnobX::cls());
		this->override(Scroller::cls(), SliderKnobY::cls(), ScrollerKnobY::cls());

		//Plan::cls().skin().m_borderColour = Colour::Red;
		//Plan::cls().skin().m_borderWidth = 1.f;
	}

	void Styler::defaultSkins()
	{
		// Skins

		TableHead::cls().layout().d_spacing = DimFloat(1.f, 0.f);

		WindowBody::cls().layout().d_padding = BoxFloat(4.f);

		Checkbox::cls().layout().d_size = DimFloat(16.f, 16.f);


		SliderKnobX::cls().layout().d_size = DimFloat(8.f, 0.f);
		SliderKnobY::cls().layout().d_size = DimFloat(0.f, 8.f);

		SliderKnob::cls().skin().m_backgroundColour = Colour::LightGrey;
		SliderKnob::cls().skin().m_cornerRadius = 3.f;
		SliderKnob::cls().decline(HOVERED).m_backgroundColour = Colour::Red;

		SliderDisplay::cls().layout().d_align = DimAlign(CENTER, CENTER);

		CloseButton::cls().skin().m_image = &findImage("close_15");
		CloseButton::cls().skin().m_padding = BoxFloat(4.f);
		CloseButton::cls().decline(HOVERED).m_backgroundColour = Colour::Red;

		DropdownToggle::cls().skin().m_backgroundColour = Colour::MidGrey;
		DropdownToggle::cls().skin().m_image = &findImage("arrow_down_15");
		DropdownToggle::cls().decline(HOVERED).m_backgroundColour = Colour::Red;

		ExpandboxToggle::cls().skin().m_image = &findImage("arrow_right_15");
		ExpandboxToggle::cls().decline(ACTIVATED).m_image = &findImage("arrow_down_15");
		ExpandboxToggle::cls().decline(HOVERED).m_backgroundColour = Colour::Red;
		ExpandboxToggle::cls().decline(DISABLED).m_image = &findImage("empty_15");
		ExpandboxToggle::cls().decline(static_cast<WidgetState>(ACTIVATED | HOVERED)).m_image = &findImage("arrow_down_15");
		ExpandboxToggle::cls().subskin(static_cast<WidgetState>(ACTIVATED | HOVERED)).m_backgroundColour = Colour::Red;

		TreeNodeToggle::cls().copySkins(ExpandboxToggle::cls());

		Label::cls().skin().m_textColour = Colour::White;
		Label::cls().skin().m_padding = BoxFloat(2.f);
		Title::cls();
		
		TypeIn::cls().skin().m_textColour = Colour::White;
		TypeIn::cls().skin().m_padding = BoxFloat(2.f);

		Button::cls().skin().m_backgroundColour = Colour::MidGrey;
		Button::cls().skin().m_textColour = Colour::White;
		Button::cls().skin().m_padding = BoxFloat(2.f);
		Button::cls().decline(HOVERED).m_backgroundColour = Colour::Red;
		Button::cls().decline(ACTIVATED).m_backgroundColour = Colour::LightGrey;
		Button::cls().decline(static_cast<WidgetState>(ACTIVATED | HOVERED)).m_backgroundColour = Colour::Red;

		ImgButton::cls().skin().m_backgroundColour = Colour::Transparent;

		CloseButton::cls().skin().m_backgroundColour = Colour::Transparent;
		DropdownToggle::cls().skin().m_backgroundColour = Colour::Transparent;

		//Toggle::cls().copySkins(Button::cls());
		WrapButton::cls().copySkins(Button::cls());

		EmptyStyle::cls().skin().m_backgroundColour = Colour::Transparent;
		DropdownHeader::cls().copySkins(EmptyStyle::cls());

		Dir::cls().copySkins(ImgButton::cls());
		File::cls().copySkins(ImgButton::cls());
		TreeNodeHeader::cls().copySkins(ImgButton::cls());

		ProgressBarX::cls().skin().m_backgroundColour = Colour::LightGrey;
		ProgressBarX::cls().skin().m_borderColour = Colour::White;
		ProgressBarX::cls().skin().m_borderWidth = 0.5f;
		ProgressBarX::cls().layout().d_padding = BoxFloat(1.f, 1.f, 1.f, 1.f);

		FillerX::cls().skin().m_backgroundColour = Colour(0.05f, 0.65f, 1.f, 0.6f);
		FillerY::cls().skin().m_backgroundColour = Colour(0.05f, 0.65f, 1.f, 0.6f);

		ScrollerKnob::cls().skin().m_backgroundColour = Colour::LightGrey;
		ScrollerKnob::cls().decline(HOVERED).m_backgroundColour = Colour::Red;
		ScrollerKnob::cls().decline(PRESSED).m_backgroundColour = Colour::Red;

		ScrollerKnobX::cls().skin().m_margin = BoxFloat(0.f, 4.f, 0.f, 4.f);
		ScrollerKnobY::cls().skin().m_margin = BoxFloat(4.f, 0.f, 4.f, 0.f);

		Scrollbar::cls().skin().m_backgroundColour = Colour::Black;

		Slider::cls().skin().m_backgroundColour = Colour::MidGrey;
		Slider::cls().skin().m_cornerRadius = 3.f;

		ScrollUp::cls().skin().m_image = &findImage("arrow_up_15");
		ScrollUp::cls().skin().m_backgroundColour = Colour::Transparent;
		ScrollUp::cls().decline(HOVERED).m_backgroundColour = Colour::Red;

		ScrollDown::cls().skin().m_image = &findImage("arrow_down_15");
		ScrollDown::cls().skin().m_backgroundColour = Colour::Transparent;
		ScrollDown::cls().decline(HOVERED).m_backgroundColour = Colour::Red;

		Scroller::cls().skin().m_backgroundColour = Colour::Transparent;

		NodeCable::cls().skin().m_borderWidth = 2.f;
		NodeCable::cls().skin().m_borderColour = Colour::White;

		Dialog::cls().skin().m_backgroundColour = Colour::DarkGrey;

		Tooltip::cls().skin().m_padding = BoxFloat(4.f);
		Tooltip::cls().skin().m_textColour = Colour::White;
		Tooltip::cls().skin().m_backgroundColour = Colour::MidGrey;

		//Tree::cls().skin().m_backgroundColour = Colour::Black;
		//List::cls().skin().m_backgroundColour = Colour::Black;
		SelectList::cls();

		Window::cls().skin().m_backgroundColour = Colour::AlphaGrey;
		//DockWindow::cls().skin().m_backgroundColour = Colour::DarkGrey;
		WindowHeader::cls().skin().m_backgroundColour = Colour::LightGrey;
		WindowFooter::cls().skin().m_backgroundColour = Colour::LightGrey;
		WindowFooter::cls().layout().d_size = DimFloat(0.f, 7.f);


		//Tab::cls().skin().m_backgroundColour = Colour::LightGrey;
		TabberHead::cls().skin().m_backgroundColour = Colour::Black;

		ExpandboxHeader::cls().skin().m_backgroundColour = Colour::LightGrey;
		ExpandboxHeader::cls().decline(ACTIVATED).m_backgroundColour = Colour::Red;

		ColumnHeader::cls().skin().m_backgroundColour = Colour::MidGrey;

		Header::cls().skin().m_backgroundColour = Colour::DarkGrey;

		ExpandboxBody::cls().skin().m_backgroundColour = Colour::DarkGrey;

		TreeNodeBody::cls().skin().m_backgroundColour = Colour::Transparent;

		TypeIn::cls().skin().m_backgroundColour = Colour::LightGrey;
		TypeIn::cls().skin().m_cornerRadius = BoxFloat(3.f, 3.f, 3.f, 3.f);
		TypeIn::cls().decline(ACTIVATED).m_backgroundColour = Colour::Red;

		Dropdown::cls().copySkins(TypeIn::cls());
		DropdownList::cls().skin().m_backgroundColour = Colour::LightGrey;

		Checkbox::cls().skin().m_backgroundColour = Colour::MidGrey;
		Checkbox::cls().decline(HOVERED).m_backgroundColour = Colour::Red;
		Checkbox::cls().decline(ACTIVATED).m_backgroundColour = Colour::LightGrey;

		Node::cls().rebaseSkins(Window::cls());
		NodeBody::cls().rebaseSkins(WindowHeader::cls());
	}
}
