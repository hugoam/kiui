//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_OGRECONTEXT_H
#define TOY_OGRECONTEXT_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/UiWindow.h>

namespace Ogre
{
	class Root;
	class RenderWindow;
	class RenderSystem;

	class HlmsManager;
	class HlmsTextureManager;
	class HlmsUnlit;
	class HlmsPbs;
}

namespace toy
{
	class OgreContext : public Context
	{
	public:
		OgreContext(OgreRenderSystem& renderSystem, const string& name, int width, int height, bool fullScreen);
	};

	class OgreRenderSystem : public RenderSystem
	{
	public:
		OgreRenderSystem(const string& resourcePath);
		~OgreRenderSystem();

		Ogre::Root& ogreRoot() { return *m_ogreRoot; }
		bool contextActive() { return m_contextActive; }

		bool nextFrame();

		void init();
		void setupRenderer(const string& name);
		void setupHiddenWindow();
		void setupUiWorkspace();

		void focusChange() { m_contextActive = !m_contextActive; }

		virtual object_ptr<Context> createContext(const string& name, int width, int height, bool fullScreen);
		virtual object_ptr<Renderer> createRenderer(Context& context);

	protected:
		unique_ptr<Ogre::Root> m_ogreRoot;
		bool m_contextActive;

		Ogre::RenderWindow* m_hiddenWindow;
		Ogre::RenderSystem* m_renderSystem;
	};
}

#endif // TOY_OGRECONTEXT_H
