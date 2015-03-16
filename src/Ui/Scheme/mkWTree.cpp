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
	WTreeNodeHeader::WTreeNodeHeader(const Trigger& trigger)
		: WWrapButton(nullptr, styleCls(), trigger)
	{}

	WTreeNodeBody::WTreeNodeBody()
		: Sheet(styleCls())
	{}

	WTreeNodeToggle::WTreeNodeToggle(const Trigger& triggerOn, const Trigger& triggerOff, bool on)
		: WToggle(styleCls(), triggerOn, triggerOff, on)
	{}

	WTreeNode::WTreeNode(Form* form, const string& image, const string& title, bool collapsed)
		: WExpandbox(form, title, collapsed)
	{
		mType = cls();
		mStyle = styleCls();
	}

	void WTreeNode::build()
	{
		Sheet::build();
		mHeader = this->makeappend<WTreeNodeHeader>(std::bind(&WTreeNode::selected, this));
		mContainer = this->makeappend<WTreeNodeBody>();

		mExpandButton = mHeader->makeappend<WTreeNodeToggle>(std::bind(&WExpandbox::expand, this), std::bind(&WExpandbox::collapse, this), !mCollapsed);
		mTitleLabel = mHeader->makeappend<WTitle>(mTitle);
	}

	void WTreeNode::selected()
	{
		Sheet* parent = mParent;
		while(parent->type() != WTree::cls())
			parent = parent->parent();

		parent->as<WTree>()->select(this);
	}

	WTree::WTree(Form* form, const Trigger& trigger)
		: Sheet(styleCls(), form)
		, mRootNode(nullptr)
		, mSelected(nullptr)
		, mOnSelected(trigger)
	{
		mType = cls();
	}

	WTree::~WTree()
	{}

	void WTree::select(WTreeNode* selected)
	{
		if(mSelected)
			mSelected->header()->updateState(ENABLED);

		selected->header()->updateState(ACTIVATED);
		mSelected = selected;

		/*Widget* node = selected;
		while(node != this)
		{
			if(node->type() == WTreeNode::cls())
			{
				node->as<WTreeNode>()->expand();
				for(auto& widget : node->parent()->contents())
					if(widget.get() != node)
						widget->as<WTreeNode>()->collapse();
			}
			node = node->parent();
		}*/

		mOnSelected(selected);
	}

	/*TreeNode::TreeNode(const string& image, const string& title, bool collapsed)
		: Expandbox(title, collapsed)
	{}*/

	TreeNode::TreeNode(Object* object, Tree* tree, bool collapsed)
		: Form(nullptr, "", [this]() { return make_unique<WTreeNode>(this, "", this->name()); })
		//: Form("formnode", "Form " + form->style(), [this]() { return make_unique<WTreeNode>(this, "", this->label()); })
		, mObject(object)
		, mTree(tree)
	{
		mTree->addNode(mObject, this);
	}

	TreeNode::~TreeNode()
	{
		mTree->removeNode(mObject, this);
	}

	Tree::Tree(std::function<void(Object*)> onSelected, Style* style)
		: Form(style ? style : styleCls(), "", [this]() { return make_unique<WTree>(this, std::bind(&Tree::selected, this, _1)); })
		, mOnSelected(onSelected)
	{}

	void Tree::selected(Widget* widget)
	{
		mOnSelected(widget->as<WTreeNode>()->form()->as<TreeNode>()->object());
	}

	void Tree::select(Object* object)
	{
		mWidget->as<WTree>()->select(mNodes[object]->widget()->as<WTreeNode>());
	}

	void Tree::addNode(Object* object, TreeNode* node)
	{
		mNodes[object] = node;
	}

	void Tree::removeNode(Object* object, TreeNode* node)
	{
		mNodes.erase(object);
	}
}
