//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <Ui/mkUiConfig.h>
#include <Ui/Frame/mkLayer.h>

#include <Object/Iterable/mkReverse.h>

#include <Ui/Frame/mkInk.h>

#include <Ui/Widget/mkWidget.h>
#include <Ui/Form/mkForm.h>

#include <iostream>

namespace mk
{
	Layer::Layer(Widget& widget, size_t zorder, InkTarget* target)
		: Stripe(widget)
		, d_index(0)
		, d_next(1)
		, d_z(zorder)
		, d_numLayers(0)
		, d_target(target)
		, d_parentLayer(nullptr)
	{}

	Layer::~Layer()
	{
		if(d_parentLayer)
			this->unbind();
	}

	void Layer::bind()
	{
		this->updateStyle();
		d_inkLayer = d_target->createLayer(*this, d_index);
		d_inkbox = d_inkLayer->createInkbox(*this);
	}

	void Layer::bind(Stripe* parent)
	{
		d_parentLayer = &parent->layer();
		d_parentLayer->add(*this);

		bool migrate = bool(d_inkLayer);

		unique_ptr<InkLayer> oldLayer = std::move(d_inkLayer);

		if(d_target)
			d_inkLayer = d_target->createLayer(*this, d_z ? d_z : d_index);
		else
			d_inkLayer = d_parentLayer->inkLayer().target().createLayer(*this, d_z ? d_z : d_index);

		if(migrate)
			this->migrate(*this);

		Frame::bind(parent);
	}

	void Layer::unbind()
	{
		Frame::unbind();
		if(d_parentLayer)
		{
			d_parentLayer->remove(*this);
			d_parentLayer = nullptr;
		}
	}

	void Layer::add(Layer& layer)
	{
		d_layers.insert(d_layers.begin() + d_numLayers, &layer);

		if(layer.z() == 0)
		{
			++d_numLayers;
			this->rootLayer().reorder();
		}
	}

	void Layer::remove(Layer& layer)
	{
		d_layers.erase(std::remove(d_layers.begin(), d_layers.end(), &layer), d_layers.end());

		if(layer.z() == 0)
			--d_numLayers;
	}

	void Layer::reorder()
	{
		this->reorder(d_index, d_next);
	}

	size_t Layer::reorder(size_t cursor, size_t next)
	{
		d_index = cursor;
		d_next = next;

#if 0 // DEBUG
		Layer* parent = d_parentLayer;
		while(parent)
		{
			printf("  ");
			parent = parent->d_parentLayer;
		}

		printf("Layer :: reorder index %u\n", d_index);
#endif

		if(d_inkLayer)
			d_inkLayer->move(d_index);

		cursor = next;
		next = next + d_numLayers;

		for(size_t i = 0; i < d_numLayers; ++i)
		{
			next += d_layers[i]->reorder(cursor, next);
			cursor += 1;
		}

		return next - cursor;
	}

	void Layer::nextFrame(size_t tick, size_t delta)
	{
		if(d_dirty >= DIRTY_VISIBILITY)
			d_visible ? d_inkLayer->show() : d_inkLayer->hide();

		Stripe::nextFrame(tick, delta);
	}

	void Layer::moveToTop()
	{
		if(!d_parentLayer)
			return;

		d_parentLayer->remove(*this);
		d_parentLayer->add(*this);
	}

	Frame* Layer::pinpoint(float x, float y, bool opaque)
	{
		Frame* result = nullptr;
		for(Layer* layer : reverse_adapt(d_layers))
			if(layer->visible() && layer->frameType() != LAYER3D)
			{
				result = layer->pinpoint(x, y, opaque);
				if(result)
					return result;
			}

		result = Stripe::pinpoint(x, y, opaque);
		return result;
	}

	Layer3D::Layer3D(Widget& widget, size_t zorder, InkTarget* target)
		: Layer(widget, zorder, target)
	{}
}
