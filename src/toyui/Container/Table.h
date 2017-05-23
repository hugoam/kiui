//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_TABLE_H
#define TOY_TABLE_H

/* toy */
#include <toyui/Widget/Sheet.h>
#include <toyui/Container/Layout.h>
#include <toyui/Button/Button.h>

namespace toy
{
	class _I_ TOY_UI_EXPORT TableHead : public GridSheet
	{
	public:
		TableHead(Table& table);
		
		void gridResized(Frame& first, Frame& second);

		static Type& cls() { static Type ty("TableHead", GridSheet::cls()); return ty; }

	protected:
		Table& m_table;
	};

	class _I_ TOY_UI_EXPORT ColumnHeader : public Label
	{
	public:
		ColumnHeader(Wedge& parent, const string& label, float span);

		static Type& cls() { static Type ty("ColumnHeader", Label::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Table : public Stack
	{
	public:
		Table(Wedge& parent, StringVector columns, std::vector<float> weights);

		static Type& cls() { static Type ty("Table", Stack::cls()); return ty; }

	protected:
		StringVector m_columns;
		std::vector<float> m_weights;
		TableHead m_head;
	};
}

#endif
