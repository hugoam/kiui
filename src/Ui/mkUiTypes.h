//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_UITYPES_H_INCLUDED
#define MK_UITYPES_H_INCLUDED

#include <Ui/Form/mkForm.h>
#include <Ui/Form/mkRootForm.h>
#include <Ui/Widget/mkInput.h>
#include <Ui/Form/mkWidgets.h>
#include <Ui/Form/mkHook.h>

#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkInk.h>

#include <Ui/Style/mkStyleParser.h>

#include <Ui/Widget/mkWidget.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkRootSheet.h>

#include <Ui/Widget/mkButton.h>
#include <Ui/Widget/mkSlider.h>
#include <Ui/Widget/mkScrollbar.h>
#include <Ui/Widget/mkProgressBar.h>
#include <Ui/Widget/mkCheckbox.h>
#include <Ui/Widget/mkTypeIn.h>
#include <Ui/Widget/mkTextbox.h>
#include <Ui/Widget/mkDirectory.h>

#include <Ui/Widget/mkContextMenu.h>

#include <Ui/Scheme/mkDropdown.h>
#include <Ui/Scheme/mkRadioButton.h>
#include <Ui/Scheme/mkExpandbox.h>
#include <Ui/Scheme/mkTree.h>
#include <Ui/Scheme/mkTable.h>
#include <Ui/Scheme/mkTabber.h>
#include <Ui/Scheme/mkDockspace.h>
#include <Ui/Scheme/mkDockbar.h>

#include <Ui/Frame/mkDimString.h>

#include <Ui/mkUiWindow.h>
#include <Ui/mkUiLayout.h>

namespace mk
{
	template <> inline Type& typecls<Dimension>() { static Type ty; return ty; }
	template <> inline Type& typecls<Sizing>() { static Type ty; return ty; }
	template <> inline Type& typecls<Pivot>() { static Type ty; return ty; }
	template <> inline Type& typecls<Flow>() { static Type ty; return ty; }
	template <> inline Type& typecls<Space>() { static Type ty; return ty; }
	template <> inline Type& typecls<Clipping>() { static Type ty; return ty; }
	template <> inline Type& typecls<BoxLayer>() { static Type ty; return ty; }
	template <> inline Type& typecls<Opacity>() { static Type ty; return ty; }
	template <> inline Type& typecls<Weight>() { static Type ty; return ty; }
	template <> inline Type& typecls<FrameType>() { static Type ty; return ty; }
	template <> inline Type& typecls<WidgetState>() { static Type ty; return ty; }
}

#endif // MK_UITYPES_H_INCLUDED
