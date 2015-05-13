//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_HTML_H
#define MK_HTML_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Frame/mkInk.h>

#include <emscripten/bind.h>

namespace mk
{
	class HtmlWindowProxy : public InkWindow
	{
	public:
		EMSCRIPTEN_WRAPPER(HtmlWindowProxy);

		InkTarget& screenTarget() { return call<InkTarget&>("screenTarget"); }
	};

	class HtmlTargetProxy : public InkTarget
	{
	public:
		EMSCRIPTEN_WRAPPER(HtmlTargetProxy);

		HtmlTargetProxy()
			: InkTarget(50)
		{}

		unique_ptr<InkLayer> createLayer(Layer& layer, size_t z) { return call<unique_ptr<InkLayer>>("createLayer", layer, z); }
	};

	class HtmlLayerProxy : public InkLayer
	{
	public:
		EMSCRIPTEN_WRAPPER(HtmlLayerProxy);

		HtmlLayerProxy(Layer& layer, InkTarget& target, size_t index) : InkLayer(layer, target, index) {}

		unique_ptr<Inkbox> createInkbox(Frame& frame) { return call<unique_ptr<Inkbox>>("createInkbox", frame); }

		void move(size_t z) { return call<void>("move", z); }
		void show() { return call<void>("show"); }
		void hide() { return call<void>("hide"); }
	};

	class HtmlInkProxy : public wrapper<Inkbox>
	{
	public:
		EMSCRIPTEN_WRAPPER(HtmlInkProxy);

		HtmlInkProxy(Frame& frame)
			: wrapper<Inkbox>(frame)
		{}

		mFrame.cleft();
		mFrame.ctop();
		mFrame.cwidth();
		mFrame.cheight();

		void updateContent() { return call<void>("updateContent"); }
		void updateFrame() { return call<void>("updateFrame"); }
		void updateClip() { return call<void>("updateClip"); }
		void updatePosition() { return call<void>("updatePosition"); }
		void updateStyle() { return call<void>("updateStyle"); }

		void show() { return call<void>("show"); }
		void hide() { return call<void>("hide"); }

		float contentSize(Dimension dim) { return call<float>("contentSize", dim); }
		size_t caretIndex(float x, float y) { return call<size_t>("caretIndex", x, y); }
		void caretCoords(size_t index, float& caretX, float& caretY, float& caretHeight) { return call<void>("caretCoords", index, caretX, caretY, caretHeight); }
	};


	EMSCRIPTEN_BINDINGS(interface)
	{
		class_<Frame>("Frame")
			.function("cleft", &Frame::cleft)
			.function("ctop", &Frame::ctop)
			.function("cwidth", &Frame::cwidth)
			.function("cheight", &Frame::cheight)
			.function("inkstyle", &Frame::inkstyle)
			;

		class_<Image>("Image")
			.field("name", &Image::d_name)
			;

		class_<Shadow>("Shadow")
			.field("xpos", &Shadow::d_xpos)
			.field("ypos", &Shadow::d_ypos)
			.field("blur", &Shadow::d_blur)
			.field("spread", &Shadow::d_spread)
			.field("colour", &Shadow::d_colour)
			;

		class_<Colour>("Colour")
			.function("r", Colour::r)
			.function("g", Colour::g)
			.function("b", Colour::b)
			.function("a", Colour::a)
			;

		class_<BoxFloat>("BoxFloat")
			.function("x0", BoxFloat::x0)
			.function("x1", BoxFloat::x1)
			.function("y0", BoxFloat::y0)
			.function("y1", BoxFloat::y1)
			;

		class_<DimFloat>("DimFloat")
			.function("x", DimFloat::x)
			.function("y", DimFloat::y)
			;

		class_<DimAlign>("DimAlign")
			.function("x", DimAlign::x)
			.function("y", DimAlign::y)
			;

		class_<InkStyle>("InkStyle")
			.function("empty", InkStyle::empty)
			.function("backgroundColour", InkStyle::backgroundColour)
			.function("borderColour", InkStyle::borderColour)
			.function("textColour", InkStyle::textColour)
			.function("textFont", InkStyle::textFont)
			.function("textSize", InkStyle::textSize)
			.function("borderWidth", InkStyle::borderWidth)
			.function("cornerRadius", InkStyle::cornerRadius)
			.function("padding", InkStyle::padding)
			.function("align", InkStyle::align)
			.function("topdownGradient", InkStyle::topdownGradient)
			.function("image", InkStyle::image)
			.function("overlay", InkStyle::overlay)
			.function("tile", InkStyle::tile)
			.function("shadow", InkStyle::shadow)
			;

		class_<InkWindow>("InkWindow")
			.function("screenTarget", &InkWindow::screenTarget, pure_virtual())
			.allow_subclass<HtmlWindowProxy>("HtmlWindowProxy")
			;

		class_<InkTarget>("InkTarget")
			.function("createLayer", &InkTarget::createLayer, pure_virtual())
			.allow_subclass<HtmlTargetProxy>("HtmlTargetProxy")
			;

		class_<InkLayer>("InkLayer")
			.function("createInkbox", &InkLayer::createInkbox, pure_virtual())
			.function("move", &InkLayer::move, pure_virtual())
			.function("show", &InkLayer::show, pure_virtual())
			.function("hide", &InkLayer::hide, pure_virtual())
			.allow_subclass<HtmlLayerProxy>("HtmlInkProxy")
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
			.allow_subclass<HtmlInkProxy>("HtmlInkProxy")
			;
	}
}

#endif
