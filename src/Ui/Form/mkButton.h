//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_BUTTON_H_INCLUDED
#define MK_BUTTON_H_INCLUDED

/* mk headers */
#include <Object/mkTyped.h>
#include <Ui/mkUiForward.h>
#include <Ui/Form/mkForm.h>

namespace mk
{
	enum ButtonState
	{
		BUTTON_DISABLED = 0,
		BUTTON_ENABLED = 1,
		BUTTON_ACTIVE = 2,
	};

	class MK_UI_EXPORT Button : public Form
	{
	public:
		typedef std::function<void(Button*)> Trigger;

	public:
		Button(const string& cls, const string& label, const string& image = "", Trigger trigger = nullptr);

		virtual void trigger() { mTrigger(this); }
		virtual void triggerAlt() { this->trigger(); }
		virtual void triggerShift() { this->trigger(); }
		virtual void triggerCtrl() { this->trigger(); }

	protected:
		Trigger mTrigger;
	};
}

#endif // MK_BUTTON_H_INCLUDED
