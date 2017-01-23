#include <toyui/Config.h>
#include <toyui/Edit/DStructure.h>

#include <toyobj/Reflect/Imprint.h>
#include <toyobj/Reflect/Member.h>

#include <toyui/Device/Stack.h>

using namespace std::placeholders;

namespace toy
{
	DStructureNode::DStructureNode(Device& parent, Object& object, Type& type)
		: Device(parent, cls())
		, m_object(make_unique<Echobject>(object, type))
	{
		for(auto& echomember : m_object->members().store())
		{
			Type& memberType = echomember->member().type();
			if(memberType.imprint().typeClass() == STORE)
			{

			}
		}
	}

	DStructure::DStructure(Device& parent)
		: Device(parent, cls())
		, m_root()
	{}

	DStructure::~DStructure()
	{}

	void DStructure::setRoot(Object& object, Type& type)
	{
		this->clear();
		m_root = &this->emplace<DStructureNode>(object, type);
	}
}
