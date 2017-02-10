//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Frame/Uibox.h>

namespace toy
{
	Uibox::Uibox()
		: d_position(0.f, 0.f)
		, d_size(0.f, 0.f)
		, d_space(AUTO)
		, d_sizing(SHRINK, SHRINK)
		, d_scale(1.f)
		, d_depth(DIM_X)
		, d_length(DIM_Y)
		, d_layout(nullptr)
	{}
}
