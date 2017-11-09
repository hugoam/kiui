//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_TREE_H
#define TOY_TREE_H

/* toy */
#include <toyobj/Type.h>
#include <toyobj/Store/Array.h>
#include <toyui/Container/Expandbox.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT TreeNode : public Expandbox
	{
	public:
		TreeNode(Wedge& parent, const StringVector& elements, bool collapsed = false, const Callback& onSelect = nullptr, const Callback& onUnselect = nullptr, Type& type = cls());

		void select();
		void unselect();

		static Type& cls() { static Type ty("TreeNode", Expandbox::cls()); return ty; }

		static Type& Header() { static Type ty("TreeNodeHeader", Expandbox::Header()); return ty; }
		static Type& Switch() { static Type ty("TreeNodeToggle", Expandbox::Switch()); return ty; }
		static Type& Body() { static Type ty("TreeNodeBody", Expandbox::Body()); return ty; }

	protected:
		Callback m_onSelect;
		Callback m_onUnselect;
	};

	class _refl_ TOY_UI_EXPORT Tree : public Wedge, public StoreObserver<TreeNode>
	{
	public:
		Tree(Wedge& parent);

		Array<TreeNode> m_selection;

		void handleAdd(TreeNode& node);
		void handleRemove(TreeNode& node);

		void expand(TreeNode& node, bool exclusive = false);
		void collapse();

		static Type& cls() { static Type ty("Tree", Wedge::cls()); return ty; }

	protected:
		TreeNode* m_rootNode;
	};
}

#endif
