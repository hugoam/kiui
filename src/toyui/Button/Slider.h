//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_SLIDER_H
#define TOY_SLIDER_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Button/Button.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT Slider : public Wedge
	{
	public:
		Slider(Wedge& parent, Dimension dim = DIM_X, const Callback& onUpdated = nullptr, bool relative = false, Type& type = cls());

		Widget& filler() { return m_filler; }
		Item& knob() { return m_button; }

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

		static Type& cls() { static Type ty("Slider", Wedge::WrapControl()); return ty; }

		static Type& Knob() { static Type ty("SliderKnob", Item::cls()); return ty; }
		static Type& Display() { static Type ty("SliderDisplay", Label::cls()); return ty; }

	protected:
		Dimension m_dim;
		Item m_filler;
		Item m_button;
		Item m_spacer;

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
