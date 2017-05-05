//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_LAYER_H
#define TOY_LAYER_H

/* toy */
#include <toyui/Frame/Stripe.h>

namespace toy
{
	class TOY_UI_EXPORT Layer : public Stripe
	{
	public:
		Layer(Widget& widget);
		~Layer();

		enum Redraw
		{
			NO_REDRAW = 0,
			REDRAW = 1,
			FORCE_REDRAW = 2
		};

		FrameType frameType() { return LAYER; }

		Layer* parentLayer() { return d_parentLayer; }
		size_t index() { return d_index; }
		size_t z() { return d_style->layout().zorder() ? d_style->layout().zorder() : d_z; }

		void setIndex(size_t index) { d_index = index; }
		void setZ(size_t z) { d_z = z; }

		bool redraw() { return d_redraw >= REDRAW; }
		bool forceRedraw() { return d_redraw >= FORCE_REDRAW; }

		void setRedraw() { if(d_redraw < REDRAW) d_redraw = REDRAW; }
		void setForceRedraw() { d_redraw = FORCE_REDRAW; }

		void endRedraw() { d_redraw = NO_REDRAW; }

		void collectLayers(std::vector<Layer*>& layers, FrameType barrier = LAYER);

		void remap();
		void reindex(size_t from);

		void moveToTop(Layer& sublayer);
		void moveToTop();

		Frame* pinpoint(float x, float y, const Filter& filter);

	protected:
		Layer* d_parentLayer;
		size_t d_index;
		size_t d_z;

		Redraw d_redraw;

		std::vector<Layer*> d_sublayers;
	};

	class TOY_UI_EXPORT MasterLayer : public Layer
	{
	public:
		MasterLayer(Widget& widget);

		FrameType frameType() { return MASTER_LAYER; }

		const std::vector<Layer*>& layers() { return d_layers; }
		void markReorder() { d_reorder = true; }

		void relayout();
		void redraw();
		
		void reorder();
		void addLayer(Layer& layer);

	protected:
		std::vector<Layer*> d_layers;
		bool d_reorder;
	};

	class TOY_UI_EXPORT Layer3D : public MasterLayer
	{
	public:
		Layer3D(Widget& widget);

		FrameType frameType() { return SPACE_LAYER; }
	};
}


#endif // TOY_LAYER_H
