//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_GRID_H
#define TOY_GRID_H

/* toy */
#include <toyui/Frame/Stripe.h>

namespace toy
{
	class TOY_UI_EXPORT GridOverlay : public Stripe
	{
	public:
		GridOverlay(Stripe& parent);

		static StyleType& cls() { static StyleType ty("GridOverlay"); return ty; }
	};

	class TOY_UI_EXPORT GridLine : public Stripe
	{
	public:
		GridLine(Stripe& parent);

		static StyleType& cls() { static StyleType ty("GridLine"); return ty; }
	};

	class TOY_UI_EXPORT GridColumn : public Stripe
	{
	public:
		GridColumn(Stripe& parent);

		static StyleType& cls() { static StyleType ty("GridColumn"); return ty; }
	};

	class TOY_UI_EXPORT TableGrid : public Stripe
	{
	public:
		TableGrid(Widget& widget);

		Stripe& column(size_t index) { return *d_columns[index]; }

		virtual void remap();
		void remap(Stripe& stripe);

		void resize(size_t lines);

		virtual void layout();

	protected:
		GridOverlay d_grid;
		std::vector<unique_ptr<Stripe>> d_columns;
	};

	class TOY_UI_EXPORT Grid : public Stripe
	{
	public:
		Grid(Widget& widget);

		Stripe& line(size_t index) { return *d_lines[index]; }

		virtual void map(Frame& frame);
		virtual void unmap(Frame& frame);

		void resize(size_t lines);

	protected:
		std::vector<unique_ptr<Stripe>> d_lines;
	};
}


#endif // TOY_GRID_H
