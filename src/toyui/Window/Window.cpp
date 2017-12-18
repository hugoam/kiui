//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Window/Window.h>

#include <toyui/Frame/Layer.h>

#include <toyui/Widget/RootSheet.h>
#include <toyui/Window/Dockspace.h>

namespace toy
{
	WindowHeader::WindowHeader(Window& window)
		: Wedge({ &window, &cls<WindowHeader>() })
		, m_window(window)
		, m_title({ this, &styles().title }, m_window.m_name)
		, m_close({ this, &Window::styles().close_button }, "", [&](Widget&) { window.close(); })
		, m_tooltip("Drag me")
	{
		if(!m_window.closable())
			m_close.hide();
		if(m_window.movable())
			this->setStyle(Window::styles().header_movable);
	}

	bool WindowHeader::leftClick(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		m_window.enableState(ACTIVATED);
		if(!m_window.m_dock) // crashes for some reason
			m_window.frame().layer().moveToTop();
		return true;
	}

	bool WindowHeader::leftDragStart(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		if(m_window.m_dock)
			m_window.undock();

		m_window.frame().layer().moveToTop();
		m_window.frame().layer().m_opacity = HOLLOW;
		return true;
	}

	bool WindowHeader::leftDrag(MouseEvent& mouseEvent)
	{
		if(m_window.movable())
			m_window.frame().setPosition(m_window.frame().d_position + mouseEvent.delta);
		return true;
	}

	bool WindowHeader::leftDragEnd(MouseEvent& mouseEvent)
	{
		if(m_window.dockable())
			m_window.dockAt(mouseEvent.pos);

		m_window.frame().layer().m_opacity = OPAQUE;
		return true;
	}

	WindowSizer::WindowSizer(const Params& params, Window& window, bool left)
		: Widget({ params, &cls<WindowSizer>() })
		, m_window(window)
		, m_resizeLeft(left)
	{}

	bool WindowSizer::leftDragStart(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		as<Layer>(m_window.frame()).moveToTop();
		return true;
	}

	bool WindowSizer::leftDrag(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		if(m_resizeLeft)
			m_window.frame().setPositionDim(DIM_X, m_window.frame().d_position.x + mouseEvent.delta.x);
		if(m_resizeLeft)
			m_window.frame().setSize({ std::max(50.f, m_window.frame().m_size.x - mouseEvent.delta.x), std::max(50.f, m_window.frame().m_size.y + mouseEvent.delta.y) });
		else
			m_window.frame().setSize({ std::max(50.f, m_window.frame().m_size.x + mouseEvent.delta.x), std::max(50.f, m_window.frame().m_size.y + mouseEvent.delta.y) });
		return true;
	}

	WindowFooter::WindowFooter(Window& window)
		: Wedge({ &window, &cls<WindowFooter>() })
		, m_firstSizer({ this, &Window::styles().sizer_left }, window, true)
		, m_secondSizer({ this, &Window::styles().sizer_right }, window, false)
	{}

	Window::Window(const Params& params, const string& title, WindowState state, const Callback& onClose, Docksection* dock)
		: Wedge({ params, &cls<Window>(), LAYER })
		, m_name(title)
		, m_windowState(state)
		, m_onClose(onClose)
		, m_header(*this)
		, m_body({ this, &styles().body })
		, m_footer(*this)
		, m_dock(dock)
	{
		if(!this->sizable())
			m_footer.hide();

		if(&m_type == &cls<Window>())
		//if(!m_dock)
			m_frame->setSize({ 480.f, 350.f });

		if(!m_dock)
			m_frame->setPosition((m_parent->frame().m_size - m_frame->m_size) / 2.f);
		else
			this->toggleDocked();
	}

	void Window::toggleWindowState(WindowState state)
	{
		m_windowState = static_cast<WindowState>(m_windowState ^ state);
	}

	void Window::toggleClosable()
	{
		this->toggleWindowState(WINDOW_CLOSABLE);
		this->closable() ? m_header.m_close.show() : m_header.m_close.hide();
	}
	
	void Window::toggleHeader()
	{
		this->toggleWindowState(WINDOW_MOVABLE);
		this->movable() ? m_header.show() : m_header.hide();
	}

	void Window::toggleMovable()
	{
		this->toggleWindowState(WINDOW_MOVABLE);
		this->movable() ? m_header.setStyle(styles().header_movable) : m_header.setStyle(styles().header);
	}

	void Window::toggleResizable()
	{
		this->toggleWindowState(WINDOW_SIZABLE);
		this->sizable() ? m_footer.show() : m_footer.hide();
	}

	void Window::showTitlebar()
	{
		m_header.show();
	}

	void Window::hideTitlebar()
	{
		m_header.hide();
	}

	void Window::dockAt(const DimFloat& pos)
	{
		Widget* target = this->rootSheet().pinpoint(pos);
		Docksection* docksection = target->findContainer<Docksection>();
		if(docksection)
			this->dock(docksection->docktarget(pos));
	}

	void Window::dock(Docksection& docksection)
	{
		docksection.dock(*this);
		m_dock = &docksection;
		this->toggleDocked();
	}

	void Window::undock()
	{
		DimFloat absolute = m_frame->absolutePosition();

		m_dock->undock(*this);
		m_dock = nullptr;

		m_frame->setPosition(absolute);
		as<Layer>(*m_frame).moveToTop();

		this->toggleDocked();
	}

	void Window::toggleDocked()
	{
		m_dock ? this->setStyle(styles().dock_window) : this->setStyle(styles().window);
		//this->toggleMovable();
		this->toggleHeader();
		this->toggleResizable();
	}

	void Window::close()
	{
		if(m_dock)
			this->undock();
		if(m_onClose)
			m_onClose(*this);
		this->extract();
	}

	bool Window::leftClick(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		if(!m_dock)
			as<Layer>(*m_frame).moveToTop();
		return true;
	}

	bool Window::rightClick(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		if(!m_dock)
			as<Layer>(*m_frame).moveToTop();
		return true;
	}
}
