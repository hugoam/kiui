//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_SCROLLSHEET_H
#define TOY_SCROLLSHEET_H

/* toy */
#include <toyobj/Typed.h>
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Button/Scrollbar.h>

namespace toy
{
	class _I_ TOY_UI_EXPORT ScrollZone : public Container
	{
	public:
		ScrollZone(Wedge& parent);

		Container& container() { return m_container; }

		static Type& cls() { static Type ty("ScrollZone", Layout::cls()); return ty; }

	protected:
		Container m_container;
	};

	class TOY_UI_EXPORT NoScrollZone
	{
	public:
		static Type& cls() { static Type ty("NoScrollZone", Wedge::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT ScrollSheet : public Container
	{
	public:
		ScrollSheet(Wedge& parent, Type& type = cls());

		Container& container() { return m_scrollzone.container(); }

		virtual Container& emplaceContainer();

		virtual void clear();

		void mouseWheel(MouseEvent& mouseEvent);

		void enableWrap();
		void disableWrap();

		void updateWrap();

		static Type& cls() { static Type ty("ScrollSheet", Container::cls()); return ty; }

	protected:
		ScrollZone m_scrollzone;
		Scrollbar m_scrollbarX;
		Scrollbar m_scrollbarY;
		bool m_wrap;
	};

	class _I_ TOY_UI_EXPORT ScrollContainer : public ScrollSheet
	{
	public:
		ScrollContainer(Wedge& parent, Type& type = cls());

		static Type& cls() { static Type ty("Container", ScrollSheet::cls()); return ty; }
	};

	class TOY_UI_EXPORT Plan
	{
	public:
		static Type& cls() { static Type ty("Plan", Sheet::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT ScrollPlan : public ScrollSheet
	{
	public:
		ScrollPlan(Wedge& parent, Type& type = cls());

		void nextFrame(size_t tick, size_t delta);

		void middleDrag(MouseEvent& mouseEvent);

		void mouseWheel(MouseEvent& mouseEvent);

		void updateBounds();

		static Type& cls() { static Type ty("ScrollPlan", ScrollSheet::cls()); return ty; }

	protected:
		Container& m_plan;
		BoxFloat m_bounds;
		bool m_clamped;
	};

	TOY_UI_EXPORT bool drawGrid(Frame& frame, Renderer& renderer);
}

#endif // TOY_SCROLLSHEET_H
