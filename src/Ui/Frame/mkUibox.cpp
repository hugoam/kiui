//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Frame/mkUibox.h>

namespace mk
{
	Uibox::Uibox()
		: d_position(0.f, 0.f)
		, d_size(0.f, 0.f)
		, d_space(FIT)
		, d_sizing(SHRINK, SHRINK)
		, d_layout(nullptr)
	{}

	Uibox::~Uibox()
	{}
}
