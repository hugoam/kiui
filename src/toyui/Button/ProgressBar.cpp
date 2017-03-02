//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Button/ProgressBar.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>

#include <toyui/Button/Slider.h>

namespace toy
{
	ProgressBar::ProgressBar(Piece& parent, Dimension dim, const Trigger& onUpdated)
		: Piece(parent, cls())
		, m_dim(dim)
		, m_percentage(0.f)
		, m_filler(*this)
		, m_spacer(*this)
		, m_onUpdated(onUpdated)
	{}

	void ProgressBar::setPercentage(float percentage)
	{
		m_percentage = percentage;
		m_filler.frame().setSpanDim(m_dim, percentage);
		m_spacer.frame().setSpanDim(m_dim, 1.f - percentage);
	}
}
