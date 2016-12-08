//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <Ui/mkUiConfig.h>
#include <Ui/Frame/mkLayer.h>

#include <Object/Iterable/mkReverse.h>

#include <Ui/Widget/mkWidget.h>

#include <iostream>
#include <algorithm>

namespace mk
{
	Layer::Layer(Widget& widget, int zorder)
		: Stripe(widget)
		, d_index(0)
		, d_z(zorder)
		, d_numLayers(0)
		, d_parentLayer(nullptr)
		, d_redraw(true)
		, d_redrawNext(true)
	{}

	Layer::~Layer()
	{
		if(d_parentLayer)
			this->unbind();
	}

	MasterLayer& Layer::rootLayer()
	{
		Layer* layer = this;
		while(layer->d_parentLayer)
			layer = layer->d_parentLayer;
		return layer->as<MasterLayer>();
	}


	void Layer::bind()
	{
		this->updateStyle();
	}

	void Layer::bind(Stripe* parent)
	{
		d_parentLayer = &parent->layer();
		d_parentLayer->add(*this);

		MasterLayer& rootLayer = this->rootLayer();
		rootLayer.add(*this);

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


	void Layer::updateOnce()
	{
		Stripe::updateOnce();

		if(d_redrawNext)
		{
			d_redraw = true;
			d_redrawNext = false;
		}
		else
		{
			d_redraw = false;
		}
	}

	void Layer::add(Layer& layer)
	{
		d_sublayers.insert(d_sublayers.begin() + d_numLayers, &layer);

		if(layer.z() == 0)
		{
			++d_numLayers;
			this->rootLayer().reorder();
		}
	}

	void Layer::remove(Layer& layer)
	{
		d_sublayers.erase(std::remove(d_sublayers.begin(), d_sublayers.end(), &layer), d_sublayers.end());

		if(layer.z() == 0)
			--d_numLayers;
	}

	size_t Layer::reorder(size_t pos, size_t cursor, size_t next)
	{
		d_index = cursor;

#if 0 // DEBUG
		Layer* parent = d_parentLayer;
		while(parent)
		{
			printf("  ");
			parent = parent->d_parentLayer;
		}

		printf("Layer :: %s reorder index %u\n", d_widget.style().name().c_str(), d_index);
#endif

		cursor = next;
		next = next + d_numLayers;

		size_t i = 0;
		for(; i < d_numLayers; ++i)
		{
			next = d_sublayers[i]->reorder(i, cursor, next);
			cursor += 1;
		}

		for(; i < d_sublayers.size(); ++i)
		{
			d_sublayers[i]->d_index = i;
		}

		return next;
	}

	void Layer::moveToTop()
	{
		if(!d_parentLayer)
			return;

		/*Stripe* parent = d_parent;
		d_parent->remove(*this);
		parent->append(*this);*/

		d_parentLayer->remove(*this);
		d_parentLayer->add(*this);
	}

	Frame* Layer::pinpoint(float x, float y, bool opaque)
	{
		/*
		This is apparently useless since the order of the layers should be the same as the order of the contents of the stripe
		and Stripe contains the exact same code
		*/
		Frame* result = nullptr;
		for(Layer* layer : reverse_adapt(d_sublayers))
			if(layer->visible() && layer->frameType() != LAYER3D)
			{
				result = layer->pinpoint(x, y, opaque);
				if(result)
					return result;
			}
		

		result = Stripe::pinpoint(x, y, opaque);
		return result;
	}

	MasterLayer::MasterLayer(Widget& widget)
		: Layer(widget, 0)
	{}

	void MasterLayer::add(Layer& layer)
	{
		d_layers.push_back(&layer);
	}

	void MasterLayer::remove(Layer& layer)
	{

	}

	void MasterLayer::reorder()
	{
		Layer::reorder(0, d_index, 1);

		auto goesBefore = [](Layer* a, Layer* b) { return a->index() < b->index(); };
		std::sort(d_layers.begin(), d_layers.end(), goesBefore);
	}

	Layer3D::Layer3D(Widget& widget, size_t zorder)
		: Layer(widget, zorder)
	{}
}
