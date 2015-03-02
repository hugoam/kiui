//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/mkUiTypes.h>

#include <Ui/mkUi.h>

#include <Ui/Nano/mkGlWindow.h>

#include <float.h>

namespace mk
{
	void createTestWindow(Form* parent)
	{
		unique_ptr<Form> boardpt = make_unique<Form>("scrollpartition");

		Window* window = parent->makeappend<Window>(std::move(boardpt));
		WWindow* wwindow = window->widget()->as<WWindow>();

		wwindow->setMovable();
		wwindow->setResizable();

		Form* board = window->contents()->at(0);

		board->setName("kiUi Test");

		board->makeappend<Label>("", "kiui says hello.");
		board->makeappend<Button>("ceguibutton", "I'm a TaharezLook button.");

		//for(size_t i = 0; i < 20; ++i)
		//	window->makeappend<Label>("", "This window is being created by the ShowTestWindow() function. Please refer to the code for programming reference.\n\nUser Guide:");

		// @todo Add Styling : Size : 550, 680
		// @todo Add Styling : Table : 0.65f, 0.35f

		Form* current;

		current = board->makeappend<Expandbox>("Help");
		current->makeappend<Textbox>("", "This window is being created by the ShowTestWindow() function. Please refer to the code for programming reference.\n\nUser Guide:");

		current = board->makeappend<Expandbox>("Window options");

		current->makeappend<InputBool>("titlebar", true, std::bind(&WWindow::showTitlebar, wwindow), std::bind(&WWindow::hideTitlebar, wwindow));
		current->makeappend<InputBool>("movable", true, std::bind(&WWindow::setMovable, wwindow), std::bind(&WWindow::setUnmovable, wwindow));
		current->makeappend<InputBool>("resizable", true, std::bind(&WWindow::setResizable, wwindow), std::bind(&WWindow::setUnsizable, wwindow));
		current->makeappend<InputBool>("scrollable", true, std::bind(&WWindow::setScrollable, wwindow), std::bind(&WWindow::setUnscrollable, wwindow));

		current->makeappend<SliderFloat>("fill alpha", Stat<float>(0.f, 0.f, 1.f), [&window](float alpha){ window->widget()->frame()->inkstyle()->mBackgroundColour.setA(alpha); });

		current = board->makeappend<Expandbox>("Widgets");

		current = current->makeappend<Table>(StringVector({ "input", "label" }), std::vector<float>({ 0.7f, 0.3f }));

		current->makeappend<InputDropdown>("dropdown input", StringVector({ "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK" }), [](string val) {});

		current->makeappend<InputText>("string input", "Hello, world!");
		current->makeappend<InputInt>("int input", 123);
		current->makeappend<InputFloat>("float input", 0.001f);

		current->makeappend<SliderInt>("int 0..3", Stat<int>(2, 0, 3));
		current->makeappend<SliderInt>("int -100..100", Stat<int>(0, -100, 100));

		current->makeappend<SliderFloat>("float input", Stat<float>(1.123f, 0.0f, 2.0f));
		current->makeappend<SliderFloat>("log float", Stat<float>(0.f, 0.0f, 10.0f));
		current->makeappend<SliderFloat>("signed log float", Stat<float>(0.f, -10.0f, 10.0f));
		current->makeappend<SliderFloat>("unbound float", Stat<float>(123456789.0f, -FLT_MAX, FLT_MAX));
	}

	void exampleApp()
	{
		unique_ptr<GlWindow> glwindow = make_unique<GlWindow>(1200, 800, "mk UiEditApp", "../Data/interface");
		glwindow->initContext();

		UiWindow* uiwindow = glwindow->uiWindow();
		Form* root = uiwindow->rootForm();
		createTestWindow(root);

		bool pursue = true;
		while(pursue)
			pursue = glwindow->renderFrame();
	}
}
