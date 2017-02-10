//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Frame/Stripe.h>

#include <toyobj/Iterable/Reverse.h>

#include <toyui/Widget/Widget.h>
#include <toyui/Widget/Sheet.h>

#include <algorithm>

namespace toy
{
	Stripe::Stripe(Widget& widget)
		: Frame(widget)
		, d_contents()
		, d_sequence(d_contents)
	{}

	Stripe::Stripe(StyleType& style, Stripe& parent)
		: Frame(style, parent)
		, d_contents()
		, d_sequence(d_contents)
	{}

	void Stripe::map(Frame& frame)
	{
		this->insert(frame, frame.widget()->index());
	}

	void Stripe::unmap(Frame& frame)
	{
		this->remove(frame);
	}

	void Stripe::remap()
	{}

	void Stripe::append(Frame& frame)
	{
		this->insert(frame, frame.flow() ? d_sequence.size() : d_contents.size());
	}

	void Stripe::insert(Frame& frame, size_t index)
	{
		if(frame.flow())
			index = std::min(d_sequence.size(), index);
		else
			index = std::max(d_sequence.size(), index);

		d_contents.insert(d_contents.begin() + index, &frame);
		this->reindex(index);
		if(frame.flow())
			++d_sequence.size();

		this->markDirty(DIRTY_LAYOUT);
	}

	void Stripe::remove(Frame& frame)
	{
		d_contents.erase(d_contents.begin() + frame.dindex(d_length));
		this->reindex(frame.dindex(d_length));
		if(frame.flow())
			--d_sequence.size();

		this->markDirty(DIRTY_LAYOUT);
	}

	void Stripe::clear()
	{
		d_sequence.size() = 0;
		d_contents.clear();
		this->markDirty(DIRTY_LAYOUT);
	}

	void Stripe::reindex(size_t from)
	{
		for(size_t i = from; i < d_contents.size(); ++i)
			d_contents[i]->setIndex(d_length, i);
	}

	void Stripe::move(size_t from, size_t to)
	{
		std::swap(d_contents[from], d_contents[to]);
		this->reindex(from < to ? from : to);
	}

	Frame* Stripe::before(Frame& frame)
	{
		int index = frame.dindex(d_length);
		while(index-- > 0)
			if(!d_contents[index]->hidden())
				return d_contents[index];
		return nullptr;
	}

	Frame& Stripe::prev(Frame& frame)
	{
		return *d_contents.at(frame.dindex(d_length) - 1);
	}

	Frame& Stripe::next(Frame& frame)
	{
		return *d_contents.at(frame.dindex(d_length) + 1);
	}

	bool Stripe::first(Frame& frame)
	{
		return frame.dindex(d_length) == 0;
	}

	bool Stripe::last(Frame& frame)
	{
		return frame.dindex(d_length) == d_sequence.size() - 1;
	}
	
	void Stripe::measure()
	{
		if(d_dirty < DIRTY_CONTENT)
			return;

		d_content = DimFloat(0.f, 0.f);

		if(d_sequence.size() < 1)
			Frame::measure();

		for(Frame* pframe : d_contents)
			this->measure(*pframe, d_content);

#if 0 // DEBUG
		this->debugPrintDepth();
		printf("%s measured content size %f , %f\n", this->style().name().c_str(), d_content[DIM_X], d_content[DIM_Y]);
#endif
	}

	void Stripe::measure(Frame& frame, DimFloat& content)
	{
		frame.measure();

		if(frame.hidden())
			return;

		if(frame.flow() && frame.dsizing(d_length) <= WRAP)
			content[d_length] += frame.dmeasure(d_length) + this->spacing(frame);

		if(frame.flow() && frame.dsizing(d_depth) <= WRAP)
			content[d_depth] = std::max(content[d_depth], frame.dmeasure(d_depth));
	}

	void Stripe::layout()
	{
		if(d_dirty < DIRTY_LAYOUT)
			return;

		this->normalizeSpan();

		DimFloat expanded;
		for(Frame* pframe : d_contents)
			this->resize(*pframe, expanded);

		DimFloat space;
		space[d_length] = std::max(this->dspace(d_length) - d_content[d_length] - expanded[d_length], 0.f);
		space[d_depth] = std::max(this->dspace(d_depth), 0.f);

		// the offset is our position relative to first parent widget frame (this skips layout frames)
		DimFloat offset;
		offset[d_length] = this->drelative(d_length);
		offset[d_depth] = this->drelative(d_depth);

		for(Frame* pframe : d_contents)
			this->layout(*pframe, offset, space);

#if 1 // DEBUG
		this->debugPrintDepth();
		printf("%s relayout size %f , %f\n", this->style().name().c_str(), dsize(DIM_X), dsize(DIM_Y));
#endif
	}

	void Stripe::resize(Frame& frame, DimFloat& expanded)
	{
		if(frame.hidden())
			return;

		if(d_layout->layout()[d_length] >= AUTOSIZE && frame.flow())
			expanded[d_length] += this->resize(frame, d_length);
		else if(d_layout->layout()[d_length] >= AUTOSIZE)
			this->resize(frame, d_length);

		if(d_layout->layout()[d_depth] >= AUTOSIZE)
			this->resize(frame, d_depth);

		frame.content().updateContentSize();
	}

	float Stripe::resize(Frame& frame, Dimension dim)
	{
		float space = this->dspace(dim);
		if(dim == d_length)
			space = (space - d_content[dim]) * frame.dspan(d_length);

		float content = frame.dcontent(dim) + frame.dpadding(dim) + frame.dbackpadding(dim);
		float expand = std::max(0.f, dim == d_length ? space : space - content);

		Sizing sizing = frame.dsizing(dim);

		if(sizing == SHRINK)
			frame.setSizeDim(dim, content);
		else if(sizing == WRAP)
			frame.setSizeDim(dim, content + expand);
		else if(sizing == EXPAND)
			frame.setSizeDim(dim, space);

		if(sizing == WRAP)
			return expand;
		else if(sizing == EXPAND)
			return space;
		else
			return 0.f;
	}

	void Stripe::layout(Frame& frame, DimFloat& offset, DimFloat& space)
	{
		this->position(frame, offset, space);
		frame.layout();
	}

	void Stripe::position(Frame& frame, DimFloat& offset, DimFloat& space)
	{
		if(frame.style().name() == "Dir")
			int i = 0;

		if(frame.hidden() || frame.unflow())
			return;

		if(d_layout->layout()[d_length] >= AUTOLAYOUT && frame.flow())
			frame.setPositionDim(d_length, this->positionSequence(frame, offset[d_length], space[d_length]));
		else if(d_layout->layout()[d_length] >= AUTOLAYOUT)
			frame.setPositionDim(d_length, this->positionFree(frame, d_length, offset[d_length], this->dspace(d_length)));

		if(d_layout->layout()[d_depth] >= AUTOLAYOUT)
			frame.setPositionDim(d_depth, this->positionFree(frame, d_depth, offset[d_depth], this->dspace(d_depth)));
	}

	float Stripe::positionFree(Frame& frame, Dimension dim, float offset, float space)
	{
		Align align = frame.dalign(dim);
		float alignOffset = space * AlignSpace[align] - frame.dextent(dim) * AlignExtent[align];
		return offset + (frame.flow() ? dpadding(dim) + frame.dmargin(dim) : 0.f) + alignOffset;
	}

	float Stripe::positionSequence(Frame& frame, float offset, float space)
	{
		Frame* before = this->before(frame);
		if(before)
			return before->doffset(d_length) + this->spacing(frame) - alignSequence(*before, space) + alignSequence(frame, space);
		else
			return offset + dpadding(d_length) + frame.dmargin(d_length) + alignSequence(frame, space);
	}

	Frame* Stripe::pinpoint(float x, float y, bool opaque)
	{
		if(this->hollow() || !this->inside(x, y))
			return nullptr;

		for(Frame* frame : reverse_adapt(d_contents))
			if(!frame->hidden() && frame->frameType() < MASTER_LAYER)
			{
				Frame* target = frame->widget() ? frame->pinpoint(x - frame->left(), y - frame->top(), opaque)
											    : frame->pinpoint(x, y, opaque);

				if(target)
					return target;
			}

		return Frame::pinpoint(x, y, opaque);
	}

	void Stripe::normalizeSpan()
	{
		float span = 0.f;

		for(Frame* frame : d_sequence)
			if(frame->dexpand(d_length) && !frame->hidden())
				span += frame->dspan(d_length);

		for(Frame* frame : d_sequence)
			if(frame->dexpand(d_length) && !frame->hidden())
				frame->setSpanDimDirect(d_length, frame->dspan(d_length) / span);
	}

	float Stripe::nextOffset(Dimension dim, float pos)
	{
		pos -= d_position[dim];

		for(Frame* frame : d_sequence)
			if(frame->dposition(dim) + frame->dsize(dim) > pos)
			{
				if(frame->frameType() >= STRIPE)
					return d_position[dim] + frame->as<Stripe>().nextOffset(dim, pos);
				else
					return d_position[dim] + frame->dposition(dim) + frame->dsize(dim);
			}

		return d_position[dim] + d_size[dim];
	}

	float Stripe::prevOffset(Dimension dim, float pos)
	{
		pos -= d_position[dim];

		for(Frame* frame : reverse_adapt(d_sequence))
			if(frame->dposition(dim) < pos)
			{
				if(frame->frameType() >= STRIPE)
					return d_position[dim] + frame->as<Stripe>().prevOffset(dim, pos);
				else
					return d_position[dim] + frame->dposition(dim);
			}

		return d_position[dim];
	}
}
