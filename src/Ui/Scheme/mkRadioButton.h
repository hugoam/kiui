//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WRADIOBUTTON_H
#define MK_WRADIOBUTTON_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Frame/mkUibox.h>
#include <Ui/Widget/mkWidget.h>
#include <Ui/Widget/mkButton.h>
#include <Ui/Form/mkForm.h>

namespace mk
{
	class MK_UI_EXPORT RadioChoice : public WrapButton, public Typed<RadioChoice, Sheet>, public Styled<RadioChoice>
	{
	public:
		RadioChoice(Widget* content, const Trigger& trigger);

		using Typed<RadioChoice, Sheet>::cls;
	};

	class MK_UI_EXPORT RadioSwitch : public Sheet, public Typed<RadioSwitch, Sheet>, public Styled<RadioSwitch>
	{
	public:
		RadioSwitch(const Trigger& onSelected, size_t active, StringVector labels = StringVector());

		Sheet* vappend(unique_ptr<Widget> widget);
		unique_ptr<Widget> vrelease(Widget* widget);

		WrapButton* active() { return mActive; }

		void activated(WrapButton* button);

		using Typed<RadioSwitch, Sheet>::cls;

	protected:
		Trigger mOnSelected;
		WrapButton* mActive;
		size_t mActiveIndex;
	};
}

#endif
