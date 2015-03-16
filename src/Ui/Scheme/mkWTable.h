//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WTABLE_H
#define MK_WTABLE_H

/* mk */
#include <Ui/Scheme/mkScheme.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkWButton.h>
#include <Ui/Form/mkForm.h>

namespace mk
{
	class MK_UI_EXPORT _I_ WTableHead : public GridSheet, public Typed<WTableHead>, public Styled<WTableHead>
	{
	public:
		WTableHead();
		
		void gridResized(Widget* first, Widget* second);

		using Typed<WTableHead>::cls;
	};

	class MK_UI_EXPORT _I_ WColumnHeader : public WLabel, public Typed<WColumnHeader>, public Styled<WColumnHeader>
	{
	public:
		WColumnHeader(const string& label);

		using Typed<WColumnHeader>::cls;
		using Styled<WColumnHeader>::styleCls;
	};

	class MK_UI_EXPORT _I_ WTable : public Sheet, public Typed<WTable>, public Styled<WTable>
	{
	public:
		WTable(StringVector columns, std::vector<float> weights);
		~WTable();

		void build();

		using Typed<WTable>::cls;

	protected:
		StringVector mColumns;
		std::vector<float> mWeights;
		WTableHead* mHead;
	};

	class MK_UI_EXPORT Table : public Form
	{
	public:
		Table(StringVector columns, std::vector<float> weights);
	};
}

#endif
