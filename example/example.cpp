//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/mkUiTypes.h>

#include <Ui/mkUi.h>

#include <Ui/Nano/mkGlWindow.h>

#ifdef KIUI_EMSCRIPTEN
#define KIUI_EXAMPLE_RESSOURCE_PATH "/data"
#include <emscripten/emscripten.h>

mk::GlWindow* gGlWindow;
void iterate()
{
	gGlWindow->renderFrame();
}
#endif

#ifndef KIUI_EXAMPLE_RESSOURCE_PATH
  #define KIUI_EXAMPLE_RESSOURCE_PATH "../data/interface"
#endif

int main(int argc, char *argv[])
{
#ifdef KIUI_EMSCRIPTEN
	mk::GlWindow* glwindow = new mk::GlWindow(1200, 800, "mk UiEditApp", KIUI_EXAMPLE_RESSOURCE_PATH);
	gGlWindow = glwindow;
#else
	std::unique_ptr<mk::GlWindow> glwindow = mk::make_unique<mk::GlWindow>(1200, 800, "mk UiEditApp", KIUI_EXAMPLE_RESSOURCE_PATH);
#endif
	glwindow->initContext();

	mk::UiWindow* uiwindow = glwindow->uiWindow();
	uiwindow->init();

	mk::Form* root = uiwindow->rootForm();
	createUiTest(root);

#ifdef KIUI_EMSCRIPTEN
	emscripten_set_main_loop(iterate, 0, 1);
#else
	bool pursue = true;
	while (pursue)
		pursue = glwindow->renderFrame();
#endif
}