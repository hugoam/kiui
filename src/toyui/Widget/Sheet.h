//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_SHEET_H
#define TOY_SHEET_H

/* toy */
#include <toyobj/Typed.h>
#include <toyui/Forward.h>
#include <toyui/Widget/Widget.h>
#include <toyui/Frame/Stripe.h>

namespace toy
{
	class _I_ TOY_UI_EXPORT Wedge : public Widget
	{
	public:
		Wedge(Wedge& parent, Type& type = cls(), FrameType frameType = STRIPE);
		Wedge(Type& type = cls(), FrameType frameType = STRIPE);
		~Wedge();

		inline Stripe& stripe() { return m_frame->as<Stripe>(); }
		inline const std::vector<Widget*>& contents() { return m_contents; }
		inline size_t count() { return m_contents.size(); }

		inline Widget& at(size_t index) { return *m_contents.at(index); }

		virtual void nextFrame(size_t tick, size_t delta);
		virtual void render(Renderer& renderer, bool force);

		virtual void visit(const Visitor& visitor);

		void push(Widget& widget, bool deferred = true);
		void insert(Widget& widget, size_t index, bool deferred = true);
		void remove(Widget& widget);

		void reindex(size_t from);
		void move(size_t from, size_t to);
		void swap(size_t from, size_t to);

		static Type& cls() { static Type ty("Wedge", Widget::cls()); return ty; }

	protected:
		std::vector<Widget*> m_contents;
	};

	class _I_ TOY_UI_EXPORT Container : public Wedge
	{
	public:
		Container(Wedge& parent, Type& type = cls(), FrameType frameType = STRIPE);
		Container(Type& type = cls(), FrameType frameType = STRIPE);
		~Container();

		Container(const Container& other) = delete;

		inline const std::vector<unique_ptr<Widget>>& containerContents() { return m_containerContents; }

		virtual Container& emplaceContainer() { return *this; }

		virtual void handleAdd(Widget& widget) {}
		virtual void handleRemove(Widget& widget) {}

		Widget& insert(unique_ptr<Widget> widget, size_t index);
		Widget& append(unique_ptr<Widget> widget);
		unique_ptr<Widget> release(Widget& widget);

		void clear();

		template <class T, class... Args>
		inline T& emplace(Args&&... args)
		{
			Container& container = this->emplaceContainer();
			return this->append(make_unique<T>(container.as<Wedge>(), std::forward<Args>(args)...)).template as<T>();
		}

		template <class T, class... Args>
		inline T& emplaceLocal(Wedge& container, Args&&... args)
		{
			return this->append(make_unique<T>(container, std::forward<Args>(args)...)).template as<T>();
		}

		static Type& cls() { static Type ty("Container", Wedge::cls()); return ty; }

	protected:
		std::vector<unique_ptr<Widget>> m_containerContents;
	};

	class _I_ TOY_UI_EXPORT WrapControl : public Container
	{
	public:
		WrapControl(Wedge& parent, Type& type = cls());

		static Type& cls() { static Type ty("WrapControl", Container::cls()); return ty; }
	};

	class TOY_UI_EXPORT Spacer : public Widget
	{
	public:
		Spacer(Wedge& parent, Type& type = cls());

		static Type& cls() { static Type ty("Spacer", Widget::cls()); return ty; }
	};

	class TOY_UI_EXPORT Filler : public Spacer
	{
	public:
		Filler(Wedge& parent);

		static Type& cls() { static Type ty("Filler", Spacer::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Decal : public Wedge
	{
	public:
		Decal(Wedge& parent, Type& type = cls());

		static Type& cls() { static Type ty("Decal", Wedge::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Overlay : public Container
	{
	public:
		Overlay(Wedge& parent, Type& type = cls());

		static Type& cls() { static Type ty("Overlay", Container::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT GridSheet : public Container
	{
	public:
		GridSheet(Wedge& parent, Dimension dim, Type& type = cls());

		Dimension dim() { return m_dim; }

		virtual void leftDragStart(MouseEvent& mouseEvent);
		virtual void leftDrag(MouseEvent& mouseEvent);

		virtual void gridResized(Frame& first, Frame& second) { UNUSED(first); UNUSED(second); }

		static Type& cls() { static Type ty("GridSheet", Container::cls()); return ty; }

	protected:
		Dimension m_dim;
		Frame* m_dragPrev;
		Frame* m_dragNext;
	};
}

#endif // TOY_SHEET_H
