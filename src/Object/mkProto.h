//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_PROTO_H_INCLUDED
#define MK_PROTO_H_INCLUDED

/* mk */
#include <Object/mkObjectForward.h>
#include <Object/mkStem.h>
#include <Object/mkIndexer.h>

/* Standard */
#include <vector>

namespace mk
{
	struct ProtoPart
	{
	public:
		ProtoPart() : type(0), index(0) {}

		Type* type;
		size_t index;
	};

	/*	A Proto represent a fixed layout of parts for an object, allowing for fast part query 
			It is a broader definition of a type, different from the C++ class, it defines a finite object
			with a finite set of capabilities, which is a sum of components : its parts

			The parts are members of a prototype, whereas additionnal components are called plugs, 
			and are not part of the object in itself : they can be here or not here, whereas the parts are always here
	*/

	class MK_OBJECT_EXPORT _I_ _S_ Proto : public IdObject
	{
	public:
		_C_ Proto(Type& type);

		void init(Type& stem, std::vector<Type*> parts) { m_stem = &stem; for(Type* type : parts) addPart(*type); }

		_A_ Type& prototype() { return m_type; }
		_A_ Type* stem() { return m_stem; }
		_A_ const std::vector<Type*>& parts() const { return m_parts; }
		_A_ Id id() const { return m_id; }

		inline void addPart(Type& type) { m_hashParts[type.id()].type = &type; m_hashParts[type.id()].index = m_numParts++; m_parts.push_back(&type); }
		inline bool hasPart(Type& type) { return (m_hashParts[type.id()].type != 0); }
		inline int partIndex(Type& type) { return m_hashParts[type.id()].index; }
		inline size_t numParts() { return m_numParts; }

		static Type& cls() { static Type ty(INDEXED); return ty; }

	protected:
		Type& m_type;
		Type* m_stem;
		size_t m_numParts;
		std::vector<ProtoPart> m_hashParts;
		std::vector<Type*> m_parts;
	};

	class MK_OBJECT_EXPORT ProtoType : public Type
	{
	public:
		ProtoType();

		Proto& proto() { return m_proto; }

		static Type& cls() { static Type ty(Type::cls()); return ty; }

	protected:
		Proto m_proto;
	};

	template <class T, class S, class... Parts>
	class TPrototype : public Part
	{
	public:
		TPrototype(Stem& stem) : Part(T::cls(), stem) {}

		static ProtoType& cls() { static ProtoType ty; return ty; }
	};
}

#endif // MK_PROTO_INCLUDED
