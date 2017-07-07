//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Container/Tree.h>

#include <toyui/Container/Expandbox.h>

namespace toy
{
	TreeNode::TreeNode(Wedge& parent, const string& image, const string& title, bool collapsed, Type& type)
		: Expandbox(parent, title, collapsed, type)
		, m_image(image)
	{
		m_header.setStyle(TreeNode::Header());
		m_toggle.setStyle(TreeNode::Switch());
		m_body.setStyle(TreeNode::Body());
		
		m_header.setTrigger([this](Widget&) { this->selected(); });

		if(!m_image.empty())
		{
			m_icon = &m_header.emplace<Item>(m_image);
			m_header.swap(1, 2);
		}

		//m_toggle.enableState(DISABLED);
	}

	void TreeNode::selected()
	{
		this->findContainer<Tree>()->select(*this);
	}

	Tree::Tree(Wedge& parent, const std::function<void(TreeNode&)>& onSelected)
		: Wedge(parent, cls())
		, m_rootNode(nullptr)
		, m_selected(nullptr)
		, m_onSelected(onSelected)
	{}

	void Tree::select(TreeNode& selected)
	{
		if(m_selected)
			m_selected->header().disableState(SELECTED);

		selected.header().enableState(SELECTED);
		m_selected = &selected;

		if(m_onSelected)
			m_onSelected(selected);
	}

	void Tree::expand(TreeNode& target, bool exclusive)
	{
		if(exclusive)
			this->collapse();

		TreeNode* node = &target;
		while(node)
		{
			node->expand();
			node = node->parent()->findContainer<TreeNode>();
		}
	}

	void Tree::collapse()
	{
		m_rootNode->visit([](Widget& widget, bool&) {
			if(&widget.type() == &TreeNode::cls())
				widget.as<TreeNode>().collapse();
		});
	}
}
