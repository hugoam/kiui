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
	class MK_UI_EXPORT SliderKnob : public Button, public Styled<SliderKnob>
	{
	public:
		SliderKnob(Dimension dim = DIM_X, Style* style = nullptr);

		float offset(float pos);

		bool leftDragStart(float xPos, float yPos);
		bool leftDrag(float xPos, float yPos, float xDif, float yDif);
		bool leftDragEnd(float xPos, float yPos);

		using Styled<SliderKnob>::styleCls;

	protected:
		Dimension mDim;
		float mStartPos;
		float mStartOffset;
	};

	class MK_UI_EXPORT SpacerX : public Widget, public Styled<SpacerX>
	{
	public:
		SpacerX();
	};

	class MK_UI_EXPORT SpacerY : public Widget, public Styled<SpacerY>
	{
	public:
		SpacerY();
	};

	class MK_UI_EXPORT SliderKnobX : public SliderKnob, public Styled<SliderKnobX>
	{
	public:
		SliderKnobX();

		using Styled<SliderKnobX>::styleCls;
	};

	class MK_UI_EXPORT SliderKnobY : public SliderKnob, public Styled<SliderKnobY>
	{
	public:
		SliderKnobY();

		using Styled<SliderKnobY>::styleCls;
	};

	class MK_UI_EXPORT Slider : public Sheet, public Styled<Slider>
	{
	public:
		Slider(Dimension dim = DIM_X, Style* style = nullptr, const Trigger& onUpdated = nullptr);

		void init();

		Widget* spaceBefore() { return mSpaceBefore; }
		SliderKnob* slider() { return mButton; }
		Widget* spaceAfter() { return mSpaceAfter; }

		float val() { return mVal; }

		void updateMetrics(float min, float max, float val, float stepLength, float knobLength = 0.f);
		void resetMetrics(float min, float max, float val, float stepLength, float knobLength = 0.f);
		void resetValue(float val);

		void offsetChange(float offset, bool ended);
		
		void updateKnob();

		virtual void sliderStep(float value, bool ended) { UNUSED(value); UNUSED(ended); mOnUpdated(this); }

	protected:
		Dimension mDim;
		Widget* mSpaceBefore;
		SliderKnob* mButton;
		Widget* mSpaceAfter;

		float mMin;
		float mMax;
		float mVal;
		float mStepLength;
		float mKnobLength;
		bool mFixedKnob;

		float mNumSteps;
		int mStep;

		Trigger mOnUpdated;
	};

	class MK_UI_EXPORT SliderX : public Slider, public Styled<SliderX>
	{
	public:
		SliderX(const Trigger& onUpdated = Trigger());

		using Styled<SliderX>::styleCls;
	};

	class MK_UI_EXPORT SliderY : public Slider, public Styled<SliderY>
	{
	public:
		SliderY(const Trigger& onUpdated = Trigger());

		using Styled<SliderY>::styleCls;
	};

	template <class T>
	class StatSlider : public WTypedInput<AutoStat<T>, T>, public Typed<StatSlider<T>>//, public Styled<StatSlider<T>>
	{
	public:
		StatSlider(Lref& lref, std::function<void(T)> callback = nullptr, Dimension dim = DIM_X)
			: WTypedInput<AutoStat<T>, T>(lref, nullptr, callback)
			, mStat(this->mValue->ref<AutoStat<T>>())
			, mDim(dim)
		{
			this->build();
		}

		StatSlider(AutoStat<T> value, std::function<void(T)> callback = nullptr, Dimension dim = DIM_X)
			: WTypedInput<AutoStat<T>, T>(value, nullptr, callback)
			, mStat(this->mValue->ref<AutoStat<T>>())
			, mDim(dim)
		{
			this->build();
		}

		void build()
		{
			if(mDim == DIM_X)
				mSlider = this->template makeappend<SliderX>(std::bind(&StatSlider::onUpdate, this));
			else
				mSlider = this->template makeappend<SliderY>(std::bind(&StatSlider::onUpdate, this));

			mDisplay = this->template makeappend<Label>(toString(mStat.value()));

			this->updateSlider();
		}

		void onUpdate()
		{
			this->updateValue();
		}

		void updateSlider()
		{
			mSlider->resetMetrics(float(mStat.min()), float(mStat.max()), float(mStat.value()), float(mStat.step()));
			mSlider->updateKnob();
			mDisplay->setLabel(toString(mStat.value()));
		}

		void updateValue()
		{
			mStat.modify(T(mSlider->val()));
			this->notifyUpdate();
			mDisplay->setLabel(toString(mStat.value()));
		}

		void notifyUpdate() { ++this->mUpdate; if(this->mOnUpdate) this->mOnUpdate(mStat.value()); }

		using Typed<StatSlider<T>>::cls;

	protected:
		AutoStat<T>& mStat;

		Dimension mDim;

		Slider* mSlider;
		Label* mDisplay;
	};

	template class MK_UI_EXPORT _I_ StatSlider<float>;
	template class MK_UI_EXPORT _I_ StatSlider<int>;
}

#endif
