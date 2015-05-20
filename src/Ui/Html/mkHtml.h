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

//#define EMCPP_IMPL

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

	class HtmlTargetProxy : public wrapper<InkTarget>
	{
	public:
		EMSCRIPTEN_WRAPPER(HtmlTargetProxy);

		unique_ptr<InkLayer> createLayer(Layer& layer, size_t z)
		{
			static val cls = val::global("HtmlLayer");
			return cls.new_(layer, *this, z).as<unique_ptr<InkLayer>>();
		}
	};

	class HtmlLayerProxy : public wrapper<InkLayer>
	{
	public:
		EMSCRIPTEN_WRAPPER(HtmlLayerProxy);

		unique_ptr<Inkbox> createInkbox(Frame& frame)
		{
			static val cls = val::global("HtmlInk");
			return cls.new_(frame).as<unique_ptr<Inkbox>>();
		}

		void move(size_t z) { return call<void>("move", z); }
		void show() { return call<void>("show"); }
		void hide() { return call<void>("hide"); }
	};

	class HtmlInkImpl : public Inkbox
	{
	public:
		HtmlInkImpl(Frame& frame, val element) : Inkbox(frame), mElement(element) {}

		void updateFrame() { this->updateCorners(); if(mFrame.dirty() > Frame::DIRTY_ABSOLUTE) this->recssElement(); }
		void updateStyle() { this->styleCorners(); this->recssStyle(); }

		void show() { mVisible = true; }
		void hide() { mVisible = false; }

		void recssElement();
		void recssStyle();

#ifndef EMCPP_IMPL
		virtual void elementCSS(const string& css) = 0;
		virtual void styleCSS(const string& name, const string& css) = 0;
#else
		void updateContent() { if(!mFrame.widget().label().empty()) mElement.set("textContent", mFrame.widget().label()); }

		void elementCSS(const string& css) { mElement["style"].set("cssText", "position:absolute;" + css); }
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

		static val textSizer()
		{
			static val document = val::global("document");
			static val textSizer = document.call<val>("createElement", val("div"));
			document["body"].call<void>("appendChild", textSizer);
			return textSizer;
		}

		static val imgSizer()
		{
			static val document = val::global("document");
			static val imgSizer = document.call<val>("createElement", val("img"));
			document["body"].call<void>("appendChild", imgSizer);
			return imgSizer;
		}

		float contentSize(Dimension dim)
		{
			if(!mFrame.widget().label().empty())
			{
				static val sizer = textSizer();
				sizer["style"].set("cssText", "position:absolute; height:auto; width:auto; white-space:nowrap;");
				sizer["style"].set("font", mElement["style"]["font"]);
				sizer.set("textContent", mElement["textContent"]);
				return dim == DIM_X ? sizer["clientWidth"].as<float>() : sizer["clientHeight"].as<float>();
			}
			else if(mFrame.widget().image())
			{
				static val sizer = imgSizer();
				sizer.set("src", "data/interface/uisprites/" + mFrame.widget().image()->d_name + ".png");
				return dim == DIM_X ? sizer["naturalWidth"].as<float>() : sizer["naturalHeight"].as<float>();
			}
			return 0.0;
		}
#endif

	protected:
		val mElement;
	};

	class HtmlInkProxy : public wrapper<HtmlInkImpl>
	{
	public:
		EMSCRIPTEN_WRAPPER(HtmlInkProxy);

#ifndef EMCPP_IMPL
		void updateContent() { return call<void>("updateContent"); }

		void elementCSS(const string& css) { return call<void>("elementCSS", css); }
		void styleCSS(const string& name, const string& css) { return call<void>("styleCSS", name, css); }

		float contentSize(Dimension dim) { return call<float>("contentSize", dim); }
#endif

		size_t caretIndex(float x, float y) { return call<size_t>("caretIndex", x, y); }
		void caretCoords(size_t index, float& caretX, float& caretY, float& caretHeight) { return call<void>("caretCoords", index, caretX, caretY, caretHeight); }
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
