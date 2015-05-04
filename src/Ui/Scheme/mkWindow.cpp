//  Copyright (c) 2015 Hugo Amiardhugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Scheme/mkWindow.h>

#include <Ui/Scheme/mkDockspace.h>

#include <Ui/Form/mkWidgets.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>
#include <Ui/Frame/mkLayer.h>

#include <Ui/Widget/mkRootSheet.h>
#include <Ui/Widget/mkSlider.h>

#include <iostream>

using namespace std::placeholders;

namespace mk
{
	WindowHeader::WindowHeader(Window& window)
		: Sequence()
		, mWindow(window)
		, mTooltip("Drag me")
		, mTitle(this->makeappend<Label>(mWindow.name()))
	{
		mStyle = &cls();
		if(mWindow.closable())
			mCloseButton = &this->makeappend<CloseButton>(std::bind(&Window::close, &mWindow));
	}

	bool WindowHeader::leftClick(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		mWindow.activate();
		mWindow.frame().layer().moveToTop();
		return true;
	}

	bool WindowHeader::leftDragStart(float xPos, float yPos)
	{
		UNUSED(xPos); UNUSED(yPos);
		if(mWindow.dock())
			mWindow.undock();

		mWindow.frame().layer().setOpacity(VOID);
		mWindow.frame().layer().moveToTop();
		return true;
	}

	bool WindowHeader::leftDrag(float xPos, float yPos, float xDif, float yDif)
	{
		UNUSED(xPos); UNUSED(yPos);
		if(mWindow.movable())
			mWindow.frame().setPosition(mWindow.frame().dposition(DIM_X) + xDif, mWindow.frame().dposition(DIM_Y) + yDif);

		return true;
	}

	bool WindowHeader::leftDragEnd(float xPos, float yPos)
	{
		if(mWindow.dockable())
		{
			Widget* widget = this->rootSheet().pinpoint(xPos, yPos);
			while(widget && &widget->type() != &Docksection::cls())
				widget = widget->parent();

			if(widget)
			{
				Docksection& section = widget->as<Docksection>().docktarget(xPos, yPos);
				mWindow.dock(section);
			}
		}

		mWindow.frame().layer().setOpacity(OPAQUE);
		return true;
	}

	WindowSizer::WindowSizer(Window& window, bool left)
		: Widget()
		, mWindow(window)
		, mResizeLeft(left)
	{
		mStyle = &cls();
	}

	bool WindowSizer::leftDragStart(float xPos, float yPos)
	{
		UNUSED(xPos); UNUSED(yPos);
		mWindow.frame().as<Layer>().moveToTop();
		return true;
	}

	bool WindowSizer::leftDrag(float xPos, float yPos, float xDif, float yDif)
	{
		UNUSED(xPos); UNUSED(yPos);
		if(mResizeLeft)
		{
			mWindow.frame().setPositionDim(DIM_X, mWindow.frame().dposition(DIM_X) + xDif);
			mWindow.frame().setSize(std::max(10.f, mWindow.frame().dsize(DIM_X) - xDif), std::max(25.f, mWindow.frame().dsize(DIM_Y) + yDif));
		}
		else
		{
			mWindow.frame().setSize(std::max(10.f, mWindow.frame().dsize(DIM_X) + xDif), std::max(25.f, mWindow.frame().dsize(DIM_Y) + yDif));
		}
		return true;
	}

	bool WindowSizer::leftDragEnd(float xPos, float yPos)
	{
		UNUSED(xPos); UNUSED(yPos);
		return true;
	}

	WindowSizerLeft::WindowSizerLeft(Window& window)
		: WindowSizer(window, true)
	{
		mStyle = &cls();
	}

	WindowSizerRight::WindowSizerRight(Window& window)
		: WindowSizer(window, false)
	{
		mStyle = &cls();
	}

	WindowFooter::WindowFooter(Window& window)
		: Sheet()
		, mFirstSizer(this->makeappend<WindowSizerLeft>(window))
		, mSecondSizer(this->makeappend<WindowSizerRight>(window))
	{
		mStyle = &cls();
	};

	WindowBody::WindowBody()
		: Sheet()
	{
		mStyle = &cls();
	}

	CloseButton::CloseButton(const Trigger& trigger)
		: Button("", trigger)
	{
		mStyle = &cls();
	}

	Window::Window(const string& title, WindowState state, const Trigger& onClose, Docksection* dock)
		: LayerSheet()
		, mName(title)
		, mWindowState(state)
		, mContent(nullptr)
		, mOnClose(onClose)
		, mDock(dock)
		, mHeader(this->makeappend<WindowHeader>(*this))
		, mBody(this->makeappend<WindowBody>())
		, mFooter(this->makeappend<WindowFooter>(*this))
	{
		mStyle = dock ? &DockWindow::cls() : &Window::cls();
		if(!this->sizable())
			mFooter.hide();
	}

	Window::~Window()
	{}

	void Window::bind(Sheet* parent, size_t index)
	{
		Sheet::bind(parent, index);

		if(!mDock)
		{
			float x = this->rootSheet().frame().dsize(DIM_X) / 2 - mFrame->dsize(DIM_X) / 2;
			float y = this->rootSheet().frame().dsize(DIM_Y) / 2 - mFrame->dsize(DIM_Y) / 2;
			mFrame->setPosition(x, y);
		}
	}

	void Window::toggleWindowState(WindowState state)
	{
		mWindowState = static_cast<WindowState>(mWindowState ^ state);
	}

	void Window::toggleClosable()
	{
		mHeader.closeButton()->frame().visible() ? mHeader.closeButton()->hide() : mHeader.closeButton()->show();
	}

	void Window::toggleMovable()
	{
		this->toggleWindowState(WINDOW_MOVABLE);
	}

	void Window::toggleResizable()
	{
		this->toggleWindowState(WINDOW_SIZABLE);
		this->sizable() ? mFooter.show() : mFooter.hide();
	}

	void Window::showTitlebar()
	{
		mHeader.show();
	}

	void Window::hideTitlebar()
	{
		mHeader.hide();
	}

	const string& Window::name()
	{
		return mContent ? mContent->name() : mName;
	}

	void Window::dock(Docksection& docksection)
	{
		std::cerr << ">>>>>>>>>>>  Window :: dock" << std::endl;
		this->docked();
		mDock = &docksection;
		docksection.dock(*this);
	}

	void Window::docked()
	{
		this->resetStyle(&DockWindow::cls());
		this->toggleMovable();
		this->toggleResizable();
	}

	void Window::undock()
	{
		std::cerr << ">>>>>>>>>>>  Window :: undock" << std::endl;
		mDock->undock(*this);
		mDock = nullptr;
		this->undocked();
	}

	void Window::undocked()
	{
		this->resetStyle(&Window::cls());
		this->toggleMovable();
		this->toggleResizable();

		mFrame->setPosition(mFrame->dabsolute(DIM_X), mFrame->dabsolute(DIM_Y));
		mFrame->as<Layer>().moveToTop();
	}
	
	void Window::close()
	{
		if(mOnClose)
			mOnClose(*this);
		this->remove();
	}

	Widget& Window::vappend(unique_ptr<Widget> widget)
	{
		mHeader.title().setLabel(widget->name());
		mContent = widget.get();
		return mBody.append(std::move(widget));
	}

	bool Window::leftClick(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		if(!mDock)
			mFrame->as<Layer>().moveToTop();
		return true;
	}

	bool Window::rightClick(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		if(!mDock)
			mFrame->as<Layer>().moveToTop();
		return true;
	}

	WindowForm::WindowForm(unique_ptr<Form> content, const string& title, WindowState state, const Widget::Trigger& onClose)
		: Form(make_unique<Window>(title, state, onClose))
	{
		this->append(std::move(content));
	}
}
