//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkProgressBar.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>

#include <Ui/Widget/mkSlider.h>

#include <Ui/mkUiWindow.h>

namespace mk
{
	FillerX::FillerX()
		: Widget()
	{
		mStyle = &cls();
	}

	FillerY::FillerY()
		: Widget()
	{
		mStyle = &cls();
	}

	ProgressBar::ProgressBar(Dimension dim, const Trigger& onUpdated)
		: Sheet()
		, mDim(dim)
		, mPercentage(0.f)
		, mOnUpdated(onUpdated)
		, mFiller(mDim == DIM_X ? (Widget&) this->makeappend<FillerX>() : (Widget&) this->makeappend<FillerY>())
		, mSpacer(mDim == DIM_X ? (Widget&) this->makeappend<SpacerX>() : (Widget&) this->makeappend<SpacerY>())
	{
		mStyle = &cls();
	}

	void ProgressBar::setPercentage(float percentage)
	{
		mPercentage = percentage;
		mFiller.frame().setSpanDim(mDim, percentage);
		mSpacer.frame().setSpanDim(mDim, 1.f - percentage);
	}

	ProgressBarX::ProgressBarX()
		: ProgressBar(DIM_X)
	{
		mStyle = &cls();
	}

	ProgressBarY::ProgressBarY()
		: ProgressBar(DIM_Y)
	{
		mStyle = &cls();
	}
}
