#include <toyui/Config.h>
#include <toyui/Edit/DValueEdit.h>

#include <toyobj/Reflect/Imprint.h>
#include <toyobj/Reflect/Member.h>

#include <toyui/Device/Hook.h>

#include <toyui/Edit/DObjectEdit.h>

#include <iostream>

using namespace std::placeholders;

namespace toy
{
	DValue::DValue(Device& parent, DeviceType& type)
		: Device(parent, type)
		, m_instance()
		, m_value(m_instance)
	{}

	DValue::DValue(Device& parent, Lref& lref, OnChange onChange)
		: Device(parent, cls())
		, m_instance()
		, m_value(lref)
		, m_onChange(onChange)
	{}

	DValue::DValue(Device& parent, Lref&& lref, OnChange onChange)
		: Device(parent, cls())
		, m_instance(lref)
		, m_value(m_instance)
		, m_onChange(onChange)
	{}

	DValue::DValue(Device& parent, Lref& lref, DeviceType& type)
		: Device(parent, type)
		, m_instance()
		, m_value(lref)
	{}

	DValue::DValue(Device& parent, Object& object, Type& type, DeviceType& deviceType)
		: Device(parent, deviceType)
		, m_instance(object, type)
		, m_value(m_instance)
	{}

	void DValue::handleValueChanged()
	{
		std::cerr << "DValue::valueChanged " << m_value->getString() << std::endl;
		if(m_onChange)
			m_onChange(m_value);
	}
	
	DEmpty::DEmpty(Device& parent)
		: DValue(parent, cls())
	{}

	DNone::DNone(Device& parent)
		: DValue(parent, cls())
	{}

	DElement::DElement(Device& parent, Stack& stack, Lref lref)
		: Device(parent, cls())
	{
		Hook& hook = this->emplace<Hook>(*lref->object(), lref->type());
		hook.stack(stack);
		this->emplace<Response>("remove", std::bind(&DElement::remove, this));
	}

	void DElement::remove()
	{
		this->parent()->remove(*this);
	}

	void DElement::handleValueChanged()
	{}

	DSequence::DSequence(Device& parent, Lref& lref, bool edit)
		: DValue(parent, lref, cls())
	{
		//this->emplace<Stack>().store(lref->imprint().sequence(*lref->object()));
		this->emplace<Response>("add", std::bind(&DSequence::reqAdd, this));
	}

	void DSequence::reqAdd()
	{
		Indexer& indexer = m_value->imprint().sequence(*m_value->object()).elementType().type().indexer();
		this->emplace<Stack>().store(indexer).picker(std::bind(&DSequence::endAdd, this, _1));
	}

	void DSequence::endAdd(Object& object)
	{
		//mLref->as<Stock>()->vaddobj(object);
		this->popback();
	}

	void DSequence::handleValueChanged()
	{}

	DEnum::DEnum(Device& parent, Lref& value, bool edit)
		: DValue(parent, value, cls())
	{
		//this->emplace<Stack>().store(m_value->imprint().enumIds());
	}

	void DEnum::set(const string& value)
	{
		m_value->imprint().enumSet(m_value, value);
	}

	void DEnum::handleValueChanged()
	{}

	DLink::DLink(Device& parent, Lref& lref, bool edit)
		: DValue(parent, lref, cls())
	{
		if(edit)
			this->emplace<Response>("Pick", std::bind(&DLink::reqPick, this));
	}

	void DLink::reqPick()
	{
		Indexer& indexer = m_value->type().indexer();
		this->emplace<Stack>().store(indexer).picker(std::bind(&DLink::endPick, this, _1));
	}

	void DLink::endPick(Object& object)
	{
		m_value->setobject(object);
		this->popback();
	}

	void DLink::handleValueChanged()
	{
		if(m_value->object())
		{
			m_linkHook = &this->emplace<Hook>(*m_value->object(), m_value->type());
		}
		else if(m_linkHook)
		{
			this->remove(*m_linkHook);
			m_linkHook = nullptr;
		}
	}

	bool isNone(Type& type) { return &type == &None::cls(); }
	bool isBaseType(Type& type) { return type.imprint().typeClass() == BASETYPE; }
	bool isEnum(Type& type) { return type.imprint().typeClass() == ENUM; }
	bool isObject(Type& type) { return type.imprint().isStruct(); }
	bool isLink(Type& type) { return type.imprint().isObject() && !type.imprint().isStruct(); }
	bool isSequence(Type& type) { return type.imprint().typeClass() == STORE || type.imprint().typeClass() == SEQUENCE; }

	unique_ptr<DValue> make_none(Device& parent, Lref& lref) { UNUSED(parent); return make_unique<DNone>(parent); }

	template <class T_Device>
	unique_ptr<DValue> make_dvalue(Device& parent, Lref& lref) { UNUSED(parent); return make_unique<T_Device>(parent, lref); }

	template <class T_Object, class T_Device>
	unique_ptr<DValue> make_typed_dvalue(Device& parent, Lref& lref) { UNUSED(parent); return make_unique<T_Device>(parent, lref->as<T_Object>(), lref->type()); }

	void declareDValueEdit()
	{
		DValueEdit::maskBranch<isNone, make_none>();
		DValueEdit::maskBranch<isBaseType, make_dvalue<DValue>>();
		DValueEdit::maskBranch<isSequence, make_dvalue<DSequence>>();
		DValueEdit::maskBranch<isEnum, make_dvalue<DEnum>>();
		DValueEdit::maskBranch<isObject, make_typed_dvalue<Echobject, DObjectEdit>>();
		DValueEdit::maskBranch<isLink, make_dvalue<DLink>>();
	}

	void declareDValueDisplay()
	{
		DValueEdit::maskBranch<isNone, make_none>();
		DValueEdit::maskBranch<isBaseType, make_dvalue<DValue>>();
		DValueEdit::maskBranch<isSequence, make_dvalue<DSequence>>();
		DValueEdit::maskBranch<isEnum, make_dvalue<DEnum>>();
		DValueEdit::maskBranch<isObject, make_typed_dvalue<Echobject, DObjectEdit>>();
		DValueEdit::maskBranch<isLink, make_dvalue<DLink>>();
	}

	//template class Dispatch<ValueForm, Quaternion&, dispatchObjectEdit<Quaternion&>>;
	//template class Dispatch<ValueForm, Vector3&, dispatchObjectEdit<Vector3&>>;	
}