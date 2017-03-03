
#include <UiExampleConfig.h>
#include <UiExample.h>

#include <toyui/Types.h>

#ifdef TOY_PLATFORM_EMSCRIPTEN
	#include <toyui/Context/EmscriptenContext.h>
	#define TOYUI_RESOURCE_PATH "/data/"
	#include <emscripten/emscripten.h>

	toy::UiWindow* gWindow;
	void iterate()
	{
		gWindow->nextFrame();
	}
#else
	#include <toyui/Context/Glfw/GlfwContext.h>
#endif

#ifndef TOYUI_RESOURCE_PATH
	#define TOYUI_RESOURCE_PATH "../../data/"
#endif

int main(int argc, char *argv[])
{
#ifdef TOY_PLATFORM_EMSCRIPTEN
	toy::EmRenderSystem renderSystem(TOYUI_RESOURCE_PATH);
#else
	toy::GlfwRenderSystem renderSystem(TOYUI_RESOURCE_PATH);
#endif

	toy::UiWindow uiwindow(renderSystem, "kiUi demo", 1200, 800, false);

	toy::Container& rootSheet = uiwindow.rootSheet();
	createUiTest(rootSheet);

#ifdef TOY_PLATFORM_EMSCRIPTEN
	gWindow = &uiwindow;
	emscripten_set_main_loop(iterate, 0, 1);
#else
	bool pursue = true;
	while (pursue)
		pursue = uiwindow.nextFrame();
#endif
}
