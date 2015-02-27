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
		std::unique_ptr<Form> window = make<Form>("scrollpartition");
		window->setName("kiUi Test");

		window->makeappend<Label>("", "kiui says hello.");

		//for(size_t i = 0; i < 20; ++i)
		//	window->makeappend<Label>("", "This window is being created by the ShowTestWindow() function. Please refer to the code for programming reference.\n\nUser Guide:");

		// @todo Add Styling : Size : 550, 680
		// @todo Add Styling : Table : 0.65f, 0.35f

		//ImGui::Text("MousePos (%g, %g)", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
		//ImGui::Text("MouseWheel %d", ImGui::GetIO().MouseWheel);
		
		Form* current;

		current = window->makeappend<Expandbox>("Help");
		current->makeappend<Label>("", "This window is being created by the ShowTestWindow() function. Please refer to the code for programming reference.\n\nUser Guide:");
		// ImGui::ShowUserGuide();

		// @todo This should be a TextBox

		current = window->makeappend<Expandbox>("Window options");

		current->makeappend<InputBool>("titlebar", true); //, [&window](Button*, bool on){ window->attrs["titlebar"] = on ? "true" : "false"; });
		current->makeappend<InputBool>("movable", true); // , [&window](Button*, bool on){ window->attrs["movable"] = on ? "true" : "false"; });
		current->makeappend<InputBool>("resizable", true); // , [&window](Button*, bool on){ window->attrs["resizable"] = on ? "true" : "false"; });
		current->makeappend<InputBool>("scrollable", true); // , [&window](Button*, bool on){ window->attrs["scrollable"] = on ? "true" : "false"; });

		current->makeappend<SliderFloat>("fill alpha", Stat<float>(0.f, 0.f, 1.f)); // callback change window alpha

		current = window->makeappend<Expandbox>("Widgets");

		/*Dropdown* dropdown = current->makeappend<Dropdown>([](Form* form) {});

		for(const char* str : { "aaaa", "bbbb", "cccc", "dddd" })
			dropdown->makeappend<Label>("", str);

		dropdown->makeappend<Label>("", "aaaa");
		dropdown->makeappend<Label>("", "bbbb");
		dropdown->makeappend<Label>("", "cccc");
		dropdown->makeappend<Label>("", "dddd");*/

		//current->makeappend<Dropdown>([](Form* form) {}, StringVector({ "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK" }));

		current = current->makeappend<Table>(StringVector({ "input", "label" }), std::vector<float>({ 0.7f, 0.3f }));

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
		

		return std::make_unique<Window>(std::move(window));
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
