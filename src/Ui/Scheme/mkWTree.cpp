//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Scheme/mkWTree.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Form/mkWidgets.h>

#include <Ui/Scheme/mkWExpandbox.h>

#include <Ui/Frame/mkFrame.h>

using namespace std::placeholders;

namespace mk
{
	WTreeNode::WTreeNode(string image, string title, bool collapsed)
		: WExpandbox(title, collapsed)
	{
		mClas = "treenode";
	}

	WTree::WTree(string cls, Form* form)
		: ScrollSheet(cls, form)
		, mRootNode(nullptr)
		, mSelected(nullptr)
	{}

	WTree::~WTree()
	{}

	void WTree::select(WTreeNode* selected)
	{
		if(mSelected)
			mSelected->header()->updateState(ENABLED);

		selected->header()->updateState(ACTIVATED);
		mSelected = selected;

		Widget* node = selected;
		while(node != this)
		{
			if(node->clas() == "expandbox")
			{
				node->as<WTreeNode>()->expand();
				for(auto& widget : node->parent()->contents()->store())
					if(widget.get() != node)
						widget->as<WTreeNode>()->collapse();
			}
			node = node->parent();
		}
	}

	TreeNode::TreeNode(string image, string title, bool collapsed)
		: Expandbox(title, collapsed)
	{}

	Tree::Tree(string cls)
		: Form(cls + " tree", "", [this]() { return make_unique<WTree>("tree", this); })
	{}
}
