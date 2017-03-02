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
		GridOverlay(Widget& widget, Stripe& parent);

		static Type& cls() { static Type ty("GridOverlay"); return ty; }
	};

	class TOY_UI_EXPORT GridLine : public Stripe
	{
	public:
		GridLine(Widget& widget, Stripe& parent);

		static Type& cls() { static Type ty("GridLine"); return ty; }
	};

	class TOY_UI_EXPORT GridColumn : public Stripe
	{
	public:
		GridColumn(Widget& widget, Stripe& parent);

		static Type& cls() { static Type ty("GridColumn"); return ty; }
	};

	class TOY_UI_EXPORT TableGrid : public Stripe
	{
	public:
		TableGrid(Widget& widget);

		Stripe& column(size_t index) { return *d_columns[index]; }

		virtual void remap();
		virtual void unmap();

		void remap(Stripe& stripe);

		void resize(size_t lines);

	protected:
		unique_ptr<GridOverlay> d_grid;
		std::vector<unique_ptr<Stripe>> d_columns;
	};

	class TOY_UI_EXPORT Grid : public Stripe
	{
	public:
		Grid(Widget& widget);

		Stripe& line(size_t index) { return *d_lines[index]; }

		virtual void map(Frame& frame);
		virtual void unmap(Frame& frame);
		virtual void unmap();

		void resize(size_t lines);

	protected:
		std::vector<unique_ptr<Stripe>> d_lines;
	};

	/*class TOY_UI_EXPORT Bigrid : public Stripe
	{
	public:
		Bigrid(Widget& widget);

		Stripe& column(size_t index) { return *d_columns[index]; }

		virtual void map(Frame& frame);
		virtual void unmap(Frame& frame);

		void resize(size_t lines);

	protected:
		std::vector<unique_ptr<Grid>> d_columns;
	};*/
}


#endif // TOY_GRID_H
