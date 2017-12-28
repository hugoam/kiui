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
	class _refl_ TOY_UI_EXPORT TypedownInput : public DropdownInput
	{
	public:
		TypedownInput(const Params& params, StringVector choices = {}, const Callback& callback = nullptr);

		virtual void dropdown(bool modal = true);
		virtual void dropup();

	protected:
		FilterInput m_input;
	};
}

#endif
