//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WTREE_H
#define MK_WTREE_H

/* mk */
#include <Object/Util/mkDispatch.h>
#include <Ui/Scheme/mkCollection.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Form/mkForm.h>

#include <Ui/Scheme/mkExpandbox.h>

namespace mk
{
	class MK_UI_EXPORT _I_ TreeNodeHeader : public WrapButton
	{
	public:
		TreeNodeHeader(const Trigger& trigger);

		static StyleType& cls() { static StyleType ty(WrapButton::cls()); return ty; }
	};

	class MK_UI_EXPORT _I_ TreeNodeBody : public Sheet
	{
	public:
		TreeNodeBody();

		static StyleType& cls() { static StyleType ty(Sheet::cls()); return ty; }
	};

	class MK_UI_EXPORT _I_ TreeNodeToggle : public Toggle
	{
	public:
		TreeNodeToggle(const Trigger& triggerOn, const Trigger& triggerOff, bool on);

		static StyleType& cls() { static StyleType ty(Toggle::cls()); return ty; }
	};

	class MK_UI_EXPORT EmptyTreeNodeToggle : public Object
	{
	public:
		static StyleType& cls() { static StyleType ty(TreeNodeToggle::cls()); return ty; }
	};

	class MK_UI_EXPORT _I_ TreeNode : public Expandbox
	{
	public:
		TreeNode(const string& image, const string& title, bool collapsed = false, Object* object = nullptr);
		~TreeNode();

		Object* object() { return mObject; }
		Tree* tree();

		Widget& vappend(unique_ptr<Widget> widget);
		unique_ptr<Widget> vrelease(Widget& widget);

		void selected();

		static StyleType& cls() { static StyleType ty(Expandbox::cls()); return ty; }

	protected:
		string mImage;
		Icon* mIcon;
		Object* mObject;
	};

	class MK_UI_EXPORT NodeDispatch : public HashDispatch<NodeDispatch, TreeNode*, unique_ptr<TreeNode>>
	{};

	template <class T>
	class AutoLeafNode : public TreeNode
	{
	public:
		AutoLeafNode(T* object)
			: TreeNode("", T::cls().name() + " " + object->name(), false, object)
			, mObject(object)
		{}

	protected:
		T* mObject;
	};

	template <class T, class T_Child>
	class AutoNode : public TreeNode, public VectorObserver<unique_ptr<T_Child>, T_Child>
	{
	public:
		AutoNode(T* object)
			: TreeNode("", object->type().name() + " " + object->name(), false, object)
			, VectorObserver<unique_ptr<T_Child>, T_Child>(object->contents())
			, mObject(object)
		{}

		void handleAdd(T_Child* object, size_t index)
		{
			this->vappend(NodeDispatch::dispatchup(this, Lref(object)));
		}

		void handleRemove(T_Child* object, size_t index)
		{
			this->vrelease(this->tree()->node(object));
		}

		void nextFrame(size_t tick, size_t delta)
		{
			Sheet::nextFrame(tick, delta);
			VectorObserver<unique_ptr<T_Child>, T_Child>::update(tick);
		}

	protected:
		T* mObject;
	};

	class MK_UI_EXPORT _I_ Tree : public ScrollSheet
	{
	public:
		Tree(const std::function<void (TreeNode*)>& onSelected = nullptr);
		~Tree();

		void select(TreeNode* node);

		TreeNode* node(Object* object);
		void select(Object* object);

		void addNode(TreeNode& node);
		void removeNode(TreeNode& node);

		static StyleType& cls() { static StyleType ty(ScrollSheet::cls()); return ty; }

	protected:
		TreeNode* mRootNode;
		TreeNode* mSelected;
		std::function<void(TreeNode*)> mOnSelected;
		std::map<Object*, TreeNode*> mNodes;
	};
}

#endif
