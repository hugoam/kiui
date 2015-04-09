//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Form/mkHook.h>

#include <Ui/Widget/mkButton.h>

namespace mk
{
	Hook::Hook(Object* object, Type* type, Style* style, const string& label, const string& image, const Button::Trigger& trigger)
		: Form(make_unique<Sheet>(style))
		, mObject(object)
		, mObjectType(type)
	{
		if(!label.empty())
			mSheet->emplace<Button>(label, nullptr, trigger);
		else if(!image.empty())
			mSheet->emplace<ImgButton>(image, trigger);
	}

	Hook::Hook(TypeObject* object, Style* style, const string& label, const string& image, const Button::Trigger& trigger)
		: Hook(object, object->type(), style, label, image, trigger)
	{}
}
