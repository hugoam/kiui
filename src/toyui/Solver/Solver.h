//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_SOLVER_H
#define TOY_SOLVER_H

/* toy */
#include <toyui/Frame/Frame.h>

/* std */
#include <vector>

namespace toy
{
	using FrameVector = std::vector<FrameSolver*>;

	class TOY_UI_EXPORT FrameSolver : public Object, public UiRect
	{
	public:
		FrameSolver(FrameSolver* solver, LayoutStyle* layout, Frame* frame = nullptr);

		inline bool flow() { return d_style->d_flow == FLOW; }
		inline bool posflow() { return d_style->d_flow <= ALIGN; }
		inline bool sizeflow() { return d_style->d_flow <= OVERLAY; }

		inline float dpadding(Dimension dim) { return d_style->d_padding.val[dim]; }
		inline float dbackpadding(Dimension dim) { return d_style->d_padding.val[dim + 2]; }
		inline float dmargin(Dimension dim) { return d_style->d_margin.val[dim]; }

		inline Align dalign(Dimension dim) { return d_style->d_align.val[dim]; }

		inline float dcontent(Dimension dim) { return d_content[dim] + dpadding(dim) + dbackpadding(dim); }
		inline float dbounds(Dimension dim) { return dcontent(dim) + dmargin(dim) * 2.f; }

		inline float dextent(Dimension dim) { return d_size[dim] + dmargin(dim) * 2.f; }
		inline float doffset(Dimension dim) { return d_position[dim] + d_size[dim] + dmargin(dim); }
		inline float dspace(Dimension dim) { return d_size[dim] - dpadding(dim) - dbackpadding(dim); }

		//inline float spacing(FrameSolver& frame) { return d_prev ? d_style->d_spacing.val[d_length] : 0.f; }
		inline float spacing() { return d_prev ? d_style->d_spacing.val[d_length] : 0.f; }

		inline Dimension orthogonal(Dimension dim) { return dim == DIM_X ? DIM_Y : DIM_X; }

		void setup(const DimFloat& position, const DimFloat& size, const DimFloat& span)
		{
			d_position = position;
			d_span = span;

			if(d_sizing.x() == FIXED) d_size[DIM_X] = size.x();
			if(d_sizing.y() == FIXED) d_size[DIM_Y] = size.y();

			d_content = d_size;
		}

		void reset()
		{
			d_size = DimFloat(0.f, 0.f);
			d_content = DimFloat(0.f, 0.f);
			d_spaceContent = DimFloat(0.f, 0.f);
			d_contentExpand = false;
			d_totalSpan = 0.f;
			d_prev = nullptr;
		}

		void applySpace(Dimension length = DIM_NULL);

		virtual void collect(FrameVector& frames);

		virtual FrameSolver& solver(FrameSolver& frame, Dimension dim);
		virtual FrameSolver* grid(FrameSolver& frame) { return nullptr; }

		void compute();
		void layout();

		virtual void compute(FrameSolver& frame, Dimension dim);
		virtual void layout(FrameSolver& frame, Dimension dim);

		static Type& cls() { static Type ty; return ty; }

	public:
		Frame* d_frame;
		FrameSolver* d_parent;
		FrameSolver* d_solvers[2];
		FrameSolver* d_grid;
		LayoutStyle* d_style;

		DimSizing d_sizing;

		Dimension d_length;
		Dimension d_depth;

		DimFloat d_content;
		DimFloat d_spaceContent;
		bool d_contentExpand;
		float d_totalSpan;

		DimIndex d_index;

		FrameSolver* d_prev;
	};

	class TOY_UI_EXPORT RowSolver : public FrameSolver
	{
	public:
		RowSolver(FrameSolver* solver, LayoutStyle* layout, Frame* frame = nullptr);

		virtual void compute(FrameSolver& frame, Dimension dim);
		virtual void layout(FrameSolver& frame, Dimension dim);

	protected:
		void measure(FrameSolver& frame, DimFloat& size, Dimension dim);
		void resize(FrameSolver& frame, Dimension dim);
		void position(FrameSolver& frame, Dimension dim);

		float positionFree(FrameSolver& frame, Dimension dim, float space);
		float positionSequence(FrameSolver& frame, float space);
	};

	class TOY_UI_EXPORT CustomSolver : public RowSolver
	{
	public:
		CustomSolver(FrameSolver* solver, LayoutStyle* layout, Frame* frame = nullptr);

		virtual void collect(FrameVector& frames);

	protected:
		std::vector<unique_ptr<FrameSolver>> m_solvers;
	};
}

#endif // TOY_SOLVER_H
