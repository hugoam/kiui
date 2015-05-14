//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/mkUiTypes.h>

#include <Ui/mkUi.h>

#include <Ui/Html/mkHtml.h>

#define KIUI_EXAMPLE_RESSOURCE_PATH "/data/"
#include <emscripten/emscripten.h>

#include <fstream>

mk::HtmlWindow* gWindow;
void iterate()
{
	gWindow->nextFrame();
}

void run_script_file(const std::string& file)
{
	std::ifstream ifs(file);
	std::stringstream sstr;
	sstr << ifs.rdbuf();
	std::string script = sstr.str();
	emscripten_run_script(script.c_str());
}

int main(int argc, char *argv[])
{
	run_script_file("/data/html/jquery-2.1.4.js");
	run_script_file("/data/html/kiui_html.js");

	mk::HtmlWindow htmlwindow(1200, 800, "kiUi demo", KIUI_EXAMPLE_RESSOURCE_PATH);
	gWindow = &htmlwindow;

	mk::UiWindow& uiwindow = htmlwindow.uiWindow();
	uiwindow.init();

	mk::Form& root = uiwindow.rootForm();
	createUiTest(root);

	emscripten_set_main_loop(iterate, 0, 1);
}
