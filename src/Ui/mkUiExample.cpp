//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/mkUiTypes.h>

#include <Ui/mkUi.h>

#include <Ui/Nano/mkGlWindow.h>
#include <Ui/Nano/mkNanoInk.h>

#include <cfloat>

using namespace std::placeholders;

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

	Sheet& createUiTestCustomList(Sheet& parent)
	{
		Window& window = parent.emplace<Window>("Customized list items");
		Page& page = window.body().emplace<Page>("List and filter");
		SelectList& list = page.emplace<SelectList>();

		for(int i = 0; boy_names[i]; i++)
			list.emplace<CustomElement>(boy_names[i]);

		page.emplace<FilterInput>(list);

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

		page.emplace<FilterInput>(list);

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
		createUiTestControls(dock0, false);

		Page& dock1 = dockspace.emplace<Page>("Dock 1", "0.1");
		createUiTestInlineControls(dock1);

		Page& dock2 = dockspace.emplace<Page>("Dock 2", "0.2");
		createUiTestTable(dock2, false);

		return dockspace;
	}

	Sheet& createUiTestTabs(Sheet& parent, bool window)
	{
		if(!window)
			parent.clear();

		Sheet& page = window ? parent.emplace<Window>("Tabs").body().emplace<Page>("Tabs")
							 : parent;

		Tabber& tabber = page.emplace<Tabber>();

		Page& tab0 = tabber.emplace<Page>("Tab 0");
		createUiTestTable(tab0, false);

		Page& tab1 = tabber.emplace<Page>("Tab 1");
		createUiTestInlineControls(tab1);

		Page& tab2 = tabber.emplace<Page>("Tab 2");
		createUiTestControls(tab2, false);

		return page;
	}

	Sheet& createUiTestTable(Sheet& parent, bool window)
	{
		Sheet& page = window ? parent.emplace<Window>("Tables").body().emplace<Page>("Tables")
							 : parent.emplace<Page>("Tables");

		Table& table0 = page.emplace<Table>(StringVector({ "ID", "Name", "Path", "Flags" }), std::vector<float>({ 0.25f, 0.25f, 0.25f, 0.25f }));

		table0.emplace<LabelSequence>(StringVector({ "0000", "Robert", "/path/robert", "...." }));
		table0.emplace<LabelSequence>(StringVector({ "0001", "Stephanie", "/path/stephanie", "line 1" }));
		table0.emplace<LabelSequence>(StringVector({ "0002", "C64", "/path/computer", "...." }));

		Table& table1 = page.emplace<Table>(StringVector({ "Column 0", "Column 1", "Column 3" }), std::vector<float>({ 0.33f, 0.33f, 0.33f }));

		table1.emplace<LabelSequence>(StringVector({ "Hello", "kiUi", "World!" }));
		table1.emplace<ButtonSequence>(StringVector({ "Banana", "Apple", "Corniflower" }));
		table1.emplace<RadioSwitch>(nullptr, 0, StringVector({ "radio a", "radio b", "radio b" }));

		Sequence& line0 = table1.emplace<Sequence>();

		Expandbox& box0 = line0.emplace<Expandbox>("Category A");
		box0.emplace<Label>("Blah blah blah");

		Expandbox& box1 = line0.emplace<Expandbox>("Category B");
		box1.emplace<Label>("Blah blah blah");

		Expandbox& box2 = line0.emplace<Expandbox>("Category C");
		box2.emplace<Label>("Blah blah blah");


		Table& table2 = page.emplace<Table>(StringVector({ "Left", "Right" }), std::vector<float>({ 0.5f, 0.5f }));

		Sequence& line1 = table2.emplace<Sequence>();

		line1.emplace<InputFloat>("Red", 0.05f);
		line1.emplace<InputFloat>("Blue", 0.05f);

		Sequence& line2 = table2.emplace<Sequence>();

		line2.emplace<Textbox>("The quick brown fox jumps over the lazy dog.");
		line2.emplace<Textbox>("The quick brown fox jumps over the lazy dog.");

		Sequence& line3 = table2.emplace<Sequence>();

		line3.emplace<Label>("Hello Left");
		line3.emplace<Label>("Hello Right");

		return page;
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

	Sheet& createUiTestMarkupText(Sheet& parent)
	{
		Page& page = parent.emplace<Page>("Markup Text");
		page.emplace<Textbox>("This is a long paragraph. The text should automatically wrap on the edge of the window. The current implementation follows no word splitting rules, text is just split at the last character.");
		page.emplace<SliderFloat>("Wrap width", AutoStat<float>(200.f, -20.f, 600.f, 0.1f), [](float){ });

		Sequence& line0 = page.emplace<Sequence>();
		line0.emplace<Icon>("bullet");
		line0.emplace<Label>("Bullet point 1");

		Sequence& line1 = page.emplace<Sequence>();
		line1.emplace<Icon>("bullet");
		line1.emplace<Textbox>("Bullet point 2\nOn multiple lines");

		Sequence& line2 = page.emplace<Sequence>();
		line2.emplace<Icon>("bullet");
		line2.emplace<Label>("Bullet point 3");

		return page;
	}

	Sheet& createUiTestControls(Sheet& parent, bool window)
	{
		Sheet& page = window ? parent.emplace<Window>("Tables").body().emplace<Page>("Tables")
							 : parent.emplace<Page>("Controls");

		Table& table = page.emplace<Table>(StringVector({ "input", "label" }), std::vector<float>({ 0.7f, 0.3f }));

		table.emplace<InputBool>("checkbox input", false, nullptr, true);
		table.emplace<InputRadio>("radio input", StringVector({ "radio a", "radio b", "radio c" }), nullptr, true);

		table.emplace<InputDropdown>("dropdown input", StringVector({ "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK" }), [](string val) {}, false, true);
		table.emplace<InputDropdown>("typedown input", StringVector({ "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK" }), [](string val) {}, true, true);

		table.emplace<InputText>("string input", "Hello, world!", nullptr, true);
		table.emplace<InputInt>("int input", 123, nullptr, true);
		table.emplace<InputFloat>("float input", 0.001f, nullptr, true);

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

	Sheet& createUiTestFocusTabbing(Sheet& parent)
	{
		Page& page = parent.emplace<Page>("Tabbing");
		page.emplace<Label>("Use TAB/SHIFT+TAB to cycle through keyboard editable fields.");

		page.emplace<TypeIn>(nullptr, "1");
		page.emplace<TypeIn>(nullptr, "2");
		page.emplace<TypeIn>(nullptr, "3");
		page.emplace<TypeIn>(nullptr, "4 (tab skip)");
		page.emplace<TypeIn>(nullptr, "5");
		return page;
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

		box1.emplace<InputBool>("titlebar", true, [&window](bool on) { on ? window.showTitlebar() : window.hideTitlebar(); }, true);
		box1.emplace<InputBool>("movable", true, [&window](bool) { window.toggleMovable(); }, true);
		box1.emplace<InputBool>("resizable", true, [&window](bool) { window.toggleResizable(); }, true);
		box1.emplace<InputBool>("closable", true, [&window](bool) { window.toggleClosable(); }, true);

		box1.emplace<SliderFloat>("fill alpha", AutoStat<float>(0.f, 0.f, 1.f, 0.1f), [&window](float alpha){ window.frame().inkstyle().mBackgroundColour.val.setA(alpha); });

		Expandbox& box2 = page.emplace<Expandbox>("Widgets");
		createUiTestControls(box2, false);

		Expandbox& box3 = page.emplace<Expandbox>("Tables");
		createUiTestTable(box3, false);

		return window;
	}

	class StyleEdit : public Page
	{
	public:
		StyleEdit(Styler& styler)
			: Page("Style Edit")
			, mStyler(styler)
			, mStylePicker(this->emplace<Typedown>([this](Widget& choice){ this->pickStyle(choice.label()); }))
			, mEmpty(this->emplace<InputBool>("Empty", true, [this](bool empty) { this->mSkin->setEmpty(empty); this->mStyle->markUpdate(); }))
			, mBackgroundColour(this->emplace<InputColour>("Background Colour", Colour(), [this](Colour colour) { this->mSkin->backgroundColour() = colour; this->mStyle->markUpdate(); }))
			, mGradientTop(this->emplace<SliderInt>("Gradient Top", AutoStat<int>(0, -50, +50), [this](int top) { this->mSkin->topdownGradient().setX(float(top)); this->mStyle->markUpdate(); }))
			, mGradientDown(this->emplace<SliderInt>("Gradient Bottom", AutoStat<int>(0, -50, +50), [this](int down) { this->mSkin->topdownGradient().setY(float(down)); this->mStyle->markUpdate(); }))
			, mCornerRadius(this->emplace<SliderInt>("Corner Radius", AutoStat<int>(0, 0, 25), [this](int radius) { this->mSkin->cornerRadius().assign(float(radius)); this->mStyle->markUpdate(); }))
			, mBorderWidth(this->emplace<SliderFloat>("Border Width", AutoStat<float>(0.f, 0.f, 10.f, 0.1f), [this](float width) { this->mSkin->borderWidth().assign(width); this->mStyle->markUpdate(); }))
			, mBorderColour(this->emplace<InputColour>("Border Colour", Colour(), [this](Colour colour) { this->mSkin->borderColour() = colour; this->mStyle->markUpdate(); }))
			, mTextSize(this->emplace<SliderInt>("Text Size", AutoStat<int>(0, 0, 50), [this](int size) { this->mSkin->textSize() = float(size); this->mStyle->markUpdate(); }))
			, mTextColour(this->emplace<InputColour>("Text Colour", Colour(), [this](Colour colour) { this->mSkin->textColour() = colour; this->mStyle->markUpdate(); }))
			, mPadding(this->emplace<SliderInt>("Padding", AutoStat<int>(0, 0, 25), [this](int padding) { this->mSkin->padding().assign(padding); this->mStyle->markUpdate(); }))
			//, mAlignX(this->emplace<InputRadio>("Align Y", StringVector({ "Left", "Center", "Right", "OutLeft", "OutRight" }), [this](const string&) {}))
			//, mAlignY(this->emplace<InputRadio>("Align Y", StringVector({ "Left", "Center", "Right", "OutLeft", "OutRight" }), [this](const string&) {}))
			, mImage(this->emplace<InputText>("Image", "", [this](string name) { this->mSkin->image().d_name = name; this->mStyle->markUpdate(); }))
			, mSkinImage(this->emplace<InputText>("Skin Image", "", [this](string name) { this->mSkin->image().d_name = name; this->mStyle->markUpdate(); }))
		{
			for(Object* object : Style::indexer().objects())
				if(object)
					mStylePicker.emplace<Label>(object->as<Style>().name());
		}

		void pickStyle(const string& name)
		{
			mStyle = mStyler.fetchStyle(name);
			mSkin = &mStyle->skin();

			mEmpty.input().modifyValue(mSkin->empty());
			mBackgroundColour.input().modifyValue<Colour>(mSkin->backgroundColour());
			mGradientTop.input().modifyValue(mSkin->topdownGradient().x());
			mGradientDown.input().modifyValue(mSkin->topdownGradient().y());
			mCornerRadius.input().modifyValue(mSkin->cornerRadius().x0());
			mBorderWidth.input().modifyValue(mSkin->borderWidth().x0());
			mBorderColour.input().modifyValue<Colour>(mSkin->borderColour());
			mTextSize.input().modifyValue(mSkin->textSize());
			mTextColour.input().modifyValue<Colour>(mSkin->textColour());
			mPadding.input().modifyValue(mSkin->padding().x0());
			//mAlignX.input().modifyValue();
			//mAlignY.input().modifyValue();
			mImage.input().modifyValue<string>(mSkin->image().d_name);
			mSkinImage.input().modifyValue<string>(mSkin->imageSkin().d_image.d_name);
		}

	protected:
		Styler& mStyler;
		Dropdown& mStylePicker;

		InputBool& mEmpty;
		InputColour& mBackgroundColour;
		SliderInt& mGradientTop;
		SliderInt& mGradientDown;
		SliderInt& mCornerRadius;
		SliderFloat& mBorderWidth;
		InputColour& mBorderColour;
		SliderInt& mTextSize;
		InputColour& mTextColour;
		SliderInt& mPadding;
		//InputRadio& mAlignX;
		//InputRadio& mAlignY;
		InputText& mImage;
		InputText& mSkinImage;

		Style* mStyle;
		InkStyle* mSkin;
	};

	Sheet& createUiStyleEdit(Sheet& parent)
	{
		Dockbar& tooldock = parent.emplace<Dockbar>();

		StyleEdit& styleedit = tooldock.emplace<StyleEdit>(parent.uiWindow().styler());
		Page& options = tooldock.emplace<Page>("Options");
		options.emplace<InputBool>("Toggle debug draw", false, [](bool on) { NanoInk::sDebugDraw = on; });

		return tooldock;
	}

	void switchUiTheme(Sheet& sheet, const string& name)
	{
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

		CustomElement::cls().layout().d_align = DimAlign(LEFT, CENTER);
	}

	void selectUiTheme(Sheet& sheet, Widget& selected)
	{
		const string name = selected.label();
		switchUiTheme(sheet, name);
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
		switchUiTheme(root.sheet(), "Blendish Dark");

		Header& demoheader = root.sheet().emplace<Header>();
		Board& demobody = root.sheet().emplace<Board>();
		LayerSheet& samplebody = demobody.emplace<LayerSheet>();
		createUiStyleEdit(demobody);

		demoheader.emplace<Label>("Pick a demo sample : ");
		demoheader.emplace<Dropdown>(std::bind(&pickUiSample, std::ref(samplebody), std::placeholders::_1), StringVector({ "Dockspace", "Window", "Text Editor", "Filtered List", "Custom List", "Tabs", "Table", "Tree", "Controls", "File Browser", "File Tree", "Progress Dialog" }));
		demoheader.emplace<Label>("Switch theme : ");
		demoheader.emplace<Dropdown>(std::bind(&selectUiTheme, std::ref(samplebody), std::placeholders::_1), StringVector({ "Blendish", "Blendish Dark", "TurboBadger", "MyGui" }));
	}
}
