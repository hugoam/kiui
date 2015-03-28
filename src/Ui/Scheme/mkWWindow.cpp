//  Copyright (c) 2015 Hugo Amiardhugo.amiard@laposte.net
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

#include <Ui/Widget/mkRootSheet.h>

#include <iostream>

using namespace std::placeholders;

namespace mk
{
	WWindowHeader::WWindowHeader(WWindow* window)
		: Sheet(styleCls())
		, mWindow(window)
	{}

	void WWindowHeader::build()
	{
		mTitle = this->makeappend<WLabel>(mWindow->name());
		this->makeappend<Widget>(DivX::styleCls());
		mCloseButton = mWindow->closable() ? this->makeappend<WCloseButton>(std::bind(&WWindow::close, mWindow)) : nullptr;
	}

	bool WWindowHeader::leftDragStart(float xPos, float yPos)
	{
		UNUSED(xPos); UNUSED(yPos);
		if(mWindow->dock())
			mWindow->undock();

		mWindow->frame()->as<Layer>()->moveToTop();
		return true;
	}

	bool WWindowHeader::leftDrag(float xPos, float yPos, float xDif, float yDif)
	{
		UNUSED(xPos); UNUSED(yPos);
		if(mWindow->movable())
			mWindow->frame()->setPosition(mWindow->frame()->dposition(DIM_X) + xDif, mWindow->frame()->dposition(DIM_Y) + yDif);

		return true;
	}

	bool WWindowHeader::leftDragEnd(float xPos, float yPos)
	{
		if(mWindow->dockable())
		{
			Widget* widget = this->rootSheet()->pinpoint(xPos, yPos);
			while(widget && widget->type() != WDocksection::cls())
				widget = widget->parent();

			if(widget)
			{
				WDocksection* section = widget->as<WDocksection>()->docktarget(xPos, yPos);
				mWindow->dock(section);
			}
		}

		return true;
	}

	WWindowSizer::WWindowSizer(WWindow* window)
		: Sheet(styleCls())
		, mWindow(window)
		, mResizeLeft(false)
	{}

	bool WWindowSizer::leftDragStart(float xPos, float yPos)
	{
		UNUSED(yPos);
		mWindow->frame()->as<Layer>()->moveToTop();
		if(xPos - mWindow->frame()->dabsolute(DIM_X) > mWindow->frame()->dsize(DIM_X) * 0.5f)
			mResizeLeft = false;
		else
			mResizeLeft = true;
		return true;
	}

	bool WWindowSizer::leftDrag(float xPos, float yPos, float xDif, float yDif)
	{
		UNUSED(xPos); UNUSED(yPos);
		if(mResizeLeft)
		{
			mWindow->frame()->setPositionDim(DIM_X, mWindow->frame()->dposition(DIM_X) + xDif);
			mWindow->frame()->setSize(std::max(10.f, mWindow->frame()->dsize(DIM_X) - xDif), std::max(25.f, mWindow->frame()->dsize(DIM_Y) + yDif));
		}
		else
		{
			mWindow->frame()->setSize(std::max(10.f, mWindow->frame()->dsize(DIM_X) + xDif), std::max(25.f, mWindow->frame()->dsize(DIM_Y) + yDif));
		}
		return true;
	}

	bool WWindowSizer::leftDragEnd(float xPos, float yPos)
	{
		UNUSED(xPos); UNUSED(yPos);
		return true;
	}

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
		, mMovable(true)
		, mSizable(true)
		, mContent(nullptr)
		, mOnClose(onClose)
		, mDock(dock)
	{}

	WWindow::~WWindow()
	{}

	void WWindow::build()
	{
		Sheet::build();
		mHeader = this->makeappend<WWindowHeader>(this);
		mBody = this->makeappend<WWindowBody>();
		mFooter = this->makeappend<WWindowSizer>(this);

		if(!mDock)
		{
			float x = this->rootSheet()->frame()->dsize(DIM_X) / 2 - mFrame->dsize(DIM_X) / 2;
			float y = this->rootSheet()->frame()->dsize(DIM_Y) / 2 - mFrame->dsize(DIM_Y) / 2;
			mFrame->setPosition(x, y);
		}
	}

	void WWindow::toggleClosable()
	{
		mHeader->closeButton()->frame()->visible() ? mHeader->closeButton()->hide() : mHeader->closeButton()->show();
	}

	void WWindow::toggleMovable()
	{
		mMovable = !mMovable;
	}

	void WWindow::toggleResizable()
	{
		mSizable = !mSizable;
		mSizable ? mFooter->show() : mFooter->hide();
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
	}
	
	void WWindow::close()
	{
		if(mOnClose)
			mOnClose(this);
		this->destroy();
	}

	Widget* WWindow::vappend(unique_ptr<Widget> widget)
	{
		mHeader->title()->setLabel(widget->name());
		mContent = widget.get();
		return mBody->append(std::move(widget));
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
		if(mOnClose)
			mOnClose(widget->form());
		mParent->remove(mIndex);
	}
}
