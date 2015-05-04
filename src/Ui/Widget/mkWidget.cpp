//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkWidget.h>

#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkRootSheet.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>
#include <Ui/Frame/mkLayer.h>

#include <Ui/mkUiWindow.h>
#include <Ui/mkUiLayout.h>

#include <Ui/Form/mkRootForm.h>

#include <Object/Iterable/mkReverse.h>

#include <iostream>

namespace mk
{
	string Widget::sNullString;

	Widget::Widget(FrameType frameType)
		: TypeObject(cls())
		, mParent(nullptr)
		, mStyle(&cls())
		, mFrame(nullptr)
		, mState(UNBOUND)
	{
		if(frameType == STRIPE)
			mFrame = make_unique<Stripe>(*this);
		else if(frameType == FRAME)
			mFrame = make_unique<Frame>(*this);
	}

	Widget::~Widget()
	{
		this->cleanup();
	}

	void Widget::cleanup()
	{
		if(mState & MODAL)
			this->unmodal();
		if(mState & HOVERED)
			this->rootSheet().cursor()->unhover();
		if(mState & ACTIVATED)
			this->deactivate();
		if(mState & FOCUSED)
			this->unfocus();
	}

	void Widget::bind(Sheet* parent, size_t index)
	{
		mParent = parent;

		if(mFrame->frameType() != LAYER3D)
			mParent->stripe().insert(*mFrame.get(), index);
		else
			mFrame->as<Layer>().bind();

		mState = static_cast<WidgetState>(mState ^ BOUND);
	}

	void Widget::rebind(Sheet* parent, size_t index)
	{
		mParent = parent;

		mFrame->transfer(mParent->frame().as<Stripe>(), index);
	}

	unique_ptr<Widget> Widget::unbind()
	{
		//this->cleanup();
		mState = static_cast<WidgetState>(mState ^ BOUND);
		return mParent->as<Sheet>().release(*this);
	}

	unique_ptr<Widget> Widget::extract()
	{
		this->cleanup();
		unique_ptr<Widget> unique = mParent->as<Sheet>().release(*this);
		mParent->destroy();
		return unique;
	}

	void Widget::remove()
	{
		this->cleanup();
		mParent->as<Sheet>().vrelease(*this);
	}

	void Widget::destroy()
	{
		this->cleanup();
		mParent->as<Sheet>().release(*this);
	}

	void Widget::detach()
	{
		mFrame->remove();
	}

	void Widget::show()
	{
		mFrame->show();
	}
	
	void Widget::hide()
	{
		mFrame->hide();
	}

	void Widget::setStyle(Style* style)
	{
		mStyle = style;
		//this->reset(style);
	}

	void Widget::resetStyle(Style* style)
	{
		mStyle = style;
		mFrame->resetStyle();
	}

	void Widget::resetSkin(Style* style)
	{
		mStyle = style;
		mFrame->updateStyle();
	}

	Style& Widget::fetchOverride(Style& style)
	{
		Style* overrider = this->uiWindow().styler().fetchOverride(style, *mStyle);
		if(overrider)
			return *overrider;
		else if(mParent)
			return mParent->fetchOverride(style);
		else
			return style;
	}

	Image* Widget::image()
	{
		if(!mFrame->inkstyle().image().null())
			return &mFrame->inkstyle().image();
		return nullptr;
	}

	RootSheet& Widget::rootSheet()
	{
		return mParent->rootSheet();
	}

	bool Widget::contains(Widget* widget)
	{
		while(widget && widget != this)
			widget = widget->parent();

		return widget == this;
	}

	UiWindow&  Widget::uiWindow()
	{
		return this->rootSheet().uiWindow();
	}

	void Widget::markDirty()
	{
		mFrame->setDirty(Frame::DIRTY_WIDGET);
	}

	void Widget::toggleState(WidgetState state)
	{
		mState = static_cast<WidgetState>(mState ^ state);
		if(mState & BOUND)
			mFrame->updateState(mState);
	}

	void Widget::nextFrame(size_t tick, size_t delta)
	{
		mFrame->nextFrame(tick, delta);
	}

	Widget* Widget::pinpoint(float x, float y, bool modal)
	{
		if(mState & PRESSED)
			return this;

		Frame* target = mFrame->pinpoint(x, y, true);
		if(target)
			return &target->widget();
		else if(modal)
			return this;
		else
			return nullptr;
	}

	Widget& Widget::prev()
	{
		return mFrame->parent()->contents()[mFrame->index() - 1]->widget();
	}

	Widget& Widget::next()
	{
		return mFrame->parent()->contents()[mFrame->index() + 1]->widget();
	}

	InputReceiver* Widget::propagateMouse(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		return mParent;
	}

	InputReceiver* Widget::propagateKey()
	{
		return mParent;
	}

	void Widget::activate()
	{
		this->toggleState(ACTIVATED);
	}

	void Widget::deactivate()
	{
		this->toggleState(ACTIVATED);
	}

	void Widget::focus()
	{
		this->rootSheet().focus(this);
		this->toggleState(FOCUSED);
		this->focused();
	}

	void Widget::unfocus()
	{
		this->rootSheet().unfocus(this);
		this->toggleState(FOCUSED);
		this->unfocused();
	}

	void Widget::hover()
	{
		//std::cerr << "HOVERED : " << mFrame->style()->name() << std::endl;
		this->rootSheet().cursor()->hover(*this);
		this->toggleState(HOVERED);
	}
	
	void Widget::unhover()
	{
		//std::cerr << "UN HOVERED : " << mFrame->style()->name() << std::endl;
		this->toggleState(HOVERED);
	}

	void Widget::modal()
	{
		this->rootSheet().modalOn(this);
		this->toggleState(MODAL);
	}

	void Widget::unmodal()
	{
		this->rootSheet().modalOff();
		this->toggleState(MODAL);
	}

	bool Widget::mouseEntered(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		this->hover();
		return true;
	}

	bool Widget::mouseLeaved(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		this->unhover();
		return true;
	}

	bool Widget::mouseMoved(float xPos, float yPos, float xDif, float yDif)
	{
		//if(!mFrame->opaque())
		//	return false;

		if(!(mState & HOVERED))
			this->hover();

		if(mState & DRAGGED)
		{
			this->leftDrag(xPos, yPos, xDif, yDif);
		}
		else if(mState & PRESSED && (abs(xPos - this->rootSheet().lastPressedX()) > 8.f || abs(yPos - this->rootSheet().lastPressedY()) > 8.f))
		{
			this->leftDragStart(this->rootSheet().lastPressedX(), this->rootSheet().lastPressedY());
			this->toggleState(DRAGGED);
			mFrame->setOpacity(VOID);
		}

		return false;

		/*if(mStyle->layout()->opacity() == GLASSY)
			return false;
		else
			return true;*/
	}

	bool Widget::mousePressed(float xPos, float yPos, MouseButton button)
	{
		UNUSED(xPos); UNUSED(yPos);
		if(button == LEFT_BUTTON)
		{
			if(!(mState & MODAL))
				this->modal();
			this->toggleState(PRESSED);
		}
		return true;
	}

	bool Widget::mouseReleased(float xPos, float yPos, MouseButton button)
	{
		if(!(mState & MODAL))
			return true;

		if(button == LEFT_BUTTON)
		{
			this->unmodal();
			this->toggleState(PRESSED);
		}

		if(mState & DRAGGED)
		{
			this->leftDragEnd(xPos, yPos);
			this->toggleState(DRAGGED);
			mFrame->setOpacity(OPAQUE);
		}
		else if(button == LEFT_BUTTON)
			this->leftClick(xPos, yPos);
		else if(button == RIGHT_BUTTON)
			this->rightClick(xPos, yPos);

		return true;
	}
}
