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
#include <Ui/Form/mkFValue.h>
#include <Ui/Widget/mkWidget.h>
#include <Ui/Widget/mkWButton.h>
#include <Ui/Widget/mkWTypeIn.h>

namespace mk
{
	class MK_UI_EXPORT WSliderKnob : public WButton, public Styled<WSliderKnob>
	{
	public:
		WSliderKnob(Dimension dim = DIM_X, Style* style = nullptr);

		float offset(float pos);

		bool leftDragStart(float xPos, float yPos);
		bool leftDrag(float xPos, float yPos, float xDif, float yDif);
		bool leftDragEnd(float xPos, float yPos);

		using Styled<WSliderKnob>::styleCls;

	protected:
		Dimension mDim;
		float mStartPos;
		float mStartOffset;
	};

	class MK_UI_EXPORT WSpacerX : public Widget, public Styled<WSpacerX>
	{
	public:
		WSpacerX();
	};

	class MK_UI_EXPORT WSpacerY : public Widget, public Styled<WSpacerY>
	{
	public:
		WSpacerY();
	};

	class MK_UI_EXPORT WSliderKnobX : public WSliderKnob, public Styled<WSliderKnobX>
	{
	public:
		WSliderKnobX();

		using Styled<WSliderKnobX>::styleCls;
	};

	class MK_UI_EXPORT WSliderKnobY : public WSliderKnob, public Styled<WSliderKnobY>
	{
	public:
		WSliderKnobY();

		using Styled<WSliderKnobY>::styleCls;
	};

	class MK_UI_EXPORT WSlider : public Sheet, public Styled<WSlider>
	{
	public:
		WSlider(Dimension dim = DIM_X, Style* style = nullptr, const Trigger& onUpdated = nullptr);

		void build();

		Widget* spaceBefore() { return mSpaceBefore; }
		WSliderKnob* slider() { return mButton; }
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
		WSliderKnob* mButton;
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

	class MK_UI_EXPORT WSliderX : public WSlider, public Styled<WSliderX>
	{
	public:
		WSliderX(const Trigger& onUpdated = Trigger());

		void build();

		using Styled<WSliderX>::styleCls;
	};

	class MK_UI_EXPORT WSliderY : public WSlider, public Styled<WSliderY>
	{
	public:
		WSliderY(const Trigger& onUpdated = Trigger());

		void build();

		using Styled<WSliderY>::styleCls;
	};

	template <class T>
	class WStatSlider : public WTypedInput<T>, public Typed<WStatSlider<T>>//, public Styled<WStatSlider<T>>
	{
	public:
		WStatSlider(Lref& lref, std::function<void(T)> callback = nullptr, Dimension dim = DIM_X)
			: WTypedInput<T>(lref, nullptr, callback)
			, mStat(lref->ref<AutoStat<T>>())
			, mDim(dim)
		{}

		void build()
		{
			Sheet::build();
			if(mDim == DIM_X)
				mSlider = this->makeappend<WSliderX>(std::bind(&WStatSlider::onUpdate, this));
			else
				mSlider = this->makeappend<WSliderY>(std::bind(&WStatSlider::onUpdate, this));

			mDisplay = this->makeappend<WLabel>(toString(mStat.value()));

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

		void notifyUpdate() { ++mUpdate; if(mOnUpdate) mOnUpdate(mStat.value()); if(mForm) mForm->as<FValue>()->updateValue(); }

		using Typed<WStatSlider<T>>::cls;

	protected:
		AutoStat<T>& mStat;

		Dimension mDim;

		WSlider* mSlider;
		WLabel* mDisplay;
	};

	template class MK_UI_EXPORT _I_ WStatSlider<float>;
	template class MK_UI_EXPORT _I_ WStatSlider<int>;
}

#endif
