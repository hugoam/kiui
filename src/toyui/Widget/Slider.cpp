//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Widget/Slider.h>

#include <toyobj/String/StringConvert.h>
#include <toyobj/Util/StatString.h>

#include <toyui/Widget/Widgets.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>

#include <toyui/Widget/ProgressBar.h>

#include <iostream>

namespace toy
{
	SliderKnob::SliderKnob(Dimension dim, StyleType& type)
		: Button("", Trigger(), type)
		, m_dim(dim)
		, m_startPos(0.f)
		, m_startOffset(0.f)
	{
		m_frame->setEmpty();
	}

	float SliderKnob::offset(float pos)
	{
		float length = m_frame->parent()->dsize(m_dim) - (m_frame->dexpand(m_dim) ? 0.f : m_frame->dsize(m_dim));
		float offset = std::min(length, std::max(0.f, m_startOffset + pos - m_startPos));
		return offset;
	}

	void SliderKnob::leftDragStart(MouseEvent& mouseEvent)
	{
		m_startPos = m_dim == DIM_X ? mouseEvent.posX : mouseEvent.posY;
		m_startOffset = m_frame->dexpand(m_dim) ? (m_startPos - m_frame->parent()->dabsolute(m_dim)) : m_frame->dposition(m_dim);
		this->activate();
	}

	void SliderKnob::leftDrag(MouseEvent& mouseEvent)
	{
		m_parent->as<Slider>().offsetChange(offset(m_dim == DIM_X ? mouseEvent.posX : mouseEvent.posY), false);
	}

	void SliderKnob::leftDragEnd(MouseEvent& mouseEvent)
	{
		m_parent->as<Slider>().offsetChange(offset(m_dim == DIM_X ? mouseEvent.posX : mouseEvent.posY), true);
		this->deactivate();
	}

	SliderKnobX::SliderKnobX()
		: SliderKnob(DIM_X, cls())
	{}

	SliderKnobY::SliderKnobY()
		: SliderKnob(DIM_Y, cls())
	{}

	SpacerX::SpacerX()
		: Widget(cls())
	{}

	SpacerY::SpacerY()
		: Widget(cls())
	{}


	Slider::Slider(Dimension dim, const Trigger& onUpdated, StyleType& type)
		: Sheet(type)
		, m_dim(dim)
		, m_filler(dim == DIM_X ? (Widget&) this->makeappend<FillerX>() : (Widget&) this->makeappend<FillerY>())
		, m_button(dim == DIM_X ? (SliderKnob&) this->makeappend<SliderKnobX>() : (SliderKnob&) this->makeappend<SliderKnobY>())
		, m_onUpdated(onUpdated)
	{}
	
	SliderX::SliderX(const Trigger& onUpdated)
		: Slider(DIM_X, onUpdated, cls())
	{}

	SliderY::SliderY(const Trigger& onUpdated)
		: Slider(DIM_Y, onUpdated, cls())
	{}

	void Slider::nextFrame(size_t tick, size_t delta)
	{
		UNUSED(tick); UNUSED(delta);
		if(m_frame->dirty() >= Frame::DIRTY_FRAME)
			this->updateKnob();
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
		m_numSteps = (m_max - m_min) / m_stepLength + 1;
		m_step = int((m_val - m_min) / m_stepLength);

		m_knobLength = knobLength ? knobLength : m_stepLength;

		this->markDirty();
		//this->updateKnob(); @useless ?
	}

	void Slider::updateKnob()
	{
		if(!(m_state & BOUND) || m_frame->hidden())
			return;

		if(m_button.frame().dmanual(m_dim))
			m_button.frame().setSizeDim(m_dim, std::max(m_frame->dsize(m_dim == DIM_X ? DIM_Y : DIM_X), m_knobLength / (m_knobLength + m_max - m_min) * m_frame->dsize(m_dim)));

		float pos = (m_val - m_min) / (m_max - m_min) * this->length();		
		m_filler.frame().setSizeDim(m_dim, pos);
		m_button.frame().parent()->positionDepth(m_button.frame());

		if(!m_button.frame().dexpand(m_dim))
			m_button.frame().setPositionDim(m_dim, pos);
		else
			m_button.frame().setPositionDim(m_dim, 0);
	}

	SliderDisplay::SliderDisplay(const string& label)
		: Label(label, cls())
	{}
}
