//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <toyui/Config.h>
#include <toyui/Frame/Layer.h>

#include <toyobj/Iterable/Reverse.h>

#include <toyui/Widget/Widget.h>
#include <toyui/Render/Renderer.h>

#include <toyui/UiWindow.h>

#include <algorithm>

namespace toy
{
	Layer::Layer(Widget& widget)
		: Stripe(widget)
		, d_parentLayer(nullptr)
		, d_index(-1)
		, d_z(0)
		, d_redraw(REDRAW)
	{}

	Layer::~Layer()
	{
		if(d_parentLayer)
			d_parentLayer->removeLayer(*this);
	}

	void Layer::collectLayers(std::vector<Layer*>& layers, FrameType barrier)
	{
		layers.clear();

		this->rootvisit([&layers, barrier](Frame& frame) {
			if(frame.frameType() == LAYER)
				layers.push_back(&frame.as<Layer>());
			return frame.frameType() < barrier;
		});
	}

	void Layer::reindex(size_t from)
	{
		for(size_t i = from; i < d_sublayers.size(); ++i)
			d_sublayers[i]->setIndex(i);
	}

	void Layer::bind(Stripe& parent)
	{
		Frame::bind(parent);
		d_parentLayer = &parent.layer();
		d_parentLayer->addLayer(*this);
	}
	
	void Layer::unbind()
	{
		d_parentLayer->removeLayer(*this);
		d_parentLayer = nullptr;
		Frame::unbind();
	}

	void Layer::addLayer(Layer& layer)
	{
		layer.setIndex(d_sublayers.size());
		d_sublayers.push_back(&layer);
	}

	void Layer::removeLayer(Layer& layer)
	{
		size_t index = layer.index();
		d_sublayers.erase(std::remove(d_sublayers.begin(), d_sublayers.end(), &layer), d_sublayers.end());
		this->reindex(index);
	}

	void Layer::moveToTop(Layer& sublayer)
	{
		size_t index = sublayer.index();
		d_sublayers.erase(d_sublayers.begin() + index);
		d_sublayers.push_back(&sublayer);
		this->reindex(index);
		this->masterlayer().markReorder();
	}

	void Layer::moveToTop()
	{
		d_parent->layer().moveToTop(*this);
	}

	Frame* Layer::pinpoint(float x, float y, const Filter& filter)
	{
		if(!this->visible() || this->hollow() || (this->clip() && !this->inside(x, y)))
			return nullptr;

		for(Layer* frame : reverse_adapt(d_sublayers))
		{
			DimFloat local = frame->localPosition(x, y); // probably should be local to this
			Frame* target = frame->pinpoint(local.x(), local.y(), filter);
			if(target)
				return target;
		}

		return Stripe::pinpoint(x, y, filter);
	}

	MasterLayer::MasterLayer(Widget& widget)
		: Layer(widget)
	{}

	void MasterLayer::relayout()
	{
		if(d_dirty >= DIRTY_STRUCTURE || d_reorder)
			this->reorder();

		this->measureLayout();
		this->resizeLayout();
		this->positionLayout();
	}

	void MasterLayer::redraw()
	{
		this->visit([](Frame& frame) {
			bool dirty = frame.dirty();

			if(dirty)
				frame.layer().setForceRedraw();
			if(dirty && frame.widget())
				frame.widget()->dirtyLayout();

			frame.clearDirty();

			return true;
		});
	}

	void MasterLayer::reorder()
	{
		this->collectLayers(d_layers, MASTER_LAYER);

		for(Layer* layer : d_layers)
			layer->setZ(layer->parentLayer() ? layer->parentLayer()->z() + layer->index() : layer->index());

		auto goesBefore = [](Layer* a, Layer* b) { return a->z() < b->z(); };
		std::sort(d_layers.begin(), d_layers.end(), goesBefore);

		d_reorder = false;

#if 0 // DEBUG
		for(Layer* layer: d_layers)
		{
			layer->debugPrintDepth();
			printf("LAYOUT: Layer %s reorder z %u index %u\n", layer->style().name().c_str(), layer->z(), layer->index());
		}
#endif
	}

	Layer3D::Layer3D(Widget& widget)
		: MasterLayer(widget)
	{}
}
