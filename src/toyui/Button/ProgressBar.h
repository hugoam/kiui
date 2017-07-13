//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_PROGRESSBAR_H
#define TOY_PROGRESSBAR_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Button/Button.h>
#include <toyui/Button/Slider.h>

namespace toy
{
	class TOY_UI_EXPORT ProgressBar : public Wedge
	{
	public:
		ProgressBar(Wedge& parent, Dimension dim = DIM_X);

		void setPercentage(float percentage);

		static Type& cls() { static Type ty("ProgressBar", Wedge::Row()); return ty; }

	public:
		Dimension m_dim;
		Item m_filler;
		Item m_spacer;
		Label m_display;

		float m_percentage;
	};
}

#endif
