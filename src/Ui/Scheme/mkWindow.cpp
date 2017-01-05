//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Scheme/mkWindow.h>

#include <Ui/Scheme/mkDockspace.h>

#include <Ui/Widget/mkWidgets.h>

#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>
#include <Ui/Frame/mkLayer.h>

#include <Ui/Widget/mkRootSheet.h>
#include <Ui/Widget/mkSlider.h>

#include <iostream>

using namespace std::placeholders;

namespace mk
{
	Popup::Popup()
		: LayerSheet(cls())
	{}

	void Popup::bound()
	{
		float x = uiWindow().mouse().lastX() - m_parent->frame().left();
		float y = uiWindow().mouse().lastY() - m_parent->frame().top();
		m_frame->setPosition(x, y);

		this->takeControl(CM_MODAL);
	}

	void Popup::leftClick(MouseEvent& mouseEvent)
	{
		mouseEvent.abort = true;
		this->yieldControl();
		this->remove();
	}

	void Popup::rightClick(MouseEvent& mouseEvent)
	{
		mouseEvent.abort = true;
		this->yieldControl();
		this->remove();
	}

	WindowHeader::WindowHeader(Window& window)
		: Band(cls())
		, m_window(window)
		, m_tooltip("Drag me")
		, m_title(this->makeappend<Label>(m_window.name()))
	{
		if(m_window.closable())
			m_closeButton = &this->makeappend<CloseButton>(std::bind(&Window::close, &m_window));
	}

	void WindowHeader::leftClick(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		m_window.activate();
		m_window.frame().layer().moveToTop();
	}

	void WindowHeader::leftDragStart(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		if(m_window.dock())
			m_window.undock();

		m_window.frame().layer().moveToTop();
	}

	void WindowHeader::leftDrag(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		if(m_window.movable())
			m_window.frame().setPosition(m_window.frame().dposition(DIM_X) + mouseEvent.deltaX, m_window.frame().dposition(DIM_Y) + mouseEvent.deltaY);
	}

	void WindowHeader::leftDragEnd(MouseEvent& mouseEvent)
	{
		m_window.frame().layer().setOpacity(HOLLOW);

		if(m_window.dockable())
		{
			Widget* widget = this->rootSheet().pinpoint(mouseEvent.posX, mouseEvent.posY);
			while(widget && &widget->type() != &Docksection::cls())
				widget = widget->parent();

			if(widget)
			{
				Docksection& section = widget->as<Docksection>().docktarget(mouseEvent.posX, mouseEvent.posY);
				m_window.dock(section);
			}
		}

		m_window.frame().layer().setOpacity(OPAQUE);
	}

	WindowSizer::WindowSizer(Window& window, StyleType& type, bool left)
		: Widget(type)
		, m_window(window)
		, m_resizeLeft(left)
	{}

	void WindowSizer::leftDragStart(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		m_window.frame().as<Layer>().moveToTop();
	}

	void WindowSizer::leftDrag(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		if(m_resizeLeft)
		{
			m_window.frame().setPositionDim(DIM_X, m_window.frame().dposition(DIM_X) + mouseEvent.deltaX);
			m_window.frame().setSize(std::max(10.f, m_window.frame().dsize(DIM_X) - mouseEvent.deltaX), std::max(25.f, m_window.frame().dsize(DIM_Y) + mouseEvent.deltaY));
		}
		else
		{
			m_window.frame().setSize(std::max(10.f, m_window.frame().dsize(DIM_X) + mouseEvent.deltaX), std::max(25.f, m_window.frame().dsize(DIM_Y) + mouseEvent.deltaY));
		}
	}

	void WindowSizer::leftDragEnd(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
	}

	WindowSizerLeft::WindowSizerLeft(Window& window)
		: WindowSizer(window, cls(), true)
	{}

	WindowSizerRight::WindowSizerRight(Window& window)
		: WindowSizer(window, cls(), false)
	{}

	WindowFooter::WindowFooter(Window& window)
		: Sheet(cls())
		, m_firstSizer(this->makeappend<WindowSizerLeft>(window))
		, m_secondSizer(this->makeappend<WindowSizerRight>(window))
	{}

	WindowBody::WindowBody()
		: Sheet(cls())
	{}

	CloseButton::CloseButton(const Trigger& trigger)
		: Button("", trigger, cls())
	{}

	void CloseButton::leftClick(MouseEvent& mouseEvent)
	{
		Button::leftClick(mouseEvent);
		mouseEvent.abort = true;
	}

	void CloseButton::rightClick(MouseEvent& mouseEvent)
	{
		Button::rightClick(mouseEvent);
		mouseEvent.abort = true;
	}

	Window::Window(const string& title, WindowState state, const Trigger& onClose, Docksection* dock, StyleType& type)
		: LayerSheet(type)
		, m_name(title)
		, m_windowState(state)
		, m_content(nullptr)
		, m_onClose(onClose)
		, m_dock(dock)
		, m_header(this->makeappend<WindowHeader>(*this))
		, m_body(this->makeappend<WindowBody>())
		, m_footer(this->makeappend<WindowFooter>(*this))
	{
		//m_style = dock ? &DockWindow::cls() : &Window::cls();
		if(!this->sizable())
			m_footer.hide();
	}

	Window::~Window()
	{}

	void Window::bind(Sheet& parent, size_t index)
	{
		Sheet::bind(parent, index);

		if(!m_dock)
		{
			float x = this->rootSheet().frame().dsize(DIM_X) / 2 - m_frame->dsize(DIM_X) / 2;
			float y = this->rootSheet().frame().dsize(DIM_Y) / 2 - m_frame->dsize(DIM_Y) / 2;
			m_frame->setPosition(x, y);
		}
	}

	void Window::toggleWindowState(WindowState state)
	{
		m_windowState = static_cast<WindowState>(m_windowState ^ state);
	}

	void Window::toggleClosable()
	{
		m_header.closeButton()->frame().hidden() ? m_header.closeButton()->show() : m_header.closeButton()->hide();
	}

	void Window::toggleMovable()
	{
		this->toggleWindowState(WINDOW_MOVABLE);
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

	const string& Window::name()
	{
		return m_content ? m_content->name() : m_name;
	}

	void Window::dock(Docksection& docksection)
	{
		std::cerr << ">>>>>>>>>>>  Window :: dock" << std::endl;
		this->docked();
		m_dock = &docksection;
		docksection.dock(*this);
	}

	void Window::docked()
	{
		this->resetStyle(DockWindow::cls());
		this->toggleMovable();
		this->toggleResizable();
	}

	void Window::undock()
	{
		std::cerr << ">>>>>>>>>>>  Window :: undock" << std::endl;
		m_dock->undock(*this);
		m_dock = nullptr;
		this->undocked();
	}

	void Window::undocked()
	{
		this->resetStyle(Window::cls());
		this->toggleMovable();
		this->toggleResizable();

		m_frame->setPosition(m_frame->dabsolute(DIM_X), m_frame->dabsolute(DIM_Y));
		m_frame->as<Layer>().moveToTop();
	}
	
	void Window::close()
	{
		if(m_onClose)
			m_onClose(*this);
		this->remove();
	}

	Widget& Window::vappend(unique_ptr<Widget> widget)
	{
		m_header.title().setLabel(widget->name());
		m_content = widget.get();
		return m_body.append(std::move(widget));
	}

	void Window::leftClick(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		if(!m_dock)
			m_frame->as<Layer>().moveToTop();
	}

	void Window::rightClick(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		if(!m_dock)
			m_frame->as<Layer>().moveToTop();
	}
}
