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
		FOCUSED = 1 << 1,		// under input device focus
		TRIGGERED = 1 << 2,		// triggered by input device (e.g. pressed)
		ACTIVATED = 1 << 3,		// activated state
		SELECTED = 1 << 4,		// selected state
		DRAGGED = 1 << 5,		// dragged by input device
		DISABLED = 1 << 6,		// disabled state
		ACTIVE = 1 << 7,		// for the unique currently active widget
		CONTROL = 1 << 8,		// widget is in the control stack
		MODAL = 1 << 9			// widget is modal in the control stack
	};

	class _refl_ TOY_UI_EXPORT Widget : public TypeObject, public InputAdapter, public Updatable
	{
	public:
		Widget(Wedge& parent, Type& type = cls(), FrameType frameType = FRAME);
		Widget(Type& type = cls(), FrameType frameType = FRAME, Wedge* parent = nullptr);
		~Widget();

		_attr_ inline Wedge* parent() { return m_parent; }
		_attr_ inline Container* container() { return m_container; }
		_attr_ inline size_t index() { return m_index; }
		_attr_ inline Frame& frame() { return *m_frame; }
		_attr_ inline WidgetState state() { return m_state; }
		_attr_ _mut_ inline Style& style() { return *m_style; }

		inline Device* device() { return m_device; }

		void setIndex(size_t index) { m_index = index; }
		void setContainer(Container& container) { m_container = &container; }
		DrawFrame& content();

		_attr_ _mut_ const string& label();
		void setLabel(const string& label);

		_attr_ _mut_ Image* image();
		void setImage(Image* image);

		Image& findImage(const string& name);

		void setDevice(Device& device) { m_device = &device; }
		void resetDevice() { m_device = nullptr; }

		virtual const string& tooltip() { return sNullString; }
		virtual const string& contentlabel();

		virtual RootSheet& rootSheet();

		UiWindow& uiWindow();
		Context& context();
		ControlSwitch& rootController();

		void show();
		void hide();

		virtual void bound(RootSheet& rootSheet);
		virtual void unbound(RootSheet& rootSheet, bool destroy);

		void bind(Wedge& parent, size_t index);
		void unbind(bool destroy);

		object_ptr<Widget> extract();
		void destroy();

		template <class T>
		T* findContainer() { Widget* widget = this->findContainer(T::cls()); return widget ? &widget->template as<T>() : nullptr; }

		Widget* findContainer(Type& type);

		typedef std::function<bool(Widget&)> Visitor;

		virtual void visit(const Visitor& visitor);

		virtual void nextFrame(size_t tick, size_t delta);

		void updateStyle();

		void setStyle(Type& type, bool hard = true);
		void setStyle(Style& style, bool hard = true);

		Style& fetchStyle(Type& type);

		void toggleState(WidgetState state);

		void enableState(WidgetState state);
		void disableState(WidgetState state);
		void updateState();

		void markDirty();

		void control(bool modal);
		void uncontrol(bool modal);

		virtual void active() {}
		virtual void inactive() {}

		Widget* pinpoint(float x, float y);
		Widget* pinpoint(float x, float y, const Frame::Filter& filter);

		virtual void dirtyLayout();

		virtual bool customDraw(Renderer& renderer) { UNUSED(renderer); return false; }

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

		typedef std::function<void(Widget&)> Callback;

		void debugPrintDepth();

		static Type& cls() { static Type ty("Widget"); return ty; }

	protected:
		Wedge* m_parent;
		Container* m_container;
		size_t m_index;
		Style* m_style;
		object_ptr<Frame> m_frame;
		WidgetState m_state;

		Device* m_device;

		static string sNullString;
	};

	class _refl_ TOY_UI_EXPORT Item : public Widget
	{
	public:
		Item(Wedge& parent, Type& type = cls());

		static Type& cls() { static Type ty("Item", Widget::cls()); return ty; }
	};

	class _refl_ TOY_UI_EXPORT Control : public Item
	{
	public:
		Control(Wedge& parent, Type& type = cls());

		static Type& cls() { static Type ty("Control", Item::cls()); return ty; }
	};
}

#endif // TOY_WIDGET_H
