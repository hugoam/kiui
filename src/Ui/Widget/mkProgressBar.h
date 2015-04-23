//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WPROGRESSBAR_H
#define MK_WPROGRESSBAR_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Frame/mkUibox.h>
#include <Ui/Widget/mkWidget.h>
#include <Ui/Widget/mkButton.h>

namespace mk
{
	class MK_UI_EXPORT FillerX : public Widget
	{
	public:
		FillerX();

		static StyleType& cls() { static StyleType ty(Widget::cls()); return ty; }
	};

	class MK_UI_EXPORT FillerY : public Widget
	{
	public:
		FillerY();

		static StyleType& cls() { static StyleType ty(Widget::cls()); return ty; }
	};

	class MK_UI_EXPORT ProgressBar : public Sheet
	{
	public:
		ProgressBar(Dimension dim = DIM_X, const Trigger& onUpdated = nullptr);

		float percentage() { return mPercentage; }
		void setPercentage(float percentage);

		static StyleType& cls() { static StyleType ty(Sheet::cls()); return ty; }

	protected:
		Dimension mDim;
		Widget& mFiller;
		Widget& mSpacer;

		float mPercentage;

		Trigger mOnUpdated;
	};

	class MK_UI_EXPORT ProgressBarX : public ProgressBar
	{
	public:
		ProgressBarX();

		static StyleType& cls() { static StyleType ty(Sheet::cls()); return ty; }
	};

	class MK_UI_EXPORT ProgressBarY : public ProgressBar
	{
	public:
		ProgressBarY();

		static StyleType& cls() { static StyleType ty(Sheet::cls()); return ty; }
	};
}

#endif
