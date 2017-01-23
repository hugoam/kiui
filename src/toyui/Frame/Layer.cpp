//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <toyui/Config.h>
#include <toyui/Frame/Layer.h>

#include <toyobj/Iterable/Reverse.h>

#include <toyui/Widget/Widget.h>
#include <toyui/Frame/Renderer.h>

#include <toyui/UiWindow.h>

#include <iostream>
#include <algorithm>

namespace toy
{
	Layer::Layer(Widget& widget, int zorder)
		: Stripe(widget)
		, d_index(0)
		, d_z(zorder)
		, d_numLayers(0)
		, d_parentLayer(nullptr)
		, d_redraw(true)
	{}

	Layer::~Layer()
	{}

	MasterLayer& Layer::rootLayer()
	{
		Layer* layer = this;
		while(layer->frameType() < MASTER_LAYER)
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
		{
			--d_numLayers;
			this->rootLayer().reorder();
		}
	}

	size_t Layer::reorder(size_t pos, size_t cursor, size_t next, std::vector<Layer*>& layers)
	{
		/*if(this->frameType() >= MASTER_LAYER)
		{
			this->as<MasterLayer>().reorder();
			return next;
		}*/

		UNUSED(pos);

		d_index = cursor;
		layers.push_back(this);

		//cursor = next;
		cursor += 1;
		//next = next + d_numLayers;

		size_t i = 0;
		for(; i < d_sublayers.size(); ++i)
		{
			next = d_sublayers[i]->reorder(i, cursor, next, layers);
			cursor += 1;
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
		Frame* result = nullptr;
		for(Layer* layer : reverse_adapt(d_sublayers))
			if(layer->visible() && layer->frameType() < MASTER_LAYER)
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
		, d_target(widget.uiWindow().renderer().createRenderTarget(*this))
	{}

	void MasterLayer::reorder()
	{
		d_layers.clear();
		Layer::reorder(0, d_index, 1, d_layers);

		auto goesBefore = [](Layer* a, Layer* b) { return a->index() < b->index(); };
		std::sort(d_layers.begin(), d_layers.end(), goesBefore);

#if 0 // DEBUG
		for(Layer* layer: d_layers)
		{
			Layer* parent = layer->parentLayer();
			while(parent)
			{
				printf("  ");
				parent = parent->parentLayer();
			}

			printf("Layer :: %s reorder index %u\n", layer->widget().style().name().c_str(), layer->index());
		}
#endif
	}

	Layer3D::Layer3D(Widget& widget)
		: MasterLayer(widget)
	{}
}
