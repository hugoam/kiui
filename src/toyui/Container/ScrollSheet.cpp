//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Container/ScrollSheet.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Layer.h>
#include <toyui/Solver/Grid.h>
#include <toyui/Render/Renderer.h>

namespace toy
{
	ScrollSurface::ScrollSurface(Wedge& parent)
		: Wedge(parent, cls())
	{}

	ScrollZone::ScrollZone(ScrollSheet& parent)
		: Wedge(parent, cls())
		, body(*this)
	{}

	ScrollSheet::ScrollSheet(Wedge& parent, Type& type)
		: Wedge(parent, type)
		, m_scrollzone(*this)
		, m_scrollbarX(*this, m_scrollzone, m_scrollzone.body, DIM_X)
		, m_scrollbarY(*this, m_scrollzone, m_scrollzone.body, DIM_Y)
	{
		m_scrollzone.frame().setIndex(0, 0);
		m_scrollbarX.frame().setIndex(0, 1);
		m_scrollbarY.frame().setIndex(1, 0);
	}

	void ScrollSheet::makeSolver()
	{
		Widget::makeSolver();

		m_frame->solver()->as<GridSolver>().divide({ Space::preset(BOARD), Space::preset(LINE) });
	}

	void ScrollSheet::dirtyLayout()
	{
		m_scrollbarX.update();
		m_scrollbarY.update();
	}

	bool ScrollSheet::mouseWheel(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		m_scrollbarX.scroll(mouseEvent.delta.x);
		m_scrollbarY.scroll(mouseEvent.delta.y);
		return true;
	}

	ScrollPlan::ScrollPlan(Wedge& parent, Type& type)
		: ScrollSheet(parent, type)
		, m_plan(m_scrollzone.body)
		, m_clamped(true)
	{
		m_plan.setStyle(ScrollPlan::Plan());
		this->updateBounds();
	}

	void ScrollPlan::dirtyLayout()
	{
		this->updateBounds();
		ScrollSheet::dirtyLayout();
	}

	void ScrollPlan::updateBounds()
	{
		// @warning: if the plan contains an expand container, the size will keep increasing endlessly

		float margin = 1000.f;
		m_bounds = BoxFloat(-margin, -margin, +margin, +margin);

		for(auto& widget : m_plan.contents())
		{
			Frame& frame = widget->frame();
			m_bounds.x0 = std::min(frame.d_position.x - margin, m_bounds.x);
			m_bounds.y0 = std::min(frame.d_position.y - margin, m_bounds.y);
			m_bounds.x1 = std::max(frame.d_position.x + frame.d_size.x + margin, m_bounds.w);
			m_bounds.y1 = std::max(frame.d_position.y + frame.d_size.y + margin, m_bounds.h);
		}

		m_plan.frame().setSize({ m_bounds.x1 - m_bounds.x0, m_bounds.y1 - m_bounds.y0 });
	}

	bool ScrollPlan::middleDrag(MouseEvent& mouseEvent)
	{
		DimFloat pos = m_plan.frame().d_position + mouseEvent.delta;
		m_plan.frame().setPosition({ std::min(0.f, pos.x), std::min(0.f, pos.y) });
		m_frame->markDirty(DIRTY_FORCE_LAYOUT);
		return true;
	}

	bool ScrollPlan::mouseWheel(MouseEvent& mouseEvent)
	{
		float deltaScale = mouseEvent.deltaZ > 0.f ? 1.2f : 0.8333f;
		float scale = m_plan.frame().d_scale * deltaScale;

		if(m_clamped)
		{
			DimFloat minScale = m_scrollzone.frame().d_size / m_plan.frame().d_size;
			scale = std::max(scale, std::max(minScale.x, minScale.y));
		}

		m_plan.frame().d_scale = scale;
		m_frame->markDirty(DIRTY_FORCE_LAYOUT);

		DimFloat offset = mouseEvent.relative - mouseEvent.relative * deltaScale;
		DimFloat pos = offset + m_plan.frame().d_position;

		if(m_clamped)
			m_plan.frame().setPosition({ std::min(0.f, pos.x), std::min(0.f, pos.y) });
		else
			m_plan.frame().setPosition(pos);

		return true;
	}

	bool drawGrid(const Frame& frame, Renderer& renderer)
	{
		float gridsizeX = 100.f;
		float gridsizeY = 50.f;

		for(float x = 0.f; x < frame.d_size.x; x += gridsizeX)
		{
			renderer.pathLine(x, 0.f, x, frame.d_size.y);
			renderer.stroke(frame.inkstyle());
		}

		for(float y = 0.f; y < frame.d_size.y; y += gridsizeY)
		{
			renderer.pathLine(0.f, y, frame.d_size.x, y);
			renderer.stroke(frame.inkstyle());
		}

		return false;
	}
}
