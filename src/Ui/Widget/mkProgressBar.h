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
	class MK_UI_EXPORT FillerX : public Widget, public Typed<FillerX, Widget>, public Styled<FillerX>
	{
	public:
		FillerX();

		using Typed<FillerX, Widget>::cls;
	};

	class MK_UI_EXPORT FillerY : public Widget, public Typed<FillerY, Widget>, public Styled<FillerY>
	{
	public:
		FillerY();

		using Typed<FillerY, Widget>::cls;
	};

	class MK_UI_EXPORT ProgressBar : public Sheet
	{
	public:
		ProgressBar(Dimension dim = DIM_X, Style* style = nullptr, const Trigger& onUpdated = nullptr);

		float percentage() { return mPercentage; }
		void setPercentage(float percentage);

	protected:
		Dimension mDim;
		Widget* mFiller;
		Widget* mSpacer;

		float mPercentage;

		Trigger mOnUpdated;
	};

	class MK_UI_EXPORT ProgressBarX : public ProgressBar, public Typed<ProgressBarX, Sheet>, public Styled<ProgressBarX>
	{
	public:
		ProgressBarX();

		using Typed<ProgressBarX, Sheet>::cls;
	};

	class MK_UI_EXPORT ProgressBarY : public ProgressBar, public Typed<ProgressBarY, Sheet>, public Styled<ProgressBarY>
	{
	public:
		ProgressBarY();

		using Typed<ProgressBarY, Sheet>::cls;
	};
}

#endif
