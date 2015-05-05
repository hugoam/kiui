//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_LAYER_H_INCLUDED
#define MK_LAYER_H_INCLUDED

/* mk headers */
#include <Ui/Frame/mkStripe.h>
#include <Ui/Frame/mkInk.h>

namespace mk
{
	class MK_UI_EXPORT Layer : public Stripe
	{
	public:
		Layer(Widget& widget, size_t zorder = 0, InkTarget* target = nullptr);
		~Layer();

		FrameType frameType() { return LAYER; }

		size_t index() { return d_index; }
		size_t z() { return d_z; }

		InkLayer& inkLayer() { return *d_inkLayer.get(); }
		InkTarget* target() { return d_target; }
		std::vector<Layer*>& layers() { return d_layers; }

		Layer& rootLayer() { if(!d_parentLayer) return *this; Layer* root = d_parentLayer; while(root->d_parentLayer) root = root->d_parentLayer; return *root; }

		void bind();

		void bind(Stripe* parent);
		void unbind();

		void nextFrame(size_t tick, size_t delta);

		void add(Layer& layer);
		void remove(Layer& layer);

		void reorder();
		size_t reorder(size_t index, size_t next);
		void moveToTop();

		Frame* pinpoint(float x, float y, bool opaque);

	protected:
		size_t d_index;
		size_t d_next;
		size_t d_z;
		size_t d_numLayers;
		InkTarget* d_target;
		Layer* d_parentLayer;
		std::vector<Layer*> d_layers;
		unique_ptr<InkLayer> d_inkLayer;
	};

	class MK_UI_EXPORT Layer3D : public Layer
	{
	public:
		Layer3D(Widget& widget, size_t zorder = 0, InkTarget* target = nullptr);

		FrameType frameType() { return LAYER3D; }
	};
}


#endif // MK_LAYER_H_INCLUDED
