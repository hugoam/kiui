//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_WIDGET_H
#define TOY_WIDGET_H

/* toy */
#include <toyobj/Type.h>
#include <toyobj/String/String.h>
#include <toyobj/Util/Updatable.h>
#include <toyui/Forward.h>
#include <toyui/Frame/Frame.h>
#include <toyui/Input/InputDispatcher.h>
#include <toyui/Style/Style.h>

#include <functional>
#include <memory>

namespace toy
{
	enum _refl_ WidgetState : unsigned int
	{
		NOSTATE = 0,			// default state
		FOCUSED = 1 << 0,		// under input device focus
		TRIGGERED = 1 << 1,		// triggered by input device (e.g. pressed)
		ACTIVATED = 1 << 2,		// activated state
		SELECTED = 1 << 3,		// selected state
		DRAGGED = 1 << 4,		// dragged by input device
		DISABLED = 1 << 5,		// disabled state
		ACTIVE = 1 << 6,		// for the unique currently active widget
		CONTROL = 1 << 7,		// widget is in the control stack
		MODAL = 1 << 8			// widget is modal in the control stack
	};

	class _refl_ TOY_UI_EXPORT Widget : public TypeObject, public InputAdapter
	{
	public:
		Widget(Wedge& parent, Type& type = cls(), FrameType frameType = FRAME);
		Widget(Type& type = cls(), FrameType frameType = FRAME, Wedge* parent = nullptr);
		~Widget();

		inline Frame& frame() { return *m_frame; }

		void setContent(const string& content);

		virtual const string& tooltip() { static string str; return str; }
		virtual const string& label();

		virtual RootSheet& rootSheet();

		UiWindow& uiWindow();
		ControlSwitch& rootController();

		void show();
		void hide();

		virtual void destroyed() {}

		void bind(Wedge& parent, size_t index);
		void unbind();

		virtual void makeSolver();

		void destroyTree();
		void destroy();
		void extract();
		
		virtual void destroyz() { this->extract(); }

		template <class T>
		T* findContainer() { Widget* widget = this->findContainer(T::cls()); return widget ? &widget->template as<T>() : nullptr; }

		Widget* findContainer(Type& type);

		using Visitor = std::function<void(Widget&, bool& visit)>;
		virtual void visit(const Visitor& visitor);

		void updateStyle();

		void setStyle(Type& type, bool hard = true);
		void setStyle(Style& style, bool hard = true);

		Style& fetchStyle(Type& type);

		void toggleState(WidgetState state);

		void enableState(WidgetState state);
		void disableState(WidgetState state);

		void control(bool modal);
		void uncontrol(bool modal);

		virtual void active() {}
		virtual void inactive() {}

		Widget* pinpoint(DimFloat pos);
		Widget* pinpoint(DimFloat pos, const Frame::Filter& filter);

		virtual void dirtyLayout();

		virtual bool customDraw(Renderer& renderer) { UNUSED(renderer); return false; }

		void transformEvent(InputEvent& inputEvent);
		virtual InputReceiver* controlEvent(InputEvent& inputEvent);
		virtual InputReceiver* receiveEvent(InputEvent& inputEvent);

		void makeActive();

		void giveControl(InputReceiver& receiver, ControlMode mode, DeviceType device = DEVICE_ALL);
		void takeControl(ControlMode mode, DeviceType device = DEVICE_ALL);
		void yieldControl();

		virtual bool mouseEntered(MouseEvent& mouseEvent);
		virtual bool mouseLeaved(MouseEvent& mouseEvent);

		virtual bool mousePressed(MouseEvent& mouseEvent);
		virtual bool mouseReleased(MouseEvent& mouseEvent);

		using Callback = std::function<void(Widget&)>;

		static Type& cls() { static Type ty("Widget"); return ty; }

	public:
		_attr_ Wedge* m_parent;
		_attr_ Wedge* m_container;
		_attr_ size_t m_index;
		_attr_ _mut_ Style* m_style;
		/*_attr_*/ object_ptr<Frame> m_frame;
		_attr_ WidgetState m_state;

		Device* m_device;
	};

	class _refl_ TOY_UI_EXPORT Item : public Widget
	{
	public:
		Item(Wedge& parent, Type& type = cls());
		Item(Wedge& parent, const string& content, Type& type = cls());

		static Type& Control() { static Type ty("Control", Item::cls()); return ty; }
		static Type& Spacer() { static Type ty("Spacer", Widget::cls()); return ty; }
		static Type& Filler() { static Type ty("Filler", Item::Spacer()); return ty; }

		static Type& cls() { static Type ty("Item", Widget::cls()); return ty; }
	};
}

#endif // TOY_WIDGET_H
