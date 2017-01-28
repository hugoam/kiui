
#ifndef MK_UI_EXAMPLE_H
#define MK_UI_EXAMPLE_H

#include <Ui/mkUiForward.h>

namespace mk
{
	MK_UIEXAMPLE_EXPORT void switchUiTheme(UiWindow& uiWindow, const string& name);
	MK_UIEXAMPLE_EXPORT void selectUiTheme(Sheet& sheet, Widget& selected);
	MK_UIEXAMPLE_EXPORT void pickUiSample(Sheet& sheet, Widget& selected);
	MK_UIEXAMPLE_EXPORT Sheet& createUiStyleEdit(Sheet& parent);
	MK_UIEXAMPLE_EXPORT Sheet& createUiTestScrollList(Sheet& parent);
	MK_UIEXAMPLE_EXPORT Sheet& createUiTestCustomList(Sheet& parent);
	MK_UIEXAMPLE_EXPORT Sheet& createUiTestFilteredList(Sheet& parent);
	MK_UIEXAMPLE_EXPORT Sheet& createUiTestTextEditor(Sheet& parent);
	MK_UIEXAMPLE_EXPORT Sheet& createUiTestDockspace(Sheet& parent);
	MK_UIEXAMPLE_EXPORT Sheet& createUiTestNodes(Sheet& parent);
	MK_UIEXAMPLE_EXPORT Sheet& createUiTestTabs(Sheet& parent, bool window = true);
	MK_UIEXAMPLE_EXPORT Sheet& createUiTestTable(Sheet& parent, bool window = true);
	MK_UIEXAMPLE_EXPORT Sheet& createUiTestTree(Sheet& parent);
	MK_UIEXAMPLE_EXPORT Sheet& createUiTestInlineControls(Sheet& parent);
	MK_UIEXAMPLE_EXPORT Sheet& createUiTestControls(Sheet& parent, bool window = true);
	MK_UIEXAMPLE_EXPORT Sheet& createUiTestProgressDialog(Sheet& parent);
	MK_UIEXAMPLE_EXPORT Window& createUiTestWindow(Sheet& parent);
	MK_UIEXAMPLE_EXPORT Sheet& createUiTestFileBrowser(Sheet& parent);
	MK_UIEXAMPLE_EXPORT Sheet& createUiTestFileTree(Sheet& parent);
	MK_UIEXAMPLE_EXPORT void createUiTest(Sheet& rootSheet);
}

#endif
