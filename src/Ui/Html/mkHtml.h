//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_HTML_H
#define MK_HTML_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkLayer.h>
#include <Ui/mkRenderWindow.h>
#include <Ui/mkUiWindow.h>
#include <Ui/Input/mkInputDispatcher.h>

#include <emscripten/bind.h>

using namespace emscripten;

namespace mk
{
	class HtmlTarget : public InkTarget
	{
	public:
		HtmlTarget() : InkTarget(50) {}

		unique_ptr<InkLayer> createLayer(Layer& layer, size_t z)
		{
			return val::global("HtmlLayer").new_(layer, *this, z).as<unique_ptr<InkLayer>>();
		}
	};

	class HtmlWindow : public InkWindow, public RenderWindow, public InputWindow
	{
	public:
		HtmlWindow(size_t width, size_t height, string title, string resourcePath)
			: RenderWindow(width, height, title, 0)
			, mTarget()
			, mUiWindow(resourcePath)
		{
			mUiWindow.setup(*this, *this, nullptr);
		}

		InkTarget& screenTarget() { return mTarget; }
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
		HtmlTarget mTarget;
		UiWindow mUiWindow;
	};

	class HtmlLayerProxy : public wrapper<InkLayer>
	{
	public:
		EMSCRIPTEN_WRAPPER(HtmlLayerProxy);

		unique_ptr<Inkbox> createInkbox(Frame& frame)
		{
			return val::global("HtmlInk").new_(frame).as<unique_ptr<Inkbox>>();
		}

		void move(size_t z) { return call<void>("move", z); }
		void show() { return call<void>("show"); }
		void hide() { return call<void>("hide"); }
	};

	class HtmlInkProxy : public wrapper<Inkbox>
	{
	public:
		EMSCRIPTEN_WRAPPER(HtmlInkProxy);

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
}

#endif
