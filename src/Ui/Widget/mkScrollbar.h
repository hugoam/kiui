//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_SCROLLBAR_H_INCLUDED
#define MK_SCROLLBAR_H_INCLUDED

/* mk */
#include <Object/mkId.h>
#include <Object/String/mkString.h>
#include <Object/Util/mkUpdatable.h>
#include <Ui/mkUiForward.h>
#include <Ui/Widget/mkWidget.h>
#include <Ui/Widget/mkButton.h>
#include <Ui/Widget/mkSlider.h>
#include <Ui/Frame/mkStripe.h>

#include <memory>

namespace mk
{
	class MK_UI_EXPORT Scroller : public Slider
	{
	public:
		Scroller(Dimension dim);

		void sliderStep(float offset, bool ended);

		static StyleType& cls() { static StyleType ty(Slider::cls()); return ty; }
	};

	class MK_UI_EXPORT ScrollerX : public Scroller
	{
	public:
		ScrollerX();
	};

	class MK_UI_EXPORT ScrollerY : public Scroller
	{
	public:
		ScrollerY();
	};

	class MK_UI_EXPORT ScrollerKnob : public SliderKnob
	{
	public:
		ScrollerKnob(Dimension dim);

		static StyleType& cls() { static StyleType ty(SliderKnob::cls()); return ty; }
	};

	class MK_UI_EXPORT ScrollerKnobX : public ScrollerKnob
	{
	public:
		ScrollerKnobX();

		static StyleType& cls() { static StyleType ty(ScrollerKnob::cls()); return ty; }
	};

	class MK_UI_EXPORT ScrollerKnobY : public ScrollerKnob
	{
	public:
		ScrollerKnobY();

		static StyleType& cls() { static StyleType ty(ScrollerKnob::cls()); return ty; }
	};

	class MK_UI_EXPORT ScrollUp : public Button
	{
	public:
		ScrollUp(const Trigger& trigger);

		static StyleType& cls() { static StyleType ty(Button::cls()); return ty; }
	};

	class MK_UI_EXPORT ScrollDown : public Button
	{
	public:
		ScrollDown(const Trigger& trigger);

		static StyleType& cls() { static StyleType ty(Button::cls()); return ty; }
	};

	class MK_UI_EXPORT _I_ Scrollbar : public Sheet
	{
	public:
		Scrollbar(Sheet& sheet);
		~Scrollbar();

		void show();
		void hide();
	
		void scrollup();
		void scrolldown();
		void scroll(float offset);
		void nextFrame(size_t tick, size_t delta);

		static StyleType& cls() { static StyleType ty(Sheet::cls()); return ty; }

	protected:
		Sheet& mSheet;
		Button& mUp;
		Scroller& mScroller;
		Button& mDown;
	};

	class MK_UI_EXPORT ScrollArea : public Sheet
	{
	public:
		ScrollArea(Sheet& sheet);

		Scrollbar& scrollbar() { return mScrollbar; }

		static StyleType& cls() { static StyleType ty(Sheet::cls()); return ty; }

	protected:
		Scrollbar& mScrollbar;
	};
}

#endif // MK_SCROLLBAR_H_INCLUDED
