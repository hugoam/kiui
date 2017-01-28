//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_EXPANDBOX_H
#define TOY_EXPANDBOX_H

/* toy */
#include <toyui/Widget/Sheet.h>
#include <toyui/Widget/Button.h>

namespace toy
{
	class TOY_UI_EXPORT ExpandboxHeader : public Band
	{
	public:
		ExpandboxHeader();

		static StyleType& cls() { static StyleType ty("ExpandboxHeader", Band::cls()); return ty; }
	};

	class TOY_UI_EXPORT ExpandboxBody : public Sheet
	{
	public:
		ExpandboxBody();

		static StyleType& cls() { static StyleType ty("ExpandboxBody", Sheet::cls()); return ty; }
	};

	class TOY_UI_EXPORT ExpandboxToggle : public Toggle
	{
	public:
		ExpandboxToggle(const Trigger& triggerOn, const Trigger& triggerOff, bool on);

		static StyleType& cls() { static StyleType ty("ExpandboxToggle", Toggle::cls()); return ty; }
	};

	class TOY_UI_EXPORT Expandbox : public Sheet
	{
	public:
		Expandbox(const string& title, bool collapsed = false, bool build = true, StyleType& type = cls());
		~Expandbox();

		Sheet* header() { return m_header; }

		Widget& vappend(unique_ptr<Widget> widget);
		unique_ptr<Widget> vrelease(Widget& widget);

		virtual void expand();
		virtual void collapse();

		static StyleType& cls() { static StyleType ty("Expandbox", Sheet::cls()); return ty; }

	protected:
		string m_title;
		Sheet* m_header;
		Sheet* m_container;
		Toggle* m_expandButton;
		Label* m_titleLabel;
		bool m_collapsed;
	};
}

#endif
