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
	ProgressFillerX::ProgressFillerX()
		: Widget(styleCls())
	{}

	ProgressFillerY::ProgressFillerY()
		: Widget(styleCls())
	{}

	ProgressBar::ProgressBar(Dimension dim, Style* style, const Trigger& onUpdated)
		: Sheet(style)
		, mDim(dim)
		, mPercentage(0.f)
		, mOnUpdated(onUpdated)
	{
		if(mDim == DIM_X)
		{
			mFiller = this->makeappend<ProgressFillerX>();
			mSpacer = this->makeappend<SpacerX>();
		}
		else
		{
			mFiller = this->makeappend<ProgressFillerY>();
			mSpacer = this->makeappend<SpacerY>();
		}
	}

	void ProgressBar::setPercentage(float percentage)
	{
		mPercentage = percentage;
		mFiller->frame()->setSpanDim(mDim, percentage);
		mSpacer->frame()->setSpanDim(mDim, 1.f - percentage);
	}

	ProgressBarX::ProgressBarX()
		: ProgressBar(DIM_X, styleCls())
	{}

	ProgressBarY::ProgressBarY()
		: ProgressBar(DIM_Y, styleCls())
	{}
}
