//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_UI_TYPES_H
#define TOY_UI_TYPES_H

#include <toyobj/Types.h>

#include <toyui/Widget/Input.h>
#include <toyui/Widget/Widgets.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Caption.h>
#include <toyui/Frame/Stencil.h>

#include <toyui/Style/StyleParser.h>

#include <toyui/Widget/Widget.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Widget/RootSheet.h>
#include <toyui/Widget/Cursor.h>

#include <toyui/Widget/Button.h>
#include <toyui/Widget/Slider.h>
#include <toyui/Widget/Scrollbar.h>
#include <toyui/Widget/ProgressBar.h>
#include <toyui/Widget/Checkbox.h>
#include <toyui/Widget/TypeIn.h>
#include <toyui/Widget/Textbox.h>
#include <toyui/Widget/Directory.h>

#include <toyui/Widget/ContextMenu.h>

#include <toyui/Scheme/Dropdown.h>
#include <toyui/Scheme/RadioButton.h>
#include <toyui/Scheme/Expandbox.h>
#include <toyui/Scheme/Tree.h>
#include <toyui/Scheme/Table.h>
#include <toyui/Scheme/Tabber.h>
#include <toyui/Scheme/Dockspace.h>
#include <toyui/Scheme/Dockbar.h>
#include <toyui/Scheme/Window.h>
#include <toyui/Scheme/Node.h>

#include <toyui/Frame/DimString.h>

#include <toyui/Device/Hook.h>

#include <toyui/UiWindow.h>
#include <toyui/UiLayout.h>

namespace toy
{
	template <> inline Type& typecls<Dimension>() { static Type ty; return ty; }
	template <> inline Type& typecls<Sizing>() { static Type ty; return ty; }
	template <> inline Type& typecls<Pivot>() { static Type ty; return ty; }
	template <> inline Type& typecls<Align>() { static Type ty; return ty; }
	template <> inline Type& typecls<Flow>() { static Type ty; return ty; }
	template <> inline Type& typecls<Space>() { static Type ty; return ty; }
	template <> inline Type& typecls<Clipping>() { static Type ty; return ty; }
	template <> inline Type& typecls<BoxLayer>() { static Type ty; return ty; }
	template <> inline Type& typecls<Opacity>() { static Type ty; return ty; }
	template <> inline Type& typecls<Weight>() { static Type ty; return ty; }
	template <> inline Type& typecls<FrameType>() { static Type ty; return ty; }
	template <> inline Type& typecls<WidgetState>() { static Type ty; return ty; }
}

#endif // TOY_UI_TYPES_H
