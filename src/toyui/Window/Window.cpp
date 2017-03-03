//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Window/Window.h>

#include <toyui/Window/Dockspace.h>

#include <toyui/Widget/Layout.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>
#include <toyui/Frame/Layer.h>

#include <toyui/Widget/RootSheet.h>
#include <toyui/Button/Slider.h>

#include <toyui/Input/InputDevice.h>

using namespace std::placeholders;

namespace toy
{
	Popup::Popup(Wedge& parent)
		: Overlay(parent, cls())
	{
		float x = this->rootSheet().mouse().lastX() - m_parent->frame().left();
		float y = this->rootSheet().mouse().lastY() - m_parent->frame().top();
		m_frame->setPosition(x, y);

		this->takeControl(CM_MODAL);
	}

	void Popup::leftClick(MouseEvent& mouseEvent)
	{
		mouseEvent.abort = true;
		this->yieldControl();
		this->as<Widget>().remove();
	}

	void Popup::rightClick(MouseEvent& mouseEvent)
	{
		mouseEvent.abort = true;
		this->yieldControl();
		this->as<Widget>().remove();
	}

	WindowHeader::WindowHeader(Window& window)
		: WrapControl(window, cls())
		, m_window(window)
		, m_tooltip("Drag me")
		, m_title(*this, m_window.name())
		, m_close(*this, std::bind(&Window::close, &m_window))
	{
		if(!m_window.closable())
			m_close.hide();
	}

	void WindowHeader::leftClick(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		m_window.activate();
		if(!m_window.dock()) // crashes for some reason
			m_window.frame().layer().moveToTop();
	}

	void WindowHeader::leftDragStart(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		if(m_window.dock())
			m_window.undock();

		m_window.frame().layer().moveToTop();
		//m_window.frame().layer().setOpacity(HOLLOW);
	}

	void WindowHeader::leftDrag(MouseEvent& mouseEvent)
	{
		if(m_window.movable())
			m_window.frame().setPosition(m_window.frame().dposition(DIM_X) + mouseEvent.deltaX, m_window.frame().dposition(DIM_Y) + mouseEvent.deltaY);
	}

	void WindowHeader::leftDragEnd(MouseEvent& mouseEvent)
	{
		if(m_window.dockable())
		{
			Docksection* target = this->docktarget(mouseEvent.relativeX, mouseEvent.relativeY);
			if(target)
				m_window.dock(*target);
		}

		//m_window.frame().layer().setOpacity(OPAQUE);
	}

	Docksection* WindowHeader::docktarget(float x, float y)
	{
		Widget* widget = this->rootSheet().pinpoint(x, y);
		while(widget && &widget->type() != &Docksection::cls())
			widget = widget->parent();

		if(widget)
			return &widget->as<Docksection>().docktarget(x, y);
		else
			return nullptr;
	}

	WindowSizer::WindowSizer(Wedge& parent, Window& window, Type& type, bool left)
		: Control(parent, type)
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

	WindowSizerLeft::WindowSizerLeft(Wedge& parent, Window& window)
		: WindowSizer(parent, window, cls(), true)
	{}

	WindowSizerRight::WindowSizerRight(Wedge& parent, Window& window)
		: WindowSizer(parent, window, cls(), false)
	{}

	WindowFooter::WindowFooter(Window& window)
		: WrapControl(window, cls())
		, m_firstSizer(*this, window)
		, m_secondSizer(*this, window)
	{}

	WindowBody::WindowBody(Wedge& parent)
		: ScrollContainer(parent, cls())
	{}

	CloseButton::CloseButton(Wedge& parent, const Trigger& trigger)
		: Button(parent, "", trigger, cls())
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

	Window::Window(Wedge& parent, const string& title, WindowState state, const Trigger& onClose, Docksection* dock, Type& type)
		: Overlay(parent, type)
		, m_name(title)
		, m_windowState(state)
		, m_content(nullptr)
		, m_onClose(onClose)
		, m_dock(dock)
		, m_header(*this)
		, m_body(*this)
		, m_footer(*this)
	{
		if(!this->sizable())
			m_footer.hide();

		if(&type == &Window::cls())
		{
			m_frame->setFixedSize(DIM_X, 480.f);
			m_frame->setFixedSize(DIM_Y, 350.f);
		}

		if(!m_dock)
		{
			float x = (m_parent->frame().dsize(DIM_X) - m_frame->dsize(DIM_X)) / 2.f;
			float y = (m_parent->frame().dsize(DIM_Y) - m_frame->dsize(DIM_Y)) / 2.f;
			m_frame->setPosition(x, y);
		}
	}

	void Window::toggleWindowState(WindowState state)
	{
		m_windowState = static_cast<WindowState>(m_windowState ^ state);
	}

	void Window::toggleClosable()
	{
		m_header.close().frame().hidden() ? m_header.close().show() : m_header.close().hide();
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

	void Window::toggleWrap()
	{
		this->toggleWindowState(WINDOW_SHRINK);
		this->shrink() ? m_body.enableWrap() : m_body.disableWrap();
		this->shrink() ? this->setStyle(WrapWindow::cls()) : this->setStyle(Window::cls());
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
		this->docked();
		m_dock = &docksection;
		docksection.dock(*this);
	}

	void Window::docked()
	{
		this->setStyle(DockWindow::cls());
		this->toggleMovable();
		this->toggleResizable();
	}

	void Window::undock()
	{
		m_dock->undock(*this);
		m_dock = nullptr;
		this->undocked();
	}

	void Window::undocked()
	{
		this->setStyle(Window::cls());
		this->toggleMovable();
		this->toggleResizable();

		DimFloat absolute = m_frame->absolutePosition();
		m_frame->setPosition(absolute[DIM_X], absolute[DIM_Y]);
		m_frame->as<Layer>().moveToTop();
	}
	
	void Window::close()
	{
		if(m_onClose)
			m_onClose(*this);
		this->as<Widget>().remove();
	}

	Container& Window::emplaceContainer()
	{
		return m_body.emplaceContainer();
	}

	void Window::handleAdd(Widget& content)
	{
		m_header.title().setLabel(content.name());
		m_content = &content;
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
