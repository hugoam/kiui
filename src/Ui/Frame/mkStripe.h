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
		Stripe(Stripe* parent, Widget* widget, size_t index);
		~Stripe();

		inline FrameVector& contents() { return d_contents; }
		inline FlowSequence& sequence() { return d_sequence; }

		inline float sequenceLength() { return d_sequenceLength; }
		inline Dimension layoutDim() { return d_style->d_layoutDim; }
		inline bool overflow() { return d_sequenceLength > dclipsize(d_length); }
		inline float cursor() { return d_cursor; }
		
		inline std::vector<float>& weights() { return *d_weights.get(); }

		void setCursor(float cursor) { d_cursor = cursor; d_relayout = true; }

		void append(Frame* widget);
		void insert(Frame* widget, size_t index);
		void remove(Frame* widget);
		void clear();

		void insertManual(Frame* frame, size_t index);
		void removeManual(Frame* frame);

		void insertFlow(Frame* widget, size_t index);
		void removeFlow(Frame* widget);

		void appendManual(Frame* frame)	{ this->insertManual(frame, d_contents.size()); }

		void appendFlow(Frame* widget) { this->insertFlow(widget, d_sequence.size()); }
		void prependFlow(Frame* widget) { this->insertFlow(widget, 0); }

		void move(size_t from, size_t to);

		void markDirty(Dirty dirty);
		void setVisible(bool visible);

		void migrate(Stripe* stripe);

		void markRelayout() { d_relayout = true; }

		void resized(Dimension dim);

		void flowHidden(Frame* child);
		void flowShown(Frame* child);

		void flowSizedLength(Frame* child, float delta);
		void flowSizedDepth(Frame* child, float delta);
		void flowSized(Frame* child, Dimension dim, float delta);

		void normalizeSpan();

		void reindex(size_t from);

		float firstVisible();

		void nextFrame(size_t tick, size_t delta);

		void deepRelayout();

		void initWeights();
		void storeWeights();
		void dispatchWeights();
		void dispatchTableWeights();

		inline float dspace(Dimension dim) { return d_size[dim] - d_style->d_padding[dim] - d_style->d_padding[dim+2]; }
		inline float dpivotposition(Dimension dim, Frame* frame) { return d_style->d_pivot[dim] ? dsize(dim) - frame->dsize(dim) - frame->dposition(dim) : frame->dposition(dim); }

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
		float d_maxDepth;

		bool d_relayout;

		unique_ptr<std::vector<float>> d_weights;
	};
}

#endif // MK_SEQUENCECONTAINER_H_INCLUDED
