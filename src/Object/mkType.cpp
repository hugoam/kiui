//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Object/mkObjectConfig.h>
#include <Object/mkType.h>

#include <Object/mkIndexer.h>
#include <Object/Reflect/mkImprint.h>

namespace mk
{
	Type::Type(int)
		: IdObject(0)
		, m_name("Type")
		, m_base(nullptr)
		, m_imprint(make_unique<Imprint>(*this))
		, m_indexer(make_unique<Indexer>(*this))
	{
		m_id = m_indexer->alloc();
		m_indexer->insert(*this, m_id);
	}

	Type::Type(TypeKind kind, const string& name)
		: IdObject(Type::cls())
		, m_name(name)
		, m_base(nullptr)
		, m_imprint(make_unique<Imprint>(*this))
		, m_indexer(kind == INDEXED ? make_unique<Indexer>(*this) : nullptr)
	{}

	Type::Type(Type& base, TypeKind kind, const string& name)
		: Type(kind, name)
	{
		m_base = &base;
		m_indexer.reset(base.m_indexer.get());
	}

	Type::~Type()
	{
		m_indexer = nullptr;
	}

	bool Type::upcast(Type& type)
	{
		if(&type == this)
			return true;
		else if(m_base)
			return m_base->upcast(type);
		else
			return false;
	}
}
