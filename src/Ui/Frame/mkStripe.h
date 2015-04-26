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
		inline bool overflow() { return d_sequenceLength > dclipsize(d_length); }
		inline float cursor() { return d_cursor; }
		inline float spacing() { return d_layout->spacing()[d_length]; }
		
		inline std::vector<float>& weights() { return *d_weights.get(); }

		inline float offsetLength(Frame* frame) { return frame->dsize(d_length) + frame->layout()->margin()[d_length] + (frame->index() != d_sequence.size()-1 ? this->spacing() : 0.f); }
		inline float offset(Frame* frame, Dimension dim) { return dim == d_length ? offsetLength(frame) : frame->doffset(d_length); }

		inline float offsetDepth(Frame* frame)
		{
			if(d_inkstyle->align()[d_depth] == CENTER)
				return (dspace(d_depth) - frame->doffset(d_depth)) / 2.f;
			else if(d_inkstyle->align()[d_depth] == RIGHT)
				return (dspace(d_depth) - frame->doffset(d_depth));
			return 0.f;
		}

		inline void positionDepth(Frame* frame)
		{
			frame->setPositionDim(d_depth, this->offsetDepth(frame) + d_layout->padding()[d_depth] + frame->layout()->margin()[d_depth] / 2);
		}

		void setCursor(float cursor) { d_cursor = cursor; d_relayout = true; }

		void append(Frame* widget);
		void insert(Frame* widget, size_t index);
		void remove(Frame* widget);
		void clear();

		void insertFlow(Frame* widget, size_t index);
		void removeFlow(Frame* widget);

		void move(size_t from, size_t to);

		void markDirty(Dirty dirty);
		void setVisible(bool visible);

		void migrate(Stripe& stripe);

		void markRelayout() { d_relayout = true; }

		void resized(Dimension dim);

		void flowHidden(Frame* child);
		void flowShown(Frame* child);

		void flowSizedLength(Frame* child, float delta);
		void flowSizedDepth(Frame* child, float delta);
		void flowSized(Frame* child, Dimension dim, float delta);

		void floatHidden(Frame* child);
		void floatShown(Frame* child);

		void floatSizedLength(Frame* child, float delta);
		void floatSizedDepth(Frame* child, float delta);

		void normalizeSpan();

		void reindex(size_t from);

		void cursorUp();
		void cursorDown();

		bool nextOffset(Dimension dim, float& pos, float seuil, bool top = false);
		bool prevOffset(Dimension dim, float& pos, float seuil, bool top = false);

		void nextFrame(size_t tick, size_t delta);

		void updateSpace();
		void updateStyle();
		void updateSizing();

		void deepRelayout();

		void initWeights();
		void dispatchWeights();
		void dispatchTableWeights();

		inline float dspace(Dimension dim) { return d_size[dim] - d_layout->padding()[dim] - d_layout->padding()[dim + 2] - (dim == d_length ? 0.f : d_floatDepth); }
		inline float dpivotposition(Dimension dim, Frame* frame) { return d_layout->pivot()[dim] ? dsize(dim) - frame->dsize(dim) - frame->dposition(dim) : frame->dposition(dim); }

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

		void positionSequence();

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

		bool d_relayout;

		unique_ptr<std::vector<float>> d_weights;
	};
}

#endif // MK_SEQUENCECONTAINER_H_INCLUDED
