//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_DROPDOWN_H
#define TOY_DROPDOWN_H

/* toy */
#include <toyui/Widget/Sheet.h>
#include <toyui/Button/Button.h>
#include <toyui/Container/List.h>

#include <functional>

namespace toy
{
	class TOY_UI_EXPORT DropdownHead : public WrapButton
	{
	public:
		DropdownHead(Piece& parent, const Trigger& trigger);

		static Type& cls() { static Type ty("DropdownHead", WrapButton::cls()); return ty; }
	};

	class TOY_UI_EXPORT DropdownToggle : public Button
	{
	public:
		DropdownToggle(Piece& parent, const Trigger& trigger);

		static Type& cls() { static Type ty("DropdownToggle", Button::cls()); return ty; }
	};

	class TOY_UI_EXPORT DropdownChoice : public WrapButton
	{
	public:
		DropdownChoice(Piece& parent, const Trigger& trigger);

		static Type& cls() { static Type ty("DropdownChoice", WrapButton::cls()); return ty; }
	};

	class TOY_UI_EXPORT DropdownList : public Stack
	{
	public:
		DropdownList(Dropdown& dropdown);

		void leftClick(MouseEvent& mouseEvent);
		void rightClick(MouseEvent& mouseEvent);
		
		static Type& cls() { static Type ty("DropdownList", Stack::cls()); return ty; }

	protected:
		Dropdown& m_dropdown;
	};

	class TOY_UI_EXPORT Dropdown : public WrapButton
	{
	public:
		Dropdown(Piece& parent, Type& type = cls());

		DropdownList& list() { return m_list; }
		DropdownHead& header() { return m_header; }
		bool down() { return m_down; }

		void dropdown(bool modal = true);
		void dropup();

		DropdownChoice& addChoice();
		virtual Container& emplaceContainer();

		static Type& cls() { static Type ty("Dropdown", WrapButton::cls()); return ty; }

	protected:
		DropdownHead m_header;
		DropdownToggle m_toggle;
		DropdownList m_list;
		bool m_down;
	};

	class TOY_UI_EXPORT DropdownInput : public Dropdown
	{
	public:
		DropdownInput(Piece& parent, const Trigger& onSelected, StringVector choices = StringVector(), Type& type = cls());

		void select(DropdownChoice& selected);
		void selected(DropdownChoice& selected);

		virtual Container& emplaceContainer();

		virtual void handleAdd(Widget& widget);

		void updateHead(Widget& choice);

		static Type& cls() { static Type ty("DropdownInput", Dropdown::cls()); return ty; }

	protected:
		Trigger m_onSelected;
		WrapButton* m_selected;
	};
}

#endif
