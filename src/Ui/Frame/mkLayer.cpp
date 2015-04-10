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
	Layer::Layer(Widget* widget, size_t zorder, InkTarget* target)
		: Stripe(widget)
		, d_zorder(zorder)
		, d_target(target)
		, d_parentLayer(nullptr)
	{}

	Layer::~Layer()
	{
		// d_inkbox.reset(); // destroy the inkbox before the layer // already handled in unbind()

		if(d_parentLayer)
			this->unbind();
	}

	void Layer::bind()
	{
		this->updateStyle(d_widget->style());
		d_inkLayer = d_target->layer(this, d_zorder);
		d_inkbox = d_inkLayer->inkbox(this);
	}

	void Layer::bind(Stripe* parent)
	{
		d_parentLayer = parent->layer();
		d_parentLayer->layers().push_back(this);

		bool migrate = bool(d_inkLayer);

		if(d_target)
			d_inkLayer = d_target->layer(this, d_zorder);
		else
			d_inkLayer = d_parentLayer->inkLayer()->target()->layer(this, d_zorder);

		if(migrate)
			this->migrate(this);

		Frame::bind(parent);
	}

	void Layer::unbind()
	{
		Frame::unbind();
		d_parentLayer->layers().erase(std::remove(d_parentLayer->layers().begin(), d_parentLayer->layers().end(), this), d_parentLayer->layers().end());
		d_parentLayer = nullptr;
	}

	void Layer::nextFrame(size_t tick, size_t delta)
	{
		if(d_dirty >= DIRTY_VISIBILITY)
			d_visible ? d_inkLayer->show() : d_inkLayer->hide();

		Stripe::nextFrame(tick, delta);
	}

	void Layer::moveToTop()
	{
		/*if(d_parent)
		{
			d_parent->layer()->layers().erase(std::remove(d_parent->layer()->layers().begin(), d_parent->layer()->layers().end(), this), d_parent->layer()->layers().end());
			d_parent->layer()->layers().push_back(this);
			d_parent->layer()->moveToTop();
		}*/

		d_inkLayer->moveToTop();
	}

	Frame* Layer::pinpoint(float x, float y, bool opaque)
	{
		Frame* result = nullptr;
		for(Layer* layer : reverse_adapt(d_layers))
			if(layer->visible())
			{
				result = layer->pinpoint(x, y, opaque);
				if(result)
					return result;
			}

		result = Stripe::pinpoint(x, y, opaque);
		return result;
	}
}
