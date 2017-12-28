//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_EXPANDBOX_H
#define TOY_EXPANDBOX_H

/* toy */
#include <toyui/Widget/Sheet.h>
#include <toyui/Button/Button.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT Expandbox : public Wedge
	{
	public:
		Expandbox(const Params& params, const StringVector& elements, bool collapsed = false);

		virtual void expand();
		virtual void collapse();

		struct Styles
		{
			Style expandbox = { cls<Expandbox>(), Widget::styles().stack };
			Style header = { "ExpandboxHeader", Widget::styles().wrap_button };
			Style toggle = { "ExpandboxToggle", Widget::styles().toggle };
			Style body = { "ExpandboxBody", Widget::styles().stack, Args{ { &Layout::m_padding, BoxFloat{ 12.f, 2.f, 0.f, 2.f } }, { &Layout::m_spacing, DimFloat(6.f) } } };
		};
		static Styles& styles() { static Styles styles; return styles; }

	public:
		MultiButton m_header;
		Toggle m_toggle;
		Wedge m_body;

	protected:
		bool m_collapsed;
	};
}

#endif
