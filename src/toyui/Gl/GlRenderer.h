//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_GLRENDERER_H
#define TOY_GLRENDERER_H

/* toy Og */
#include <toyobj/Util/Timer.h>
#include <toyui/Forward.h>
#include <toyui/Nano/NanoRenderer.h>

namespace toy
{
	class TOY_UI_EXPORT GlRenderer : public NanoRenderer
	{
	public:
		GlRenderer(const string& resourcePath);
		~GlRenderer();

		// init
		virtual void setupContext();
		virtual void releaseContext();

		void render(MasterLayer& layer);

		void logFPS();

	protected:
		void initGlew();

	protected:
		Clock m_clock;
	};



}

#endif
