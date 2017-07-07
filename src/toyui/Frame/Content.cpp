//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Frame/Content.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Layer.h>
#include <toyui/Widget/Widget.h>

#include <toyui/UiWindow.h>
#include <toyui/Widget/RootSheet.h>

namespace toy
{
	Icon::Icon(Frame& frame)
		: d_frame(frame)
		, m_image(nullptr)
	{}

	void Icon::setImage(Image* image)
	{
		m_image = image;
		d_frame.markDirty(DIRTY_LAYOUT);
	}
}
