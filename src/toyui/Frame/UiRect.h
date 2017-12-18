//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_BOX_H
#define TOY_BOX_H

/* toy */
#include <toyobj/Type.h>
#include <toyui/Types.h>
#include <toyui/Style/Style.h>

namespace toy
{
	class TOY_UI_EXPORT UiRect
	{
	public:
		UiRect() : d_position(0.f, 0.f), m_size(0.f, 0.f), m_span(1.f, 1.f), d_scale(1.f) {}

		DimFloat d_position;
		DimFloat m_size;
		DimFloat m_span;
		float d_scale;
	};
}

#endif // TOY_BOX_H
