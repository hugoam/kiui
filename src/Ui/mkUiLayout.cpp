//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/mkUiLayout.h>

#include <Ui/mkUiWindow.h>

#include <Object/String/mkString.h>
#include <Object/Util/mkMake.h>

#include <Ui/Widget/mkWidget.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkRootSheet.h>

#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>

#include <Ui/Scheme/mkTabber.h>
#include <Ui/Scheme/mkDropdown.h>
#include <Ui/Widget/mkButton.h>
#include <Ui/Scheme/mkWindow.h>
#include <Ui/Widget/mkTypeIn.h>
#include <Ui/Widget/mkContextMenu.h>

#include <Ui/Controller/mkController.h>

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
		this->setupTypes();

		mOverrides.resize(InkStyle::indexer()->size());

		for(Object* object : InkStyle::indexer()->objects())
			if(object)
			{
				InkStyle* ink = object->as<InkStyle>();
				if(ink->mBackgroundColour.a() > 0.f || ink->mTextColour.a() > 0.f || ink->mBorderColour.a() > 0.f || !ink->mImage.empty())
					ink->mEmpty = false;
			}
	}

	void Styler::reset()
	{
		for(Object* object : Style::indexer()->objects())
			if(object)
				object->as<Style>()->reset();
	}

	void Styler::inheritLayout(StyleVector styles, Style* base)
	{
		for(Style* style : styles)
			style->inheritLayout(base);
	}

	void Styler::inheritSkins(StyleVector styles, Style* base)
	{
		for(Style* style : styles)
			style->inheritSkins(base);
	}

	Style* Styler::fetchOverride(Style* style, Style* overrider)
	{
		if(mOverrides[overrider->id()].size() > 0)
			for(StyleOverride& override : mOverrides[overrider->id()])
				if(override.mStyle == style)
					return override.mOverride;

		return nullptr;
	}

	void Styler::override(Style* stem, Style* overrideWhat, Style* overrideWith)
	{
		if(mOverrides.size() <= stem->id())
			mOverrides.resize(stem->id() + 1);

		mOverrides[stem->id()].emplace_back();
		mOverrides[stem->id()].back().mStyle = overrideWhat;
		mOverrides[stem->id()].back().mOverride = overrideWith;
	}

	void Styler::override(const string& stem, const string& style, const string& overrider)
	{
		this->override(this->fetchStyle(stem), this->fetchStyle(style), this->fetchStyle(overrider));
	}

	Style* Styler::dynamicStyle(const string& name)
	{
		if(this->fetchStyle(name) == nullptr)
			mDynamicStyles.emplace_back(make_unique<Style>(name));
		return this->fetchStyle(name);
	}

	Style* Styler::fetchStyle(const string& name)
	{
		for(Object* object : Style::indexer()->objects())
			if(object && object->as<Style>()->name() == name)
				return object->as<Style>();
		return nullptr;
	}

	void Styler::setupTypes()
	{
		RootSheet::cls()->setupName("RootSheet");

		ScrollSheet::cls()->setupName("ScrollSheet");
		Page::cls()->setupName("Page");

		Cursor::cls()->setupName("Cursor");

		SliderKnob::cls()->setupName("SliderKnob");
		CloseButton::cls()->setupName("CloseButton");

		DropdownToggle::cls()->setupName("DropdownToggle");

		Label::cls()->setupName("Label");
		Title::cls()->setupName("Title");
		Icon::cls()->setupName("Icon");
		SliderDisplay::cls()->setupName("SliderDisplay");

		Button::cls()->setupName("Button");
		ImgButton::cls()->setupName("ImgButton");
		TabHeader::cls()->setupName("TabHeader");
		ColumnHeader::cls()->setupName("ColumnHeader");
		DropdownChoice::cls()->setupName("DropdownChoice");
		RadioChoice::cls()->setupName("RadioChoice");

		Dir::cls()->setupName("Dir");
		File::cls()->setupName("File");
		Directory::cls()->setupName("Directory");

		ProgressBarX::cls()->setupName("ProgressBarX");
		FillerX::cls()->setupName("FillerX");
		FillerY::cls()->setupName("FillerY");

		Slider::cls()->setupName("Slider");
		SliderX::cls()->setupName("SliderX");
		SliderY::cls()->setupName("SliderY");
		SliderKnobX::cls()->setupName("SliderKnobX");
		SliderKnobY::cls()->setupName("SliderKnobY");

		ProgressBarX::cls()->setupName("ProgressBarX");
		ProgressBarY::cls()->setupName("ProgressBarY");

		Scrollbar::cls()->setupName("Scrollbar");
		Scroller::cls()->setupName("Scroller");
		ScrollUp::cls()->setupName("ScrollUp");
		ScrollDown::cls()->setupName("ScrollDown");
		ScrollerKnobX::cls()->setupName("ScrollerKnobX");
		ScrollerKnobY::cls()->setupName("ScrollerKnobY");

		DocklineX::cls()->setupName("DocklineX");
		DocklineY::cls()->setupName("DocklineY");

		Tooltip::cls()->setupName("Tooltip");
		Caret::cls()->setupName("Caret");

		TypeIn::cls()->setupName("TypeIn");
		Checkbox::cls()->setupName("Checkbox");

		Dialog::cls()->setupName("Dialog");
		Header::cls()->setupName("Header");

		List::cls()->setupName("List");

		Window::cls()->setupName("Window");
		DockWindow::cls()->setupName("DockWindow");
		WindowHeader::cls()->setupName("WindowHeader");
		WindowBody::cls()->setupName("WindowBody");
		WindowSizer::cls()->setupName("WindowSizer");

		Table::cls()->setupName("Table");
		TableHead::cls()->setupName("TableHead");

		Tab::cls()->setupName("Tab");
		Tabber::cls()->setupName("Tabber");
		TabberHead::cls()->setupName("TabberHead");

		Expandbox::cls()->setupName("Expandbox");
		ExpandboxToggle::cls()->setupName("ExpandboxToggle");
		ExpandboxHeader::cls()->setupName("ExpandboxHeader");
		ExpandboxBody::cls()->setupName("ExpandboxBody");

		Tree::cls()->setupName("Tree");
		TreeNodeToggle::cls()->setupName("TreeNodeToggle");
		TreeNodeHeader::cls()->setupName("TreeNodeHeader");
		TreeNodeBody::cls()->setupName("TreeNodeBody");

		Dropdown::cls()->setupName("Dropdown");
		DropdownHeader::cls()->setupName("DropdownHeader");
		DropdownBox::cls()->setupName("DropdownBox");

		RadioSwitch::cls()->setupName("RadioSwitch");

		Input<int>::cls()->setupName("Input<int>");
		Input<float>::cls()->setupName("Input<float>");
	}

	void Styler::defaultLayout()
	{
		// Built-in Layouts

		Cursor::styleCls()->layout()->d_flow = MANUAL;
		Cursor::styleCls()->layout()->d_clipping = NOCLIP;
		Cursor::styleCls()->layout()->d_sizing = DimSizing(SHRINK, SHRINK);

		PartitionX::styleCls()->layout()->d_layoutDim = DIM_X;
		PartitionX::styleCls()->layout()->d_sizing = DimSizing(EXPAND, EXPAND);

		PartitionY::styleCls()->layout()->d_layoutDim = DIM_Y;
		PartitionY::styleCls()->layout()->d_sizing = DimSizing(EXPAND, EXPAND);

		DivX::styleCls()->layout()->d_layoutDim = DIM_X;
		DivX::styleCls()->layout()->d_sizing = DimSizing(EXPAND, SHRINK);

		DivY::styleCls()->layout()->d_layoutDim = DIM_Y;
		DivY::styleCls()->layout()->d_sizing = DimSizing(EXPAND, SHRINK);

		WrapY::styleCls()->layout()->d_layoutDim = DIM_Y;
		WrapY::styleCls()->layout()->d_sizing = DimSizing(SHRINK, SHRINK);

		WrapX::styleCls()->layout()->d_layoutDim = DIM_X;
		WrapX::styleCls()->layout()->d_sizing = DimSizing(SHRINK, SHRINK);

		Control::styleCls()->layout()->d_opacity = OPAQUE;
		Control::styleCls()->layout()->d_sizing = DimSizing(SHRINK, SHRINK);

		Dialog::styleCls()->layout()->d_layoutDim = DIM_Y;
		Dialog::styleCls()->layout()->d_sizing = DimSizing(EXPAND, SHRINK);
		Dialog::styleCls()->layout()->d_padding = BoxFloat(25.f, 12.f, 25.f, 12.f);
		Dialog::styleCls()->layout()->d_spacing = DimFloat(6.f, 6.f);

		Caret::styleCls()->layout()->d_flow = MANUAL;
		Caret::styleCls()->layout()->d_sizing = DimSizing(FIXED, FIXED);

		Window::styleCls()->layout()->d_flow = MANUAL;
		Window::styleCls()->layout()->d_opacity = OPAQUE;
		Window::styleCls()->layout()->d_layoutDim = DIM_Y;
		Window::styleCls()->layout()->d_size = DimFloat(480.f, 350.f);
		Window::styleCls()->layout()->d_sizing = DimSizing(FIXED, FIXED);

		DockWindow::styleCls()->layout()->d_opacity = OPAQUE;
		DockWindow::styleCls()->layout()->d_sizing = DimSizing(EXPAND, EXPAND);
		DockWindow::styleCls()->layout()->d_padding = BoxFloat(1.f);

		// Layouts

		this->inheritLayout(StyleVector({ Button::styleCls(), Checkbox::styleCls() }), Control::styleCls());
		this->inheritLayout(StyleVector({ ColumnHeader::styleCls(), TabHeader::styleCls(), RadioChoice::styleCls() }), Control::styleCls());
		this->inheritLayout(StyleVector({ TreeNodeToggle::styleCls(), ExpandboxToggle::styleCls(), DropdownToggle::styleCls(), CloseButton::styleCls() }), Control::styleCls());
		this->inheritLayout(StyleVector({ SliderKnobX::styleCls(), SliderKnobY::styleCls() }), Control::styleCls());
		this->inheritLayout(StyleVector({ ScrollerKnobX::styleCls(), ScrollerKnobY::styleCls(), ScrollUp::styleCls(), ScrollDown::styleCls() }), Control::styleCls());
		this->inheritLayout(StyleVector({ DropdownHeader::styleCls() }), Control::styleCls());
		this->inheritLayout(StyleVector({ Dir::styleCls(), File::styleCls() }), Control::styleCls());
		this->inheritLayout(StyleVector({ Icon::styleCls() }), Control::styleCls());

		this->inheritLayout(StyleVector({ Label::styleCls(), Title::styleCls() }), WrapX::styleCls());
		this->inheritLayout(StyleVector({ Input<bool>::styleCls() }), WrapX::styleCls());

		this->inheritLayout(StyleVector({ Table::styleCls(), DropdownBox::styleCls(), }), DivY::styleCls());
		this->inheritLayout(StyleVector({ RadioSwitch::styleCls() }), DivX::styleCls());
		this->inheritLayout(StyleVector({ Dropdown::styleCls(), DropdownChoice::styleCls(), }), DivX::styleCls());
		this->inheritLayout(StyleVector({ Expandbox::styleCls(), ExpandboxBody::styleCls() }), DivY::styleCls());
		this->inheritLayout(StyleVector({ TreeNode::styleCls(), TreeNodeBody::styleCls() }), DivY::styleCls());
		this->inheritLayout(StyleVector({ TabberHead::styleCls(), TableHead::styleCls(), WindowHeader::styleCls(), ExpandboxHeader::styleCls(), TreeNodeHeader::styleCls() }), DivX::styleCls());
		this->inheritLayout(StyleVector({ Sequence::styleCls(), Header::styleCls() }), DivX::styleCls());

		this->inheritLayout(StyleVector({ SpacerX::styleCls(), SpacerY::styleCls() }), PartitionX::styleCls());
		this->inheritLayout(StyleVector({ DocklineX::styleCls(), ScrollSheet::styleCls() }), PartitionX::styleCls());
		this->inheritLayout(StyleVector({ Page::styleCls() }), PartitionX::styleCls());

		this->inheritLayout(StyleVector({ Dockspace::styleCls(), Docksection::styleCls(), DocklineY::styleCls() }), PartitionY::styleCls());
		this->inheritLayout(StyleVector({ WindowBody::styleCls(), Tabber::styleCls(), TabberBody::styleCls(), Tab::styleCls(), Tree::styleCls(), List::styleCls() }), PartitionY::styleCls());

		this->inheritLayout(StyleVector({ Tooltip::styleCls(), WContextMenu::styleCls() }), Cursor::styleCls());

		this->inheritLayout(StyleVector({ ResizeCursorX::styleCls(), ResizeCursorY::styleCls(), CaretCursor::styleCls() }), Cursor::styleCls());
		this->inheritLayout(StyleVector({ ResizeCursorDiagLeft::styleCls(), ResizeCursorDiagRight::styleCls(), MoveCursor::styleCls() }), Cursor::styleCls());

		this->inheritLayout(StyleVector({ TypeIn::styleCls() }), DivX::styleCls());
		this->inheritLayout(StyleVector({ WValue::styleCls() }), DivX::styleCls());
		this->inheritLayout(StyleVector({ Input<int>::styleCls(), Input<float>::styleCls() }), DivX::styleCls());

		this->inheritLayout(StyleVector({ SliderX::styleCls() }), DivX::styleCls());
		this->inheritLayout(StyleVector({ SliderY::styleCls() }), DivY::styleCls());
		this->inheritLayout(StyleVector({ SliderDisplay::styleCls() }), PartitionX::styleCls());
		this->inheritLayout(StyleVector({ SliderInt::styleCls(), SliderFloat::styleCls() }), DivX::styleCls());

		this->inheritLayout(StyleVector({ InputInt::styleCls(), InputFloat::styleCls(), InputBool::styleCls(), InputText::styleCls(), InputDropdown::styleCls() }), DivX::styleCls());

		this->inheritLayout(StyleVector({ ScrollerX::styleCls() }), PartitionX::styleCls());
		this->inheritLayout(StyleVector({ ScrollerY::styleCls() }), PartitionY::styleCls());

		this->inheritLayout(StyleVector({ RootSheet::styleCls() }), PartitionY::styleCls());

		File::styleCls()->layout()->d_sizing = DimSizing(EXPAND, SHRINK);
		Dir::styleCls()->layout()->d_sizing = DimSizing(EXPAND, SHRINK);

		Icon::styleCls()->skin()->mEmpty = false;
		Dir::styleCls()->layout()->d_layoutDim = DIM_X;
		File::styleCls()->layout()->d_layoutDim = DIM_X;
		Dir::styleCls()->layout()->d_padding = BoxFloat(2.f, 2.f, 2.f, 2.f);
		Dir::styleCls()->layout()->d_spacing = DimFloat(2.f, 2.f);
		File::styleCls()->layout()->d_padding = BoxFloat(2.f, 2.f, 2.f, 2.f);
		File::styleCls()->layout()->d_spacing = DimFloat(2.f, 2.f);
		TreeNodeHeader::styleCls()->layout()->d_padding = BoxFloat(2.f, 2.f, 2.f, 2.f);
		TreeNodeHeader::styleCls()->layout()->d_spacing = DimFloat(2.f, 2.f);

		RootSheet::styleCls()->layout()->d_opacity = OPAQUE;

		TypeIn::styleCls()->layout()->d_opacity = OPAQUE;
		TypeIn::styleCls()->layout()->d_sizing = DimSizing(EXPAND, SHRINK);

		WindowHeader::styleCls()->layout()->d_opacity = OPAQUE;
		WindowSizer::styleCls()->layout()->d_opacity = OPAQUE;
		TableHead::styleCls()->layout()->d_opacity = OPAQUE;
		ColumnHeader::styleCls()->layout()->d_opacity = VOID;

		Tree::styleCls()->layout()->d_overflow = SCROLL;
		List::styleCls()->layout()->d_overflow = SCROLL;

		Tree::styleCls()->layout()->d_layoutDim = DIM_X;
		List::styleCls()->layout()->d_layoutDim = DIM_X;
		Directory::styleCls()->layout()->d_layoutDim = DIM_X;
		List::styleCls()->layout()->d_layoutDim = DIM_X;

		List::styleCls()->layout()->d_sizing = DimSizing(CAPPED, CAPPED);

		Directory::styleCls()->inheritLayout(List::styleCls());

		DropdownHeader::styleCls()->layout()->d_sizing[DIM_X] = EXPAND;

		ProgressBarX::styleCls()->layout()->d_sizing = DimSizing(EXPAND, SHRINK);
		ProgressBarX::styleCls()->layout()->d_layoutDim = DIM_X;
		ProgressBarY::styleCls()->layout()->d_sizing = DimSizing(SHRINK, EXPAND);
		ProgressBarY::styleCls()->layout()->d_layoutDim = DIM_Y;

		FillerX::styleCls()->layout()->d_sizing = DimSizing(EXPAND, FIXED);
		FillerY::styleCls()->layout()->d_sizing = DimSizing(FIXED, EXPAND);
		FillerX::styleCls()->layout()->d_size[DIM_Y] = 20.f;
		FillerY::styleCls()->layout()->d_size[DIM_X] = 20.f;

		SliderDisplay::styleCls()->layout()->d_flow = MANUAL;

		//SliderX::styleCls()->layout()->d_weight = LIST;
		//SliderY::styleCls()->layout()->d_weight = LIST;

		//ScrollerX::styleCls()->layout()->d_weight = LIST;
		//ScrollerY::styleCls()->layout()->d_weight = LIST;

		DocklineY::styleCls()->layout()->d_weight = LIST;
		DocklineX::styleCls()->layout()->d_weight = LIST;
		DocklineY::styleCls()->layout()->d_opacity = OPAQUE;
		DocklineX::styleCls()->layout()->d_opacity = OPAQUE;
		DocklineY::styleCls()->layout()->d_spacing = DimFloat(0.f, 5.f);
		DocklineX::styleCls()->layout()->d_spacing = DimFloat(5.f, 0.f);

		MasterDockline::styleCls()->inheritLayout(DocklineX::styleCls());

		ExpandboxBody::styleCls()->layout()->d_spacing = DimFloat(0.f, 2.f);
		ExpandboxBody::styleCls()->layout()->d_padding = BoxFloat(12.f, 2.f, 0.f, 2.f);

		TreeNodeBody::styleCls()->layout()->d_padding = BoxFloat(24.f, 2.f, 0.f, 2.f);

		Table::styleCls()->layout()->d_spacing = DimFloat(0.f, 2.f);
		Table::styleCls()->layout()->d_layoutDim = DIM_Y;
		Table::styleCls()->layout()->d_weight = TABLE;

		TreeNodeHeader::styleCls()->layout()->d_opacity = OPAQUE;

		DropdownBox::styleCls()->layout()->d_flow = MANUAL;
		DropdownBox::styleCls()->layout()->d_clipping = NOCLIP;
		DropdownChoice::styleCls()->layout()->d_opacity = OPAQUE;

		SliderKnobX::styleCls()->layout()->d_sizing = DimSizing(FIXED, EXPAND);
		SliderKnobY::styleCls()->layout()->d_sizing = DimSizing(EXPAND, FIXED);
		SliderKnobX::styleCls()->layout()->d_size = DimFloat(8.f, 18.f);
		SliderKnobY::styleCls()->layout()->d_size = DimFloat(18.f, 8.f);

		ScrollerKnobX::styleCls()->layout()->d_sizing = DimSizing(EXPAND, EXPAND);
		ScrollerKnobY::styleCls()->layout()->d_sizing = DimSizing(EXPAND, EXPAND);

		Scrollbar::styleCls()->layout()->d_sizing = DimSizing(SHRINK, EXPAND);
		Scrollbar::styleCls()->layout()->d_layoutDim = DIM_Y;

		Tab::styleCls()->layout()->d_padding = BoxFloat(0.f, 4.f, 0.f, 0.f);

		Header::styleCls()->layout()->d_padding = BoxFloat(6.f, 6.f, 6.f, 6.f);

		EmptyStyle::styleCls()->skin()->mEmpty = true;

		Cursor::styleCls()->skin()->mImage = "mousepointer";

		ResizeCursorX::styleCls()->skin()->mImage = "resize_h_20";
		ResizeCursorY::styleCls()->skin()->mImage = "resize_v_20";
		MoveCursor::styleCls()->skin()->mImage = "move_20";
		ResizeCursorDiagLeft::styleCls()->skin()->mImage = "resize_diag_left_20";
		ResizeCursorDiagRight::styleCls()->skin()->mImage = "resize_diag_right_20";
		CaretCursor::styleCls()->skin()->mImage = "caret_white";
	}

	void Styler::defaultSkins()
	{
		// @todo WSIWYG mode for frame OPACITY parameter where any frame inked with background is set as _OPAQUE
		// this will allow to have an editor interface where any rectangle you see can be selected
		// whereas if it was set as _VOID it would not be possible to select it (the pinpointing just passes through)

		// Skins

		TableHead::styleCls()->layout()->d_spacing[DIM_X] = 1.f;

		WindowBody::styleCls()->layout()->d_padding = BoxFloat(4.f);

		Checkbox::styleCls()->layout()->d_sizing = DimSizing(FIXED, FIXED);
		Checkbox::styleCls()->layout()->d_size = DimFloat(16.f, 16.f);

		SliderKnob::styleCls()->skin()->mBackgroundColour = Colour::LightGrey;
		SliderKnob::styleCls()->skin()->mCornerRadius = 3.f;
		SliderKnob::styleCls()->decline(HOVERED)->mBackgroundColour = Colour::Red;

		CloseButton::styleCls()->skin()->mImage = "close_15";
		CloseButton::styleCls()->skin()->mPadding = DimFloat(4.f, 4.f);
		CloseButton::styleCls()->decline(HOVERED)->mBackgroundColour = Colour::Red;

		DropdownToggle::styleCls()->skin()->mBackgroundColour = Colour::MidGrey;
		DropdownToggle::styleCls()->skin()->mImage = "arrow_down_15";
		DropdownToggle::styleCls()->decline(HOVERED)->mBackgroundColour = Colour::Red;

		ExpandboxToggle::styleCls()->skin()->mImage = "arrow_right_15";
		ExpandboxToggle::styleCls()->decline(ACTIVATED)->mImage = "arrow_down_15";
		ExpandboxToggle::styleCls()->decline(HOVERED)->mBackgroundColour = Colour::Red;
		ExpandboxToggle::styleCls()->decline(DISABLED)->mImage = "empty_15";
		ExpandboxToggle::styleCls()->decline(static_cast<WidgetState>(ACTIVATED | HOVERED))->mImage = "arrow_down_15";
		ExpandboxToggle::styleCls()->subskin(static_cast<WidgetState>(ACTIVATED | HOVERED))->mBackgroundColour = Colour::Red;

		TreeNodeToggle::styleCls()->inheritSkins(ExpandboxToggle::styleCls());
		EmptyTreeNodeToggle::styleCls()->inheritLayout(TreeNodeToggle::styleCls());
		EmptyTreeNodeToggle::styleCls()->inheritSkins(TreeNodeToggle::styleCls());

		Label::styleCls()->skin()->mTextColour = Colour::White;
		Label::styleCls()->skin()->mPadding = DimFloat(2.f, 2.f);
		
		Label::styleCls()->inheritSkins(Label::styleCls());
		Title::styleCls()->inheritSkins(Label::styleCls());
		TypeIn::styleCls()->inheritSkins(Label::styleCls());
		SliderDisplay::styleCls()->inheritSkins(Label::styleCls());

		Button::styleCls()->skin()->mBackgroundColour = Colour::MidGrey;
		Button::styleCls()->skin()->mTextColour = Colour::White;
		Button::styleCls()->skin()->mPadding = DimFloat(2.f, 2.f);
		Button::styleCls()->decline(HOVERED)->mBackgroundColour = Colour::Red;
		Button::styleCls()->decline(ACTIVATED)->mBackgroundColour = Colour::LightGrey;
		Button::styleCls()->decline(static_cast<WidgetState>(ACTIVATED | HOVERED))->mBackgroundColour = Colour::Red;

		ImgButton::styleCls()->inheritSkins(Button::styleCls());
		ImgButton::styleCls()->skin()->mBackgroundColour = Colour::Transparent;

		//Toggle::styleCls()->inheritSkins(Button::styleCls());
		TabHeader::styleCls()->inheritSkins(Button::styleCls());
		ColumnHeader::styleCls()->inheritSkins(Button::styleCls());
		DropdownChoice::styleCls()->inheritSkins(Button::styleCls());
		RadioChoice::styleCls()->inheritSkins(Button::styleCls());

		Dir::styleCls()->inheritSkins(ImgButton::styleCls());
		File::styleCls()->inheritSkins(ImgButton::styleCls());
		TreeNodeHeader::styleCls()->inheritSkins(ImgButton::styleCls());

		ProgressBarX::styleCls()->skin()->mBackgroundColour = Colour::LightGrey;
		ProgressBarX::styleCls()->skin()->mBorderColour = Colour::White;
		ProgressBarX::styleCls()->skin()->mBorderWidth = 0.5f;
		ProgressBarX::styleCls()->layout()->d_padding = BoxFloat(1.f, 1.f, 1.f, 1.f);

		FillerX::styleCls()->skin()->mBackgroundColour = Colour(0.05f, 0.65f, 1.f, 0.6f);
		FillerY::styleCls()->skin()->mBackgroundColour = Colour(0.05f, 0.65f, 1.f, 0.6f);

		SliderKnobX::styleCls()->inheritSkins(SliderKnob::styleCls());
		SliderKnobY::styleCls()->inheritSkins(SliderKnob::styleCls());

		ScrollerKnobX::styleCls()->skin()->mBackgroundColour = Colour::LightGrey;
		ScrollerKnobY::styleCls()->skin()->mBackgroundColour = Colour::LightGrey;

		ScrollerKnobX::styleCls()->skin()->mMargin = BoxFloat(0.f, 4.f, 0.f, 4.f);
		ScrollerKnobY::styleCls()->skin()->mMargin = BoxFloat(4.f, 0.f, 4.f, 0.f);

		ScrollerKnobX::styleCls()->decline(HOVERED)->mBackgroundColour = Colour::Red;
		ScrollerKnobY::styleCls()->decline(HOVERED)->mBackgroundColour = Colour::Red;

		Scrollbar::styleCls()->skin()->mBackgroundColour = Colour::Black;

		Slider::styleCls()->skin()->mBackgroundColour = Colour::MidGrey;
		Slider::styleCls()->skin()->mCornerRadius = 3.f;

		SliderX::styleCls()->inheritSkins(Slider::styleCls());
		SliderY::styleCls()->inheritSkins(Slider::styleCls());

		ScrollUp::styleCls()->skin()->mImage = "arrow_up_15";
		ScrollUp::styleCls()->decline(HOVERED)->mBackgroundColour = Colour::Red;

		ScrollDown::styleCls()->skin()->mImage = "arrow_down_15";
		ScrollDown::styleCls()->decline(HOVERED)->mBackgroundColour = Colour::Red;

		Scroller::styleCls()->skin()->mBackgroundColour = Colour::Black;

		DropdownHeader::styleCls()->inheritSkins(EmptyStyle::styleCls());
		DocklineX::styleCls()->inheritSkins(EmptyStyle::styleCls());
		DocklineY::styleCls()->inheritSkins(EmptyStyle::styleCls());

		Dialog::styleCls()->skin()->mBackgroundColour = Colour::DarkGrey;

		Tooltip::styleCls()->skin()->mPadding = DimFloat(4.f, 4.f);
		Tooltip::styleCls()->skin()->mTextColour = Colour::White;
		Tooltip::styleCls()->skin()->mBackgroundColour = Colour::MidGrey;

		Tree::styleCls()->skin()->mBackgroundColour = Colour::Black;
		List::styleCls()->skin()->mBackgroundColour = Colour::Black;

		Window::styleCls()->skin()->mBackgroundColour = Colour::AlphaGrey;
		DockWindow::styleCls()->skin()->mBackgroundColour = Colour::DarkGrey;
		WindowHeader::styleCls()->skin()->mBackgroundColour = Colour::LightGrey;
		WindowSizer::styleCls()->skin()->mBackgroundColour = Colour::LightGrey;
		WindowSizer::styleCls()->layout()->d_sizing = DimSizing(EXPAND, FIXED);
		WindowSizer::styleCls()->layout()->d_size[DIM_Y] = 5.f;

		Tab::styleCls()->skin()->mBackgroundColour = Colour::LightGrey;
		TabberHead::styleCls()->skin()->mBackgroundColour = Colour::Black;

		ExpandboxHeader::styleCls()->skin()->mBackgroundColour = Colour::LightGrey;
		ExpandboxHeader::styleCls()->decline(ACTIVATED)->mBackgroundColour = Colour::Red;

		//ExpandboxBody::styleCls()->skin()->mBackgroundColour = Colour::DarkGrey;

		TreeNodeBody::styleCls()->skin()->mBackgroundColour = Colour::Transparent;

		Caret::styleCls()->skin()->mBackgroundColour = Colour::Black;

		TypeIn::styleCls()->skin()->mBackgroundColour = Colour::LightGrey;
		TypeIn::styleCls()->skin()->mCornerRadius = BoxFloat(3.f, 3.f, 3.f, 3.f);
		TypeIn::styleCls()->decline(ACTIVATED)->mBackgroundColour = Colour::Red;

		Dropdown::styleCls()->inheritSkins(TypeIn::styleCls());
		DropdownBox::styleCls()->skin()->mBackgroundColour = Colour::LightGrey;

		Checkbox::styleCls()->skin()->mBackgroundColour = Colour::MidGrey;
		Checkbox::styleCls()->decline(HOVERED)->mBackgroundColour = Colour::Red;
		Checkbox::styleCls()->decline(ACTIVATED)->mBackgroundColour = Colour::LightGrey;

		this->override(Table::styleCls(), List::styleCls(), DivX::styleCls());
	}
}
