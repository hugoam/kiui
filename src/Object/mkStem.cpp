//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Object/mkObjectConfig.h>
#include <Object/mkStem.h>

#include <Object/mkProto.h>

namespace mk
{
	Stem::Stem(Id id, Type* type, Proto* proto)
		: IdObject(id, type)
		, Modular(proto)
	{}

	Part::Part(Type* type, Stem* stem)
		: Object()
		, mStem(stem)
	{
		stem->addPart(type, this);
	}

	Part::Part(Stem* stem)
		: Object()
		, mStem(stem)
	{}
}
