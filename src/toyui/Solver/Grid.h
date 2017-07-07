//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_GRID_H
#define TOY_GRID_H

/* toy */
#include <toyui/Solver/Solver.h>

namespace toy
{
	class TOY_UI_EXPORT TableSolver : public CustomSolver
	{
	public:
		TableSolver(FrameSolver* solver, LayoutStyle* layout, Frame* frame = nullptr);

		void divide(const std::vector<float>& spans);
		void update(const std::vector<float>& spans);

		virtual FrameSolver& solver(FrameSolver& frame, Dimension dim);
		virtual FrameSolver* grid(FrameSolver& frame) { return this; }
	};

	class TOY_UI_EXPORT LineSolver : public RowSolver
	{
	public:
		LineSolver(FrameSolver* solver, Space space);

		LayoutStyle d_style;
	};

	class TOY_UI_EXPORT GridSolver : public CustomSolver
	{
	public:
		GridSolver(FrameSolver* solver, LayoutStyle* layout, Frame* frame = nullptr);

		void divide(std::vector<Space> spaces);

		virtual FrameSolver& solver(FrameSolver& frame, Dimension dim);
	};

	typedef std::vector<size_t> GridIndex;
}


#endif // TOY_GRID_H
