//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_HOOK_H_INCLUDED
#define MK_HOOK_H_INCLUDED

/* mk headers */
#include <Object/mkTyped.h>
#include <Object/mkObjectForward.h>
#include <Ui/Form/mkForm.h>
#include <Ui/Widget/mkButton.h>

namespace mk
{
	class MK_UI_EXPORT _I_ Hook : public Form
	{
	public:
		Hook(Object* object, Type* type, Style* style = nullptr, const string& label = "", const string& image = "", const Button::Trigger& trigger = nullptr);
		Hook(TypeObject* object, Style* style = nullptr, const string& label = "", const string& image = "", const Button::Trigger& trigger = nullptr);

		Object* object() { return mObject; }
		Type* objectType() { return mObjectType; }

	protected:
		Object* mObject;
		Type* mObjectType;
		TypeObject* mStem;
	};
}

#endif // MK_HOOK_H_INCLUDED
