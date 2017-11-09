//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Container/Table.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Solver/Grid.h>

namespace toy
{
	Table::Table(Wedge& parent, StringVector columns, std::vector<float> weights)
		: Wedge(parent, cls())
		, m_columns(columns)
		, m_weights(weights)
		, m_head(*this, DIM_X, [this](Frame& first, Frame& second) { this->resize(first, second); }, Table::Head())
	{
		for(size_t i = 0; i < m_columns.size(); ++i)
		{
			Wedge& header = m_head.emplace<Wedge>(Table::ColumnHeader());
			header.emplace<Label>(m_columns[i]);
			header.frame().setSpanDim(DIM_X, m_weights[i]);
		}
	}

	void Table::makeSolver()
	{
		Widget::makeSolver();
		//m_frame->d_solver->as<TableSolver>().divide(m_weights);
	}

	void Table::resize(Frame& first, Frame& second)
	{
		m_weights[first.d_index[DIM_X]] = first.d_span.x;
		m_weights[second.d_index[DIM_X]] = second.d_span.x;
		m_frame->d_solver->as<TableSolver>().update(m_weights);
		m_frame->markDirty(DIRTY_FORCE_LAYOUT);
	}
}
