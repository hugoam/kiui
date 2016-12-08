//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_LAYER_H
#define MK_LAYER_H

/* mk headers */
#include <Ui/Frame/mkStripe.h>

namespace mk
{
	class MK_UI_EXPORT Layer : public Stripe
	{
	public:
		Layer(Widget& widget, int zorder = 0);
		~Layer();

		FrameType frameType() { return LAYER; }

		size_t index() { return d_index; }
		int z() { return d_z; }

		std::vector<Layer*>& sublayers() { return d_sublayers; }

		bool redraw() { return d_redraw; }
		void setRedraw() { d_redrawNext = true; }

		MasterLayer& rootLayer();

		void bind();

		void bind(Stripe* parent);
		void unbind();

		void add(Layer& layer);
		void remove(Layer& layer);

		size_t reorder(size_t pos, size_t index, size_t next);
		void moveToTop();

		virtual void updateOnce();

		Frame* pinpoint(float x, float y, bool opaque);

	protected:
		size_t d_index;
		int d_z;
		size_t d_numLayers;
		Layer* d_parentLayer;
		std::vector<Layer*> d_sublayers;

		bool d_redraw;
		bool d_redrawNext;
	};

	class MK_UI_EXPORT MasterLayer : public Layer
	{
	public:
		MasterLayer(Widget& widget);

		void add(Layer& layer);
		void remove(Layer& layer);

		const std::vector<Layer*>& layers() { return d_layers; }

		void reorder();

	protected:
		std::vector<Layer*> d_layers;
	};

	class MK_UI_EXPORT Layer3D : public Layer
	{
	public:
		Layer3D(Widget& widget, size_t zorder = 0);

		FrameType frameType() { return LAYER3D; }
	};
}


#endif // MK_LAYER_H
