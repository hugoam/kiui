//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Object/mkObjectConfig.h>
#include <Object/mkObject.h>

#include <Object/mkType.h>
#include <Object/mkIndexer.h>

namespace mk
{
	TypeObject::TypeObject(Type* type)
		: mType(type)
	{}

	IdObject::IdObject(Id id, Type* type)
		: TypeObject(type)
		, mId(id ? id : mType->indexer()->alloc()) // @note this is due only to loading and creating using same constructor, one passing 0 as id // id
	{
		mType->indexer()->add(this);
	}

	IdObject::IdObject(Type* type)
		: TypeObject(type)
		, mId(mType->indexer()->alloc())
	{
		mType->indexer()->add(this);
	}

	IdObject::IdObject(Id id)
		: TypeObject(Type::cls())
		, mId(id)
	{
		Indexed<Type>::indexer()->add(this);
	}

	IdObject::~IdObject()
	{
		if(mType->indexer())
			mType->indexer()->remove(this);
	}
}
