//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_LAYER_H_INCLUDED
#define MK_LAYER_H_INCLUDED

/* mk headers */
#include <Ui/Frame/mkStripe.h>

namespace mk
{
	class MK_UI_EXPORT Layer : public Stripe
	{
	public:
		Layer(Stripe* parent, Widget* widget, size_t index, size_t zorder = 0);
		~Layer();

		InkLayer* inkLayer() { return d_inkLayer.get(); }
		std::vector<Layer*>& layers() { return d_layers; }

		void nextFrame(size_t tick, size_t delta);

		void moveToTop();

		Frame* pinpoint(float x, float y, bool opaque);

	protected:
		unique_ptr<InkLayer> d_inkLayer;
		std::vector<Layer*> d_layers;
	};
}


#endif // MK_LAYER_H_INCLUDED
