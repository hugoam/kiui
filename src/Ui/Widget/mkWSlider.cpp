//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkWSlider.h>

#include <Object/String/mkStringConvert.h>
#include <Object/Util/mkStatString.h>

#include <Ui/Form/mkWidgets.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>

#include <Ui/Form/mkFValue.h>

#include <Ui/Form/mkHook.h>

#include <Ui/mkUiWindow.h>

namespace mk
{
	WSlideButton::WSlideButton(string clas, Dimension dim)
		: WButton("", clas)
		, mDim(dim)
	{}

	float WSlideButton::offset(float pos)
	{
		float length = mFrame->parent()->dsize(mDim) - mFrame->dsize(mDim);
		float offset = std::min(length, std::max(0.f, mStartOffset + pos - mStartPos));
		return offset;
	}

	bool WSlideButton::leftDragStart(float xPos, float yPos)
	{
		mStartPos = mDim == DIM_X ? xPos : yPos;
		mStartOffset = mFrame->dposition(mDim);
		updateState(ACTIVATED);
		return true;
	}

	bool WSlideButton::leftDrag(float xPos, float yPos, float xDif, float yDif)
	{
		UNUSED(xDif); UNUSED(yDif);
		mParent->as<WSlider>()->offsetChange(offset(mDim == DIM_X ? xPos : yPos), false);
		return true;
	}

	bool WSlideButton::leftDragEnd(float xPos, float yPos)
	{
		mParent->as<WSlider>()->offsetChange(offset(mDim == DIM_X ? xPos : yPos), true);
		updateState(ENABLED);
		return true;
	}

	WSlider::WSlider(Dimension dim, string clas, Trigger onUpdated)
		: Sheet(clas == "" ? (dim == DIM_X ? "xslider" : "yslider") : (dim == DIM_X ? "x" + clas : "y" + clas))
		, mDim(dim)
		, mOnUpdated(onUpdated)
	{}

	void WSlider::build()
	{
		Sheet::build();
		mSpaceBefore = this->makeappend<Widget>(mClas + "spacer");
		mButton = this->makeappend<WSlideButton>(mClas + "knob", mDim);
		mSpaceAfter = this->makeappend<Widget>(mClas + "spacer");
	}

	void WSlider::offsetChange(float offset, bool ended)
	{
		int step = int(offset / (mFrame->dsize(mDim) - mButton->frame()->dsize(mDim)) * (mNumSteps - 1.f));
		if(step != mStep)
		{
			mStep = step;
			mVal = mMin + step * mStepLength;
			this->updateKnob();
			this->sliderStep(mVal, ended);
		}
	}

	void WSlider::updateMetrics(float min, float max, float val, float stepLength, float knobLength)
	{
		if(min != mMin || max != mMax || val != mVal || stepLength != mStepLength || (knobLength && knobLength != mKnobLength))
			this->resetMetrics(min, max, val, stepLength, knobLength);
	}

	void WSlider::resetMetrics(float min, float max, float val, float stepLength, float knobLength)
	{
		mMin = min;
		mMax = max;
		mVal = val;
		mStepLength = stepLength;
		mNumSteps = (mMax - mMin) / stepLength + 1;
		mStep = int((mVal - mMin) / mStepLength);

		mKnobLength = knobLength ? knobLength : mStepLength;

		this->updateKnob();
	}

	void WSlider::updateKnob()
	{
		// @was : mButton->frame()->setPositionDim(mDim, offset);

		mSpaceBefore->frame()->setSpanDim(mDim, mVal);
		mButton->frame()->setSpanDim(mDim, mKnobLength);
		mSpaceAfter->frame()->setSpanDim(mDim, mMax - mVal);
	}

	WStatSlider::WStatSlider(Form* form, Lref& stat, Dimension dim)
		: Sheet("", form)
		, mStat(stat)
		, mDim(dim)
	{}

	void WStatSlider::build()
	{
		Sheet::build();
		mSlider = this->makeappend<WSlider>(mDim, "", std::bind(&WStatSlider::onUpdate, this));
		mDisplay = this->makeappend<WLabel>(mStat->getString(), "slidervalue");

		this->updateSlider();
	}

	void WStatSlider::onUpdate()
	{
		this->updateValue();
	}

	WIntSlider::WIntSlider(FIntStat* form)
		: WStatSlider(form, form->valref())
	{}

	void WIntSlider::updateSlider()
	{
		mSlider->resetMetrics(mStat->ref<Stat<int>>().min(), mStat->ref<Stat<int>>().max(), mStat->ref<Stat<int>>().value(), 1.f);
		mSlider->updateKnob();
		mDisplay->setLabel(mStat->getString());
	}

	void WIntSlider::updateValue()
	{
		mStat->ref<Stat<int>>().setValue(int(mSlider->val()));
		mDisplay->setLabel(mStat->getString());
	}

	WFloatSlider::WFloatSlider(FFloatStat* form)
		: WStatSlider(form, form->valref())
	{}
	
	void WFloatSlider::updateSlider()
	{
		mSlider->resetMetrics(mStat->ref<Stat<float>>().min(), mStat->ref<Stat<float>>().max(), mStat->ref<Stat<float>>().value(), 0.1f);
		mSlider->updateKnob();
		mDisplay->setLabel(mStat->getString());
	}

	void WFloatSlider::updateValue()
	{
		mStat->ref<Stat<float>>().setValue(mSlider->val());
		mDisplay->setLabel(mStat->getString());
	}
}
