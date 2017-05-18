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
	class _I_ TOY_UI_EXPORT SliderKnob : public Item
	{
	public:
		SliderKnob(Wedge& parent, Dimension dim = DIM_X, Type& type = cls());

		static Type& cls() { static Type ty("SliderKnob", Item::cls()); return ty; }

	protected:
		Dimension m_dim;
	};

	class _I_ TOY_UI_EXPORT Slider : public WrapControl
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

		virtual void leftDragStart(MouseEvent& mouseEvent);
		virtual void leftDrag(MouseEvent& mouseEvent);
		virtual void leftDragEnd(MouseEvent& mouseEvent);

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

	class _I_ TOY_UI_EXPORT SliderDisplay : public Label
	{
	public:
		SliderDisplay(Wedge& parent, const string& label);

		static Type& cls() { static Type ty("SliderDisplay", Label::cls()); return ty; }
	};

	template <class T>
	class StatSlider : public WValue
	{
	public:
		StatSlider(Wedge& parent, Lref& lref, std::function<void(T)> callback = nullptr, Dimension dim = DIM_X)
			: WValue(parent, lref, this->cls(), callback ? [callback](Lref& lref) { callback(lref->get<AutoStat<T>>()); } : OnUpdate())
			, m_stat(this->m_value->template ref<AutoStat<T>>())
			, m_dim(dim)
			, m_slider(*this, m_dim, std::bind(&StatSlider::updateStat, this))
			, m_display(*this, this->getString())
		{
			this->updateSlider();
		}

		StatSlider(Wedge& parent, AutoStat<T> value, std::function<void(T)> callback = nullptr, Dimension dim = DIM_X)
			: WValue(parent, lref(value), this->cls(), callback ? [callback](Lref& lref) { callback(lref->get<AutoStat<T>>()); } : OnUpdate())
			, m_stat(this->m_value->template ref<AutoStat<T>>())
			, m_dim(dim)
			, m_slider(*this, m_dim, std::bind(&StatSlider::updateStat, this))
			, m_display(*this, this->getString())
		{
			this->updateSlider();
		}

		void updateSlider()
		{
			m_slider.resetMetrics(float(m_stat.min()), float(m_stat.max()), float(m_stat.value()), float(m_stat.step()));
			m_slider.updateKnob();
			m_display.setLabel(this->getString());
		}

		void updateStat()
		{
			m_stat.modify(T(m_slider.val()));
			m_display.setLabel(this->getString());
			this->triggerModify();
		}

		void updateValue(T val) { m_stat.modify(val); this->triggerUpdate(); }
		void modifyValue(T val) { m_stat.modify(val); this->triggerModify(); }

		void notifyUpdate() { this->updateSlider(); }
		void notifyModify() { this->updateSlider(); }

		static Type& cls() { static Type ty("StatSlider<" + typecls<T>().name() + ">", WValue::cls()); return ty; }

	protected:
		AutoStat<T>& m_stat;

		Dimension m_dim;

		Slider m_slider;
		SliderDisplay m_display;
	};

	template class _I_ TOY_UI_EXPORT StatSlider<float>;
	template class _I_ TOY_UI_EXPORT StatSlider<int>;
}

#endif
