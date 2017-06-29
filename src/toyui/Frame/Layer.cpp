//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <toyui/Config.h>
#include <toyui/Frame/Layer.h>

#include <toyui/Widget/Sheet.h>
#include <toyobj/Iterable/Reverse.h>

namespace toy
{
	Layer::Layer(Wedge& wedge, FrameType layerType)
		: Frame(wedge)
		, d_parentLayer(nullptr)
		, d_index(-1)
		, d_z(0)
		, d_redraw(REDRAW)
		, d_layerType(layerType)
	{}

	Layer::~Layer()
	{
		if(d_parentLayer)
			d_parentLayer->removeLayer(*this);
	}

	void Layer::reindex(size_t from)
	{
		for(size_t i = from; i < d_sublayers.size(); ++i)
			d_sublayers[i]->setIndex(i);
	}

	void Layer::bind(Frame& parent)
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
		vector_remove(d_sublayers, &layer);
		this->reindex(index);
	}

	void Layer::moveToTop(Layer& sublayer)
	{
		size_t index = sublayer.index();
		d_sublayers.erase(d_sublayers.begin() + index);
		d_sublayers.push_back(&sublayer);
		this->reindex(index);
	}

	void Layer::moveToTop()
	{
		d_parent->layer().moveToTop(*this);
	}

	Frame* Layer::pinpoint(DimFloat pos, const Filter& filter)
	{
		if(!this->visible() || this->hollow() || (this->clip() && !this->inside(pos)))
			return nullptr;

		for(Layer* frame : reverse_adapt(d_sublayers))
		{
			DimFloat local = frame->integratePosition(pos, *this);
			Frame* target = frame->pinpoint(local, filter);
			if(target)
				return target;
		}

		return Frame::pinpoint(pos, filter);
	}

	void Layer::visit(const Visitor& visitor)
	{
		visitor(*this);

		for(Layer* layer : d_sublayers)
			layer->visit(visitor);
	}
}
