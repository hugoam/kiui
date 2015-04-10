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
	class MK_UI_EXPORT SliderKnob : public Button, public Typed<SliderKnob, Button>, public Styled<SliderKnob>
	{
	public:
		SliderKnob(Dimension dim = DIM_X, Style* style = nullptr);

		float offset(float pos);

		bool leftDragStart(float xPos, float yPos);
		bool leftDrag(float xPos, float yPos, float xDif, float yDif);
		bool leftDragEnd(float xPos, float yPos);

		using Typed<SliderKnob, Button>::cls;
		using Styled<SliderKnob>::styleCls;

	protected:
		Dimension mDim;
		float mStartPos;
		float mStartOffset;
	};

	class MK_UI_EXPORT SpacerX : public Widget, public Typed<SpacerX, Widget>, public Styled<SpacerX>
	{
	public:
		SpacerX();

		using Typed<SpacerX, Widget>::cls;
	};

	class MK_UI_EXPORT SpacerY : public Widget, public Typed<SpacerY, Widget>, public Styled<SpacerY>
	{
	public:
		SpacerY();

		using Typed<SpacerY, Widget>::cls;
	};

	class MK_UI_EXPORT SliderKnobX : public SliderKnob, public Typed<SliderKnobX, SliderKnob>, public Styled<SliderKnobX>
	{
	public:
		SliderKnobX();

		using Typed<SliderKnobX, SliderKnob>::cls;
		using Styled<SliderKnobX>::styleCls;
	};

	class MK_UI_EXPORT SliderKnobY : public SliderKnob, public Typed<SliderKnobY, SliderKnob>, public Styled<SliderKnobY>
	{
	public:
		SliderKnobY();

		using Typed<SliderKnobY, SliderKnob>::cls;
		using Styled<SliderKnobY>::styleCls;
	};

	class MK_UI_EXPORT Slider : public Sheet, public Typed<Slider, Sheet>, public Styled<Slider>
	{
	public:
		Slider(Dimension dim = DIM_X, Style* style = nullptr, const Trigger& onUpdated = nullptr);

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

		using Typed<Slider, Sheet>::cls;

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

		float mNumSteps;
		int mStep;

		Trigger mOnUpdated;
	};

	class MK_UI_EXPORT SliderX : public Slider, public Typed<SliderX, Slider>, public Styled<SliderX>
	{
	public:
		SliderX(const Trigger& onUpdated = Trigger());

		using Typed<SliderX, Slider>::cls;
		using Styled<SliderX>::styleCls;
	};

	class MK_UI_EXPORT SliderY : public Slider, public Typed<SliderY, Slider>, public Styled<SliderY>
	{
	public:
		SliderY(const Trigger& onUpdated = Trigger());

		using Typed<SliderY, Slider>::cls;
		using Styled<SliderY>::styleCls;
	};

	class MK_UI_EXPORT SliderDisplay : public Label, public Typed<SliderDisplay, Label>, public Styled<SliderDisplay>
	{
	public:
		SliderDisplay(const string& label);

		using Typed<SliderDisplay, Label>::cls;
		using Styled<SliderDisplay>::styleCls;
	};

	template <class T>
	class StatSlider : public WTypedInput<AutoStat<T>, T>, public Typed<StatSlider<T>, WValue>//, public Styled<StatSlider<T>>
	{
	public:
		StatSlider(Lref& lref, std::function<void(T)> callback = nullptr, Dimension dim = DIM_X)
			: WTypedInput<AutoStat<T>, T>(lref, nullptr, callback)
			, mStat(this->mValue->template ref<AutoStat<T>>())
			, mDim(dim)
		{
			this->build();
		}

		StatSlider(AutoStat<T> value, std::function<void(T)> callback = nullptr, Dimension dim = DIM_X)
			: WTypedInput<AutoStat<T>, T>(value, nullptr, callback)
			, mStat(this->mValue->template ref<AutoStat<T>>())
			, mDim(dim)
		{
			this->build();
		}

		void build()
		{
			if(mDim == DIM_X)
				mSlider = this->template makeappend<SliderX>(std::bind(&StatSlider::updateStat, this));
			else
				mSlider = this->template makeappend<SliderY>(std::bind(&StatSlider::updateStat, this));

			mDisplay = this->template makeappend<SliderDisplay>(toString(mStat.value()));

			this->updateSlider();
		}

		void updateSlider()
		{
			mSlider->resetMetrics(float(mStat.min()), float(mStat.max()), float(mStat.value()), float(mStat.step()));
			mSlider->updateKnob();
			mDisplay->setLabel(toString(mStat.value()));
		}

		void updateStat()
		{
			mStat.modify(T(mSlider->val()));
			this->updateValue();
			mDisplay->setLabel(toString(mStat.value()));
		}

		void notifyUpdate() { ++this->mUpdate; if(this->mOnUpdate) this->mOnUpdate(mStat.value()); }

		using Typed<StatSlider<T>, WValue>::cls;

	protected:
		AutoStat<T>& mStat;

		Dimension mDim;

		Slider* mSlider;
		SliderDisplay* mDisplay;
	};

	template class MK_UI_EXPORT _I_ StatSlider<float>;
	template class MK_UI_EXPORT _I_ StatSlider<int>;
}

#endif
