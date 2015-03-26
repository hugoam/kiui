//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkWProgressBar.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>

#include <Ui/Widget/mkWSlider.h>

#include <Ui/mkUiWindow.h>

namespace mk
{
	WProgressFillerX::WProgressFillerX()
		: Widget(styleCls())
	{}

	WProgressFillerY::WProgressFillerY()
		: Widget(styleCls())
	{}

	WProgressBar::WProgressBar(Dimension dim, Style* style, const Trigger& onUpdated)
		: Sheet(style)
		, mDim(dim)
		, mPercentage(0.f)
		, mOnUpdated(onUpdated)
	{}

	void WProgressBar::build()
	{
		Sheet::build();

		if(mDim == DIM_X)
		{
			mFiller = this->makeappend<WProgressFillerX>();
			mSpacer = this->makeappend<WSpacerX>();
		}
		else
		{
			mFiller = this->makeappend<WProgressFillerY>();
			mSpacer = this->makeappend<WSpacerY>();
		}
	}

	void WProgressBar::setPercentage(float percentage)
	{
		mPercentage = percentage;
		mFiller->frame()->setSpanDim(mDim, percentage);
		mSpacer->frame()->setSpanDim(mDim, 1.f - percentage);
	}

	WProgressBarX::WProgressBarX()
		: WProgressBar(DIM_X, styleCls())
	{}

	WProgressBarY::WProgressBarY()
		: WProgressBar(DIM_Y, styleCls())
	{}
}
