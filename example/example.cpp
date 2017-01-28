
#include <mkUiExampleConfig.h>
#include <mkUiExample.h>

#include <Ui/Gl/mkGlWindow.h>
#include <Ui/mkUiTypes.h>

#ifdef KIUI_EMSCRIPTEN
#define TOYUI_EXAMPLE_RESOURCE_PATH "/data/"
#include <emscripten/emscripten.h>

mk::GlWindow* gGlWindow;
void iterate()
{
	gGlWindow->renderFrame();
}
#endif

#ifndef TOYUI_EXAMPLE_RESOURCE_PATH
  #define TOYUI_EXAMPLE_RESOURCE_PATH "../../data/"
#endif

int main(int argc, char *argv[])
{
	mk::GlContext glContext(TOYUI_EXAMPLE_RESOURCE_PATH);
	mk::UiWindow uiwindow(glContext, "kiUi demo", 1200, 800, false);

	mk::Sheet& rootSheet = uiwindow.rootSheet();
	createUiTest(rootSheet);

#ifdef KIUI_EMSCRIPTEN
	gGlWindow = &glwindow;
	emscripten_set_main_loop(iterate, 0, 1);
#else
	bool pursue = true;
	while (pursue)
		pursue = uiwindow.nextFrame();
#endif
}
