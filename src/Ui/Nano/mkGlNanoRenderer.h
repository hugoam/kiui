//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_GLNANORENDERER_H
#define MK_GLNANORENDERER_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Nano/mkNanoRenderer.h>

namespace mk
{
	class MK_UI_EXPORT GlNanoRenderer : public NanoRenderer
	{
	public:
		GlNanoRenderer(const string& resourcePath);
		~GlNanoRenderer();

		// init
		virtual void setupContext();
		virtual void releaseContext();
	};
}

#endif
