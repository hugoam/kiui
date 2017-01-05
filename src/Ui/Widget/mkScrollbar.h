//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_SCROLLBAR_H
#define MK_SCROLLBAR_H

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
		Scroller(Dimension dim, StyleType& type);

		void sliderStep(float offset, bool ended);

		static StyleType& cls() { static StyleType ty("Scroller", Slider::cls()); return ty; }
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
		ScrollerKnob(Dimension dim, StyleType& type);

		static StyleType& cls() { static StyleType ty("ScrollerKnob", SliderKnob::cls()); return ty; }
	};

	class MK_UI_EXPORT ScrollerKnobX : public ScrollerKnob
	{
	public:
		ScrollerKnobX();

		static StyleType& cls() { static StyleType ty("ScrollerKnobX", ScrollerKnob::cls()); return ty; }
	};

	class MK_UI_EXPORT ScrollerKnobY : public ScrollerKnob
	{
	public:
		ScrollerKnobY();

		static StyleType& cls() { static StyleType ty("ScrollerKnobY", ScrollerKnob::cls()); return ty; }
	};

	class MK_UI_EXPORT ScrollUp : public Button
	{
	public:
		ScrollUp(const Trigger& trigger);

		static StyleType& cls() { static StyleType ty("ScrollUp", Button::cls()); return ty; }
	};

	class MK_UI_EXPORT ScrollDown : public Button
	{
	public:
		ScrollDown(const Trigger& trigger);

		static StyleType& cls() { static StyleType ty("ScrollDown", Button::cls()); return ty; }
	};

	class MK_UI_EXPORT _I_ Scrollbar : public Sheet
	{
	public:
		Scrollbar(Sheet& sheet, Dimension dim = DIM_Y);
		~Scrollbar();

		void scrollup();
		void scrolldown();
		void scroll(float offset);
		void nextFrame(size_t tick, size_t delta);

		static StyleType& cls() { static StyleType ty("Scrollbar", Sheet::cls()); return ty; }

	protected:
		Dimension m_dim;
		Sheet& m_sheet;
		Button& m_up;
		Scroller& m_scroller;
		Button& m_down;
	};

	class MK_UI_EXPORT ScrollArea : public Sheet
	{
	public:
		ScrollArea(Sheet& sheet);

		Scrollbar& scrollbar() { return m_scrollbar; }

		static StyleType& cls() { static StyleType ty("ScrollArea", Sheet::cls()); return ty; }

	protected:
		Scrollbar& m_scrollbar;
	};
}

#endif // MK_SCROLLBAR_H
