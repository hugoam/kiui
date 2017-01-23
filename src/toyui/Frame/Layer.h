//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_LAYER_H
#define TOY_LAYER_H

/* toy headers */
#include <toyui/Frame/Stripe.h>

namespace toy
{
	class TOY_UI_EXPORT Layer : public Stripe
	{
	public:
		Layer(Widget& widget, int zorder = 0);
		~Layer();

		FrameType frameType() { return LAYER; }

		size_t index() { return d_index; }
		int z() { return d_z; }
		Layer* parentLayer() { return d_parentLayer; }

		std::vector<Layer*>& sublayers() { return d_sublayers; }

		bool redraw() { return d_redraw; }
		void setRedraw() { d_redraw = true; }

		MasterLayer& rootLayer();

		void bind();

		void bind(Stripe* parent);
		void unbind();

		void add(Layer& layer);
		void remove(Layer& layer);

		size_t reorder(size_t pos, size_t index, size_t next, std::vector<Layer*>& layers);
		void moveToTop();

		Frame* pinpoint(float x, float y, bool opaque);

	protected:
		size_t d_index;
		int d_z;
		size_t d_numLayers;
		Layer* d_parentLayer;
		std::vector<Layer*> d_sublayers;

		bool d_redraw;
	};

	class TOY_UI_EXPORT MasterLayer : public Layer
	{
	public:
		MasterLayer(Widget& widget);

		FrameType frameType() { return MASTER_LAYER; }

		RenderTarget& target() { return *d_target; }
		const std::vector<Layer*>& layers() { return d_layers; }

		void reorder();

	protected:
		std::vector<Layer*> d_layers;
		unique_ptr<RenderTarget> d_target;
	};

	class TOY_UI_EXPORT Layer3D : public MasterLayer
	{
	public:
		Layer3D(Widget& widget);

		FrameType frameType() { return SPACE_LAYER; }
	};
}


#endif // TOY_LAYER_H
