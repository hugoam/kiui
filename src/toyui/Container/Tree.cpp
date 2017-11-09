//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Container/Tree.h>

#include <toyui/Container/Expandbox.h>

namespace toy
{
	TreeNode::TreeNode(Wedge& parent, const StringVector& elements, bool collapsed, const Callback& onSelect, const Callback& onUnselect, Type& type)
		: Expandbox(parent, elements, collapsed, type)
		, m_onSelect(onSelect)
		, m_onUnselect(onUnselect)
	{
		m_header.setStyle(TreeNode::Header());
		m_toggle.setStyle(TreeNode::Switch());
		m_body.setStyle(TreeNode::Body());
		
		m_header.m_trigger = [this](Widget&) { this->findContainer<Tree>()->m_selection.select(*this); };
		m_header.m_triggerShift = [this](Widget&) { this->findContainer<Tree>()->m_selection.swap(*this); };
	}

	void TreeNode::select()
	{
		this->enableState(SELECTED);
		m_onSelect(*this);
	}

	void TreeNode::unselect()
	{
		this->disableState(SELECTED);
		m_onUnselect(*this);
	}

	Tree::Tree(Wedge& parent)
		: Wedge(parent, cls())
		, m_rootNode(nullptr)
	{
		m_selection.observe(*this);
	}

	void Tree::handleAdd(TreeNode& node)
	{
		node.select();
	}

	void Tree::handleRemove(TreeNode& node)
	{
		node.unselect();
	}

	void Tree::expand(TreeNode& target, bool exclusive)
	{
		if(exclusive)
			this->collapse();

		TreeNode* node = &target;
		while(node)
		{
			node->expand();
			node = node->m_parent->findContainer<TreeNode>();
		}
	}

	void Tree::collapse()
	{
		m_rootNode->visit([](Widget& widget, bool&) {
			if(&widget.m_type == &TreeNode::cls())
				widget.as<TreeNode>().collapse();
		});
	}
}
