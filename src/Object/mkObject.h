//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_OBJECT_H_INCLUDED
#define MK_OBJECT_H_INCLUDED

/* mk headers */
#include <Object/Util/mkMake.h>
#include <Object/mkId.h>
#include <Object/mkObjectForward.h>

#include <vector>

namespace mk
{
	class MK_OBJECT_EXPORT Object
	{
	public:
		Object() {}
		virtual ~Object() {}

		template <class T> 
		inline T* as() { return static_cast<T*>(this); }

		template <class T>
		inline const T* as() const { return static_cast<const T*>(this); }

		Object(const Object&) = delete;
		Object& operator=(const Object&) = delete;
	};

	class MK_OBJECT_EXPORT Struct : public Object
	{
	public:
		Struct() {}
		Struct(const Struct&) {}
		Struct& operator=(const Struct&) { return *this; }
	};

	class MK_OBJECT_EXPORT TypeObject : public Object
	{
	public:
		TypeObject(Type* type);

		Type* type() const { return mType; }

	protected:
		Type* mType;
	};

	class MK_OBJECT_EXPORT IdObject : public TypeObject
	{
	public:
		IdObject(Id id, Type* type);
		~IdObject();

		template <class T>
		Id index(Id id) { Id = id ? id : T::indexer()->alloc(); T::indexer()->insert(this, id); return id; }

		template <class T>
		Id index() { Id id = T::indexer()->alloc(); T::indexer()->insert(this, id); return id; }

		Id id() const { return mId; }

	protected:
		Id mId;
	};

	class MK_OBJECT_EXPORT IdStruct : public IdObject
	{
	public:
		IdStruct(Id id, Type* type) : IdObject(id, type) {}
		IdStruct& operator=(const IdStruct&) { return *this; }
	};

	typedef std::vector<Object*> ObjectVector;
}

#endif // mkOBJECT_H_INCLUDED
