//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Frame/mkInk.h>

#include <Ui/Widget/mkWidget.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkLayer.h>

namespace mk
{
	void Inkbox::styleCorners()
	{
		mCorners = skin().mCornerRadius;
	}

	void Inkbox::updateCorners()
	{
		Inkbox& parent = mFrame.parent()->inkbox();
		if(parent.mCorners.null() || !skin().mWeakCorners || !mFrame.flow())
			return;

		mFitCorners = mFrame.parent()->layoutDim();

		if(mFrame.parent()->layoutDim() == DIM_X)
		{
			mCorners.setX0(fmaxf(0.f, parent.mCorners.x0() - mFrame.dposition(DIM_X)));
			mCorners.setY1(fmaxf(0.f, parent.mCorners.y1() - mFrame.dposition(DIM_X)));

			mCorners.setY0(fmaxf(0.f, parent.mCorners.y0() - (mFrame.parent()->dsize(DIM_X) - (mFrame.dposition(DIM_X) + mFrame.dsize(DIM_X)))));
			mCorners.setX1(fmaxf(0.f, parent.mCorners.x1() - (mFrame.parent()->dsize(DIM_X) - (mFrame.dposition(DIM_X) + mFrame.dsize(DIM_X)))));
		}
		else if(mFrame.parent()->layoutDim() == DIM_Y)
		{
			mCorners.setX0(fmaxf(0.f, parent.mCorners.x0() - mFrame.dposition(DIM_Y)));
			mCorners.setY0(fmaxf(0.f, parent.mCorners.y0() - mFrame.dposition(DIM_Y)));

			mCorners.setX1(fmaxf(0.f, parent.mCorners.x1() - (mFrame.parent()->dsize(DIM_Y) - (mFrame.dposition(DIM_Y) + mFrame.dsize(DIM_Y)))));
			mCorners.setY1(fmaxf(0.f, parent.mCorners.y1() - (mFrame.parent()->dsize(DIM_Y) - (mFrame.dposition(DIM_Y) + mFrame.dsize(DIM_Y)))));
		}
	}
}
