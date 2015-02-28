//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/mkUiTypes.h>

#include <Ui/mkUi.h>

#include <Ui/Nano/mkGlWindow.h>

namespace mk
{
	std::unique_ptr<Window> createTestWindow()
	{
		std::unique_ptr<Form> boardpt = make<Form>("scrollpartition");
		std::unique_ptr<Window> window = make<Window>(std::move(boardpt));

		Form* board = window->contents()->at(0);

		board->setName("kiUi Test");

		board->makeappend<Label>("", "kiui says hello.");

		//for(size_t i = 0; i < 20; ++i)
		//	window->makeappend<Label>("", "This window is being created by the ShowTestWindow() function. Please refer to the code for programming reference.\n\nUser Guide:");

		// @todo Add Styling : Size : 550, 680
		// @todo Add Styling : Table : 0.65f, 0.35f

		Form* current;

		current = board->makeappend<Expandbox>("Help");
		current->makeappend<Textbox>("", "This window is being created by the ShowTestWindow() function. Please refer to the code for programming reference.\n\nUser Guide:");

		current = board->makeappend<Expandbox>("Window options");

		current->makeappend<InputBool>("titlebar", true, [&window](){ window->widget()->as<WWindow>()->showTitlebar(); }, [&window](){ window->widget()->as<WWindow>()->hideTitlebar(); });
		current->makeappend<InputBool>("movable", true, [&window](){ window->widget()->as<WWindow>()->setMovable(); }, [&window](){ window->widget()->as<WWindow>()->setUnmovable(); });
		current->makeappend<InputBool>("resizable", true, [&window](){ window->widget()->as<WWindow>()->setResizable(); }, [&window](){ window->widget()->as<WWindow>()->setUnsizable(); });
		current->makeappend<InputBool>("scrollable", true, [&window](){ window->widget()->as<WWindow>()->setScrollable(); }, [&window](){ window->widget()->as<WWindow>()->setUnscrollable(); });

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

		// current->makeappend<SliderAngle>("angle", 0.f);
		// current->makeappend<FVector3>("slider float3", 0.0f, 1.0f);

		// window->setMovable(false);
		// window->setResizable(false);
		// window->setTitlebar(true);
		

		return std::move(window);
	}

	void exampleApp()
	{
		std::unique_ptr<GlWindow> glwindow = std::make_unique<GlWindow>(1200, 800, "mk UiEditApp");
		glwindow->initContext();

		UiWindow* uiwindow = glwindow->uiWindow();
		Form* root = uiwindow->rootForm();
		root->append(createTestWindow());

		bool pursue = true;
		while(pursue)
			pursue = glwindow->renderFrame();
	}
}
