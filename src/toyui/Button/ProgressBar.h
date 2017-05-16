//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_PROGRESSBAR_H
#define TOY_PROGRESSBAR_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Frame/Uibox.h>
#include <toyui/Widget/Widget.h>
#include <toyui/Widget/Layout.h>
#include <toyui/Button/Button.h>
#include <toyui/Button/Slider.h>

namespace toy
{
	class TOY_UI_EXPORT ProgressBar : public Wedge
	{
	public:
		ProgressBar(Wedge& parent, Dimension dim = DIM_X, const Callback& onUpdated = nullptr);

		float percentage() { return m_percentage; }
		void setPercentage(float percentage);

		static Type& cls() { static Type ty("ProgressBar", Row::cls()); return ty; }

	protected:
		Dimension m_dim;
		Filler m_filler;
		Spacer m_spacer;
		SliderDisplay m_display;

		float m_percentage;

		Callback m_onUpdated;
	};
}

#endif
