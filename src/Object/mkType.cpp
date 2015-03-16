//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Object/mkObjectConfig.h>
#include <Object/mkType.h>

#include <Object/mkIndexer.h>

namespace mk
{
	Type Type::sType;
	size_t Type::sTypeId = 0;

	Type::Type(Type* base)
		: IdObject(++sTypeId)
		, mName()
		, mBase(base)
		, mProto(nullptr)
		, mIndexer(nullptr)
		, mLibrary(nullptr)
	{}

	Type::Type()
		: IdObject(++sTypeId)
		, mName()
		, mBase(nullptr)
		, mProto(nullptr)
		, mIndexer(Indexed<Type>::indexer())
		, mLibrary(nullptr)
	{}
	
	Type::~Type()
	{}

	bool Type::upcast(Type* type)
	{
		if(mBase)
			return mBase->upcast(type);
		else
			return type == this;
	}
}
