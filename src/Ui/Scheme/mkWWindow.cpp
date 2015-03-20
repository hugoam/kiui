//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Scheme/mkWWindow.h>

#include <Ui/Scheme/mkWDockspace.h>

#include <Ui/Form/mkWidgets.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>
#include <Ui/Frame/mkLayer.h>
#include <Ui/Frame/mkGrid.h>

#include <Ui/Widget/mkRootSheet.h>

#include <iostream>

using namespace std::placeholders;

namespace mk
{
	WWindowHeader::WWindowHeader()
		: Sheet(styleCls())
	{}

	WWindowBody::WWindowBody()
		: Sheet(styleCls())
	{}

	WCloseButton::WCloseButton(const Trigger& trigger)
		: WButton("", styleCls(), trigger)
	{}

	WWindow::WWindow(const Trigger& onClose, string title, bool closable, bool dockable, WDocksection* dock)
		//: Sheet(dock ? style + "window dockwindow" : style + "window window")
		: Sheet(dock ? WDockWindow::styleCls() : WWindow::styleCls())
		, mName(title)
		, mClosable(closable)
		, mDockable(dockable)
		, mMovable(false)
		, mSizable(false)
		, mContent(nullptr)
		, mOnClose(onClose)
		, mDragging(false)
		, mResizing(false)
		, mDock(dock)
	{}

	WWindow::~WWindow()
	{}

	void WWindow::build()
	{
		Sheet::build();
		mHeader = this->makeappend<WWindowHeader>();
		mBody = this->makeappend<WWindowBody>();
		mTitle = mHeader->makeappend<WLabel>(mName);
		mCloseButton = mClosable ? mHeader->makeappend<WCloseButton>(std::bind(&WWindow::close, this)) : nullptr;

		if(!mDock)
		{
			float x = this->rootSheet()->frame()->dsize(DIM_X) / 2 - mFrame->dsize(DIM_X) / 2;
			float y = this->rootSheet()->frame()->dsize(DIM_Y) / 2 - mFrame->dsize(DIM_Y) / 2;
			mFrame->setPosition(x, y);
		}
	}

	void WWindow::setClosable()
	{
		mCloseButton->show();
	}

	void WWindow::setUnclosable()
	{
		mCloseButton->hide();
	}

	void WWindow::setScrollable()
	{
	}

	void WWindow::setUnscrollable()
	{
	}

	void WWindow::setMovable()
	{
		mMovable = true;
	}

	void WWindow::setUnmovable()
	{
		mMovable = false;
	}

	void WWindow::setResizable()
	{
		mSizable = true;
	}

	void WWindow::setUnsizable()
	{
		mSizable = false;
	}

	void WWindow::showTitlebar()
	{
		mHeader->show();
	}

	void WWindow::hideTitlebar()
	{
		mHeader->hide();
	}

	const string& WWindow::name()
	{
		return mContent ? mContent->name() : mName;
	}

	void WWindow::dock(WDocksection* docksection)
	{
		std::cerr << ">>>>>>>>>>>  Window :: dock" << std::endl;
		this->reset(WDockWindow::styleCls());
		docksection->dock(this);
		mDock = docksection;
	}

	void WWindow::undock()
	{
		std::cerr << ">>>>>>>>>>>  Window :: undock" << std::endl;

		this->reset(WWindow::styleCls());
		mDock->undock(this);
		mDock = nullptr;

		mFrame->setPosition(mFrame->dabsolute(DIM_X), mFrame->dabsolute(DIM_Y));
		mFrame->as<Layer>()->moveToTop();
		mDragging = true;
	}
	
	void WWindow::close()
	{
		if(mOnClose)
			mOnClose(this);
		this->destroy();
	}

	Widget* WWindow::vappend(unique_ptr<Widget> widget)
	{
		mTitle->setLabel(widget->name());
		mContent = widget.get();
		return mBody->append(std::move(widget));
	}

	bool WWindow::leftDragStart(float xPos, float yPos)
	{
		if(mDockable && mDock)
			this->undock();
		else if(mSizable && (yPos - mFrame->dabsolute(DIM_Y) > mFrame->dsize(DIM_Y) * 0.8f && xPos - mFrame->dabsolute(DIM_X) > mFrame->dsize(DIM_X) * 0.8f))
			mResizing = true;
		else if(mMovable)
			mDragging = true;

		if(mDragging)
			mFrame->as<Layer>()->moveToTop();

		return true;
	}

	bool WWindow::leftDrag(float xPos, float yPos, float xDif, float yDif)
	{
		UNUSED(xPos); UNUSED(yPos);
		if(mDragging)
			mFrame->setPosition(mFrame->dposition(DIM_X) + xDif, mFrame->dposition(DIM_Y) + yDif);
		else if(mResizing)
			mFrame->setSize(mFrame->dsize(DIM_X) + xDif, mFrame->dsize(DIM_Y) + yDif);

		return true;
	}

	bool WWindow::leftDragEnd(float xPos, float yPos)
	{
		if(mDockable)
		{
			Widget* widget = this->rootSheet()->pinpoint(xPos, yPos);
			while(widget && widget->type() != WDocksection::cls())
				widget = widget->parent();

			if(widget)
			{
				WDocksection* section = widget->as<WDocksection>()->docktarget(xPos, yPos);
				this->dock(section);
			}
		}

		mDragging = false;
		mResizing = false;

		return true;
	}

	bool WWindow::leftClick(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		mFrame->as<Layer>()->moveToTop();
		return true;
	}

	bool WWindow::rightClick(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		mFrame->as<Layer>()->moveToTop();
		return true;
	}

	Window::Window(unique_ptr<Form> content, bool closable, bool dockable, const Trigger& onClose)
		: Form(nullptr, "", [this, closable, dockable]() { return make_unique<WWindow>(std::bind(&Window::onClose, this, _1), this->name(), closable, dockable); })
		, mOnClose(onClose)
	{
		this->append(std::move(content));
	}

	void Window::onClose(Widget* widget)
	{
		mOnClose(widget->form());
	}
}
