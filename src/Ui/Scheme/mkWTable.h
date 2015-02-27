//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WTABLE_H
#define MK_WTABLE_H

/* mk */
#include <Ui/Scheme/mkScheme.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Form/mkForm.h>

namespace mk
{
	class MK_UI_EXPORT WTableHead : public GridSheet
	{
	public:
		WTableHead();
		
		void gridResized(Widget* first, Widget* second);
	};

	class MK_UI_EXPORT WTable : public Sheet
	{
	public:
		WTable(StringVector columns, std::vector<float> weights);
		~WTable();

		void build();

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
