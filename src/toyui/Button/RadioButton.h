//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_RADIOBUTTON_H
#define TOY_RADIOBUTTON_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Frame/Uibox.h>
#include <toyui/Widget/Widget.h>
#include <toyui/Button/Button.h>

namespace toy
{
	class TOY_UI_EXPORT RadioChoice : public WrapButton
	{
	public:
		RadioChoice(Wedge& parent, const Callback& trigger);

		static Type& cls() { static Type ty("RadioChoice", WrapButton::cls()); return ty; }
	};

	class TOY_UI_EXPORT RadioSwitch : public WrapControl
	{
	public:
		RadioSwitch(Wedge& parent, const Callback& onSelected, size_t active, StringVector labels = {});

		RadioChoice* active() { return m_active; }

		RadioChoice& addChoice();

		void activated(RadioChoice& choice);

		static Type& cls() { static Type ty("RadioSwitch", WrapControl::cls()); return ty; }

	protected:
		Callback m_onSelected;
		RadioChoice* m_active;
		size_t m_activeIndex;
	};
}

#endif
