//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkValue.h>

#include <Object/mkObject.h>
#include <Object/String/mkStringConvert.h>
#include <Object/Util/mkStatString.h>

#include <Ui/Form/mkWidgets.h>

#include <Ui/Widget/mkTypeIn.h>
#include <Ui/Widget/mkSlider.h>

using namespace std::placeholders;

namespace mk
{
	Value::Value(Lref& value, bool edit)
		: mValue(value)
		, mUpdate(0)
		, mEdit(edit)
	{}

	Value::Value(Lref&& value, bool edit)
		: mCopy(value)
		, mValue(mCopy)
		, mUpdate(0)
		, mEdit(edit)
	{}

	void Value::triggerUpdate()
	{
		++mUpdate;
		this->notifyUpdate();
	}

	void Value::triggerModify()
	{
		++mUpdate;
		this->notifyUpdate();
		this->notifyModify();
	}

	string Value::getString()
	{
		return mValue->getString();
	}

	void Value::setString(const string& value)
	{
		mValue->setString(value);
		this->triggerModify();
	}

	WValue::WValue(Lref& value, bool edit)
		: Sheet()
		, Value(value, edit)
	{
		mStyle = &cls();
	}

	WValue::WValue(Lref&& value, bool edit)
		: Sheet()
		, Value(std::move(value), edit)
	{
		mStyle = &cls();
	}

	void WValue::notifyUpdate()
	{
		this->markDirty();
	}
}
