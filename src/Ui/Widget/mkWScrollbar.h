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
	class MK_UI_EXPORT WScroller : public WSlider
	{
	public:
		WScroller();

		void sliderStep(float offset, bool ended);
	};

	class MK_UI_EXPORT WScrollbar : public Sheet
	{
	public:
		WScrollbar(Stripe* sheet);
		~WScrollbar();

		void build();

		string clas() { return "scrollbar"; }

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
}

#endif // MK_SCROLLBAR_H_INCLUDED
