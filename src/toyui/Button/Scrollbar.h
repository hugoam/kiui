//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_SCROLLBAR_H
#define TOY_SCROLLBAR_H

/* toy */
#include <toyui/Types.h>
#include <toyui/Button/Button.h>
#include <toyui/Button/Slider.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT Scrollbar : public Wedge
	{
	public:
		Scrollbar(const Params& params, Wedge& frameSheet, Wedge& contentSheet, Dimension dim);

		float cursor() { return -m_contentSheet.frame().d_position[m_dim]; }
		float contentSize() { return m_contentSheet.frame().m_size[m_dim] * m_contentSheet.frame().d_scale; }
		float visibleSize() { return m_frameSheet.frame().m_size[m_dim]; }
		float overflow() { return m_frameSheet.m_contents.size() > 0 ? contentSize() - visibleSize() : 0.f; }

		void scrollforward();
		void scrollback();

		void scroll(float amount);
		void scrollTo(float offset);

		void update();

		float nextOffset(Widget& widget, Dimension dim, float pos);
		float prevOffset(Widget& widget, Dimension dim, float pos);

		struct Styles
		{
			Style scrollbar = { cls<Scrollbar>(), Widget::styles().row };

			Style scroll_up = { "ScrollUp", Widget::styles().button };
			Style scroll_down = { "ScrollDown", Widget::styles().button };
			Style scroll_left = { "ScrollLeft", Widget::styles().button };
			Style scroll_right = { "ScrollRight", Widget::styles().button };

			Style scroller = { "Scroller", Widget::styles().slider, Args{ { &Layout::m_space, FLEX } } };
			Style scroller_knob = { "ScrollerKnob", Widget::styles().slider_knob, Args{ { &Layout::m_flow, FLOW } } };
		};
		static Styles& styles() { static Styles styles; return styles; }

	protected:
		Dimension m_dim;
		Wedge& m_frameSheet;
		Wedge& m_contentSheet;

	public:
		Button m_rewind;
		Slider m_scroller;
		Button m_seek;
	};
}

#endif // TOY_SCROLLBAR_H
