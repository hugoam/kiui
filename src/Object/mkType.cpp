//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Object/mkObjectConfig.h>
#include <Object/mkType.h>

#include <Object/mkIndexer.h>

namespace mk
{
	size_t Type::sTypeId = 0;

	Type::Type()
		: IdObject(++sTypeId, Type::cls())
		, mName()
		, mProto(nullptr)
		, mBase(nullptr)
		, mIndexer(nullptr)
		, mLibrary(nullptr)
	{
		Indexed<Type>::indexer().insert(*this, mId);

		if(mId == 0)
			mIndexer = &Indexed<Type>::indexer();
	}

	Type::Type(Type& base)
		: Type()
	{
		mBase = &base;
	}
	
	Type::~Type()
	{
		mIndexer = nullptr;
	}

	bool Type::upcast(Type* type)
	{
		if(mBase)
			return mBase->upcast(type);
		else
			return type == this;
	}
}
