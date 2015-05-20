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
		toString(value.x0(), css);
		css += "px ";
		toString(value.y0(), css);
		css += "px ";
		toString(value.x1(), css);
		css += "px ";
		toString(value.y1(), css);
		css += "px";
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


	void cssStyle(InkStyle& style, string& css)
	{
		css += "font-style: arial, sans-serif; ";
		css += "font-size: "; toString(style.textSize(), css); css += "px; ";
		css += "text-align: "; cssAlign(style.align().x(), css); css += "; ";
		css += "vertical-align: middle; ";

		if(!style.image().null())
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
		}
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
		if(inkbox.frame().widget().image())
		{
			css += "background-image: url(\"data/interface/uisprites/";
			css += inkbox.frame().widget().image()->d_name;
			css += ".png\"); ";
			css += "backgroundSize:100%; ";
		}
		if(!inkbox.corners().null())
		{
			css += "border-radius: ";
			cssBoxFloat(inkbox.corners(), css);
			css += "; ";
		}
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
		BoxFloat& bwidth = inkbox.skin().borderWidth();
		float width = inkbox.frame().cwidth() - bwidth.x0() - bwidth.x1();
		float height = inkbox.frame().cheight() - bwidth.y0() - bwidth.y1();

		css += "width:";
		toString(width, css);
		css += "px; ";

		css += "height:";
		toString(height, css);
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

	void HtmlInkImpl::recssElement()
	{
		string css;

		cssElement(*this, css);
		cssFrame(*this, css);
		cssPosition(*this, css);
		cssCorners(*this, css);
		cssVisible(*this, css);

		this->elementCSS(css);
	}

	void HtmlInkImpl::recssStyle()
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
			.function("image", &InkStyle::image)
			.function("overlay", &InkStyle::overlay)
			.function("tile", &InkStyle::tile)
			.function("shadow", &InkStyle::shadow)
			;

		class_<InkTarget>("InkTarget")
			.allow_subclass<HtmlTargetProxy>("HtmlTargetProxy", constructor<size_t>())
			;

		class_<InkLayer>("InkLayer")
			.function("move", &InkLayer::move, pure_virtual())
			.function("show", &InkLayer::show, pure_virtual())
			.function("hide", &InkLayer::hide, pure_virtual())
			.allow_subclass<HtmlLayerProxy>("HtmlLayerProxy", constructor<Layer&, InkTarget&, size_t>())
			;

		class_<Inkbox>("Inkbox")
			.function("frame", &Inkbox::frame)
#ifndef EMCPP_IMPL
			.function("updateContent", &Inkbox::updateContent, pure_virtual())
			.function("contentSize", &Inkbox::show, pure_virtual())
#endif
			.function("caretIndex", &Inkbox::hide, pure_virtual())
			.function("caretCoords", &Inkbox::hide, pure_virtual())
			;

		class_<HtmlInkImpl, base<Inkbox>>("HtmlInkImpl")
#ifndef EMCPP_IMPL
			.function("elementCSS", &HtmlInkImpl::elementCSS, pure_virtual())
			.function("styleCSS", &HtmlInkImpl::styleCSS, pure_virtual())
#endif
			.allow_subclass<HtmlInkProxy>("HtmlInkProxy", constructor<Frame&, val>())
			;
	}
}
