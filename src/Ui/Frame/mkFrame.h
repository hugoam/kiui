//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_FRAME_H
#define MK_FRAME_H

/* mk */
#include <Object/mkTyped.h>
#include <Object/String/mkString.h>
#include <Object/Util/mkUpdatable.h>
#include <Ui/mkUiForward.h>
#include <Ui/Frame/mkUibox.h>
#include <Ui/Frame/mkDrawFrame.h>

#include <cmath>

namespace mk
{
	class MK_UI_EXPORT _I_ Frame : public Object, public Uibox, public DrawFrame, public Updatable
	{
	public:
		Frame(Widget& widget);
		~Frame();

		enum Dirty
		{
			CLEAN,				// Frame doesn't need update
			DIRTY_ABSOLUTE,		// The absolute position of the frame has changed
			DIRTY_CLIP,			// The clipping of the frame has changed
			DIRTY_POSITION,		// The relative position of the frame has changed
			DIRTY_OFFSET,		// The offset of the contents has changed
			DIRTY_FLOW,			// The flow of the contents has changed
			DIRTY_FRAME,		// The size of the frame has changed
			DIRTY_SKIN,			// The skin of the frame has changed
			DIRTY_WIDGET,		// The content of the widget has changed
			DIRTY_VISIBILITY,	// The visibility of the frame has changed
		};

		virtual FrameType frameType() { return FRAME; }

		inline Widget& widget() { return d_widget; }
		inline Stripe* parent() { return d_parent; }
		inline Dirty dirty() { return d_dirty; }
		inline bool hidden() { return d_hidden; }
		inline bool visible() { return d_visible; }
		inline size_t index() { return d_index; }
		inline bool flow() { return d_flow; }

		inline Style& style() { return *d_style; }

		void setIndex(size_t index) { d_index = index; }
		void setDirty(Dirty dirty) { if(dirty > d_dirty) d_dirty = dirty; }
		void clearDirty() { d_dirty = CLEAN; }

		Layer& layer();

		virtual void bind(Stripe* parent);
		virtual void unbind();

		void show();
		void hide();

		void setVisible();
		void setInvisible();

		void transfer(Stripe& stripe, size_t index);
		void remove();

		Frame* before();

		Frame& prev();
		Frame& next();

		bool first();
		bool last();

		virtual bool nextOffset(Dimension dim, float& pos, float seuil, bool top = false);
		virtual bool prevOffset(Dimension dim, float& pos, float seuil, bool top = false);

		virtual void setVisible(bool visible);

		virtual Frame* pinpoint(float x, float y, bool opaque);

		virtual void migrate(Stripe& stripe);

		virtual void nextFrame(size_t tick, size_t delta);

		void resetStyle();

		virtual void updateOnce();

		void updateSizing(Dimension dim);
		void updateFixed(Dimension dim);

		virtual void updateChildren() {}

		virtual void updateSpace();
		virtual void updateSizing();
		virtual void updateStyle();

		void updatePosition();
		void derivePosition();

		void updateState(WidgetState state);

		float calcAbsolute(Dimension dim);

		void setSizeDim(Dimension dim, float size);
		void setSpanDim(Dimension dim, float span);
		void setSpanDimDirect(Dimension dim, float span) { d_span[dim] = span; }
		void setPositionDim(Dimension dim, float position);

		inline void setPosition(float x, float y) { setPositionDim(DIM_X, x); setPositionDim(DIM_Y, y); }
		inline void setSize(float width, float height) { setSizeDim(DIM_X, width); setSizeDim(DIM_Y, height); }
		inline void setSize(DimFloat dim) { setSizeDim(DIM_X, dim[DIM_X]); setSizeDim(DIM_Y, dim[DIM_Y]); }

		inline float left() { return dabsolute(DIM_X); }
		inline float right() { return dabsolute(DIM_X) + dsize(DIM_X); }

		inline float top() { return dabsolute(DIM_Y); }
		inline float bottom() { return dabsolute(DIM_Y) + dsize(DIM_Y); }

		inline float width() { return dsize(DIM_X); }
		inline float height() { return dsize(DIM_Y); }

		inline float dextent(Dimension dim) { return dsize(dim) + dmargin(dim) * 2.f; }
		inline float doffset(Dimension dim) { return dposition(dim) + dextent(dim); }

		inline float dabsolute(Dimension dim) { return d_absolute[dim]; }

		bool inside(float x, float y);

		static Type& cls() { static Type ty; return ty; }

	public:
		virtual void resized(Dimension dim) { UNUSED(dim); }

	protected:
		Widget& d_widget;
		Stripe* d_parent;
		Dirty d_dirty;
		bool d_hidden;
		bool d_visible;
		bool d_flow;
		DimFloat d_absolute;
		size_t d_index;

		Style* d_style;
		size_t d_styleStamp;
	};
}

#endif // MK_WIDGET_H
