//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_RADIOBUTTON_H
#define TOY_RADIOBUTTON_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Frame/UiRect.h>
#include <toyui/Widget/Widget.h>
#include <toyui/Button/Button.h>

namespace toy
{
	class TOY_UI_EXPORT RadioSwitch : public Wedge
	{
	public:
		RadioSwitch(Wedge& parent, const Callback& onSelected, size_t active, StringVector labels = {});

		MultiButton& addChoice(const StringVector& elements);

		void activated(MultiButton& choice);

		static Type& cls() { static Type ty("RadioSwitch", Wedge::WrapControl()); return ty; }

		static Type& Choice() { static Type ty("RadioChoice", MultiButton::cls()); return ty; }

	protected:
		Callback m_onSelected;
		MultiButton* m_active;
		size_t m_activeIndex;
	};
}

#endif
