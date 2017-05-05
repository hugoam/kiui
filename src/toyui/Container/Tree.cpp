//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Container/Tree.h>

#include <toyui/Widget/Layout.h>

#include <toyui/Container/Expandbox.h>

#include <toyui/Frame/Frame.h>

namespace toy
{
	TreeNode::TreeNode(Wedge& parent, const string& image, const string& title, bool collapsed, Type& type)
		: Expandbox(parent, title, collapsed, false, type)
		, m_image(image)
	{
		m_header.setStyle(TreeNodeHeader::cls());
		m_toggle.setStyle(TreeNodeToggle::cls());
		m_container.setStyle(TreeNodeBody::cls());

		if(!m_image.empty())
		{
			m_icon = &m_header.emplace<Icon>(m_image);
			m_header.swap(1, 2);
		}

		m_toggle.enableState(DISABLED);
	}

	TreeNode::~TreeNode()
	{}

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

	Tree::~Tree()
	{}

	void Tree::select(TreeNode& selected)
	{
		if(m_selected)
			m_selected->header().toggleState(ACTIVATED);

		selected.header().toggleState(ACTIVATED);
		m_selected = &selected;

		/*Widget* node = selected;
		while(node != this)
		{
			if(node->type() == TreeNode::cls())
			{
				node->as<TreeNode>()->expand();
				for(auto& widget : node->parent()->contents())
					if(widget.get() != node)
						widget->as<TreeNode>()->collapse();
			}
			node = node->parent();
		}*/

		if(m_onSelected)
			m_onSelected(selected);
	}
}
