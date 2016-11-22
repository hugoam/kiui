//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkValue.h>

#include <Object/mkObject.h>
#include <Object/String/mkStringConvert.h>
#include <Object/Util/mkStatString.h>

#include <Ui/Widget/mkWidgets.h>

#include <Ui/Widget/mkTypeIn.h>
#include <Ui/Widget/mkSlider.h>

using namespace std::placeholders;

namespace mk
{
	Value::Value(Lref& value, const OnUpdate& onUpdate, bool edit)
		: m_value(value)
		, m_update(0)
		, m_edit(edit)
		, m_onUpdate(onUpdate)
	{}

	Value::Value(Lref&& value, const OnUpdate& onUpdate, bool edit)
		: m_copy(value)
		, m_value(m_copy)
		, m_update(0)
		, m_edit(edit)
		, m_onUpdate(onUpdate)
	{}

	void Value::triggerUpdate()
	{
		++m_update;
		this->notifyUpdate();
	}

	void Value::triggerModify()
	{
		++m_update;
		this->notifyUpdate();
		this->notifyModify();

		if(m_onUpdate)
			m_onUpdate(m_value);
	}

	string Value::getString()
	{
		return m_value->getString();
	}

	void Value::setString(const string& value)
	{
		m_value->setString(value);
		this->triggerModify();
	}

	WValue::WValue(Lref& value, StyleType& type, const OnUpdate& onUpdate, bool edit)
		: Sheet(type)
		, Value(value, onUpdate, edit)
	{}

	WValue::WValue(Lref&& value, StyleType& type, const OnUpdate& onUpdate, bool edit)
		: Sheet(type)
		, Value(std::move(value), onUpdate, edit)
	{}

	void WValue::notifyUpdate()
	{
		this->markDirty();
	}
}
