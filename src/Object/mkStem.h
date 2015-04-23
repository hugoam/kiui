//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_STEM_H_INCLUDED
#define MK_STEM_H_INCLUDED

/* mk headers */
#include <Object/mkTyped.h>
#include <Object/mkModular.h>

namespace mk
{
	class MK_OBJECT_EXPORT Stem : public IdObject, public Modular
	{
	public:
		Stem(Id id, Type& type, Proto* proto);
	};

	class MK_OBJECT_EXPORT Part : public Object
	{
	public:
		Part(Type& type, Stem& stem);
		Part(Stem& stem);

		Stem& stem() { return mStem; }

	protected:
		Stem& mStem;
	};
}

#endif // MK_STEM_H_INCLUDED
