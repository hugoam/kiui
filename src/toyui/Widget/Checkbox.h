//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_WCHECKBOX_H
#define TOY_WCHECKBOX_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Widget/Button.h>

namespace toy
{
	class _I_ TOY_UI_EXPORT Checkbox : public Toggle
	{
	public:
		Checkbox(WValue* input, bool on);

		void toggleOn();
		void toggleOff();

		static StyleType& cls() { static StyleType ty("Checkbox", Toggle::cls()); return ty; }

	protected:
		WValue* m_input;
	};
}

#endif
