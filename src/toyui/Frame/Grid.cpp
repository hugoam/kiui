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
		, d_grid(make_unique<GridOverlay>(widget, *this))
	{}

	void TableGrid::remap()
	{
		if(d_dirty < DIRTY_MAPPING)
			return;

		Stripe::remap();

		for(Frame* pframe : d_sequence)
			if(pframe->frameType() >= STRIPE)
				this->remap(pframe->as<Stripe>());
	}

	void TableGrid::unmap()
	{
		Stripe::unmap();
		this->append(*d_grid);
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
			d_columns.emplace_back(make_unique<GridColumn>(*d_widget, *d_grid));
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
	
	void Grid::unmap()
	{
		for(auto& line : d_lines)
			line->clear();
	}

	void Grid::resize(size_t lines)
	{
		while(d_lines.size() < lines)
			d_lines.emplace_back(make_unique<GridLine>(*d_widget, *this));
	}

	MultiGrid::MultiGrid(Widget& widget)
		: Stripe(widget)
		, d_maindiv(make_unique<GridSubdiv>(widget, *this, 0, DIM_Y))
	{}

	void MultiGrid::printIndex(const GridIndex& index)
	{
		printf("GridIndex : ");
		for(size_t i : index)
			printf("%u, ", i);
		printf("\n");
	}

	Stripe& MultiGrid::appendLine(Stripe& parent, size_t level)
	{
		d_subdivs.emplace_back(make_unique<GridSubdiv>(*d_widget, parent, level, parent.length() == DIM_X ? DIM_Y : DIM_X));
		return *d_subdivs.back();
	}

	Stripe& MultiGrid::findLine(GridIndex index)
	{
		printf("MultiGrid : find line");
		this->printIndex(index);

		std::reverse(index.begin(), index.end());

		Stripe* line = d_maindiv.get();
		size_t level = 0;

		while(index.size() > 0)
		{
			size_t subindex = index.back(); index.pop_back();
			while(line->sequence().size() <= subindex)
				this->appendLine(*line, level);
			line = &line->contents()[subindex]->as<Stripe>();
			++level;
		}

		return *line;
	}

	void MultiGrid::map(Frame& frame)
	{
		GridIndex location = frame.widget()->frameIndex()->get<GridIndex>();

		Stripe& line = this->findLine(location);
		line.append(frame);
		frame.bind(line);
	}

	void MultiGrid::unmap(Frame& frame)
	{
		this->remove(frame);
	}

	void MultiGrid::unmap()
	{
		for(Widget* widget : d_widget->as<Wedge>().contents())
		{
			Frame& frame = widget->frame();
			if(frame.parent())
				frame.parent()->remove(frame);
		}

		//d_subdivs.clear();
		//d_maindiv->clear();
	}

	void MultiGrid::remove(Frame& element)
	{
		printf("MultiGrid : remove line\n");

		Stripe& parent = *element.parent();
		size_t index = element.dindex(parent.length());
		parent.remove(element);

		if(&parent == this)
			return;

		if(parent.contents().size() == 0)
			this->remove(parent);
		else
			this->shift(parent.as<GridSubdiv>(), index, -1);
	}

	void MultiGrid::shift(GridSubdiv& line, size_t from, int amount)
	{
		size_t level = line.level() + 1;

		line.visit(line, [level, from, amount](Frame& frame)
		{
			if(!frame.widget() || &frame.widget()->frameIndex()->type() != &typecls<GridIndex>()) // shitty way to check if we are leaf subdiv
				return true;
			GridIndex& index = frame.widget()->frameIndex()->ref<GridIndex>();
			if(index[level] > from)
				index[level] += amount;
			return true;
		});
	}

	GridIndex MultiGrid::insertNextTo(Frame& frame, bool before)
	{
		GridSubdiv& line = frame.parent()->as<GridSubdiv>();
		GridIndex index = frame.widget()->frameIndex()->get<GridIndex>();

		size_t level = index.size() - 1;
		size_t position = before ? index[level] - 1 : index[level];

		this->shift(line.parent()->as<GridSubdiv>(), position, 1);

		index[level] = before ? index[level] : index[level] + 1;

		return index;
	}

	GridIndex MultiGrid::insertDivide(Frame& frame, bool before)
	{
		GridSubdiv& line = frame.parent()->as<GridSubdiv>();

		GridIndex location = frame.widget()->frameIndex()->ref<GridIndex>();
		location.push_back(before ? 1 : 0);

		frame.widget()->frameIndex()->set<GridIndex>(location);

		location.back() = before ? 0 : 1;
		return location;
	}

	void MultiGrid::locate(float x, float y, GridSubdiv*& line, Frame*& prev, Frame*& next)
	{
		Frame* target = this->pinpoint(x, y, false);

		if(&target->style() != &d_widget->fetchStyle(GridSubdiv::cls()))
			return;

		line = &target->as<GridSubdiv>();

		DimFloat local(x, y);
		line->integratePosition(*this, local);

		float pos = line->length() == DIM_X ? local.x() : local.y();
		for(Frame* frame : line->sequence())
			if(frame->dposition(line->length()) >= pos)
			{
				next = frame;
				prev = line->before(*next);
				break;
			}
	}
}

