//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <toyui/Config.h>
#include <toyui/Frame/Grid.h>

#include <toyui/Widget/Sheet.h>

namespace toy
{
	GridOverlay::GridOverlay(Widget& widget, Stripe& parent)
		: Stripe(widget.fetchStyle(cls()), parent)
	{}

	GridLine::GridLine(Widget& widget, Stripe& parent)
		: Stripe(widget.fetchStyle(cls()), parent)
	{}

	GridColumn::GridColumn(Widget& widget, Stripe& parent)
		: Stripe(widget.fetchStyle(cls()), parent)
	{}

	GridSubdiv::GridSubdiv(Widget& widget, Stripe& parent, size_t level, Dimension dim)
		: Stripe(widget.fetchStyle(cls()), parent)
		, d_level(level)
	{
		this->setLength(dim);
	}

	TableGrid::TableGrid(Widget& widget)
		: Stripe(widget)
		, d_grid(make_object<GridOverlay>(widget, *this))
	{}

	void TableGrid::deepMap(Frame& frame)
	{
		Stripe& stripe = *frame.parent();

		if(stripe.length() != d_depth || stripe.parent() != this) //|| stripe.dindex(d_length) > d_sequence.size())
			return;

		this->resize(stripe.sequence().size());
		if(stripe.sequence().size() >= d_columns.size())
			for(size_t i = 0; i < d_columns.size(); ++i)
				d_columns[i]->append(*stripe.contents()[i]);
	}

	void TableGrid::deepUnmap(Frame& frame)
	{
		for(auto& column : d_columns)
			if(std::find(column->contents().begin(), column->contents().end(), &frame) != column->contents().end())
				column->remove(frame);
	}

	void TableGrid::resize(size_t columns)
	{
		while(d_columns.size() < columns)
			d_columns.emplace_back(make_object<GridColumn>(*d_widget, *d_grid));
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
		frame.bind(*d_lines[line]);
	}

	void Grid::unmap(Frame& frame)
	{
		size_t line = frame.dindex(d_length);
		d_lines[line]->remove(frame);
	}

	void Grid::resize(size_t lines)
	{
		while(d_lines.size() < lines)
			d_lines.emplace_back(make_object<GridLine>(*d_widget, *this));
	}

	void Grid::move(Frame& frame, size_t xindex, size_t yindex)
	{
		this->unmap(frame);
		frame.setIndex(xindex, yindex);
		this->map(frame);
	}
}

