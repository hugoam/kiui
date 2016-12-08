//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_MODULAR_H
#define MK_MODULAR_H

/* mk */
#include <Object/mkObjectForward.h>
#include <Object/Util/mkNonCopy.h>
#include <Object/Util/mkUnique.h>

/* Standard */
#include <vector>
#include <memory>

namespace mk
{
	class MK_OBJECT_EXPORT Modular : public NonCopy
	{
	protected:
		class Plug;

	public:
		Modular(Proto& proto);
		~Modular();

		Proto& proto() { return m_proto; }

		void addPart(Type& type, Part* part);
		bool hasPart(Type& type);
		Part& part(Type& type);

		void pushPlug(unique_ptr<Part> part, Type& type);
		void removePlug(Type& type);
		void removePlug(void* plug);
		bool hasPlug(Type& type);
		Part& plug(Type& type);

		std::vector<Part*>& parts() { return m_parts; }

		std::vector<Plug>& plugs() { return m_plugs; }

	public:
		template <class T>
		inline bool is() { return hasPart(T::cls()); }

		template <class T>
		inline T& part() { return static_cast<T&>(part(T::cls())); }

		template <class T>
		inline T& plug() { return static_cast<T&>(plug(T::cls())); }

	protected:
		Proto& m_proto;
		std::vector<Part*> m_parts;
		
		class Plug : public NonCopy
		{
		public:
			Plug(unique_ptr<Part> p, Type& t) : part(std::move(p)), type(&t) {}
			Plug(Plug&& other) : part(std::move(other.part)), type(other.type) {}

			Plug& operator=(Plug&& other) { part = std::move(other.part); type = other.type; return *this; }

			unique_ptr<Part> part;
			Type* type;
		};

		std::vector<Plug> m_plugs;
	};
}

#endif
