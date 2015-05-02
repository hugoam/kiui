//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Scheme/mkTable.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Form/mkWidgets.h>

#include <Ui/Frame/mkFrame.h>

#include <iostream>

using namespace std::placeholders;

namespace mk
{
	TableHead::TableHead()
		: GridSheet(DIM_X)
	{
		mStyle = &cls();
	}

	void TableHead::gridResized(Widget& first, Widget& second)
	{
		mParent->stripe().weights()[first.frame().index()] = first.frame().dspan(DIM_X);
		mParent->stripe().weights()[second.frame().index()] = second.frame().dspan(DIM_X);
		mParent->stripe().setDirty(Frame::DIRTY_FLOW);
	}

	ColumnHeader::ColumnHeader(const string& label)
		: Label(label)
	{
		mStyle = &cls();
	}

	Table::Table(StringVector columns, std::vector<float> weights)
		: Sheet()
		, mColumns(columns)
		, mWeights(weights)
		, mHead(this->makeappend<TableHead>())
	{
		mStyle = &cls();
		for(string& name : mColumns)
			mHead.emplace<ColumnHeader>(name);

		this->stripe().initWeights();
		for(float& weight : mWeights)
			this->stripe().weights().push_back(weight);
	}

	Table::~Table()
	{}
}
