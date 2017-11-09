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
		Expandbox(Wedge& parent, const StringVector& elements, bool collapsed = false, Type& type = cls());

		virtual void expand();
		virtual void collapse();

		static Type& cls() { static Type ty("Expandbox", Wedge::Stack()); return ty; }

		static Type& Header() { static Type ty("ExpandboxHeader", WrapButton::cls()); return ty; }
		static Type& Switch() { static Type ty("ExpandboxToggle", Toggle::cls()); return ty; }
		static Type& Body() { static Type ty("ExpandboxBody", Wedge::cls()); return ty; }

	public:
		MultiButton m_header;
		Toggle m_toggle;
		Wedge m_body;

	protected:
		bool m_collapsed;
	};
}

#endif
