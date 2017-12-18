
#ifndef MK_UI_EXAMPLE_H
#define MK_UI_EXAMPLE_H

#include <toyui/Types.h>

namespace toy
{
	TOY_UIEXAMPLE_EXPORT void switchUiTheme(UiWindow& uiWindow, const string& name);
	TOY_UIEXAMPLE_EXPORT void selectUiTheme(Wedge& sheet, Widget& selected);
	TOY_UIEXAMPLE_EXPORT void pickUiSample(Wedge& sheet, Widget& selected);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiStyleEdit(Wedge& parent);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiTestScrollList(Wedge& parent);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiTestCustomList(Wedge& parent);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiTestFilteredList(Wedge& parent);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiTestTextEditor(Wedge& parent);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiTestApplication(Wedge& parent);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiTestDockspace(Wedge& parent);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiTestNodes(Wedge& parent);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiTestTabs(Wedge& parent);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiTestTable(Wedge& parent);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiTestTree(Wedge& parent);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiTestInlineControls(Wedge& parent);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiTestControls(Wedge& parent);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiTestProgressDialog(Wedge& parent);
	TOY_UIEXAMPLE_EXPORT Window& createUiTestWindow(Wedge& parent);
	TOY_UIEXAMPLE_EXPORT Window& createUiTestWindowPage(Wedge& parent);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiTestFileBrowser(Wedge& parent);
	TOY_UIEXAMPLE_EXPORT Wedge& createUiTestFileTree(Wedge& parent);
	TOY_UIEXAMPLE_EXPORT void createUiTest(Wedge& rootSheet);
}

#endif
