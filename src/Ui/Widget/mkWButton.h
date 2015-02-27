//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WBUTTON_H
#define MK_WBUTTON_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Widget/mkWidget.h>
#include <Ui/Widget/mkSheet.h>

namespace mk
{
	class MK_UI_EXPORT WLabel :public Widget
	{
	public:
		WLabel(Form* form);
		WLabel(string label, string clas);

		const string& label() { return mLabel; }
		
		void setLabel(string label);

	protected:
		string mLabel;
	};

	template <class T_Widget>
	class WidgetTrigger
	{
	public:
		typedef std::function<void(T_Widget*)> Trigger;

	public:
		WidgetTrigger(Trigger trigger) : mTrigger(trigger) {}

		virtual void trigger() { if(mTrigger) mTrigger(static_cast<T_Widget*>(this)); }
		virtual void triggerAlt() { if(mTriggerAlt) mTriggerAlt(static_cast<T_Widget*>(this)); }
		virtual void triggerShift() { if(mTriggerShift) mTriggerShift(static_cast<T_Widget*>(this)); }
		virtual void triggerCtrl() { if(mTriggerCtrl) mTriggerCtrl(static_cast<T_Widget*>(this)); }

	protected:
		Trigger mTrigger;
		Trigger mTriggerAlt;
		Trigger mTriggerShift;
		Trigger mTriggerCtrl;
	};

	class MK_UI_EXPORT WButton : public Widget, public WidgetTrigger<WButton>
	{
	public:
		using WidgetTrigger<WButton>::Trigger;

	public:
		WButton(Form* form);
		WButton(string label, string clas, Trigger trigger = Trigger());

		const string& label() { return mLabel; }

		bool leftPressed(float x, float y);
		bool leftClick(float x, float y);
		bool rightClick(float x, float y);

	protected:
		string mLabel;
	};

	class MK_UI_EXPORT WWrapButton : public Sheet, public WidgetTrigger<WWrapButton>
	{
	public:
		using WidgetTrigger<WWrapButton>::Trigger;

	public:
		WWrapButton(Widget* content, string clas, Trigger trigger = Trigger());

		Widget* content();

		bool leftPressed(float x, float y);
		bool leftClick(float x, float y);
		bool rightClick(float x, float y);

	protected:
		Widget* mContent;
	};

	class MK_UI_EXPORT WToggle : public Widget
	{
	public:
		typedef std::function<void(WToggle*)> Trigger;

	public:
		WToggle(string clas, Trigger triggerOn, Trigger triggerOff, bool isOn = true);

		void build();
		
		void toggle();

		bool leftClick(float x, float y);

	protected:
		Trigger mTriggerOn;
		Trigger mTriggerOff;

		bool mOn;
	};
}

#endif
