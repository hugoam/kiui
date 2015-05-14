//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Html/mkHtml.h>

#include <Ui/Widget/mkWidget.h>

namespace mk
{

	EMSCRIPTEN_BINDINGS(interface)
	{
		class_<Widget>("Widget")
			.function("label", &Widget::label)
			;

		class_<Frame>("Frame")
			.function("widget", &Frame::widget)
			.function("dabsolute", &Frame::dabsolute)
			.function("cleft", &Frame::cleft)
			.function("ctop", &Frame::ctop)
			.function("cwidth", &Frame::cwidth)
			.function("cheight", &Frame::cheight)
			.function("inkstyle", &Frame::inkstyle)
			;

		class_<Layer>("Layer")
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
			;

		class_<HtmlTarget, base<InkTarget>>("HtmlTarget")
			;

		class_<InkLayer>("InkLayer")
			//.function("createInkbox", &InkLayer::createInkbox, pure_virtual())
			.function("move", &InkLayer::move, pure_virtual())
			.function("show", &InkLayer::show, pure_virtual())
			.function("hide", &InkLayer::hide, pure_virtual())
			.allow_subclass<HtmlLayerProxy>("HtmlLayerProxy", constructor<Layer&, InkTarget&, size_t>())
			;

		class_<Inkbox>("Inkbox")
			.function("frame", &Inkbox::frame)
			.function("updateContent", &Inkbox::updateContent, pure_virtual())
			.function("updateFrame", &Inkbox::updateFrame, pure_virtual())
			.function("updateClip", &Inkbox::updateClip, pure_virtual())
			.function("updatePosition", &Inkbox::updatePosition, pure_virtual())
			.function("updateStyle", &Inkbox::updateStyle, pure_virtual())
			.function("show", &Inkbox::show, pure_virtual())
			.function("hide", &Inkbox::hide, pure_virtual())
			.function("contentSize", &Inkbox::show, pure_virtual())
			.function("caretIndex", &Inkbox::hide, pure_virtual())
			.function("caretCoords", &Inkbox::hide, pure_virtual())
			.allow_subclass<HtmlInkProxy>("HtmlInkProxy", constructor<Frame&>())
			;
	}
}
