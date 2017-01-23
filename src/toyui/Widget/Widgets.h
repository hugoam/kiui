//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_WIDGETS_H
#define TOY_WIDGETS_H

/* toy headers */
#include <toyobj/Typed.h>
#include <toyobj/Util/Stat.h>
#include <toyobj/Util/Unique.h>
#include <toyui/Forward.h>
#include <toyui/Scheme/Window.h>
#include <toyui/Scheme/List.h>
#include <toyui/Scheme/Tabber.h>
#include <toyui/Scheme/Dropdown.h>
#include <toyui/Scheme/RadioButton.h>

namespace toy
{
	class _I_ TOY_UI_EXPORT Page : public ScrollSheet
	{
	public:
		Page(const string& name, const string& dockid = "");

		const string& name() { return m_name; }
		const string& dockid() { return m_dockId; }

		static StyleType& cls() { static StyleType ty("Page", ScrollSheet::cls()); return ty; }

	protected:
		string m_name;
		string m_dockId;
	};

	class _I_ TOY_UI_EXPORT Dialog : public Sheet
	{
	public:
		Dialog();

		static StyleType& cls() { static StyleType ty("Dialog", Sheet::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Header : public Sheet
	{
	public:
		Header();

		static StyleType& cls() { static StyleType ty("Header", Sheet::cls()); return ty; }
	};
}

#endif // TOY_WIDGET_H
