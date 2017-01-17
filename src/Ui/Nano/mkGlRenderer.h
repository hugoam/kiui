//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_NANOGLRENDERER_H
#define MK_NANOGLRENDERER_H

/* mk Og */
#include <Object/Util/mkTimer.h>
#include <Ui/mkUiForward.h>
#include <Ui/Nano/mkNanoRenderer.h>

namespace mk
{
	class MK_UI_EXPORT GlRenderer : public NanoRenderer
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
