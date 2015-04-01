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
	class MK_UI_EXPORT Label : public Widget, public Styled<Label>
	{
	public:
		Label(const string& label, Style* style = nullptr);

		const string& label() { return mLabel; }
		unique_ptr<Widget> clone() { return make_unique<Label>(mLabel, mStyle); }

		void setLabel(const string& label);

	protected:
		string mLabel;
	};

	class MK_UI_EXPORT Title : public Label, public Styled<Title>
	{
	public:
		Title(const string& label);

		using Styled<Title>::styleCls;
	};

	class MK_UI_EXPORT Icon :public Widget, public Styled<Icon>
	{
	public:
		Icon(const string& image, Style* style = nullptr);

		const string& image() { return mImage; }

		void setImage(const string& image);

	protected:
		string mImage;
	};

	/*Textbox::Textbox(Style* style, const string& text)
		: Form(style, text, [this, text](){ return make_unique<Textbox>(this, text); })
	{
		mType = cls();
	}

	Textbox::Textbox(const string& text)
		: Textbox(nullptr, text)
	{}

	DynamicImage::DynamicImage(Style* style, unique_ptr<Image256> image)
		: Form(style)
		, mImage(std::move(image))
	{
		mType = cls();
	}

	DynamicImage::~DynamicImage()
	{}*/

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

	class MK_UI_EXPORT Button : public Widget, public WidgetTrigger<Button>, public Styled<Button>
	{
	public:
		typedef WidgetTrigger<Button>::Trigger Trigger;

	public:
		Button(const string& label, Style* style = nullptr, const Trigger& trigger = Trigger());

		const string& label() { return mLabel; }

		bool leftPressed(float x, float y);
		bool leftClick(float x, float y);
		bool rightClick(float x, float y);

	protected:
		string mLabel;
	};

	class MK_UI_EXPORT ImgButton : public Button, public Styled<ImgButton>
	{
	public:
		typedef WidgetTrigger<Button>::Trigger Trigger;

	public:
		ImgButton(const string& image, const Trigger& trigger = Trigger());

		const string& image() { return mImage; }

		using Styled<ImgButton>::styleCls;

	protected:
		string mImage;
	};

	class MK_UI_EXPORT WrapButton : public Sheet, public WidgetTrigger<WrapButton>
	{
	public:
		typedef WidgetTrigger<WrapButton>::Trigger Trigger;

	public:
		WrapButton(Widget* content, Style* style, const Trigger& trigger = Trigger());

		Widget* content();

		bool leftPressed(float x, float y);
		bool leftClick(float x, float y);
		bool rightClick(float x, float y);

	protected:
		Widget* mContent;
	};

	class MK_UI_EXPORT Toggle : public Widget
	{
	public:
		typedef std::function<void(Toggle*)> Trigger;

	public:
		Toggle(Style* style, const Trigger& triggerOn, const Trigger& triggerOff, bool isOn = true);

		void toggle();

		bool leftClick(float x, float y);

	protected:
		Trigger mTriggerOn;
		Trigger mTriggerOff;

		bool mOn;
	};
}

#endif
