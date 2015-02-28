//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WRADIOBUTTON_H
#define MK_WRADIOBUTTON_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Frame/mkUibox.h>
#include <Ui/Scheme/mkScheme.h>
#include <Ui/Widget/mkWidget.h>
#include <Ui/Widget/mkWButton.h>
#include <Ui/Form/mkForm.h>

namespace mk
{
	class MK_UI_EXPORT WRadioSwitch : public Sheet
	{
	public:
		WRadioSwitch(Trigger onSelected, size_t active);

		Sheet* vaddwrapper(Widget* widget);
		unique_ptr<Widget> vrelease(Widget* widget);

		WWrapButton* active() { return mActive; }

		void activated(WWrapButton* button);

	protected:
		Trigger mOnSelected;
		WWrapButton* mActive;
		size_t mActiveIndex;
	};

	class MK_UI_EXPORT RadioSwitch : public Form
	{
	public:
		RadioSwitch(Trigger onSelected, size_t active = 0);

		void onSelected(Widget* widget);

	protected:
		Trigger mOnSelected;
	};
}

#endif
