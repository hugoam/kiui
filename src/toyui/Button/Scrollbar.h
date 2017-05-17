//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_SCROLLBAR_H
#define TOY_SCROLLBAR_H

/* toy */
#include <toyobj/Id.h>
#include <toyobj/String/String.h>
#include <toyobj/Util/Updatable.h>
#include <toyui/Forward.h>
#include <toyui/Widget/Widget.h>
#include <toyui/Widget/Layout.h>
#include <toyui/Button/Button.h>
#include <toyui/Button/Slider.h>
#include <toyui/Frame/Stripe.h>

#include <memory>

namespace toy
{
	class _I_ TOY_UI_EXPORT Scroller : public Slider
	{
	public:
		Scroller(Wedge& parent, Dimension dim);

		void sliderStep(float offset, bool ended);

		static Type& cls() { static Type ty("Scroller", Slider::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT ScrollerKnob : public SliderKnob
	{
	public:
		ScrollerKnob(Wedge& parent, Dimension dim);

		static Type& cls() { static Type ty("ScrollerKnob", SliderKnob::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT ScrollForward : public Button
	{
	public:
		ScrollForward(Wedge& parent, const Callback& trigger);

		static Type& cls() { static Type ty("ScrollForward", Button::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT ScrollBackward : public Button
	{
	public:
		ScrollBackward(Wedge& parent, const Callback& trigger);

		static Type& cls() { static Type ty("ScrollBackward", Button::cls()); return ty; }
	};

	class TOY_UI_EXPORT ScrollUp
	{
	public:
		static Type& cls() { static Type ty("ScrollUp", Button::cls()); return ty; }
	};

	class TOY_UI_EXPORT ScrollDown
	{
	public:
		static Type& cls() { static Type ty("ScrollDown", Button::cls()); return ty; }
	};

	class TOY_UI_EXPORT ScrollLeft
	{
	public:
		static Type& cls() { static Type ty("ScrollLeft", Button::cls()); return ty; }
	};

	class TOY_UI_EXPORT ScrollRight
	{
	public:
		static Type& cls() { static Type ty("ScrollRight", Button::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Scrollbar : public Row
	{
	public:
		Scrollbar(Wedge& parent, Wedge& frameSheet, Wedge& contentSheet, Dimension dim);
		~Scrollbar();

		float contentSize();
		float visibleSize();

		float overflow();

		void scrollup();
		void scrolldown();

		void scroll(float amount);
		void scrollTo(float offset);

		virtual void nextFrame(size_t tick, size_t delta);

		static Type& cls() { static Type ty("Scrollbar", Row::cls()); return ty; }

	protected:
		Dimension m_dim;
		float d_cursor;
		Wedge& m_frameSheet;
		Wedge& m_contentSheet;

		ScrollForward m_up;
		Scroller m_scroller;
		ScrollBackward m_down;
	};
}

#endif // TOY_SCROLLBAR_H
