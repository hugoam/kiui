//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_PROGRESSBAR_H
#define TOY_PROGRESSBAR_H

/* toy */
#include <toyui/Types.h>
#include <toyui/Button/Button.h>
#include <toyui/Button/Slider.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT Fillbar : public Wedge
	{
	public:
		Fillbar(const Params& params, Dimension dim = DIM_X);

		void setPercentage(float percentage);

	public:
		Dimension m_dim;
		Widget m_filler;
		Widget m_spacer;
		Label m_display;

		float m_percentage;
	};
}

#endif
