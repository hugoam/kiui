//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_HOOK_H_INCLUDED
#define MK_HOOK_H_INCLUDED

/* mk headers */
#include <Object/mkTyped.h>
#include <Object/mkObjectForward.h>
#include <Ui/Form/mkButton.h>

namespace mk
{
	class MK_UI_EXPORT Hook : public Button
	{
	public:
		Hook(Object* object, Type* type, const string& cls = "", const string& label = "", const string& image = "", Trigger trigger = nullptr);
		Hook(TypeObject* object, const string& cls = "", const string& label = "", const string& image = "", Trigger trigger = nullptr);

		Object* object() { return mObject; }
		Type* objectType() { return mObjectType; }

	protected:
		Object* mObject;
		Type* mObjectType;
		TypeObject* mStem;
	};
}

#endif // MK_HOOK_H_INCLUDED
