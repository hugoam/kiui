//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Container/Table.h>

#include <toyui/Container/Layout.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Grid.h>

namespace toy
{
	TableHead::TableHead(Table& table)
		: GridSheet(table, DIM_X, cls())
		, m_table(table)
	{}

	void TableHead::gridResized(Frame& first, Frame& second)
	{
		Stripe& firstColumn = m_table.frame().as<TableGrid>().column(first.dindex(DIM_X));
		Stripe& secondColumn = m_table.frame().as<TableGrid>().column(second.dindex(DIM_X));
		firstColumn.setSpanDim(DIM_X, first.dspan(DIM_X));
		secondColumn.setSpanDim(DIM_X, second.dspan(DIM_X));
	}

	ColumnHeader::ColumnHeader(Wedge& parent, const string& label, float span)
		: Label(parent, label, cls())
	{
		m_frame->setSpanDim(DIM_X, span);
	}

	Table::Table(Wedge& parent, StringVector columns, std::vector<float> weights)
		: Stack(parent, cls(), TABLE)
		, m_columns(columns)
		, m_weights(weights)
		, m_head(*this)
	{
		for(size_t i = 0; i < m_columns.size(); ++i)
			m_head.emplace<ColumnHeader>(m_columns[i], m_weights[i]);

		TableGrid& grid = this->frame().as<TableGrid>();
		grid.resize(m_columns.size());

		for(size_t i = 0; i < m_columns.size(); ++i)
			grid.column(i).setSpanDim(DIM_X, m_weights[i]);
	}
}
