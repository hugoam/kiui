//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_UI_TYPES_H
#define TOY_UI_TYPES_H

#include <toyobj/Types.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>
#include <toyui/Frame/Grid.h>

#include <toyui/Render/Caption.h>
#include <toyui/Render/Stencil.h>

#include <toyui/Style/StyleParser.h>

#include <toyui/Widget/Widget.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Widget/RootSheet.h>
#include <toyui/Widget/Cursor.h>
#include <toyui/Widget/Layout.h>

#include <toyui/Button/Button.h>
#include <toyui/Button/Image.h>
#include <toyui/Button/Slider.h>
#include <toyui/Button/Scrollbar.h>
#include <toyui/Button/ProgressBar.h>
#include <toyui/Button/Checkbox.h>
#include <toyui/Button/Dropdown.h>
#include <toyui/Button/Typedown.h>
#include <toyui/Button/RadioButton.h>
#include <toyui/Button/Filter.h>

#include <toyui/Edit/TypeIn.h>
#include <toyui/Edit/Textbox.h>
#include <toyui/Edit/Input.h>

#include <toyui/Window/ContextMenu.h>

#include <toyui/Container/Expandbox.h>
#include <toyui/Container/Tree.h>
#include <toyui/Container/Table.h>
#include <toyui/Container/Tabber.h>

#include <toyui/Container/Directory.h>

#include <toyui/Window/Dockspace.h>
#include <toyui/Window/Dockbar.h>
#include <toyui/Window/Window.h>
#include <toyui/Window/Node.h>
#include <toyui/Window/Menu.h>
#include <toyui/Window/Toolbar.h>

#include <toyui/Frame/DimString.h>

#include <toyui/UiWindow.h>
#include <toyui/UiLayout.h>

namespace toy
{
	template <> inline Type& typecls<AutoLayout>() { static Type ty; return ty; }
	template <> inline Type& typecls<Dimension>() { static Type ty; return ty; }
	template <> inline Type& typecls<Direction>() { static Type ty; return ty; }
	template <> inline Type& typecls<Sizing>() { static Type ty; return ty; }
	template <> inline Type& typecls<Pivot>() { static Type ty; return ty; }
	template <> inline Type& typecls<Align>() { static Type ty; return ty; }
	template <> inline Type& typecls<Flow>() { static Type ty; return ty; }
	template <> inline Type& typecls<Space>() { static Type ty; return ty; }
	template <> inline Type& typecls<Clipping>() { static Type ty; return ty; }
	template <> inline Type& typecls<BoxLayer>() { static Type ty; return ty; }
	template <> inline Type& typecls<Opacity>() { static Type ty; return ty; }
	template <> inline Type& typecls<FrameType>() { static Type ty; return ty; }
	template <> inline Type& typecls<WidgetState>() { static Type ty; return ty; }
}

#endif // TOY_UI_TYPES_H
