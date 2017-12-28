//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_BGFX_UI_RENDERER_H
#define TOY_BGFX_UI_RENDERER_H

/* toy */
#include <toyui/Types.h>
#include <toyui/Backend/Nano/NanoRenderer.h>

namespace toy
{
	class TOY_UI_BGFX_EXPORT BgfxUiRenderer : public NanoRenderer
	{
	public:
		BgfxUiRenderer(const string& resourcePath);

		// init
		virtual void setupContext();
		virtual void releaseContext();
	};
}

#endif // TOY_BGFX_UI_RENDERER_H
