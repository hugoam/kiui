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
	// @todo add size_t d_shiftpos, from the shiftpos, the rest of the elements in the sequence are reverse positioned (from the end)
	class MK_UI_EXPORT Stripe : public Frame
	{
	public:
		typedef std::vector<Frame*> Sequence;

	public:
		Stripe(Stripe* parent, Widget* widget, string clas = "");
		~Stripe();

		inline Sequence& contents() { return d_contents; }
		inline Sequence& sequence() { return d_sequence; }

		inline float sequenceLength() { return d_sequenceLength; }
		inline Dimension layoutDim() { return d_style->d_layoutDim; }
		inline bool overflow() { return d_sequenceLength > dclipsize(d_length); }
		inline float cursor() { return d_cursor; }
		
		inline std::vector<float>& weightTable() { return d_weightTable; }

		void setCursor(float cursor) { d_cursor = cursor; d_relayout = true; }

		void append(Frame* widget);
		void insert(Frame* widget, size_t index);
		void remove(Frame* widget);
		void clear();

		void appendManual(Frame* frame);
		void insertManual(Frame* frame, size_t index);
		void removeManual(Frame* frame);

		void insertFlow(Frame* widget, size_t index);
		void removeFlow(Frame* widget);

		void shiftBack(Frame* frame);
		void move(size_t from, size_t to);

		void appendFlow(Frame* widget) { insertFlow(widget, d_sequence.size()); }
		void prependFlow(Frame* widget) { insertFlow(widget, 0); }

		void markDirty(Dirty dirty);
		void setVisible(bool visible);

		void migrate(Stripe* stripe);

		void markRelayout() { d_relayout = true; }

		void resized(Dimension dim);

		void flowChanged(Frame* child);
		void flowChanged(Frame* child, Dimension dim);

		void normalizeSpan();

		void reindexFlow(size_t from);
		void reindexManual(size_t from);

		float firstVisible();

		void nextFrame(size_t tick, size_t delta);

		void deepRelayout();

		void distributeWeights();

		inline float dspace(Dimension dim) { return d_size[dim] - d_style->d_padding[dim] - d_style->d_padding[dim+2]; }
		inline float dpivotposition(Dimension dim, Frame* frame) { return d_style->d_pivot[dim] ? dsize(dim) - frame->dsize(dim) - frame->dposition(dim) : frame->dposition(dim); }

		FrameType frameType() { return STRIPE; }

		Frame* pinpoint(float x, float y, bool opaque);

		void shrinkSizeDim(Dimension dim, float size);

	protected:
		void relayout();

		void updateDepth();
		void updateLength();

		void expandDepth();
		void expandLength();

		void positionSequence();

	protected:
		Dimension d_depth;
		Dimension d_length;
		float d_cursor;

		Sequence d_sequence;
		Sequence d_contents;

		float d_sequenceLength;
		float d_maxDepth;

		bool d_relayout;

		std::vector<float> d_weightTable;
	};
}

#endif // MK_SEQUENCECONTAINER_H_INCLUDED
