//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_SCROLLBAR_H
#define TOY_SCROLLBAR_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Button/Button.h>
#include <toyui/Button/Slider.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT Scrollbar : public Wedge
	{
	public:
		Scrollbar(Wedge& parent, Wedge& frameSheet, Wedge& contentSheet, Dimension dim);

		float contentSize();
		float visibleSize();

		float overflow();

		void scrollup();
		void scrolldown();

		void scroll(float amount);
		void scrollTo(float offset);

		void update();

		float nextOffset(Widget& widget, Dimension dim, float pos);
		float prevOffset(Widget& widget, Dimension dim, float pos);

		static Type& cls() { static Type ty("Scrollbar", Wedge::Row()); return ty; }

		static Type& ScrollUp() { static Type ty("ScrollUp", Button::cls()); return ty; }
		static Type& ScrollDown() { static Type ty("ScrollDown", Button::cls()); return ty; }
		static Type& ScrollLeft() { static Type ty("ScrollLeft", Button::cls()); return ty; }
		static Type& ScrollRight() { static Type ty("ScrollRight", Button::cls()); return ty; }

		static Type& Scroller() { static Type ty("Scroller", Slider::cls()); return ty; }
		static Type& Knob() { static Type ty("ScrollerKnob", Slider::Knob()); return ty; }

	protected:
		Dimension m_dim;
		float d_cursor;
		Wedge& m_frameSheet;
		Wedge& m_contentSheet;

		Button m_rewind;
		Slider m_scroller;
		Button m_seek;
	};
}

#endif // TOY_SCROLLBAR_H
