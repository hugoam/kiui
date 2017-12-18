//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_LAYER_H
#define TOY_LAYER_H

/* toy */
#include <toyui/Frame/Frame.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT Layer : public Frame
	{
	public:
		Layer(Wedge& wedge, FrameType layerType);
		~Layer();

		enum Redraw
		{
			NO_REDRAW = 0,
			REDRAW = 1,
			FORCE_REDRAW = 2
		};

		virtual FrameType frameType() { return d_layerType; }

		size_t z() { return d_style->m_layout.m_zorder ? d_style->m_layout.m_zorder : d_z; }

		bool redraw() { return d_redraw >= REDRAW; }
		bool forceRedraw() { return d_redraw >= FORCE_REDRAW; }

		void setRedraw() { if(d_redraw < REDRAW) d_redraw = REDRAW; }
		void setForceRedraw() { d_redraw = FORCE_REDRAW; }

		void endRedraw() { d_redraw = NO_REDRAW; }

		virtual void bind(Frame& parent);
		virtual void unbind();

		void addLayer(Layer& layer);
		void removeLayer(Layer& layer);

		void moveToTop();

		void reindex();
		void reorder();

		using Visitor = std::function<void(Layer&)>;
		void visit(const Visitor& visitor);

		Frame* pinpoint(DimFloat pos, const Filter& filter);

	protected:
		Layer* d_parentLayer;
		size_t d_index;
		size_t d_z;

		Redraw d_redraw;

		std::vector<Layer*> d_sublayers;

		FrameType d_layerType;
	};
}


#endif // TOY_LAYER_H
