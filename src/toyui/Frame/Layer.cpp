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

	void Layer::reindex()
	{
		for(size_t i = 0; i < d_sublayers.size(); ++i)
			d_sublayers[i]->d_index = i;
	}

	void Layer::reorder()
	{
		std::sort(d_sublayers.begin(), d_sublayers.end(), [](Layer* first, Layer* second) { if(first->z() < second->z()) return true; else if(first->z() > second->z()) return false; return first->d_index < second->d_index; });
		this->reindex();
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
		layer.d_index = d_sublayers.size();
		d_sublayers.push_back(&layer);
		this->reorder();
	}

	void Layer::removeLayer(Layer& layer)
	{
		vector_remove(d_sublayers, &layer);
		this->reindex();
		this->reorder();
	}

	void Layer::moveToTop()
	{
		d_parentLayer->removeLayer(*this);
		d_parentLayer->addLayer(*this);
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
