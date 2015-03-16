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
#include <Ui/Widget/mkWButton.h>
#include <Ui/Widget/mkWSlider.h>
#include <Ui/Frame/mkStripe.h>

#include <memory>

namespace mk
{
	class MK_UI_EXPORT WScroller : public WSlider, public Styled<WScroller>
	{
	public:
		WScroller(Dimension dim);

		void sliderStep(float offset, bool ended);

		using Styled<WScroller>::styleCls;
	};

	class MK_UI_EXPORT WScrollerX : public WScroller
	{
	public:
		WScrollerX();

		void build();
	};

	class MK_UI_EXPORT WScrollerY : public WScroller
	{
	public:
		WScrollerY();

		void build();
	};

	class MK_UI_EXPORT WScrollerKnobX : public WSliderKnob, public Styled<WScrollerKnobX>
	{
	public:
		WScrollerKnobX();

		using Styled<WScrollerKnobX>::styleCls;
	};

	class MK_UI_EXPORT WScrollerKnobY : public WSliderKnob, public Styled<WScrollerKnobY>
	{
	public:
		WScrollerKnobY();

		using Styled<WScrollerKnobY>::styleCls;
	};

	class MK_UI_EXPORT WScrollUp : public WButton, public Styled<WScrollUp>
	{
	public:
		WScrollUp(const Trigger& trigger);

		using Styled<WScrollUp>::styleCls;
	};

	class MK_UI_EXPORT WScrollDown : public WButton, public Styled<WScrollDown>
	{
	public:
		WScrollDown(const Trigger& trigger);

		using Styled<WScrollDown>::styleCls;
	};

	class MK_UI_EXPORT WScrollbar : public Sheet, public Styled<WScrollbar>
	{
	public:
		WScrollbar(Stripe* sheet);
		~WScrollbar();

		void build();

		void scrollup();
		void scrolldown();
		void scroll(float offset);
		void nextFrame(size_t tick, size_t delta);

	protected:
		Stripe* mSheet;
		WButton* mUp;
		WScroller* mScroller;
		WButton* mDown;
	};

	class MK_UI_EXPORT WScrollSheet : public Sheet, public Styled<WScrollSheet>
	{
	public:
		WScrollSheet();
	};
}

#endif // MK_SCROLLBAR_H_INCLUDED
