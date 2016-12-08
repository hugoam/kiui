//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WIDGET_H
#define MK_WIDGET_H

/* mk */
#include <Object/mkTyped.h>
#include <Object/String/mkString.h>
#include <Object/Util/mkUpdatable.h>
#include <Ui/mkUiForward.h>
#include <Ui/Frame/mkUibox.h>
#include <Ui/Input/mkInputDispatcher.h>
#include <Ui/Input/mkInputDevice.h>
#include <Ui/Style/mkStyle.h>

#include <functional>
#include <memory>

namespace mk
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

	class MK_UI_EXPORT _I_ Widget : public TypeObject, public InputWidget, public Updatable
	{
	public:
		Widget(StyleType& type = cls(), FrameType frameType = FRAME);
		~Widget();

		_A_ inline Sheet* parent() { return m_parent; }
		_A_ inline Frame& frame() { return *m_frame; }
		_A_ inline WidgetState state() { return m_state; }
		_A_ _M_ inline Style& style() { return *m_style; }
		_A_ inline Device* device() { return m_device; }

		const string& label();
		void setLabel(const string& label);

		Image* image();
		void setImage(Image* image);

		void setStyle(Style& style);

		void setDevice(Device& device) { m_device = &device; }

		virtual unique_ptr<Widget> clone() { return make_unique<Widget>(); }

		virtual Style& fetchOverride(Style& style);

		virtual const string& name() { return sNullString; }
		virtual const string& tooltip() { return sNullString; }
		virtual const string& dockid() { return sNullString; }
		virtual Style* hoverCursor() { return nullptr; }

		virtual const string& contentlabel();

		virtual RootSheet& rootSheet();

		UiWindow& uiWindow();

		void show();
		void hide();

		virtual void cleanup();

		virtual void bind(Sheet& parent, size_t index);
		virtual void rebind(Sheet& parent, size_t index);

		virtual void bound() {}
		
		unique_ptr<Widget> unbind();
		unique_ptr<Widget> extract();

		void remove();
		void destroy();
		void detach();

		void resetStyle(Style& style);
		void resetSkin(Style& style);

		void nextFrame(size_t tick, size_t delta) { UNUSED(tick); UNUSED(delta); }

		void toggleState(WidgetState state);

		void markDirty();

		void hover();
		void unhover();

		void control();
		void uncontrol();

		void modal();
		void unmodal();

		void activate();
		void deactivate();

		virtual void focused() {}
		virtual void unfocused() {}

		virtual Widget* pinpoint(float x, float y);

		Widget& prev();
		Widget& next();

		bool contains(Widget& widget);

		virtual void customDraw(Renderer& renderer) { UNUSED(renderer); }

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
		Style* m_style;
		unique_ptr<Frame> m_frame;
		WidgetState m_state;

		Device* m_device;

		static string sNullString;
	};

	class MK_UI_EXPORT Control : public Widget
	{
	public:
		Control(StyleType& type = cls());

		static StyleType& cls() { static StyleType ty("Control"); return ty; }
	};
}

#endif // MK_WIDGET_H
