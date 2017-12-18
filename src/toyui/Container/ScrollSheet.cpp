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
	ScrollSheet::ScrollSheet(const Params& params)
		: Wedge({ params, &cls<ScrollSheet>() })
		, m_scrollzone({ this, &styles().scroll_zone })
		, m_body({ &m_scrollzone, &styles().scroll_surface })
		, m_scrollbarX({ this }, m_scrollzone, m_body, DIM_X)
		, m_scrollbarY({ this }, m_scrollzone, m_body, DIM_Y)
	{
		m_scrollzone.frame().d_index = { 0, 0 };
		m_scrollbarX.frame().d_index = { 0, 1 };
		m_scrollbarY.frame().d_index = { 1, 0 };
	}

	void ScrollSheet::makeSolver()
	{
		Widget::makeSolver();

		as<GridSolver>(*m_frame->m_solver).divide({ Space::preset(BOARD), Space::preset(LINE) });
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

	ScrollPlan::ScrollPlan(const Params& params)
		: ScrollSheet({ params, &cls<ScrollPlan>() })
		, m_plan(m_body)
		, m_clamped(true)
	{
		m_plan.setStyle(styles().scrollplan_surface);
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

		for(auto& widget : m_plan.m_contents)
		{
			Frame& frame = widget->frame();
			m_bounds.x0 = std::min(frame.d_position.x - margin, m_bounds.x);
			m_bounds.y0 = std::min(frame.d_position.y - margin, m_bounds.y);
			m_bounds.x1 = std::max(frame.d_position.x + frame.m_size.x + margin, m_bounds.w);
			m_bounds.y1 = std::max(frame.d_position.y + frame.m_size.y + margin, m_bounds.h);
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
			DimFloat minScale = m_scrollzone.frame().m_size / m_plan.frame().m_size;
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
	
	void drawLines(const Frame& frame, Dimension dim, float frequency, InkStyle& style, Renderer& renderer)
	{
		float start = frequency;
		for(float val = start; val < frame.m_size[dim]; val += frequency)
		{
			if(dim == DIM_X)
				renderer.pathLine(val, 0.f, val, frame.m_size.y);
			else
				renderer.pathLine(0.f, val, frame.m_size.x, val);
			renderer.stroke(style);
		}
	}

	bool drawGrid(const Frame& frame, Renderer& renderer)
	{
		static InkStyle mainStyle;
		mainStyle.m_border_width = 1.f;
		mainStyle.m_border_colour = Colour(132 / 255.f, 132 / 255.f, 132 / 255.f, 1.f);

		static InkStyle secondaryStyle;
		secondaryStyle.m_border_width = 1.f;
		secondaryStyle.m_border_colour = Colour(34 / 255.f, 34 / 255.f, 34 / 255.f, 1.f);

		float mainFrequency = 100.f;
		float secondaryFrequency = 20.f;

		drawLines(frame, DIM_X, mainFrequency, mainStyle, renderer);
		drawLines(frame, DIM_Y, mainFrequency, mainStyle, renderer);

		drawLines(frame, DIM_X, secondaryFrequency, secondaryStyle, renderer);
		drawLines(frame, DIM_Y, secondaryFrequency, secondaryStyle, renderer);

		return false;
	}
}
