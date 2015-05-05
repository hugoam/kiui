//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_STRIPE_H_INCLUDED
#define MK_STRIPE_H_INCLUDED

/* mk headers */
#include <Ui/Frame/mkFrame.h>

/* Standard */
#include <list>
#include <map>

namespace mk
{
	typedef std::vector<Frame*> FrameVector;

	class MK_UI_EXPORT FlowSequence
	{
	public:
		FlowSequence(FrameVector& vec) : d_vector(vec), d_size(0) {}
		FlowSequence& operator=(const FlowSequence&) = delete;
		FrameVector::const_iterator begin() { return d_vector.begin(); }
		FrameVector::const_iterator end() { return d_vector.begin() + d_size; }
		size_t& size() { return d_size; }
	private:
		FrameVector& d_vector;
		size_t d_size;
	};

	class MK_UI_EXPORT Stripe : public Frame
	{
	public:
		Stripe(Widget& widget);
		~Stripe();

		FrameType frameType() { return STRIPE; }

		inline FrameVector& contents() { return d_contents; }
		inline FlowSequence& sequence() { return d_sequence; }
		inline float& floatDepth() { return d_floatDepth; }
		inline float& floatLength() { return d_sequenceLength; }

		inline float sequenceLength() { return d_sequenceLength; }
		inline Dimension layoutDim() { return d_layout->d_layoutDim; }
		inline bool overflow() { return d_sequenceLength > dsize(d_length); }
		inline float cursor() { return d_cursor; }
		inline float spacing() { return d_layout->spacing()[d_length]; }

		inline Dirty forceDirty() { return d_forceDirty; }
		inline void setForceDirty(Dirty dirty) { if(dirty > d_forceDirty) d_forceDirty = dirty; }
		inline void clearForceDirty() { d_forceDirty = CLEAN; }
		
		inline std::vector<float>& weights() { return *d_weights.get(); }

		inline float dspace(Dimension dim) { return d_size[dim] - dpadding(dim) - dbackpadding(dim) - (dim == d_length ? 0.f : d_floatDepth); }

		inline float spacing(Frame& frame) { return (frame.index() != d_sequence.size()-1) ? this->spacing() : 0.f; }
		inline float extent(Frame& frame, Dimension dim) { return frame.dextent(dim) + (dim == d_length ? this->spacing(frame) : 0.f); }
		inline float extentSequence(Frame& frame) { return frame.dextent(d_length) + this->spacing(frame); }

		inline float align(float space, float extent, Align align) { return space * AlignSpace[align] - extent * AlignExtent[align]; }
		inline float align(Frame& frame, Dimension dim) { return  align(frame.flow() ? dspace(dim) : dsize(dim), frame.dextent(dim), frame.dalign(dim)); }
		inline float alignSequence(Frame& frame) { return d_freeSpace * AlignSpace[frame.dalign(d_length)]; }

		inline float offset(Frame& frame, Dimension dim) { return (frame.flow() ? dpadding(dim) + frame.dmargin(dim) : 0.f) + align(frame, dim); }

		inline float offsetSequenceFirst(Frame& frame) { return -d_cursor + dpadding(d_length) + frame.dmargin(d_length) + alignSequence(frame); }
		inline float offsetSequenceNext(Frame& frame, Frame& prev) { return prev.doffset(d_length) + this->spacing() - alignSequence(prev) + alignSequence(frame); }
		inline float offsetSequence(Frame& frame) { Frame* before = frame.before(); return before ? offsetSequenceNext(frame, *before) : offsetSequenceFirst(frame); }

		inline float dpivotposition(Frame& frame, Dimension dim) { return d_layout->pivot()[dim] ? dsize(dim) - frame.dsize(dim) - frame.dposition(dim) : frame.dposition(dim); }

		void positionLength(Frame& frame);
		void positionDepth(Frame& frame);

		void setCursor(float cursor) { d_cursor = cursor; this->setDirty(DIRTY_OFFSET); }

		void append(Frame& widget);
		void insert(Frame& widget, size_t index);
		void remove(Frame& widget);
		void clear();

		void move(size_t from, size_t to);

		void setVisible(bool visible);

		void migrate(Stripe& stripe);

		void resized(Dimension dim);

		void childShown(Frame& child);
		void childHidden(Frame& child);
		void childSized(Frame& child, Dimension dim, float delta);
		void childSizedLength(Frame& child, float delta);
		void childSizedDepth(Frame& child, float delta);

		void flowSizedDepth(Frame& child, float delta);
		void floatSizedDepth(Frame& child, float delta);

		void normalizeSpan();

		void reindex(size_t from);

		void cursorUp();
		void cursorDown();

		bool nextOffset(Dimension dim, float& pos, float seuil, bool top = false);
		bool prevOffset(Dimension dim, float& pos, float seuil, bool top = false);

		void updateOnce();

		void updateSpace();
		void updateStyle();
		void updateSizing();

		void updateSize();

		void initWeights();
		void dispatchWeights();
		void dispatchTableWeights();

		Frame* pinpoint(float x, float y, bool opaque);

		void shrinkSizeDim(Dimension dim, float size);

	protected:
		void relayout();

		void updateDepth();
		void updateLength();

		void recomputeDepth();
		void recomputeLength();

		void expandDepth();
		void expandLength();

	protected:
		Dimension d_depth;
		Dimension d_length;
		float d_cursor;

		FrameVector d_contents;
		FlowSequence d_sequence;

		float d_sequenceLength;
		float d_floatDepth;
		float d_freeSpace;
		float d_maxDepth;

		Dirty d_forceDirty;

		unique_ptr<std::vector<float>> d_weights;
	};
}

#endif // MK_SEQUENCECONTAINER_H_INCLUDED
