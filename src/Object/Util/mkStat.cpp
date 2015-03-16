//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Object/mkObjectConfig.h>
#include <Object/Util/mkStat.h>

namespace mk
{
	StatDef<float> Ratio::mDef(0.f, 1.f, 0.01f);
	StatDef<float> Gauge::mDef(0.f, FLT_MAX, 1.f);
}
