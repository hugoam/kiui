
#ifndef MK_UI_EXAMPLE_H
#define MK_UI_EXAMPLE_H

#include <toyui/Forward.h>

namespace toy
{
	TOY_UIEXAMPLE_EXPORT void switchUiTheme(UiWindow& uiWindow, const string& name);
	TOY_UIEXAMPLE_EXPORT void selectUiTheme(Sheet& sheet, Widget& selected);
	TOY_UIEXAMPLE_EXPORT void pickUiSample(Sheet& sheet, Widget& selected);
	TOY_UIEXAMPLE_EXPORT Sheet& createUiStyleEdit(Sheet& parent);
	TOY_UIEXAMPLE_EXPORT Sheet& createUiTestScrollList(Sheet& parent);
	TOY_UIEXAMPLE_EXPORT Sheet& createUiTestCustomList(Sheet& parent);
	TOY_UIEXAMPLE_EXPORT Sheet& createUiTestFilteredList(Sheet& parent);
	TOY_UIEXAMPLE_EXPORT Sheet& createUiTestTextEditor(Sheet& parent);
	TOY_UIEXAMPLE_EXPORT Sheet& createUiTestDockspace(Sheet& parent);
	TOY_UIEXAMPLE_EXPORT Sheet& createUiTestNodes(Sheet& parent);
	TOY_UIEXAMPLE_EXPORT Sheet& createUiTestTabs(Sheet& parent, bool window = true);
	TOY_UIEXAMPLE_EXPORT Sheet& createUiTestTable(Sheet& parent, bool window = true);
	TOY_UIEXAMPLE_EXPORT Sheet& createUiTestTree(Sheet& parent);
	TOY_UIEXAMPLE_EXPORT Sheet& createUiTestInlineControls(Sheet& parent);
	TOY_UIEXAMPLE_EXPORT Sheet& createUiTestControls(Sheet& parent, bool window = true);
	TOY_UIEXAMPLE_EXPORT Sheet& createUiTestProgressDialog(Sheet& parent);
	TOY_UIEXAMPLE_EXPORT Window& createUiTestWindow(Sheet& parent);
	TOY_UIEXAMPLE_EXPORT Sheet& createUiTestFileBrowser(Sheet& parent);
	TOY_UIEXAMPLE_EXPORT Sheet& createUiTestFileTree(Sheet& parent);
	TOY_UIEXAMPLE_EXPORT void createUiTest(Sheet& rootSheet);
}

#endif
