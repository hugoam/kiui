#include <toyui/Config.h>
#include <toyui/Edit/DObjectEdit.h>

#include <toyobj/Reflect/Imprint.h>
#include <toyobj/Reflect/Member.h>
#include <toyobj/Reflect/Method.h>
#include <toyobj/String/String.h>
#include <toyobj/String/StringConvert.h>
#include <toyobj/Reflect/Injector.h>

#include <toyobj/Stem.h>
#include <toyobj/Proto.h>

#include <toyui/Device/RootDevice.h>

using namespace std::placeholders;

namespace toy
{
	DMemberEdit::DMemberEdit(Device& parent, Echomember& echomember)
		: Device(parent, cls())
		, m_member(echomember)
		, m_lref(echomember.member().imprint().emptyref())
		, m_value(m_lref)
		, m_device(DValueEdit::check(m_value) ? (DValue&) this->append(DValueEdit::dispatch(*this, m_value)) : (DValue&) this->emplace<DEmpty>())
	{
		this->collect();
	}

	void DMemberEdit::assign()
	{
		if(m_member.member().muttable())
			m_member.set(m_lref);
	}

	void DMemberEdit::collect()
	{
		m_member.get(m_lref);
		m_device.handleValueChanged();
	}

	DObjectEdit::DObjectEdit(Device& parent, Echobject& echobject)
		: DValue(parent, echobject.object(), echobject.type(), cls())
		, m_instance(echobject.object(), echobject.type())
		, m_object(echobject)
		, m_members(this->emplace<Stack>())
	{
		m_members.maker(&make_device<Echomember, DMemberEdit>);
		m_members.tstore<Echomember>(m_object.members());
	}

	DObjectEdit::DObjectEdit(Device& parent, Object& object, Type& type)
		: DValue(parent, object, type, cls())
		, m_instance(object, type)
		, m_object(m_instance)
		, m_members(this->emplace<Stack>())
	{
		m_members.maker(&make_device<Echomember, DMemberEdit>);
		m_members.tstore<Echomember>(m_object.members());
	}

	/*void DObjectEdit::updateDevices()
	{
	this->updateObject();
	}*/

	void DObjectEdit::updateObject()
	{
		for(auto& member : m_contents)
			member->as<DMemberEdit>().assign();

		//if(m_objectType.imprint().hasMember("updated"))
		//	m_objectType.imprint().member("updated").set(*m_object, lref(this->rootForm().lastTick()));
	}

	void DObjectEdit::updateDevice()
	{
		for(auto& member : m_contents)
			member->as<DMemberEdit>().collect();
	}

	/*void DObjectEdit::updateMembers(LrefVector& args)
	{
	size_t i = 0;
	for(auto& member : m_contents)
	if(i != 0) // we skip the first one which is the id, auto-allocated
	copyref(args[i++], member->as<FMember>().valref());
	}*/

	void DObjectEdit::handleValueChanged()
	{}

	DPartEdit::DPartEdit(Device& parent, Echobject& object)
		: Device(parent, cls())
		, m_objectEdit(this->emplace<DObjectEdit>(object))
	{}

	DPartEdit::DPartEdit(Device& parent, Object& object, Type& type)
		: Device(parent, cls())
		, m_objectEdit(this->emplace<DObjectEdit>(object, type))
	{}

	DModularEdit::DModularEdit(Device& parent, Echobject& object)
		: Device(parent, cls())
		, m_objectEdit(this->emplace<DObjectEdit>(object))
		, m_parts(this->emplace<Stack>().maker(&make_device<Echobject, DPartEdit>).tstore<Echobject>(object.parts()))
	{}

	DEdit::DEdit(Device& parent)
		: Device(parent, cls())
		, m_objectEdit(nullptr)
	{}

	void DEdit::edit(Object& object, Type& type)
	{
		this->clear();
		m_objectEdit = &this->emplace<DObjectEdit>(object, type);
	}

	void DEdit::edit(Echobject& echobject)
	{
		this->clear();
		m_objectEdit = &this->emplace<DObjectEdit>(echobject);
	}
}