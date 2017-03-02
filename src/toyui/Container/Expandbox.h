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
	class TOY_UI_EXPORT ExpandboxHeader : public WrapButton
	{
	public:
		ExpandboxHeader(Piece& parent, const Trigger& trigger = Trigger());

		static Type& cls() { static Type ty("ExpandboxHeader", WrapButton::cls()); return ty; }
	};

	class TOY_UI_EXPORT ExpandboxBody : public Container
	{
	public:
		ExpandboxBody(Piece& parent);

		static Type& cls() { static Type ty("ExpandboxBody", Container::cls()); return ty; }
	};

	class TOY_UI_EXPORT ExpandboxToggle : public Toggle
	{
	public:
		ExpandboxToggle(Piece& parent, const Trigger& triggerOn, const Trigger& triggerOff, bool on);

		static Type& cls() { static Type ty("ExpandboxToggle", Toggle::cls()); return ty; }
	};

	class TOY_UI_EXPORT Expandbox : public Stack
	{
	public:
		Expandbox(Piece& parent, const string& title, bool collapsed = false, bool build = true, Type& type = cls());
		~Expandbox();

		Piece& header() { return m_header; }

		virtual Container& emplaceContainer();

		virtual void expand();
		virtual void collapse();

		static Type& cls() { static Type ty("Expandbox", Stack::cls()); return ty; }

	protected:
		ExpandboxHeader m_header;
		ExpandboxToggle m_toggle;
		Label m_title;
		ExpandboxBody m_container;
		bool m_collapsed;
	};
}

#endif
