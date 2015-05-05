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
	class MK_UI_EXPORT Label : public Widget
	{
	public:
		Label(const string& label, FrameType frameType = FRAME);

		const string& label() { return mLabel; }
		unique_ptr<Widget> clone() { return make_unique<Label>(mLabel); }

		void setLabel(const string& label);

		static StyleType& cls() { static StyleType ty("Label", Widget::cls()); return ty; }

	protected:
		string mLabel;
	};

	class MK_UI_EXPORT Title : public Label
	{
	public:
		Title(const string& label);

		static StyleType& cls() { static StyleType ty("Title", Label::cls()); return ty; }
	};

	class MK_UI_EXPORT Icon : public Widget
	{
	public:
		Icon(Image& image);
		Icon(const string& image);

		Image* image() { return &mImage; }

		//void setImage(Image& image);

		static StyleType& cls() { static StyleType ty("Icon", Widget::cls()); return ty; }

	protected:
		Image& mImage;
	};

	/*
	DynamicImage::DynamicImage(unique_ptr<Image256> image)
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
		typedef std::function<void(T_Widget&)> Trigger;

	public:
		WidgetTrigger(const Trigger& trigger) : mTrigger(trigger) {}

		virtual void trigger() { if(mTrigger) mTrigger(static_cast<T_Widget&>(*this)); }
		virtual void triggerAlt() { if(mTriggerAlt) mTriggerAlt(static_cast<T_Widget&>(*this)); }
		virtual void triggerShift() { if(mTriggerShift) mTriggerShift(static_cast<T_Widget&>(*this)); }
		virtual void triggerCtrl() { if(mTriggerCtrl) mTriggerCtrl(static_cast<T_Widget&>(*this)); }

	protected:
		Trigger mTrigger;
		Trigger mTriggerAlt;
		Trigger mTriggerShift;
		Trigger mTriggerCtrl;
	};

	class MK_UI_EXPORT Button : public Control, public WidgetTrigger<Button>
	{
	public:
		typedef WidgetTrigger<Button>::Trigger Trigger;

	public:
		Button(const string& label, const Trigger& trigger = Trigger());

		const string& label() { return mLabel; }
		const string& tooltip() { return mTooltip; }

		bool leftPressed(float x, float y);
		bool leftClick(float x, float y);
		bool rightClick(float x, float y);

		static StyleType& cls() { static StyleType ty("Button", Control::cls()); return ty; }

	protected:
		string mLabel;
		string mTooltip;
	};

	class MK_UI_EXPORT ImgButton : public Button
	{
	public:
		typedef WidgetTrigger<Button>::Trigger Trigger;

	public:
		ImgButton(Image& image, const Trigger& trigger = Trigger());
		ImgButton(const string& image, const Trigger& trigger = Trigger());

		Image* image() { return &mImage; }
		const string& tooltip() { return mTooltip; }

		static StyleType& cls() { static StyleType ty("ImgButton", Button::cls()); return ty; }

	protected:
		Image& mImage;
		string mTooltip;
	};

	class MK_UI_EXPORT WrapButton : public Sheet, public WidgetTrigger<WrapButton>
	{
	public:
		typedef WidgetTrigger<WrapButton>::Trigger Trigger;

	public:
		WrapButton(Widget* content, const Trigger& trigger = Trigger());
		WrapButton(unique_ptr<Widget> content, const Trigger& trigger = Trigger());

		Widget* content();

		bool leftPressed(float x, float y);
		bool leftClick(float x, float y);
		bool rightClick(float x, float y);

		const string& contentlabel() { return mContent->contentlabel(); }

		static StyleType& cls() { static StyleType ty("WrapButton", Sheet::cls()); return ty; }

	protected:
		Widget* mContent;
	};

	class MK_UI_EXPORT Toggle : public Control
	{
	public:
		typedef std::function<void(Toggle*)> Trigger;

	public:
		Toggle(const Trigger& triggerOn, const Trigger& triggerOff, bool isOn = true);

		bool on() { return mOn; }

		void update(bool on);
		void toggle();

		bool leftClick(float x, float y);

		static StyleType& cls() { static StyleType ty("Toggle", Control::cls()); return ty; }

	protected:
		Trigger mTriggerOn;
		Trigger mTriggerOff;

		bool mOn;
	};
}

#endif
