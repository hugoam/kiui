//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_TREE_H
#define TOY_TREE_H

/* toy */
#include <toyobj/Type.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Container/ScrollSheet.h>

#include <toyui/Container/Expandbox.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT TreeNode : public Expandbox
	{
	public:
		TreeNode(Wedge& parent, const string& image, const string& title, bool collapsed = false, Type& type = cls());

		void selected();

		static Type& cls() { static Type ty("TreeNode", Expandbox::cls()); return ty; }

		static Type& Header() { static Type ty("TreeNodeHeader", Expandbox::Header()); return ty; }
		static Type& Switch() { static Type ty("TreeNodeToggle", Expandbox::Switch()); return ty; }
		static Type& Body() { static Type ty("TreeNodeBody", Expandbox::Body()); return ty; }

	protected:
		string m_image;
		Item* m_icon;
	};

	class _refl_ TOY_UI_EXPORT Tree : public Wedge
	{
	public:
		Tree(Wedge& parent, const std::function<void (TreeNode&)>& onSelected = nullptr);

		void select(TreeNode& node);
		void expand(TreeNode& node, bool exclusive = false);
		void collapse();

		static Type& cls() { static Type ty("Tree", Wedge::cls()); return ty; }

	protected:
		TreeNode* m_rootNode;
		TreeNode* m_selected;
		std::function<void(TreeNode&)> m_onSelected;
	};
}

#endif
