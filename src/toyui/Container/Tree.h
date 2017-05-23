//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_TREE_H
#define TOY_TREE_H

/* toy */
#include <toyobj/Typed.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Container/ScrollSheet.h>

#include <toyui/Container/Expandbox.h>

namespace toy
{
	class TOY_UI_EXPORT TreeNodeHeader : public Object
	{
	public:
		static Type& cls() { static Type ty("TreeNodeHeader", ExpandboxHeader::cls()); return ty; }
	};

	class TOY_UI_EXPORT TreeNodeBody : public Object
	{
	public:
		static Type& cls() { static Type ty("TreeNodeBody", ExpandboxBody::cls()); return ty; }
	};

	class TOY_UI_EXPORT TreeNodeToggle : public Object
	{
	public:
		static Type& cls() { static Type ty("TreeNodeToggle", ExpandboxToggle::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT TreeNode : public Expandbox
	{
	public:
		TreeNode(Wedge& parent, const string& image, const string& title, bool collapsed = false, Type& type = cls());

		Tree& tree();

		virtual void handleAdd(Widget& widget);
		virtual void handleRemove(Widget& widget);

		void selected();

		static Type& cls() { static Type ty("TreeNode", Expandbox::cls()); return ty; }

	protected:
		string m_image;
		Icon* m_icon;
	};

	class _I_ TOY_UI_EXPORT Tree : public Container
	{
	public:
		Tree(Wedge& parent, const std::function<void (TreeNode&)>& onSelected = nullptr);

		void select(TreeNode& node);
		void expand(TreeNode& node, bool exclusive = false);
		void collapse();

		static Type& cls() { static Type ty("Tree", Container::cls()); return ty; }

	protected:
		TreeNode* m_rootNode;
		TreeNode* m_selected;
		std::function<void(TreeNode&)> m_onSelected;
	};
}

#endif
