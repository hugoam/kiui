//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Frame/mkStripe.h>

#include <Object/Iterable/mkReverse.h>

#include <Ui/Frame/mkInk.h>

#include <algorithm>
#include <iostream>

#include <Ui/Widget/mkWidget.h>
#include <Ui/Form/mkForm.h>

#include <Ui/Scheme/mkTree.h>

namespace mk
{

	Stripe::Stripe(Widget* widget)
		: Frame(widget)
		, d_depth(d_style->d_layoutDim == DIM_X ? DIM_Y : DIM_X)
		, d_length(d_style->d_layoutDim)
		, d_cursor(0.f)
		, d_contents()
		, d_sequence(d_contents)
		, d_sequenceLength(0)
		, d_maxDepth(0)
		, d_relayout(true)
		, d_weights()
	{
		if(d_style->d_weights.size() > 0)
			this->initWeights();
	}

	Stripe::~Stripe()
	{}

	void Stripe::append(Frame* frame)
	{
		this->insert(frame, frame->flow() ? d_sequence.size() : d_contents.size());
	}

	void Stripe::insert(Frame* frame, size_t index)
	{
		frame->bind(this);

		if(frame->flow())
			index = std::min(d_sequence.size(), index);

		d_contents.insert(d_contents.begin() + index, frame);
		this->reindex(index);

		if(frame->flow())
			this->insertFlow(frame, index);
	}

	void Stripe::remove(Frame* frame)
	{
		frame->unbind();
		d_contents.erase(d_contents.begin() + frame->index());
		this->reindex(frame->index());

		if(frame->flow())
			this->removeFlow(frame);
	}

	void Stripe::clear()
	{
		d_contents.clear();
		d_relayout = true;
	}

	void Stripe::insertFlow(Frame* frame, size_t index)
	{
		UNUSED(index);
		++d_sequence.size();
		d_relayout = true;

		if(!frame->hidden())
			this->flowShown(frame);
	}

	void Stripe::removeFlow(Frame* frame)
	{
		--d_sequence.size();
		d_relayout = true;

		if(!frame->hidden())
			this->flowHidden(frame);
	}

	void Stripe::reindex(size_t from)
	{
		for(size_t i = from; i < d_contents.size(); ++i)
			d_contents[i]->setIndex(i);
	}

	void Stripe::move(size_t from, size_t to)
	{
		std::swap(d_contents[from], d_contents[to]);
		this->reindex(from < to ? from : to);
	}

	void Stripe::recomputeLength()
	{
		d_sequenceLength = 0.f;

		for(Frame* frame : d_sequence)
			if(!frame->dexpand(d_length) && !frame->hidden())
				d_sequenceLength += frame->doffset(d_length) + (frame == d_contents[d_sequence.size()-1]/*d_sequence.back()*/ ? 0.f : d_style->d_spacing[d_length]);

		this->updateLength();
	}

	void Stripe::recomputeDepth()
	{
		d_maxDepth = 0.f;

		for(Frame* frame : d_sequence)
			if(dshrink(d_depth))
				d_maxDepth = std::max(d_maxDepth, frame->doffset(d_depth));

		this->updateDepth();
	}

	void Stripe::updateLength()
	{
		if(dshrink(d_length))// || dwrap(d_length))
			this->setSizeDim(d_length, d_sequenceLength + d_style->d_padding[d_length] + d_style->d_padding[d_length+2]);
	}

	void Stripe::updateDepth()
	{
		if(dshrink(d_depth)) // || dwrap(d_depth))
			this->setSizeDim(d_depth, d_maxDepth + d_style->d_padding[d_depth] + d_style->d_padding[d_depth+2]);
	}

	void Stripe::expandDepth()
	{
		for(Frame* frame : d_contents)
			if(frame->dexpand(d_depth))
				frame->setSizeDim(d_depth, dspace(d_depth));
	}

	void Stripe::expandLength()
	{
		float freeSpace = dspace(d_length) - d_sequenceLength;

		for(Frame* frame : d_contents)
			if(frame->dexpand(d_length))
			{
				if(frame->flow())
					frame->setSizeDim(d_length, freeSpace * frame->dspan(d_length));
				else
					frame->setSizeDim(d_length, dspace(d_length));
			}
	}

	void Stripe::relayout()
	{
		if(!d_relayout)
			return;

		d_relayout = false;

		this->normalizeSpan();

		if(d_style->d_weight == LIST && d_weights && d_weights->size() > 0)
			this->dispatchWeights();
		else if(d_style->d_weight == TABLE)
			this->dispatchTableWeights();

		this->expandDepth();
		this->expandLength();

		this->positionSequence();

#if 0 // DEBUG
			Stripe* parent = d_parent;
			while(parent)
			{
				printf("  ");
				parent = parent->parent();
			}

			printf("Stripe :: relayout %s name %s size %f , %f\n", d_widget->style()->name().c_str(), d_widget->name().c_str(), dsize(DIM_X), dsize(DIM_Y));
#endif
	}

	void Stripe::positionSequence()
	{
		float offset = -d_cursor + d_style->d_padding[d_length];

		Frame* prev = nullptr;
		for(Frame* frame : d_sequence)
			if(!frame->hidden())
			{
				frame->setPositionDim(d_length, !prev ? offset : prev->dposition(d_length) + prev->dsize(d_length) + d_style->d_spacing[d_length]);
				frame->setPositionDim(d_depth, d_style->d_padding[d_depth] + frame->dmargin(d_depth) / 2);
				prev = frame;
			}
	}

	void Stripe::initWeights()
	{
		d_weights = make_unique<std::vector<float>>();
		*d_weights = d_style->d_weights;
	}

	void Stripe::dispatchWeights()
	{
		for(size_t index = 0; index != d_weights->size(); ++index)
			if((*d_weights)[index] >= 0.f)
				d_contents[index]->setSpanDim(d_length, (*d_weights)[index]);

		d_weights->clear();
	}

	void Stripe::dispatchTableWeights()
	{
		for(size_t index = 0; index != d_weights->size(); ++index)
			for(Frame* frame : d_sequence)
				if(frame->as<Stripe>()->sequence().size() == d_weights->size())
					frame->as<Stripe>()->contents()[index]->setSpanDim(d_depth, (*d_weights)[index]);
	}

	void Stripe::nextFrame(size_t tick, size_t delta)
	{
		// Layouting consists of :
		//	0. Shrinking the tree recursively from leaves to root to determine free space (Done each time a frame size is adjusted)
		//	1. Expanding the tree recursively from root to leaves to occupy all space (Upward relayout)
		//		Size the tree recursively from root to leaves
		//		Position the tree recursively from root to leaves

		this->relayout();

		Frame::nextFrame(tick, delta);
	}

	void Stripe::deepRelayout()
	{
		this->markRelayout();

		for(Frame* frame : d_contents)
			if(frame->frameType() >= STRIPE)
				frame->as<Stripe>()->deepRelayout();
	}

	void Stripe::markDirty(Dirty dirty)
	{
		Frame::markDirty(dirty);

		for(Frame* frame : d_contents)
			frame->markDirty(dirty);
	}

	void Stripe::setVisible(bool visible)
	{
		Frame::setVisible(visible);

		for(Frame* frame : d_contents)
			frame->setVisible(visible);
	}

	void Stripe::migrate(Stripe* stripe)
	{
		Frame::migrate(stripe);
		
		for(Frame* frame : d_contents)
			if(!frame->layer())
				frame->migrate(stripe);
	}

	void Stripe::flowShown(Frame* child)
	{
		if(d_sequence.size() > 1)
			d_sequenceLength += d_style->d_spacing[d_length];

		if(!child->dexpand(d_length))
			this->flowSizedLength(child, child->doffset(d_length));

		if(!child->dexpand(d_depth))
			this->flowSizedDepth(child, child->doffset(d_depth));
	}

	void Stripe::flowHidden(Frame* child)
	{
		if(d_sequence.size() > 1)
			d_sequenceLength -= d_style->d_spacing[d_length];

		if(!child->dexpand(d_length))
			this->flowSizedLength(child, -child->doffset(d_length));

		if(!child->dexpand(d_depth))
			this->flowSizedDepth(child, -child->doffset(d_depth));
	}

	void Stripe::flowSizedLength(Frame* child, float delta)
	{
		UNUSED(child);
		d_sequenceLength += delta;
		this->updateLength();
		d_relayout = true;
	}

	void Stripe::flowSizedDepth(Frame* child, float delta)
	{
		if(delta < 0.f && d_maxDepth == -delta + child->doffset(d_depth))
		{
			this->recomputeDepth();
		}
		else if(delta > 0.f)
		{
			d_maxDepth = std::max(d_maxDepth, child->doffset(d_depth));
			this->updateDepth();
		}
	}

	void Stripe::flowSized(Frame* child, Dimension dim, float delta)
	{
		if(child->hidden())
			return;

		if(dim == d_length)
			this->flowSizedLength(child, delta);
		else
			this->flowSizedDepth(child, delta);
	}

	void Stripe::resized(Dimension dim)
	{
		UNUSED(dim);
		if(dim == d_length)
			this->expandLength();
		else
			this->expandDepth();
		d_relayout = true;
	}

	Frame* Stripe::pinpoint(float x, float y, bool opaque)
	{
		if(!this->inside(x, y))
			return nullptr;

		Frame* target;
		for(Frame* frame : reverse_adapt(d_contents))
			if(frame->visible())
			{
				target = frame->pinpoint(x, y, opaque);
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
				frame->setSpanDimDirect(d_length, (1.f / span) * frame->dspan(d_length));
	}

	float Stripe::firstVisible()
	{
		// Find first whole frame : broken because we only account for first level of children

		float pos = 0.f;
		for(Frame* frame : d_sequence)
		{
			if(pos >= d_cursor)
				break;

			pos += frame->doffset(d_length);
		}

		return -pos + d_style->d_padding[d_length];
	}
}
