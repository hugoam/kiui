//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_UI_H_INCLUDED
#define MK_UI_H_INCLUDED

#include <Ui/mkUiForward.h>
#include <Ui/Form/mkForm.h>

#include <memory>

namespace mk
{
	MK_UI_EXPORT Dockspace* createUiTestDockspace(Sheet* parent);
	MK_UI_EXPORT Tabber* createUiTestTabs(Sheet* parent);
	MK_UI_EXPORT Table* createUiTestTable(Sheet* parent);
	MK_UI_EXPORT Table* createUiTestTableAlt(Sheet* parent);
	MK_UI_EXPORT Tree* createUiTestTree(Sheet* parent);
	MK_UI_EXPORT Sheet* createUiTestInlineControls(Sheet* parent);
	MK_UI_EXPORT Sheet* createUiTestControls(Sheet* parent);
	MK_UI_EXPORT Sheet* createUiTestProgressDialog(Sheet* parent);
	MK_UI_EXPORT Window* createUiTestWindow(Sheet* parent);
	MK_UI_EXPORT Sheet* createUiTestFileBrowser(Sheet* parent);
	MK_UI_EXPORT Sheet* createUiTestFileTree(Sheet* parent);
	MK_UI_EXPORT void createUiTest(Form* parent);
}

#endif // MK_UI_H_INCLUDED
