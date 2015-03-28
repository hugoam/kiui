//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/mkUiTypes.h>

#include <Ui/mkUi.h>

#include <Ui/Nano/mkGlWindow.h>

int main(int argc, char *argv[])
{
	std::unique_ptr<mk::GlWindow> glwindow = make_unique<mk::GlWindow>(1200, 800, "mk UiEditApp", "../data/interface");
	glwindow->initContext();

	mk::UiWindow* uiwindow = glwindow->uiWindow();
	mk::Form* root = uiwindow->rootForm();
	createUiTestWindow(root);

	bool pursue = true;
	while(pursue)
		pursue = glwindow->renderFrame();
}