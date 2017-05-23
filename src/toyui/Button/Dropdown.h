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
	class _I_ TOY_UI_EXPORT DropdownHead : public MultiButton
	{
	public:
		DropdownHead(Dropdown& dropdown, const Callback& trigger);

		static Type& cls() { static Type ty("DropdownHead", MultiButton::cls()); return ty; }

	protected:
		Dropdown& m_dropdown;
	};

	class _I_ TOY_UI_EXPORT DropdownToggle : public Button
	{
	public:
		DropdownToggle(Wedge& parent, const Callback& trigger);

		static Type& cls() { static Type ty("DropdownToggle", Button::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT DropdownChoice : public MultiButton
	{
	public:
		DropdownChoice(Wedge& parent, Dropdown& dropdown, const Callback& trigger, const StringVector& elements);

		virtual bool leftClick(MouseEvent& mouseEvent);

		static Type& cls() { static Type ty("DropdownChoice", MultiButton::cls()); return ty; }

	protected:
		Dropdown& m_dropdown;
	};

	class _I_ TOY_UI_EXPORT DropdownList : public Container
	{
	public:
		DropdownList(Dropdown& dropdown);

		virtual bool leftClick(MouseEvent& mouseEvent);
		virtual bool rightClick(MouseEvent& mouseEvent);
		
		static Type& cls() { static Type ty("DropdownList", Container::cls()); return ty; }

	protected:
		Dropdown& m_dropdown;
	};

	class _I_ TOY_UI_EXPORT Dropdown : public WrapButton
	{
	public:
		Dropdown(Wedge& parent, Type& type = cls());

		DropdownList& list() { return m_list; }
		DropdownHead& header() { return m_header; }
		bool down() { return m_down; }

		virtual Widget& insert(unique_ptr<Widget> widget);

		void dropdown(bool modal = true);
		void dropup();

		virtual void selected(DropdownChoice& selected);

		DropdownChoice& addChoice(const StringVector& elements, const Callback& trigger = nullptr);

		static Type& cls() { static Type ty("Dropdown", WrapButton::cls()); return ty; }

	protected:
		DropdownHead m_header;
		DropdownToggle m_toggle;
		DropdownList m_list;
		bool m_down;
	};

	class _I_ TOY_UI_EXPORT DropdownInput : public Dropdown
	{
	public:
		DropdownInput(Wedge& parent, const Callback& onSelected = nullptr, StringVector choices = StringVector(), Type& type = cls());

		virtual void selected(DropdownChoice& selected);
		void select(DropdownChoice& selected);

		DropdownChoice& addChoice(const StringVector& elements, const Callback& trigger = nullptr);

		static Type& cls() { static Type ty("DropdownInput", Dropdown::cls()); return ty; }

	protected:
		Callback m_onSelected;
		MultiButton* m_selected;
		bool m_activeHeader;
	};
}

#endif
