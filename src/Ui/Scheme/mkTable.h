//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WTABLE_H
#define MK_WTABLE_H

/* mk */
#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkButton.h>

namespace mk
{
	class MK_UI_EXPORT _I_ TableHead : public GridSheet
	{
	public:
		TableHead();
		
		void gridResized(Widget& first, Widget& second);

		static StyleType& cls() { static StyleType ty("TableHead", GridSheet::cls()); return ty; }
	};

	class MK_UI_EXPORT _I_ ColumnHeader : public Label
	{
	public:
		ColumnHeader(const string& label);

		static StyleType& cls() { static StyleType ty("ColumnHeader", Label::cls()); return ty; }
	};

	class MK_UI_EXPORT _I_ Table : public Sheet
	{
	public:
		Table(StringVector columns, std::vector<float> weights);
		~Table();

		static StyleType& cls() { static StyleType ty("Table", Sheet::cls()); return ty; }

	protected:
		StringVector m_columns;
		std::vector<float> m_weights;
		TableHead& m_head;
	};
}

#endif
