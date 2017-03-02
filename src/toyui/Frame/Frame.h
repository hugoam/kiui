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
		Frame(Style& style, Stripe& parent);

		enum Dirty
		{
			CLEAN,				// Frame doesn't need update
			DIRTY_ABSOLUTE,		// The absolute position of the frame has changed
			DIRTY_POSITION,		// The relative position of the frame has changed
			DIRTY_CONTENT,		// The content of the widget has changed
			DIRTY_LAYOUT,		// The skin of the frame has changed
			DIRTY_STRUCTURE,
			DIRTY_MAPPING		// The widget needs to be remapped
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
		MasterLayer& masterlayer();

		void bind(Stripe& parent);
		void unbind();

		typedef std::function<bool(Frame&)> Visitor;

		virtual void visit(Stripe& root, const Visitor& visitor);

		void show();
		void hide();

		bool visible();

		void clearDirty() { d_dirty = CLEAN; }
		void setDirty(Dirty dirty) { if(dirty > d_dirty) d_dirty = dirty; }
		void markDirty(Dirty dirty);

		virtual Frame* pinpoint(float x, float y, bool opaque);

		void updateFixed(Dimension dim);
		void setFixedSize(Dimension dim, float size);

		void updateLayout();

		void applySpace(Direction direction, Sizing length, Sizing depth);

		void setStyle(Style& style, bool reset = false);
		void updateStyle();
		void resetStyle();

		virtual void remap();

		virtual void measureLayout();
		virtual void resizeLayout();
		virtual void positionLayout();

		void setSizeDim(Dimension dim, float size);
		void setSpanDim(Dimension dim, float span);
		void setSpanDimDirect(Dimension dim, float span) { d_span[dim] = span; }
		void setPositionDim(Dimension dim, float position);

		inline void setPosition(float x, float y) { setPositionDim(DIM_X, x); setPositionDim(DIM_Y, y); }
		inline void setSize(float width, float height) { setSizeDim(DIM_X, width); setSizeDim(DIM_Y, height); }
		inline void setSize(DimFloat dim) { setSizeDim(DIM_X, dim[DIM_X]); setSizeDim(DIM_Y, dim[DIM_Y]); }

		void integratePosition(Frame& root, DimFloat& local);
		void derivePosition(Frame& root, DimFloat& local);
		float deriveScale(Frame& root);

		DimFloat absolutePosition();
		float absoluteScale();

		DimFloat relativePosition(Frame& root);
		DimFloat localPosition(float x, float y);

		float doffset(Dimension dim);

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
	};
}

#endif // TOY_WIDGET_H
