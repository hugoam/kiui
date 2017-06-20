//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Render/Stencil.h>

#include <toyui/Widget/Widget.h>
#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Layer.h>

#include <toyui/UiWindow.h>
#include <toyui/Widget/RootSheet.h>

namespace toy
{
	Stencil::Stencil(DrawFrame& frame)
		: m_frame(frame)
	{}

	BoxFloat Stencil::selectCorners()
	{
		Frame& frame = m_frame.frame();
		Stripe& parent = *m_frame.frame().parent();

		BoxFloat& corners = parent.style().skin().cornerRadius();
		if(parent.first(frame))
			return parent.length() == DIM_X ? BoxFloat(corners.v0(), 0.f, 0.f, corners.v3()) : BoxFloat(corners.v0(), corners.v1(), 0.f, 0.f);
		else if(parent.last(frame))
			return parent.length() == DIM_X ? BoxFloat(0.f, corners.v1(), corners.v2(), 0.f) : BoxFloat(0.f, 0.f, corners.v2(), corners.v3());
		else 
			return BoxFloat();
	}
}
