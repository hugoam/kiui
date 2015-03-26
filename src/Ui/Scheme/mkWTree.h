//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WTREE_H
#define MK_WTREE_H

/* mk */
#include <Ui/Scheme/mkScheme.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Form/mkForm.h>

#include <Ui/Scheme/mkWExpandbox.h>

namespace mk
{
	class MK_UI_EXPORT _I_ WTreeNodeHeader : public WWrapButton, public Typed<WTreeNodeHeader>, public Styled<WTreeNodeHeader>
	{
	public:
		WTreeNodeHeader(const Trigger& trigger);

		using Typed<WTreeNodeHeader>::cls;
	};

	class MK_UI_EXPORT _I_ WTreeNodeBody : public Sheet, public Typed<WTreeNodeBody>, public Styled<WTreeNodeBody>
	{
	public:
		WTreeNodeBody();

		using Typed<WTreeNodeBody>::cls;
	};

	class MK_UI_EXPORT _I_ WTreeNodeToggle : public WToggle, public Typed<WTreeNodeToggle>, public Styled<WTreeNodeToggle>
	{
	public:
		WTreeNodeToggle(const Trigger& triggerOn, const Trigger& triggerOff, bool on);

		using Typed<WTreeNodeToggle>::cls;
	};

	class MK_UI_EXPORT _I_ WTreeNode : public WExpandbox, public Typed<WTreeNode>, public Styled<WTreeNode>
	{
	public:
		WTreeNode(Form* form, const string& image, const string& title, bool collapsed = false);

		void build();

		Widget* vappend(unique_ptr<Widget> widget);
		unique_ptr<Widget> vrelease(Widget* widget);

		void selected();

		using Typed<WTreeNode>::cls;
		using Styled<WTreeNode>::styleCls;
	};

	class MK_UI_EXPORT _I_ WTree : public ScrollSheet, public Typed<WTree, Widget>, public Styled<WTree>
	{
	public:
		WTree(Form* form, const Trigger& trigger);
		~WTree();

		void select(WTreeNode* node);

		using Typed<WTree, Widget>::cls;

	protected:
		WTreeNode* mRootNode;
		WTreeNode* mSelected;
		Trigger mOnSelected;
	};

	class MK_UI_EXPORT TreeNode : public Form
	{
	public:
		TreeNode(Object* object, Tree* tree, const string& name = "", bool collapsed = false);
		~TreeNode();

		Object* object() { return mObject; }

	protected:
		Object* mObject;
		Tree* mTree;
	};

	class MK_UI_EXPORT TableNode : public Form
	{
	public:
		TableNode(Object* object, Tree* tree, bool collapsed = false);
		~TableNode();

		Object* object() { return mObject; }

	protected:
		Object* mObject;
		Tree* mTree;
	};

	class MK_UI_EXPORT Tree : public Form, public Styled<Tree>
	{
	public:
		Tree(std::function<void(Object*)> onSelected, Style* style = nullptr);
		~Tree();

		void selected(Widget* widget);

		void select(Object* object);
		void addNode(Object* object, TreeNode* node);
		void removeNode(Object* object, TreeNode* node);

	protected:
		std::map<Object*, TreeNode*> mNodes;
		std::function<void(Object*)> mOnSelected;
	};
}

#endif
