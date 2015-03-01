//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Frame/mkStripe.h>

#include <Object/Store/mkReverse.h>

#include <Ui/Frame/mkInk.h>

#include <algorithm>
#include <iostream>

#include <Ui/Widget/mkWidget.h>
#include <Ui/Form/mkForm.h>

namespace mk
{
	Stripe::Stripe(Stripe* parent, Widget* widget, string clas)
		: Frame(parent, widget, clas)
		, d_depth(d_style->d_layoutDim == DIM_X ? DIM_Y : DIM_X)
		, d_length(d_style->d_layoutDim)
		, d_cursor(0.f)
		, d_sequence()
		, d_sequenceLength(0)
		, d_maxDepth(0)
		, d_relayout(true)
		, d_weightTable(d_style->d_weightTable)
	{
		d_frameType = STRIPE;
	}

	Stripe::~Stripe()
	{}

	void Stripe::append(Frame* frame)
	{
		if(frame->flow())
			appendFlow(frame);
		else
			appendManual(frame);
	}

	void Stripe::insert(Frame* frame, size_t index)
	{
		if(frame->flow())
			insertFlow(frame, index);
		else
			insertManual(frame, index);
	}

	void Stripe::remove(Frame* frame)
	{
		if(frame->flow())
			removeFlow(frame);
		else
			removeManual(frame);
	}

	void Stripe::appendManual(Frame* frame)
	{
		this->insertManual(frame, d_contents.size());
	}

	void Stripe::insertManual(Frame* frame, size_t index)
	{
		frame->setParent(this);
		d_contents.insert(d_contents.begin() + index, frame);
		this->reindexManual(index);
	}

	void Stripe::removeManual(Frame* frame)
	{
		d_contents.erase(std::remove(d_contents.begin(), d_contents.end(), frame), d_contents.end());
		this->reindexManual(0);
	}

	void Stripe::clear()
	{
		d_sequence.clear();
		d_contents.clear();
		d_relayout = true;
	}

	void Stripe::insertFlow(Frame* frame, size_t index)
	{
		frame->setParent(this);
		d_sequence.insert(d_sequence.begin() + index, frame);
		d_contents.push_back(frame);
		this->reindexFlow(index);
		d_relayout = true;
	}

	void Stripe::removeFlow(Frame* frame)
	{
		d_sequence.erase(std::remove(d_sequence.begin(), d_sequence.end(), frame), d_sequence.end());
		d_contents.erase(std::remove(d_contents.begin(), d_contents.end(), frame), d_contents.end());
		this->reindexFlow(0);
		this->normalizeSpan();
		d_relayout = true;
	}

	void Stripe::reindexFlow(size_t from)
	{
		for(size_t i = from; i < d_sequence.size(); ++i)
			d_sequence[i]->setIndex(i);
	}

	void Stripe::reindexManual(size_t from)
	{
		for(size_t i = from; i < d_contents.size(); ++i)
			if(!d_contents[i]->flow())
				d_contents[i]->setIndex(i);
	}

	void Stripe::shiftBack(Frame* toshift)
	{
		for(size_t i = 0; i < d_sequence.size(); ++i)
			if(d_sequence[i] == toshift)
			{
				std::swap(d_sequence[i-1], d_sequence[i]);
				break;
			}

		d_relayout = true;
	}

	void Stripe::move(size_t from, size_t to)
	{
		Frame* toshift = d_sequence[from];
		d_sequence.insert(d_sequence.begin() + to, toshift);
		d_sequence.erase(from < to ? d_sequence.begin() + from : d_sequence.begin() + from + 1);
		this->reindexFlow(from < to ? from : to);
	}

	void Stripe::updateLength()
	{
		d_sequenceLength = 0.f;

		for(Frame* frame : d_sequence)
			if(!frame->dexpand(d_length) && !frame->hidden())
				d_sequenceLength += frame->doffset(d_length) + (frame == d_sequence.back() ? 0.f : d_style->d_spacing[d_length]);

		if(dshrink(d_length))// || dwrap(d_length))
			this->setSizeDim(d_length, d_sequenceLength + d_style->d_frontpadding[d_length] + d_style->d_backpadding[d_length]);
	}

	void Stripe::updateDepth()
	{
		d_maxDepth = 0.f;

		for(Frame* frame : d_sequence)
			if(dshrink(d_depth))
				d_maxDepth = std::max(d_maxDepth, frame->doffset(d_depth));

		if(dshrink(d_depth)) // || dwrap(d_depth))
			this->setSizeDim(d_depth, d_maxDepth + d_style->d_frontpadding[d_length] + d_style->d_backpadding[d_length]);
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
				if(frame->flow())
					frame->setSizeDim(d_length, freeSpace * frame->dspan(d_length) - (frame == d_sequence.back() ? 0.f : d_style->d_spacing[d_length])); // @note not optimal since we remove the spacing from the first item, but to account for spacing evenly we should keep track of the number of expanding elements
				else
					frame->setSizeDim(d_length, dspace(d_length));
	}

	void Stripe::relayout()
	{
		if(!d_relayout)
			return;

		d_relayout = false;

		this->normalizeSpan();

		if(d_weightTable.size() > 0)
			this->distributeWeights();

		this->expandDepth();
		this->expandLength();

#if 0 // DEBUG
			Stripe* parent = d_parent;
			while(parent)
			{
				std::cerr << "  ";
				parent = parent->parent();
			}

			std::cerr << "Stripe :: relayout " << d_widget->clas() << " name " << d_widget->name() <<  " size " << dsize(DIM_X) << " , " << dsize(DIM_Y) << std::endl;
#endif

		this->positionSequence();
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

		return -pos + d_style->d_frontpadding[d_length];
	}

	void Stripe::positionSequence()
	{
		float offset = -d_cursor + d_style->d_frontpadding[d_length];

		Frame* prev = nullptr;
		for(Frame* frame : d_sequence)
			if(!frame->hidden())
			{
				frame->setPositionDim(d_length, !prev ? offset : prev->dposition(d_length) + prev->dsize(d_length) + d_style->d_spacing[d_length]);
				frame->setPositionDim(d_depth, d_style->d_frontpadding[d_depth] + frame->dmargin(d_depth) / 2);
				prev = frame;
			}
	}

	void Stripe::distributeWeights()
	{
		for(size_t index = 0; index != d_weightTable.size(); ++index)
			for(Frame* frame : d_sequence)
				if(frame->as<Stripe>()->sequence().size() == d_weightTable.size())
					frame->as<Stripe>()->sequence()[index]->setSpanDim(d_depth, d_weightTable[index]);
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

		for(Frame* frame : d_contents)
			frame->nextFrame(tick, delta);

		// adjustDepth();
	}

	void Stripe::deepRelayout()
	{
		this->markRelayout();

		for(Frame* frame : d_contents)
			if(frame->container())
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

	void Stripe::flowChanged(Frame* child)
	{
		UNUSED(child);
		this->updateDepth();
		this->updateLength();
		d_relayout = true;
	}

	void Stripe::flowChanged(Frame* child, Dimension dim)
	{
		if(dim == d_depth)
			this->updateDepth();
		else
			this->updateLength();

		if(dim == d_length)
		{
			d_relayout = true;
		}
		else
		{
			//d_relayout = true;
			d_maxDepth = std::max(d_maxDepth, child->doffset(d_depth));
		}
	}

	void Stripe::resized(Dimension dim)
	{
		UNUSED(dim);
		d_relayout = true;
	}

	Frame* Stripe::pinpoint(float x, float y, bool opaque)
	{
		Frame* target;
		for(Frame* frame : reverse_adapt(d_contents))
			if(!frame->hidden() && frame->inside(x, y))
			{
				target = frame->pinpoint(x, y, opaque);
				if(target)
					return target;
			}

		return Frame::pinpoint(x, y, opaque);
	}
}
