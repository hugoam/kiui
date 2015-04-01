//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Scheme/mkTree.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Form/mkWidgets.h>

#include <Ui/Scheme/mkExpandbox.h>

#include <Ui/Frame/mkFrame.h>

using namespace std::placeholders;

namespace mk
{
	TreeNodeHeader::TreeNodeHeader(const Trigger& trigger)
		: WrapButton(nullptr, styleCls(), trigger)
	{}

	TreeNodeBody::TreeNodeBody()
		: Sheet(styleCls())
	{}

	TreeNodeToggle::TreeNodeToggle(const Trigger& triggerOn, const Trigger& triggerOff, bool on)
		: Toggle(styleCls(), triggerOn, triggerOff, on)
	{}

	TreeNode::TreeNode(const string& image, const string& title, bool collapsed, Object* object)
		: Expandbox(title, collapsed, false)
		, mImage(image)
	{
		mType = cls();
		mStyle = styleCls();

		//mParent->as<Tree>()->addNode(mObject, this);

		mHeader = this->makeappend<TreeNodeHeader>(std::bind(&TreeNode::selected, this));
		mContainer = this->makeappend<TreeNodeBody>();

		mExpandButton = mHeader->emplace<TreeNodeToggle>(std::bind(&Expandbox::expand, this), std::bind(&Expandbox::collapse, this), !mCollapsed);
		if(!mImage.empty())
			mIcon = mHeader->emplace<Icon>(mImage);
		mTitleLabel = mHeader->emplace<Title>(mTitle);

		mExpandButton->toggleState(DISABLED);
		mContainer->hide();
	}

	TreeNode::~TreeNode()
	{
		//mParent->as<Tree>()->removeNode(mObject, this);
	}

	Widget* TreeNode::vappend(unique_ptr<Widget> widget)
	{
		if(mContainer->count() == 0)
			mExpandButton->toggleState(DISABLED);

		return Expandbox::vappend(std::move(widget));
	}

	unique_ptr<Widget> TreeNode::vrelease(Widget* widget)
	{
		if(mContainer->count() == 1)
			mExpandButton->toggleState(DISABLED);

		return Expandbox::vrelease(widget);
	}

	void TreeNode::selected()
	{
		Sheet* parent = mParent;
		while(parent->type() != Tree::cls())
			parent = parent->parent();

		parent->as<Tree>()->select(this);
	}

	Tree::Tree(const Trigger& trigger)
		: ScrollSheet(styleCls())
		, mRootNode(nullptr)
		, mSelected(nullptr)
		, mOnSelected(trigger)
	{
		mType = cls();
	}

	Tree::~Tree()
	{}

	void Tree::addNode(Object* object, TreeNode* node)
	{
		mNodes[object] = node;
	}

	void Tree::removeNode(Object* object, TreeNode* node)
	{
		mNodes.erase(object);
	}

	void Tree::select(Object* object)
	{
		this->select(mNodes[object]);
	}

	void Tree::select(TreeNode* selected)
	{
		if(mSelected)
			mSelected->header()->toggleState(ACTIVATED);

		selected->header()->toggleState(ACTIVATED);
		mSelected = selected;

		/*Widget* node = selected;
		while(node != this)
		{
			if(node->type() == TreeNode::cls())
			{
				node->as<TreeNode>()->expand();
				for(auto& widget : node->parent()->contents())
					if(widget.get() != node)
						widget->as<TreeNode>()->collapse();
			}
			node = node->parent();
		}*/

		if(mOnSelected)
			mOnSelected(selected);
	}
}
