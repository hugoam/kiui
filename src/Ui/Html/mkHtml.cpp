//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Html/mkHtml.h>

#include <Ui/Widget/mkWidget.h>

namespace mk
{	
	string rcssStyle(InkStyle& style) { string css; cssStyle(style, css); return css; }
	string rcssElement(Inkbox& inkbox) { string css; cssElement(inkbox, css); return css; }
	string rcssCorners(Inkbox& inkbox) { string css; cssCorners(inkbox, css); return css; }

	void cssBoxFloat(const BoxFloat& value, string& css)
	{
		toString(int(value.x0()), css);
		css += "px ";
		toString(int(value.y0()), css);
		css += "px ";
		toString(int(value.x1()), css);
		css += "px ";
		toString(int(value.y1()), css);
		css += "px";
	}

	string cssBoxFloat(const BoxFloat& value)
	{
		string css;
		cssBoxFloat(value, css);
		return css;
	}

	void cssColour(const Colour& colour, string& css)
	{
		css += "rgba(";
		toString(int(round(colour.r() * 255)), css);
		css += ",";
		toString(int(round(colour.g() * 255)), css);
		css += ",";
		toString(int(round(colour.b() * 255)), css);
		css += ",";
		toString(int(round(colour.a() * 255)), css);
		css += ")";
	}

	void cssColourOffset(const Colour& colour, int offset, string& css)
	{
		css += "rgba(";
		toString(int(round(colour.r() * 255) + offset), css);
		css += ",";
		toString(int(round(colour.g() * 255) + offset), css);
		css += ",";
		toString(int(round(colour.b() * 255) + offset), css);
		css += ",";
		toString(int(round(colour.a() * 255) + offset), css);
		css += ")";
	}

	void cssAlign(Align align, string& css)
	{
		switch(align)
		{
		case LEFT: css += "left"; break;
		case CENTER: css += "center"; break;
		case RIGHT:	css += "right"; break;
		}
	}

	void cssVerticalAlign(Align align, string& css)
	{
		switch(align)
		{
		case LEFT: css += "top"; break;
		case CENTER: css += "middle"; break;
		case RIGHT:	css += "bottom"; break;
		}
	}

	void cssFontStyle(const string& font, string& css)
	{
		css += "arial, sans-serif; ";
	}

	void cssFontSize(int size, string& css)
	{
		toString(size, css); css += "px; ";
	}

	void cssStyle(InkStyle& style, string& css)
	{
		css += "font-style: "; cssFontStyle(style.textFont(), css);
		css += "font-size: "; cssFontSize(style.textSize(), css);
		css += "text-align: "; cssAlign(style.align().x(), css); css += "; ";
		css += "vertical-align: middle; ";

		css += "padding: "; cssBoxFloat(style.padding(), css); css += "; ";
		css += "box-sizing: border-box; ";

		/*if(!style.image().null())
		{
			css += "background-image: url(\"data/interface/uisprites/";
			css += style.image().d_name;
			css += ".png\"); background-size: 100%; ";
		}
		if(!style.overlay().null())
		{
		}
		if(!style.tile().null())
		{
		}*/
		if(!style.backgroundColour().null())
		{
			css += "background-color: ";
			cssColour(style.backgroundColour(), css);
			css += "; ";
		}
		if(!style.textColour().null())
		{
			css += "color: ";
			cssColour(style.textColour(), css);
			css += "; ";
		}
		if(!style.borderColour().null())
		{
			css += "border-color: ";
			cssColour(style.borderColour(), css);
			css += "; ";
		}
		if(!style.topdownGradient().null())
		{
			css += "background: linear-gradient(";
			cssColourOffset(style.backgroundColour(), style.topdownGradient().x(), css);
			css += ",";
			cssColourOffset(style.backgroundColour(), style.topdownGradient().y(), css);
			css += "); ";
		}
		if(!style.shadow().d_null)
		{
			css += "box-shadow: ";
			toString(style.shadow().d_xpos, css);
			css += " ";
			toString(style.shadow().d_ypos, css);
			css += " ";
			toString(style.shadow().d_blur, css);
			css += " ";
			toString(style.shadow().d_spread, css);
			css += " ";
			cssColour(style.shadow().d_colour, css);
			css += "; ";
		}
	}

	void cssElement(Inkbox& inkbox, string& css)
	{
		if(!inkbox.skin().borderWidth().null())
		{
			css += "border-style:solid; ";
			css += "border-width:";
			cssBoxFloat(inkbox.skin().borderWidth(), css);
			css += "; ";
		}
	}

	void cssFrame(Inkbox& inkbox, string& css)
	{
		css += "width:";
		toString(inkbox.frame().cwidth(), css);
		css += "px; ";

		css += "height:";
		toString(inkbox.frame().cheight(), css);
		css += "px; ";
	}

	void cssPosition(Inkbox& inkbox, string& css)
	{
		BoxFloat& bwidth = inkbox.skin().borderWidth();
		float left = inkbox.frame().dposition(DIM_X) - bwidth.x0();
		float top = inkbox.frame().dposition(DIM_Y) - bwidth.y0();

		css += "left:";
		toString(left, css);
		css += "px; ";

		css += "top:";
		toString(top, css);
		css += "px; ";
	}

	void cssCorners(Inkbox& inkbox, string& css)
	{
		if(!inkbox.corners().null())
		{
			css += "border-radius:";
			cssBoxFloat(inkbox.corners(), css);
			css += "; ";
		}
	}

	void cssVisible(Inkbox& inkbox, string& css)
	{
		if(inkbox.visible())
			css += "display:block; ";
		else if(!inkbox.visible())
			css += "display:none; ";
	}

#ifndef EMCPP_PROPERTIES
	void HtmlInk::recssElement()
	{
		mCss.clear();

		mCss += "position:absolute;";

		cssElement(*this, mCss);
		cssFrame(*this, mCss);
		cssPosition(*this, mCss);
		cssCorners(*this, mCss);
		cssVisible(*this, mCss);

		this->elementCSS(mCss);
	}
#else
	void HtmlInk::updateFrame()
	{
		this->updateCorners();

		BoxFloat& bwidth = mFrame.inkstyle().borderWidth();

		if(mFrame.dirty() > Frame::DIRTY_ABSOLUTE)
		{
			float left = mFrame.dposition(DIM_X) - bwidth.x0();
			float top = mFrame.dposition(DIM_Y) - bwidth.y0();

			static val kleft("left");
			static val ktop("top");

			mStyle.set(kleft, toString(left) + "px");
			mStyle.set(ktop, toString(top) + "px");
		}

		if(mFrame.dirty() >= Frame::DIRTY_FRAME)
		{
			float width = mFrame.cwidth() - bwidth.x0() - bwidth.x1();
			float height = mFrame.cheight() - bwidth.y0() - bwidth.y1();

			static val kwidth("width");
			static val kheight("height");

			mStyle.set(kwidth, toString(width) + "px");
			mStyle.set(kheight, toString(height) + "px");
		}

		if(mFrame.widget().image())
		{
			mStyle.set("backgroundImage", "url(\"data/interface/uisprites/" + mFrame.widget().image()->d_name + ".png\")");
			mStyle.set("backgroundSize", "100%");
		}
		if(!mFrame.inkstyle().borderWidth().null())
		{
			mStyle.set("borderStyle", "solid");
			mStyle.set("borderWidth", cssBoxFloat(mFrame.inkstyle().borderWidth()));
		}
		if(!mCorners.null())
		{
			mStyle.set("borderRadius", cssBoxFloat(mCorners));
		}
	}
#endif

	void HtmlInk::recssStyle()
	{
		string css;

		cssStyle(this->skin(), css);

		this->styleCSS(this->skin().name(), css);
	}

	EMSCRIPTEN_BINDINGS(interface)
	{
		function("cssStyle", &rcssStyle);
		function("cssElement", &rcssElement);
		function("cssCorners", &rcssCorners);

		class_<UiWindow>("UiWindow")
			.function("dispatchKeyPressed", &UiWindow::dispatchKeyPressed)
			.function("dispatchKeyReleased", &UiWindow::dispatchKeyReleased)
			.function("dispatchMousePressed", &UiWindow::dispatchMousePressed)
			.function("dispatchMouseMoved", &UiWindow::dispatchMouseMoved)
			.function("dispatchMouseReleased", &UiWindow::dispatchMouseReleased)
			.function("dispatchMouseWheeled", &UiWindow::dispatchMouseWheeled)
			;

		class_<Style>("Style")
			.function("name", &Style::name)
			;

		class_<Widget>("Widget")
			.function("label", &Widget::label)
			.function("image", &Widget::image, allow_raw_pointers())
			;

		class_<Uibox>("Uibox")
			.function("dposition", &Frame::dposition)
			;

		class_<Frame, base<Uibox>>("Frame")
			.function("parent", &Frame::parent, allow_raw_pointers())
			.function("widget", &Frame::widget)
			.function("dabsolute", &Frame::dabsolute)
			.function("cleft", &Frame::cleft)
			.function("ctop", &Frame::ctop)
			.function("cwidth", &Frame::cwidth)
			.function("cheight", &Frame::cheight)
			.function("style", &Frame::style)
			.function("inkbox", &Frame::inkbox)
			.function("inkstyle", &Frame::inkstyle)
			;

		class_<Stripe, base<Frame>>("Stripe")
			;

		class_<Layer>("Layer")
			;

		enum_<MouseButton>("MouseButton")
			.value("NO_BUTTON", NO_BUTTON)
			.value("LEFT_BUTTON", LEFT_BUTTON)
			.value("RIGHT_BUTTON", RIGHT_BUTTON)
			.value("MIDDLE_BUTTON", MIDDLE_BUTTON)
			;

		enum_<Dimension>("Dimension")
			.value("DIM_X", DIM_X)
			.value("DIM_Y", DIM_Y)
			.value("DIM_XX", DIM_XX)
			.value("DIM_YY", DIM_YY)
			.value("DIM_NULL", DIM_NULL)
			;

		enum_<Align>("Align")
			.value("LEFT", LEFT)
			.value("CENTER", CENTER)
			.value("RIGHT", RIGHT)
			;

		class_<Image>("Image")
			.property("name", &Image::d_name)
			;

		class_<Shadow>("Shadow")
			.property("null", &Shadow::d_null)
			.property("xpos", &Shadow::d_xpos)
			.property("ypos", &Shadow::d_ypos)
			.property("blur", &Shadow::d_blur)
			.property("spread", &Shadow::d_spread)
			.property("colour", &Shadow::d_colour)
			;

		class_<Colour>("Colour")
			.function("r", &Colour::r)
			.function("g", &Colour::g)
			.function("b", &Colour::b)
			.function("a", &Colour::a)
			;

		class_<BoxFloat>("BoxFloat")
			.function("null", &BoxFloat::null)
			.function("x0", &BoxFloat::x0)
			.function("x1", &BoxFloat::x1)
			.function("y0", &BoxFloat::y0)
			.function("y1", &BoxFloat::y1)
			;

		class_<DimFloat>("DimFloat")
			.function("x", &DimFloat::x)
			.function("y", &DimFloat::y)
			;

		class_<DimAlign>("DimAlign")
			.function("x", &DimAlign::x)
			.function("y", &DimAlign::y)
			;

		class_<InkStyle>("InkStyle")
			.function("name", &InkStyle::name)
			.function("empty", &InkStyle::empty)
			.function("backgroundColour", &InkStyle::backgroundColour)
			.function("borderColour", &InkStyle::borderColour)
			.function("textColour", &InkStyle::textColour)
			.function("textFont", &InkStyle::textFont)
			.function("textSize", &InkStyle::textSize)
			.function("borderWidth", &InkStyle::borderWidth)
			.function("cornerRadius", &InkStyle::cornerRadius)
			.function("padding", &InkStyle::padding)
			.function("align", &InkStyle::align)
			.function("topdownGradient", &InkStyle::topdownGradient)
			.function("image", &InkStyle::image, allow_raw_pointers())
			.function("overlay", &InkStyle::overlay, allow_raw_pointers())
			.function("tile", &InkStyle::tile, allow_raw_pointers())
			.function("shadow", &InkStyle::shadow)
			;

		class_<InkWindow>("InkWindow")
			;

		class_<InkTarget>("InkTarget")
			.allow_subclass<HtmlTargetProxy>("HtmlTargetProxy", constructor<size_t>())
			;

		class_<InkLayer>("InkLayer")
			;

		class_<Inkbox>("Inkbox")
			.function("frame", &Inkbox::frame)
			;
	}
}
