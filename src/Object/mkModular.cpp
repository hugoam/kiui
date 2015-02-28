//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Object/mkObjectConfig.h>
#include <Object/mkModular.h>

#include <Object/mkProto.h>

#include <algorithm>

namespace mk
{
	class Modular::Plug : public NonCopy
	{
	public:
		Plug(unique_ptr<Part> p, Type* t) : part(std::move(p)), type(t) {}
		Plug(Plug&& other) : part(std::move(other.part)), type(other.type) {}

		Plug& operator=(Plug&& other) { part = std::move(other.part); type = other.type; return *this; }

		unique_ptr<Part> part;
		Type* type;
	};

	Modular::Modular(Proto* proto)
		: mProto(proto)
		, mParts(proto ? proto->numParts() : 0)
	{}

	Modular::~Modular()
	{
		for(size_t i = mParts.size(); i > 0; --i)
			mParts.pop_back();
	}

	void Modular::addPart(Type* type, Part* part)
	{
		mParts[mProto->partIndex(type)] = part;
	}

	bool Modular::hasPart(Type* type)
	{
		return mProto->hasPart(type);
	}

	Part* Modular::part(Type* type)
	{
		return mParts[mProto->partIndex(type)];
	}

	void Modular::pushPlug(unique_ptr<Part> part, Type* type)
	{
		mPlugs.emplace_back(std::move(part), type);
	}

	void Modular::removePlug(Type* type)
	{
		mPlugs.erase(std::remove_if(mPlugs.begin(), mPlugs.end(), [type](const Plug& p) { return p.type == type; }), mPlugs.end());
	}

	void Modular::removePlug(void* plug)
	{
		mPlugs.erase(std::remove_if(mPlugs.begin(), mPlugs.end(), [plug](const Plug& p) { return p.part.get() == plug; }), mPlugs.end());
	}

	Part* Modular::plug(Type* type)
	{
		for(Plug& plug : mPlugs)
			if(plug.type == type)
				return plug.part.get();

		return nullptr;
	}
}
