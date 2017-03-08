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

	Stripe::Stripe(Style& style, Stripe& parent)
		: Frame(style, parent)
		, d_contents()
		, d_sequence(d_contents)
	{}

	void Stripe::map(Frame& frame)
	{
		frame.bind(*this);
		this->insert(frame, frame.widget()->index());
	}

	void Stripe::unmap(Frame& frame)
	{
		frame.unbind();
		this->remove(frame);
	}

	void Stripe::remap()
	{
		if(d_dirty < DIRTY_MAPPING)
			return;

		this->unmap();

		for(Widget* widget : d_widget->as<Wedge>().contents())
		{
			this->map(widget->frame());
			widget->frame().remap();
		}
	}

	void Stripe::unmap()
	{
		this->clear();
	}

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

		this->markDirty(DIRTY_STRUCTURE);
	}

	void Stripe::remove(Frame& frame)
	{
		d_contents.erase(d_contents.begin() + frame.dindex(d_length));
		this->reindex(frame.dindex(d_length));
		if(frame.flow())
			--d_sequence.size();

		this->markDirty(DIRTY_STRUCTURE);
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

	void Stripe::visit(Stripe& root, const Visitor& visitor)
	{
		if(this != &root)
		{
			bool pursue = visitor(*this);
			if(!pursue)
				return;
		}

		for(Frame* pframe : d_contents)
			pframe->visit(root, visitor);
	}

	void Stripe::measureLayout()
	{
		if(d_dirty < DIRTY_CONTENT)
			return;

		d_content = DimFloat(0.f, 0.f);
		d_spaceContent = DimFloat(0.f, 0.f);
		d_contentExpand = false;

		if(d_sequence.size() < 1)
			Frame::measureLayout();

		for(Frame* pframe : d_contents)
			this->measure(*pframe);
	}

	void Stripe::resizeLayout()
	{
		if(d_dirty < DIRTY_LAYOUT)
			return;

		this->normalizeSpan();

		for(Frame* pframe : d_contents)
			this->resize(*pframe);
	}

	void Stripe::positionLayout()
	{
		if(d_dirty < DIRTY_LAYOUT)
			return;

		for(Frame* pframe : d_contents)
			this->position(*pframe);
	}

	void Stripe::measure(Frame& frame)
	{
		frame.measureLayout();

		if(frame.hidden() || !frame.sizeflow())
			return;

		this->measure(frame, d_length);
		this->measure(frame, d_depth);

		if(frame.dsizing(d_length) > WRAP)
			d_contentExpand = true;

#if 0 // DEBUG
		frame.debugPrintDepth();
		printf("%s measured content size %f , %f\n", frame.style().name().c_str(), frame.dcontent(DIM_X), frame.dcontent(DIM_Y));
#endif
	}

	void Stripe::measure(Frame& frame, Dimension dim)
	{
		if(frame.dsizing(dim) > WRAP)
			return;

		if(dim == d_length && frame.flow())
			d_content[dim] += frame.dmeasure(dim) + this->spacing(frame);
		else
			d_content[dim] = std::max(d_content[dim], frame.dmeasure(dim));


		if(frame.dsizing(dim) > SHRINK || !frame.flow())
			return;

		if(dim == d_length && frame.flow())
			d_spaceContent[dim] += frame.dmeasure(dim) + this->spacing(frame);
		else
			d_spaceContent[dim] = std::max(d_spaceContent[dim], frame.dmeasure(dim));
	}

	void Stripe::resize(Frame& frame)
	{
		if(frame.hidden())
			return;

		this->resize(frame, d_length);
		this->resize(frame, d_depth);

#if 0 // DEBUG
		frame.debugPrintDepth();
		printf("%s resize size %f , %f\n", frame.style().name().c_str(), frame.dsize(DIM_X), frame.dsize(DIM_Y));
#endif

		frame.content().updateContentSize();

		frame.resizeLayout();
	}

	void Stripe::resize(Frame& frame, Dimension dim)
	{
		if(d_style->layout().layout()[dim] < AUTO_SIZE)
			return;

		float space = this->dspace(dim);
		if(dim == d_length)
			space = (space - d_spaceContent[dim]) * frame.dspan(d_length);

		float content = frame.dcontent(dim) + frame.dpadding(dim) + frame.dbackpadding(dim);
		float expand = std::max(0.f, space - content);

		Sizing sizing = frame.dsizing(dim);
		if(sizing == SHRINK)
			frame.setSizeDim(dim, content);
		else if(sizing == WRAP)
			frame.setSizeDim(dim, content + expand);
		else if(sizing == EXPAND)
			frame.setSizeDim(dim, space);
	}

	void Stripe::position(Frame& frame)
	{
		if(frame.hidden())
			return;

		if(frame.posflow())
		{
			this->position(frame, d_length);
			this->position(frame, d_depth);
		}

		frame.positionLayout();

#if 0 // DEBUG
		frame.debugPrintDepth();
		printf("%s layout position %f , %f\n", frame.style().name().c_str(), frame.dposition(DIM_X), frame.dposition(DIM_Y));
#endif
	}

	void Stripe::position(Frame& frame, Dimension dim)
	{
		if(d_style->layout().layout()[dim] < AUTO_LAYOUT)
			return;

		float offset = frame.widget() ? this->doffset(dim) : 0.f;
		float space = this->dspace(dim);

		if(dim == d_length && frame.flow())
			frame.setPositionDim(dim, this->positionSequence(frame, offset, d_contentExpand ? 0.f : space - d_content[d_length]));
		else
			frame.setPositionDim(dim, this->positionFree(frame, dim, offset, space));
	}

	float Stripe::positionFree(Frame& frame, Dimension dim, float offset, float space)
	{
		Align align = frame.dalign(dim == d_length ? DIM_X : DIM_Y);
		float alignOffset = space * AlignSpace[align] - frame.dextent(dim) * AlignExtent[align];
		return offset + (frame.flow() ? dpadding(dim) + frame.dmargin(dim) : 0.f) + alignOffset;
	}

	namespace
	{
		inline float alignSequence(Frame& frame, float space) { return space * AlignSpace[frame.dalign(DIM_X)]; }
	}

	float Stripe::positionSequence(Frame& frame, float offset, float space)
	{
		Frame* before = this->before(frame);
		if(before)
			return before->dposition(d_length) + before->dextent(d_length) + this->spacing(frame) - alignSequence(*before, space) + alignSequence(frame, space);
		else
			return offset + dpadding(d_length) + frame.dmargin(d_length) + alignSequence(frame, space);
	}

	Frame* Stripe::pinpoint(float x, float y, bool opaque)
	{
		if(this->hidden() || this->hollow() || (this->clip() && !this->inside(x, y)))
			return nullptr;

		if(!this->widget())
		{
			x += this->left();
			y += this->top();
		}

		for(Frame* frame : reverse_adapt(d_contents))
		{
			Frame* target = frame->pinpoint((x - frame->left()) / frame->scale(), (y - frame->top()) / frame->scale(), opaque);
			if(target)
				return target;
		}

		if(!this->widget())
		{
			x -= this->left();
			y -= this->top();
		}

		return Frame::pinpoint(x, y, opaque);
	}

	void Stripe::transferPixelSpan(Frame& prev, Frame& next, float pixelSpan)
	{
		float pixspan = 1.f / this->dsize(d_length);
		float offset = pixelSpan * pixspan;

		prev.setSpanDim(d_length, std::max(0.01f, prev.dspan(d_length) + offset));
		next.setSpanDim(d_length, std::max(0.01f, next.dspan(d_length) - offset));
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
