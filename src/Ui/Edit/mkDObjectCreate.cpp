#include <Ui/mkUiConfig.h>
#include <Ui/Edit/mkDObjectCreate.h>

#include <Object/Reflect/mkImprint.h>
#include <Object/Reflect/mkEcho.h>

#include <Object/mkIndexer.h>

#include <Ui/Edit/mkDObjectEdit.h>

#include <Ui/Device/mkHook.h>

using namespace std::placeholders;

namespace mk
{
	// hook<Type> = Label(proto.imprint().name())
	// ProtoSelector sheet = Dropdown

	// DObjectCreate
	/*
		Form(make_unique<Page>("Create Object"))
		, m_title(m_sheet.emplace<Label>("Create Object"))

		
		, m_cancelButton(m_buttons.sheet().emplace<Button>("Cancel", std::bind(&FNewObject::cancel, this)))
	*/

	DRootObjectCreate::DRootObjectCreate(Device& parent)
		: Device(parent, cls())
		, m_rootTypes()
		, m_types(this->emplace<Stack>(Type::cls()).tstore(m_rootTypes).picker([this](Object& object) { this->selectType(object.as<Type>()); }))
		, m_type(nullptr)
		, m_objectCreate(nullptr)
	{
		for(Object* object : Type::cls().indexer().objects())
		{
			if(!object)
				continue;

			Type& type = object->as<Type>();
			if(type.imprint().isRoot() && type.imprint().constructible())
				m_rootTypes.add(type);
		}
	}

	void DRootObjectCreate::selectType(Type& type)
	{
		if(m_objectCreate)
			m_objectCreate->destroy();

		if(type.imprint().protos().size() > 0)
			m_objectCreate = &this->emplace<DProtoCreate>(type);
		else
			m_objectCreate = &this->emplace<DObjectCreate>(type);
	}

	DProtoCreate::DProtoCreate(Device& parent, Type& type)
		: Device(parent, cls())
		, m_type(type)
		, m_prototypes(this->emplace<Stack>().store(type.imprint().protos()).maker(&make_object_device<Type, Hook>).picker([this](Object& object) { this->selectProto(object.as<Type>()); }))
		, m_prototype(nullptr)
		, m_objectCreate(nullptr)
	{

	}

	void DProtoCreate::selectProto(Type& prototype)
	{
		if(m_objectCreate)
			m_objectCreate->destroy();

		m_objectCreate = &this->emplace<DObjectCreate>(prototype);
	}

	DCreateArg::DCreateArg(Device& parent, Member& member, Lref& lref)
		: Device(parent, cls())
		, m_member(member)
		, m_value(lref)
		, m_device(DValueEdit::check(m_value) ? (DValue&) this->append(DValueEdit::dispatch(*this, m_value)) : (DValue&) this->emplace<DEmpty>())
	{}

	DObjectCreate::DObjectCreate(Device& parent, Type& type)
		: Device(parent, cls())
		, m_type(type)
		, m_injector(type)
		, m_values(this->emplace<Stack>())
		, m_create(this->emplace<Response>("Create", std::bind(&DObjectCreate::createObject, this)))
		//, m_cancel(this->emplace<Response>("Cancel", std::bind(&DObjectCreate::cancel, this)))
	{
		for(size_t i = 0; i < m_injector.args().size(); ++i)
			m_values.emplace<DCreateArg>(*m_type.imprint().members()[i], m_injector.args()[i]);
	}

	void DObjectCreate::createObject()
	{
		Lref lref = m_type.imprint().emptyref();
		m_type.imprint().lrefInject(lref, m_injector.args());
	}

	void DObjectCreate::destroyObject()
	{
		//mObjectType.imprint().pool()->object(*m_object)->as<MultiPool>().pool(*m_prototype).free(m_object);
		//mObject = nullptr;
	}

	void DObjectCreate::cancel()
	{
		this->parent()->destroy();
	}



}
