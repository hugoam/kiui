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
	WValue::WValue(Lref& value, Style* style, bool edit)
		: Sheet(style)
		, mValue(value)
		, mUpdate(0)
		, mEdit(edit)
	{}

	WValue::WValue(Lref&& value, Style* style, bool edit)
		: Sheet(style ? style : styleCls())
		, mCopy(value)
		, mValue(mCopy)
		, mUpdate(0)
		, mEdit(edit)
	{}

	void WValue::updateValue()
	{
		++mUpdate;
		this->markDirty();
		//this->updated();
	}

	string WValue::getString()
	{
		return mValue->getString();
	}

	void WValue::setString(const string& value)
	{
		mValue->setString(value);
	}
}
