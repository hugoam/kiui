//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <toyui/Config.h>
#include <toyui/Frame/Grid.h>

#include <toyui/Widget/Sheet.h>

namespace toy
{
	GridOverlay::GridOverlay(Stripe& parent)
		: Stripe(cls(), parent)
	{}

	GridLine::GridLine(Stripe& parent)
		: Stripe(cls(), parent)
	{}

	GridColumn::GridColumn(Stripe& parent)
		: Stripe(cls(), parent)
	{}

	TableGrid::TableGrid(Widget& widget)
		: Stripe(widget)
		, d_grid(*this)
	{}

	void TableGrid::remap()
	{
		for(Frame* pframe : d_sequence)
			if(pframe->frameType() >= STRIPE)
				this->remap(pframe->as<Stripe>());
	}

	void TableGrid::remap(Stripe& stripe)
	{
		if(stripe.length() != d_depth)
			return;

		this->resize(stripe.sequence().size());
		if(stripe.sequence().size() >= d_columns.size())
			for(size_t i = 0; i < d_columns.size(); ++i)
				d_columns[i]->append(*stripe.contents()[i]);
	}

	void TableGrid::resize(size_t columns)
	{
		while(d_columns.size() < columns)
			d_columns.emplace_back(make_unique<GridColumn>(d_grid));
	}

	void TableGrid::layout()
	{
		Stripe::layout();
		d_grid.layout();
	}

	Grid::Grid(Widget& widget)
		: Stripe(widget)
	{}

	void Grid::map(Frame& frame)
	{
		size_t line = frame.dindex(d_length);
		size_t index = frame.dindex(d_depth);
		this->resize(line + 1);
		d_lines[line]->insert(frame, index);
	}

	void Grid::unmap(Frame& frame)
	{
		size_t line = frame.dindex(d_length);
		d_lines[line]->remove(frame);
	}

	void Grid::resize(size_t lines)
	{
		while(d_lines.size() < lines)
			d_lines.emplace_back(make_unique<GridLine>(*this));
	}
}

