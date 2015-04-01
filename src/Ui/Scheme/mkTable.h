//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WTABLE_H
#define MK_WTABLE_H

/* mk */
#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkButton.h>
#include <Ui/Form/mkForm.h>

namespace mk
{
	class MK_UI_EXPORT _I_ TableHead : public GridSheet, public Typed<TableHead>, public Styled<TableHead>
	{
	public:
		TableHead();
		
		void gridResized(Widget* first, Widget* second);

		using Typed<TableHead>::cls;
	};

	class MK_UI_EXPORT _I_ ColumnHeader : public Label, public Typed<ColumnHeader>, public Styled<ColumnHeader>
	{
	public:
		ColumnHeader(const string& label);

		using Typed<ColumnHeader>::cls;
		using Styled<ColumnHeader>::styleCls;
	};

	class MK_UI_EXPORT _I_ Table : public Sheet, public Typed<Table>, public Styled<Table>
	{
	public:
		Table(StringVector columns, std::vector<float> weights);
		~Table();

		using Typed<Table>::cls;

	protected:
		StringVector mColumns;
		std::vector<float> mWeights;
		TableHead* mHead;
	};
}

#endif
