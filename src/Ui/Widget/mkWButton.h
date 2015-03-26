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
	class MK_UI_EXPORT WLabel :public Widget, public Styled<WLabel>
	{
	public:
		WLabel(Form* form);
		WLabel(const string& label, Style* style = nullptr);

		const string& label() { return mLabel; }
		
		void setLabel(const string& label);

	protected:
		string mLabel;
	};

	class MK_UI_EXPORT WTitle : public WLabel, public Styled<WTitle>
	{
	public:
		WTitle(const string& label);

		using Styled<WTitle>::styleCls;
	};

	class MK_UI_EXPORT WIcon :public Widget, public Styled<WIcon>
	{
	public:
		WIcon(Form* form);
		WIcon(const string& image, Style* style = nullptr);

		const string& image() { return mImage; }

		void setImage(const string& image);

	protected:
		string mImage;
	};

	template <class T_Widget>
	class WidgetTrigger
	{
	public:
		typedef std::function<void(T_Widget*)> Trigger;

	public:
		WidgetTrigger(const Trigger& trigger) : mTrigger(trigger) {}

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

	class MK_UI_EXPORT WButton : public Widget, public WidgetTrigger<WButton>, public Styled<WButton>
	{
	public:
		using WidgetTrigger<WButton>::Trigger;

	public:
		WButton(Form* form);
		WButton(const string& label, Style* style = nullptr, const Trigger& trigger = Trigger());

		const string& label() { return mLabel; }

		bool leftPressed(float x, float y);
		bool leftClick(float x, float y);
		bool rightClick(float x, float y);

	protected:
		string mLabel;
	};

	class MK_UI_EXPORT WImgButton : public WButton, public Styled<WImgButton>
	{
	public:
		using WidgetTrigger<WButton>::Trigger;

	public:
		WImgButton(const string& image, const Trigger& trigger = Trigger());

		using Styled<WImgButton>::styleCls;
	};

	class MK_UI_EXPORT WWrapButton : public Sheet, public WidgetTrigger<WWrapButton>
	{
	public:
		using WidgetTrigger<WWrapButton>::Trigger;

	public:
		WWrapButton(Widget* content, Style* style, const Trigger& trigger = Trigger());

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
		WToggle(Style* style, const Trigger& triggerOn, const Trigger& triggerOff, bool isOn = true);

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
