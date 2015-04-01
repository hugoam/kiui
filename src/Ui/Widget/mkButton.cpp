//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkButton.h>

#include <Ui/Form/mkWidgets.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>

#include <Ui/Form/mkHook.h>

#include <Ui/mkUiWindow.h>

namespace mk
{
	Label::Label(const string& label, Style* style)
		: Widget(style ? style : styleCls())
		, mLabel(label)
	{}

	void Label::setLabel(const string& label)
	{
		mLabel = label;
		mFrame->setDirty(Frame::DIRTY_WIDGET);
	}

	Title::Title(const string& label)
		: Label(label, styleCls())
	{}

	Icon::Icon(const string& image, Style* style)
		: Widget(style ? style : styleCls())
		, mImage(image)
	{}

	void Icon::setImage(const string& image)
	{
		mImage = image;
		mFrame->setDirty(Frame::DIRTY_WIDGET);
	}

	Button::Button(const string& label, Style* style, const Trigger& trigger)
		: Widget(style ? style : styleCls())
		, WidgetTrigger(trigger)
		, mLabel(label)
	{}

	bool Button::leftPressed(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		//toggleState(TRIGGERED);
		return true;
	}

	bool Button::leftClick(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		if(uiWindow()->ctrlPressed())
			this->triggerCtrl();
		else if(uiWindow()->shiftPressed())
			this->triggerShift();
		else
			this->trigger();

		//toggleState(HOVERED);
		return true;
	}

	bool Button::rightClick(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		triggerAlt();
		return true;
	}

	ImgButton::ImgButton(const string& image, const Trigger& trigger)
		: Button("", styleCls(), trigger)
		, mImage(image)
	{}

	WrapButton::WrapButton(Widget* content, Style* style, const Trigger& trigger)
		: Sheet(style)
		, WidgetTrigger(trigger)
		, mContent(content)
	{}

	Widget* WrapButton::content()
	{
		return mContents[0].get();
	}

	bool WrapButton::leftPressed(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		toggleState(TRIGGERED);
		return true;
	}

	bool WrapButton::leftClick(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		if(uiWindow()->ctrlPressed())
			this->triggerCtrl();
		else if(uiWindow()->shiftPressed())
			this->triggerShift();
		else
			this->trigger();

		//toggleState(HOVERED);
		return true;
	}

	bool WrapButton::rightClick(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		triggerAlt();
		return true;
	}

	Toggle::Toggle(Style* style, const Trigger& triggerOn, const Trigger& triggerOff, bool on)
		: Widget(style)
		, mTriggerOn(triggerOn)
		, mTriggerOff(triggerOff)
		, mOn(on)
	{
		if(mOn)
			this->toggleState(ACTIVATED);
	}

	void Toggle::toggle()
	{
		mOn = !mOn;
		this->toggleState(ACTIVATED);

		if(mOn)
			mTriggerOn(this);
		else
			mTriggerOff(this);
	}

	bool Toggle::leftClick(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		this->toggle();
		return true;
	}
}
