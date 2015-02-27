//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkWButton.h>

#include <Ui/Form/mkWidgets.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>

#include <Ui/Form/mkHook.h>

#include <Ui/mkUiWindow.h>

namespace mk
{
	WLabel::WLabel(Form* form)
		: Widget("", form)
		, mLabel(form->label())
	{}
	
	WLabel::WLabel(string label, string clas)
		: Widget(clas)
		, mLabel(label)
	{}

	void WLabel::setLabel(string label)
	{
		mLabel = label;
		mFrame->setDirty(Frame::DIRTY_WIDGET);
	}

	WButton::WButton(Form* form)
		: Widget("", form)
		, WidgetTrigger(nullptr)
		, mLabel(form->label())
	{
		mTrigger = std::bind(&Button::trigger, form->as<Button>());
		mTriggerShift = std::bind(&Button::trigger, form->as<Button>());
	}

	WButton::WButton(string label, string clas, Trigger trigger)
		: Widget(clas)
		, WidgetTrigger(trigger)
		, mLabel(label)
	{}

	bool WButton::leftPressed(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		updateState(TRIGGERED);
		return true;
	}

	bool WButton::leftClick(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		if(uiWindow()->ctrlPressed())
			this->triggerCtrl();
		else if(uiWindow()->shiftPressed())
			this->triggerShift();
		else
			this->trigger();

		//updateState(HOVERED);
		return true;
	}

	bool WButton::rightClick(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		triggerAlt();
		return true;
	}

	WWrapButton::WWrapButton(Widget* content, string clas, Trigger trigger)
		: Sheet(clas)
		, WidgetTrigger(trigger)
		, mContent(content)
	{}

	Widget* WWrapButton::content()
	{
		return mFrame->as<Stripe>()->contents()[0]->widget();
	}

	bool WWrapButton::leftPressed(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		updateState(TRIGGERED);
		return true;
	}

	bool WWrapButton::leftClick(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		if(uiWindow()->ctrlPressed())
			this->triggerCtrl();
		else if(uiWindow()->shiftPressed())
			this->triggerShift();
		else
			this->trigger();

		//updateState(HOVERED);
		return true;
	}

	bool WWrapButton::rightClick(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		triggerAlt();
		return true;
	}

	WToggle::WToggle(string clas, Trigger triggerOn, Trigger triggerOff, bool on)
		: Widget(clas)
		, mTriggerOn(triggerOn)
		, mTriggerOff(triggerOff)
		, mOn(on)
	{}

	void WToggle::build()
	{
		if(mOn)
			this->updateState(ACTIVATED);
	}

	void WToggle::toggle()
	{
		if(mOn)
		{
			mOn = false;
			mTriggerOff(this);
			this->updateState(ENABLED);
		}
		else
		{
			mOn = true;
			mTriggerOn(this);
			this->updateState(ACTIVATED);
		}
	}

	bool WToggle::leftClick(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		this->toggle();
		return true;
	}
}
