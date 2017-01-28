//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Scheme/Tree.h>

#include <toyui/Widget/Widgets.h>

#include <toyui/Scheme/Expandbox.h>

#include <toyui/Frame/Frame.h>

using namespace std::placeholders;

namespace toy
{
	TreeNodeHeader::TreeNodeHeader(const Trigger& trigger)
		: WrapButton(nullptr, trigger, cls())
	{}

	TreeNodeBody::TreeNodeBody()
		: Sheet(cls())
	{}

	TreeNodeToggle::TreeNodeToggle(const Trigger& triggerOn, const Trigger& triggerOff, bool on)
		: Toggle(triggerOn, triggerOff, on, cls())
	{}

	TreeNode::TreeNode(const string& image, const string& title, bool collapsed, StyleType& type)
		: Expandbox(title, collapsed, false, type)
		, m_image(image)
	{
		m_header = &this->makeappend<TreeNodeHeader>(std::bind(&TreeNode::selected, this));
		m_container = &this->makeappend<TreeNodeBody>();

		m_expandButton = &m_header->emplace<TreeNodeToggle>(std::bind(&Expandbox::expand, this), std::bind(&Expandbox::collapse, this), !m_collapsed);
		if(!m_image.empty())
			m_icon = &m_header->emplace<Icon>(m_image);
		m_titleLabel = &m_header->emplace<Title>(m_title);

		m_expandButton->toggleState(DISABLED);
		m_container->hide();
	}

	TreeNode::~TreeNode()
	{}

	Widget& TreeNode::vappend(unique_ptr<Widget> widget)
	{
		if(m_container->count() == 0)
			m_expandButton->toggleState(DISABLED);

		return Expandbox::vappend(std::move(widget));
	}

	unique_ptr<Widget> TreeNode::vrelease(Widget& widget)
	{
		if(m_container->count() == 1)
			m_expandButton->toggleState(DISABLED);

		return Expandbox::vrelease(widget);
	}

	Tree& TreeNode::tree()
	{
		Sheet* parent = m_parent;
		while(&parent->type() != &Tree::cls())
			parent = parent->parent();
		return parent->as<Tree>();
	}

	void TreeNode::selected()
	{
		this->tree().select(*this);
	}

	Tree::Tree(const std::function<void(TreeNode&)>& onSelected)
		: ScrollSheet(cls())
		, m_rootNode(nullptr)
		, m_selected(nullptr)
		, m_onSelected(onSelected)
	{}

	Tree::~Tree()
	{}

	void Tree::select(TreeNode& selected)
	{
		if(m_selected)
			m_selected->header()->toggleState(ACTIVATED);

		selected.header()->toggleState(ACTIVATED);
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
