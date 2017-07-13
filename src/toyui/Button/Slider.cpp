//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Button/Slider.h>

#include <toyobj/String/StringConvert.h>
#include <toyobj/Util/StatString.h>

namespace toy
{
	Slider::Slider(Wedge& parent, Dimension dim, const Callback& onUpdated, bool relative, Type& type)
		: Wedge(parent, type)
		, m_dim(dim)
		, m_filler(*this, Item::Filler())
		, m_button(*this, Slider::Knob())
		, m_spacer(*this, Item::Spacer())
		, m_onUpdated(onUpdated)
		, m_dragRelative(relative)
	{
		m_frame->d_length = dim;
	}

	void Slider::dirtyLayout()
	{
		this->updateKnob();
	}

	float Slider::cursor(MouseEvent& mouseEvent, float offset)
	{
		float size = m_frame->d_size[m_dim];
		float knob = m_button.frame().d_size[m_dim];
		return std::min(size - knob, std::max(0.f, mouseEvent.relative[m_dim] + offset)) / size;
	}

	bool Slider::leftClick(MouseEvent& mouseEvent)
	{
		float offset = -m_button.frame().d_size[m_dim] / 2.f;
		this->cursorChange(this->cursor(mouseEvent, offset));
		return true;
	}

	bool Slider::leftDragStart(MouseEvent& mouseEvent)
	{
		m_dragOffset = m_dragRelative ? mouseEvent.relative[m_dim] - m_filler.frame().d_size[m_dim] : 0.f;
		this->enableState(TRIGGERED);
		m_button.enableState(TRIGGERED);
		return true;
	}

	bool Slider::leftDrag(MouseEvent& mouseEvent)
	{
		this->cursorChange(this->cursor(mouseEvent, -m_dragOffset));
		return true;
	}

	bool Slider::leftDragEnd(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		this->disableState(TRIGGERED);
		m_button.disableState(TRIGGERED);
		return true;
	}

	void Slider::cursorChange(float offset)
	{
		int step = int(round(offset * (m_numSteps - 1.f)));
		if(step != m_step)
		{
			m_step = step;
			m_val = m_min + step * m_stepLength;
			this->updateKnob();
			m_onUpdated(*this);
		}
	}

	void Slider::updateMetrics(float min, float max, float val, float stepLength, float knobLength)
	{
		if(min != m_min || max != m_max || val != m_val || stepLength != m_stepLength || (knobLength && knobLength != m_knobLength))
			this->resetMetrics(min, max, val, stepLength, knobLength);
	}

	void Slider::resetMetrics(float min, float max, float val, float stepLength, float knobLength)
	{
		m_min = min;
		m_max = max;
		m_val = val;
		m_stepLength = stepLength == 0 ? 1.f : stepLength;
		//m_knobLength = knobLength ? knobLength : m_stepLength;
		m_knobLength = knobLength;
		m_range = m_max + m_knobLength - m_min;
		m_numSteps = m_range / m_stepLength + 1;
		m_step = int((m_val - m_min) / m_stepLength);

		this->updateKnob();
	}

	void Slider::updateKnob()
	{
		if(m_frame->d_hidden)
			return;

		float knobspan = m_knobLength / m_range;
		float fillspan = (m_val - m_min) / m_range;
		float spacespan = 1.f - fillspan - knobspan;

		m_button.frame().setSpanDim(m_dim, knobspan);
		m_filler.frame().setSpanDim(m_dim, fillspan);
		m_spacer.frame().setSpanDim(m_dim, spacespan);
	}
}
