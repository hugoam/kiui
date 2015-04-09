//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/mkUiTypes.h>

#include <Ui/mkUi.h>

#include <Ui/Nano/mkGlWindow.h>

#include <cfloat>

namespace mk
{
	Dockspace* createUiTestDockspace(Sheet* root)
	{
		MasterDockline::styleCls()->layout()->d_weights = { 0.2f, 0.6f, 0.2f };

		Dockspace* dockspace = root->emplace<Dockspace>();

		Page* dock0 = dockspace->emplace<Page>("Dock 0", "0.0");
		createUiTestControls(dock0);

		Page* dock1 = dockspace->emplace<Page>("Dock 1", "0.1");
		createUiTestInlineControls(dock1);

		Page* dock2 = dockspace->emplace<Page>("Dock 2", "0.2");
		createUiTestTable(dock2);

		return dockspace;
	}

	Tabber* createUiTestTabs(Sheet* root)
	{
		Tabber* tabber = root->emplace<Tabber>();

		Page* tab0 = tabber->emplace<Page>("Tab 0");
		createUiTestTable(tab0);

		Page* tab1 = tabber->emplace<Page>("Tab 1");
		createUiTestInlineControls(tab1);

		Page* tab2 = tabber->emplace<Page>("Tab 2");
		createUiTestControls(tab2);

		return tabber;
	}

	Table* createUiTestTable(Sheet* parent)
	{
		Table* table = parent->emplace<Table>(StringVector({ "ID", "Name", "Path", "Flags" }), std::vector<float>({ 0.25f, 0.25f, 0.25f, 0.25f }));

		table->emplace<LabelSequence>(StringVector({ "0000", "Robert", "/path/robert", "...." }));
		table->emplace<LabelSequence>(StringVector({ "0001", "Stephanie", "/path/stephanie", "line 1" }));
		table->emplace<LabelSequence>(StringVector({ "0002", "C64", "/path/computer", "...." }));

		return table;
	}

	Table* createUiTestTableAlt(Sheet* parent)
	{
		Table* table = parent->emplace<Table>(StringVector({ "Column 0", "Column 1", "Column 3" }), std::vector<float>({ 0.33f, 0.33f, 0.33f }));

		table->emplace<LabelSequence>(StringVector({ "Hello", "kiUi", "World!" }));
		table->emplace<ButtonSequence>(StringVector({ "Banana", "Apple", "Corniflower" }));
		table->emplace<RadioSwitch>(nullptr, 0, StringVector({ "radio a", "radio b", "radio b" }));

		Sequence* line = table->emplace<Sequence>();

		Expandbox* box0 = line->emplace<Expandbox>("Category A");
		box0->emplace<Label>("Blah blah blah");
		
		Expandbox* box1 = line->emplace<Expandbox>("Category B");
		box1->emplace<Label>("Blah blah blah");

		Expandbox* box2 = line->emplace<Expandbox>("Category C");
		box2->emplace<Label>("Blah blah blah");


		table = parent->emplace<Table>(StringVector({ "Left", "Right" }), std::vector<float>({ 0.5f, 0.5f }));

		line = table->emplace<Sequence>();

		line->emplace<InputFloat>("Red", 0.05f);
		line->emplace<InputFloat>("Blue", 0.05f);

		line = table->emplace<Sequence>();

		line->emplace<Textbox>("The quick brown fox jumps over the lazy dog.");
		line->emplace<Textbox>("The quick brown fox jumps over the lazy dog.");

		line = table->emplace<Sequence>();

		line->emplace<Label>("Hello Left");
		line->emplace<Label>("Hello Right");

		return table;
	}

	Tree* createUiTestTree(Sheet* parent)
	{
		Tree* tree = parent->emplace<Tree>();

		TreeNode* node = tree->emplace<TreeNode>("", "Tree");

		for(size_t i = 0; i < 5; i++)
		{
			TreeNode* innernode = node->emplace<TreeNode>("", "Child " + toString(i), true);
			TreeNode* innestnode = innernode;
			for(size_t j = 0; j < 5; j++)
			{
				innestnode = innestnode->emplace<TreeNode>("", "Child " + toString(i) + " : " + toString(j), true);
			}
		}

		for(size_t i = 0; i < 5; i++)
		{
			TreeNode* innernode = node->emplace<TreeNode>("", "Child " + toString(5+i));

			innernode->emplace<Label>("Blah blah");
			innernode->emplace<Button>("Print");
		}

		return tree;
	}

	Tree* createUiTestTableTree(Sheet* parent)
	{
		Tree* tree = parent->emplace<Tree>();

		TreeNode* node = tree->emplace<TreeNode>("", "Inside a tree...");

		node = node->emplace<TreeNode>("", "node 1 (with borders)");

		TreeNode* tablenode = node->emplace<TreeNode>("", "Table Node 0");
		
		tablenode->emplace<Label>("aaa");
		tablenode->emplace<Label>("bbb");
		tablenode->emplace<Label>("ccc");
		tablenode->emplace<Label>("ddd");

		tablenode = node->emplace<TreeNode>("", "Table Node 1");

		tablenode->emplace<Label>("eee");
		tablenode->emplace<Label>("fff");
		tablenode->emplace<Label>("ggg");
		tablenode->emplace<Label>("hhh");

		return tree;
	}

	Textbox* createUiTestMarkupText(Sheet* parent)
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

	Sheet* createUiTestControls(Sheet* parent)
	{
		Table* table = parent->emplace<Table>(StringVector({ "input", "label" }), std::vector<float>({ 0.7f, 0.3f }));

		table->emplace<InputDropdown>("dropdown input", StringVector({ "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK" }), [](string val) {});

		table->emplace<InputText>("string input", "Hello, world!");
		table->emplace<InputInt>("int input", 123);
		table->emplace<InputFloat>("float input", 0.001f);

		table->emplace<SliderInt>("int 0..3", AutoStat<int>(2, 0, 3, 1));
		table->emplace<SliderInt>("int -100..100", AutoStat<int>(0, -100, 100, 1));

		table->emplace<SliderFloat>("float input", AutoStat<float>(1.123f, 0.0f, 2.0f, 0.001f));
		table->emplace<SliderFloat>("log float", AutoStat<float>(0.f, 0.0f, 10.0f, 1.f));
		//table->emplace<SliderFloat>("signed log float", AutoStat<float>(0.f, -10.0f, 10.0f, 1.f));
		//table->emplace<SliderFloat>("unbound float", AutoStat<float>(123456789.0f, -FLT_MAX, FLT_MAX, 1.f));

		// table->emplace<SliderAngle>("angle", 0.f);
		// table->emplace<FVector3>("slider float3", 0.0f, 1.0f);

		// ImGui::ColorEdit3("color 1", col1);
		// ImGui::ColorEdit4("color 2", col2);

		return table;
	}

	Sheet* createUiTestFileBrowser(Sheet* parent)
	{
		Window* window = parent->emplace<Window>("File Browser");
		Sheet* filebrowser = window->body()->emplace<Directory>("..");
		return window;
	}

	Sheet* createUiTestFileTree(Sheet* parent)
	{
		Window* window = parent->emplace<Window>("File Tree");
		Tree* filetree = window->body()->emplace<Tree>();
		DirectoryNode* node = filetree->emplace<DirectoryNode>("..", "..", false);
		node->update();
		return window;
	}

	Sheet* createUiTestInlineControls(Sheet* parent)
	{
		//Sheet* page = parent;
		Page* page = parent->emplace<Page>("Inline Controls");
		// @bug 280X : page inside page doesn't work @todo

		DivX* line;
		
		line = page->emplace<DivX>();

		line->emplace<Label>("Hello");
		line->emplace<Label>("World");

		line = page->emplace<DivX>();

		line->emplace<Button>("Banana");
		line->emplace<Button>("Apple");
		line->emplace<Button>("Corniflower");

		line = page->emplace<DivX>();

		line->emplace<Label>("Small buttons");
		line->emplace<Button>("Like this one");
		line->emplace<Label>("can fit within a text block.");

		line = page->emplace<DivX>();

		line->emplace<InputBool>("My", true);
		line->emplace<InputBool>("Tailor", true);
		line->emplace<InputBool>("Is", true);
		line->emplace<InputBool>("Rich", true);

		line = page->emplace<DivX>();

		line->emplace<InputFloat>("X", 0.f);
		line->emplace<InputFloat>("Y", 0.f);
		line->emplace<InputFloat>("Z", 0.f);

		return page;
	}

	Sheet* createUiTestProgressDialog(Sheet* parent)
	{
		Window* window = parent->emplace<Window>("Progress Dialog");
		Page* page = window->body()->emplace<Page>("Progress Dialog");
		ProgressBar* bar = page->emplace<ProgressBarX>();
		bar->setPercentage(0.57f);
		page->emplace<SliderFloat>("Set progress", AutoStat<float>(0.57f, 0.f, 1.f, 0.01f), [bar](float val) { bar->setPercentage(val); });
		return window;
	}

	Window* createUiTestWindow(Sheet* parent)
	{
		Window* window = parent->emplace<Window>("kiUi v0.1");
		Page* page = window->body()->emplace<Page>("kiUi v0.1");

		page->emplace<Label>("kiui says hello.");

		Expandbox* box;

		box = page->emplace<Expandbox>("Help");
		//current->emplace<Textbox>("This window is being created by the ShowTestWindow() function. Please refer to the code for programming reference.\n\nUser Guide:");

		box = page->emplace<Expandbox>("Window options");

		box->emplace<InputBool>("titlebar", true, [window](bool on) { on ? window->showTitlebar() : window->hideTitlebar(); });
		box->emplace<InputBool>("movable", true, [window](bool) { window->toggleMovable(); });
		box->emplace<InputBool>("resizable", true, [window](bool) { window->toggleResizable(); });
		box->emplace<InputBool>("closable", true, [window](bool) { window->toggleClosable(); });

		box->emplace<SliderFloat>("fill alpha", AutoStat<float>(0.f, 0.f, 1.f, 0.1f), [window](float alpha){ window->frame()->inkstyle()->mBackgroundColour.setA(alpha); });

		box = page->emplace<Expandbox>("Widgets");
		createUiTestControls(box);

		box = page->emplace<Expandbox>("Table");
		createUiTestTable(box);

		box = page->emplace<Expandbox>("Columns");
		createUiTestTableAlt(box);

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

	void switchTheme(Sheet* sheet, Widget* selected)
	{
		const string name = selected->label();
		mk::StyleParser parser(sheet->uiWindow()->styler());

		if(name == "Blendish")
			parser.loadStyleSheet("../Data/interface/styles/blendish.yml");
		else if(name == "Blendish Dark")
			parser.loadStyleSheet("../Data/interface/styles/blendish_dark.yml");
		else if(name == "MyGui")
			parser.loadStyleSheet("../Data/interface/styles/mygui.yml");
		else if(name == "Default")
			parser.loadDefaultStyle();
	}

	void pickSample(Sheet* sheet, Widget* selected)
	{
		const string name = selected->label();
		sheet->clear();

		if(name == "Dockspace")
			createUiTestDockspace(sheet);
		else if(name == "Window")
			createUiTestWindow(sheet);
		else if(name == "Tabs")
			createUiTestTabs(sheet);
		else if(name == "Table")
			createUiTestTable(sheet);
		else if(name == "Tree")
			createUiTestTree(sheet);
		else if(name == "Controls")
			createUiTestControls(sheet);
		else if(name == "File Browser")
			createUiTestFileBrowser(sheet);
		else if(name == "File Tree")
			createUiTestFileTree(sheet);
		else if(name == "Progress Dialog")
			createUiTestProgressDialog(sheet);
	}

	void createUiTest(Form* root)
	{
		Header* demoheader = root->sheet()->emplace<Header>();
		PartitionX* demobody = root->sheet()->emplace<PartitionX>();
		demoheader->emplace<Label>("Pick a demo sample : ");
		demoheader->emplace<Dropdown>(std::bind(&pickSample, demobody, std::placeholders::_1), StringVector({ "Dockspace", "Window", "Tabs", "Table", "Tree", "Controls", "File Browser", "File Tree", "Progress Dialog" }));
		demoheader->emplace<Label>("Switch theme : ");
		Dropdown* dropdown = demoheader->emplace<Dropdown>(std::bind(&switchTheme, demobody, std::placeholders::_1), StringVector({ "Blendish", "Blendish Dark", "MyGui", "Default" }));
		dropdown->frame()->setSpanDim(DIM_X, 0.3f);
	}
}
