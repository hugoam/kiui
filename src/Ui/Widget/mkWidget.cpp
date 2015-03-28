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

	Widget::Widget(Style* style, Form* form)
		: TypeObject(cls())
		, mParent(nullptr)
		, mStyle(style)
		, mFrame(nullptr)
		, mState(NOSTATE)
		, mForm(form)
	{
		if(!mStyle && form)
			mStyle = form->style();
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
			this->unhover();
		if(mState & ACTIVATED)
			this->deactivate();
		if(mState & FOCUSED)
			this->unfocus();
	}

	void Widget::bind(Sheet* parent, size_t index)
	{
		mParent = parent;
		mStyle = this->fetchOverride(mStyle);

		Stripe* stripe = mParent->frame()->as<Stripe>();

		if(this->frameType() == LAYER3D)
			mFrame = make_unique<Layer>(this, index, this->zorder());
		else if(this->frameType() == LAYER)
			mFrame = make_unique<Layer>(this, index, this->zorder());
		else if(this->frameType() == STRIPE)
			mFrame = make_unique<Stripe>(this, index);
		else
			mFrame = make_unique<Frame>(this, index);

		if(this->frameType() != LAYER3D)
			stripe->insert(mFrame.get(), index);
		else
			mFrame->as<Layer>()->bind();

		this->build();
	}

	void Widget::rebind(Sheet* parent, size_t index)
	{
		mParent = parent;

		mFrame->transfer(mParent->frame()->as<Stripe>(), index);
	}

	unique_ptr<Widget> Widget::unbind()
	{
		//this->cleanup();
		return mParent->as<Sheet>()->release(this);
	}

	unique_ptr<Widget> Widget::extract()
	{
		this->cleanup();
		unique_ptr<Widget> unique = mParent->as<Sheet>()->release(this);
		mParent->destroy();
		return unique;
	}

	void Widget::destroy()
	{
		this->cleanup();
		mParent->as<Sheet>()->vrelease(this);
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

	Widget* Widget::copy(Sheet* parent)
	{
		Sheet* widget = this->clone(parent);

		if(mFrame->frameType() == STRIPE)
			for(Frame* frame : mFrame->as<Stripe>()->contents())
				frame->widget()->copy(widget);

		return widget;
	}

	Sheet* Widget::clone(Sheet* parent)
	{
		return parent->makeappend<Sheet>(mStyle, mForm);
	}

	void Widget::reset(Form* form)
	{
		mForm = form;
		this->reset(form->style());
	}

	void Widget::setStyle(Style* style)
	{
		this->reset(style);
	}

	void Widget::reset(Style* style)
	{
		mFrame->reset(style);
	}

	Style* Widget::fetchOverride(Style* style)
	{
		Style* overrider = this->uiWindow()->styler()->fetchOverride(style, mStyle);
		if(overrider)
			return overrider;
		else if(mParent)
			return mParent->fetchOverride(style);
		else
			return style;
	}

	FrameType Widget::frameType()
	{
		return FRAME;
	}

	const string& Widget::name()
	{
		return mForm ? mForm->name() : sNullString;
	}

	const string& Widget::image()
	{
		if(!mFrame->inkstyle()->mImage.empty())
			return mFrame->inkstyle()->mImage;
		else
			return mForm ? mForm->image() : sNullString;
	}

	const string& Widget::label()
	{
		return mForm ? mForm->label() : sNullString;
	}

	const string& Widget::tooltip()
	{
		return mForm ? mForm->tooltip() : sNullString;
	}

	Style* Widget::hoverCursor()
	{
		return nullptr;
	}

	RootSheet* Widget::rootSheet()
	{
		return mParent->rootSheet();
	}

	InkTarget* Widget::inkTarget()
	{
		return mParent->inkTarget();
	}

	bool Widget::contains(Widget* widget)
	{
		while(widget && widget != this)
			widget = widget->parent();

		return widget == this;
	}

	UiWindow*  Widget::uiWindow()
	{
		return this->rootSheet()->uiWindow();
	}

	void Widget::markDirty()
	{
		mFrame->setDirty(Frame::DIRTY_WIDGET);
	}

	void Widget::toggleState(WidgetState state)
	{
		mState = static_cast<WidgetState>(mState ^ state);
		mFrame->updateState(mState);
	}

	void Widget::nextFrame(size_t tick, size_t delta)
	{
		mFrame->nextFrame(tick, delta);

		//std::cerr << "Widget :: nextFrame " << tick << " , " << delta << std::endl;
		if(mForm)
		{
			if(mForm->updated() == mForm->rootForm()->lastTick())
				this->markDirty();
			mForm->nextFrame(tick, delta);
		}
	}

	Widget* Widget::pinpoint(float x, float y, bool modal)
	{
		if(mState & PRESSED)
			return this;

		Frame* target = mFrame->pinpoint(x, y, true);
		if(target)
			return target->widget();
		else if(modal)
			return this;
		else
			return nullptr;
	}

	Widget* Widget::prev()
	{
		return mFrame->parent()->contents()[mFrame->index() - 1]->widget();
	}

	Widget* Widget::next()
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
		this->rootSheet()->activate(this);
		this->toggleState(ACTIVATED);
	}

	void Widget::deactivate()
	{
		this->rootSheet()->deactivate(this);
		this->toggleState(ACTIVATED);
	}

	void Widget::focus()
	{
		this->rootSheet()->activate(this);
		this->toggleState(FOCUSED);
	}

	void Widget::unfocus()
	{
		this->rootSheet()->deactivate(this);
		this->toggleState(FOCUSED);
	}

	void Widget::hover()
	{
		this->rootSheet()->cursor()->hover(this);
		this->toggleState(HOVERED);
	}
	
	void Widget::unhover()
	{
		this->rootSheet()->cursor()->unhover(this);
		this->toggleState(HOVERED);
	}

	void Widget::modal()
	{
		this->rootSheet()->modalOn(this);
		this->toggleState(MODAL);
	}

	void Widget::unmodal()
	{
		this->rootSheet()->modalOff();
		this->toggleState(MODAL);
	}

	bool Widget::mouseEntered(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		//std::cerr << "HOVERED : " << mFrame->wstyle()->name() << std::endl;
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
		if(this->rootSheet()->cursor()->hovered() != this)
		{
			this->rootSheet()->cursor()->hovered()->mouseLeaved(xPos, yPos);
			this->mouseEntered(xPos, yPos);
		}

		if(mState & DRAGGED)
		{
			this->leftDrag(xPos, yPos, xDif, yDif);
		}
		else if(mState & PRESSED && (abs(xPos - this->rootSheet()->lastPressedX()) > 8.f || abs(yPos - this->rootSheet()->lastPressedY()) > 8.f))
		{
			this->leftDragStart(this->rootSheet()->lastPressedX(), this->rootSheet()->lastPressedY());
			this->toggleState(DRAGGED);
			mFrame->setOpacity(_VOID);
		}

		return true;
	}

	bool Widget::mousePressed(float xPos, float yPos, MouseButton button)
	{
		UNUSED(xPos); UNUSED(yPos);
		if(button == LEFT_BUTTON)
		{
			this->modal();
			this->toggleState(PRESSED);
		}
		return true;
	}

	bool Widget::mouseReleased(float xPos, float yPos, MouseButton button)
	{
		if(button == LEFT_BUTTON)
		{
			this->unmodal();
			this->toggleState(PRESSED);
		}

		if(mState & DRAGGED)
		{
			this->leftDragEnd(xPos, yPos);
			this->toggleState(DRAGGED);
			mFrame->setOpacity(_OPAQUE);
		}
		else if(button == LEFT_BUTTON)
			this->leftClick(xPos, yPos);
		else if(button == RIGHT_BUTTON)
			this->rightClick(xPos, yPos);

		return true;
	}
}
