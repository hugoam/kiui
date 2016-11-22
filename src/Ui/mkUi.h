//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_UI_H_INCLUDED
#define MK_UI_H_INCLUDED

#include <Ui/mkUiForward.h>

namespace mk
{
	MK_UI_EXPORT void switchUiTheme(UiWindow& uiWindow, const string& name);
	MK_UI_EXPORT void selectUiTheme(Sheet& sheet, Widget& selected);
	MK_UI_EXPORT void pickUiSample(Sheet& sheet, Widget& selected);
	MK_UI_EXPORT Sheet& createUiStyleEdit(Sheet& parent);
	MK_UI_EXPORT Sheet& createUiTestScrollList(Sheet& parent);
	MK_UI_EXPORT Sheet& createUiTestCustomList(Sheet& parent);
	MK_UI_EXPORT Sheet& createUiTestFilteredList(Sheet& parent);
	MK_UI_EXPORT Sheet& createUiTestTextEditor(Sheet& parent);
	MK_UI_EXPORT Sheet& createUiTestDockspace(Sheet& parent);
	MK_UI_EXPORT Sheet& createUiTestNodes(Sheet& parent);
	MK_UI_EXPORT Sheet& createUiTestNodeEditor(Sheet& parent);
	MK_UI_EXPORT Sheet& createUiTestTabs(Sheet& parent, bool window = true);
	MK_UI_EXPORT Sheet& createUiTestTable(Sheet& parent, bool window = true);
	MK_UI_EXPORT Sheet& createUiTestTree(Sheet& parent);
	MK_UI_EXPORT Sheet& createUiTestInlineControls(Sheet& parent);
	MK_UI_EXPORT Sheet& createUiTestControls(Sheet& parent, bool window = true);
	MK_UI_EXPORT Sheet& createUiTestProgressDialog(Sheet& parent);
	MK_UI_EXPORT Window& createUiTestWindow(Sheet& parent);
	MK_UI_EXPORT Sheet& createUiTestFileBrowser(Sheet& parent);
	MK_UI_EXPORT Sheet& createUiTestFileTree(Sheet& parent);
	MK_UI_EXPORT void createUiTest(Device& parent);
}

#endif // MK_UI_H_INCLUDED
