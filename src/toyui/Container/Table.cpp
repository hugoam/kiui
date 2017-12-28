//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Container/Table.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Solver/Grid.h>

namespace toy
{
	Table::Table(const Params& params, StringVector columns, std::vector<float> weights)
		: Wedge({ params, &cls<Table>() })
		, m_columns(columns)
		, m_weights(weights)
		, m_head({ this, &styles().table_head }, DIM_X, [this](Frame& first, Frame& second) { this->resize(first, second); })
	{
		if(m_weights.empty())
			m_weights = std::vector<float>(columns.size(), 1.f);

		for(size_t i = 0; i < m_columns.size(); ++i)
		{
			Wedge& header = m_head.emplace_style<Wedge>(styles().column_header);
			header.emplace<Label>(m_columns[i]);
			header.frame().setSpanDim(DIM_X, m_weights[i]);
		}
	}

	void Table::makeSolver()
	{
		Widget::makeSolver();
		//as<TableSolver>(*m_frame->m_solver).divide(m_weights);
	}

	void Table::resize(Frame& first, Frame& second)
	{
		m_weights[first.d_index[DIM_X]] = first.m_span.x;
		m_weights[second.d_index[DIM_X]] = second.m_span.x;
		//as<TableSolver>(*m_frame->m_solver).update(m_weights);
		m_frame->markDirty(DIRTY_FORCE_LAYOUT);
	}
}
