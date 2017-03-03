
#ifndef MK_UI_EXAMPLE_H
#define MK_UI_EXAMPLE_H

#include <toyui/Forward.h>

namespace toy
{
	TOY_UIEXAMPLE_EXPORT void switchUiTheme(UiWindow& uiWindow, const string& name);
	TOY_UIEXAMPLE_EXPORT void selectUiTheme(Container& sheet, Widget& selected);
	TOY_UIEXAMPLE_EXPORT void pickUiSample(Container& sheet, Widget& selected);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiStyleEdit(Container& parent);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiTestScrollList(Container& parent);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiTestCustomList(Container& parent);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiTestFilteredList(Container& parent);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiTestTextEditor(Container& parent);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiTestApplication(Container& parent);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiTestDockspace(Container& parent);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiTestNodes(Container& parent);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiTestTabs(Container& parent, bool window = true);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiTestTable(Container& parent, bool window = true);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiTestTree(Container& parent);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiTestInlineControls(Container& parent);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiTestControls(Container& parent, bool window = true);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiTestProgressDialog(Container& parent);
	TOY_UIEXAMPLE_EXPORT Window& createUiTestWindow(Container& parent);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiTestFileBrowser(Container& parent);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiTestFileTree(Container& parent);
	TOY_UIEXAMPLE_EXPORT void createUiTest(Container& rootSheet);
}

#endif
