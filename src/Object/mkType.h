//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_TYPE_H
#define MK_TYPE_H

/* mk */
#include <Object/mkObjectForward.h>
#include <Object/mkObject.h>

/* Standard */
#include <stdint.h>
#include <memory>

namespace mk
{
	enum TypeKind
	{
		TYPE,
		INDEXED,
		PROTOTYPE
	};

	class MK_OBJECT_EXPORT _I_ Type : public IdObject
	{
	public:
		Type(TypeKind kind = TYPE, const string& name = "");
		Type(Type& base, TypeKind kind = TYPE, const string& name = "");
		~Type();

		Type(Type&&) = delete;

		_A_ Id id() const { return IdObject::id(); }
		_A_ const string& name() const { return m_name; }
		_A_ Type* base() const { return m_base; }

		Imprint& imprint() { return *m_imprint; }

		Indexer& indexer() { return *m_indexer; }

		Type* base() { return m_base; }

		void setupName(string name) { m_name = name; }

		bool upcast(Type& type);

		static Type& cls() { static Type ty(0); return ty; }

	public:
		template <class T>
		bool upcast() { return this->upcast(typecls<T>()); }

	private:
		Type(int);

	protected:
		string m_name;
		Type* m_base;

		unique_ptr<Imprint> m_imprint;

		unique_ptr<Indexer> m_indexer;
	};

	/*class MK_OBJECT_EXPORT IdType : public Type
	{
	public:
		IdType();

		Indexer& indexer() { return *m_indexer; }

	protected:
		unique_ptr<Indexer> m_indexer;
	};

	*/
}

#endif
