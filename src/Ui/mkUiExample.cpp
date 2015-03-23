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
	Dockspace* createUiTestDockspace(Form* root)
	{
		WMasterDockline::styleCls()->layout()->d_weights = { 0.2f, 0.6f, 0.2f };

		Dockspace* dockspace = root->makeappend<Dockspace>();

		unique_ptr<Form> dock0 = make_unique<PartitionY>();
		dock0->setAttr("dockid", string("0.0"));
		dock0->setAttr("name", string("Dock 0"));

		unique_ptr<Form> dock1 = make_unique<PartitionY>();
		dock1->setAttr("dockid", string("0.1"));
		dock1->setAttr("name", string("Dock 1"));

		unique_ptr<Form> dock2 = make_unique<PartitionY>();
		dock2->setAttr("dockid", string("0.2"));
		dock2->setAttr("name", string("Dock 2"));

		dockspace->append(std::move(dock0));
		dockspace->append(std::move(dock1));
		dockspace->append(std::move(dock2));

		return dockspace;
	}

	Tabber* createUiTestTabs(Form* root)
	{
		Tabber* tabber = root->makeappend<Tabber>();

		unique_ptr<Form> tab0 = make_unique<Tabber>();
		tab0->setAttr("name", string("Tab 0"));

		unique_ptr<Form> tab1 = make_unique<PartitionY>();
		tab1->setAttr("name", string("Tab 1"));

		unique_ptr<Form> tab2 = make_unique<PartitionY>();
		tab2->setAttr("name", string("Tab 2"));

		tabber->append(std::move(tab0));
		tabber->append(std::move(tab1));
		tabber->append(std::move(tab2));

		return tabber;
	}

	Table* createUiTestTable(Form* parent)
	{
		Table* table = parent->makeappend<Table>(StringVector({ "ID", "Name", "Path", "Flags" }), std::vector<float>({ 0.25f, 0.25f, 0.25f, 0.25f }));

		table->makeappend<LabelSequence>(StringVector({ "0000", "Robert", "/path/robert", "...." }));
		table->makeappend<LabelSequence>(StringVector({ "0001", "Stephanie", "/path/stephanie", "line 1" }));
		table->makeappend<LabelSequence>(StringVector({ "0002", "C64", "/path/computer", "...." }));

		return table;
	}

	Table* createUiTestTableAlt(Form* parent)
	{
		Table* table = parent->makeappend<Table>(StringVector({ "Column 0", "Column 1", "Column 3" }), std::vector<float>({ 0.33f, 0.33f, 0.33f }));

		table->makeappend<LabelSequence>(StringVector({ "Hello", "ImGui", "World!" }));
		table->makeappend<ButtonSequence>(StringVector({ "Banana", "Apple", "Corniflower" }));
		table->makeappend<RadioSwitch>(Form::Trigger(), 0, StringVector({ "radio a", "radio b", "radio b" }));

		Sequence* line = table->makeappend<Sequence>();

		Expandbox* box0 = line->makeappend<Expandbox>("Category A");
		box0->makeappend<Label>("Blah blah blah");
		
		Expandbox* box1 = line->makeappend<Expandbox>("Category B");
		box1->makeappend<Label>("Blah blah blah");

		Expandbox* box2 = line->makeappend<Expandbox>("Category C");
		box2->makeappend<Label>("Blah blah blah");


		table = parent->makeappend<Table>(StringVector({ "Left", "Right" }), std::vector<float>({ 0.5f, 0.5f }));

		line = table->makeappend<Sequence>();

		line->makeappend<InputFloat>("Red", 0.05f);
		line->makeappend<InputFloat>("Blue", 0.05f);

		line = table->makeappend<Sequence>();

		line->makeappend<Textbox>("The quick brown fox jumps over the lazy dog.");
		line->makeappend<Textbox>("The quick brown fox jumps over the lazy dog.");

		line = table->makeappend<Sequence>();

		line->makeappend<Label>("Hello Left");
		line->makeappend<Label>("Hello Right");

		return table;
	}

	Tree* createUiTestTree(Form* parent)
	{
		Tree* tree = parent->makeappend<Tree>(nullptr);

		TreeNode* node = tree->makeappend<TreeNode>(nullptr, tree);
		node->setName("Tree");

		for(size_t i = 0; i < 5; i++)
		{
			TreeNode* innernode = node->makeappend<TreeNode>(nullptr, tree);
			innernode->setName("Child " + toString(i));

			innernode->makeappend<Label>("Blah blah");
			innernode->makeappend<Button>("Print");
		}

		return tree;
	}

	Tree* createUiTestTableTree(Form* parent)
	{
		Tree* tree = parent->makeappend<Tree>(nullptr);

		TreeNode* node = tree->makeappend<TreeNode>(nullptr, tree);
		node->setName("Inside a tree...");

		node = node->makeappend<TreeNode>(nullptr, tree);
		node->setName("node 1 (with borders)");

		TableNode* tablenode = node->makeappend<TableNode>(nullptr, tree);
		
		tablenode->makeappend<Label>("aaa");
		tablenode->makeappend<Label>("bbb");
		tablenode->makeappend<Label>("ccc");
		tablenode->makeappend<Label>("ddd");

		tablenode = node->makeappend<TableNode>(nullptr, tree);

		tablenode->makeappend<Label>("eee");
		tablenode->makeappend<Label>("fff");
		tablenode->makeappend<Label>("ggg");
		tablenode->makeappend<Label>("hhh");

		return tree;
	}

	Textbox* createUiTestMarkupText(Form* parent)
	{
		return nullptr;

		/*if(ImGui::TreeNode("Colored Text"))
		{
			// Using shortcut. You can use PushStyleColor()/PopStyleColor() for more flexibility.
			ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Pink");
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Yellow");
			ImGui::TreePop();
		}
		if(ImGui::TreeNode("Word Wrapping"))
		{
			// Using shortcut. You can use PushTextWrapPos()/PopTextWrapPos() for more flexibility.
			ImGui::TextWrapped("This is a long paragraph. The text should automatically wrap on the edge of the window. The current implementation follows simple rules that works for English and possibly other languages.");
			ImGui::Spacing();
			static float wrap_width = 200.0f;
			ImGui::SliderFloat("Wrap width", &wrap_width, -20, 600, "%.0f");
			ImGui::Text("Test paragraph 1:");
			ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetCursorScreenPos() + ImVec2(wrap_width, 0.0f), ImGui::GetCursorScreenPos() + ImVec2(wrap_width + 10, ImGui::GetTextLineHeight()), 0xFFFF00FF);
			ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + wrap_width);
			ImGui::Text("lazy dog. This paragraph is made to fit within %.0f pixels. The quick brown fox jumps over the lazy dog.", wrap_width);
			ImGui::GetWindowDrawList()->AddRect(ImGui::GetItemBoxMin(), ImGui::GetItemBoxMax(), 0xFF00FFFF);
			ImGui::PopTextWrapPos();
			ImGui::Text("Test paragraph 2:");
			ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetCursorScreenPos() + ImVec2(wrap_width, 0.0f), ImGui::GetCursorScreenPos() + ImVec2(wrap_width + 10, ImGui::GetTextLineHeight()), 0xFFFF00FF);
			ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + wrap_width);
			ImGui::Text("aaaaaaaa bbbbbbbb, cccccccc,dddddddd. eeeeeeee ffffffff. gggggggg!hhhhhhhh");
			ImGui::GetWindowDrawList()->AddRect(ImGui::GetItemBoxMin(), ImGui::GetItemBoxMax(), 0xFF00FFFF);
			ImGui::PopTextWrapPos();
			ImGui::TreePop();
		}
		if(ImGui::TreeNode("UTF-8 Text"))
		{
			// UTF-8 test (need a suitable font, try extra_fonts/mplus* files for example)
			// Most compiler appears to support UTF-8 in source code (with Visual Studio you need to save your file as 'UTF-8 without signature')
			// However for the sake for maximum portability here we are *not* including raw UTF-8 character in this source file, instead we encode the string with hexadecimal constants.
			// In your own application please be reasonable and use UTF-8 in the source or get the data from external files! :)
			ImGui::TextWrapped("(CJK text will only appears if the font supports it. Please check in the extra_fonts/ folder if you intend to use non-ASCII characters. Note that characters values are preserved even if the font cannot be displayed, so you can safely copy & paste garbled characters.)");
			ImGui::Text("Hiragana: \xe3\x81\x8b\xe3\x81\x8d\xe3\x81\x8f\xe3\x81\x91\xe3\x81\x93 (kakikukeko)");
			ImGui::Text("Kanjis: \xe6\x97\xa5\xe6\x9c\xac\xe8\xaa\x9e (nihongo)");
			static char buf[32] = "\xe6\x97\xa5\xe6\x9c\xac\xe8\xaa\x9e";
			ImGui::InputText("UTF-8 input", buf, IM_ARRAYSIZE(buf));
			ImGui::TreePop();
		}*/
	}

	Form* createUiTestControls(Form* parent)
	{
		Table* table = parent->makeappend<Table>(StringVector({ "input", "label" }), std::vector<float>({ 0.7f, 0.3f }));

		table->makeappend<InputDropdown>("dropdown input", StringVector({ "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK" }), [](string val) {});

		table->makeappend<InputText>("string input", "Hello, world!");
		table->makeappend<InputInt>("int input", 123);
		table->makeappend<InputFloat>("float input", 0.001f);

		table->makeappend<SliderInt>("int 0..3", AutoStat<int>(2, 0, 3, 1));
		table->makeappend<SliderInt>("int -100..100", AutoStat<int>(0, -100, 100, 1));

		table->makeappend<SliderFloat>("float input", AutoStat<float>(1.123f, 0.0f, 2.0f, 0.001f));
		table->makeappend<SliderFloat>("log float", AutoStat<float>(0.f, 0.0f, 10.0f, 1.f));
		//table->makeappend<SliderFloat>("signed log float", AutoStat<float>(0.f, -10.0f, 10.0f, 1.f));
		//table->makeappend<SliderFloat>("unbound float", AutoStat<float>(123456789.0f, -FLT_MAX, FLT_MAX, 1.f));

		// table->makeappend<SliderAngle>("angle", 0.f);
		// table->makeappend<FVector3>("slider float3", 0.0f, 1.0f);

		// ImGui::ColorEdit3("color 1", col1);
		// ImGui::ColorEdit4("color 2", col2);

		return table;
	}

	Form* createUiTestImageSkin(Form* parent)
	{
		Styler* styler = parent->uiWindow()->styler();

		styler->dynamicStyle("tlookwindow");
		styler->fetchStyle("tlookwindow")->inheritLayout(WWindow::styleCls());

		styler->dynamicStyle("tlookwindowheader");
		styler->fetchStyle("tlookwindowheader")->inheritLayout(WWindowHeader::styleCls());
		styler->fetchStyle("tlookwindowheader")->layout()->d_sizing[DIM_Y] = FIXED;
		styler->fetchStyle("tlookwindowheader")->layout()->d_size[DIM_Y] = 30.f;
		styler->fetchStyle("tlookwindowheader")->skin()->mImageSkin = ImageSkin("tlookhead");
		styler->fetchStyle("tlookwindowheader")->skin()->mEmpty = false;

		styler->dynamicStyle("tlookwindowbody");
		styler->fetchStyle("tlookwindowbody")->inheritLayout(WWindowBody::styleCls());
		styler->fetchStyle("tlookwindowbody")->layout()->d_padding = BoxFloat(20.f, 10.f, 10.f, 10.f);
		styler->fetchStyle("tlookwindowbody")->skin()->mImageSkin = ImageSkin("tlook");
		styler->fetchStyle("tlookwindowbody")->skin()->mMargin = BoxFloat(10.f, -5.f, 5.f, 0.f);
		styler->fetchStyle("tlookwindowbody")->skin()->mEmpty = false;

		styler->dynamicStyle("tlookbutton");
		styler->fetchStyle("tlookbutton")->inheritLayout(WButton::styleCls());
		styler->fetchStyle("tlookbutton")->skin()->mTextColour = Colour::White;
		styler->fetchStyle("tlookbutton")->skin()->mImageSkin = ImageSkin("tlookbutton");
		styler->fetchStyle("tlookbutton")->skin()->mPadding = DimFloat(20.f, 8.f);
		styler->fetchStyle("tlookbutton")->skin()->mEmpty = false;

		styler->dynamicStyle("tlooksection");
		styler->fetchStyle("tlooksection")->inheritLayout(PartitionX::styleCls());

		styler->override(styler->fetchStyle("tlooksection"), WWindow::styleCls(), styler->fetchStyle("tlookwindow"));
		styler->override(styler->fetchStyle("tlooksection"), WWindowHeader::styleCls(), styler->fetchStyle("tlookwindowheader"));
		styler->override(styler->fetchStyle("tlooksection"), WWindowBody::styleCls(), styler->fetchStyle("tlookwindowbody"));
		styler->override(styler->fetchStyle("tlooksection"), WButton::styleCls(), styler->fetchStyle("tlookbutton"));

		Form* overrider = parent->makeappend<Form>(styler->fetchStyle("tlooksection"));
		createUiTestWindow(overrider);

		return overrider;
	}

	Form* createUiTestInlineControls(Form* parent)
	{
		Form* div = parent->makeappend<DivY>();
		Form* line = div->makeappend<DivX>();

		line->makeappend<Label>("Hello");
		line->makeappend<Label>("World");

		line = parent->makeappend<DivX>();

		line->makeappend<Button>("Banana");
		line->makeappend<Button>("Apple");
		line->makeappend<Button>("Corniflower");

		line = parent->makeappend<DivX>();

		line->makeappend<Label>("Small buttons");
		line->makeappend<Button>("Like this one");
		line->makeappend<Label>("can fit within a text block.");

		line = parent->makeappend<DivX>();

		line->makeappend<InputBool>("My", true);
		line->makeappend<InputBool>("Tailor", true);
		line->makeappend<InputBool>("Is", true);
		line->makeappend<InputBool>("Rich", true);

		line = parent->makeappend<DivX>();

		line->makeappend<InputFloat>("X", 0.f);
		line->makeappend<InputFloat>("Y", 0.f);
		line->makeappend<InputFloat>("Z", 0.f);

		return div;
	}

	Form* createUiTestProgressDialog(Form* parent)
	{
		Dialog* dialog = parent->makeappend<Dialog>();
		ProgressBar* bar = dialog->makeappend<ProgressBar>();
		bar->widget()->as<WProgressBar>()->setPercentage(0.57f);
		return dialog;
	}

	Window* createUiTestWindow(Form* parent)
	{
		unique_ptr<Form> boardpt = make_unique<ScrollDivY>();

		Window* window = parent->makeappend<Window>(std::move(boardpt));
		WWindow* wwindow = window->widget()->as<WWindow>();

		wwindow->setMovable();
		wwindow->setResizable();

		Form* board = window->child(0);

		board->setName("kiUi Test");

		board->makeappend<Label>("kiui says hello.");

		Form* current;

		current = board->makeappend<Expandbox>("Help");
		current->makeappend<Textbox>("This window is being created by the ShowTestWindow() function. Please refer to the code for programming reference.\n\nUser Guide:");

		current = board->makeappend<Expandbox>("Window options");

		current->makeappend<InputBool>("titlebar", true, std::bind(&WWindow::showTitlebar, wwindow), std::bind(&WWindow::hideTitlebar, wwindow));
		current->makeappend<InputBool>("movable", true, std::bind(&WWindow::setMovable, wwindow), std::bind(&WWindow::setUnmovable, wwindow));
		current->makeappend<InputBool>("resizable", true, std::bind(&WWindow::setResizable, wwindow), std::bind(&WWindow::setUnsizable, wwindow));
		current->makeappend<InputBool>("scrollable", true, std::bind(&WWindow::setScrollable, wwindow), std::bind(&WWindow::setUnscrollable, wwindow));

		current->makeappend<SliderFloat>("fill alpha", AutoStat<float>(0.f, 0.f, 1.f, 0.1f), [&window](float alpha){ window->widget()->frame()->inkstyle()->mBackgroundColour.setA(alpha); });

		current = board->makeappend<Expandbox>("Widgets");
		createUiTestControls(current);

		current = board->makeappend<Expandbox>("Table");
		createUiTestTable(current);

		current = board->makeappend<Expandbox>("Columns");
		createUiTestTableAlt(current);

		/*
		if(ImGui::TreeNode("Style Editor"))
		{
		ImGui::ShowStyleEditor();
		ImGui::TreePop();
		}
		static bool a = false;
		if(ImGui::Button("Button")) { printf("Clicked\n"); a ^= 1; }
		if(a)
		{
		ImGui::SameLine();
		ImGui::Text("Thanks for clicking me!");
		}
		if(ImGui::TreeNode("Bullets"))
		{
		ImGui::BulletText("Bullet point 1");
		ImGui::BulletText("Bullet point 2\nOn multiple lines");
		ImGui::BulletText("Bullet point 3");
		ImGui::TreePop();
		}

		static bool check = true;
		ImGui::Checkbox("checkbox", &check);
		static int e = 0;
		ImGui::RadioButton("radio a", &e, 0); ImGui::SameLine();
		ImGui::RadioButton("radio b", &e, 1); ImGui::SameLine();
		ImGui::RadioButton("radio c", &e, 2);
		ImGui::Text("Hover me");
		if(ImGui::IsItemHovered())
		ImGui::SetTooltip("I am a tooltip");
		ImGui::SameLine();
		ImGui::Text("- or me");
		if(ImGui::IsItemHovered())
		{
		ImGui::BeginTooltip();
		ImGui::Text("I am a fancy tooltip");
		static float arr[] = { 0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f };
		ImGui::PlotLines("Curve", arr, IM_ARRAYSIZE(arr));
		ImGui::EndTooltip();
		}*/


		// Testing IMGUI_ONCE_UPON_A_FRAME macro
		//for (int i = 0; i < 5; i++)
		//{
		// IMGUI_ONCE_UPON_A_FRAME
		// {
		// ImGui::Text("This will be displayed only once.");
		// }
		//}

/*
		if(ImGui::CollapsingHeader("Graphs widgets"))
		{
		static float arr[] = { 0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f };
		ImGui::PlotLines("Frame Times", arr, IM_ARRAYSIZE(arr));
		static bool pause;
		static ImVector<float> values; if(values.empty()) { values.resize(100); memset(&values.front(), 0, values.size()*sizeof(float)); }
		static size_t values_offset = 0;
		if(!pause)
		{
		// create dummy data at fixed 60 hz rate
		static float refresh_time = -1.0f;
		if(ImGui::GetTime() > refresh_time + 1.0f / 60.0f)
		{
		refresh_time = ImGui::GetTime();
		static float phase = 0.0f;
		values[values_offset] = cosf(phase);
		values_offset = (values_offset + 1) % values.size();
		phase += 0.10f*values_offset;
		}
		}
		ImGui::PlotLines("Frame Times", &values.front(), (int)values.size(), (int)values_offset, "avg 0.0", -1.0f, 1.0f, ImVec2(0, 70));
		ImGui::SameLine(); ImGui::Checkbox("pause", &pause);
		ImGui::PlotHistogram("Histogram", arr, IM_ARRAYSIZE(arr), 0, NULL, 0.0f, 1.0f, ImVec2(0, 70));
		}
		
		if(ImGui::CollapsingHeader("Child regions"))
		{
		ImGui::Text("Without border");
		static int line = 50;
		bool goto_line = ImGui::Button("Goto");
		ImGui::SameLine();
		ImGui::PushItemWidth(100);
		goto_line |= ImGui::InputInt("##Line", &line, 0, 0, ImGuiInputTextFlags_EnterReturnsTrue);
		ImGui::PopItemWidth();
		ImGui::BeginChild("Sub1", ImVec2(ImGui::GetWindowWidth() * 0.5f, 300));
		for(int i = 0; i < 100; i++)
		{
		ImGui::Text("%04d: scrollable region", i);
		if(goto_line && line == i)
		ImGui::SetScrollPosHere();
		}
		if(goto_line && line >= 100)
		ImGui::SetScrollPosHere();
		ImGui::EndChild();
		ImGui::SameLine();
		ImGui::BeginChild("Sub2", ImVec2(0, 300), true);
		ImGui::Text("With border");
		ImGui::Columns(2);
		for(int i = 0; i < 100; i++)
		{
		char buf[32];
		ImFormatString(buf, IM_ARRAYSIZE(buf), "%08x", i * 5731);
		ImGui::Button(buf);
		ImGui::NextColumn();
		}
		ImGui::EndChild();
		}*/


	/*
	if(ImGui::CollapsingHeader("Filtering"))
	{
	static ImGuiTextFilter filter;
	ImGui::Text("Filter usage:\n"
	" \"\" display all lines\n"
	" \"xxx\" display lines containing \"xxx\"\n"
	" \"xxx,yyy\" display lines containing \"xxx\" or \"yyy\"\n"
	" \"-xxx\" hide lines containing \"xxx\"");
	filter.Draw();
	const char* lines[] = { "aaa1.c", "bbb1.c", "ccc1.c", "aaa2.cpp", "bbb2.cpp", "ccc2.cpp", "abc.h", "hello, world" };
	for(size_t i = 0; i < IM_ARRAYSIZE(lines); i++)
	if(filter.PassFilter(lines[i]))
	ImGui::BulletText("%s", lines[i]);
	}
	if(ImGui::CollapsingHeader("Keyboard & Focus"))
	{
	if(ImGui::TreeNode("Tabbing"))
	{
	ImGui::Text("Use TAB/SHIFT+TAB to cycle thru keyboard editable fields.");
	static char buf[32] = "dummy";
	ImGui::InputText("1", buf, IM_ARRAYSIZE(buf));
	ImGui::InputText("2", buf, IM_ARRAYSIZE(buf));
	ImGui::InputText("3", buf, IM_ARRAYSIZE(buf));
	ImGui::PushAllowKeyboardFocus(false);
	ImGui::InputText("4 (tab skip)", buf, IM_ARRAYSIZE(buf));
	//ImGui::SameLine(); ImGui::Text("(?)"); if (ImGui::IsHovered()) ImGui::SetTooltip("Use ImGui::PushAllowKeyboardFocus(bool)\nto disable tabbing through certain widgets.");
	ImGui::PopAllowKeyboardFocus();
	ImGui::InputText("5", buf, IM_ARRAYSIZE(buf));
	ImGui::TreePop();
	}
	if(ImGui::TreeNode("Focus from code"))
	{
	bool focus_1 = ImGui::Button("Focus on 1"); ImGui::SameLine();
	bool focus_2 = ImGui::Button("Focus on 2"); ImGui::SameLine();
	bool focus_3 = ImGui::Button("Focus on 3");
	int has_focus = 0;
	static char buf[128] = "click on a button to set focus";
	if(focus_1) ImGui::SetKeyboardFocusHere();
	ImGui::InputText("1", buf, IM_ARRAYSIZE(buf));
	if(ImGui::IsItemFocused()) has_focus = 1;
	if(focus_2) ImGui::SetKeyboardFocusHere();
	ImGui::InputText("2", buf, IM_ARRAYSIZE(buf));
	if(ImGui::IsItemFocused()) has_focus = 2;
	ImGui::PushAllowKeyboardFocus(false);
	if(focus_3) ImGui::SetKeyboardFocusHere();
	ImGui::InputText("3 (tab skip)", buf, IM_ARRAYSIZE(buf));
	if(ImGui::IsItemFocused()) has_focus = 3;
	ImGui::PopAllowKeyboardFocus();
	if(has_focus)
	ImGui::Text("Item with focus: %d", has_focus);
	else
	ImGui::Text("Item with focus: <none>");
	ImGui::TreePop();
	}
	}
	static bool show_app_console = false;
	static bool show_app_long_text = false;
	static bool show_app_auto_resize = false;
	static bool show_app_fixed_overlay = false;
	if(ImGui::CollapsingHeader("App Examples"))
	{
	ImGui::Checkbox("Console", &show_app_console);
	ImGui::Checkbox("Long text display", &show_app_long_text);
	ImGui::Checkbox("Auto-resizing window", &show_app_auto_resize);
	ImGui::Checkbox("Simple overlay", &show_app_fixed_overlay);
	}
	if(show_app_console)
	ShowExampleAppConsole(&show_app_console);
	if(show_app_long_text)
	ShowExampleAppLongText(&show_app_long_text);
	if(show_app_auto_resize)
	ShowExampleAppAutoResize(&show_app_auto_resize);
	if(show_app_fixed_overlay)
	ShowExampleAppFixedOverlay(&show_app_fixed_overlay);
	ImGui::End();*/

		return window;

	}
}
