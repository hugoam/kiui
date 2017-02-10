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
#include <toyui/Frame/Uibox.h>
#include <toyui/Input/InputDispatcher.h>
#include <toyui/Input/InputDevice.h>
#include <toyui/Style/Style.h>

#include <functional>
#include <memory>

namespace toy
{
	enum _I_ WidgetState : unsigned int
	{
		UNBOUND = 0,
		BOUND = 1 << 0,
		HOVERED = 1 << 1,
		TRIGGERED = 1 << 2,
		ACTIVATED = 1 << 3,
		FOCUSED = 1 << 4,
		DISABLED = 1 << 5,
		PRESSED = 1 << 6,
		DRAGGED = 1 << 7,
		CONTROL = 1 << 8,
		MODAL = 1 << 9
	};

	class _I_ TOY_UI_EXPORT Widget : public TypeObject, public InputWidget, public Updatable
	{
	public:
		Widget(StyleType& type = cls(), FrameType frameType = FRAME);
		~Widget();

		_A_ inline Sheet* parent() { return m_parent; }
		_A_ inline size_t index() { return m_index; }
		_A_ inline Frame& frame() { return *m_frame; }
		_A_ inline WidgetState state() { return m_state; }
		_A_ _M_ inline Style& style() { return *m_style; }
		inline Device* device() { return m_device; }

		void setIndex(size_t index) { m_index = index; }

		DrawFrame& content();

		const string& label();
		void setLabel(const string& label);

		Image* image();
		void setImage(Image* image);

		void setDevice(Device& device) { m_device = &device; }
		void resetDevice() { m_device = nullptr; }

		virtual unique_ptr<Widget> clone() { return make_unique<Widget>(); }

		virtual Style& fetchOverride(Style& style);

		virtual const string& name() { return sNullString; }
		virtual const string& tooltip() { return sNullString; }
		virtual const string& dockid() { return sNullString; }
		virtual Style* hoverCursor() { return nullptr; }

		virtual const string& contentlabel();

		virtual RootSheet& rootSheet();

		UiWindow& uiWindow();
		Context& context();

		void show();
		void hide();

		virtual void bind(Sheet& parent, size_t index);
		virtual void unbind();

		virtual void bound() {}
		virtual void unbound() {}

		unique_ptr<Widget> detach();
		unique_ptr<Widget> extract();

		void remove();
		void destroy();

		void updateStyle();
		void resetStyle();
		void resetStyle(Style& style);
		void resetSkin(Style& style);

		virtual void nextFrame(size_t tick, size_t delta);
		virtual void render(Renderer& renderer);

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

		virtual Widget* pinpoint(float x, float y);

		virtual bool customDraw(Renderer& renderer) { UNUSED(renderer); return false; }

		InputReceiver* controlEvent(InputEvent& inputEvent);
		InputReceiver* propagateEvent(InputEvent& inputEvent);

		void mouseEntered(MouseEvent& mouseEvent);
		void mouseLeaved(MouseEvent& mouseEvent);

		void mousePressed(MouseEvent& mouseEvent);
		void mouseReleased(MouseEvent& mouseEvent);

		typedef std::function<void(Widget&)> Trigger;

		static StyleType& cls() { static StyleType ty("Widget"); return ty; }

	protected:
		Sheet* m_parent;
		size_t m_index;
		Style* m_style;
		size_t d_styleStamp;
		unique_ptr<Frame> m_frame;
		WidgetState m_state;

		Device* m_device;

		static string sNullString;
	};

	class TOY_UI_EXPORT Control : public Widget
	{
	public:
		Control(StyleType& type = cls());

		static StyleType& cls() { static StyleType ty("Control"); return ty; }
	};
}

#endif // TOY_WIDGET_H
