//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WTREE_H
#define MK_WTREE_H

/* mk */
#include <Ui/Scheme/mkScheme.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Form/mkForm.h>

namespace mk
{
	class MK_UI_EXPORT WTree : public ScrollSheet
	{
	public:
		WTree(string cls, Form* form);
		~WTree();

		void select(WExpandbox* node);

	protected:
		WExpandbox* mRootNode;
		WExpandbox* mSelected;
	};

	class MK_UI_EXPORT Tree : public Form
	{
	public:
		Tree(string cls = "");
	};
}

#endif
