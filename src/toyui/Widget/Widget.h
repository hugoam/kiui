//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_WIDGET_H
#define TOY_WIDGET_H

/* toy */
#include <toyobj/Typed.h>
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
	enum _I_ WidgetState : unsigned int
	{
		NOSTATE = 0,
		HOVERED = 1 << 0,
		TRIGGERED = 1 << 1,
		ACTIVATED = 1 << 2,
		FOCUSED = 1 << 3,
		DISABLED = 1 << 4,
		PRESSED = 1 << 5,
		DRAGGED = 1 << 6,
		CONTROL = 1 << 7,
		MODAL = 1 << 8
	};

	class _I_ TOY_UI_EXPORT Widget : public TypeObject, public InputReceiver, public Updatable
	{
	public:
		Widget(Wedge& parent, Type& type = cls(), FrameType frameType = FRAME);
		Widget(Type& type = cls(), FrameType frameType = FRAME, Wedge* parent = nullptr);
		~Widget();

		_A_ inline Wedge* parent() { return m_parent; }
		_A_ inline Container* container() { return m_container; }
		_A_ inline size_t index() { return m_index; }
		_A_ inline Frame& frame() { return *m_frame; }
		_A_ inline WidgetState state() { return m_state; }
		_A_ _M_ inline Style& style() { return *m_style; }

		inline Device* device() { return m_device; }

		void setIndex(size_t index) { m_index = index; }
		void setContainer(Container& container) { m_container = &container; }
		DrawFrame& content();

		_A_ _M_ const string& label();
		void setLabel(const string& label);

		_A_ _M_ Image* image();
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

		void bind(Wedge& parent, size_t index, bool deferred = true);
		void unbind();

		unique_ptr<Widget> extract();

		void remove();
		void destroy();

		template <class T>
		T* findContainer() { Widget* widget = this->findContainer(T::cls()); return widget ? &widget->template as<T>() : nullptr; }

		Widget* findContainer(Type& type);

		typedef std::function<bool(Widget&)> Visitor;

		virtual void visit(const Visitor& visitor);

		virtual void nextFrame(size_t tick, size_t delta);
		virtual void render(Renderer& renderer, bool force);

		void updateStyle();

		void setStyle(Type& type, bool hard = true);
		void setStyle(Style& style, bool hard = true);

		Style& fetchStyle(Type& type);

		void toggleState(WidgetState state);

		void enableState(WidgetState state);
		void disableState(WidgetState state);
		void updateState();

		void markDirty();

		void control();
		void uncontrol();

		void modal();
		void unmodal();

		void activate();
		void deactivate();

		virtual void focused() {}
		virtual void unfocused() {}

		Widget* pinpoint(float x, float y);
		Widget* pinpoint(float x, float y, const Frame::Filter& filter);

		virtual bool customDraw(Renderer& renderer) { UNUSED(renderer); return false; }

		virtual InputReceiver* controlEvent(InputEvent& inputEvent);
		virtual InputReceiver* receiveEvent(InputEvent& inputEvent);
		virtual InputReceiver* propagateEvent(InputEvent& inputEvent);

		void giveControl(InputReceiver& receiver, ControlMode mode, DeviceType device = DEVICE_ALL);
		void takeControl(ControlMode mode, DeviceType device = DEVICE_ALL);
		void yieldControl();

		void mouseEntered(MouseEvent& mouseEvent);
		void mouseLeaved(MouseEvent& mouseEvent);

		void mousePressed(MouseEvent& mouseEvent);
		void mouseReleased(MouseEvent& mouseEvent);

		typedef std::function<void(Widget&)> Trigger;

		void debugPrintDepth();

		static Type& cls() { static Type ty("Widget"); return ty; }

	protected:
		Wedge* m_parent;
		Container* m_container;
		size_t m_index;
		Style* m_style;
		unique_ptr<Frame> m_frame;
		WidgetState m_state;

		Device* m_device;

		static string sNullString;
	};

	class _I_ TOY_UI_EXPORT Item : public Widget
	{
	public:
		Item(Wedge& parent, Type& type = cls());

		static Type& cls() { static Type ty("Item", Widget::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Control : public Item
	{
	public:
		Control(Wedge& parent, Type& type = cls());

		static Type& cls() { static Type ty("Control", Item::cls()); return ty; }
	};
}

#endif // TOY_WIDGET_H
