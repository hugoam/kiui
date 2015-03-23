//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <Ui/mkUiConfig.h>
#include <Ui/Frame/mkLayer.h>

#include <Object/Store/mkReverse.h>

#include <Ui/Frame/mkInk.h>

#include <Ui/Widget/mkWidget.h>
#include <Ui/Form/mkForm.h>

#include <iostream>

namespace mk
{
	Layer::Layer(Stripe* parent, Widget* widget, size_t index, size_t zorder)
		: Stripe(parent, widget, index)
		, d_inkLayer(widget->inkTarget()->layer(this, zorder))
	{
		d_inkbox = d_inkLayer->inkbox(this);

		if(parent)
			parent->layer()->layers().push_back(this);
	}

	Layer::~Layer()
	{
		d_inkbox.reset(); // destroy the inkbox before the layer

		if(d_parent)
			d_parent->layer()->layers().erase(std::remove(d_parent->layer()->layers().begin(), d_parent->layer()->layers().end(), this), d_parent->layer()->layers().end());
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
