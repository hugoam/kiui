//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Object/mkObjectConfig.h>
#include <Object/mkModular.h>

#include <Object/mkProto.h>

#include <algorithm>

namespace mk
{
	Modular::Modular(Proto& proto)
		: m_proto(proto)
		, m_parts(proto.numParts())
	{}

	Modular::~Modular()
	{
		for(size_t i = m_parts.size(); i > 0; --i)
			m_parts.pop_back();
	}

	void Modular::addPart(Type& type, Part* part)
	{
		m_parts[m_proto.partIndex(type)] = part;
	}

	bool Modular::hasPart(Type& type)
	{
		return m_proto.hasPart(type);
	}

	Part& Modular::part(Type& type)
	{
		return *m_parts[m_proto.partIndex(type)];
	}

	void Modular::pushPlug(unique_ptr<Part> part, Type& type)
	{
		m_plugs.emplace_back(std::move(part), type);
	}

	void Modular::removePlug(Type& type)
	{
		m_plugs.erase(std::remove_if(m_plugs.begin(), m_plugs.end(), [&type](const Plug& p) { return p.type == &type; }), m_plugs.end());
	}

	void Modular::removePlug(void* plug)
	{
		m_plugs.erase(std::remove_if(m_plugs.begin(), m_plugs.end(), [plug](const Plug& p) { return p.part.get() == plug; }), m_plugs.end());
	}

	Part& Modular::plug(Type& type)
	{
		for(Plug& plug : m_plugs)
			if(plug.type == &type)
				return *plug.part.get();
		//return nullptr;
	}

	bool Modular::hasPlug(Type& type)
	{
		for (Plug& plug : m_plugs)
			if (plug.type == &type)
				return true;
		return false;
	}
}
