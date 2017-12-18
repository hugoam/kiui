//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_SLIDER_H
#define TOY_SLIDER_H

/* toy */
#include <toyui/Types.h>
#include <toyui/Button/Button.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT Slider : public Wedge
	{
	public:
		Slider(const Params& params, Dimension dim = DIM_X, const Callback& onUpdated = nullptr, bool relative = false);

		float val() { return m_val; }

		virtual void dirtyLayout();

		void updateMetrics(float min, float max, float val, float stepLength, float knobLength = 0.f);
		void resetMetrics(float min, float max, float val, float stepLength, float knobLength = 0.f);

		void cursorChange(float cursor);
		
		void updateKnob();

		float cursor(MouseEvent& mouseEvent, float offset);

		virtual bool leftClick(MouseEvent& mouseEvent);

		virtual bool leftDragStart(MouseEvent& mouseEvent);
		virtual bool leftDrag(MouseEvent& mouseEvent);
		virtual bool leftDragEnd(MouseEvent& mouseEvent);

	public:
		Dimension m_dim;
		Widget m_filler;
		Widget m_button;
		Widget m_spacer;

	protected:
		float m_min;
		float m_max;
		float m_range;
		float m_val;
		float m_stepLength;
		float m_knobLength;

		float m_numSteps;
		int m_step;

		Callback m_onUpdated;

		float m_dragOffset;
		bool m_dragRelative;
	};
}

#endif
