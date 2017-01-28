//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_WRADIOBUTTON_H
#define TOY_WRADIOBUTTON_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Frame/Uibox.h>
#include <toyui/Widget/Widget.h>
#include <toyui/Widget/Button.h>

namespace toy
{
	class TOY_UI_EXPORT RadioChoice : public WrapButton
	{
	public:
		RadioChoice(Widget* content, const Trigger& trigger);

		static StyleType& cls() { static StyleType ty("RadioChoice", WrapButton::cls()); return ty; }
	};

	class TOY_UI_EXPORT RadioSwitch : public Sheet
	{
	public:
		RadioSwitch(const Trigger& onSelected, size_t active, StringVector labels = StringVector());

		Widget& vappend(unique_ptr<Widget> widget);
		unique_ptr<Widget> vrelease(Widget& widget);

		WrapButton* active() { return m_active; }

		void activated(WrapButton& button);

		static StyleType& cls() { static StyleType ty("RadioSwitch", Sheet::cls()); return ty; }

	protected:
		Trigger m_onSelected;
		WrapButton* m_active;
		size_t m_activeIndex;
	};
}

#endif
