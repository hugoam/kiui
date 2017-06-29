//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <toyui/Config.h>
#include <toyui/Solver/Grid.h>

#include <toyui/Widget/Sheet.h>

namespace toy
{
	static LayoutStyle& gridOverlayStyle()
	{
		static LayoutStyle style;
		style.d_space = { READING, EXPAND, EXPAND };
		style.d_flow = OVERLAY;
		return style;
	}

	static LayoutStyle& columnSolverStyle()
	{
		static LayoutStyle style;
		style.d_space = { PARAGRAPH, WRAP, WRAP };
		style.d_layout = { AUTO_LAYOUT, NO_LAYOUT };
		return style;
	}

	TableSolver::TableSolver(FrameSolver* solver, LayoutStyle* layout, Frame* frame)
		: CustomSolver(solver, layout, frame)
	{}

	void TableSolver::divide(std::vector<float> columns)
	{
		m_solvers.clear();
		m_solvers.emplace_back(make_unique<RowSolver>(this, &gridOverlayStyle()));
		for(size_t i = 0; i < columns.size(); ++i)
		{
			m_solvers.emplace_back(make_unique<RowSolver>(m_solvers.front().get(), &columnSolverStyle()));
			m_solvers.back()->d_span = { columns[i], 0.f };
		}
	}

	void TableSolver::setSpan(size_t index, float span)
	{
	}

	FrameSolver& TableSolver::solver(FrameSolver& frame, Dimension dim)
	{
		if(frame.d_frame && frame.d_parent != this)
		{
			size_t column0 = frame.d_frame->dindex(d_depth);
			size_t column = frame.d_frame->widget().index();
			return *m_solvers[1 + column];
		}
		return *this;
	}

	/*this->styledef(GridSubdiv::cls()).layout().d_direction = DIMENSION;*/

	LineSolver::LineSolver(FrameSolver* solver, Space space)
		: RowSolver(solver, nullptr)
		, d_style()
	{
		d_style.d_space = space;
		d_style.d_space.val.direction = READING;
		FrameSolver::d_style = &d_style;
		this->applySpace();
	}

	GridSolver::GridSolver(FrameSolver* solver, LayoutStyle* layout, Frame* frame)
		: CustomSolver(solver, layout, frame)
	{}

	void GridSolver::divide(std::vector<Space> lines)
	{
		m_solvers.clear();
		for(size_t i = 0; i < lines.size(); ++i)
			m_solvers.emplace_back(make_unique<LineSolver>(this, lines[i]));
	}

	FrameSolver& GridSolver::solver(FrameSolver& frame, Dimension dim)
	{
		if(frame.d_frame)
		{
			size_t row = frame.d_frame->dindex(d_length);
			return *m_solvers[row];
		}
		return *this;
	}
}

