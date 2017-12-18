//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_FRAME_H
#define TOY_FRAME_H

/* toy */
#include <toyobj/Type.h>
#include <toyui/Types.h>
#include <toyui/Frame/UiRect.h>
#include <toyui/Frame/Content.h>
#include <toyui/Frame/Caption.h>

#include <cmath>

namespace toy
{
	using SolverVector = std::vector<FrameSolver*>;

	enum DirtyLayout
	{
		CLEAN,				// Frame doesn't need update
		DIRTY_REDRAW,		// The parent layout has changed
		DIRTY_PARENT,		// The parent layout has changed
		DIRTY_MARK,		    // 
		DIRTY_LAYOUT,		// The frame layout has changed
		DIRTY_FORCE_LAYOUT,	// The frame layout has changed
		DIRTY_STRUCTURE		// The structure (tree) has changed
	};

	class _refl_ TOY_UI_EXPORT Frame : public Object, public UiRect
	{
	public:
		Frame(Widget& widget);
		~Frame();

		virtual FrameType frameType() { return FRAME; }

		bool empty() const { return d_caption == nullptr && d_icon == nullptr; }

		inline bool flow() const { return d_style->m_layout.m_flow == FLOW; }
		inline bool clip() const { return d_style->m_layout.m_clipping == CLIP; }

		inline bool opaque() const { return m_opacity == OPAQUE; }
		inline bool hollow() const { return m_opacity == HOLLOW; }

		void setEmpty() { d_icon = nullptr; d_caption = nullptr; }

		Caption& setCaption(const string& text);
		Icon& setIcon(Image* image);

		DimFloat contentSize();

		Frame& lookup(FrameType type = LAYER);
		Layer& layer(FrameType type = LAYER);

		virtual void bind(Frame& parent);
		virtual void unbind();

		void show();
		void hide();

		bool visible();

		DirtyLayout clearDirty() { DirtyLayout dirty = d_dirty; d_dirty = CLEAN; return dirty; }
		void setDirty(DirtyLayout dirty) { if(dirty > d_dirty) d_dirty = dirty; }
		void markDirty(DirtyLayout dirty);

		using Filter = std::function<bool(Frame&)>;
		virtual Frame* pinpoint(DimFloat pos, const Filter& filter = nullptr);

		void makeSolver();

		void setStyle(Style& style, bool reset = false);
		void updateStyle(bool reset = false);
		void updateInkstyle(InkStyle& inkstyle);

		void setSizeDim(Dimension dim, float size);
		void setSpanDim(Dimension dim, float span);
		void setPositionDim(Dimension dim, float position);

		inline void setPosition(const DimFloat& pos) { setPositionDim(DIM_X, pos.x), setPositionDim(DIM_Y, pos.y); }
		inline void setSize(const DimFloat& size) { setSizeDim(DIM_X, size.x); setSizeDim(DIM_Y, size.y); }

		// global to local
		void integratePosition(Frame& root, DimFloat& global);
		inline DimFloat integratePosition(const DimFloat& pos, Frame& root) { DimFloat local = pos; integratePosition(root, local); return local; }
		inline DimFloat localPosition(const DimFloat& pos) { return integratePosition(pos, lookup(MASTER_LAYER)); }

		// local to global
		void derivePosition(Frame& root, DimFloat& local);
		inline DimFloat derivePosition(const DimFloat& pos, Frame& root) { DimFloat local = pos; derivePosition(root, local); return local; }
		inline DimFloat derivePosition(const DimFloat& pos) { return derivePosition(pos, lookup(MASTER_LAYER)); }
		inline DimFloat absolutePosition() { return derivePosition({ 0.f, 0.f }); }

		float deriveScale(Frame& root);
		inline float absoluteScale() { return this->deriveScale(lookup(MASTER_LAYER)); }

		bool inside(const DimFloat& pos);

		bool first(Frame& frame);
		bool last(Frame& frame);

		void transferPixelSpan(Frame& prev, Frame& next, Dimension dim, float pixelSpan);

		void setHardClip(const BoxFloat& hardClip);

		void relayout();
		void collect(SolverVector& solvers, DirtyLayout dirtyTop);
		void relayout(SolverVector& solvers);

		void syncSolver(FrameSolver& solver);
		void readSolver(FrameSolver& solver);

		void debugPrintDepth();

	public:
		Widget& d_widget;
		Wedge* d_wedge;
		Frame* d_parent;
		DirtyLayout d_dirty;
		bool d_hidden;
		Dim<size_t> d_index;

		BoxFloat d_hardClip;

		Opacity m_opacity;
		Dimension d_length;

		Style* d_style;
		InkStyle* d_inkstyle;

	public:
		object_ptr<Caption> d_caption;
		object_ptr<Icon> d_icon;
		object_ptr<FrameSolver> m_solver;
	};
}

#endif // TOY_WIDGET_H
