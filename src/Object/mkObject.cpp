//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Object/mkObjectConfig.h>
#include <Object/mkObject.h>

#include <Object/mkType.h>
#include <Object/mkIndexer.h>

namespace mk
{
	TypeObject::TypeObject(Type& type)
		: m_type(type)
	{}

	IdObject::IdObject(int)
		: TypeObject(static_cast<Type&>(*this))
	{}

	IdObject::IdObject(Id id, Type& type)
		: TypeObject(type)
		, m_id(id == 0 ? type.indexer().alloc() : id)
	{
		type.indexer().insert(*this, m_id);
	}

	IdObject::IdObject(Type& type)
		: TypeObject(type)
		, m_id(type.indexer().alloc())
	{
		type.indexer().insert(*this, m_id);
	}

	IdObject::~IdObject()
	{
		m_type.indexer().remove(*this);
	}
}
