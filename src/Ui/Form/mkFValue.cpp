//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Form/mkFValue.h>

#include <Object/mkObject.h>
#include <Object/String/mkStringConvert.h>
#include <Object/Util/mkStatString.h>

#include <Ui/Form/mkWidgets.h>

#include <Ui/Widget/mkWTypeIn.h>
#include <Ui/Widget/mkWSlider.h>

using namespace std::placeholders;

namespace mk
{
	FValue::FValue(Lref& value, Style* style, bool edit, SchemeMapper mapper)
		: Form(style, "", mapper)
		, mLref(value)
		, mUpdate(0)
		, mEdit(edit)
	{
		if(edit)
			this->setAttr("edit", string("true"));
	}

	FValue::FValue(Lref&& value, Style* style, bool edit, SchemeMapper mapper)
		: Form(style, "", mapper)
		, mValue(value)
		, mLref(mValue)
		, mUpdate(0)
		, mEdit(edit)
	{
		if(edit)
			this->setAttr("edit", string("true"));
	}

	void FValue::updateValue()
	{
		++mUpdate;
		mWidget->markDirty();
		//this->updated();
	}

	string FValue::toString()
	{
		return mLref->getString();
	}

	void FValue::setString(const string& value)
	{
		mLref->setString(value);
	}
}
