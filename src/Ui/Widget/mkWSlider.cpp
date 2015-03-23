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
	WSliderKnob::WSliderKnob(Dimension dim, Style* style)
		: WButton("", style)
		, mDim(dim)
		, mStartPos(0.f)
		, mStartOffset(0.f)
	{}

	float WSliderKnob::offset(float pos)
	{
		float length = mFrame->parent()->dsize(mDim) - mFrame->dsize(mDim);
		float offset = std::min(length, std::max(0.f, mStartOffset + pos - mStartPos));
		return offset;
	}

	bool WSliderKnob::leftDragStart(float xPos, float yPos)
	{
		mStartPos = mDim == DIM_X ? xPos : yPos;
		mStartOffset = mFrame->dposition(mDim);
		toggleState(ACTIVATED);
		return true;
	}

	bool WSliderKnob::leftDrag(float xPos, float yPos, float xDif, float yDif)
	{
		UNUSED(xDif); UNUSED(yDif);
		mParent->as<WSlider>()->offsetChange(offset(mDim == DIM_X ? xPos : yPos), false);
		return true;
	}

	bool WSliderKnob::leftDragEnd(float xPos, float yPos)
	{
		mParent->as<WSlider>()->offsetChange(offset(mDim == DIM_X ? xPos : yPos), true);
		toggleState(ACTIVATED);
		return true;
	}

	WSliderKnobX::WSliderKnobX()
		: WSliderKnob(DIM_X, styleCls())
	{}

	WSliderKnobY::WSliderKnobY()
		: WSliderKnob(DIM_Y, styleCls())
	{}

	WSpacerX::WSpacerX()
		: Widget(styleCls())
	{}

	WSpacerY::WSpacerY()
		: Widget(styleCls())
	{}


	WSlider::WSlider(Dimension dim, Style* style, const Trigger& onUpdated)
		: Sheet(style ? style : styleCls())
		, mDim(dim)
		, mOnUpdated(onUpdated)
		, mFixedKnob(false)
	{}
	
	WSliderX::WSliderX(const Trigger& onUpdated)
		: WSlider(DIM_X, styleCls(), onUpdated)
	{}

	void WSliderX::build()
	{
		mSpaceBefore = this->makeappend<WSpacerX>();
		mButton = this->makeappend<WSliderKnobX>();
		mSpaceAfter = this->makeappend<WSpacerX>();

		WSlider::build();
	}

	WSliderY::WSliderY(const Trigger& onUpdated)
		: WSlider(DIM_Y, styleCls(), onUpdated)
	{}

	void WSliderY::build()
	{
		mSpaceBefore = this->makeappend<WSpacerY>();
		mButton = this->makeappend<WSliderKnobY>();
		mSpaceAfter = this->makeappend<WSpacerY>();

		WSlider::build();
	}

	void WSlider::build()
	{
		Sheet::build();

		if(mButton->frame()->style()->d_sizing[mDim] == FIXED)
			mFixedKnob = true;

		/*this->stripe()->initWeights();

		if(mFixedKnob)
			this->stripe()->weights() = { 1.f, -1.f, 1.f };
		else
			this->stripe()->weights() = { 1.f, 1.f, 1.f };*/
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
		mSpaceBefore->frame()->setSpanDim(mDim, mVal - mMin);
		mSpaceAfter->frame()->setSpanDim(mDim, mMax - mVal);

		if(!mFixedKnob)
			mButton->frame()->setSpanDim(mDim, mKnobLength);
	}
}
