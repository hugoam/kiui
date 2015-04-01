//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WTREE_H
#define MK_WTREE_H

/* mk */
#include <Ui/Widget/mkSheet.h>
#include <Ui/Form/mkForm.h>

#include <Ui/Scheme/mkExpandbox.h>

namespace mk
{
	class MK_UI_EXPORT _I_ TreeNodeHeader : public WrapButton, public Typed<TreeNodeHeader>, public Styled<TreeNodeHeader>
	{
	public:
		TreeNodeHeader(const Trigger& trigger);

		using Typed<TreeNodeHeader>::cls;
	};

	class MK_UI_EXPORT _I_ TreeNodeBody : public Sheet, public Typed<TreeNodeBody>, public Styled<TreeNodeBody>
	{
	public:
		TreeNodeBody();

		using Typed<TreeNodeBody>::cls;
	};

	class MK_UI_EXPORT _I_ TreeNodeToggle : public Toggle, public Typed<TreeNodeToggle>, public Styled<TreeNodeToggle>
	{
	public:
		TreeNodeToggle(const Trigger& triggerOn, const Trigger& triggerOff, bool on);

		using Typed<TreeNodeToggle>::cls;
	};

	class MK_UI_EXPORT WEmptyTreeNodeToggle : public Object, public Typed<WEmptyTreeNodeToggle>, public Styled<WEmptyTreeNodeToggle>
	{};

	class MK_UI_EXPORT _I_ TreeNode : public Expandbox, public Typed<TreeNode>, public Styled<TreeNode>
	{
	public:
		TreeNode(const string& image, const string& title, bool collapsed = false, Object* object = nullptr);
		~TreeNode();

		Object* object() { return mObject; }

		Widget* vappend(unique_ptr<Widget> widget);
		unique_ptr<Widget> vrelease(Widget* widget);

		void selected();

		using Typed<TreeNode>::cls;
		using Styled<TreeNode>::styleCls;

	protected:
		string mImage;
		Icon* mIcon;
		Object* mObject;
	};

	class MK_UI_EXPORT _I_ Tree : public ScrollSheet, public Typed<Tree, Widget>, public Styled<Tree>
	{
	public:
		Tree(const Trigger& trigger = nullptr);
		~Tree();

		void select(TreeNode* node);

		void select(Object* object);
		void addNode(Object* object, TreeNode* node);
		void removeNode(Object* object, TreeNode* node);

		using Typed<Tree, Widget>::cls;
		using Styled<Tree>::styleCls;

	protected:
		TreeNode* mRootNode;
		TreeNode* mSelected;
		Trigger mOnSelected;
		std::map<Object*, TreeNode*> mNodes;
	};
}

#endif
