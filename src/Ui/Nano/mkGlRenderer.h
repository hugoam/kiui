//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_NANOGLRENDERER_H
#define MK_NANOGLRENDERER_H

/* mk Og */
#include <Ui/mkUiForward.h>
#include <Ui/Nano/mkNanoWindow.h>
#include <Object/Util/mkTimer.h>

namespace mk
{
	class MK_UI_EXPORT GlRenderer
	{
	public:
		GlRenderer(UiWindow& uiWindow, RenderWindow& renderWindow);
		~GlRenderer();

		UiWindow& uiWindow() { return m_uiWindow; }
		NanoWindow& nanoWindow() { return *m_nanoWindow; }

		void initContext();

		void renderFrame();

		static void initGlew();

	protected:
		UiWindow& m_uiWindow;
		RenderWindow& m_renderWindow;
		string m_resourcePath;

		unique_ptr<NanoWindow> m_nanoWindow;

		Clock m_clock;
	};



}

#endif
