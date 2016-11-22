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

		static StyleType& cls() { static StyleType ty("FillerX", Widget::cls()); return ty; }
	};

	class MK_UI_EXPORT FillerY : public Widget
	{
	public:
		FillerY();

		static StyleType& cls() { static StyleType ty("FillerY", Widget::cls()); return ty; }
	};

	class MK_UI_EXPORT ProgressBar : public Sheet
	{
	public:
		ProgressBar(StyleType& type = cls(), Dimension dim = DIM_X, const Trigger& onUpdated = nullptr);

		float percentage() { return m_percentage; }
		void setPercentage(float percentage);

		static StyleType& cls() { static StyleType ty("ProgressBar", Sheet::cls()); return ty; }

	protected:
		Dimension m_dim;
		Widget& m_filler;
		Widget& m_spacer;

		float m_percentage;

		Trigger m_onUpdated;
	};

	class MK_UI_EXPORT ProgressBarX : public ProgressBar
	{
	public:
		ProgressBarX();

		static StyleType& cls() { static StyleType ty("ProgressBarX", Sheet::cls()); return ty; }
	};

	class MK_UI_EXPORT ProgressBarY : public ProgressBar
	{
	public:
		ProgressBarY();

		static StyleType& cls() { static StyleType ty("ProgressBarY", Sheet::cls()); return ty; }
	};
}

#endif
