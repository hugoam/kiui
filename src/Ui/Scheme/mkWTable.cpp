//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Scheme/mkWTable.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Form/mkWidgets.h>

#include <Ui/Frame/mkFrame.h>

#include <iostream>

using namespace std::placeholders;

namespace mk
{
	WTableHead::WTableHead()
		: GridSheet(DIM_X, styleCls())
	{}

	void WTableHead::gridResized(Widget* first, Widget* second)
	{
		mParent->stripe()->weights()[first->frame()->index()] = first->frame()->dspan(DIM_X);
		mParent->stripe()->weights()[second->frame()->index()] = second->frame()->dspan(DIM_X);
		mParent->stripe()->markRelayout();
	}

	WColumnHeader::WColumnHeader(const string& label)
		: WLabel(label, styleCls())
	{}

	WTable::WTable(StringVector columns, std::vector<float> weights)
		: Sheet(styleCls())
		, mColumns(columns)
		, mWeights(weights)
	{}

	WTable::~WTable()
	{}

	void WTable::build()
	{
		mHead = this->makeappend<WTableHead>();

		for(string& name : mColumns)
			mHead->makeappend<WColumnHeader>(name);

		this->stripe()->initWeights();
		for(float& weight : mWeights)
			this->stripe()->weights().push_back(weight);
	}

	Table::Table(StringVector columns, std::vector<float> weights)
		: Form(nullptr, "", [columns, weights]() { return make_unique<WTable>(columns, weights); })
	{}

	// @ todo : table->add(Form* form)
}
