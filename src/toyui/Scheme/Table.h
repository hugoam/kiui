//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_WTABLE_H
#define TOY_WTABLE_H

/* toy */
#include <toyui/Widget/Sheet.h>
#include <toyui/Widget/Button.h>

namespace toy
{
	class _I_ TOY_UI_EXPORT TableHead : public GridSheet
	{
	public:
		TableHead(Table& table);
		
		void gridResized(Frame& first, Frame& second);

		static StyleType& cls() { static StyleType ty("TableHead", GridSheet::cls()); return ty; }

	protected:
		Table& m_table;
	};

	class _I_ TOY_UI_EXPORT ColumnHeader : public Label
	{
	public:
		ColumnHeader(const string& label, float span);

		static StyleType& cls() { static StyleType ty("ColumnHeader", Label::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Table : public Sheet
	{
	public:
		Table(StringVector columns, std::vector<float> weights);

		void bound();

		static StyleType& cls() { static StyleType ty("Table", Sheet::cls()); return ty; }

	protected:
		StringVector m_columns;
		std::vector<float> m_weights;
		TableHead& m_head;
	};
}

#endif
