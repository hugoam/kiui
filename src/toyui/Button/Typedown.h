//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_TYPEDOWN_H
#define TOY_TYPEDOWN_H

/* toy */
#include <toyui/Widget/Sheet.h>
#include <toyui/Button/Dropdown.h>
#include <toyui/Button/Filter.h>

namespace toy
{
	class TOY_UI_EXPORT TypedownInput : public DropdownInput
	{
	public:
		TypedownInput(Wedge& parent, const Trigger& onSelected, StringVector choices = StringVector());

		FilterInput& input() { return m_input; }

		void click();

		void showFilter();
		void hideFilter();

		void onInput(string value);

		static Type& cls() { static Type ty("TypedownInput", DropdownInput::cls()); return ty; }

	protected:
		FilterInput m_input;
	};
}

#endif
