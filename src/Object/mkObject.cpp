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
		: mType(&type)
	{}

	IdObject::IdObject(Id id, Type& type)
		: TypeObject(type)
		, mId(id)
	{}

	IdObject::~IdObject()
	{
		if(mType->indexer())
			mType->indexer()->remove(*this);
	}
}
