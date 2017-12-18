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
		TreeNode(const Params& params, const StringVector& elements, bool collapsed = false, const Callback& onSelect = nullptr, const Callback& onUnselect = nullptr);

		void select();
		void unselect();

		struct Styles
		{
			Style treenode = { cls<TreeNode>(), Expandbox::styles().expandbox };
			Style header = { "TreeNodeHeader", Expandbox::styles().header };
			Style toggle = { "TreeNodeHeader", Expandbox::styles().toggle };
			Style body = { "TreeNodeHeader", Expandbox::styles().body, Args{ { &Layout::m_padding, BoxFloat{ 18.f, 0.f, 0.f, 0.f } },{ &Layout::m_spacing, DimFloat(0.f) } } };
		};
		static Styles& styles() { static Styles styles; return styles; }

	protected:
		Callback m_onSelect;
		Callback m_onUnselect;
	};

	class _refl_ TOY_UI_EXPORT Tree : public Wedge, public StoreObserver<TreeNode>
	{
	public:
		Tree(const Params& params);

		Array<TreeNode> m_selection;

		void handleAdd(TreeNode& node);
		void handleRemove(TreeNode& node);

		void expand(TreeNode& node, bool exclusive = false);
		void collapse();

	protected:
		TreeNode* m_rootNode;
	};
}

#endif
