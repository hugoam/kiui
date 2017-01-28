//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_WTREE_H
#define TOY_WTREE_H

/* toy */
#include <toyobj/Util/Dispatch.h>
#include <toyui/Widget/Sheet.h>

#include <toyui/Scheme/Expandbox.h>

namespace toy
{
	class _I_ TOY_UI_EXPORT TreeNodeHeader : public WrapButton
	{
	public:
		TreeNodeHeader(const Trigger& trigger);

		static StyleType& cls() { static StyleType ty("TreeNodeHeader", WrapButton::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT TreeNodeBody : public Sheet
	{
	public:
		TreeNodeBody();

		static StyleType& cls() { static StyleType ty("TreeNodeBody", Sheet::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT TreeNodeToggle : public Toggle
	{
	public:
		TreeNodeToggle(const Trigger& triggerOn, const Trigger& triggerOff, bool on);

		static StyleType& cls() { static StyleType ty("TreeNodeToggle", Toggle::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT TreeNode : public Expandbox
	{
	public:
		TreeNode(const string& image, const string& title, bool collapsed = false, StyleType& type = cls());
		~TreeNode();

		Tree& tree();

		Widget& vappend(unique_ptr<Widget> widget);
		unique_ptr<Widget> vrelease(Widget& widget);

		void selected();

		static StyleType& cls() { static StyleType ty("TreeNode", Expandbox::cls()); return ty; }

	protected:
		string m_image;
		Icon* m_icon;
	};

	class _I_ TOY_UI_EXPORT Tree : public ScrollSheet
	{
	public:
		Tree(const std::function<void (TreeNode&)>& onSelected = nullptr);
		~Tree();

		void select(TreeNode& node);

		static StyleType& cls() { static StyleType ty("Tree", ScrollSheet::cls()); return ty; }

	protected:
		TreeNode* m_rootNode;
		TreeNode* m_selected;
		std::function<void(TreeNode&)> m_onSelected;
	};
}

#endif
