//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WPROGRESSBAR_H
#define MK_WPROGRESSBAR_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Frame/mkUibox.h>
#include <Ui/Widget/mkWidget.h>
#include <Ui/Widget/mkWButton.h>

namespace mk
{
	class MK_UI_EXPORT WProgressBar : public Sheet
	{
	public:
		WProgressBar(Dimension dim = DIM_X, Style* style = nullptr, const Trigger& onUpdated = nullptr);

		void build();

		float percentage() { return mPercentage; }
		void setPercentage(float percentage);

	protected:
		Dimension mDim;
		Widget* mFiller;

		float mPercentage;

		Trigger mOnUpdated;
	};

	class MK_UI_EXPORT WProgressBarX : public WProgressBar, public Styled<WProgressBarX>
	{
	public:
		WProgressBarX();
	};

	class MK_UI_EXPORT WProgressBarY : public WProgressBar, public Styled<WProgressBarY>
	{
	public:
		WProgressBarY();
	};
}

#endif
