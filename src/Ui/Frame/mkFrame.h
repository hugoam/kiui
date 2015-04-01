//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_FRAME_H_INCLUDED
#define MK_FRAME_H_INCLUDED

/* mk */
#include <Object/mkTyped.h>
#include <Object/String/mkString.h>
#include <Object/Util/mkUpdatable.h>
#include <Ui/mkUiForward.h>
#include <Ui/Frame/mkUibox.h>

namespace mk
{
	class MK_UI_EXPORT _I_ Frame : public Object, public Typed<Frame>, public Uibox, public Updatable
	{
	public:
		Frame(Widget* widget);
		~Frame();

		enum Dirty
		{
			CLEAN,				// Frame doesn't need update
			DIRTY_FRAME,		// The size of the frame has changed
			DIRTY_CONTENT,		// The content of the inkbox has changed
			DIRTY_WIDGET,		// The content of the widget has changed
			DIRTY_SKIN,			// The skin of the frame has changed
			//DIRTY_FLOW,		// The flow of the frame has changed
			DIRTY_VISIBLE,		// The visibility of the frame has changed
			DIRTY_HIDE			// The visibility of the frame has changed
		};

		virtual FrameType frameType() { return FRAME; }

		inline Widget* widget() { return d_widget; }
		inline Stripe* parent() { return d_parent; }
		inline Dirty dirty() { return d_dirty; }
		inline bool hidden() { return d_hidden; }
		inline bool visible() { return d_visible; }
		inline size_t index() { return d_index; }

		inline Inkbox* inkbox() { return d_inkbox.get(); }
		inline Style* wstyle() { return d_wstyle; }
		inline InkStyle* inkstyle() { return d_inkstyle; }

		void setIndex(size_t index) { d_index = index; }
		void setDirty(Dirty dirty) { if(dirty > d_dirty) d_dirty = dirty; }

		Layer* layer();

		virtual void bind(Stripe* parent);
		virtual void unbind();

		void show();
		void hide();

		void setVisible();
		void setInvisible();

		//void moveToTop();

		void transfer(Stripe* stripe, size_t index);
		void remove();

		Frame* prev();
		Frame* next();

		void clip();

		void wrap(Dimension dim);

		virtual void setVisible(bool visible);

		virtual void markDirty(Dirty dirty);

		virtual Frame* pinpoint(float x, float y, bool opaque);

		virtual void migrate(Stripe* stripe);

		virtual void nextFrame(size_t tick, size_t delta);

		void reset(Style* style);

		void updatePosition();
		void updateSize();

		void updateState(WidgetState state);

		float calcAbsolute(Dimension dim);

		enum Clip
		{
			VISIBLE,
			CLIPPED,
			HIDDEN
		};

		Clip dclip(Dimension dim) { if(dclipsize(dim) <= 0.f) return HIDDEN; else if(dclipsize(dim) < dsize(dim)) return CLIPPED; else return VISIBLE; }

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

		inline float dabsolute(Dimension dim) { return d_absolute[dim]; }
		inline float dclippos(Dimension dim) { return d_clipPos[dim]; }
		inline float dclipsize(Dimension dim) { return d_clipSize[dim]; }

		bool inside(float x, float y);

	public:
		virtual void resized(Dimension dim) { UNUSED(dim); }

	protected:
		Widget* d_widget;
		Stripe* d_parent;
		Dirty d_dirty;
		bool d_hidden;
		bool d_visible;
		DimFloat d_absolute;
		DimFloat d_clipPos;
		DimFloat d_clipSize;
		size_t d_index;

		Style* d_wstyle;
		InkStyle* d_inkstyle;

		unique_ptr<Inkbox> d_inkbox;
	};

	class MK_UI_EXPORT FrameSkin
	{
	public:
		FrameSkin(Frame* frame, ImageSkin* skin);

		Frame* d_frame;
		ImageSkin* d_skin;

		std::vector<BoxFloat> mRects;

		float d_left;
		float d_top;

		float d_inleft;
		float d_intop;
		float d_inright;
		float d_inbottom;

		float d_inwidth;
		float d_inheight;

		float d_outtop;
		float d_outleft;
	};
}

#endif // MK_WIDGET_H_INCLUDED
