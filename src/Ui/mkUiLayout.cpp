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

#include <iostream>

namespace mk
{
	UiLayout::UiLayout()
	{}

	void UiLayout::add(string name)
	{
		mLayoutStyles.add(make_unique<LayoutStyle>(name, FLOW, FLAT, _OPAQUE, false, DimSizing(SHRINK, SHRINK), DimFloat(0.f, 0.f), DIM_Y));
	}

	void UiLayout::add(string name, string base)
	{
		this->add(name);
		this->style(name)->copy(this->style(base));
	}

	void UiLayout::add(StringVector names, string base)
	{
		for(string& name : names)
			this->add(name, base);
	}

	LayoutStyle* UiLayout::style(string name)
	{
		return mLayoutStyles.findNamed(name);
	}

	LayoutStyle* UiLayout::elementStyle(string clas, string overrider)
	{
		std::vector<string> classes = splitString(clas, " ");

		for(string& cls : classes)
		{
			LayoutStyle* style;

			if(mOverrides.find(overrider) != mOverrides.end())
				for(string& overriden : mOverrides[overrider])
					if(overriden == cls || overriden == "")
						return mLayoutStyles.findNamed(overrider + "." + cls);

			style = mLayoutStyles.findNamed(cls);

			if(style)
				return style;
		}

		std::cerr << "Layout Style not found for clas " << clas << std::endl;
		return mLayoutStyles.findNamed("default");
	}

	void UiLayout::addOverride(string stem, string name, string skin)
	{
		mOverrides[stem].push_back(name);
		this->add(stem + "." + name, skin);
	}

	bool UiLayout::hasOverrides(string stem)
	{
		return mOverrides.find(stem) != mOverrides.end();
	}


	UiSkinner::UiSkinner()
	{}

	void UiSkinner::add(string name)
	{
		mSkins.add(make_unique<InkStyle>(name));
	}

	void UiSkinner::add(string name, Colour colour)
	{
		mSkins.add(make_unique<InkStyle>(name, colour, Colour(1.f, 1.f, 1.f)));
	}

	void UiSkinner::add(string name, string base)
	{
		InkStyle* baseskin = this->skin(base);
		this->add(name);
		this->skin(name)->copy(baseskin);
	}

	void UiSkinner::add(StringVector names, string base)
	{
		for(string name : names)
			this->add(name, base);
	}

	InkStyle* UiSkinner::skin(string name)
	{
		return mSkins.findNamed(name);
	}

	InkStyle* UiSkinner::elementSkin(string clas, string overrider)
	{
		std::vector<string> classes = splitString(clas, " ");

		for(string& cls : classes)
		{
			InkStyle* style;

			if(overrider != "")
			{
				//std::cerr << "overrider :: " << overrider << " clas " << clas << std::endl;
				if(mOverrides.find(overrider) != mOverrides.end())
					for(string& overriden : mOverrides[overrider])
						if(overriden == cls || overriden == "")
							return mSkins.findNamed(overrider + "." + cls);
			}

			style = mSkins.findNamed(cls);
			if(style)
				return style;
		}

		return mSkins.findNamed("default");
	}

	void UiSkinner::addOverride(string stem, string name, string skin)
	{
		mOverrides[stem].push_back(name);
		this->add(stem + "." + name, skin);
	}

	bool UiSkinner::hasOverrides(string stem)
	{
		return mOverrides.find(stem) != mOverrides.end();
	}

	void setupUiLayout(UiSkinner* skinner, UiLayout* layout)
	{
		// @todo WSIWYG mode for frame OPACITY parameter where any frame inked with background is set as _OPAQUE
		// this will allow to have an editor interface where any rectangle you see can be selected
		// whereas if it was set as _VOID it would not be possible to select it (the pinpointing just passes through)

		// Skins

		skinner->add("default", Colour(0.f, 0.f, 0.f, 0.f));
		skinner->skin("default")->mTextColour = Colour(1.f, 1.f, 1.f);
		skinner->skin("default")->mPadding = DimFloat(3.f, 3.f);
		//skinner->skin("default")->mBorderColour = Colour(1.f, 1.f, 1.f);
		//skinner->skin("default")->mBorderWidth = 1.f;

		skinner->add("empty");

		skinner->add("black", Colour(0.f, 0.f, 0.f));
		skinner->skin("black")->mPadding = DimFloat(3.f, 3.f);
		skinner->add("grey", Colour(0.3f, 0.3f, 0.3f));
		skinner->skin("grey")->mPadding = DimFloat(3.f, 3.f);
		skinner->add("alphagrey", Colour(0.3f, 0.3f, 0.3f, 0.7f));
		skinner->skin("alphagrey")->mPadding = DimFloat(3.f, 3.f);
		skinner->add("midgrey", Colour(0.45f, 0.45f, 0.45f));
		skinner->skin("midgrey")->mPadding = DimFloat(3.f, 3.f);
		skinner->add("lightgrey", Colour(0.6f, 0.6f, 0.6f));
		skinner->skin("lightgrey")->mPadding = DimFloat(3.f, 3.f);
		skinner->add("red", Colour(1.f, 0.f, 0.f));
		skinner->skin("red")->mPadding = DimFloat(3.f, 3.f);
		skinner->add("pink", Colour(1.f, 0.f, 1.f));
		skinner->skin("pink")->mPadding = DimFloat(3.f, 3.f);
		skinner->add("blue", Colour(0.f, 0.f, 1.f));
		skinner->skin("blue")->mPadding = DimFloat(3.f, 3.f);

		skinner->add("transparent", Colour(0.f, 0.f, 0.f, 0.f));
		skinner->skin("transparent")->mPadding = DimFloat(3.f, 3.f);

		skinner->add("whitetext", Colour(0.f, 0.f, 0.f, 0.f));
		skinner->skin("whitetext")->mTextColour = Colour(1.f, 1.f, 1.f);
		skinner->skin("whitetext")->mPadding = DimFloat(3.f, 3.f);

		skinner->add("blacktext", Colour(0.f, 0.f, 0.f, 0.f));
		skinner->skin("blacktext")->mTextColour = Colour(0.f, 0.f, 0.f);
		skinner->skin("blacktext")->mPadding = DimFloat(3.f, 3.f);

		skinner->add("white", Colour(1.f, 1.f, 1.f));
		skinner->skin("white")->mTextColour = Colour(0.f, 0.f, 0.f);
		skinner->skin("white")->mPadding = DimFloat(3.f, 3.f);

		skinner->add("bgrey", Colour(0.3f, 0.3f, 0.3f));
		//skinner->skin("bgrey")->mBorderColour = Colour(1.f, 1.f, 1.f);
		//skinner->skin("bgrey")->mBorderWidth = 1.f;

		skinner->add("dropdownbutton", "midgrey");
		//skinner->skin("dropdownbutton")->mImageColour = Colour(0.6f, 0.6f, 0.6f);
		skinner->skin("dropdownbutton")->mImage = "arrow_down_15.png";

		skinner->add("dropdownbutton.hovered", "lightgrey");
		skinner->skin("dropdownbutton.hovered")->mBackgroundColour = Colour(1.f, 0.f, 0.f);
		skinner->skin("dropdownbutton")->mSubInks[HOVERED] = skinner->skin("dropdownbutton.hovered");

		skinner->add("sliderknob", "lightgrey");
		skinner->skin("sliderknob")->mCornerRadius = 3.f;

		skinner->add("slidervalue", "lightgrey");
		skinner->skin("slidervalue")->mCornerRadius = 3.f;

		skinner->add("sliderknob.hovered", "red");
		skinner->skin("sliderknob.hovered")->mCornerRadius = 3.f;
		skinner->skin("sliderknob")->mSubInks[HOVERED] = skinner->skin("sliderknob.hovered");

		skinner->add("scrollerknob", "lightgrey");
		skinner->skin("scrollerknob")->mMargin = BoxFloat(4.f, 0.f, 4.f, 0.f);

		skinner->add("scrollerknob.hovered", "red");
		skinner->skin("scrollerknob.hovered")->mMargin = BoxFloat(4.f, 0.f, 4.f, 0.f);
		skinner->skin("scrollerknob")->mSubInks[HOVERED] = skinner->skin("scrollerknob.hovered");

		skinner->add("expandbutton", Colour(1.f, 1.f, 1.f, 0.f));
		skinner->skin("expandbutton")->mImage = "arrow_right_15.png";

		skinner->add("expandbutton.hover", Colour(1.f, 0.f, 0.f));
		skinner->skin("expandbutton.hover")->mImage = "arrow_right_15.png";
		skinner->skin("expandbutton")->mSubInks[HOVERED] = skinner->skin("expandbutton.hover");

		skinner->add("expandbutton.active", Colour(1.f, 1.f, 1.f, 0.f));
		skinner->skin("expandbutton.active")->mImage = "arrow_down_15.png";
		skinner->skin("expandbutton")->mSubInks[ACTIVATED] = skinner->skin("expandbutton.active");

		skinner->add("expandbutton.activehover", Colour(1.f, 0.f, 0.f));
		skinner->skin("expandbutton.activehover")->mImage = "arrow_down_15.png";
		skinner->skin("expandbutton")->mSubInks[ACTIVATED_HOVERED] = skinner->skin("expandbutton.activehover");

		skinner->add("scrollbutton_up", Colour(1.f, 1.f, 1.f, 0.f));
		//skinner->skin("scrollbutton_up")->mImageColour = Colour(0.6f, 0.6f, 0.6f);
		skinner->skin("scrollbutton_up")->mImage = "arrow_up_15.png";

		skinner->add("scrollbutton_up.hovered", "scrollbutton_up");
		skinner->skin("scrollbutton_up.hovered")->mBackgroundColour = Colour(1.f, 0.f, 0.f);
		skinner->skin("scrollbutton_up")->mSubInks[HOVERED] = skinner->skin("scrollbutton_up.hovered");

		skinner->add("scrollbutton_down", Colour(1.f, 1.f, 1.f, 0.f));
		//skinner->skin("scrollbutton_down")->mImageColour = Colour(0.6f, 0.6f, 0.6f);
		skinner->skin("scrollbutton_down")->mImage = "arrow_down_15.png";

		skinner->add("scrollbutton_down.hovered", "scrollbutton_down");
		skinner->skin("scrollbutton_down.hovered")->mBackgroundColour = Colour(1.f, 0.f, 0.f);
		skinner->skin("scrollbutton_down")->mSubInks[HOVERED] = skinner->skin("scrollbutton_down.hovered");

		skinner->add("cursor", Colour(1.f, 1.f, 1.f, 0.f));
		skinner->skin("cursor")->mImage = "mousepointer.png";

		skinner->add("resize_v", Colour(1.f, 1.f, 1.f, 0.f));
		skinner->skin("resize_v")->mImage = "resize_v_20.png";

		skinner->add("resize_h", Colour(1.f, 1.f, 1.f, 0.f));
		skinner->skin("resize_h")->mImage = "resize_h_20.png";


		skinner->add("scrollbar", "black");

		skinner->add("slider", "midgrey");
		skinner->skin("slider")->mCornerRadius = 3.f;

		skinner->add("xslider", "slider");
		skinner->add("yslider", "slider");

		skinner->add("xscroller", "black");
		skinner->add("yscroller", "black");

		skinner->add("xsliderknob", "sliderknob");
		skinner->add("ysliderknob", "sliderknob");

		skinner->add("xscrollerknob", "scrollerknob");
		skinner->add("yscrollerknob", "scrollerknob");

		skinner->add("button", "midgrey");
		skinner->skin("button")->mSubInks[HOVERED] = skinner->skin("lightgrey");
		skinner->skin("button")->mSubInks[ACTIVATED] = skinner->skin("red");
		skinner->skin("button")->mSubInks[ACTIVATED_HOVERED] = skinner->skin("red");

		skinner->add("imagebutton", "transparent");
		skinner->skin("imagebutton")->mSubInks[HOVERED] = skinner->skin("lightgrey");
		skinner->skin("imagebutton")->mSubInks[ACTIVATED] = skinner->skin("red");
		skinner->skin("imagebutton")->mSubInks[ACTIVATED_HOVERED] = skinner->skin("red");

		skinner->add("hook", "button");
		skinner->add("tabheader", "button");
		skinner->add("columnheader", "button");

		skinner->add("dropdownheader", "empty");
		
		skinner->add("dropbutton", "midgrey"); // was "empty", not possible at the moment
		skinner->skin("dropbutton")->mSubInks[ACTIVATED] = skinner->skin("red");
		skinner->skin("dropbutton")->mSubInks[HOVERED] = skinner->skin("lightgrey");

		skinner->add("enumid", "blacktext");

		skinner->add("radiobutton", "white"); // was "empty", not possible at the moment
		skinner->skin("radiobutton")->mSubInks[ACTIVATED] = skinner->skin("red");
		skinner->skin("radiobutton")->mSubInks[HOVERED] = skinner->skin("lightgrey");
		skinner->skin("radiobutton")->mSubInks[ACTIVATED_HOVERED] = skinner->skin("lightgrey");

		skinner->add("xdockline", "empty");
		skinner->add("ydockline", "empty");

		skinner->add("xdragline", "button");
		skinner->add("ydragline", "button");

		skinner->add("tooltip", "red");

		skinner->add("label", "whitetext");

		skinner->add("list", "black");
		skinner->add("collection", "black");

		//skinner->add("window", "grey");
		//skinner->skin("window")->mImageSkin = ImageSkin("tlook");

		skinner->add("dockwindow", "black");

		skinner->add("window", "alphagrey");
		skinner->add("windowheader", "lightgrey");

		skinner->add("tlookwindow", "transparent");

		skinner->add("tlookwindowheader", "transparent");
		skinner->skin("tlookwindowheader")->mImageSkin = ImageSkin("tlookhead");

		skinner->add("tlookwindowbody", "transparent");
		skinner->skin("tlookwindowbody")->mImageSkin = ImageSkin("tlook");
		skinner->skin("tlookwindowbody")->mMargin = BoxFloat(10.f, -5.f, 5.f, 0.f);

		skinner->addOverride("uieditboard", "window", "tlookwindow");
		skinner->addOverride("uieditboard", "windowheader", "tlookwindowheader");
		skinner->addOverride("uieditboard", "windowbody", "tlookwindowbody");

		skinner->add("ceguibutton", "transparent");
		skinner->skin("ceguibutton")->mImageSkin = ImageSkin("tlookbutton");
		skinner->skin("ceguibutton")->mPadding = DimFloat(20.f, 8.f);

		skinner->add("radioswitch", "white");


		skinner->add("tab", "red");
		skinner->add("headtabs", "black");

		skinner->add("expandboxheader", "lightgrey");
		skinner->skin("expandboxheader")->mSubInks[ACTIVATED] = skinner->skin("red");

		skinner->add("expandboxcontainer", "grey");

		skinner->add("treenodeheader", "transparent");
		skinner->skin("treenodeheader")->mSubInks[ACTIVATED] = skinner->skin("red");

		skinner->add("treenodecontainer", "transparent");

		skinner->add("typein", "lightgrey");
		skinner->skin("typein")->mCornerRadius = 3.f;

		skinner->add("typein.active", "red");
		skinner->skin("typein.active")->mCornerRadius = 3.f;
		skinner->skin("typein")->mSubInks[ACTIVATED] = skinner->skin("typein.active");

		skinner->add("dropdown", "typein");
		skinner->add("dropdownbox", "lightgrey");

		skinner->add("bool", "midgrey");
		skinner->skin("bool")->mSubInks[ACTIVATED] = skinner->skin("lightgrey");

		//skinner->add(StringVector({ "int", "float", "string", "bool" }), "typein");

		// Built-in Layouts

		layout->add("cursor");
		layout->style("cursor")->d_flow = MANUAL;
		layout->style("cursor")->d_layer = LAYER;
		layout->style("cursor")->d_opacity = _VOID;
		layout->style("cursor")->d_span = DimFloat(0.f, 0.f);
		layout->style("cursor")->d_size = DimFloat(10.f, 18.f);

		layout->add("default");

		layout->add("window");
		layout->style("window")->d_flow = MANUAL;
		layout->style("window")->d_layer = LAYER;
		layout->style("window")->d_layoutDim = DIM_Y;

		layout->style("window")->d_span = DimFloat(0.f, 0.f);
		layout->style("window")->d_size = DimFloat(480.f, 350.f);
		layout->style("window")->d_sizing = DimSizing(FIXED, FIXED);

		layout->add("shrinkwindow", "window");
		layout->style("shrinkwindow")->d_span = DimFloat(0.f, 0.f);
		layout->style("shrinkwindow")->d_size = DimFloat(0.f, 0.f);
		layout->style("shrinkwindow")->d_sizing = DimSizing(SHRINK, SHRINK);

		layout->add("partition");
		layout->style("partition")->d_span = DimFloat(1.f, 1.f);
		layout->style("partition")->d_opacity = _VOID;
		layout->style("partition")->d_layoutDim = DIM_Y;
		layout->style("partition")->d_sizing = DimSizing(EXPAND, EXPAND);

		layout->add("layer");
		layout->style("layer")->d_flow = MANUAL;
		layout->style("layer")->d_layer = LAYER;
		layout->style("layer")->d_opacity = _VOID;
		layout->style("layer")->d_span = DimFloat(1.f, 1.f);
		layout->style("layer")->d_sizing = DimSizing(EXPAND, EXPAND);

		layout->add("div");
		layout->style("div")->d_opacity = _VOID;
		layout->style("div")->d_layoutDim = DIM_X;
		layout->style("div")->d_span = DimFloat(1.f, 0.f); // @todo Div should actually shrink perpendicularly to parent layout dimension
		layout->style("div")->d_sizing = DimSizing(EXPAND, SHRINK);

		layout->add("wrap");
		layout->style("wrap")->d_opacity = _VOID;
		layout->style("wrap")->d_sizing = DimSizing(SHRINK, SHRINK);

		layout->add("wrap_inline");
		layout->style("wrap_inline")->d_layoutDim = DIM_X;
		layout->style("wrap_inline")->d_sizing = DimSizing(SHRINK, SHRINK);

		layout->add("leaf");
		layout->style("leaf")->d_sizing = DimSizing(SHRINK, SHRINK);

		layout->add("fixed");
		layout->style("fixed")->d_sizing = DimSizing(FIXED, FIXED);

		layout->add("dockwindow", "partition");

		layout->style("dockwindow")->d_padding = BoxFloat(1.f);

		layout->style("dockwindow")->d_opacity = _OPAQUE;

		// Layouts

		layout->add(StringVector({ "label", "title", "image", "button", "hook", "tabheader" }), "leaf");

		layout->add(StringVector({ "bool" }), "fixed");
		layout->add(StringVector({ "expandbutton", "closebutton", "dropdownbutton", "scrollbutton", "slidervalue", "xscrollerspacer", "yscrollerspacer" "xsliderspacer", "ysliderspacer", "xscrollerknob", "yscrollerknob", "xsliderknob", "ysliderknob", "checkbox" }), "fixed");

		layout->add(StringVector({ "scrollpartition", "scrollsheet", "scrollbox", "tree", "list", "tab", "docksection", "xdockline", "ydockline", "dockspace", "dockwindowboard", "windowbody", "collection", "tabber", "tabs", "xscroller", "yscroller", "gridline" }), "partition");

		layout->add(StringVector({ "controls", "radioswitch", "radiobutton", "dropdown", "dropdownheader", "dropbutton" }), "wrap_inline");

		layout->add(StringVector({ "columnheader", "dropdown", "dropdownheader", "typein", "value", "string", "int", "float", "intstat", "floatstat", "xslider", "yslider", "sliderint", "sliderfloat", "dropdowninput", "intinput", "floatinput", "boolinput", "textinput", "windowheader", "table", "tablehead", "headtabs", "scrollbar" }), "div");
		layout->add(StringVector({ "expandbox", "expandboxheader", "expandboxcontainer" }), "div");
		layout->add(StringVector({ "treenode", "treenodeheader", "treenodecontainer" }), "div");

		layout->add(StringVector({ "root" }), "layer");

		layout->add(StringVector({ "dropdownbox", "tooltip", "context" }), "shrinkwindow");

		layout->style("dropdownbox")->d_sizing[DIM_X] = EXPAND;
		layout->style("dropdownbox")->d_span[DIM_X] = 1.f;

		layout->style("tablehead")->d_opacity = _OPAQUE;
		layout->style("tablehead")->d_spacing[DIM_X] = 1.f;

		layout->style("windowbody")->d_padding = BoxFloat(4.f);

		layout->style("int")->d_opacity = _OPAQUE;
		layout->style("float")->d_opacity = _OPAQUE;
		layout->style("string")->d_opacity = _OPAQUE;
		layout->style("bool")->d_opacity = _OPAQUE;

		layout->style("checkbox")->d_opacity = _OPAQUE;

		layout->style("bool")->d_size = DimFloat(15.f, 15.f);
		layout->style("checkbox")->d_size = DimFloat(15.f, 15.f);

		layout->style("tree")->d_overflow = SCROLL;
		layout->style("list")->d_overflow = SCROLL;
		layout->style("windowbody")->d_overflow = SCROLL;
		layout->style("scrollpartition")->d_overflow = SCROLL;

		layout->style("list")->d_sizing = DimSizing(CAPPED, CAPPED);

		layout->style("scrollsheet")->d_layoutDim = DIM_X;

		layout->style("docksection")->d_layoutDim = DIM_Y;

		layout->style("ydockline")->d_opacity = _OPAQUE;
		layout->style("xdockline")->d_opacity = _OPAQUE;
		layout->style("ydockline")->d_layoutDim = DIM_Y;
		layout->style("xdockline")->d_layoutDim = DIM_X;
		layout->style("ydockline")->d_spacing = DimFloat(0.f, 5.f);
		layout->style("xdockline")->d_spacing = DimFloat(5.f, 0.f);

		layout->style("expandbox")->d_layoutDim = DIM_Y;
		layout->style("expandboxcontainer")->d_layoutDim = DIM_Y;
		layout->style("expandboxcontainer")->d_spacing[DIM_Y] = 2.f;
		layout->style("expandboxcontainer")->d_padding = BoxFloat(12.f, 2.f, 0.f, 0.f);

		layout->style("treenode")->d_layoutDim = DIM_Y;
		layout->style("treenodecontainer")->d_layoutDim = DIM_Y;
		layout->style("treenodecontainer")->d_padding = BoxFloat(12.f, 2.f, 0.f, 0.f);

		layout->style("scrollpartition")->d_spacing[DIM_Y] = 4.f;

		layout->style("table")->d_spacing[DIM_Y] = 2.f;
		layout->style("table")->d_layoutDim = DIM_Y;

		

		layout->style("dropbutton")->d_opacity = _OPAQUE;

		layout->style("label")->d_opacity = _VOID;

		layout->style("tooltip")->d_opacity = _VOID;

		layout->style("slidervalue")->d_size = DimFloat(40.f, 18.f);

		layout->style("xsliderknob")->d_size = DimFloat(0.f, 18.f);
		layout->style("ysliderknob")->d_size = DimFloat(18.f, 0.f);

		layout->style("xscrollerknob")->d_sizing = DimSizing(FIXED, EXPAND);
		layout->style("yscrollerknob")->d_sizing = DimSizing(EXPAND, FIXED);

		//layout->style("xsliderknob")->d_flow = MANUAL;
		//layout->style("ysliderknob")->d_flow = MANUAL;

		//layout->style("xscrollerknob")->d_flow = MANUAL;
		//layout->style("yscrollerknob")->d_flow = MANUAL;

		layout->style("scrollbar")->d_sizing = DimSizing(SHRINK, EXPAND);
		layout->style("scrollbar")->d_layoutDim = DIM_Y;

		layout->style("closebutton")->d_size = DimFloat(15.f, 15.f);
		layout->style("scrollbutton")->d_size = DimFloat(15.f, 15.f);
		layout->style("expandbutton")->d_size = DimFloat(15.f, 15.f);

		layout->style("dropdownbutton")->d_span[DIM_Y] = 1.f;
		layout->style("dropdownbutton")->d_sizing[DIM_Y] = EXPAND;
		layout->style("dropdownbutton")->d_size = DimFloat(15.f, 0.f);

		layout->style("gridline")->d_layoutDim = DIM_X;

		layout->style("headtabs")->d_layoutDim = DIM_X;

		layout->style("tab")->d_overflow = SCROLL;
		layout->style("tab")->d_layoutDim = DIM_X;

		layout->style("windowheader")->d_opacity = _VOID;

		layout->add("string", "fixed");

		layout->style("tab")->d_padding = BoxFloat(0.f, 4.f, 0.f, 0.f);

		layout->add("newobject", "div");
		layout->addOverride("newobject", "dropdown", "div");

		layout->add("tlookwindowbody", "windowbody");
		layout->style("tlookwindowbody")->d_padding = BoxFloat(20.f, 10.f, 10.f, 10.f);

		layout->add("tlookwindowheader", "windowheader");
		layout->style("tlookwindowheader")->d_sizing[DIM_Y] = FIXED;
		layout->style("tlookwindowheader")->d_size[DIM_Y] = 30.f;

		layout->addOverride("uieditboard", "windowheader", "tlookwindowheader");
		layout->addOverride("uieditboard", "windowbody", "tlookwindowbody");
	}
}
