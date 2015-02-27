//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_MODULAR_H_INCLUDED
#define MK_MODULAR_H_INCLUDED

/* mk */
#include <Object/mkObjectForward.h>
#include <Object/mkObject.h>
#include <Object/mkTyped.h>
#include <Object/Util/mkNonCopy.h>

/* Standard */
#include <vector>
#include <memory>

namespace mk
{
	class MK_OBJECT_EXPORT Modular : public NonCopy
	{
	public:
		Modular(Proto* proto);
		~Modular();

		Proto* proto() { return mProto; }

		void addPart(Type* type, Part* part);
		bool hasPart(Type* type);
		Part* part(Type* type);

		void pushPlug(std::unique_ptr<Part> part, Type* type);
		void removePlug(Type* type);
		void removePlug(void* plug);
		Part* plug(Type* type);

		std::vector<Part*>& parts() { return mParts; }

	public:
		template <class T>
		inline T* part() { return static_cast<T*>(part(T::cls())); }

		template <class T>
		inline T* plug() { return static_cast<T*>(plug(T::cls())); }

	protected:
		Proto* mProto;
		std::vector<Part*> mParts;
		
		class Plug;
		std::vector<Plug> mPlugs;
	};
}

#endif // mkMODULAR_H_INCLUDED
