//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_RADIOBUTTON_H
#define TOY_RADIOBUTTON_H

/* toy */
#include <toyui/Types.h>
#include <toyui/Frame/UiRect.h>
#include <toyui/Widget/Widget.h>
#include <toyui/Button/Button.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT RadioSwitch : public Wedge
	{
	public:
		RadioSwitch(const Params& params, StringVector labels = {}, const Callback& callback = nullptr, size_t active = 0);

		MultiButton& addChoice(const StringVector& elements);

		void activated(MultiButton& choice);

	protected:
		Callback m_onSelected;
		MultiButton* m_active;
		size_t m_activeIndex;
	};
}

#endif
