//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TOY_GL

#ifndef MK_GLRENDERER_H
#define MK_GLRENDERER_H

/* mk Og */
#include <Object/Util/mkTimer.h>
#include <Ui/mkUiForward.h>
#include <Ui/Nano/mkGlNanoRenderer.h>

namespace mk
{
	class MK_UI_EXPORT GlRenderer : public GlNanoRenderer
	{
	public:
		GlRenderer(const string& resourcePath);
		~GlRenderer();

		void init();

		void render(MasterLayer& layer);

		void logFPS();

	protected:
		void initGlew();

	protected:
		Clock m_clock;
	};



}

#endif

#endif