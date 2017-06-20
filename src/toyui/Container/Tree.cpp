//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Container/Tree.h>

#include <toyui/Container/Layout.h>

#include <toyui/Container/Expandbox.h>

#include <toyui/Frame/Frame.h>

namespace toy
{
	TreeNode::TreeNode(Wedge& parent, const string& image, const string& title, bool collapsed, Type& type)
		: Expandbox(parent, title, collapsed, type)
		, m_image(image)
	{
		m_header.setStyle(TreeNodeHeader::cls());
		m_toggle.setStyle(TreeNodeToggle::cls());
		m_container.setStyle(TreeNodeBody::cls());
		
		m_header.setTrigger([this](Widget&) { this->selected(); });

		if(!m_image.empty())
		{
			m_icon = &m_header.emplace<Icon>(m_image);
			m_header.swap(1, 2);
		}

		m_toggle.enableState(DISABLED);
	}

	void TreeNode::handleAdd(Widget& widget)
	{
		m_toggle.disableState(DISABLED);
	}

	void TreeNode::handleRemove(Widget& widget)
	{
		if(m_container.containerContents().size() == 1)
			m_toggle.disableState(DISABLED);
	}

	Tree& TreeNode::tree()
	{
		Wedge* parent = m_parent;
		while(&parent->type() != &Tree::cls())
			parent = parent->parent();
		return parent->as<Tree>();
	}

	void TreeNode::selected()
	{
		this->tree().select(*this);
	}

	Tree::Tree(Wedge& parent, const std::function<void(TreeNode&)>& onSelected)
		: Container(parent, cls())
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
		m_rootNode->visit([](Widget& widget) {
			if(&widget.type() == &TreeNode::cls())
				widget.as<TreeNode>().collapse();
			return true;
		});
	}
}
