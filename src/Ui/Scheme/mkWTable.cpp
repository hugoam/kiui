//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Scheme/mkWTable.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Form/mkWidgets.h>

#include <Ui/Frame/mkFrame.h>

using namespace std::placeholders;

namespace mk
{
	WTableHead::WTableHead()
		: GridSheet(DIM_X, "tablehead")
	{}

	void WTableHead::gridResized(Widget* first, Widget* second)
	{
		mParent->stripe()->weightTable()[first->frame()->index()] = first->frame()->dspan(DIM_X);
		mParent->stripe()->weightTable()[second->frame()->index()] = second->frame()->dspan(DIM_X);
		mParent->stripe()->markRelayout();
	}

	WTable::WTable(StringVector columns, std::vector<float> weights)
		: Sheet("table")
		, mColumns(columns)
		, mWeights(weights)
	{}

	WTable::~WTable()
	{}

	void WTable::build()
	{
		mHead = this->makeappend<WTableHead>();

		for(string& name : mColumns)
			mHead->makeappend<WLabel>(name, "columnheader");

		for(float& weight : mWeights)
			this->stripe()->weightTable().push_back(weight);
	}

	Table::Table(StringVector columns, std::vector<float> weights)
		: Form("table", "", [columns, weights]() { return make_unique<WTable>(columns, weights); })
	{}

	// @ todo : table->add(Form* form)
}
