//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_SLIDER_H
#define TOY_SLIDER_H

/* toy */
#include <toyobj/Util/Stat.h>
#include <toyobj/String/StringConvert.h>
#include <toyui/Forward.h>
#include <toyui/Frame/Uibox.h>
#include <toyui/Edit/Value.h>
#include <toyui/Widget/Widget.h>
#include <toyui/Button/Button.h>
#include <toyui/Edit/TypeIn.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT SliderKnob : public Item
	{
	public:
		SliderKnob(Wedge& parent, Dimension dim = DIM_X, Type& type = cls());

		static Type& cls() { static Type ty("SliderKnob", Item::cls()); return ty; }

	protected:
		Dimension m_dim;
	};

	class _refl_ TOY_UI_EXPORT Slider : public WrapControl
	{
	public:
		Slider(Wedge& parent, Dimension dim = DIM_X, const Callback& onUpdated = nullptr, Type& type = cls());

		Widget& filler() { return m_filler; }
		SliderKnob& slider() { return m_button; }

		float val() { return m_val; }

		float length();

		virtual void dirtyLayout();

		void updateMetrics(float min, float max, float val, float stepLength, float knobLength = 0.f);
		void resetMetrics(float min, float max, float val, float stepLength, float knobLength = 0.f);

		void offsetChange(float offset, bool ended);
		
		void updateKnob();

		virtual void sliderStep(float value, bool ended) { UNUSED(value); UNUSED(ended); m_onUpdated(*this); }

		float offset(float pos);

		virtual bool leftDragStart(MouseEvent& mouseEvent);
		virtual bool leftDrag(MouseEvent& mouseEvent);
		virtual bool leftDragEnd(MouseEvent& mouseEvent);

		static Type& cls() { static Type ty("Slider", WrapControl::cls()); return ty; }

	protected:
		Dimension m_dim;
		Filler m_filler;
		SliderKnob m_button;
		Spacer m_spacer;

		float m_min;
		float m_max;
		float m_range;
		float m_val;
		float m_stepLength;
		float m_knobLength;

		float m_numSteps;
		int m_step;

		float m_startPos;
		float m_startOffset;

		Callback m_onUpdated;
	};

	class _refl_ TOY_UI_EXPORT SliderDisplay : public Label
	{
	public:
		SliderDisplay(Wedge& parent, const string& label);

		static Type& cls() { static Type ty("SliderDisplay", Label::cls()); return ty; }
	};
}

#endif
