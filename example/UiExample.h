
#ifndef MK_UI_EXAMPLE_H
#define MK_UI_EXAMPLE_H

#include <toyui/Forward.h>

namespace toy
{
	TOY_UIEXAMPLE_EXPORT void switchUiTheme(UiWindow& uiWindow, const string& name);
	TOY_UIEXAMPLE_EXPORT void selectUiTheme(Container& sheet, Widget& selected);
	TOY_UIEXAMPLE_EXPORT void pickUiSample(Container& sheet, Widget& selected);
	TOY_UIEXAMPLE_EXPORT Piece& createUiStyleEdit(Container& parent);
	TOY_UIEXAMPLE_EXPORT Piece& createUiTestScrollList(Container& parent);
	TOY_UIEXAMPLE_EXPORT Piece& createUiTestCustomList(Container& parent);
	TOY_UIEXAMPLE_EXPORT Piece& createUiTestFilteredList(Container& parent);
	TOY_UIEXAMPLE_EXPORT Piece& createUiTestTextEditor(Container& parent);
	TOY_UIEXAMPLE_EXPORT Piece& createUiTestApplication(Container& parent);
	TOY_UIEXAMPLE_EXPORT Piece& createUiTestDockspace(Container& parent);
	TOY_UIEXAMPLE_EXPORT Piece& createUiTestNodes(Container& parent);
	TOY_UIEXAMPLE_EXPORT Piece& createUiTestTabs(Container& parent, bool window = true);
	TOY_UIEXAMPLE_EXPORT Piece& createUiTestTable(Container& parent, bool window = true);
	TOY_UIEXAMPLE_EXPORT Piece& createUiTestTree(Container& parent);
	TOY_UIEXAMPLE_EXPORT Piece& createUiTestInlineControls(Container& parent);
	TOY_UIEXAMPLE_EXPORT Piece& createUiTestControls(Container& parent, bool window = true);
	TOY_UIEXAMPLE_EXPORT Piece& createUiTestProgressDialog(Container& parent);
	TOY_UIEXAMPLE_EXPORT Window& createUiTestWindow(Container& parent);
	TOY_UIEXAMPLE_EXPORT Piece& createUiTestFileBrowser(Container& parent);
	TOY_UIEXAMPLE_EXPORT Piece& createUiTestFileTree(Container& parent);
	TOY_UIEXAMPLE_EXPORT void createUiTest(Container& rootSheet);
}

#endif
