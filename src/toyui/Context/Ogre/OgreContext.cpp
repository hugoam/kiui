//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Context/Ogre/OgreContext.h>

#include <toyui/Context/Ogre/OgreWindow.h>
#include <toyui/Context/Ogre/OgreRenderer.h>

#include <toyui/UiWindow.h>

#include <toyui/Gl/GlRenderer.h>
#include <toyui/Render/Renderer.h>

#include <OgreRoot.h>
#include <Compositor/OgreCompositorManager2.h>
#include <Compositor/OgreCompositorNodeDef.h>
#include <Compositor/OgreCompositorWorkspaceDef.h>
#include <Compositor/Pass/OgreCompositorPass.h>
#include <Compositor/Pass/OgreCompositorPassProvider.h>

namespace toy
{
	class UiPassProvider : public Ogre::CompositorPassProvider
	{
	public:
		Ogre::CompositorPassDef* addPassDef(Ogre::CompositorPassType passType, Ogre::IdString customId, Ogre::uint32 rtIndex, Ogre::CompositorNodeDef* parentNodeDef);

		Ogre::CompositorPass* addPass(const Ogre::CompositorPassDef* definition, Ogre::Camera* camera, Ogre::CompositorNode* parentNode, const Ogre::CompositorChannel& target, Ogre::SceneManager* sceneManager);

		static Ogre::IdString m_passId;
	};

	class UiPassDef : public Ogre::CompositorPassDef
	{
	public:
		UiPassDef(Ogre::uint32 rtIndex)
			: Ogre::CompositorPassDef(Ogre::PASS_CUSTOM, rtIndex)
		{}
	};

	class UiPass : public Ogre::CompositorPass
	{
	public:
		UiPass(const Ogre::CompositorPassDef* definition, const Ogre::CompositorChannel& target, Ogre::CompositorNode* parentNode, Ogre::Camera* camera)
			: Ogre::CompositorPass(definition, target, parentNode)
			, m_camera(camera)
		{}

		virtual void execute(const Ogre::Camera* lodCameraconst)
		{
			RenderTarget* renderer = Ogre::any_cast<RenderTarget*>(m_camera->getUserAny());
			renderer->render();
		}

	protected:
		Ogre::Camera* m_camera;
	};

	Ogre::CompositorPassDef* UiPassProvider::addPassDef(Ogre::CompositorPassType passType, Ogre::IdString customId, Ogre::uint32 rtIndex, Ogre::CompositorNodeDef* parentNodeDef)
	{
		if(customId == m_passId)
			return OGRE_NEW UiPassDef(rtIndex);
		return nullptr;
	}

	Ogre::CompositorPass* UiPassProvider::addPass(const Ogre::CompositorPassDef* definition, Ogre::Camera* camera, Ogre::CompositorNode* parentNode
		, const Ogre::CompositorChannel& target, Ogre::SceneManager* sceneManager)
	{
		return OGRE_NEW UiPass(definition, target, parentNode, camera);
	}

	Ogre::IdString UiPassProvider::m_passId("Ui");

	OgreContext::OgreContext(OgreRenderSystem& renderSystem, const string& name, int width, int height, bool fullScreen)
		: Context(renderSystem)
	{
		unique_ptr<OgreRenderWindow> renderWindow = make_unique<OgreRenderWindow>(renderSystem, name, width, height, fullScreen);
		unique_ptr<OISInputWindow> inputWindow = make_unique<OISInputWindow>(*renderWindow);

		this->init(std::move(renderWindow), std::move(inputWindow));
	}

	OgreRenderSystem::OgreRenderSystem(const string& resourcePath)
		: RenderSystem(resourcePath)
		, m_ogreRoot(make_unique<Ogre::Root>())
	{}
	
	OgreRenderSystem::~OgreRenderSystem()
	{}

	unique_ptr<Context> OgreRenderSystem::createContext(const string& name, int width, int height, bool fullScreen)
	{
		return make_unique<OgreContext>(*this, name, width, height, fullScreen);
	}

	unique_ptr<Renderer> OgreRenderSystem::createRenderer(Context& context)
	{
		return make_unique<OgreRenderer>(m_resourcePath);
	}

	bool OgreRenderSystem::nextFrame()
	{
		Ogre::WindowEventUtilities::messagePump();

		if(m_contextActive)
			m_ogreRoot->renderOneFrame();
		else
			m_ogreRoot->clearEventTimes();

		return true;
	}

	void OgreRenderSystem::initWorkspace()
	{
		static UiPassProvider m_passProvider;

		Ogre::CompositorManager2* compositorManager = m_ogreRoot->getCompositorManager2();
		compositorManager->setCompositorPassProvider(&m_passProvider);

		Ogre::CompositorNodeDef* nodeDef = compositorManager->addNodeDefinition("AutoGen " + (Ogre::IdString("Ui Workspace") + Ogre::IdString("/Node")).getReleaseText());
		nodeDef->addTextureSourceName("WindowRT", 0, Ogre::TextureDefinitionBase::TEXTURE_INPUT);
		nodeDef->setNumTargetPass(1);

		Ogre::CompositorTargetDef* targetDef = nodeDef->addTargetPass("WindowRT");
		targetDef->setNumPasses(1);
		targetDef->addPass(Ogre::PASS_CUSTOM, UiPassProvider::m_passId);

		Ogre::CompositorWorkspaceDef* workDef = compositorManager->addWorkspaceDefinition("Ui Workspace");
		workDef->connectExternal(0, nodeDef->getName(), 0);
	}

	/*void OgreSystem::setupSpaceSheet()
	{
		m_sceneNode = m_viewport.sceneManager().createSceneNode();
		m_sceneNode->getUserObjectBindings().setUserAny(Ogre::Any(static_cast<Object*>(this)));

		m_viewport.ogreCamera().setUserAny(Ogre::Any(&m_layer->target()));

		Ogre::Item& item = *m_sceneNode->getCreator()->createItem("SpaceSheet");
		item.setQueryFlags(SPACESHEET_OGRE_MASK);

		Ogre::HlmsUnlitDatablock* datablock = ogModule.createUnlitDatablock("SpaceSheet", "", m_texture);
		item.setDatablock(datablock);

		m_sceneNode->attachObject(&item);

		OgreSystem& ogreSystem = static_cast<OgreSystem&>(m_viewport.uiContext());

		Ogre::Root& ogreRoot = ogWindow.ogModule().ogreRoot();

		m_texture = ogreRoot.getTextureManager()->createManual("SpaceSheetTexture",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			Ogre::TEX_TYPE_2D,
			size_t(m_width),
			size_t(m_height),
			0,
			Ogre::PF_R8G8B8,
			Ogre::TU_RENDERTARGET,
			0,
			true
		);

		Ogre::RenderTarget& renderTexture = *m_texture->getBuffer()->getRenderTarget();

		ogreRoot.getCompositorManager2()->addWorkspace(&m_viewport.sceneManager(), &renderTexture, &m_viewport.ogreCamera(), "Ui Workspace", true, 0);
		ogreRoot.getCompositorManager2()->addWorkspace(&m_viewport.sceneManager(), &renderTexture, &m_viewport.ogreCamera(), "Clear Workspace", true, 0);
	}*/
}
