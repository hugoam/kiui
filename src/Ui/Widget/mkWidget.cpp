//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkWidget.h>

#include <Ui/Widget/mkSheet.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>
#include <Ui/Frame/mkLayer.h>
#include <Ui/Frame/mkGrid.h>

#include <Ui/mkUiWindow.h>
#include <Ui/mkUiLayout.h>

#include <Ui/Form/mkRootForm.h>

#include <Object/Store/mkReverse.h>

#include <iostream>

namespace mk
{
	string Widget::sNullString;

	Widget::Widget(Style* style, Form* form)
		: TypeObject(cls())
		, mParent(nullptr)
		, mStyle(style)
		, mFrame(nullptr)
		, mState(ENABLED)
		, mForm(form)
	{
		if(!mStyle && form)
			mStyle = form->style();

		if(!mStyle)
			int i = 0;
	}

	Widget::~Widget()
	{
		if(mState == HOVERED)
			uiWindow()->unhover();
		if(mState == FOCUSED)
			uiWindow()->deactivate(this);
	}

	void Widget::bind(Sheet* parent, size_t index)
	{
		mParent = parent;
		mStyle = this->fetchOverride(mStyle);

		Stripe* stripe = mParent ? mParent->frame()->as<Stripe>() : nullptr;

		if(this->frameType() == LAYER)
			mFrame = make_unique<Layer>(stripe, this, index, this->zorder());
		else if(this->frameType() == STRIPE)
			mFrame = make_unique<Stripe>(stripe, this, index);
		else
			mFrame = make_unique<Frame>(stripe, this, index);

		this->build();
	}

	void Widget::rebind(Sheet* parent, size_t index)
	{
		mParent = parent;

		parent->frame()->as<Stripe>()->insert(mFrame.get(), index);

		mFrame->migrate(mParent->frame()->as<Stripe>());
	}

	unique_ptr<Widget> Widget::unbind()
	{
		return mParent->as<Sheet>()->release(this);
	}

	unique_ptr<Widget> Widget::extract()
	{
		mFrame->remove();
		unique_ptr<Widget> unique = mParent->as<Sheet>()->release(this);
		mParent->destroy();
		return unique;
	}

	void Widget::destroy()
	{
		mParent->as<Sheet>()->release(this);
	}

	void Widget::detach()
	{
		mFrame->remove();
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

	RootSheet* Widget::rootWidget()
	{
		return mParent->rootWidget();
	}

	InkTarget* Widget::inkTarget()
	{
		return this->uiWindow()->inkWindow()->screenTarget();
	}

	bool Widget::contains(Widget* widget)
	{
		while(widget && widget != this)
			widget = widget->parent();

		return widget == this;
	}

	UiWindow*  Widget::uiWindow()
	{
		return this->rootWidget()->uiWindow();
	}

	void Widget::markDirty()
	{
		mFrame->setDirty(Frame::DIRTY_WIDGET);
	}

	void Widget::updateState(WidgetState state)
	{
		mState = state;
		mFrame->updateState(mState);
	}

	void Widget::nextFrame(size_t tick, size_t delta)
	{
		//std::cerr << "Widget :: nextFrame " << tick << " , " << delta << std::endl;
		if(mForm)
		{
			if(mForm->updated() == mForm->rootForm()->lastTick())
				this->markDirty();
			mForm->nextFrame(tick, delta);
		}
	}

	Widget* Widget::pinpoint(float x, float y, bool opaque)
	{
		Frame* target = mFrame->pinpoint(x, y, opaque);
		if(target)
			return target->widget();
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
		this->updateState(ACTIVATED);
	}

	void Widget::deactivate()
	{
		this->updateState(ENABLED);
	}

	void Widget::focus()
	{
		this->updateState(FOCUSED);
		uiWindow()->activate(this);
	}

	void Widget::unfocus()
	{
		this->updateState(ENABLED);
		uiWindow()->deactivate(this);
	}

	void Widget::hover()
	{
		if(mState == ACTIVATED)
			this->updateState(ACTIVATED_HOVERED);
		else
			this->updateState(HOVERED);
	}
	
	void Widget::unhover()
	{
		if(mState == ACTIVATED_HOVERED || mState == ACTIVATED)
			this->updateState(ACTIVATED);
		else
			this->updateState(ENABLED);
	}

	bool Widget::mouseEntered(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		std::cerr << "HOVERED : " << mFrame->wstyle()->name() << std::endl;
		this->hover();
		return true;
	}

	bool Widget::mouseLeaved(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		this->unhover();
		return true;
	}
}
