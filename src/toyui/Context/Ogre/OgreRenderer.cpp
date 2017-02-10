//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Context/Ogre/OgreRenderer.h>

#include <toyui/Context/Ogre/OgreWindow.h>

#include <toyui/Widget/RootSheet.h>

#include <Ogre.h>
#include <Compositor/OgreCompositorManager2.h>

namespace toy
{
	OgreRenderTarget::OgreRenderTarget(Renderer& renderer, MasterLayer& masterLayer)
		: RenderTarget(renderer, masterLayer, true)
		, m_scene(*Ogre::Root::getSingleton().createSceneManager(Ogre::ST_GENERIC, 1, Ogre::INSTANCING_CULLING_SINGLETHREAD))
		, m_node(*m_scene.getRootSceneNode()->createChildSceneNode())
		, m_camera(*m_scene.createCamera("Ui Camera"))
	{
		m_camera.detachFromParent();
		m_node.attachObject(&m_camera);

		OgreRenderWindow& renderWindow = static_cast<OgreRenderWindow&>(masterLayer.widget()->context().renderWindow());

		Ogre::CompositorManager2& compositorManager = *Ogre::Root::getSingleton().getCompositorManager2();
		compositorManager.addWorkspace(&m_scene, &renderWindow.context(), &m_camera, "Clear Workspace", true);
		compositorManager.addWorkspace(&m_scene, &renderWindow.context(), &m_camera, "Ui Workspace", true);

		m_camera.setUserAny(Ogre::Any(static_cast<RenderTarget*>(this)));
	}

	OgreRenderTarget::~OgreRenderTarget()
	{}

	OgreRenderer::OgreRenderer(const string& resourcePath)
		: GlRenderer(resourcePath)
	{}

	unique_ptr<RenderTarget> OgreRenderer::createRenderTarget(MasterLayer& masterLayer)
	{
		return make_unique<OgreRenderTarget>(*this, masterLayer);
	}
}
