//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_WRADIOBUTTON_H
#define TOY_WRADIOBUTTON_H

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
		RadioChoice(Piece& parent, const Trigger& trigger);

		static Type& cls() { static Type ty("RadioChoice", WrapButton::cls()); return ty; }
	};

	class TOY_UI_EXPORT RadioSwitch : public WideControl
	{
	public:
		RadioSwitch(Piece& parent, const Trigger& onSelected, size_t active, StringVector labels = StringVector());

		RadioChoice* active() { return m_active; }

		RadioChoice& addChoice();
		virtual Container& emplaceContainer();

		void activated(RadioChoice& choice);

		static Type& cls() { static Type ty("RadioSwitch", WideControl::cls()); return ty; }

	protected:
		Trigger m_onSelected;
		RadioChoice* m_active;
		size_t m_activeIndex;
	};
}

#endif
