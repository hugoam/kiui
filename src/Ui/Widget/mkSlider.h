//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WSLIDER_H
#define MK_WSLIDER_H

/* mk */
#include <Object/Util/mkStat.h>
#include <Object/String/mkStringConvert.h>
#include <Ui/mkUiForward.h>
#include <Ui/Frame/mkUibox.h>
#include <Ui/Widget/mkValue.h>
#include <Ui/Widget/mkWidget.h>
#include <Ui/Widget/mkButton.h>
#include <Ui/Widget/mkTypeIn.h>

namespace mk
{
	class MK_UI_EXPORT SliderKnob : public Button
	{
	public:
		SliderKnob(Dimension dim = DIM_X);

		float offset(float pos);

		bool leftDragStart(float xPos, float yPos);
		bool leftDrag(float xPos, float yPos, float xDif, float yDif);
		bool leftDragEnd(float xPos, float yPos);

		static StyleType& cls() { static StyleType ty("SliderKnob", Button::cls()); return ty; }

	protected:
		Dimension mDim;
		float mStartPos;
		float mStartOffset;
	};

	class MK_UI_EXPORT SpacerX : public Widget
	{
	public:
		SpacerX();

		static StyleType& cls() { static StyleType ty("SpacerX", Widget::cls()); return ty; }
	};

	class MK_UI_EXPORT SpacerY : public Widget
	{
	public:
		SpacerY();

		static StyleType& cls() { static StyleType ty("SpacerY", Widget::cls()); return ty; }
	};

	class MK_UI_EXPORT SliderKnobX : public SliderKnob
	{
	public:
		SliderKnobX();

		static StyleType& cls() { static StyleType ty("SliderKnobX", SliderKnob::cls()); return ty; }
	};

	class MK_UI_EXPORT SliderKnobY : public SliderKnob
	{
	public:
		SliderKnobY();

		static StyleType& cls() { static StyleType ty("SliderKnobY", SliderKnob::cls()); return ty; }
	};

	class MK_UI_EXPORT Slider : public Sheet
	{
	public:
		Slider(Dimension dim = DIM_X, const Trigger& onUpdated = nullptr);

		Widget& filler() { return mFiller; }
		SliderKnob& slider() { return mButton; }

		float val() { return mVal; }

		float length();

		void nextFrame(size_t tick, size_t delta);

		void updateMetrics(float min, float max, float val, float stepLength, float knobLength = 0.f);
		void resetMetrics(float min, float max, float val, float stepLength, float knobLength = 0.f);
		void resetValue(float val);

		void offsetChange(float offset, bool ended);
		
		void updateKnob();

		virtual void sliderStep(float value, bool ended) { UNUSED(value); UNUSED(ended); mOnUpdated(*this); }

		static StyleType& cls() { static StyleType ty("Slider", Sheet::cls()); return ty; }

	protected:
		Dimension mDim;
		Widget& mFiller;
		SliderKnob& mButton;

		float mMin;
		float mMax;
		float mVal;
		float mStepLength;
		float mKnobLength;

		float mNumSteps;
		int mStep;

		Trigger mOnUpdated;
	};

	class MK_UI_EXPORT SliderX : public Slider
	{
	public:
		SliderX(const Trigger& onUpdated = Trigger());

		static StyleType& cls() { static StyleType ty("SliderX", Slider::cls()); return ty; }
	};

	class MK_UI_EXPORT SliderY : public Slider
	{
	public:
		SliderY(const Trigger& onUpdated = Trigger());

		static StyleType& cls() { static StyleType ty("SliderY", Slider::cls()); return ty; }
	};

	class MK_UI_EXPORT SliderDisplay : public Label
	{
	public:
		SliderDisplay(const string& label);

		static StyleType& cls() { static StyleType ty("SliderDisplay", Label::cls()); return ty; }
	};

	template <class T>
	class StatSlider : public WTypedInput<AutoStat<T>, T>
	{
	public:
		StatSlider(Lref& lref, std::function<void(T)> callback = nullptr, Dimension dim = DIM_X)
			: WTypedInput<AutoStat<T>, T>(lref, callback)
			, mStat(this->mValue->template ref<AutoStat<T>>())
			, mDim(dim)
			, mDisplay(this->template makeappend<SliderDisplay>(toString(mStat.value())))
			, mSlider(mDim == DIM_X ? (Slider&) this->template makeappend<SliderX>(std::bind(&StatSlider::updateStat, this))
									: (Slider&) this->template makeappend<SliderY>(std::bind(&StatSlider::updateStat, this)))
		{
			this->updateSlider();
		}

		StatSlider(AutoStat<T> value, std::function<void(T)> callback = nullptr, Dimension dim = DIM_X)
			: WTypedInput<AutoStat<T>, T>(value, callback)
			, mStat(this->mValue->template ref<AutoStat<T>>())
			, mDim(dim)
			, mDisplay(this->template makeappend<SliderDisplay>(toString(mStat.value())))
			, mSlider(mDim == DIM_X ? (Slider&) this->template makeappend<SliderX>(std::bind(&StatSlider::updateStat, this))
									: (Slider&) this->template makeappend<SliderY>(std::bind(&StatSlider::updateStat, this)))
		{
			this->updateSlider();
		}

		void updateSlider()
		{
			mSlider.resetMetrics(float(mStat.min()), float(mStat.max()), float(mStat.value()), float(mStat.step()));
			mSlider.updateKnob();
			mDisplay.setLabel(toString(mStat.value()));
		}

		void updateStat()
		{
			mStat.modify(T(mSlider.val()));
			mDisplay.setLabel(toString(mStat.value()));
			this->triggerModify();
		}

		void updateValue(T val) { mStat.modify(val); this->triggerUpdate(); }
		void modifyValue(T val) { mStat.modify(val); this->triggerModify(); }

		void notifyUpdate() { this->updateSlider(); }
		void notifyModify() { this->updateSlider(); if(this->mOnUpdate) this->mOnUpdate(mStat.value()); }

		static StyleType& cls() { static StyleType ty("StatSlider<" + typecls<T>().name() + ">", WValue::cls()); return ty; }

	protected:
		AutoStat<T>& mStat;

		Dimension mDim;

		Slider& mSlider;
		SliderDisplay& mDisplay;
	};

	template class MK_UI_EXPORT _I_ StatSlider<float>;
	template class MK_UI_EXPORT _I_ StatSlider<int>;
}

#endif
