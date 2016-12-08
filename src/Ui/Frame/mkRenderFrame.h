//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_RENDERFRAME_H
#define MK_RENDERFRAME_H

/* mk Front */
#include <Object/mkTyped.h>
#include <Ui/mkUiForward.h>
#include <Ui/Style/mkDim.h>

namespace mk
{
	class MK_UI_EXPORT RenderFrame : public NonCopy
	{
	public:
		RenderFrame(Frame& frame);
		~RenderFrame();

		DrawFrame& drawFrame() { return m_drawFrame; }
		Frame& frame() { return m_frame; }

		virtual void redraw(Renderer& target, BoxFloat& rect, BoxFloat& paddedRect, BoxFloat& contentRect) = 0;

	protected:
		DrawFrame& m_drawFrame;
		Frame& m_frame;
	};
}

#endif
