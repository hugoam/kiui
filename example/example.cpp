
#include <UiExampleConfig.h>
#include <UiExample.h>

#include <toyui/Bundle.h>

#if TOY_PLATFORM_EMSCRIPTEN
	#include <toyui/Context/EmscriptenContext.h>
	#define TOYUI_RESOURCE_PATH "/data/"
	#include <emscripten/emscripten.h>

	toy::UiWindow* gWindow;
	void iterate()
	{
		gWindow->nextFrame();
	}
#elif TOY_CONTEXT_OGRE
	#include <toyui/Context/Ogre/OgreContext.h>
#elif TOY_CONTEXT_WINDOWS
	#include <toyui/Context/Windows/WindowsContext.h>
#elif TOY_RENDERER_GL
	#include <toyui/Context/Glfw/GlfwContext.h>
#elif TOY_RENDERER_BGFX
	#include <toyui/Context/Bgfx/BgfxContext.h>
#endif

#ifndef TOYUI_RESOURCE_PATH
	#define TOYUI_RESOURCE_PATH "../../data/"
#endif

int main(int argc, char *argv[])
{
#ifdef TOY_PLATFORM_EMSCRIPTEN
	toy::EmRenderSystem renderSystem(TOYUI_RESOURCE_PATH);
#elif defined TOY_CONTEXT_OGRE
	toy::OgreRenderSystem renderSystem(TOYUI_RESOURCE_PATH);
	renderSystem.init();
#elif TOY_CONTEXT_WINDOWS
	toy::WinRenderSystem renderSystem(TOYUI_RESOURCE_PATH);
#elif TOY_RENDERER_GL
	toy::GlfwRenderSystem renderSystem(TOYUI_RESOURCE_PATH);
#elif TOY_RENDERER_BGFX
	toy::BgfxSystem renderSystem(TOYUI_RESOURCE_PATH);
#endif

	toy::UiWindow uiwindow(renderSystem, "kiUi demo", 1200, 800, false);

	toy::Wedge& rootSheet = *uiwindow.m_rootSheet;
	createUiTest(rootSheet);

#ifdef TOY_PLATFORM_EMSCRIPTEN
	gWindow = &uiwindow;
	emscripten_set_main_loop(iterate, 0, 1);
#else
	bool pursue = true;
	while(pursue)
	{
#if defined TOY_RENDERER_OGRE || defined TOY_RENDERER_BGFX
		renderSystem.nextFrame();
#endif
		pursue = uiwindow.nextFrame();
	}
#endif
}
