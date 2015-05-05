//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Frame/mkStripe.h>

#include <Object/Iterable/mkReverse.h>

#include <Ui/Frame/mkInk.h>

#include <Ui/Widget/mkWidget.h>
#include <Ui/Form/mkForm.h>

#include <algorithm>
#include <iostream>

namespace mk
{
	Stripe::Stripe(Widget& widget)
		: Frame(widget)
		, d_cursor(0.f)
		, d_contents()
		, d_sequence(d_contents)
		, d_sequenceLength(0)
		, d_freeSpace(0)
		, d_floatDepth(0)
		, d_maxDepth(0)
		, d_forceDirty(CLEAN)
		, d_weights()
	{
		this->setDirty(DIRTY_FLOW);
	}

	Stripe::~Stripe()
	{}

	void Stripe::append(Frame& frame)
	{
		this->insert(frame, frame.flow() ? d_sequence.size() : d_contents.size());
	}

	void Stripe::insert(Frame& frame, size_t index)
	{
		frame.bind(this);

		if(frame.flow())
			index = std::min(d_sequence.size(), index);
		else
			index = std::max(d_sequence.size(), index);

		d_contents.insert(d_contents.begin() + index, &frame);
		this->reindex(index);
		if(frame.flow())
			++d_sequence.size();

		if(!frame.hidden())
			this->childShown(frame);
	}

	void Stripe::remove(Frame& frame)
	{
		frame.unbind();

		d_contents.erase(d_contents.begin() + frame.index());
		this->reindex(frame.index());
		if(frame.flow())
			--d_sequence.size();

		if(!frame.hidden())
			this->childHidden(frame);
	}

	void Stripe::clear()
	{
		d_sequence.size() = 0;
		d_contents.clear();
		this->setDirty(DIRTY_FLOW);
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
				d_sequenceLength += this->extentSequence(*frame);

		this->updateLength();
	}

	void Stripe::recomputeDepth()
	{
		d_maxDepth = 0.f;

		for(Frame* frame : d_sequence)
			if(!frame->dexpand(d_depth) && !frame->hidden())
				d_maxDepth = std::max(d_maxDepth, frame->dextent(d_depth));

		this->updateDepth();
	}

	void Stripe::updateSize()
	{
		Frame::updateSize();
	}

	void Stripe::updateLength()
	{
		if(dshrink(d_length))// || dwrap(d_length))
			this->setSizeDim(d_length, d_sequenceLength + d_layout->padding()[d_length] + d_layout->padding()[d_length+2]);
	}

	void Stripe::updateDepth()
	{
		if(dshrink(d_depth)) // || dwrap(d_depth))
			this->setSizeDim(d_depth, d_maxDepth + d_layout->padding()[d_depth] + d_layout->padding()[d_depth+2]);
	}

	void Stripe::expandDepth()
	{
		float space = dspace(d_depth);

		for(Frame* frame : d_contents)
			if(frame->dexpand(d_depth))
				frame->setSizeDim(d_depth, space);
	}

	void Stripe::expandLength()
	{
		float space = dspace(d_length) - d_sequenceLength;
		d_freeSpace = space;

		for(Frame* frame : d_contents)
			if(frame->dexpand(d_length))
			{
				if(frame->flow())
					frame->setSizeDim(d_length, space * frame->dspan(d_length));
				else
					frame->setSizeDim(d_length, dspace(d_length));
				d_freeSpace = 0.f;
			}
	}

	void Stripe::relayout()
	{
		this->normalizeSpan();

		if(d_layout->d_weight == LIST && d_weights && d_weights->size() > 0)
			this->dispatchWeights();
		else if(d_layout->d_weight == TABLE)
			this->dispatchTableWeights();

		this->expandDepth();
		this->expandLength();

#if 0 // DEBUG
			Stripe* parent = d_parent;
			while(parent)
			{
				printf("  ");
				parent = parent->parent();
			}

			printf("Stripe :: relayout %s size %f , %f\n", d_widget.style().name().c_str(), dsize(DIM_X), dsize(DIM_Y));
#endif
	}

	void Stripe::positionLength(Frame& frame)
	{
		if(frame.flow())
			frame.setPositionDim(d_length, this->offsetSequence(frame));
		else
			frame.setPositionDim(d_length, this->offset(frame, d_length));
	}

	void Stripe::positionDepth(Frame& frame)
	{
		frame.setPositionDim(d_depth, this->offset(frame, d_depth));
	}

	void Stripe::initWeights()
	{
		d_weights = make_unique<std::vector<float>>();
		if(d_layout)
			*d_weights = d_layout->d_weights;
	}

	void Stripe::dispatchWeights()
	{
		if(d_contents.size() < d_weights->size())
			return;

		for(size_t index = 0; index != d_weights->size(); ++index)
			if((*d_weights)[index] >= 0.f)
				d_contents[index]->setSpanDim(d_length, (*d_weights)[index]);

		d_weights->clear();
	}

	void Stripe::dispatchTableWeights()
	{
		for(size_t index = 0; index != d_weights->size(); ++index)
			for(Frame* frame : d_sequence)
				if(frame->as<Stripe>().sequence().size() == d_weights->size())
					frame->as<Stripe>().contents()[index]->setSpanDim(d_depth, (*d_weights)[index]);
	}

	void Stripe::updateOnce()
	{
		this->clearForceDirty();

		if(d_parent)
			this->setForceDirty(d_parent->d_forceDirty);

		switch(d_dirty)
		{
		case DIRTY_FLOW:
			this->relayout();
		case DIRTY_OFFSET:
			this->setForceDirty(DIRTY_POSITION);
		case DIRTY_ABSOLUTE:
			this->setForceDirty(DIRTY_ABSOLUTE);
		}

		Frame::updateOnce();
	}

	void Stripe::updateSpace()
	{
		if(!d_parent)
			d_space = BOARD;
		else if(!flow())
			d_space = BLOCK;
		else if(d_length == d_parent->d_length && d_length == DIM_X) // @idea : make this distinction depend on a space Scarcity property (which by default would be Scarce for Y containers and Ample for X containers)
			d_space = SPACE;
		else if(d_length != d_parent->d_length && d_parent->d_length == DIM_X)
			d_space = DIV;
		else
			d_space = DIV;
	}

	void Stripe::updateStyle()
	{
		Frame::updateStyle();

		if(d_layout->weights().size() > 0)
			this->initWeights();
	}

	void Stripe::updateSizing()
	{
		d_length = d_layout->d_layoutDim;
		d_depth = d_layout->d_layoutDim == DIM_X ? DIM_Y : DIM_X;

		Frame::updateSizing();
	}

	void Stripe::setVisible(bool visible)
	{
		Frame::setVisible(visible);

		for(Frame* frame : d_contents)
			frame->setVisible(visible);
	}

	void Stripe::migrate(Stripe& stripe)
	{
		Frame::migrate(stripe);
		
		for(Frame* frame : d_contents)
			if(frame->frameType() < LAYER)
				frame->migrate(stripe);
	}

	void Stripe::childShown(Frame& child)
	{
		this->childSizedLength(child, child.dextent(d_length));
		this->childSizedDepth(child, child.dextent(d_depth));

		if(child.flow())
			this->setDirty(DIRTY_FLOW);

		if(child.flow() && d_sequence.size() != 1)
			d_sequenceLength += d_layout->spacing()[d_length];
	}

	void Stripe::childHidden(Frame& child)
	{
		this->childSizedLength(child, -child.dextent(d_length));
		this->childSizedDepth(child, -child.dextent(d_depth));

		if(child.flow())
			this->setDirty(DIRTY_FLOW);

		if(child.flow() && d_sequence.size() != 0)
			d_sequenceLength -= d_layout->spacing()[d_length];
	}

	void Stripe::childSized(Frame& child, Dimension dim, float delta)
	{
		if(child.hidden() || child.dexpand(dim))
			return;

		if(dim == d_length)
			this->childSizedLength(child, delta);
		else
			this->childSizedDepth(child, delta);
	}

	void Stripe::childSizedLength(Frame& child, float delta)
	{
		if(!(child.flow() || child.floats()) || child.layout()->d_flow == FLOAT_DEPTH || child.dexpand(d_length))
			return;

		d_sequenceLength += delta;
		this->updateLength();
		this->setDirty(DIRTY_FLOW);
	}

	void Stripe::childSizedDepth(Frame& child, float delta)
	{
		if(child.flow() || child.layout()->d_flow == FREE_FILL)
			this->flowSizedDepth(child, delta);
		else if(child.layout()->d_flow == FLOAT_DEPTH)
			this->floatSizedDepth(child, delta);
	}

	void Stripe::flowSizedDepth(Frame& child, float delta)
	{
		if(delta < 0.f)
		{
			this->recomputeDepth();
		}
		else if(delta > 0.f)
		{
			d_maxDepth = std::max(d_maxDepth, child.dextent(d_depth));
			this->updateDepth();
		}
	}

	void Stripe::floatSizedDepth(Frame& child, float delta)
	{
		UNUSED(child);
		d_floatDepth += delta;
		this->setDirty(DIRTY_FLOW);
	}

	void Stripe::resized(Dimension dim)
	{
		UNUSED(dim);
		if(dim == d_length)
			this->expandLength();
		else
			this->expandDepth();
		this->setDirty(DIRTY_FLOW);
	}

	Frame* Stripe::pinpoint(float x, float y, bool opaque)
	{
		if(!this->inside(x, y))
			return nullptr;

		Frame* target;
		for(Frame* frame : reverse_adapt(d_contents))
			if(frame->visible() && frame->frameType() != LAYER3D)
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

	bool Stripe::nextOffset(Dimension dim, float& pos, float seuil, bool top)
	{
		if(d_length != dim)
			return Frame::nextOffset(dim, pos, seuil);

		pos += d_parent->extentSequence(*this);

		if(pos < seuil && !top)
			return false;

		pos -= d_parent->extentSequence(*this);
		for(Frame* frame : d_sequence)
			if(frame->nextOffset(dim, pos, seuil))
				return true;

		pos -= d_parent->extentSequence(*this);
		return Frame::nextOffset(dim, pos, seuil);
	}

	bool Stripe::prevOffset(Dimension dim, float& pos, float seuil, bool top)
	{
		if(d_length != dim)
			return Frame::prevOffset(dim, pos, seuil);

		if(top || pos + d_parent->extentSequence(*this) >= seuil)
			for(Frame* frame : d_sequence)
				if(frame->prevOffset(dim, pos, seuil))
					return true;

		return Frame::prevOffset(dim, pos, seuil);
	}

	void Stripe::cursorUp()
	{
		float pos = 0.f;
		this->prevOffset(d_length, pos, d_cursor, true);
		d_cursor = std::max(0.f, pos);
		this->setDirty(DIRTY_FLOW);
	}

	void Stripe::cursorDown()
	{
		float pos = 0.f;
		this->nextOffset(d_length, pos, d_cursor, true);
		d_cursor = std::min(d_sequenceLength - d_clipSize[DIM_Y], pos);
		this->setDirty(DIRTY_FLOW);
	}
}
