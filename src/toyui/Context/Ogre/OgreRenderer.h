//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_OGRERENDERER_H
#define TOY_OGRERENDERER_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Render/Renderer.h>
#include <toyui/Gl/GlRenderer.h>

/* Ogre */
#include <Ogre.h>

namespace toy
{
	class OgreRenderTarget : public RenderTarget
	{
	public:
		OgreRenderTarget(Renderer& renderer, MasterLayer& masterLayer);
		~OgreRenderTarget();

	protected:
		Ogre::SceneManager& m_scene;
		Ogre::SceneNode& m_node;
		Ogre::Camera& m_camera;
	};

	class OgreRenderer : public GlRenderer
	{
	public:
		OgreRenderer(const string& resourcePath);

		virtual object_ptr<RenderTarget> createRenderTarget(MasterLayer& masterLayer);
	};
}

#endif // TOY_OGRERENDERER_H
