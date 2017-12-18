//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/UiLayout.h>

#include <toyui/UiWindow.h>

#include <toyui/Bundle.h>

namespace toy
{
	Styler::Styler(UiWindow& uiWindow)
		: m_uiWindow(uiWindow)
	{
		Widget::styles();
		Cursor::styles();
		Scrollbar::styles();
		Dropdown::styles();
		Expandbox::styles();
		TreeNode::styles();
		Tabber::styles();
		Menu::styles();
		Toolbar::styles();
		Window::styles();
		Dockspace::styles();
		Docker::styles();
		Canvas::styles();
		Node::styles();
	}

	void Styler::clear()
	{
		m_layout_definitions = {};
		m_skin_definitions = {};
	}

	void Styler::setup()
	{
		for(auto& kv : Widget::s_styles)
			kv.second->load(m_layout_definitions, m_skin_definitions);

		m_uiWindow.m_rootSheet->visit([](Widget& widget, bool&) {
			widget.frame().updateStyle(true);
		});
	}

	Styles::Styles()
	{}

	void Styles::setup(UiWindow& uiWindow)
	{
		Widget::styles().scrollplan_surface.m_skin.m_customRenderer = &drawGrid;
		
		Cursor::styles().cursor.m_skin.m_image = &uiWindow.findImage("mousepointer");

		Cursor::styles().resize_x.m_skin.m_image = &uiWindow.findImage("resize_h_20");
		Cursor::styles().resize_y.m_skin.m_image = &uiWindow.findImage("resize_v_20");
		Cursor::styles().move.m_skin.m_image = &uiWindow.findImage("move_20");
		Cursor::styles().resize_diag_left.m_skin.m_image = &uiWindow.findImage("resize_diag_left_20");
		Cursor::styles().resize_diag_right.m_skin.m_image = &uiWindow.findImage("resize_diag_right_20");
		Cursor::styles().caret.m_skin.m_image = &uiWindow.findImage("caret_white");

		Toolbar::styles().mover.m_skin.m_image = &uiWindow.findImage("handle");
	}
}
