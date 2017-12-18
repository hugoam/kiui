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
	class TOY_UI_EXPORT FrameSolver : public Object, public UiRect
	{
	public:
		FrameSolver(FrameSolver* solver, Layout* layout, Frame* frame = nullptr);

		inline bool flow() { return d_style->m_flow == FLOW; }
		inline bool posflow() { return d_style->m_flow <= ALIGN; }
		inline bool sizeflow() { return d_style->m_flow <= OVERLAY; }

		inline float dpadding(Dimension dim) { return d_style->m_padding[dim]; }
		inline float dbackpadding(Dimension dim) { return d_style->m_padding[dim + 2]; }
		inline float dmargin(Dimension dim) { return d_style->m_margin[dim]; }

		inline Align dalign(Dimension dim) { return d_style->m_align[dim]; }

		inline float dcontent(Dimension dim) { return d_content[dim] + dpadding(dim) + dbackpadding(dim); }
		inline float dbounds(Dimension dim) { return dcontent(dim) + dmargin(dim) * 2.f; }

		inline float dextent(Dimension dim) { return m_size[dim] + dmargin(dim) * 2.f; }
		inline float doffset(Dimension dim) { return d_position[dim] + m_size[dim] + dmargin(dim); }
		inline float dspace(Dimension dim) { return m_size[dim] - dpadding(dim) - dbackpadding(dim); }

		//inline float spacing(FrameSolver& frame) { return d_prev ? d_style->m_spacing[d_length] : 0.f; }
		inline float spacing() { return d_style->m_spacing[d_length]; }

		inline Dimension orthogonal(Dimension dim) { return dim == DIM_X ? DIM_Y : DIM_X; }

		void setup(const DimFloat& position, const DimFloat& size, const DimFloat& span, const DimFloat* content)
		{
			d_position = position;
			m_span = span;
			m_size = size;

			if(d_sizing.x == FIXED) d_content.x = (content ? content->x : m_size.x - dpadding(DIM_X) - dbackpadding(DIM_X));
			if(d_sizing.y == FIXED) d_content.y = (content ? content->y : m_size.y - dpadding(DIM_Y) - dbackpadding(DIM_Y));
			if(d_sizing.x == FIXED) m_size.x = d_content.x + dpadding(DIM_X) + dbackpadding(DIM_X);
			if(d_sizing.y == FIXED) m_size.y = d_content.y + dpadding(DIM_Y) + dbackpadding(DIM_Y);
		}

		void reset(bool partial = false)
		{
			m_size = { 0.f, 0.f };
			if(!partial)
				d_content = { 0.f, 0.f };
			m_spaceContent = { 0.f, 0.f };
			d_contentExpand = false;
			d_totalSpan = 0.f;
			d_prev = nullptr;
			d_count = 0;
		}

		void applySpace(Dimension length = DIM_NULL);

		virtual void collect(SolverVector& solvers);

		virtual FrameSolver& solver(FrameSolver& frame, Dimension dim);
		virtual FrameSolver* grid() { return nullptr; }

		void sync();
		void compute();
		void layout();
		void read();

		virtual void compute(FrameSolver& frame, Dimension dim);
		virtual void layout(FrameSolver& frame, Dimension dim);

	public:
		Frame* d_frame;
		FrameSolver* d_parent;
		FrameSolver* m_solvers[2];
		FrameSolver* d_grid;
		Layout* d_style;

		Dimension d_length;
		Dimension d_depth;

		Dim<Sizing> d_sizing;

		DimFloat d_content;
		DimFloat m_spaceContent;
		bool d_contentExpand;
		float d_totalSpan;

		Dim<size_t> d_index;

		FrameSolver* d_prev;
		size_t d_count;
	};

	class TOY_UI_EXPORT RowSolver : public FrameSolver
	{
	public:
		RowSolver(FrameSolver* solver, Layout* layout, Frame* frame = nullptr);

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
		CustomSolver(FrameSolver* solver, Layout* layout, Frame* frame = nullptr);

		virtual void collect(SolverVector& solvers);

	protected:
		std::vector<unique_ptr<FrameSolver>> m_solvers;
	};
}

#endif // TOY_SOLVER_H
