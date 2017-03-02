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
	class _I_ TOY_UI_EXPORT Piece : public Widget
	{
	public:
		Piece(Piece& parent, Type& type = cls(), FrameType frameType = STRIPE);
		Piece(Type& type = cls(), FrameType frameType = STRIPE);
		~Piece();

		inline Stripe& stripe() { return m_frame->as<Stripe>(); }
		inline const std::vector<Widget*>& contents() { return m_contents; }
		inline size_t count() { return m_contents.size(); }

		inline Widget& at(size_t index) { return *m_contents.at(index); }

		virtual void nextFrame(size_t tick, size_t delta);
		virtual void render(Renderer& renderer, bool force);

		virtual void visit(const Visitor& visitor);

		void push(Widget& widget, bool deferred = true);
		void remove(Widget& widget);

		void reindex(size_t from);
		void swap(size_t from, size_t to);

		static Type& cls() { static Type ty("Piece", Widget::cls()); return ty; }

	protected:
		std::vector<Widget*> m_contents;
	};

	class _I_ TOY_UI_EXPORT Container : public Piece
	{
	public:
		Container(Piece& parent, Type& type = cls(), FrameType frameType = STRIPE);
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
			return this->append(make_unique<T>(container.as<Piece>(), std::forward<Args>(args)...)).template as<T>();
		}

		template <class T, class... Args>
		inline T& emplaceLocal(Piece& container, Args&&... args)
		{
			return this->append(make_unique<T>(container, std::forward<Args>(args)...)).template as<T>();
		}

		static Type& cls() { static Type ty("Container", Piece::cls()); return ty; }

	protected:
		std::vector<unique_ptr<Widget>> m_containerContents;
	};

	class _I_ TOY_UI_EXPORT WrapControl : public Container
	{
	public:
		WrapControl(Piece& parent, Type& type = cls());

		static Type& cls() { static Type ty("WrapControl", Container::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT WideControl : public WrapControl
	{
	public:
		WideControl(Piece& parent, Type& type = cls());

		static Type& cls() { static Type ty("WideControl", WrapControl::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Board : public Container
	{
	public:
		Board(Piece& parent, Type& type = cls());

		static Type& cls() { static Type ty("Board", Container::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Line : public Container
	{
	public:
		Line(Piece& parent, Type& type = cls());

		static Type& cls() { static Type ty("Line", Container::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Div : public Container
	{
	public:
		Div(Piece& parent, Type& type = cls());

		static Type& cls() { static Type ty("Div", Container::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Stack : public Container
	{
	public:
		Stack(Piece& parent, Type& type = cls(), FrameType frameType = STRIPE);

		static Type& cls() { static Type ty("Stack", Container::cls()); return ty; }
	};

	class TOY_UI_EXPORT Spacer : public Widget
	{
	public:
		Spacer(Piece& parent, Type& type = cls());

		static Type& cls() { static Type ty("Spacer", Widget::cls()); return ty; }
	};

	class TOY_UI_EXPORT Filler : public Spacer
	{
	public:
		Filler(Piece& parent);

		static Type& cls() { static Type ty("Filler", Spacer::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Layout : public Board
	{
	public: 
		Layout(Piece& parent, Type& type = cls());

		static Type& cls() { static Type ty("Layout", Board::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Decal : public Piece
	{
	public:
		Decal(Piece& parent, Type& type = cls());

		static Type& cls() { static Type ty("Decal", Piece::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Overlay : public Container
	{
	public:
		Overlay(Piece& parent, Type& type = cls());

		static Type& cls() { static Type ty("Overlay", Container::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Sheet : public Container
	{
	public:
		Sheet(Piece& parent, Type& type = cls());

		static Type& cls() { static Type ty("Sheet", Container::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT GridSheet : public Container
	{
	public:
		GridSheet(Piece& parent, Dimension dim, Type& type = cls());

		void leftDragStart(MouseEvent& mouseEvent);
		void leftDrag(MouseEvent& mouseEvent);
		void leftDragEnd(MouseEvent& mouseEvent);

		virtual void gridResized(Frame& first, Frame& second) { UNUSED(first); UNUSED(second); }

		static Type& cls() { static Type ty("GridSheet", Container::cls()); return ty; }

	protected:
		Dimension m_dim;
		Widget* m_resizing;
	};
}

#endif // TOY_SHEET_H
