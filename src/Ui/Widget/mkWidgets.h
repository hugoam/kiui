//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WIDGETS_H
#define MK_WIDGETS_H

/* mk headers */
#include <Object/mkTyped.h>
#include <Object/Util/mkStat.h>
#include <Object/Util/mkUnique.h>
#include <Ui/mkUiForward.h>
#include <Ui/Scheme/mkWindow.h>
#include <Ui/Scheme/mkList.h>
#include <Ui/Scheme/mkTabber.h>
#include <Ui/Scheme/mkDropdown.h>
#include <Ui/Scheme/mkRadioButton.h>

namespace mk
{
	class MK_UI_EXPORT _I_ Page : public ScrollSheet
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

	class MK_UI_EXPORT _I_ Dialog : public Sheet
	{
	public:
		Dialog();

		static StyleType& cls() { static StyleType ty("Dialog", Sheet::cls()); return ty; }
	};

	class MK_UI_EXPORT _I_ Header : public Sheet
	{
	public:
		Header();

		static StyleType& cls() { static StyleType ty("Header", Sheet::cls()); return ty; }
	};
}

#endif // MK_WIDGET_H
