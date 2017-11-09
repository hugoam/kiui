//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Solver/Solver.h>

#include <toyui/Widget/Widget.h>
#include <toyui/Frame/Caption.h>

namespace toy
{
	Space Space::preset(SpacePreset preset)
	{
		if     (preset == SHEET)  return { PARAGRAPH,  WRAP,   WRAP };
		else if(preset == FLEX)	  return { PARALLEL,   WRAP,   WRAP };
		else if(preset == ITEM)   return { READING,    SHRINK, SHRINK };
		else if(preset == UNIT)   return { PARAGRAPH,  SHRINK, SHRINK };
		else if(preset == BLOCK)  return { PARAGRAPH,  FIXED,  FIXED };
		else if(preset == LINE)   return { READING,    WRAP,   SHRINK };
		else if(preset == STACK)  return { PARAGRAPH,  SHRINK, WRAP };
		else if(preset == DIV)    return { ORTHOGONAL, WRAP,   SHRINK };
		else if(preset == SPACER) return { PARALLEL,   WRAP,   SHRINK };
		else if(preset == BOARD)  return { PARAGRAPH,  EXPAND, EXPAND };
		else 					  return { PARAGRAPH,  WRAP,   WRAP };
	}

	float AlignSpace[5] = { 0.f, 0.5f, 1.f, 0.f, 1.f };
	float AlignExtent[5] = { 0.f, 0.5f, 1.f, 1.f, 0.f };

	FrameSolver::FrameSolver(FrameSolver* solver, LayoutStyle* layout, Frame* frame)
		: d_frame(frame)
		, d_parent(solver)
		, d_solvers{ solver ? &solver->solver(*this, DIM_X) : nullptr, solver ? &solver->solver(*this, DIM_Y) : nullptr }
		, d_grid(solver ? solver->grid() : nullptr)
		, d_style(layout)
		, d_length(DIM_NULL)
		, d_depth(DIM_NULL)
		, d_sizing(SHRINK, SHRINK)
		, d_content(0.f, 0.f)
		, d_spaceContent(0.f, 0.f)
		, d_contentExpand(false)
		, d_prev(nullptr)
	{
		if(d_style)
			this->applySpace();
	}

	FrameSolver& FrameSolver::solver(FrameSolver& frame, Dimension dim)
	{
		if(dim == d_length && d_grid && frame.d_frame && frame.d_parent != d_grid)
			return d_grid->solver(frame, dim);
		return *this;
	}

	void FrameSolver::applySpace(Dimension length)
	{
		const Space& space = d_style->d_space;

		if(length != DIM_NULL)
			d_length = length;
		else if(space.direction == ORTHOGONAL)
			d_length = this->orthogonal(d_parent->d_length);
		else if(space.direction == PARALLEL)
			d_length = d_parent->d_length;
		else if(space.direction == READING)
			d_length = DIM_X;
		else if(space.direction == PARAGRAPH)
			d_length = DIM_Y;

		d_depth = this->orthogonal(d_length);

		d_sizing[d_length] = space.sizingLength;
		d_sizing[d_depth] = space.sizingDepth;
	}

	void FrameSolver::collect(SolverVector& solvers)
	{
		this->reset();
		this->sync();
		solvers.push_back(this);
	}

	void FrameSolver::sync()
	{
		if(d_frame)
			d_frame->syncSolver(*this);
	}

	void FrameSolver::compute()
	{
		if(!d_parent) return;
		d_solvers[DIM_X]->compute(*this, DIM_X);
		d_solvers[DIM_Y]->compute(*this, DIM_Y);

#if 0 // DEBUG
		if(!d_frame) return;
		d_frame->debugPrintDepth();
		printf("LAYOUT: %s measured content size %i , %i\n", d_frame->style().m_name.c_str(), int(d_content.x), int(d_content.y));
#endif
	}

	void FrameSolver::layout()
	{
		if(!d_parent) return;
		d_solvers[DIM_X]->layout(*this, DIM_X);
		d_solvers[DIM_Y]->layout(*this, DIM_Y);

#if 0 // DEBUG
		if(!d_frame) return;
		d_frame->debugPrintDepth();
		printf("LAYOUT: %s size %i , %i\n", d_frame->style().m_name.c_str(), int(d_size.x), int(d_size.y));
		d_frame->debugPrintDepth();
		printf("        %s position %i , %i\n", d_frame->style().m_name.c_str(), int(d_position.x), int(d_position.y));
#endif
	}

	void FrameSolver::read()
	{
		if(d_frame)
			d_frame->readSolver(*this);
	}

	void FrameSolver::compute(FrameSolver& frame, Dimension dim)
	{
		UNUSED(frame); UNUSED(dim);
	}

	void FrameSolver::layout(FrameSolver& frame, Dimension dim)
	{
		UNUSED(frame); UNUSED(dim);
	}

	RowSolver::RowSolver(FrameSolver* solver, LayoutStyle* layout, Frame* frame)
		: FrameSolver(solver, layout, frame)
	{}

	void RowSolver::compute(FrameSolver& frame, Dimension dim)
	{
		if(dim == d_length && frame.flow() && frame.d_sizing[d_length] >= WRAP)
			d_totalSpan += frame.d_span[d_length];

		if(!frame.sizeflow())
			return;

		if(frame.d_sizing[dim] <= WRAP)
			this->measure(frame, d_content, dim);

		if(frame.d_sizing[dim] <= SHRINK && frame.flow() && dim == d_length)
			d_spaceContent[dim] += frame.dbounds(dim);

		if(dim == d_length && frame.d_sizing[d_length] >= WRAP)
			d_contentExpand = true;
	}

	void RowSolver::measure(FrameSolver& frame, DimFloat& size, Dimension dim)
	{
		if(dim == d_length && frame.flow())
			size[dim] += frame.dbounds(dim) + (d_count++ ? this->spacing() : 0.f);
		else
			size[dim] = std::max(size[dim], frame.dbounds(dim));
	}

	void RowSolver::layout(FrameSolver& frame, Dimension dim)
	{
		if(dim == d_length && frame.flow() && frame.d_sizing[d_length] >= WRAP)
			frame.d_span[d_length] = frame.d_span[d_length] / d_totalSpan;

		this->resize(frame, dim);

		if(frame.posflow())
			this->position(frame, dim);
	}

	void RowSolver::resize(FrameSolver& frame, Dimension dim)
	{
		if(d_style->d_layout.val[dim] < AUTO_SIZE)
			return;

		float space = this->dspace(dim);
		//bool hasSpace = space > d_content[dim]; // @todo: implement scarcity check, current behavior when scarce is wrong
		float spacings = float(std::max(int(d_count) - 1, 0)) * this->spacing();
		if(dim == d_length)
			space = (space - d_spaceContent[dim] - spacings) * frame.d_span[d_length];

		float content = frame.dcontent(dim);

		Sizing sizing = frame.d_sizing[dim];
		if(sizing == SHRINK)
			frame.d_size[dim] = content;
		else if(sizing == WRAP)
			frame.d_size[dim] = std::max(content, space);
		else if(sizing == EXPAND)
			frame.d_size[dim] = space;
	}

	void RowSolver::position(FrameSolver& frame, Dimension dim)
	{
		if(d_style->d_layout.val[dim] < AUTO_LAYOUT)
			return;

		float space = this->dspace(dim);

		if(dim == d_length && frame.flow())
			frame.d_position[dim] = this->positionSequence(frame, d_contentExpand ? 0.f : space - d_content[d_length]);
		else
			frame.d_position[dim] = this->positionFree(frame, dim, space);

		if(dim == d_length)
			d_prev = &frame;
	}

	float RowSolver::positionFree(FrameSolver& frame, Dimension dim, float space)
	{
		Align align = frame.dalign(dim == d_length ? DIM_X : DIM_Y);
		float alignOffset = space * AlignSpace[align] - frame.dextent(dim) * AlignExtent[align];
		return (frame.flow() ? dpadding(dim) + frame.dmargin(dim) : 0.f) + alignOffset;
	}

	namespace
	{
		inline float alignSequence(FrameSolver& frame, float space) { return space * AlignSpace[frame.dalign(DIM_X)]; }
	}

	float RowSolver::positionSequence(FrameSolver& frame, float space)
	{
		if(d_prev)
			return d_prev->doffset(d_length) - alignSequence(*d_prev, space) + this->spacing() + alignSequence(frame, space);
		else
			return dpadding(d_length) + frame.dmargin(d_length) + alignSequence(frame, space);
	}

	CustomSolver::CustomSolver(FrameSolver* solver, LayoutStyle* layout, Frame* frame)
		: RowSolver(solver, layout, frame)
	{}

	void CustomSolver::collect(SolverVector& solvers)
	{
		FrameSolver::collect(solvers);

		for(auto& solver : m_solvers)
			solver->collect(solvers);
	}
}
