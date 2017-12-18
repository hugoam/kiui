//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_SCROLLSHEET_H
#define TOY_SCROLLSHEET_H

/* toy */
#include <toyobj/Type.h>
#include <toyui/Types.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Button/Scrollbar.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT ScrollSheet : public Wedge
	{
	public:
		ScrollSheet(const Params& params);

		virtual void dirtyLayout();

		virtual bool mouseWheel(MouseEvent& mouseEvent);

		virtual void makeSolver();

	public:
		Wedge m_scrollzone;
		Wedge m_body;
		Scrollbar m_scrollbarX;
		Scrollbar m_scrollbarY;
	};

	class _refl_ TOY_UI_EXPORT ScrollPlan : public ScrollSheet
	{
	public:
		ScrollPlan(const Params& params);

		virtual bool middleDrag(MouseEvent& mouseEvent);
		virtual bool mouseWheel(MouseEvent& mouseEvent);

		virtual void dirtyLayout();

		void updateBounds();

	protected:
		Wedge& m_plan;
		BoxFloat m_bounds;
		bool m_clamped;
	};

	TOY_UI_EXPORT bool drawGrid(const Frame& frame, Renderer& renderer);
}

#endif // TOY_SCROLLSHEET_H
