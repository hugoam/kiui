//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_HTML_H
#define MK_HTML_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkLayer.h>
#include <Ui/Widget/mkWidget.h>
#include <Ui/mkRenderWindow.h>
#include <Ui/mkUiWindow.h>
#include <Ui/Input/mkInputDispatcher.h>

#include <emscripten/bind.h>

//#define EMCPP_PROPERTIES

using namespace emscripten;

namespace mk
{
	class HtmlWindow : public InkWindow, public RenderWindow, public InputWindow
	{
	public:
		HtmlWindow(size_t width, size_t height, string title, string resourcePath)
			: RenderWindow(width, height, title, 0)
			, mUiWindow(resourcePath)
			, mTarget(val::global("HtmlTarget").new_(50, width, height, mUiWindow).as<unique_ptr<InkTarget>>())
		{
			mUiWindow.setup(*this, *this, nullptr);
		}

		InkTarget& screenTarget() { return *mTarget.get(); }
		UiWindow& uiWindow() { return mUiWindow; }

		void initInput(InputDispatcher& dispatcher, size_t wndHandle)
		{}

		void resize(size_t width, size_t height)
		{}

		bool nextFrame()
		{
			return mUiWindow.nextFrame();
		}

	protected:
		UiWindow mUiWindow;
		unique_ptr<InkTarget> mTarget;
	};

	class HtmlInk : public Inkbox
	{
	public:
		HtmlInk(Frame& frame)
			: Inkbox(frame)
			, mElement(val::null())
			, mStyle(val::null())
			, mText(val::null())
			, mImage(val::null())
		{
			createElement();
		}

		~HtmlInk()
		{
			static val parentNode("parentNode");
			mElement[parentNode].call<void>("removeChild", mElement);
		}

		val& element() { return mElement; }

#ifndef EMCPP_PROPERTIES
		void updateFrame() { this->updateCorners(); if(mFrame.dirty() > Frame::DIRTY_ABSOLUTE) this->recssElement(); }
		void updateStyle() { this->styleCorners(); this->recssStyle(); mStyle = mElement["style"]; }

		void show() { mVisible = true; }
		void hide() { mVisible = false; }
#else
		void updateStyle() { this->styleCorners(); this->recssStyle(); mStyle = mElement["style"]; }
		void updateFrame();

		void show() { mVisible = true; static val display("display"); static val block("block"); mStyle.set(display, block); }
		void hide() { mVisible = false; static val display("display"); static val none("none"); mStyle.set(display, none); }
#endif

#ifndef EMCPP_PROPERTIES
		void recssElement();
#endif
		void recssStyle();

		void updateContent()
		{
			static val textContent("textContent");
			if(!mFrame.widget().label().empty() && mText.isNull())
				this->createText();
			if(!mFrame.widget().label().empty())
				mText.set(textContent, mFrame.widget().label());

			static val src("src");
			if(mFrame.widget().image() && mImage.isNull())
				this->createImage();
			if(mFrame.widget().image())
				mImage.set(src, "data/interface/uisprites/" + mFrame.widget().image()->d_name + ".png");
		}

		void createElement()
		{
			static val document = val::global("document");
			mElement = document.call<val>("createElement", val("div"));
			mStyle = mElement["style"];
			//this.element.style.position = "absolute";
			if(mFrame.parent())
				static_cast<HtmlInk&>(mFrame.parent()->inkbox()).mElement.call<void>("appendChild", mElement);
			else
				document.call<val>("getElementById", val("main_target")).call<void>("appendChild", mElement);
		}

		void createText()
		{
			static val document = val::global("document");
			static val div("div");
			mText = document.call<val>("createElement", div);
			mText["style"].set("cssText", "height:auto; width:auto; white-space:nowrap; overflow:hidden; ");
			mElement.call<void>("appendChild", mText);
		}

		void createImage()
		{
			static val document = val::global("document");
			static val img("img");
			mImage = document.call<val>("createElement", img);
			mElement.call<void>("appendChild", mImage);
		}

		void elementCSS(const string& css) { static val key("cssText"); mStyle.set(key, css.c_str()); }
		void styleCSS(const string& name, const string& css)
		{
			static val document = val::global("document");
			if(!document.call<val>("getElementById", val(name)).as<bool>())
			{
				val style = document.call<val>("createElement", val("style"));
				style.set("id", val(name));
				style.set("type", val("text/css"));
				style.set("innerHTML", "." + name + " { " + css + " }");
				document["head"].call<void>("appendChild", style);
			}

			mElement.set("className", name);
		}

		float textWidth()
		{
			static val document = val::global("document");
			static val canvas = document.call<val>("createElement", val("canvas"));
			static val context = canvas.call<val>("getContext", val("2d"));

			static val font("font");
			static val textContent("textContent");
			static val width("width");

			context.set(font, mStyle[font]);
			val metrics = context.call<val>("measureText", mText[textContent]);
			return metrics[width].as<float>();
		};

		float contentSize(Dimension dim)
		{
			if(!mFrame.widget().label().empty())
			{
				return dim == DIM_X ? textWidth() : mFrame.inkstyle().textSize();
			}
			else if(mFrame.widget().image())
			{
				static val naturalWidth("naturalWidth");
				static val naturalHeight("naturalHeight");
				return dim == DIM_X ? mImage[naturalWidth].as<float>() : mImage[naturalHeight].as<float>();
			}
			return 0.0;
		}

		size_t caretIndex(float x, float y) { return 0; }
		void caretCoords(size_t index, float& caretX, float& caretY, float& caretHeight) { printf("caretCoords\n"); }

	protected:
		val mElement;
		val mText;
		val mImage;
		val mStyle;
		string mCss;
	};

	class HtmlLayer : public InkLayer
	{
	public:
		HtmlLayer(Layer& layer, InkTarget& target, size_t z) : InkLayer(layer, target, z) {}

		unique_ptr<Inkbox> createInkbox(Frame& frame)
		{
			return make_unique<HtmlInk>(frame);
		}

		void move(size_t pos, size_t z)
		{
			if(!mLayer.bound() || !mLayer.parent()) return;

			static val parentNode("parentNode");
			val parent = static_cast<HtmlInk&>(mLayer.parent()->layer().inkbox()).element();
			val next = static_cast<HtmlInk&>(mLayer.parent()->layer().layers()[pos]->inkbox()).element();
			val element = static_cast<HtmlInk&>(mLayer.inkbox()).element();
			parent[parentNode].call<void>("insertBefore", next, element);
		}

		void show() {}
		void hide() {}
	};

	class HtmlTargetProxy : public wrapper<InkTarget>
	{
	public:
		EMSCRIPTEN_WRAPPER(HtmlTargetProxy);

		unique_ptr<InkLayer> createLayer(Layer& layer, size_t z)
		{
			return make_unique<HtmlLayer>(layer, *this, z);
		}
	};

	void cssStyle(InkStyle& style, string& css);
	void cssElement(Inkbox& inkbox, string& css);
	void cssFrame(Inkbox& inkbox, string& css);
	void cssPosition(Inkbox& inkbox, string& css);
	void cssCorners(Inkbox& inkbox, string& css);
	void cssVisible(Inkbox& inkbox, string& css);

	string rcssStyle(InkStyle& style);
	string rcssElement(Inkbox& inkbox);
	string rcssCorners(Inkbox& inkbox);
}

#endif
