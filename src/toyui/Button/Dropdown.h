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
	class TOY_UI_EXPORT DropdownHead : public MultiButton
	{
	public:
		DropdownHead(Wedge& parent, const Trigger& trigger);

		static Type& cls() { static Type ty("DropdownHead", MultiButton::cls()); return ty; }
	};

	class TOY_UI_EXPORT DropdownToggle : public Button
	{
	public:
		DropdownToggle(Wedge& parent, const Trigger& trigger);

		static Type& cls() { static Type ty("DropdownToggle", Button::cls()); return ty; }
	};

	class TOY_UI_EXPORT DropdownChoice : public MultiButton
	{
	public:
		DropdownChoice(Wedge& parent, const Trigger& trigger, const StringVector& elements);

		static Type& cls() { static Type ty("DropdownChoice", MultiButton::cls()); return ty; }
	};

	class TOY_UI_EXPORT DropdownList : public Container
	{
	public:
		DropdownList(Dropdown& dropdown);

		void leftClick(MouseEvent& mouseEvent);
		void rightClick(MouseEvent& mouseEvent);
		
		static Type& cls() { static Type ty("DropdownList", Container::cls()); return ty; }

	protected:
		Dropdown& m_dropdown;
	};

	class TOY_UI_EXPORT Dropdown : public WrapButton
	{
	public:
		Dropdown(Wedge& parent, Type& type = cls());

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
		DropdownInput(Wedge& parent, const Trigger& onSelected, StringVector choices = StringVector(), Type& type = cls());

		void select(DropdownChoice& selected);
		void selected(DropdownChoice& selected);

		DropdownChoice& addChoice(const StringVector& elements);
		virtual Container& emplaceContainer();

		void updateHead(MultiButton& choice);

		static Type& cls() { static Type ty("DropdownInput", Dropdown::cls()); return ty; }

	protected:
		Trigger m_onSelected;
		MultiButton* m_selected;
	};
}

#endif
