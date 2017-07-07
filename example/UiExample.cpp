 
#include <UiExampleConfig.h>
#include <UiExample.h>

#include <toyui/Bundle.h>

#include <cfloat>

using namespace std::placeholders;

namespace toy
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

	class CustomElement : public Wedge
	{
	public:
		CustomElement(Wedge& parent, const string& name, const string& gender)
			: Wedge(parent, cls())
			, checkbox(*this, nullptr, false)
			, icon(*this, "(tbb/icon48)")
			, stack(*this, Wedge::Stack())
			, name(stack, name)
			, gender(stack, gender)
			, close(*this, "", [this](Widget&) { this->extract(); }, Window::CloseButton())
		{}

		Checkbox checkbox;
		Item icon;
		Wedge stack;
		Label name;
		Label gender;
		Button close;

		static Type& cls() { static Type ty("CustomElement", Wedge::Row()); return ty; }
	};

	Wedge& createUiTestCustomList(Wedge& parent)
	{
		SelectList& list = parent.emplace<SelectList>();

		for(int i = 0; boy_names[i]; i++)
			list.body().emplace<CustomElement>(boy_names[i], "Male");
		for(int i = 0; girl_names[i]; i++)
			list.body().emplace<CustomElement>(girl_names[i], "Female");

		parent.emplace<FilterInput>(list.body(), [](Widget& widget) { return widget.as<CustomElement>().name.label(); });
		return parent;
	}

	Wedge& createUiTestFilteredList(Wedge& parent)
	{
		SelectList& list = parent.emplace<SelectList>();

		for(int i = 0; boy_names[i]; i++)
			list.body().emplace<Label>(boy_names[i]);
		for(int i = 0; girl_names[i]; i++)
			list.body().emplace<Label>(girl_names[i]);

		parent.emplace<FilterInput>(list.body());
		return parent;
	}

	Wedge& createUiTestScrollList(Wedge& parent)
	{
		Wedge& sequence = parent.emplace<Wedge>(Wedge::Layout());

		ScrollSheet& list0 = sequence.emplace<ScrollSheet>();
		for(int i = 0; i < 100; i++)
			list0.body().emplace<Label>("Element " + toString(i));

		ScrollSheet& list1 = sequence.emplace<ScrollSheet>();
		for(int i = 0; i < 100; i++)
			list1.body().emplace<Button>("Element " + toString(i));
		return parent;
	}

	Wedge& createUiTestTextEditor(Wedge& parent)
	{
		Wedge& buttons = parent.emplace<Menubar>();
		Menu& menu = buttons.emplace<Menu>("Menu");
		menu.addChoice({ "Redo" });
		menu.addChoice({ "Undo" });
		Menu& submenu = menu.addChoice({}).emplace<Menu>("Change Font", true);
		submenu.addChoice({ "Arial" });
		submenu.addChoice({ "Myriad" });

		buttons.emplace<Button>("Open File");
		buttons.emplace<Button>("Undo");
		buttons.emplace<Button>("Redo");

		static string text = "This is an example text editor field\n You can use it as any common editor";
		parent.emplace<Textbox>(text);

		return parent;
	}

	Wedge& createUiTestApplication(Wedge& parent)
	{
		Wedge& menubar = parent.emplace<Menubar>();

		Menu& menufile = menubar.emplace<Menu>("File");
		menufile.addChoice({ "Open" });
		menufile.addChoice({ "Save" });
		Menu& menusave = menufile.addChoice({}).emplace<Menu>("Save As", true);
		menufile.addChoice({ "Close" });

		menusave.addChoice({ "Save As JPEG" });
		menusave.addChoice({ "Save As PNG" });
		menusave.addChoice({ "Save As PDF" });

		Menu& menuedit = menubar.emplace<Menu>("Edit");
		menuedit.addChoice({ "Redo" });
		menuedit.addChoice({ "Undo" });

		Menu& menuhelp = menubar.emplace<Menu>("Help");
		menuhelp.addChoice({ "About kiUi" });

		Tooldock& tooldock = parent.emplace<Tooldock>();

		Toolbar& toolbar0 = tooldock.emplace<Toolbar>();
		toolbar0.emplace<ToolButton>("(arrow_left_15)");
		toolbar0.emplace<ToolButton>("(arrow_right_15)");

		Toolbar& toolbar1 = tooldock.emplace<Toolbar>();
		toolbar1.emplace<ToolButton>("(file_15)");
		toolbar1.emplace<ToolButton>("(folder_15)");
		toolbar1.emplace<ToolButton>("(close_15)");

		return tooldock;
	}

	Wedge& createUiTestDockspace(Wedge& parent)
	{
		//MasterDockline::cls().layout().d_weights = { 0.2f, 0.6f, 0.2f };

		Dockspace& dockspace = parent.emplace<Dockspace>();

		Wedge& dock0 = dockspace.addDockWindow("Dock 0", { 0, 0 }).body();
		createUiTestControls(dock0);
		
		Wedge& dock1 = dockspace.addDockWindow("Dock 1", { 0, 1 }).body();
		createUiTestInlineControls(dock1);

		Wedge& dock2 = dockspace.addDockWindow("Dock 2", { 0, 2 }).body();
		createUiTestTable(dock2);

		return dockspace;
	}

	Wedge& createUiTestNodes(Wedge& parent)
	{
		Canvas& canvas = parent.emplace<Canvas>("Node Editor");

		Toolbar& toolbar = parent.emplace<Toolbar>();
		toolbar.emplace<ToolButton>("autolayout", [&canvas](Widget&) { canvas.autoLayout(); });
		toolbar.emplace<ToolButton>("autolayout selected", [&canvas](Widget&) { canvas.autoLayoutSelected(); });

		parent.swap(canvas.index(), toolbar.index());

		Node& node0 = canvas.plan().emplace<Node>("A Node");
		node0.addInput("a", "", Colour::Cyan);
		node0.addInput("b", "", Colour::Cyan);
		node0.addOutput("result");
		node0.frame().setPosition({ 150.f, 250.f });

		Node& node1 = canvas.plan().emplace<Node>("A Node");
		node1.addInput("a");
		node1.addInput("b");
		node1.addOutput("result", "", Colour::Red);
		node1.frame().setPosition({ 350.f, 150.f });

		Node& node2 = canvas.plan().emplace<Node>("Another Node");
		node2.addInput("u", "", Colour::Pink);
		node2.addInput("v", "", Colour::Pink);
		node2.addOutput("x", "", Colour::Cyan);
		node2.addOutput("y", "", Colour::Cyan);
		node2.addOutput("z", "", Colour::Cyan);
		node2.frame().setPosition({ 450.f, 450.f });

		Node& node3 = canvas.plan().emplace<Node>("End Node");
		node3.addInput("input 1");
		node3.addInput("input 2");
		node3.frame().setPosition({ 800.f, 200.f });

		return parent;
	}

	Wedge& createUiTestTabs(Wedge& parent)
	{
		Tabber& tabber = parent.emplace<Tabber>();
		
		Tab& tab0 = tabber.addTab("Tab 0");
		createUiTestTable(tab0);

		Tab& tab1 = tabber.addTab("Tab 1");
		createUiTestInlineControls(tab1);

		Tab& tab2 = tabber.addTab("Tab 2");
		createUiTestControls(tab2);

		return parent;
	}

	Wedge& createUiTestTable(Wedge& parent)
	{
		Table& table0 = parent.emplace<Table>(StringVector({ "ID", "Name", "Path", "Flags" }), std::vector<float>({ 0.25f, 0.25f, 0.25f, 0.25f }));

		table0.emplace<LabelSequence>(StringVector({ "0000", "Robert", "/path/robert", "...." }));
		table0.emplace<LabelSequence>(StringVector({ "0001", "Stephanie", "/path/stephanie", "line 1" }));
		table0.emplace<LabelSequence>(StringVector({ "0002", "C64", "/path/computer", "...." }));

		Table& table1 = parent.emplace<Table>(StringVector({ "Column 0", "Column 1", "Column 3" }), std::vector<float>({ 0.33f, 0.33f, 0.33f }));

		table1.emplace<LabelSequence>(StringVector({ "Hello", "kiUi", "World!" }));
		table1.emplace<ButtonSequence>(StringVector({ "Banana", "Apple", "Corniflower" }));
		table1.emplace<RadioSwitch>(StringVector({ "radio a", "radio b", "radio b" }));

		Wedge& line0 = table1.emplace<Wedge>(Wedge::Row());

		Expandbox& box0 = line0.emplace<Expandbox>("Category A");
		box0.body().emplace<Label>("Blah blah blah");

		Expandbox& box1 = line0.emplace<Expandbox>("Category B");
		box1.body().emplace<Label>("Blah blah blah");

		Expandbox& box2 = line0.emplace<Expandbox>("Category C");
		box2.body().emplace<Label>("Blah blah blah");


		Table& table2 = parent.emplace<Table>(StringVector({ "Left", "Right" }), std::vector<float>({ 0.5f, 0.5f }));

		Wedge& line1 = table2.emplace<Wedge>(Wedge::Row());

		line1.emplace<InputFloat>("Red", 0.05f);
		line1.emplace<InputFloat>("Blue", 0.05f);

		Wedge& line2 = table2.emplace<Wedge>(Wedge::Row());

		static string text1 = "The quick brown fox jumps over the lazy dog.";
		static string text2 = "The quick brown fox jumps over the lazy dog.";

		line2.emplace<TypeIn>(text1);
		line2.emplace<TypeIn>(text2);

		Wedge& line3 = table2.emplace<Wedge>(Wedge::Row());

		line3.emplace<Label>("Hello Left");
		line3.emplace<Label>("Hello Right");

		return parent;
	}

	Wedge& createUiTestTree(Wedge& parent)
	{
		Tree& tree = parent.emplace<Tree>();
		TreeNode& node = tree.emplace<TreeNode>("", "Tree");

		for(size_t i = 0; i < 5; i++)
		{
			TreeNode& innerNode = node.body().emplace<TreeNode>("", "Child " + toString(i), true);
			TreeNode* nestedNode = &innerNode;
			for(size_t j = 0; j < 5; j++)
				nestedNode = &nestedNode->body().emplace<TreeNode>("", "Child " + toString(i) + " : " + toString(j), true);
		}

		for(size_t i = 0; i < 5; i++)
		{
			TreeNode& innerNode = node.body().emplace<TreeNode>("", "Child " + toString(5 + i));
			innerNode.body().emplace<Label>("Blah blah");
			innerNode.body().emplace<Button>("Print");
		}
		return parent;
	}

	Tree& createUiTestTableTree(Wedge& parent)
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

	Wedge& createUiTestMarkupText(Wedge& parent)
	{
		static string multiline = "This is a long paragraph. The text should automatically wrap on the edge of the window. The current implementation follows no word splitting rules, text is just split at the last character.";
		parent.emplace<Textbox>(multiline);
		parent.emplace<SliderFloat>("Wrap width", AutoStat<float>(200.f, -20.f, 600.f, 0.1f), [](float) {});
		
		Wedge& line0 = parent.emplace<Wedge>(Wedge::Row());
		line0.emplace<Item>("(bullet)");
		line0.emplace<Label>("Bullet point 1");

		static string multiline2 = "Bullet point 2\nOn multiple lines";
		Wedge& line1 = parent.emplace<Wedge>(Wedge::Row());
		line1.emplace<Item>("(bullet)");
		line1.emplace<Textbox>(multiline2);

		Wedge& line2 = parent.emplace<Wedge>(Wedge::Row());
		line2.emplace<Item>("(bullet)");
		line2.emplace<Label>("Bullet point 3");

		return parent;
	}

	Wedge& createUiTestControls(Wedge& parent)
	{
		Table& table = parent.emplace<Table>(StringVector({ "input", "label" }), std::vector<float>({ 0.7f, 0.3f }));

		table.emplace<InputBool>("checkbox input", false, nullptr, true);
		table.emplace<InputRadio>("radio input", StringVector({ "radio a", "radio b", "radio c" }), nullptr, true);

		table.emplace<InputDropdown>("dropdown input", StringVector({ "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK" }), [](Widget&) {}, true);
		table.emplace<InputTypedown>("typedown input", StringVector({ "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK" }), [](Widget&) {}, true);

		table.emplace<InputText>("string input", "Hello, world!", nullptr, true);
		table.emplace<InputInt>("int input", AutoStat<int>(123, 0, 1000, 1), nullptr, true);
		table.emplace<InputFloat>("float input", AutoStat<float>(0.001f, 0.f, 100.f, 0.001f), nullptr, true);

		table.emplace<SliderInt>("int 0..3", AutoStat<int>(2, 0, 3, 1), nullptr, true);
		table.emplace<SliderInt>("int -100..100", AutoStat<int>(0, -100, 100, 1), nullptr, true);

		table.emplace<SliderFloat>("float input", AutoStat<float>(1.123f, 0.0f, 2.0f, 0.001f), nullptr, true);
		//table.emplace<SliderFloat>("log float", AutoStat<float>(0.f, 0.0f, 10.0f, 1.f));
		//table.emplace<SliderFloat>("signed log float", AutoStat<float>(0.f, -10.0f, 10.0f, 1.f));
		//table.emplace<SliderFloat>("unbound float", AutoStat<float>(123456789.0f, -FLT_MAX, FLT_MAX, 1.f));

		// table.emplace<SliderAngle>("angle", 0.f);

		// table.emplace<InputVec3>("slider float3", 0.0f, 1.0f);
		// table.emplace<InputColor>("color input");

		return parent;
	}

	Wedge& createUiTestFocusTabbing(Wedge& parent)
	{
		parent.emplace<Label>("Use TAB/SHIFT+TAB to cycle through keyboard editable fields.");

		static string first = "1";
		static string second = "2";
		static string third = "3";
		static string fourth = "4 (tab skip)";
		static string fifth = "5";

		parent.emplace<TypeIn>(first);
		parent.emplace<TypeIn>(second);
		parent.emplace<TypeIn>(third);
		parent.emplace<TypeIn>(fourth);
		parent.emplace<TypeIn>(fifth);
		return parent;
	}

	Wedge& createUiTestFileBrowser(Wedge& parent)
	{
		parent.emplace<Directory>("..");
		return parent;
	}

	Wedge& createUiTestFileTree(Wedge& parent)
	{
		Tree& filetree = parent.emplace<Tree>();
		DirectoryNode& node = filetree.emplace<DirectoryNode>("..", "..", false);
		node.update();
		return parent;
	}

	Wedge& createUiTestInlineControls(Wedge& parent)
	{
		Wedge& line0 = parent.emplace<Wedge>(Wedge::Row());

		line0.emplace<Label>("Hello");
		line0.emplace<Label>("World");

		Wedge& line1 = parent.emplace<Wedge>(Wedge::Row());

		line1.emplace<Button>("Banana");
		line1.emplace<Button>("Apple");
		line1.emplace<Button>("Corniflower");

		Wedge& line2 = parent.emplace<Wedge>(Wedge::Row());

		line2.emplace<Label>("Small buttons");
		line2.emplace<Button>("Like this one");
		line2.emplace<Label>("can fit within a text block.");

		Wedge& line3 = parent.emplace<Wedge>(Wedge::Row());

		line3.emplace<InputBool>("My", true);
		line3.emplace<InputBool>("Tailor", true);
		line3.emplace<InputBool>("Is", true);
		line3.emplace<InputBool>("Rich", true);

		Wedge& line4 = parent.emplace<Wedge>(Wedge::Row());

		line4.emplace<InputFloat>("X", 0.f);
		line4.emplace<InputFloat>("Y", 0.f);
		line4.emplace<InputFloat>("Z", 0.f);

		return parent;
	}

	Wedge& createUiTestProgressDialog(Wedge& parent)
	{
		ProgressBar& bar = parent.emplace<ProgressBar>();
		bar.setPercentage(0.57f);
		parent.emplace<SliderFloat>("Set progress", AutoStat<float>(0.57f, 0.f, 1.f, 0.01f), [&bar](float val) { bar.setPercentage(val); });
		return parent;
	}

	Window& createUiTestWindow(Wedge& parent)
	{
		Window& window = parent.emplace<Window>("Test Window");
		createUiTestWindow(window.body());
		return window;
	}

	Window& createUiTestWindowPage(Wedge& parent)
	{
		Window& window = *parent.findContainer<Window>();

		parent.emplace<Label>("kiui says hello.\n" "line breaks can happen in a label");

		static string help = "This window is being created by the ShowTestWindow() function. Please refer to the code for programming reference.\n\nUser Guide:";
		Expandbox& box0 = parent.emplace<Expandbox>("Help");
		box0.body().emplace<Text>(help);

		Expandbox& box1 = parent.emplace<Expandbox>("Window options");

		box1.body().emplace<InputBool>("titlebar", true, [&window](bool on) { on ? window.showTitlebar() : window.hideTitlebar(); }, true);
		box1.body().emplace<InputBool>("movable", true, [&window](bool) { window.toggleMovable(); }, true);
		box1.body().emplace<InputBool>("resizable", true, [&window](bool) { window.toggleResizable(); }, true);
		box1.body().emplace<InputBool>("closable", true, [&window](bool) { window.toggleClosable(); }, true);

		box1.body().emplace<SliderFloat>("fill alpha", AutoStat<float>(0.f, 0.f, 1.f, 0.1f), [&window](float alpha) { window.frame().inkstyle().m_backgroundColour.val.setA(alpha); });

		Expandbox& box2 = parent.emplace<Expandbox>("Widgets");
		createUiTestControls(box2.body());

		Expandbox& box3 = parent.emplace<Expandbox>("Table");
		createUiTestTable(box3.body());

		return window;
	}

	Wedge& createUiDebugDock(Wedge& parent)
	{
		Dockbar& tooldock = parent.emplace<Dockbar>();

		Renderer& renderer = *Caption::s_renderer;

		Wedge& options = tooldock.addDock("Options").body();
		options.emplace<InputText>("Debug draw filter", "", [&renderer](string value) { renderer.m_debugDrawFilter = value; });
		options.emplace<InputBool>("Debug draw Frame", false, [&renderer](bool on) { renderer.m_debugDrawFrameRect = on; });
		options.emplace<InputBool>("Debug draw Padding", false, [&renderer](bool on) { renderer.m_debugDrawPaddedRect = on; });
		options.emplace<InputBool>("Debug draw Content", false, [&renderer](bool on) { renderer.m_debugDrawContentRect = on; });
		options.emplace<InputBool>("Debug draw Clip", false, [&renderer](bool on) { renderer.m_debugDrawClipRect = on; });

		return tooldock;
	}

	void switchUiTheme(UiWindow& uiWindow, const string& name)
	{
		StyleParser parser(uiWindow.styler());

		if(name == "Blendish")
			parser.loadStyleSheet(uiWindow.resourcePath() + "interface/styles/blendish.yml");
		else if(name == "Blendish Dark")
			parser.loadStyleSheet(uiWindow.resourcePath() + "interface/styles/blendish_dark.yml");
		else if(name == "TurboBadger")
			parser.loadStyleSheet(uiWindow.resourcePath() + "interface/styles/turbobadger.yml");
		else if(name == "MyGui")
			parser.loadStyleSheet(uiWindow.resourcePath() + "interface/styles/mygui.yml");
		else if(name == "Photoshop")
			parser.loadStyleSheet(uiWindow.resourcePath() + "interface/styles/photoshop.yml");
		else if(name == "Default")
			parser.loadDefaultStyle();

		uiWindow.styler().style(CustomElement::cls()).layout().d_align = DimAlign(LEFT, CENTER);
	}

	void selectUiTheme(Wedge& sheet, Widget& selected)
	{
		const string name = selected.label();
		switchUiTheme(sheet.uiWindow(), name);
	}

	template <class T>
	auto windowSample(T func)
	{
		return [func](const string& name, Wedge& sheet) {
			Window& window = sheet.emplace<Window>(name);
			ScrollSheet& scrollSheet = window.body().emplace<ScrollSheet>();
			func(scrollSheet.body());
		};
	}

	template <class T>
	auto boardSample(T func)
	{
		return [func](const string& name, Wedge& sheet) {
			UNUSED(name);
			sheet.store().clear();
			func(sheet);
		};
	}

	using Sample = std::function<void(const string&, Wedge&)>;

	static std::map<string, Sample>& sampleMap()
	{
		static std::map<string, Sample> samples;
		samples["Application"] = boardSample(createUiTestApplication);
		samples["Dockspace"] = boardSample(createUiTestDockspace);
		samples["Nodes"] = boardSample(createUiTestNodes);
		samples["Window"] = windowSample(createUiTestWindowPage);
		samples["Filtered List"] = windowSample(createUiTestFilteredList); //window.frame().setSize(130.f, 300.f);
		samples["Custom List"] = windowSample(createUiTestCustomList);
		samples["Text Editor"] = windowSample(createUiTestTextEditor);
		samples["Tabs"] = windowSample(createUiTestTabs);
		samples["Table"] = windowSample(createUiTestTable);
		samples["Tree"] = windowSample(createUiTestTree);
		samples["Controls"] = windowSample(createUiTestControls);
		samples["File Browser"] = windowSample(createUiTestFileBrowser);
		samples["File Tree"] = windowSample(createUiTestFileTree);
		samples["Progress Dialog"] = windowSample(createUiTestProgressDialog);
		return samples;
	}

	void createUiTest(Wedge& rootSheet)
	{
		switchUiTheme(rootSheet.uiWindow(), "Blendish Dark");

		Wedge& demoheader = rootSheet.emplace<Wedge>(Wedge::Header());
		Wedge& demobody = rootSheet.emplace<Wedge>(Wedge::Board());
		Wedge& samplebody = demobody.emplace<Wedge>(Wedge::Layout());
		createUiDebugDock(demobody);

		std::map<string, Sample>& samples = sampleMap();

		StringVector sampleNames;
		for(auto& kv : samples)
			sampleNames.push_back(kv.first);
		
		StringVector themes({ "Blendish", "Blendish Dark", "TurboBadger", "MyGui" });

		auto pickUiSample = [&samplebody, &samples](Widget& selected)
		{
			samples[selected.label()](selected.label(), samplebody);
		};

		demoheader.emplace<Label>("Pick a demo sample : ");
		demoheader.emplace<DropdownInput>(sampleNames, pickUiSample);
		demoheader.emplace<Label>("Switch theme : ");
		demoheader.emplace<DropdownInput>(themes, [&samplebody](Widget& selected) { selectUiTheme(samplebody, selected); });
	}
}
