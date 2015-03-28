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

#include <Ui/Scheme/mkWTabber.h>
#include <Ui/Scheme/mkWDropdown.h>
#include <Ui/Widget/mkWButton.h>
#include <Ui/Scheme/mkWWindow.h>
#include <Ui/Widget/mkWTypeIn.h>
#include <Ui/Widget/mkWContextMenu.h>

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

		ScrollDivY::styleCls()->layout()->d_layoutDim = DIM_X;
		ScrollDivY::styleCls()->layout()->d_sizing = DimSizing(EXPAND, EXPAND);

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

		WWindow::styleCls()->layout()->d_flow = MANUAL;
		WWindow::styleCls()->layout()->d_opacity = _OPAQUE;
		WWindow::styleCls()->layout()->d_layoutDim = DIM_Y;
		WWindow::styleCls()->layout()->d_size = DimFloat(480.f, 350.f);
		WWindow::styleCls()->layout()->d_sizing = DimSizing(FIXED, FIXED);

		WDockWindow::styleCls()->layout()->d_opacity = _OPAQUE;
		WDockWindow::styleCls()->layout()->d_sizing = DimSizing(EXPAND, EXPAND);
		WDockWindow::styleCls()->layout()->d_padding = BoxFloat(1.f);

		// Layouts

		styler->inheritLayout(StyleVector({ WButton::styleCls(), WCheckbox::styleCls() }), Control::styleCls());
		styler->inheritLayout(StyleVector({ WColumnHeader::styleCls(), WTabHeader::styleCls(), WRadioChoice::styleCls() }), Control::styleCls());
		styler->inheritLayout(StyleVector({ WTreeNodeToggle::styleCls(), WExpandboxToggle::styleCls(), WDropdownToggle::styleCls(), WCloseButton::styleCls() }), Control::styleCls());
		styler->inheritLayout(StyleVector({ WSliderKnobX::styleCls(), WSliderKnobY::styleCls() }), Control::styleCls());
		styler->inheritLayout(StyleVector({ WScrollerKnobX::styleCls(), WScrollerKnobY::styleCls(), WScrollUp::styleCls(), WScrollDown::styleCls() }), Control::styleCls());
		styler->inheritLayout(StyleVector({ WIcon::styleCls() }), Control::styleCls());
		styler->inheritLayout(StyleVector({ WDir::styleCls(), WFile::styleCls() }), Control::styleCls());
		styler->inheritLayout(StyleVector({ Label::styleCls(), Image::styleCls(), Hook::styleCls() }), Control::styleCls());

		styler->inheritLayout(StyleVector({ WLabel::styleCls(), WTitle::styleCls() }), WrapX::styleCls());
		styler->inheritLayout(StyleVector({ WNumControls::styleCls(), WRadioSwitch::styleCls(), WDropdown::styleCls(), WDropdownHeader::styleCls() }), WrapX::styleCls());
		styler->inheritLayout(StyleVector({ WInput<bool>::styleCls() }), WrapX::styleCls());

		styler->inheritLayout(StyleVector({ WTable::styleCls(), WDropdownBox::styleCls(), }), DivY::styleCls());
		styler->inheritLayout(StyleVector({ WDropdown::styleCls(), WDropdownHeader::styleCls(), WDropdownChoice::styleCls(), }), DivX::styleCls());
		styler->inheritLayout(StyleVector({ WExpandbox::styleCls(), WExpandboxBody::styleCls() }), DivY::styleCls());
		styler->inheritLayout(StyleVector({ WTreeNode::styleCls(), WTreeNodeBody::styleCls() }), DivY::styleCls());
		styler->inheritLayout(StyleVector({ WTabberHead::styleCls(), WTableHead::styleCls(), WWindowHeader::styleCls(), WExpandboxHeader::styleCls(), WTreeNodeHeader::styleCls() }), DivX::styleCls());
		styler->inheritLayout(StyleVector({ Sequence::styleCls(), Header::styleCls() }), DivX::styleCls());

		styler->inheritLayout(StyleVector({ WSpacerX::styleCls(), WSpacerY::styleCls() }), PartitionX::styleCls());
		styler->inheritLayout(StyleVector({ WDocklineX::styleCls(), WScrollSheet::styleCls() }), PartitionX::styleCls());
		
		styler->inheritLayout(StyleVector({ WDockspace::styleCls(), WDocksection::styleCls(), WDocklineY::styleCls() }), PartitionY::styleCls());
		styler->inheritLayout(StyleVector({ WWindowBody::styleCls(), WTabber::styleCls(), WTabberBody::styleCls(), WTab::styleCls(), WTree::styleCls(), WList::styleCls(), List::styleCls() }), PartitionY::styleCls());

		styler->inheritLayout(StyleVector({ Tooltip::styleCls(), WContextMenu::styleCls() }), WrapY::styleCls());
		
		styler->inheritLayout(StyleVector({ ResizeCursorX::styleCls(), ResizeCursorY::styleCls(), CaretCursor::styleCls() }), Cursor::styleCls());
		styler->inheritLayout(StyleVector({ ResizeCursorDiagLeft::styleCls(), ResizeCursorDiagRight::styleCls(), MoveCursor::styleCls() }), Cursor::styleCls());

		styler->inheritLayout(StyleVector({ WTypeIn::styleCls() }), DivX::styleCls());
		styler->inheritLayout(StyleVector({ WInputBase::styleCls() }), DivX::styleCls());
		styler->inheritLayout(StyleVector({ WSliderX::styleCls() }), DivX::styleCls());
		styler->inheritLayout(StyleVector({ WSliderY::styleCls() }), DivY::styleCls());
		styler->inheritLayout(StyleVector({ SliderInt::styleCls(), SliderFloat::styleCls() }), DivX::styleCls());
		styler->inheritLayout(StyleVector({ InputInt::styleCls(), InputFloat::styleCls(), InputBool::styleCls(), InputText::styleCls(), InputDropdown::styleCls() }), DivX::styleCls());

		styler->inheritLayout(StyleVector({ WScrollerX::styleCls() }), PartitionX::styleCls());
		styler->inheritLayout(StyleVector({ WScrollerY::styleCls() }), PartitionY::styleCls());
		
		styler->inheritLayout(StyleVector({ RootSheet::styleCls() }), PartitionY::styleCls());

		WFile::styleCls()->layout()->d_sizing = DimSizing(EXPAND, SHRINK);
		WDir::styleCls()->layout()->d_sizing = DimSizing(EXPAND, SHRINK);

		WIcon::styleCls()->skin()->mEmpty = false;
		WDir::styleCls()->layout()->d_layoutDim = DIM_X;
		WFile::styleCls()->layout()->d_layoutDim = DIM_X;
		WDir::styleCls()->layout()->d_padding = BoxFloat(2.f, 2.f, 2.f, 2.f);
		WDir::styleCls()->layout()->d_spacing = DimFloat(2.f, 2.f);
		WFile::styleCls()->layout()->d_padding = BoxFloat(2.f, 2.f, 2.f, 2.f);
		WFile::styleCls()->layout()->d_spacing = DimFloat(2.f, 2.f);
		WTreeNodeHeader::styleCls()->layout()->d_padding = BoxFloat(2.f, 2.f, 2.f, 2.f);
		WTreeNodeHeader::styleCls()->layout()->d_spacing = DimFloat(2.f, 2.f);

		RootSheet::styleCls()->layout()->d_opacity = _OPAQUE;

		WTypeIn::styleCls()->layout()->d_opacity = _OPAQUE;
		WTypeIn::styleCls()->layout()->d_sizing = DimSizing(EXPAND, SHRINK);

		WWindowHeader::styleCls()->layout()->d_opacity = _OPAQUE;
		WTableHead::styleCls()->layout()->d_opacity = _OPAQUE;
		WColumnHeader::styleCls()->layout()->d_opacity = _VOID;

		WTree::styleCls()->layout()->d_overflow = SCROLL;
		List::styleCls()->layout()->d_overflow = SCROLL;

		WTree::styleCls()->layout()->d_layoutDim = DIM_X;
		WList::styleCls()->layout()->d_layoutDim = DIM_X;
		WDirectory::styleCls()->layout()->d_layoutDim = DIM_X;
		List::styleCls()->layout()->d_layoutDim = DIM_X;

		List::styleCls()->layout()->d_sizing = DimSizing(CAPPED, CAPPED);
		
		WDirectory::styleCls()->inheritLayout(WList::styleCls());

		WProgressBarX::styleCls()->layout()->d_sizing = DimSizing(EXPAND, SHRINK);
		WProgressBarX::styleCls()->layout()->d_layoutDim = DIM_X;
		WProgressBarY::styleCls()->layout()->d_sizing = DimSizing(SHRINK, EXPAND);
		WProgressBarY::styleCls()->layout()->d_layoutDim = DIM_Y;

		WProgressFillerX::styleCls()->layout()->d_sizing = DimSizing(EXPAND, FIXED);
		WProgressFillerY::styleCls()->layout()->d_sizing = DimSizing(FIXED, EXPAND);
		WProgressFillerX::styleCls()->layout()->d_size[DIM_Y] = 20.f;
		WProgressFillerY::styleCls()->layout()->d_size[DIM_X] = 20.f;

		WSliderX::styleCls()->layout()->d_weight = LIST;
		WSliderY::styleCls()->layout()->d_weight = LIST;

		WScrollerX::styleCls()->layout()->d_weight = LIST;
		WScrollerY::styleCls()->layout()->d_weight = LIST;

		WDocklineY::styleCls()->layout()->d_weight = LIST;
		WDocklineX::styleCls()->layout()->d_weight = LIST;
		WDocklineY::styleCls()->layout()->d_opacity = _OPAQUE;
		WDocklineX::styleCls()->layout()->d_opacity = _OPAQUE;
		WDocklineY::styleCls()->layout()->d_spacing = DimFloat(0.f, 5.f);
		WDocklineX::styleCls()->layout()->d_spacing = DimFloat(5.f, 0.f);

		WMasterDockline::styleCls()->inheritLayout(WDocklineX::styleCls());

		WExpandboxBody::styleCls()->layout()->d_spacing = DimFloat(0.f, 2.f);
		WExpandboxBody::styleCls()->layout()->d_padding = BoxFloat(12.f, 2.f, 0.f, 2.f);

		WTreeNodeBody::styleCls()->layout()->d_padding = BoxFloat(24.f, 2.f, 0.f, 2.f);

		WTable::styleCls()->layout()->d_spacing = DimFloat(0.f, 2.f);
		WTable::styleCls()->layout()->d_layoutDim = DIM_Y;
		WTable::styleCls()->layout()->d_weight = TABLE;

		WTreeNodeHeader::styleCls()->layout()->d_opacity = _OPAQUE;
		
		WDropdownBox::styleCls()->layout()->d_flow = MANUAL;
		WDropdownChoice::styleCls()->layout()->d_opacity = _OPAQUE;

		WSliderKnobX::styleCls()->layout()->d_sizing = DimSizing(FIXED, FIXED);
		WSliderKnobY::styleCls()->layout()->d_sizing = DimSizing(FIXED, FIXED);
		WSliderKnobX::styleCls()->layout()->d_size = DimFloat(8.f, 18.f);
		WSliderKnobY::styleCls()->layout()->d_size = DimFloat(18.f, 8.f);

		WScrollerKnobX::styleCls()->layout()->d_sizing = DimSizing(EXPAND, EXPAND);
		WScrollerKnobY::styleCls()->layout()->d_sizing = DimSizing(EXPAND, EXPAND);

		WScrollbar::styleCls()->layout()->d_sizing = DimSizing(SHRINK, EXPAND);
		WScrollbar::styleCls()->layout()->d_layoutDim = DIM_Y;

		WDropdownToggle::styleCls()->layout()->d_sizing = DimSizing(SHRINK, EXPAND);

		WTab::styleCls()->layout()->d_padding = BoxFloat(0.f, 4.f, 0.f, 0.f);



		// Skins

		EmptyStyle::styleCls()->skin()->mEmpty = true;

		WTableHead::styleCls()->layout()->d_spacing[DIM_X] = 1.f;

		WWindowBody::styleCls()->layout()->d_padding = BoxFloat(4.f);

		WCheckbox::styleCls()->layout()->d_sizing = DimSizing(FIXED, FIXED);
		WCheckbox::styleCls()->layout()->d_size = DimFloat(16.f, 16.f);

		Cursor::styleCls()->skin()->mImage = "mousepointer.png";

		ResizeCursorX::styleCls()->skin()->mImage = "resize_h_20.png";
		ResizeCursorY::styleCls()->skin()->mImage = "resize_v_20.png";
		MoveCursor::styleCls()->skin()->mImage = "move_20.png";
		ResizeCursorDiagLeft::styleCls()->skin()->mImage = "resize_diag_left_20.png";
		ResizeCursorDiagRight::styleCls()->skin()->mImage = "resize_diag_right_20.png";
		CaretCursor::styleCls()->skin()->mImage = "caret_white.png";

		WSliderKnob::styleCls()->skin()->mBackgroundColour = Colour::LightGrey;
		WSliderKnob::styleCls()->skin()->mCornerRadius = 3.f;
		WSliderKnob::styleCls()->decline(HOVERED)->mBackgroundColour = Colour::Red;

		WCloseButton::styleCls()->skin()->mImage = "close_15.png";
		WCloseButton::styleCls()->skin()->mPadding = DimFloat(4.f, 4.f);
		WCloseButton::styleCls()->decline(HOVERED)->mBackgroundColour = Colour::Red;

		WDropdownToggle::styleCls()->skin()->mBackgroundColour = Colour::MidGrey;
		WDropdownToggle::styleCls()->skin()->mImage = "arrow_down_15.png";
		WDropdownToggle::styleCls()->decline(HOVERED)->mBackgroundColour = Colour::Red;

		WExpandboxToggle::styleCls()->skin()->mImage = "arrow_right_15.png";
		WExpandboxToggle::styleCls()->decline(ACTIVATED)->mImage = "arrow_down_15.png";
		WExpandboxToggle::styleCls()->decline(HOVERED)->mBackgroundColour = Colour::Red;
		WExpandboxToggle::styleCls()->decline(DISABLED)->mImage = "empty_15.png";
		WExpandboxToggle::styleCls()->decline(static_cast<WidgetState>(ACTIVATED | HOVERED))->mImage = "arrow_down_15.png";
		WExpandboxToggle::styleCls()->subskin(static_cast<WidgetState>(ACTIVATED | HOVERED))->mBackgroundColour = Colour::Red;

		WTreeNodeToggle::styleCls()->inheritSkins(WExpandboxToggle::styleCls());
		WEmptyTreeNodeToggle::styleCls()->inheritLayout(WTreeNodeToggle::styleCls());
		WEmptyTreeNodeToggle::styleCls()->inheritSkins(WTreeNodeToggle::styleCls());

		WLabel::styleCls()->skin()->mTextColour = Colour::White;
		WLabel::styleCls()->skin()->mPadding = DimFloat(2.f, 2.f);
		
		Label::styleCls()->inheritSkins(WLabel::styleCls());
		WTitle::styleCls()->inheritSkins(WLabel::styleCls());
		WTypeIn::styleCls()->inheritSkins(WLabel::styleCls());

		WButton::styleCls()->skin()->mBackgroundColour = Colour::MidGrey;
		WButton::styleCls()->skin()->mTextColour = Colour::White;
		WButton::styleCls()->skin()->mPadding = DimFloat(2.f, 2.f);
		WButton::styleCls()->decline(HOVERED)->mBackgroundColour = Colour::LightGrey;
		WButton::styleCls()->decline(ACTIVATED)->mBackgroundColour = Colour::Red;
		WButton::styleCls()->decline(static_cast<WidgetState>(ACTIVATED | HOVERED))->mBackgroundColour = Colour::Red;

		WImgButton::styleCls()->inheritSkins(WButton::styleCls());
		WImgButton::styleCls()->skin()->mBackgroundColour = Colour::Transparent;

		//WToggle::styleCls()->inheritSkins(WButton::styleCls());
		Hook::styleCls()->inheritSkins(WButton::styleCls());
		WTabHeader::styleCls()->inheritSkins(WButton::styleCls());
		WColumnHeader::styleCls()->inheritSkins(WButton::styleCls());
		WDropdownChoice::styleCls()->inheritSkins(WButton::styleCls());
		WRadioChoice::styleCls()->inheritSkins(WButton::styleCls());

		WDir::styleCls()->inheritSkins(WImgButton::styleCls());
		WFile::styleCls()->inheritSkins(WImgButton::styleCls());
		WTreeNodeHeader::styleCls()->inheritSkins(WImgButton::styleCls());

		WProgressBarX::styleCls()->skin()->mBackgroundColour = Colour::LightGrey;
		WProgressBarX::styleCls()->skin()->mBorderColour = Colour::White;
		WProgressBarX::styleCls()->skin()->mBorderWidth = 1.f;
		WProgressBarX::styleCls()->layout()->d_padding = BoxFloat(1.f, 1.f, 1.f, 1.f);

		WProgressFillerX::styleCls()->skin()->mBackgroundColour = Colour::Blue;
		WProgressFillerY::styleCls()->skin()->mBackgroundColour = Colour::Blue;

		WSliderKnobX::styleCls()->inheritSkins(WSliderKnob::styleCls());
		WSliderKnobY::styleCls()->inheritSkins(WSliderKnob::styleCls());

		WScrollerKnobX::styleCls()->skin()->mBackgroundColour = Colour::LightGrey;
		WScrollerKnobY::styleCls()->skin()->mBackgroundColour = Colour::LightGrey;

		WScrollerKnobX::styleCls()->skin()->mMargin = BoxFloat(0.f, 4.f, 0.f, 4.f);
		WScrollerKnobY::styleCls()->skin()->mMargin = BoxFloat(4.f, 0.f, 4.f, 0.f);

		WScrollerKnobX::styleCls()->decline(HOVERED)->mBackgroundColour = Colour::Red;
		WScrollerKnobY::styleCls()->decline(HOVERED)->mBackgroundColour = Colour::Red;

		WScrollbar::styleCls()->skin()->mBackgroundColour = Colour::Black;

		WSlider::styleCls()->skin()->mBackgroundColour = Colour::MidGrey;
		WSlider::styleCls()->skin()->mCornerRadius = 3.f;

		WSliderX::styleCls()->inheritSkins(WSlider::styleCls());
		WSliderY::styleCls()->inheritSkins(WSlider::styleCls());

		WScrollUp::styleCls()->skin()->mImage = "arrow_up_15.png";
		WScrollUp::styleCls()->decline(HOVERED)->mBackgroundColour = Colour::Red;

		WScrollDown::styleCls()->skin()->mImage = "arrow_down_15.png";
		WScrollDown::styleCls()->decline(HOVERED)->mBackgroundColour = Colour::Red;

		WScroller::styleCls()->skin()->mBackgroundColour = Colour::Black;

		WDropdownHeader::styleCls()->inheritSkins(EmptyStyle::styleCls());
		WDocklineX::styleCls()->inheritSkins(EmptyStyle::styleCls());
		WDocklineY::styleCls()->inheritSkins(EmptyStyle::styleCls());

		Dialog::styleCls()->skin()->mBackgroundColour = Colour::DarkGrey;

		Tooltip::styleCls()->skin()->mBackgroundColour = Colour::MidGrey;

		WList::styleCls()->skin()->mBackgroundColour = Colour::Black;
		WTree::styleCls()->skin()->mBackgroundColour = Colour::Black;
		List::styleCls()->skin()->mBackgroundColour = Colour::Black;

		Header::styleCls()->layout()->d_padding = BoxFloat(6.f, 6.f, 6.f, 6.f);

		WWindow::styleCls()->skin()->mBackgroundColour = Colour::AlphaGrey;
		WDockWindow::styleCls()->skin()->mBackgroundColour = Colour::DarkGrey;
		WWindowHeader::styleCls()->skin()->mBackgroundColour = Colour::LightGrey;
		WWindowSizer::styleCls()->skin()->mBackgroundColour = Colour::LightGrey;
		WWindowSizer::styleCls()->layout()->d_opacity = _OPAQUE;
		WWindowSizer::styleCls()->layout()->d_sizing = DimSizing(EXPAND, FIXED);
		WWindowSizer::styleCls()->layout()->d_size[DIM_Y] = 5.f;

		WTab::styleCls()->skin()->mBackgroundColour = Colour::Red;
		WTabberHead::styleCls()->skin()->mBackgroundColour = Colour::Black;

		WExpandboxHeader::styleCls()->skin()->mBackgroundColour = Colour::LightGrey;
		WExpandboxHeader::styleCls()->decline(ACTIVATED)->mBackgroundColour = Colour::Red;

		WExpandboxBody::styleCls()->skin()->mBackgroundColour = Colour::DarkGrey;

		WTreeNodeBody::styleCls()->skin()->mBackgroundColour = Colour::Transparent;

		WTypeIn::styleCls()->skin()->mBackgroundColour = Colour::LightGrey;
		WTypeIn::styleCls()->skin()->mCornerRadius = 3.f;
		WTypeIn::styleCls()->decline(ACTIVATED)->mBackgroundColour = Colour::Red;

		WDropdown::styleCls()->inheritSkins(WTypeIn::styleCls());
		WDropdownBox::styleCls()->skin()->mBackgroundColour = Colour::LightGrey;

		WCheckbox::styleCls()->skin()->mBackgroundColour = Colour::MidGrey;
		WCheckbox::styleCls()->decline(HOVERED)->mBackgroundColour = Colour::Red;
		WCheckbox::styleCls()->decline(ACTIVATED)->mBackgroundColour = Colour::LightGrey;

		styler->override(WTable::styleCls(), List::styleCls(), DivX::styleCls());
	}
}
