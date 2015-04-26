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
	const char* girl_names[] =
	{
		"Maja", "Alice", "Julia", "Linnéa", "Wilma", "Ella", "Elsa", "Emma", "Alva", "Olivia", "Molly", "Ebba", "Klara", "Nellie", "Agnes",
		"Isabelle", "Ida", "Elin", "Ellen", "Moa", "Emilia", "Nova", "Alma", "Saga", "Amanda", "Isabella", "Lilly", "Alicia", "Astrid",
		"Matilda", "Tuva", "Tilde", "Stella", "Felicia", "Elvira", "Tyra", "Hanna", "Sara", "Vera", "Thea", "Freja", "Lova", "Selma",
		"Meja", "Signe", "Ester", "Lovisa", "Ellie", "Lea", "Tilda", "Tindra", "Sofia", "Nora", "Nathalie", "Leia", "Filippa", "Siri",
		"Emelie", "Inez", "Edith", "Stina", "Liv", "Lisa", "Linn", "Tove", "Emmy", "Livia", "Jasmine", "Evelina", "Cornelia", "Märta",
		"Svea", "Ingrid", "My", "Rebecca", "Joline", "Mira", "Ronja", "Hilda", "Melissa", "Anna", "Frida", "Maria", "Iris", "Josefine",
		"Elise", "Elina", "Greta", "Vilda", "Minna", "Lina", "Hedda", "Nicole", "Kajsa", "Majken", "Sofie", "Annie", "Juni", "Novalie", "Hedvig", 0
	};

	const char* boy_names[] =
	{
		"Oscar", "William", "Lucas", "Elias", "Alexander", "Hugo", "Oliver", "Theo", "Liam", "Leo", "Viktor", "Erik", "Emil",
		"Isak", "Axel", "Filip", "Anton", "Gustav", "Edvin", "Vincent", "Arvid", "Albin", "Ludvig", "Melvin", "Noah", "Charlie", "Max",
		"Elliot", "Viggo", "Alvin", "Alfred", "Theodor", "Adam", "Olle", "Wilmer", "Benjamin", "Simon", "Nils", "Noel", "Jacob", "Leon",
		"Rasmus", "Kevin", "Linus", "Casper", "Gabriel", "Jonathan", "Milo", "Melker", "Felix", "Love", "Ville", "Sebastian", "Sixten",
		"Carl", "Malte", "Neo", "David", "Joel", "Adrian", "Valter", "Josef", "Jack", "Hampus", "Samuel", "Mohammed", "Alex", "Tim",
		"Daniel", "Vilgot", "Wilhelm", "Harry", "Milton", "Maximilian", "Robin", "Sigge", "Måns", "Eddie", "Elton", "Vidar", "Hjalmar",
		"Loke", "Elis", "August", "John", "Hannes", "Sam", "Frank", "Svante", "Marcus", "Mio", "Otto", "Ali", "Johannes", "Fabian",
		"Ebbe", "Aron", "Julian", "Elvin", "Ivar", 0
	};

	Sheet& createUiTestCustomList(Sheet& parent)
	{
		Window& window = parent.emplace<Window>("Customized list items");
		Page& page = window.body().emplace<Page>("List and filter");
		SelectList& list = page.emplace<SelectList>();

		class CustomElement : public Sequence
		{
		public:
			CustomElement(const string& name)
				: Sequence()
				, mLabel(this->build(name))
			{
				mStyle = &cls();
			}

			Label& build(const string& name)
			{
				this->emplace<Checkbox>(nullptr, false);
				this->emplace<Icon>("tbb/icon48");
				Sheet& sheet = this->emplace<Sheet>();
				Label& label = sheet.emplace<Label>(name);
				sheet.emplace<Label>("Male");
				this->emplace<CloseButton>([this](Button&){ this->parent()->parent()->vrelease(*this); });
				return label;
			}

			const string& contentlabel() { return mLabel.label(); }

			static StyleType& cls() { static StyleType ty("CustomElement", Sequence::cls()); return ty; }

		protected:
			Label& mLabel;
		};

		CustomElement::cls().skin().mAlign = DimAlign(LEFT, CENTER);

		for(int i = 0; boy_names[i]; i++)
			list.emplace<CustomElement>(boy_names[i]);

		FilterInput& input = page.emplace<FilterInput>(list);

		window.frame().setSize(250.f, 300.f);
		return window;
	}

	Sheet& createUiTestFilteredList(Sheet& parent)
	{
		Window& window = parent.emplace<Window>("List and filter");
		Page& page = window.body().emplace<Page>("List and filter");
		SelectList& list = page.emplace<SelectList>();

		for(int i = 0; boy_names[i]; i++)
			list.emplace<Label>(boy_names[i]);
		for(int i = 0; girl_names[i]; i++)
			list.emplace<Label>(boy_names[i]);

		FilterInput& input = page.emplace<FilterInput>(list);

		window.frame().setSize(130.f, 300.f);
		return window;
	}

	Sheet& createUiTestScrollList(Sheet& parent)
	{
		Window& window = parent.emplace<Window>("Scroll List");
		Page& page = window.body().emplace<Page>("Scroll List");
		Sequence& sequence = page.emplace<Sequence>();

		List& list0 = sequence.emplace<List>();
		for(int i = 0; i < 100; i++)
			list0.emplace<Label>("Element " + toString(i));

		List& list1 = sequence.emplace<List>();
		for(int i = 0; i < 100; i++)
			list1.emplace<Button>("Element " + toString(i));

		window.frame().setSize(400.f, 600.f);
		return window;
	}

	Sheet& createUiTestTextEditor(Sheet& parent)
	{
		Window& window = parent.emplace<Window>("Text Editor");
		Page& page = window.body().emplace<Page>("Text Editor");
		Sequence& buttons = page.emplace<Sequence>();
		Menu& menu = buttons.emplace<Menu>("Menu");
		menu.emplace<Button>("Redo");
		menu.emplace<Button>("Undo");
		Menu& submenu = menu.emplace<Menu>("Set Font", true);
		submenu.emplace<Button>("Arial");
		submenu.emplace<Button>("Myriad");

		buttons.emplace<Button>("Open File");
		buttons.emplace<Button>("Undo");
		buttons.emplace<Button>("Redo");
		page.emplace<Textbox>("This is an example text editor field\n You can use it as any common editor");
		return window;
	}

	Sheet& createUiTestDockspace(Sheet& parent)
	{
		parent.clear();

		MasterDockline::cls().layout().d_weights = { 0.2f, 0.6f, 0.2f };

		Dockspace& dockspace = parent.emplace<Dockspace>();

		Page& dock0 = dockspace.emplace<Page>("Dock 0", "0.0");
		createUiTestControls(dock0);

		Page& dock1 = dockspace.emplace<Page>("Dock 1", "0.1");
		createUiTestInlineControls(dock1);

		Page& dock2 = dockspace.emplace<Page>("Dock 2", "0.2");
		createUiTestTable(dock2);

		return dockspace;
	}

	Sheet& createUiTestTabs(Sheet& parent)
	{
		parent.clear();

		Tabber& tabber = parent.emplace<Tabber>();

		Page& tab0 = tabber.emplace<Page>("Tab 0");
		createUiTestTable(tab0);

		Page& tab1 = tabber.emplace<Page>("Tab 1");
		createUiTestInlineControls(tab1);

		Page& tab2 = tabber.emplace<Page>("Tab 2");
		createUiTestControls(tab2);

		return tabber;
	}

	Sheet& createUiTestTable(Sheet& parent)
	{
		Table& table = parent.emplace<Table>(StringVector({ "ID", "Name", "Path", "Flags" }), std::vector<float>({ 0.25f, 0.25f, 0.25f, 0.25f }));

		table.emplace<LabelSequence>(StringVector({ "0000", "Robert", "/path/robert", "...." }));
		table.emplace<LabelSequence>(StringVector({ "0001", "Stephanie", "/path/stephanie", "line 1" }));
		table.emplace<LabelSequence>(StringVector({ "0002", "C64", "/path/computer", "...." }));

		return table;
	}

	Sheet& createUiTestTableAlt(Sheet& parent)
	{
		Table& table0 = parent.emplace<Table>(StringVector({ "Column 0", "Column 1", "Column 3" }), std::vector<float>({ 0.33f, 0.33f, 0.33f }));

		table0.emplace<LabelSequence>(StringVector({ "Hello", "kiUi", "World!" }));
		table0.emplace<ButtonSequence>(StringVector({ "Banana", "Apple", "Corniflower" }));
		table0.emplace<RadioSwitch>(nullptr, 0, StringVector({ "radio a", "radio b", "radio b" }));

		Sequence& line0 = table0.emplace<Sequence>();

		Expandbox& box0 = line0.emplace<Expandbox>("Category A");
		box0.emplace<Label>("Blah blah blah");
		
		Expandbox& box1 = line0.emplace<Expandbox>("Category B");
		box1.emplace<Label>("Blah blah blah");

		Expandbox& box2 = line0.emplace<Expandbox>("Category C");
		box2.emplace<Label>("Blah blah blah");


		Table& table1 = parent.emplace<Table>(StringVector({ "Left", "Right" }), std::vector<float>({ 0.5f, 0.5f }));

		Sequence& line1 = table1.emplace<Sequence>();

		line1.emplace<InputFloat>("Red", 0.05f);
		line1.emplace<InputFloat>("Blue", 0.05f);

		Sequence& line2 = table1.emplace<Sequence>();

		line2.emplace<Textbox>("The quick brown fox jumps over the lazy dog.");
		line2.emplace<Textbox>("The quick brown fox jumps over the lazy dog.");

		Sequence& line3 = table1.emplace<Sequence>();

		line3.emplace<Label>("Hello Left");
		line3.emplace<Label>("Hello Right");

		return table0;
	}

	Sheet& createUiTestTree(Sheet& parent)
	{
		Window& window = parent.emplace<Window>("Tree");
		Page& page = window.body().emplace<Page>("Tree");

		Tree& tree = page.emplace<Tree>();

		TreeNode& node = tree.emplace<TreeNode>("", "Tree");

		for(size_t i = 0; i < 5; i++)
		{
			TreeNode& innernode = node.emplace<TreeNode>("", "Child " + toString(i), true);
			TreeNode* innestnode = &innernode;
			for(size_t j = 0; j < 5; j++)
			{
				innestnode = &innestnode->emplace<TreeNode>("", "Child " + toString(i) + " : " + toString(j), true);
			}
		}

		for(size_t i = 0; i < 5; i++)
		{
			TreeNode& innernode = node.emplace<TreeNode>("", "Child " + toString(5+i));

			innernode.emplace<Label>("Blah blah");
			innernode.emplace<Button>("Print");
		}

		window.frame().setSize(300.f, 500.f);
		return window;
	}

	Tree& createUiTestTableTree(Sheet& parent)
	{
		Tree& tree = parent.emplace<Tree>();

		TreeNode& node0 = tree.emplace<TreeNode>("", "Inside a tree...");

		TreeNode& node1 = node0.emplace<TreeNode>("", "node 1 (with borders)");

		TreeNode& tablenode0 = node1.emplace<TreeNode>("", "Table Node 0");
		
		tablenode0.emplace<Label>("aaa");
		tablenode0.emplace<Label>("bbb");
		tablenode0.emplace<Label>("ccc");
		tablenode0.emplace<Label>("ddd");

		TreeNode& tablenode1 = node1.emplace<TreeNode>("", "Table Node 1");

		tablenode1.emplace<Label>("eee");
		tablenode1.emplace<Label>("fff");
		tablenode1.emplace<Label>("ggg");
		tablenode1.emplace<Label>("hhh");

		return tree;
	}

	Textbox* createUiTestMarkupText(Sheet& parent)
	{
		parent.emplace<Textbox>("This is a long paragraph. The text should automatically wrap on the edge of the window. The current implementation follows simple rules that works for English and possibly other languages.");
		parent.emplace<SliderFloat>("Wrap width", AutoStat<float>(200.f, -20.f, 600.f, 0.1f), [](float width){ });
		
		/*ImGui::Text("Test paragraph 1:");
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
		ImGui::TreePop();*/

		return nullptr;

		/*if(ImGui::TreeNode("Colored Text"))
		{
			// Using shortcut. You can use PushStyleColor()/PopStyleColor() for more flexibility.
			ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Pink");
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Yellow");
			ImGui::TreePop();
		}*/
	}

	Sheet& createUiTestControls(Sheet& parent)
	{
		Table& table = parent.emplace<Table>(StringVector({ "input", "label" }), std::vector<float>({ 0.7f, 0.3f }));

		table.emplace<InputDropdown>("dropdown input", StringVector({ "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK" }), [](string val) {});
		table.emplace<InputDropdown>("dropdown input", StringVector({ "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK" }), [](string val) {}, true);

		table.emplace<InputText>("string input", "Hello, world!");
		table.emplace<InputInt>("int input", 123);
		table.emplace<InputFloat>("float input", 0.001f);

		table.emplace<SliderInt>("int 0..3", AutoStat<int>(2, 0, 3, 1));
		table.emplace<SliderInt>("int -100..100", AutoStat<int>(0, -100, 100, 1));

		table.emplace<SliderFloat>("float input", AutoStat<float>(1.123f, 0.0f, 2.0f, 0.001f));
		table.emplace<SliderFloat>("log float", AutoStat<float>(0.f, 0.0f, 10.0f, 1.f));
		//table.emplace<SliderFloat>("signed log float", AutoStat<float>(0.f, -10.0f, 10.0f, 1.f));
		//table.emplace<SliderFloat>("unbound float", AutoStat<float>(123456789.0f, -FLT_MAX, FLT_MAX, 1.f));

		// table.emplace<SliderAngle>("angle", 0.f);
		// table.emplace<FVector3>("slider float3", 0.0f, 1.0f);

		// ImGui::ColorEdit3("color 1", col1);
		// ImGui::ColorEdit4("color 2", col2);

		return table;
	}

	Sheet& createUiTestFileBrowser(Sheet& parent)
	{
		Window& window = parent.emplace<Window>("File Browser");
		window.body().emplace<Directory>("..");
		return window;
	}

	Sheet& createUiTestFileTree(Sheet& parent)
	{
		Window& window = parent.emplace<Window>("File Tree");
		Tree& filetree = window.body().emplace<Tree>();
		DirectoryNode& node = filetree.emplace<DirectoryNode>("..", "..", false);
		node.update();
		return window;
	}

	Sheet& createUiTestInlineControls(Sheet& parent)
	{
		Page& page = parent.emplace<Page>("Inline Controls");

		Sequence& line0 = page.emplace<Sequence>();

		line0.emplace<Label>("Hello");
		line0.emplace<Label>("World");

		Sequence& line1 = page.emplace<Sequence>();

		line1.emplace<Button>("Banana");
		line1.emplace<Button>("Apple");
		line1.emplace<Button>("Corniflower");

		Sequence& line2 = page.emplace<Sequence>();

		line2.emplace<Label>("Small buttons");
		line2.emplace<Button>("Like this one");
		line2.emplace<Label>("can fit within a text block.");

		Sequence& line3 = page.emplace<Sequence>();

		line3.emplace<InputBool>("My", true);
		line3.emplace<InputBool>("Tailor", true);
		line3.emplace<InputBool>("Is", true);
		line3.emplace<InputBool>("Rich", true);

		Sequence& line4 = page.emplace<Sequence>();

		line4.emplace<InputFloat>("X", 0.f);
		line4.emplace<InputFloat>("Y", 0.f);
		line4.emplace<InputFloat>("Z", 0.f);

		return page;
	}

	Sheet& createUiTestProgressDialog(Sheet& parent)
	{
		Window& window = parent.emplace<Window>("Progress Dialog");
		Page& page = window.body().emplace<Page>("Progress Dialog");
		ProgressBar& bar = page.emplace<ProgressBarX>();
		bar.setPercentage(0.57f);
		page.emplace<SliderFloat>("Set progress", AutoStat<float>(0.57f, 0.f, 1.f, 0.01f), [&bar](float val) { bar.setPercentage(val); });
		return window;
	}

	Window& createUiTestWindow(Sheet& parent)
	{
		Window& window = parent.emplace<Window>("kiUi v0.1");
		Page& page = window.body().emplace<Page>("kiUi v0.1");

		page.emplace<Label>("kiui says hello.");

		Expandbox& box0 = page.emplace<Expandbox>("Help");
		box0.emplace<Textbox>("This window is being created by the ShowTestWindow() function. Please refer to the code for programming reference.\n\nUser Guide:");

		Expandbox& box1 = page.emplace<Expandbox>("Window options");

		box1.emplace<InputBool>("titlebar", true, [&window](bool on) { on ? window.showTitlebar() : window.hideTitlebar(); });
		box1.emplace<InputBool>("movable", true, [&window](bool) { window.toggleMovable(); });
		box1.emplace<InputBool>("resizable", true, [&window](bool) { window.toggleResizable(); });
		box1.emplace<InputBool>("closable", true, [&window](bool) { window.toggleClosable(); });

		box1.emplace<SliderFloat>("fill alpha", AutoStat<float>(0.f, 0.f, 1.f, 0.1f), [&window](float alpha){ window.frame().inkstyle().mBackgroundColour.val.setA(alpha); });

		Expandbox& box2 = page.emplace<Expandbox>("Widgets");
		createUiTestControls(box2);

		Expandbox& box3 = page.emplace<Expandbox>("Table");
		createUiTestTable(box3);

		Expandbox& box4 = page.emplace<Expandbox>("Columns");
		createUiTestTableAlt(box4);

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

	void switchUiTheme(Sheet& sheet, Widget& selected)
	{
		const string name = selected.label();
		mk::StyleParser parser(sheet.uiWindow().styler());

		if(name == "Blendish")
			parser.loadStyleSheet(sheet.uiWindow().resourcePath() + "interface/styles/blendish.yml");
		else if(name == "Blendish Dark")
			parser.loadStyleSheet(sheet.uiWindow().resourcePath() + "interface/styles/blendish_dark.yml");
		else if(name == "TurboBadger")
			parser.loadStyleSheet(sheet.uiWindow().resourcePath() + "interface/styles/turbobadger.yml");
		else if(name == "MyGui")
			parser.loadStyleSheet(sheet.uiWindow().resourcePath() + "interface/styles/mygui.yml");
		else if(name == "Photoshop")
			parser.loadStyleSheet(sheet.uiWindow().resourcePath() + "interface/styles/photoshop.yml");
		else if(name == "Default")
			parser.loadDefaultStyle();
	}

	void pickUiSample(Sheet& sheet, Widget& selected)
	{
		const string name = selected.label();
		
		if(sheet.stripe().sequence().size() > 0)
			sheet.clear();

		if(name == "Dockspace")
			createUiTestDockspace(sheet);
		else if(name == "Window")
			createUiTestWindow(sheet);
		else if(name == "Filtered List")
			createUiTestFilteredList(sheet);
		else if(name == "Custom List")
			createUiTestCustomList(sheet);
		else if(name == "Text Editor")
			createUiTestTextEditor(sheet);
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

	void createUiTest(Form& root)
	{
		Header& demoheader = root.sheet().emplace<Header>();
		Board& demobody = root.sheet().emplace<Board>();
		demoheader.emplace<Label>("Pick a demo sample : ");
		demoheader.emplace<Dropdown>(std::bind(&pickUiSample, std::ref(demobody), std::placeholders::_1), StringVector({ "Dockspace", "Window", "Text Editor", "Filtered List", "Custom List", "Tabs", "Table", "Tree", "Controls", "File Browser", "File Tree", "Progress Dialog" }));
		demoheader.emplace<Label>("Switch theme : ");
		demoheader.emplace<Dropdown>(std::bind(&switchUiTheme, std::ref(demobody), std::placeholders::_1), StringVector({ "Blendish", "Blendish Dark", "TurboBadger", "MyGui", "Photoshop", "Default" }));
	}
}
