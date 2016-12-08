//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/mkUiTypes.h>

#include <Ui/Nano/mkGlWindow.h>

#include <example.h>

#ifdef KIUI_EMSCRIPTEN
#define KIUI_EXAMPLE_RESSOURCE_PATH "/data/"
#include <emscripten/emscripten.h>

mk::GlWindow* gGlWindow;
void iterate()
{
	gGlWindow->renderFrame();
}
#endif

#ifndef KIUI_EXAMPLE_RESSOURCE_PATH
  #define KIUI_EXAMPLE_RESSOURCE_PATH "../data/"
#endif

int main(int argc, char *argv[])
{
	mk::GlWindow glwindow(1200, 800, "kiUi demo", KIUI_EXAMPLE_RESSOURCE_PATH);
	glwindow.initContext();

	mk::UiWindow& uiwindow = glwindow.uiWindow();
	//uiwindow.init();

	mk::Device& root = uiwindow.rootDevice();
	createUiTest(root);

#ifdef KIUI_EMSCRIPTEN
	gGlWindow = &glwindow;
	emscripten_set_main_loop(iterate, 0, 1);
#else
	bool pursue = true;
	while (pursue)
		pursue = glwindow.renderFrame();
#endif
}
