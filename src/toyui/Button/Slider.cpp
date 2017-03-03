//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Button/Slider.h>

#include <toyobj/String/StringConvert.h>
#include <toyobj/Util/StatString.h>

#include <toyui/Widget/Layout.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>

#include <toyui/Button/ProgressBar.h>

namespace toy
{
	SliderKnob::SliderKnob(Wedge& parent, Dimension dim, Type& type)
		: Item(parent, type)
		, m_dim(dim)
	{
		//this->content().setEmpty();
	}

	Slider::Slider(Wedge& parent, Dimension dim, const Trigger& onUpdated, Type& type)
		: WrapControl(parent, type)
		, m_dim(dim)
		, m_filler(*this)
		, m_button(*this, dim)
		, m_spacer(*this)
		, m_startPos(0.f)
		, m_startOffset(0.f)
		, m_onUpdated(onUpdated)
	{
		m_frame->setLength(dim);
	}

	void Slider::nextFrame(size_t tick, size_t delta)
	{
		if(m_frame->dirty() >= Frame::DIRTY_LAYOUT)
			this->updateKnob();

		Wedge::nextFrame(tick, delta);
	}

	float Slider::offset(float pos)
	{
		float length = m_frame->dsize(m_dim) - (m_button.frame().flow() ? m_button.frame().dsize(m_dim) : 0.f);
		float offset = std::min(length, std::max(0.f, m_startOffset + pos - m_startPos));
		return offset;
	}

	void Slider::leftDragStart(MouseEvent& mouseEvent)
	{
		DimFloat absolute = m_frame->absolutePosition();
		m_startPos = m_dim == DIM_X ? mouseEvent.posX : mouseEvent.posY;
		m_startOffset = m_button.frame().flow() ? m_button.frame().dposition(m_dim) : (m_startPos - absolute[m_dim]);
		this->activate();
		m_button.activate();
	}

	void Slider::leftDrag(MouseEvent& mouseEvent)
	{
		this->offsetChange(this->offset(m_dim == DIM_X ? mouseEvent.posX : mouseEvent.posY), false);
	}

	void Slider::leftDragEnd(MouseEvent& mouseEvent)
	{
		this->offsetChange(this->offset(m_dim == DIM_X ? mouseEvent.posX : mouseEvent.posY), true);
		this->deactivate();
		m_button.deactivate();
	}

	float Slider::length()
	{
		if(m_button.frame().dexpand(m_dim))
			return m_frame->dsize(m_dim);
		else
			return m_frame->dsize(m_dim) - m_button.frame().dsize(m_dim);
	}

	void Slider::offsetChange(float offset, bool ended)
	{
		int step = int(round(offset / this->length() * (m_numSteps - 1.f)));
		if(step != m_step)
		{
			m_step = step;
			m_val = m_min + step * m_stepLength;
			this->updateKnob();
			this->sliderStep(m_val, ended);
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

		this->updateKnob(); // @useless ?
	}

	void Slider::updateKnob()
	{
		if(m_frame->hidden())
			return;

		float knobspan = m_knobLength / m_range;
		float fillspan = (m_val - m_min) / m_range;
		float spacespan = 1.f - fillspan - knobspan;

		if(m_button.frame().flow() && m_button.frame().dexpand(m_dim))
			m_button.frame().setSpanDim(m_dim, knobspan);

		m_filler.frame().setSpanDim(m_dim, fillspan);
		m_spacer.frame().setSpanDim(m_dim, spacespan);

		this->markDirty();
	}

	SliderDisplay::SliderDisplay(Wedge& parent, const string& label)
		: Label(parent, label, cls())
	{}
}
