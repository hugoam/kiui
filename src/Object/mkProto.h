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
#include <map>
#include <unordered_map>
#include <unordered_set>

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

	class MK_OBJECT_EXPORT _I_ _S_ Proto : public IdObject, public Indexed<Proto>
	{
	public:
		_C_ Proto(Type* type);

		void init(Type* stem, std::vector<Type*> parts) { mStem = stem; for(Type* type : parts) addPart(type); }

		_A_ Type* prototype() { return mType; }
		_A_ Type* stem() { return mStem; }
		_A_ const std::vector<Type*>& parts() const { return mParts; }
		_A_ Id id() const { return mId; }

		inline void addPart(Type* type) { mHashParts[type->id()].type = type; mHashParts[type->id()].index = mNumParts++; mParts.push_back(type); }
		inline bool hasPart(Type* type) { return (mHashParts[type->id()].type != 0); }
		inline int partIndex(Type* type) { return mHashParts[type->id()].index; }
		inline size_t numParts() { return mNumParts; }

	protected:
		Type* mType;
		Type* mStem;
		size_t mNumParts;
		std::vector<ProtoPart> mHashParts;
		std::vector<Type*> mParts;
	};

	class MK_OBJECT_EXPORT ProtoChunk
	{
	public:
		virtual ~ProtoChunk() {}
	};

	template <class T, class... Parts>
	class Prototyped
	{
	public:
		static Proto* proto() { return &sProto; }

	private:
		static Proto sProto;
	};

	template <class T, class... Parts>
	Proto Prototyped<T, Parts...>::sProto(T::cls());

	template <class T, class S, class... Parts>
	class TPrototype : public Part, public Indexed<T, S>, public Prototyped<T, Parts...>
	{
	public:
		TPrototype(Stem* stem) : Part(T::cls(), stem) {}
	};
}

#endif // MK_PROTO_INCLUDED
