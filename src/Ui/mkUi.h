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
	MK_UI_EXPORT Dockspace* createUiTestDockspace(Form* parent);
	MK_UI_EXPORT Tabber* createUiTestTabs(Form* parent);
	MK_UI_EXPORT Table* createUiTestTable(Form* parent);
	MK_UI_EXPORT Table* createUiTestTableAlt(Form* parent);
	MK_UI_EXPORT Tree* createUiTestTree(Form* parent);
	MK_UI_EXPORT Form* createUiTestControls(Form* parent);
	MK_UI_EXPORT Window* createUiTestWindow(Form* parent);
}

#endif // MK_UI_H_INCLUDED
