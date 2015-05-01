//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkSlider.h>

#include <Object/String/mkStringConvert.h>
#include <Object/Util/mkStatString.h>

#include <Ui/Form/mkWidgets.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>

#include <Ui/Widget/mkProgressBar.h>

#include <iostream>

namespace mk
{
	SliderKnob::SliderKnob(Dimension dim)
		: Button("")
		, mDim(dim)
		, mStartPos(0.f)
		, mStartOffset(0.f)
	{}

	float SliderKnob::offset(float pos)
	{
		float length = mFrame->parent()->dsize(mDim) - (mFrame->dexpand(mDim) ? 0.f : mFrame->dsize(mDim));
		float offset = std::min(length, std::max(0.f, mStartOffset + pos - mStartPos));
		return offset;
	}

	bool SliderKnob::leftDragStart(float xPos, float yPos)
	{
		mStartPos = mDim == DIM_X ? xPos : yPos;
		mStartOffset = mFrame->dexpand(mDim) ? (mStartPos - mFrame->parent()->dabsolute(mDim)) : mFrame->dposition(mDim);
		toggleState(ACTIVATED);
		return true;
	}

	bool SliderKnob::leftDrag(float xPos, float yPos, float xDif, float yDif)
	{
		UNUSED(xDif); UNUSED(yDif);
		mParent->as<Slider>().offsetChange(offset(mDim == DIM_X ? xPos : yPos), false);
		return true;
	}

	bool SliderKnob::leftDragEnd(float xPos, float yPos)
	{
		mParent->as<Slider>().offsetChange(offset(mDim == DIM_X ? xPos : yPos), true);
		toggleState(ACTIVATED);
		return true;
	}

	SliderKnobX::SliderKnobX()
		: SliderKnob(DIM_X)
	{
		mStyle = &cls();
	}

	SliderKnobY::SliderKnobY()
		: SliderKnob(DIM_Y)
	{
		mStyle = &cls();
	}

	SpacerX::SpacerX()
		: Widget()
	{
		mStyle = &cls();
	}

	SpacerY::SpacerY()
		: Widget()
	{
		mStyle = &cls();
	}


	Slider::Slider(Dimension dim, const Trigger& onUpdated)
		: Sheet()
		, mDim(dim)
		, mOnUpdated(onUpdated)
		, mFiller(dim == DIM_X ? (Widget&) this->makeappend<FillerX>() : (Widget&) this->makeappend<FillerY>())
		, mButton(dim == DIM_X ? (SliderKnob&) this->makeappend<SliderKnobX>() : (SliderKnob&) this->makeappend<SliderKnobY>())
	{
		mStyle = &cls();
	}
	
	SliderX::SliderX(const Trigger& onUpdated)
		: Slider(DIM_X, onUpdated)
	{
		mStyle = &cls();
	}

	SliderY::SliderY(const Trigger& onUpdated)
		: Slider(DIM_Y, onUpdated)
	{
		mStyle = &cls();
	}

	void Slider::nextFrame(size_t tick, size_t delta)
	{
		bool dirty = mFrame->dirty() >= Frame::DIRTY_WIDGET;
		Sheet::nextFrame(tick, delta);
		if(dirty)
			this->updateKnob();
	}

	float Slider::length()
	{
		if(mButton.frame().dexpand(mDim))
			return mFrame->dsize(mDim);
		else
			return mFrame->dsize(mDim) - mButton.frame().dsize(mDim);
	}

	void Slider::offsetChange(float offset, bool ended)
	{
		int step = int(round(offset / this->length() * (mNumSteps - 1.f)));
		if(step != mStep)
		{
			mStep = step;
			mVal = mMin + step * mStepLength;
			this->updateKnob();
			this->sliderStep(mVal, ended);
		}
	}

	void Slider::updateMetrics(float min, float max, float val, float stepLength, float knobLength)
	{
		if(min != mMin || max != mMax || val != mVal || stepLength != mStepLength || (knobLength && knobLength != mKnobLength))
			this->resetMetrics(min, max, val, stepLength, knobLength);
	}

	void Slider::resetMetrics(float min, float max, float val, float stepLength, float knobLength)
	{
		mMin = min;
		mMax = max;
		mVal = val;
		mStepLength = stepLength;
		mNumSteps = (mMax - mMin) / stepLength + 1;
		mStep = int((mVal - mMin) / mStepLength);

		mKnobLength = knobLength ? knobLength : mStepLength;

		this->markDirty();
		this->updateKnob();
	}

	void Slider::updateKnob()
	{
		if(!(mState & BOUND) || !mFrame->visible())
			return;

		float pos = (mVal - mMin) / (mMax - mMin) * this->length();		
		mFiller.frame().setSizeDim(mDim, pos);
		mButton.frame().parent()->positionDepth(&mButton.frame());

		if(!mButton.frame().dexpand(mDim))
			mButton.frame().setPositionDim(mDim, pos);
		else
			mButton.frame().setPositionDim(mDim, 0);

		if(mButton.frame().dmanual(mDim))
			mButton.frame().setSizeDim(mDim, std::max(mFrame->dsize(mDim == DIM_X ? DIM_Y : DIM_X), mKnobLength / (mKnobLength + mMax - mMin) * mFrame->dsize(mDim)));
	}

	SliderDisplay::SliderDisplay(const string& label)
		: Label(label)
	{
		mStyle = &cls();
	}
}
