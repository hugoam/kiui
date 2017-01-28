//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Widget/ProgressBar.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>

#include <toyui/Widget/Slider.h>

namespace toy
{
	FillerX::FillerX()
		: Widget(cls())
	{}

	FillerY::FillerY()
		: Widget(cls())
	{}

	ProgressBar::ProgressBar(StyleType& type, Dimension dim, const Trigger& onUpdated)
		: Sheet(type)
		, m_dim(dim)
		, m_percentage(0.f)
		, m_filler(m_dim == DIM_X ? (Widget&) this->makeappend<FillerX>() : (Widget&) this->makeappend<FillerY>())
		, m_spacer(m_dim == DIM_X ? (Widget&) this->makeappend<SpacerX>() : (Widget&) this->makeappend<SpacerY>())
		, m_onUpdated(onUpdated)
	{}

	void ProgressBar::setPercentage(float percentage)
	{
		m_percentage = percentage;
		m_filler.frame().setSpanDim(m_dim, percentage);
		m_spacer.frame().setSpanDim(m_dim, 1.f - percentage);
	}

	ProgressBarX::ProgressBarX()
		: ProgressBar(cls(), DIM_X)
	{}

	ProgressBarY::ProgressBarY()
		: ProgressBar(cls(), DIM_Y)
	{}
}
