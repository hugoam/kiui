//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Edit/Value.h>

#include <toyobj/Object.h>
#include <toyobj/String/StringConvert.h>
#include <toyobj/Util/StatString.h>

#include <toyui/Widget/Layout.h>

#include <toyui/Edit/TypeIn.h>
#include <toyui/Button/Slider.h>

using namespace std::placeholders;

namespace toy
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

	WValue::WValue(Wedge& parent, Lref& value, Type& type, const OnUpdate& onUpdate, bool edit)
		: WrapControl(parent, type)
		, Value(value, onUpdate, edit)
	{}

	WValue::WValue(Wedge& parent, Lref&& value, Type& type, const OnUpdate& onUpdate, bool edit)
		: WrapControl(parent, type)
		, Value(std::move(value), onUpdate, edit)
	{}

	string WValue::getString()
	{
		size_t precision = 3;

		string result = m_value->getString();

		if(&m_value->type() == &typecls<float>() || &m_value->type() == &typecls<double>()
		|| &m_value->type() == &typecls<AutoStat<float>>() || &m_value->type() == &typecls<AutoStat<double>>())
		{
			size_t dot = result.find(".");
			if(precision > 0 && dot != string::npos)
				result.resize(std::min(result.size(), dot + precision + 1));
		}

		return result;
	}

	void WValue::notifyUpdate()
	{
		this->markDirty();
	}
}
