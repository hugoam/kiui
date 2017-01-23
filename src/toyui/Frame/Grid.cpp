//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

/*
#include <toyui/Config.h>
#include <toyui/Frame/Grid.h>

#include <toyobj/Store/Reverse.h>
#include <toyobj/Util/Make.h>

#include <toyui/Frame/Ink.h>

#include <algorithm>
#include <iostream>

#include <toyui/Widget/Widget.h>
#include <toyui/Form/Form.h>

#include <toyui/UiWindow.h>
#include <toyui/UiLayout.h>

#include <toyui/Widget/Layer.h>

namespace toy
{
	Grid::Grid(Stripe* parent, LayoutStyle* style, Skin* skin, InkLayer* inklayer, Widget* widget)
		: Stripe(parent, style, skin, inklayer, widget)
	{
		this->addStripe();
	}

	Grid::~Grid()
	{}

	void Grid::addStripe()
	{
		UiWindow* window = d_widget->uiWindow();
		d_stripes.push_back(make<Stripe>(nullptr, window->layout()->style("gridline"), window->skinner()->skin("gridline"), d_widget->layer()->inkLayer(), nullptr));
		d_stripes.back()->setParent(this);
		d_sequence.push_back(d_stripes.back().get());
		d_contents.push_back(d_stripes.back().get());
	}
	void Grid::add(Frame* frame)
	{
		if(frame->flow())
			appendFlow(frame);
		else
			insertManual(frame);
	}

	void Grid::appendFlow(Frame* frame)
	{
		if(frame->style()->d_div)
			this->addStripe();

		frame->setParent(this);
		d_sequence.back()->as<Stripe>()->add(frame);
		d_relayout = true;
	}

	void Grid::insertStripe(float x, float y, Frame* frame)
	{}
}
*/