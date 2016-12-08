//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Frame/mkRenderFrame.h>

#include <Ui/Frame/mkFrame.h>
#include <Ui/Widget/mkWidget.h>

namespace mk
{
	RenderFrame::RenderFrame(Frame& frame)
		: m_drawFrame(frame)
		, m_frame(frame)
	{}

	RenderFrame::~RenderFrame()
	{}
}
