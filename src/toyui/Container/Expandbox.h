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
		Expandbox(Wedge& parent, const string& title, bool collapsed = false, Type& type = cls());

		Wedge& header() { return m_header; }
		Wedge& body() { return m_body; }

		virtual void expand();
		virtual void collapse();

		static Type& cls() { static Type ty("Expandbox", Wedge::Stack()); return ty; }

		static Type& Header() { static Type ty("ExpandboxHeader", WrapButton::cls()); return ty; }
		static Type& Switch() { static Type ty("ExpandboxToggle", Toggle::cls()); return ty; }
		static Type& Body() { static Type ty("ExpandboxBody", Wedge::cls()); return ty; }

	protected:
		WrapButton m_header;
		Toggle m_toggle;
		Label m_title;
		Wedge m_body;
		bool m_collapsed;
	};
}

#endif
