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
		mOverrides.resize(InkStyle::indexer()->size());

		for(Object* object : InkStyle::indexer()->objects())
			if(object)
			{
				InkStyle* ink = object->as<InkStyle>();
				if(ink->mBackgroundColour.a() > 0.f || ink->mTextColour.a() > 0.f || ink->mBorderColour.a() > 0.f || !ink->mImage.empty())
					ink->mEmpty = false;
			}
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

	Style* Styler::dynamicStyle(const string& name)
	{
		if(this->fetchStyle(name) == nullptr)
			mDynamicStyles.emplace_back(make_unique<Style>(name));
		return this->fetchStyle(name);
	}

	Style* Styler::fetchStyle(const string& name)
	{
		for(auto& style : mDynamicStyles)
			if(style->name() == name)
				return style.get();
		return nullptr;
	}

	void setupUiLayout(Styler* styler)
	{
		// @todo WSIWYG mode for frame OPACITY parameter where any frame inked with background is set as _OPAQUE
		// this will allow to have an editor interface where any rectangle you see can be selected
		// whereas if it was set as _VOID it would not be possible to select it (the pinpointing just passes through)


		// Built-in Layouts

		Cursor::styleCls()->layout()->d_flow = MANUAL;
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

		Control::styleCls()->layout()->d_opacity = _OPAQUE;
		Control::styleCls()->layout()->d_sizing = DimSizing(SHRINK, SHRINK);

		Dialog::styleCls()->layout()->d_layoutDim = DIM_Y;
		Dialog::styleCls()->layout()->d_sizing = DimSizing(EXPAND, SHRINK);
		Dialog::styleCls()->layout()->d_padding = BoxFloat(25.f, 12.f, 25.f, 12.f);
		Dialog::styleCls()->layout()->d_spacing = DimFloat(6.f, 6.f);

		Caret::styleCls()->layout()->d_flow = MANUAL;
		Caret::styleCls()->layout()->d_sizing = DimSizing(FIXED, FIXED);
		
		Window::styleCls()->layout()->d_flow = MANUAL;
		Window::styleCls()->layout()->d_opacity = _OPAQUE;
		Window::styleCls()->layout()->d_layoutDim = DIM_Y;
		Window::styleCls()->layout()->d_size = DimFloat(480.f, 350.f);
		Window::styleCls()->layout()->d_sizing = DimSizing(FIXED, FIXED);

		DockWindow::styleCls()->layout()->d_opacity = _OPAQUE;
		DockWindow::styleCls()->layout()->d_sizing = DimSizing(EXPAND, EXPAND);
		DockWindow::styleCls()->layout()->d_padding = BoxFloat(1.f);

		// Layouts

		styler->inheritLayout(StyleVector({ Button::styleCls(), Checkbox::styleCls() }), Control::styleCls());
		styler->inheritLayout(StyleVector({ ColumnHeader::styleCls(), TabHeader::styleCls(), RadioChoice::styleCls() }), Control::styleCls());
		styler->inheritLayout(StyleVector({ TreeNodeToggle::styleCls(), ExpandboxToggle::styleCls(), DropdownToggle::styleCls(), CloseButton::styleCls() }), Control::styleCls());
		styler->inheritLayout(StyleVector({ SliderKnobX::styleCls(), SliderKnobY::styleCls() }), Control::styleCls());
		styler->inheritLayout(StyleVector({ ScrollerKnobX::styleCls(), ScrollerKnobY::styleCls(), ScrollUp::styleCls(), ScrollDown::styleCls() }), Control::styleCls());
		styler->inheritLayout(StyleVector({ Dir::styleCls(), File::styleCls() }), Control::styleCls());
		styler->inheritLayout(StyleVector({ Label::styleCls(), Icon::styleCls() }), Control::styleCls());

		styler->inheritLayout(StyleVector({ Label::styleCls(), Title::styleCls() }), WrapX::styleCls());
		styler->inheritLayout(StyleVector({ NumberControls::styleCls(), DropdownHeader::styleCls() }), WrapX::styleCls());
		styler->inheritLayout(StyleVector({ Input<bool>::styleCls() }), WrapX::styleCls());

		styler->inheritLayout(StyleVector({ Table::styleCls(), DropdownBox::styleCls(), }), DivY::styleCls());
		styler->inheritLayout(StyleVector({ RadioSwitch::styleCls() }), DivX::styleCls());
		styler->inheritLayout(StyleVector({ Dropdown::styleCls(), DropdownHeader::styleCls(), DropdownChoice::styleCls(), }), DivX::styleCls());
		styler->inheritLayout(StyleVector({ Expandbox::styleCls(), ExpandboxBody::styleCls() }), DivY::styleCls());
		styler->inheritLayout(StyleVector({ TreeNode::styleCls(), TreeNodeBody::styleCls() }), DivY::styleCls());
		styler->inheritLayout(StyleVector({ TabberHead::styleCls(), TableHead::styleCls(), WindowHeader::styleCls(), ExpandboxHeader::styleCls(), TreeNodeHeader::styleCls() }), DivX::styleCls());
		styler->inheritLayout(StyleVector({ Sequence::styleCls(), Header::styleCls() }), DivX::styleCls());

		styler->inheritLayout(StyleVector({ SpacerX::styleCls(), SpacerY::styleCls() }), PartitionX::styleCls());
		styler->inheritLayout(StyleVector({ DocklineX::styleCls(), ScrollSheet::styleCls() }), PartitionX::styleCls());
		styler->inheritLayout(StyleVector({ Page::styleCls() }), PartitionX::styleCls());

		styler->inheritLayout(StyleVector({ Dockspace::styleCls(), Docksection::styleCls(), DocklineY::styleCls() }), PartitionY::styleCls());
		styler->inheritLayout(StyleVector({ WindowBody::styleCls(), Tabber::styleCls(), TabberBody::styleCls(), Tab::styleCls(), Tree::styleCls(), List::styleCls() }), PartitionY::styleCls());

		styler->inheritLayout(StyleVector({ Tooltip::styleCls(), WContextMenu::styleCls() }), Cursor::styleCls());
		
		styler->inheritLayout(StyleVector({ ResizeCursorX::styleCls(), ResizeCursorY::styleCls(), CaretCursor::styleCls() }), Cursor::styleCls());
		styler->inheritLayout(StyleVector({ ResizeCursorDiagLeft::styleCls(), ResizeCursorDiagRight::styleCls(), MoveCursor::styleCls() }), Cursor::styleCls());

		styler->inheritLayout(StyleVector({ TypeIn::styleCls() }), DivX::styleCls());
		styler->inheritLayout(StyleVector({ WValue::styleCls() }), DivX::styleCls());
		styler->inheritLayout(StyleVector({ SliderX::styleCls() }), DivX::styleCls());
		styler->inheritLayout(StyleVector({ SliderY::styleCls() }), DivY::styleCls());
		styler->inheritLayout(StyleVector({ SliderInt::styleCls(), SliderFloat::styleCls() }), DivX::styleCls());
		styler->inheritLayout(StyleVector({ InputInt::styleCls(), InputFloat::styleCls(), InputBool::styleCls(), InputText::styleCls(), InputDropdown::styleCls() }), DivX::styleCls());

		styler->inheritLayout(StyleVector({ ScrollerX::styleCls() }), PartitionX::styleCls());
		styler->inheritLayout(StyleVector({ ScrollerY::styleCls() }), PartitionY::styleCls());
		
		styler->inheritLayout(StyleVector({ RootSheet::styleCls() }), PartitionY::styleCls());

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

		RootSheet::styleCls()->layout()->d_opacity = _OPAQUE;

		TypeIn::styleCls()->layout()->d_opacity = _OPAQUE;
		TypeIn::styleCls()->layout()->d_sizing = DimSizing(EXPAND, SHRINK);

		WindowHeader::styleCls()->layout()->d_opacity = _OPAQUE;
		TableHead::styleCls()->layout()->d_opacity = _OPAQUE;
		ColumnHeader::styleCls()->layout()->d_opacity = _VOID;

		Tree::styleCls()->layout()->d_overflow = SCROLL;
		List::styleCls()->layout()->d_overflow = SCROLL;

		Tree::styleCls()->layout()->d_layoutDim = DIM_X;
		List::styleCls()->layout()->d_layoutDim = DIM_X;
		Directory::styleCls()->layout()->d_layoutDim = DIM_X;
		List::styleCls()->layout()->d_layoutDim = DIM_X;

		List::styleCls()->layout()->d_sizing = DimSizing(CAPPED, CAPPED);
		
		Directory::styleCls()->inheritLayout(List::styleCls());

		ProgressBarX::styleCls()->layout()->d_sizing = DimSizing(EXPAND, SHRINK);
		ProgressBarX::styleCls()->layout()->d_layoutDim = DIM_X;
		ProgressBarY::styleCls()->layout()->d_sizing = DimSizing(SHRINK, EXPAND);
		ProgressBarY::styleCls()->layout()->d_layoutDim = DIM_Y;

		ProgressFillerX::styleCls()->layout()->d_sizing = DimSizing(EXPAND, FIXED);
		ProgressFillerY::styleCls()->layout()->d_sizing = DimSizing(FIXED, EXPAND);
		ProgressFillerX::styleCls()->layout()->d_size[DIM_Y] = 20.f;
		ProgressFillerY::styleCls()->layout()->d_size[DIM_X] = 20.f;

		SliderX::styleCls()->layout()->d_weight = LIST;
		SliderY::styleCls()->layout()->d_weight = LIST;

		ScrollerX::styleCls()->layout()->d_weight = LIST;
		ScrollerY::styleCls()->layout()->d_weight = LIST;

		DocklineY::styleCls()->layout()->d_weight = LIST;
		DocklineX::styleCls()->layout()->d_weight = LIST;
		DocklineY::styleCls()->layout()->d_opacity = _OPAQUE;
		DocklineX::styleCls()->layout()->d_opacity = _OPAQUE;
		DocklineY::styleCls()->layout()->d_spacing = DimFloat(0.f, 5.f);
		DocklineX::styleCls()->layout()->d_spacing = DimFloat(5.f, 0.f);

		WMasterDockline::styleCls()->inheritLayout(DocklineX::styleCls());

		ExpandboxBody::styleCls()->layout()->d_spacing = DimFloat(0.f, 2.f);
		ExpandboxBody::styleCls()->layout()->d_padding = BoxFloat(12.f, 2.f, 0.f, 2.f);

		TreeNodeBody::styleCls()->layout()->d_padding = BoxFloat(24.f, 2.f, 0.f, 2.f);

		Table::styleCls()->layout()->d_spacing = DimFloat(0.f, 2.f);
		Table::styleCls()->layout()->d_layoutDim = DIM_Y;
		Table::styleCls()->layout()->d_weight = TABLE;

		TreeNodeHeader::styleCls()->layout()->d_opacity = _OPAQUE;
		
		DropdownBox::styleCls()->layout()->d_flow = MANUAL;
		DropdownChoice::styleCls()->layout()->d_opacity = _OPAQUE;

		SliderKnobX::styleCls()->layout()->d_sizing = DimSizing(FIXED, FIXED);
		SliderKnobY::styleCls()->layout()->d_sizing = DimSizing(FIXED, FIXED);
		SliderKnobX::styleCls()->layout()->d_size = DimFloat(8.f, 18.f);
		SliderKnobY::styleCls()->layout()->d_size = DimFloat(18.f, 8.f);

		ScrollerKnobX::styleCls()->layout()->d_sizing = DimSizing(EXPAND, EXPAND);
		ScrollerKnobY::styleCls()->layout()->d_sizing = DimSizing(EXPAND, EXPAND);

		Scrollbar::styleCls()->layout()->d_sizing = DimSizing(SHRINK, EXPAND);
		Scrollbar::styleCls()->layout()->d_layoutDim = DIM_Y;

		DropdownToggle::styleCls()->layout()->d_sizing = DimSizing(SHRINK, EXPAND);

		Tab::styleCls()->layout()->d_padding = BoxFloat(0.f, 4.f, 0.f, 0.f);



		// Skins

		EmptyStyle::styleCls()->skin()->mEmpty = true;

		TableHead::styleCls()->layout()->d_spacing[DIM_X] = 1.f;

		WindowBody::styleCls()->layout()->d_padding = BoxFloat(4.f);

		Checkbox::styleCls()->layout()->d_sizing = DimSizing(FIXED, FIXED);
		Checkbox::styleCls()->layout()->d_size = DimFloat(16.f, 16.f);

		Cursor::styleCls()->skin()->mImage = "mousepointer.png";

		ResizeCursorX::styleCls()->skin()->mImage = "resize_h_20.png";
		ResizeCursorY::styleCls()->skin()->mImage = "resize_v_20.png";
		MoveCursor::styleCls()->skin()->mImage = "move_20.png";
		ResizeCursorDiagLeft::styleCls()->skin()->mImage = "resize_diag_left_20.png";
		ResizeCursorDiagRight::styleCls()->skin()->mImage = "resize_diag_right_20.png";
		CaretCursor::styleCls()->skin()->mImage = "caret_white.png";

		SliderKnob::styleCls()->skin()->mBackgroundColour = Colour::LightGrey;
		SliderKnob::styleCls()->skin()->mCornerRadius = 3.f;
		SliderKnob::styleCls()->decline(HOVERED)->mBackgroundColour = Colour::Red;

		CloseButton::styleCls()->skin()->mImage = "close_15.png";
		CloseButton::styleCls()->skin()->mPadding = DimFloat(4.f, 4.f);
		CloseButton::styleCls()->decline(HOVERED)->mBackgroundColour = Colour::Red;

		DropdownToggle::styleCls()->skin()->mBackgroundColour = Colour::MidGrey;
		DropdownToggle::styleCls()->skin()->mImage = "arrow_down_15.png";
		DropdownToggle::styleCls()->decline(HOVERED)->mBackgroundColour = Colour::Red;

		ExpandboxToggle::styleCls()->skin()->mImage = "arrow_right_15.png";
		ExpandboxToggle::styleCls()->decline(ACTIVATED)->mImage = "arrow_down_15.png";
		ExpandboxToggle::styleCls()->decline(HOVERED)->mBackgroundColour = Colour::Red;
		ExpandboxToggle::styleCls()->decline(DISABLED)->mImage = "empty_15.png";
		ExpandboxToggle::styleCls()->decline(static_cast<WidgetState>(ACTIVATED | HOVERED))->mImage = "arrow_down_15.png";
		ExpandboxToggle::styleCls()->subskin(static_cast<WidgetState>(ACTIVATED | HOVERED))->mBackgroundColour = Colour::Red;

		TreeNodeToggle::styleCls()->inheritSkins(ExpandboxToggle::styleCls());
		WEmptyTreeNodeToggle::styleCls()->inheritLayout(TreeNodeToggle::styleCls());
		WEmptyTreeNodeToggle::styleCls()->inheritSkins(TreeNodeToggle::styleCls());

		Label::styleCls()->skin()->mTextColour = Colour::White;
		Label::styleCls()->skin()->mPadding = DimFloat(2.f, 2.f);
		
		Label::styleCls()->inheritSkins(Label::styleCls());
		Title::styleCls()->inheritSkins(Label::styleCls());
		TypeIn::styleCls()->inheritSkins(Label::styleCls());

		Button::styleCls()->skin()->mBackgroundColour = Colour::MidGrey;
		Button::styleCls()->skin()->mTextColour = Colour::White;
		Button::styleCls()->skin()->mPadding = DimFloat(2.f, 2.f);
		Button::styleCls()->decline(HOVERED)->mBackgroundColour = Colour::LightGrey;
		Button::styleCls()->decline(ACTIVATED)->mBackgroundColour = Colour::Red;
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
		ProgressBarX::styleCls()->skin()->mBorderWidth = 1.f;
		ProgressBarX::styleCls()->layout()->d_padding = BoxFloat(1.f, 1.f, 1.f, 1.f);

		ProgressFillerX::styleCls()->skin()->mBackgroundColour = Colour::Blue;
		ProgressFillerY::styleCls()->skin()->mBackgroundColour = Colour::Blue;

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

		ScrollUp::styleCls()->skin()->mImage = "arrow_up_15.png";
		ScrollUp::styleCls()->decline(HOVERED)->mBackgroundColour = Colour::Red;

		ScrollDown::styleCls()->skin()->mImage = "arrow_down_15.png";
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

		Header::styleCls()->layout()->d_padding = BoxFloat(6.f, 6.f, 6.f, 6.f);

		Window::styleCls()->skin()->mBackgroundColour = Colour::AlphaGrey;
		DockWindow::styleCls()->skin()->mBackgroundColour = Colour::DarkGrey;
		WindowHeader::styleCls()->skin()->mBackgroundColour = Colour::LightGrey;
		WindowSizer::styleCls()->skin()->mBackgroundColour = Colour::LightGrey;
		WindowSizer::styleCls()->layout()->d_opacity = _OPAQUE;
		WindowSizer::styleCls()->layout()->d_sizing = DimSizing(EXPAND, FIXED);
		WindowSizer::styleCls()->layout()->d_size[DIM_Y] = 5.f;

		Tab::styleCls()->skin()->mBackgroundColour = Colour::Red;
		TabberHead::styleCls()->skin()->mBackgroundColour = Colour::Black;

		ExpandboxHeader::styleCls()->skin()->mBackgroundColour = Colour::LightGrey;
		ExpandboxHeader::styleCls()->decline(ACTIVATED)->mBackgroundColour = Colour::Red;

		ExpandboxBody::styleCls()->skin()->mBackgroundColour = Colour::DarkGrey;

		TreeNodeBody::styleCls()->skin()->mBackgroundColour = Colour::Transparent;

		Caret::styleCls()->skin()->mBackgroundColour = Colour::Black;

		TypeIn::styleCls()->skin()->mBackgroundColour = Colour::LightGrey;
		TypeIn::styleCls()->skin()->mCornerRadius = 3.f;
		TypeIn::styleCls()->decline(ACTIVATED)->mBackgroundColour = Colour::Red;

		Dropdown::styleCls()->inheritSkins(TypeIn::styleCls());
		DropdownBox::styleCls()->skin()->mBackgroundColour = Colour::LightGrey;

		Checkbox::styleCls()->skin()->mBackgroundColour = Colour::MidGrey;
		Checkbox::styleCls()->decline(HOVERED)->mBackgroundColour = Colour::Red;
		Checkbox::styleCls()->decline(ACTIVATED)->mBackgroundColour = Colour::LightGrey;

		styler->override(Table::styleCls(), List::styleCls(), DivX::styleCls());
	}
}
