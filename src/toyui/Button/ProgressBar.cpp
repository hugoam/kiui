//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Button/ProgressBar.h>

#include <toyobj/String/StringConvert.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Caption.h>

#include <toyui/Button/Slider.h>

namespace toy
{
	ProgressBar::ProgressBar(const Params& params, Dimension dim)
		: Wedge({ params, &cls<ProgressBar>() })
		, m_dim(dim)
		, m_filler({ this, &styles().filler })
		, m_spacer({ this, &styles().spacer })
		, m_display({ this, &styles().slider_display }, "0%")
		, m_percentage(0.f)
	{}

	void ProgressBar::setPercentage(float percentage)
	{
		m_percentage = percentage;
		m_filler.frame().setSpanDim(m_dim, percentage);
		m_spacer.frame().setSpanDim(m_dim, 1.f - percentage);
		m_display.frame().setCaption(toString(m_percentage) + "%");
	}
}
