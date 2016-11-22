//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Scheme/mkTable.h>

#include <Ui/Widget/mkWidgets.h>

#include <Ui/Frame/mkFrame.h>

#include <iostream>

using namespace std::placeholders;

namespace mk
{
	TableHead::TableHead()
		: GridSheet(DIM_X, cls())
	{}

	void TableHead::gridResized(Widget& first, Widget& second)
	{
		m_parent->stripe().weights()[first.frame().index()] = first.frame().dspan(DIM_X);
		m_parent->stripe().weights()[second.frame().index()] = second.frame().dspan(DIM_X);
		m_parent->stripe().setDirty(Frame::DIRTY_FLOW);
	}

	ColumnHeader::ColumnHeader(const string& label)
		: Label(label, cls())
	{}

	Table::Table(StringVector columns, std::vector<float> weights)
		: Sheet(cls())
		, m_columns(columns)
		, m_weights(weights)
		, m_head(this->makeappend<TableHead>())
	{
		for(string& name : m_columns)
			m_head.emplace<ColumnHeader>(name);

		this->stripe().initWeights();
		for(float& weight : m_weights)
			this->stripe().weights().push_back(weight);
	}

	Table::~Table()
	{}
}
