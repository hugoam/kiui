//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_FRAME_H
#define TOY_FRAME_H

/* toy */
#include <toyobj/Typed.h>
#include <toyobj/String/String.h>
#include <toyobj/Util/Updatable.h>
#include <toyui/Forward.h>
#include <toyui/Frame/Uibox.h>
#include <toyui/Render/DrawFrame.h>

#include <cmath>

namespace toy
{
	class _I_ TOY_UI_EXPORT Frame : public Object, public Uibox
	{
	public:
		Frame(Widget& widget);
		Frame(StyleType& style, Stripe& parent);

		enum Dirty
		{
			CLEAN,				// Frame doesn't need update
			DIRTY_ABSOLUTE,		// The absolute position of the frame has changed
			DIRTY_POSITION,		// The relative position of the frame has changed
			DIRTY_CONTENT,		// The skin of the frame has changed
			DIRTY_LAYOUT,		// The content of the widget has changed
		};

		virtual FrameType frameType() { return FRAME; }

		inline Widget* widget() { return d_widget; }
		inline DrawFrame& content() { return d_frame; }
		inline Stripe* parent() { return d_parent; }
		inline Dirty dirty() { return d_dirty; }
		inline bool hidden() { return d_hidden; }
		inline const Index& index() { return d_index; }
		inline size_t dindex(Dimension dim) { return d_index[dim]; }

		inline Style& style() { return *d_style; }

		void setIndex(Dimension dim, size_t index) { d_index[dim] = index; }
		void setIndex(size_t xindex, size_t yindex) { d_index[DIM_X] = xindex; d_index[DIM_Y] = yindex; }

		inline float dspace(Dimension dim) { return d_size[dim] - dpadding(dim) - dbackpadding(dim); }

		Layer& layer();

		virtual void bind(Stripe& parent);
		virtual void unbind();

		void show();
		void hide();

		bool visible();

		void setDirty(Dirty dirty) { if(dirty > d_dirty) d_dirty = dirty; }
		void markDirty(Dirty dirty);

		virtual Frame* pinpoint(float x, float y, bool opaque);

		virtual void updateOnce();

		void updateSizing(Dimension dim);
		void updateFixed(Dimension dim);

		void updateSpace();
		void updateSizing();

		void setStyle(Style& style);

		virtual void measure();
		virtual void layout();

		void setSizeDim(Dimension dim, float size);
		void setSpanDim(Dimension dim, float span);
		void setSpanDimDirect(Dimension dim, float span) { d_span[dim] = span; }
		void setPositionDim(Dimension dim, float position);

		inline void setPosition(float x, float y) { setPositionDim(DIM_X, x); setPositionDim(DIM_Y, y); }
		inline void setSize(float width, float height) { setSizeDim(DIM_X, width); setSizeDim(DIM_Y, height); }
		inline void setSize(DimFloat dim) { setSizeDim(DIM_X, dim[DIM_X]); setSizeDim(DIM_Y, dim[DIM_Y]); }

		float dabsolute(Dimension dim);
		float drelative(Dimension dim);

		bool inside(float x, float y);

		void debugPrintDepth();

		static Type& cls() { static Type ty; return ty; }

	protected:
		Widget* d_widget;
		DrawFrame d_frame;
		Stripe* d_parent;
		Dirty d_dirty;
		bool d_hidden;
		Index d_index;

		Style* d_style;
	};
}

#endif // TOY_WIDGET_H
