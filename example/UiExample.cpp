 
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

	class CustomElement : public Row
	{
	public:
		CustomElement(Wedge& parent, const string& name)
			: Row(parent, cls())
			, m_label(this->build(name))
		{}

		Label& build(const string& name)
		{
			this->emplace<Checkbox>(nullptr, false);
			this->emplace<Icon>("tbb/icon48");
			Container& sheet = this->emplace<Container>();
			Label& label = sheet.emplace<Label>(name);
			sheet.emplace<Label>("Male");
			this->emplace<CloseButton>([this](Widget&){ this->destroy(); });
			return label;
		}

		const string& contentlabel() { return m_label.label(); }

		static Type& cls() { static Type ty("CustomElement", Row::cls()); return ty; }

	protected:
		Label& m_label;
	};

	Wedge& createUiTestCustomList(Container& parent)
	{
		Window& window = parent.emplace<Window>("Customized list items");
		Page& page = window.emplace<Page>();
		SelectList& list = page.emplace<SelectList>();

		for(int i = 0; boy_names[i]; i++)
			list.emplace<CustomElement>(boy_names[i]);

		page.emplace<FilterInput>(list.container());

		window.frame().setSize(250.f, 300.f);
		return window;
	}

	Wedge& createUiTestFilteredList(Container& parent)
	{
		Window& window = parent.emplace<Window>("List and filter");
		Page& page = window.emplace<Page>();
		SelectList& list = page.emplace<SelectList>();

		for(int i = 0; boy_names[i]; i++)
			list.emplace<Label>(boy_names[i]);
		for(int i = 0; girl_names[i]; i++)
			list.emplace<Label>(boy_names[i]);

		page.emplace<FilterInput>(list.container());

		window.frame().setSize(130.f, 300.f);
		return window;
	}

	Wedge& createUiTestScrollList(Container& parent)
	{
		Window& window = parent.emplace<Window>("Scroll List");
		Page& page = window.emplace<Page>();
		Container& sequence = page.emplace<Container>(Layout::cls());

		List& list0 = sequence.emplace<List>();
		for(int i = 0; i < 100; i++)
			list0.emplace<Label>("Element " + toString(i));

		List& list1 = sequence.emplace<List>();
		for(int i = 0; i < 100; i++)
			list1.emplace<Button>("Element " + toString(i));

		window.frame().setSize(400.f, 600.f);
		return window;
	}

	Wedge& createUiTestTextEditor(Container& parent)
	{
		Window& window = parent.emplace<Window>("Text Editor");
		Page& page = window.emplace<Page>();
		Container& buttons = page.emplace<Menubar>();
		Menu& menu = buttons.emplace<Menu>("Menu");
		menu.emplace<Button>("Redo");
		menu.emplace<Button>("Undo");
		Menu& submenu = menu.emplace<Menu>("Change Font", true);
		submenu.emplace<Button>("Arial");
		submenu.emplace<Button>("Myriad");

		buttons.emplace<Button>("Open File");
		buttons.emplace<Button>("Undo");
		buttons.emplace<Button>("Redo");

		static string text = "This is an example text editor field\n You can use it as any common editor";
		page.emplace<Textbox>(text);
		
		return window;
	}

	Wedge& createUiTestApplication(Container& parent)
	{
		parent.clear();

		Container& menubar = parent.emplace<Menubar>();

		Menu& menufile = menubar.emplace<Menu>("File");
		menufile.emplace<Button>("Open");
		menufile.emplace<Button>("Save");
		Menu& menusave = menufile.emplace<Menu>("Save As", true);
		menufile.emplace<Button>("Close");

		menusave.emplace<Button>("Save As JPEG");
		menusave.emplace<Button>("Save As PNG");
		menusave.emplace<Button>("Save As PDF");

		Menu& menuedit = menubar.emplace<Menu>("Edit");
		menuedit.emplace<Button>("Redo");
		menuedit.emplace<Button>("Undo");

		Menu& menuhelp = menubar.emplace<Menu>("Help");
		menuhelp.emplace<Button>("About kiUi");

		Tooldock& tooldock = parent.emplace<Tooldock>();

		Toolbar& toolbar0 = tooldock.emplace<Toolbar>();
		ToolButton& toolUndo = toolbar0.emplace<ToolButton>("arrow_left_15");
		ToolButton& toolRedo = toolbar0.emplace<ToolButton>("arrow_right_15");

		Toolbar& toolbar1 = tooldock.emplace<Toolbar>();
		ToolButton& toolOpen =  toolbar1.emplace<ToolButton>("file_15");
		ToolButton& toolSave =  toolbar1.emplace<ToolButton>("folder_15");
		ToolButton& toolClose = toolbar1.emplace<ToolButton>("close_15");

		return tooldock;
	}

	Wedge& createUiTestDockspace(Container& parent)
	{
		parent.clear();

		//MasterDockline::cls().layout().d_weights = { 0.2f, 0.6f, 0.2f };

		Dockspace& dockspace = parent.emplace<Dockspace>();

		Page& dock0 = dockspace.addDockWindow("Dock 0", { 0, 0 }).emplace<Page>();
		createUiTestControls(dock0, false);

		Page& dock1 = dockspace.addDockWindow("Dock 1", { 0, 1 }).emplace<Page>();
		createUiTestInlineControls(dock1);

		Page& dock2 = dockspace.addDockWindow("Dock 2", { 0, 2 }).emplace<Page>();
		createUiTestTable(dock2, false);

		return dockspace;
	}

	Wedge& createUiTestNodes(Container& parent)
	{
		parent.clear();

		Canvas& canvas = parent.emplace<Canvas>("Node Editor");

		Node& node0 = canvas.emplace<Node>("A Node");
		node0.addInput("a");
		node0.addInput("b");
		node0.addOutput("result");
		node0.frame().setPosition(150.f, 250.f);

		Node& node1 = canvas.emplace<Node>("A Node");
		node1.addInput("a");
		node1.addInput("b");
		node1.addOutput("result");
		node1.frame().setPosition(350.f, 150.f);

		Node& node2 = canvas.emplace<Node>("Another Node");
		node2.addInput("u");
		node2.addInput("v");
		node2.addOutput("x");
		node2.addOutput("y");
		node2.addOutput("z");
		node2.frame().setPosition(450.f, 450.f);

		Node& node3 = canvas.emplace<Node>("End Node");
		node3.addInput("input 1");
		node3.addInput("input 2");
		node3.frame().setPosition(800.f, 200.f);

		return parent;
	}

	Wedge& createUiTestTabs(Container& parent, bool window)
	{
		if(!window)
			parent.clear();

		Container& page = window ? parent.emplace<Window>("Tabs").emplace<Page>()
							     : parent;

		Tabber& tabber = page.emplace<Tabber>();

		Page& tab0 = tabber.addTab("Tab 0").emplace<Page>();
		createUiTestTable(tab0, false);

		Page& tab1 = tabber.addTab("Tab 1").emplace<Page>();
		createUiTestInlineControls(tab1);

		Page& tab2 = tabber.addTab("Tab 2").emplace<Page>();
		createUiTestControls(tab2, false);

		return page;
	}

	Wedge& createUiTestTable(Container& parent, bool window)
	{
		Container& page = window ? parent.emplace<Window>("Table").emplace<Page>()
							     : parent.emplace<Page>();

		Table& table0 = page.emplace<Table>(StringVector({ "ID", "Name", "Path", "Flags" }), std::vector<float>({ 0.25f, 0.25f, 0.25f, 0.25f }));

		table0.emplace<LabelSequence>(StringVector({ "0000", "Robert", "/path/robert", "...." }));
		table0.emplace<LabelSequence>(StringVector({ "0001", "Stephanie", "/path/stephanie", "line 1" }));
		table0.emplace<LabelSequence>(StringVector({ "0002", "C64", "/path/computer", "...." }));

		Table& table1 = page.emplace<Table>(StringVector({ "Column 0", "Column 1", "Column 3" }), std::vector<float>({ 0.33f, 0.33f, 0.33f }));

		table1.emplace<LabelSequence>(StringVector({ "Hello", "kiUi", "World!" }));
		table1.emplace<ButtonSequence>(StringVector({ "Banana", "Apple", "Corniflower" }));
		table1.emplace<RadioSwitch>(nullptr, 0, StringVector({ "radio a", "radio b", "radio b" }));

		Container& line0 = table1.emplace<Row>();

		Expandbox& box0 = line0.emplace<Expandbox>("Category A");
		box0.emplace<Label>("Blah blah blah");

		Expandbox& box1 = line0.emplace<Expandbox>("Category B");
		box1.emplace<Label>("Blah blah blah");

		Expandbox& box2 = line0.emplace<Expandbox>("Category C");
		box2.emplace<Label>("Blah blah blah");


		Table& table2 = page.emplace<Table>(StringVector({ "Left", "Right" }), std::vector<float>({ 0.5f, 0.5f }));

		Container& line1 = table2.emplace<Row>();

		line1.emplace<InputFloat>("Red", 0.05f);
		line1.emplace<InputFloat>("Blue", 0.05f);

		Container& line2 = table2.emplace<Row>();

		static string text1 = "The quick brown fox jumps over the lazy dog.";
		static string text2 = "The quick brown fox jumps over the lazy dog.";

		line2.emplace<TypeIn>(text1);
		line2.emplace<TypeIn>(text2);

		Container& line3 = table2.emplace<Row>();

		line3.emplace<Label>("Hello Left");
		line3.emplace<Label>("Hello Right");

		return page;
	}

	Wedge& createUiTestTree(Container& parent)
	{
		Window& window = parent.emplace<Window>("Tree");
		Page& page = window.emplace<Page>(); // "Tree"

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

	Tree& createUiTestTableTree(Container& parent)
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

	Wedge& createUiTestMarkupText(Container& parent)
	{
		static string multiline = "This is a long paragraph. The text should automatically wrap on the edge of the window. The current implementation follows no word splitting rules, text is just split at the last character.";
		Page& page = parent.emplace<Page>(); // "Markup Text"
		page.emplace<Textbox>(multiline);
		page.emplace<SliderFloat>("Wrap width", AutoStat<float>(200.f, -20.f, 600.f, 0.1f), [](float){ });

		Container& line0 = page.emplace<Row>();
		line0.emplace<Icon>("bullet");
		line0.emplace<Label>("Bullet point 1");

		static string multiline2 = "Bullet point 2\nOn multiple lines";
		Container& line1 = page.emplace<Row>();
		line1.emplace<Icon>("bullet");
		line1.emplace<Textbox>(multiline2);

		Container& line2 = page.emplace<Row>();
		line2.emplace<Icon>("bullet");
		line2.emplace<Label>("Bullet point 3");

		return page;
	}

	Wedge& createUiTestControls(Container& parent, bool window)
	{
		Container& page = window ? parent.emplace<Window>("Table").emplace<Page>()
								 : parent.emplace<Page>(); // "Controls"

		Table& table = page.emplace<Table>(StringVector({ "input", "label" }), std::vector<float>({ 0.7f, 0.3f }));

		table.emplace<InputBool>("checkbox input", false, nullptr, true);
		table.emplace<InputRadio>("radio input", StringVector({ "radio a", "radio b", "radio c" }), nullptr, true);

		table.emplace<InputDropdown>("dropdown input", StringVector({ "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK" }), [](string val) {}, true);
		//table.emplace<InputDropdown>("typedown input", StringVector({ "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK" }), [](string val) {}, true, true);

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

		return page;
	}

	Wedge& createUiTestFocusTabbing(Container& parent)
	{
		Page& page = parent.emplace<Page>(); // "Tabbing"
		page.emplace<Label>("Use TAB/SHIFT+TAB to cycle through keyboard editable fields.");

		static string first = "1";
		static string second = "2";
		static string third = "3";
		static string fourth = "4 (tab skip)";
		static string fifth = "5";

		page.emplace<TypeIn>(first);
		page.emplace<TypeIn>(second);
		page.emplace<TypeIn>(third);
		page.emplace<TypeIn>(fourth);
		page.emplace<TypeIn>(fifth);
		return page;
	}

	Wedge& createUiTestFileBrowser(Container& parent)
	{
		Window& window = parent.emplace<Window>("File Browser");
		window.emplace<Directory>("..");
		return window;
	}

	Wedge& createUiTestFileTree(Container& parent)
	{
		Window& window = parent.emplace<Window>("File Tree");
		Tree& filetree = window.emplace<Tree>();
		DirectoryNode& node = filetree.emplace<DirectoryNode>("..", "..", false);
		node.update();
		return window;
	}

	Wedge& createUiTestInlineControls(Container& parent)
	{
		Page& page = parent.emplace<Page>(); // "Inline Controls"

		Container& line0 = page.emplace<Row>();

		line0.emplace<Label>("Hello");
		line0.emplace<Label>("World");

		Container& line1 = page.emplace<Row>();

		line1.emplace<Button>("Banana");
		line1.emplace<Button>("Apple");
		line1.emplace<Button>("Corniflower");

		Container& line2 = page.emplace<Row>();

		line2.emplace<Label>("Small buttons");
		line2.emplace<Button>("Like this one");
		line2.emplace<Label>("can fit within a text block.");

		Container& line3 = page.emplace<Row>();

		line3.emplace<InputBool>("My", true);
		line3.emplace<InputBool>("Tailor", true);
		line3.emplace<InputBool>("Is", true);
		line3.emplace<InputBool>("Rich", true);

		Container& line4 = page.emplace<Row>();

		line4.emplace<InputFloat>("X", 0.f);
		line4.emplace<InputFloat>("Y", 0.f);
		line4.emplace<InputFloat>("Z", 0.f);

		return page;
	}

	Wedge& createUiTestProgressDialog(Container& parent)
	{
		Window& window = parent.emplace<Window>("Progress Dialog");
		Page& page = window.emplace<Page>();
		ProgressBar& bar = page.emplace<ProgressBar>();
		bar.setPercentage(0.57f);
		page.emplace<SliderFloat>("Set progress", AutoStat<float>(0.57f, 0.f, 1.f, 0.01f), [&bar](float val) { bar.setPercentage(val); });
		return window;
	}

	Window& createUiTestWindow(Container& parent)
	{
		Window& window = parent.emplace<Window>("kiUi v0.1");
		Page& page = window.emplace<Page>();

		page.emplace<Label>("kiui says hello.");

		static string help = "This window is being created by the ShowTestWindow() function. Please refer to the code for programming reference.\n\nUser Guide:";
		Expandbox& box0 = page.emplace<Expandbox>("Help");
		//box0.emplace<Text>(help);

		Expandbox& box1 = page.emplace<Expandbox>("Window options");

		box1.emplace<InputBool>("titlebar", true, [&window](bool on) { on ? window.showTitlebar() : window.hideTitlebar(); }, true);
		box1.emplace<InputBool>("movable", true, [&window](bool) { window.toggleMovable(); }, true);
		box1.emplace<InputBool>("resizable", true, [&window](bool) { window.toggleResizable(); }, true);
		box1.emplace<InputBool>("closable", true, [&window](bool) { window.toggleClosable(); }, true);
		box1.emplace<InputBool>("wrap content", false, [&window](bool) { window.toggleWrap(); }, true);

		box1.emplace<SliderFloat>("fill alpha", AutoStat<float>(0.f, 0.f, 1.f, 0.1f), [&window](float alpha){ window.content().inkstyle().m_backgroundColour.val.setA(alpha); });

		Expandbox& box2 = page.emplace<Expandbox>("Widgets");
		createUiTestControls(box2, false);

		Expandbox& box3 = page.emplace<Expandbox>("Table");
		createUiTestTable(box3, false);

		return window;
	}

	class StyleEdit : public Page
	{
	public:
		StyleEdit(Wedge& parent, Styler& styler)
			: Page(parent)
			, m_styler(styler)
			, m_stylePicker(*this, [this](Widget& choice) { this->pickStyle(choice.contentlabel()); })
			, m_table(*this, { "Field", "Value" }, { 0.3f, 0.7f })
			, m_empty(m_table, "Empty", true, [this](bool empty) { this->m_skin->setEmpty(empty); this->m_style->markUpdate(); })
			, m_backgroundColour(m_table, "Background Colour", Colour(), [this](Colour colour) { this->m_skin->backgroundColour() = colour; this->m_style->markUpdate(); })
			, m_gradientTop(m_table, "Gradient Top", AutoStat<int>(0, -50, +50), [this](int top) { this->m_skin->linearGradient().setX(float(top)); this->m_style->markUpdate(); })
			, m_gradientDown(m_table, "Gradient Bottom", AutoStat<int>(0, -50, +50), [this](int down) { this->m_skin->linearGradient().setY(float(down)); this->m_style->markUpdate(); })
			, m_cornerRadius(m_table, "Corner Radius", AutoStat<int>(0, 0, 25), [this](int radius) { this->m_skin->cornerRadius().assign(float(radius)); this->m_style->markUpdate(); })
			, m_borderWidth(m_table, "Border Width", AutoStat<float>(0.f, 0.f, 10.f, 0.1f), [this](float width) { this->m_skin->borderWidth().assign(width); this->m_style->markUpdate(); })
			, m_borderColour(m_table, "Border Colour", Colour(), [this](Colour colour) { this->m_skin->borderColour() = colour; this->m_style->markUpdate(); })
			, m_textSize(m_table, "Text Size", AutoStat<int>(0, 0, 50), [this](int size) { this->m_skin->textSize() = float(size); this->m_style->markUpdate(); })
			, m_textColour(m_table, "Text Colour", Colour(), [this](Colour colour) { this->m_skin->textColour() = colour; this->m_style->markUpdate(); })
			, m_padding(m_table, "Padding", AutoStat<int>(0, 0, 25), [this](int padding) { this->m_skin->padding().assign(float(padding)); this->m_style->markUpdate(); })
			//, m_alignX(m_table, "Align Y", StringVector({ "Left", "Center", "Right", "OutLeft", "OutRight" }), [this](const string&) {})
			//, m_alignY(m_table, "Align Y", StringVector({ "Left", "Center", "Right", "OutLeft", "OutRight" }), [this](const string&) {})
			, m_image(m_table, "Image", "", [this](string name) { /*this->m_skin->image().d_name = name;*/ this->m_style->markUpdate(); })
			, m_skinImage(m_table, "Skin Image", "", [this](string name) { /*this->m_skin->image().d_name = name;*/ this->m_style->markUpdate(); })
		{
			for(Object* object : Style::cls().indexer().objects())
				if(object)
					m_stylePicker.emplace<Label>(object->as<Style>().name());

			this->pickStyle("Widget");
		}

		void pickStyle(const string& name)
		{
			m_style = &m_styler.styledef(name); // @todo fix with style
			m_skin = &m_style->skin();

			m_empty.input().modifyValue(m_skin->empty());
			m_backgroundColour.input().modifyValue<Colour>(m_skin->backgroundColour());
			m_gradientTop.input().modifyValue(int(m_skin->linearGradient().x()));
			m_gradientDown.input().modifyValue(int(m_skin->linearGradient().y()));
			m_cornerRadius.input().modifyValue(int(m_skin->cornerRadius().x0()));
			m_borderWidth.input().modifyValue(int(m_skin->borderWidth().x0()));
			m_borderColour.input().modifyValue<Colour>(m_skin->borderColour());
			m_textSize.input().modifyValue(int(m_skin->textSize()));
			m_textColour.input().modifyValue<Colour>(m_skin->textColour());
			m_padding.input().modifyValue(int(m_skin->padding().x0()));
			//mAlignX.input().modifyValue();
			//mAlignY.input().modifyValue();
			if(m_skin->image())
				m_image.input().modifyValue<string>(m_skin->image()->d_name);
			if(!m_skin->imageSkin().null())
				m_skinImage.input().modifyValue<string>(m_skin->imageSkin().d_image->d_name);
		}

	protected:
		Styler& m_styler;

		DropdownInput m_stylePicker;
		Table m_table;


		InputBool m_empty;
		InputColour m_backgroundColour;
		SliderInt m_gradientTop;
		SliderInt m_gradientDown;
		SliderInt m_cornerRadius;
		SliderFloat m_borderWidth;
		InputColour m_borderColour;
		SliderInt m_textSize;
		InputColour m_textColour;
		SliderInt m_padding;
		//InputRadio m_alignX;
		//InputRadio m_alignY;
		InputText m_image;
		InputText m_skinImage;

		Style* m_style;
		InkStyle* m_skin;
	};

	Wedge& createUiStyleEdit(Container& parent)
	{
		Dockbar& tooldock = parent.emplace<Dockbar>();

		tooldock.addDock("Style Edit").emplace<StyleEdit>(parent.uiWindow().styler());

		Renderer& renderer = *DrawFrame::s_renderer;

		Page& options = tooldock.addDock("Options").emplace<Page>();
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

	void selectUiTheme(Container& sheet, Widget& selected)
	{
		const string name = selected.contentlabel();
		switchUiTheme(sheet.uiWindow(), name);
	}

	void pickUiSample(Container& sheet, Widget& selected)
	{
		const string name = selected.contentlabel();

		if(sheet.stripe().sequence().size() > 0)
			sheet.clear();

		if(name == "Application")
			createUiTestApplication(sheet);
		else if(name == "Dockspace")
			createUiTestDockspace(sheet);
		else if(name == "Nodes")
			createUiTestNodes(sheet);
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

	void createUiTest(Container& rootSheet)
	{
		switchUiTheme(rootSheet.uiWindow(), "Blendish Dark");

		Container& demoheader = rootSheet.emplace<Container>(Header::cls());
		Container& demobody = rootSheet.emplace<Container>(Board::cls());
		Container& samplebody = demobody.emplace<Container>(Layout::cls());
		createUiStyleEdit(demobody);

		StringVector samples({ "Application", "Dockspace", "Nodes", "Window", "Text Editor", "Filtered List", "Custom List", "Tabs", "Table", "Tree", "Controls", "File Browser", "File Tree", "Progress Dialog" });
		StringVector themes({ "Blendish", "Blendish Dark", "TurboBadger", "MyGui" });

		demoheader.emplace<Label>("Pick a demo sample : ");
		demoheader.emplace<DropdownInput>(std::bind(&pickUiSample, std::ref(samplebody), std::placeholders::_1), samples);
		demoheader.emplace<Label>("Switch theme : ");
		demoheader.emplace<DropdownInput>(std::bind(&selectUiTheme, std::ref(samplebody), std::placeholders::_1), themes);
	}
}
