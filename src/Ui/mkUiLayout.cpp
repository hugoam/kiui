//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/mkUiLayout.h>

#include <Ui/mkUiWindow.h>

#include <Ui/mkUiTypes.h>

#include <iostream>

namespace mk
{
	Styler::Styler()
	{}

	Styler::~Styler()
	{}

	void Styler::prepare()
	{
		mOverrides.resize(1000);

		for(Object* object : Style::indexer().objects())
			if(object)
				object->as<Style>().inherit();

		for(Object* object : InkStyle::indexer().objects())
			if(object)
			{
				InkStyle& ink = object->as<InkStyle>();
				if(ink.backgroundColour().a() > 0.f || ink.textColour().a() > 0.f || ink.borderColour().a() > 0.f || !ink.image().null() || !ink.imageSkin().null())
					ink.mEmpty = false;
			}
	}

	void Styler::reset()
	{
		mOverrides.clear();

		for(Object* object : Style::indexer().objects())
			if(object)
				object->as<Style>().reset();

		this->defaultLayout();
	}

	Style* Styler::fetchOverride(Style& style, Style& overrider)
	{
		if(mOverrides[overrider.id()].size() > 0)
			for(StyleOverride& override : mOverrides[overrider.id()])
				if(&override.mStyle == &style)
					return &override.mOverride;

		return nullptr;
	}

	void Styler::override(Style& stem, Style& overrideWhat, Style& overrideWith)
	{
		if(mOverrides.size() <= stem.id())
			mOverrides.resize(stem.id() + 1);

		mOverrides[stem.id()].emplace_back(overrideWhat, overrideWith);
	}

	void Styler::override(const string& stem, const string& style, const string& overrider)
	{
		this->override(*this->fetchStyle(stem), *this->fetchStyle(style), *this->fetchStyle(overrider));
	}

	Style& Styler::dynamicStyle(const string& name)
	{
		if(this->fetchStyle(name) == nullptr)
			mDynamicStyles.emplace_back(make_unique<Style>(name));
		return *this->fetchStyle(name);
	}

	Style* Styler::fetchStyle(const string& name)
	{
		for(Object* object : Style::indexer().objects())
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

		Caret::cls().layout().d_flow = FREE;

		Window::cls().layout().d_flow = FREE;
		Window::cls().layout().d_opacity = OPAQUE;
		Window::cls().layout().d_layoutDim = DIM_Y;
		Window::cls().layout().d_size = DimFloat(480.f, 350.f);

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

		Caret::cls().layout().d_space = BLOCK;
		Caret::cls().layout().d_size = DimFloat(1.f, 1.f);

		DropdownHeader::cls().layout().d_space = SPACE;

		DropdownList::cls().layout().d_space = SPACE;

		Menu::cls().layout().d_space = BLOCK;
		MenuList::cls().layout().d_space = BLOCK;

		SliderDisplay::cls().layout().d_space = BLOCK;

		Input<bool>::cls().layout().d_space = BLOCK;

		TableHead::cls().layout().d_layoutDim = DIM_X;

		RadioSwitch::cls().layout().d_layoutDim = DIM_X;
		RadioChoice::cls();

		Sequence::cls().layout().d_layoutDim = DIM_X;
		Header::cls().layout().d_layoutDim = DIM_X;
		Dropdown::cls().layout().d_layoutDim = DIM_X;
		Typedown::cls();

		SliderX::cls().layout().d_layoutDim = DIM_X;
		SliderY::cls().layout().d_layoutDim = DIM_Y;

		SliderKnob::cls().layout().d_flow = FREE_FILL;

		ScrollerX::cls().layout().d_layoutDim = DIM_X;
		ScrollerY::cls().layout().d_layoutDim = DIM_Y;

		Icon::cls().skin().mEmpty = false;

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

		DropdownToggle::cls().layout().d_opacity = GLASSY;

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

		Scrollbar::cls().layout().d_layoutDim = DIM_Y;

		Tab::cls().layout().d_padding = BoxFloat(0.f, 4.f, 0.f, 0.f);
		TabHeader::cls();

		Header::cls().layout().d_padding = BoxFloat(6.f);

		EmptyStyle::cls().skin().mEmpty = true;

		Cursor::cls().skin().mImage = Image("mousepointer");

		ResizeCursorX::cls().skin().mImage = Image("resize_h_20");
		ResizeCursorX::cls().skin().mPadding = BoxFloat(-10.f, -10.f, +10.f, +10.f);
		ResizeCursorY::cls().skin().mImage = Image("resize_v_20");
		ResizeCursorY::cls().skin().mPadding = BoxFloat(-10.f, -10.f, +10.f, +10.f);
		MoveCursor::cls().skin().mImage = Image("move_20");
		MoveCursor::cls().skin().mPadding = BoxFloat(-10.f, -10.f, +10.f, +10.f);
		ResizeCursorDiagLeft::cls().skin().mImage = Image("resize_diag_left_20");
		ResizeCursorDiagLeft::cls().skin().mPadding = BoxFloat(-10.f, -10.f, +10.f, +10.f);
		ResizeCursorDiagRight::cls().skin().mImage = Image("resize_diag_right_20");
		ResizeCursorDiagRight::cls().skin().mPadding = BoxFloat(-10.f, -10.f, +10.f, +10.f);
		CaretCursor::cls().skin().mImage = Image("caret_white");
		CaretCursor::cls().skin().mPadding = BoxFloat(-4.f, -9.f, +4.f, +9.f);

		Caret::cls().skin().mBackgroundColour = Colour::White;

		Textbox::cls().skin().mTextWrap = true;

		Page::cls().layout().d_spacing = DimFloat(4.f, 6.f);
		ExpandboxBody::cls().layout().d_spacing = DimFloat(4.f, 6.f);

		Button::cls().layout().d_align = DimAlign(LEFT, CENTER);
		Toggle::cls().layout().d_align = DimAlign(LEFT, CENTER);
		WrapButton::cls().layout().d_align = DimAlign(LEFT, CENTER);
		CloseButton::cls().layout().d_align = DimAlign(RIGHT, CENTER);

		ScrollerKnob::cls().layout().d_sizing = DimSizing(FIXED, MANUAL);
		FillerX::cls().layout().d_sizing = DimSizing(MANUAL, FIXED);

		this->override(Scroller::cls(), SliderKnobX::cls(), ScrollerKnobX::cls());
		this->override(Scroller::cls(), SliderKnobY::cls(), ScrollerKnobY::cls());
	}

	void Styler::defaultSkins()
	{
		// @todo WSIWYG mode for frame OPACITY parameter where any frame inked with background is set as _OPAQUE
		// this will allow to have an editor interface where any rectangle you see can be selected
		// whereas if it was set as _VOID it would not be possible to select it (the pinpointing just passes through)

		// Skins

		TableHead::cls().layout().d_spacing = DimFloat(1.f, 0.f);

		WindowBody::cls().layout().d_padding = BoxFloat(4.f);

		Checkbox::cls().layout().d_size = DimFloat(16.f, 16.f);


		SliderKnobX::cls().layout().d_size = DimFloat(8.f, 0.f);
		SliderKnobY::cls().layout().d_size = DimFloat(0.f, 8.f);

		SliderKnob::cls().skin().mBackgroundColour = Colour::LightGrey;
		SliderKnob::cls().skin().mCornerRadius = 3.f;
		SliderKnob::cls().decline(HOVERED).mBackgroundColour = Colour::Red;

		SliderDisplay::cls().layout().d_align = DimAlign(CENTER, CENTER);

		CloseButton::cls().skin().mImage = Image("close_15");
		CloseButton::cls().skin().mPadding = BoxFloat(4.f);
		CloseButton::cls().decline(HOVERED).mBackgroundColour = Colour::Red;

		DropdownToggle::cls().skin().mBackgroundColour = Colour::MidGrey;
		DropdownToggle::cls().skin().mImage = Image("arrow_down_15");
		DropdownToggle::cls().decline(HOVERED).mBackgroundColour = Colour::Red;

		ExpandboxToggle::cls().skin().mImage = Image("arrow_right_15");
		ExpandboxToggle::cls().decline(ACTIVATED).mImage = Image("arrow_down_15");
		ExpandboxToggle::cls().decline(HOVERED).mBackgroundColour = Colour::Red;
		ExpandboxToggle::cls().decline(DISABLED).mImage = Image("empty_15");
		ExpandboxToggle::cls().decline(static_cast<WidgetState>(ACTIVATED | HOVERED)).mImage = Image("arrow_down_15");
		ExpandboxToggle::cls().subskin(static_cast<WidgetState>(ACTIVATED | HOVERED)).mBackgroundColour = Colour::Red;

		TreeNodeToggle::cls().copySkins(ExpandboxToggle::cls());

		Label::cls().skin().mTextColour = Colour::White;
		Label::cls().skin().mPadding = BoxFloat(2.f);
		Title::cls();
		
		TypeIn::cls().skin().mTextColour = Colour::White;
		TypeIn::cls().skin().mPadding = BoxFloat(2.f);

		Button::cls().skin().mBackgroundColour = Colour::MidGrey;
		Button::cls().skin().mTextColour = Colour::White;
		Button::cls().skin().mPadding = BoxFloat(2.f);
		Button::cls().decline(HOVERED).mBackgroundColour = Colour::Red;
		Button::cls().decline(ACTIVATED).mBackgroundColour = Colour::LightGrey;
		Button::cls().decline(static_cast<WidgetState>(ACTIVATED | HOVERED)).mBackgroundColour = Colour::Red;

		ImgButton::cls().skin().mBackgroundColour = Colour::Transparent;

		CloseButton::cls().skin().mBackgroundColour = Colour::Transparent;
		DropdownToggle::cls().skin().mBackgroundColour = Colour::Transparent;

		//Toggle::cls().copySkins(Button::cls());
		WrapButton::cls().copySkins(Button::cls());

		EmptyStyle::cls().skin().mBackgroundColour = Colour::Transparent;
		DropdownHeader::cls().copySkins(EmptyStyle::cls());

		Dir::cls().copySkins(ImgButton::cls());
		File::cls().copySkins(ImgButton::cls());
		TreeNodeHeader::cls().copySkins(ImgButton::cls());

		ProgressBarX::cls().skin().mBackgroundColour = Colour::LightGrey;
		ProgressBarX::cls().skin().mBorderColour = Colour::White;
		ProgressBarX::cls().skin().mBorderWidth = 0.5f;
		ProgressBarX::cls().layout().d_padding = BoxFloat(1.f, 1.f, 1.f, 1.f);

		FillerX::cls().skin().mBackgroundColour = Colour(0.05f, 0.65f, 1.f, 0.6f);
		FillerY::cls().skin().mBackgroundColour = Colour(0.05f, 0.65f, 1.f, 0.6f);

		ScrollerKnob::cls().skin().mBackgroundColour = Colour::LightGrey;
		ScrollerKnob::cls().decline(HOVERED).mBackgroundColour = Colour::Red;
		ScrollerKnob::cls().decline(PRESSED).mBackgroundColour = Colour::Red;

		ScrollerKnobX::cls().skin().mMargin = BoxFloat(0.f, 4.f, 0.f, 4.f);
		ScrollerKnobY::cls().skin().mMargin = BoxFloat(4.f, 0.f, 4.f, 0.f);

		Scrollbar::cls().skin().mBackgroundColour = Colour::Black;

		Slider::cls().skin().mBackgroundColour = Colour::MidGrey;
		Slider::cls().skin().mCornerRadius = 3.f;

		ScrollUp::cls().skin().mImage = Image("arrow_up_15");
		ScrollUp::cls().skin().mBackgroundColour = Colour::Transparent;
		ScrollUp::cls().decline(HOVERED).mBackgroundColour = Colour::Red;

		ScrollDown::cls().skin().mImage = Image("arrow_down_15");
		ScrollDown::cls().skin().mBackgroundColour = Colour::Transparent;
		ScrollDown::cls().decline(HOVERED).mBackgroundColour = Colour::Red;

		Scroller::cls().skin().mBackgroundColour = Colour::Transparent;

		Dialog::cls().skin().mBackgroundColour = Colour::DarkGrey;

		Tooltip::cls().skin().mPadding = BoxFloat(4.f);
		Tooltip::cls().skin().mTextColour = Colour::White;
		Tooltip::cls().skin().mBackgroundColour = Colour::MidGrey;

		Tree::cls().skin().mBackgroundColour = Colour::Black;
		List::cls().skin().mBackgroundColour = Colour::Black;
		SelectList::cls();

		Window::cls().skin().mBackgroundColour = Colour::AlphaGrey;
		DockWindow::cls().skin().mBackgroundColour = Colour::DarkGrey;
		WindowHeader::cls().skin().mBackgroundColour = Colour::LightGrey;
		WindowFooter::cls().skin().mBackgroundColour = Colour::LightGrey;
		WindowFooter::cls().layout().d_size = DimFloat(0.f, 7.f);

		Tab::cls().skin().mBackgroundColour = Colour::LightGrey;
		TabberHead::cls().skin().mBackgroundColour = Colour::Black;

		ExpandboxHeader::cls().skin().mBackgroundColour = Colour::LightGrey;
		ExpandboxHeader::cls().decline(ACTIVATED).mBackgroundColour = Colour::Red;

		ColumnHeader::cls().skin().mBackgroundColour = Colour::MidGrey;

		Header::cls().skin().mBackgroundColour = Colour::DarkGrey;

		//ExpandboxBody::cls().skin().mBackgroundColour = Colour::DarkGrey;

		TreeNodeBody::cls().skin().mBackgroundColour = Colour::Transparent;

		Caret::cls().skin().mBackgroundColour = Colour::Black;

		TypeIn::cls().skin().mBackgroundColour = Colour::LightGrey;
		TypeIn::cls().skin().mCornerRadius = BoxFloat(3.f, 3.f, 3.f, 3.f);
		TypeIn::cls().decline(ACTIVATED).mBackgroundColour = Colour::Red;

		Dropdown::cls().copySkins(TypeIn::cls());
		DropdownList::cls().skin().mBackgroundColour = Colour::LightGrey;

		Checkbox::cls().skin().mBackgroundColour = Colour::MidGrey;
		Checkbox::cls().decline(HOVERED).mBackgroundColour = Colour::Red;
		Checkbox::cls().decline(ACTIVATED).mBackgroundColour = Colour::LightGrey;
	}
}
