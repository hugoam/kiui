//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_FRAME_H
#define TOY_FRAME_H

/* toy */
#include <toyobj/Type.h>
#include <toyobj/String/String.h>
#include <toyobj/Util/Updatable.h>
#include <toyui/Forward.h>
#include <toyui/Frame/UiRect.h>
#include <toyui/Frame/Content.h>
#include <toyui/Frame/Caption.h>

#include <cmath>

namespace toy
{
	class _refl_ TOY_UI_EXPORT Frame : public Object, public UiRect
	{
	public:
		Frame(Widget& widget);
		~Frame();

		enum Dirty
		{
			CLEAN,				// Frame doesn't need update
			DIRTY_ABSOLUTE,		// The absolute position of the frame has changed
			DIRTY_POSITION,		// The relative position of the frame has changed
			DIRTY_CONTENT,		// The content of the widget has changed
			DIRTY_LAYOUT,		// The skin of the frame has changed
			DIRTY_STRUCTURE
		};

		virtual FrameType frameType() { return FRAME; }

		inline Widget& widget() { return d_widget; }
		inline Wedge& wedge() { return *d_wedge; }
		inline Frame* parent() const { return d_parent; }
		inline Dirty dirty() const { return d_dirty; }
		inline bool hidden() const { return d_hidden; }
		inline const DimIndex& index() const { return d_index; }
		inline size_t dindex(Dimension dim) const { return d_index[dim]; }

		bool empty() const { return d_caption == nullptr && d_icon == nullptr; }

		inline const BoxFloat& hardClip() const { return d_hardClip; }

		inline bool flow() const { return d_style->layout().d_flow == FLOW; }
		inline bool clip() const { return d_style->layout().d_clipping == CLIP; }

		inline bool opaque() const { return d_opacity == OPAQUE; }
		inline bool hollow() const { return d_opacity == HOLLOW; }

		inline FrameSolver& solver() { return *d_solver; }

		inline Style& style() const { return *d_style; }
		inline InkStyle& inkstyle() const { return *d_inkstyle; }

		void setIndex(size_t xindex, size_t yindex) { d_index[DIM_X] = xindex; d_index[DIM_Y] = yindex; }

		void setEmpty() { d_icon = nullptr; d_caption = nullptr; }

		Caption* caption() { return d_caption.get(); }
		Icon* icon() { return d_icon.get(); }

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

		void clearDirty() { d_dirty = CLEAN; }
		void setDirty(Dirty dirty) { if(dirty > d_dirty) d_dirty = dirty; }
		void markDirty(Dirty dirty);

		using Filter = std::function<bool(Frame&)>;
		virtual Frame* pinpoint(DimFloat pos, const Filter& filter = nullptr);

		void makeSolver();

		void setStyle(Style& style, bool reset = false);
		void updateStyle(bool reset = false);
		void updateInkstyle(InkStyle& inkstyle);

		void setSizeDim(Dimension dim, float size);
		void setSpanDim(Dimension dim, float span);
		void setPositionDim(Dimension dim, float position);

		inline void setPosition(const DimFloat& pos) { setPositionDim(DIM_X, pos.x()), setPositionDim(DIM_Y, pos.y()); }
		inline void setSize(const DimFloat& size) { setSizeDim(DIM_X, size.x()); setSizeDim(DIM_Y, size.y()); }

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

		void transferPixelSpan(Frame& prev, Frame& next, float pixelSpan);

		void setHardClip(const BoxFloat& hardClip);

		void relayout();
		void syncSolver();
		void readSolver();

		void debugPrintDepth();

		static Type& cls() { static Type ty; return ty; }

	public:
		Widget& d_widget;
		Wedge* d_wedge;
		Frame* d_parent;
		Dirty d_dirty;
		bool d_hidden;
		DimIndex d_index;

		BoxFloat d_hardClip;

		Opacity d_opacity;
		Dimension d_length;

		Style* d_style;
		InkStyle* d_inkstyle;

	protected:
		object_ptr<Caption> d_caption;
		object_ptr<Icon> d_icon;
		object_ptr<FrameSolver> d_solver;
	};
}

#endif // TOY_WIDGET_H
