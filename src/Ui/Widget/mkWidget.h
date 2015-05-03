//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WIDGET_H_INCLUDED
#define MK_WIDGET_H_INCLUDED

/* mk */
#include <Object/mkTyped.h>
#include <Object/String/mkString.h>
#include <Object/Util/mkUpdatable.h>
#include <Ui/mkUiForward.h>
#include <Ui/Frame/mkUibox.h>
#include <Ui/Input/mkInputDispatcher.h>
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
		MODAL = 1 << 8
	};

	class MK_UI_EXPORT _I_ Widget : public TypeObject, public InputReceiver, public Updatable
	{
	public:
		Widget(FrameType frameType = FRAME);
		~Widget();

		_A_ inline Sheet* parent() { return mParent; }
		_A_ inline Frame& frame() { return *mFrame.get(); }
		_A_ inline WidgetState state() { return mState; }
		_A_ _M_ inline Style& style() { return *mStyle; }

		void setStyle(Style* style);

		virtual unique_ptr<Widget> clone() { return make_unique<Widget>(); }

		virtual Style& fetchOverride(Style& style);

		virtual const string& name() { return sNullString; }
		virtual const string& label() { return sNullString; }
		virtual const string& tooltip() { return sNullString; }
		virtual const string& dockid() { return sNullString; }
		virtual Style* hoverCursor() { return nullptr; }
		virtual Image* image(); // { return sNullString; }

		virtual const string& contentlabel() { return this->label(); }

		virtual RootSheet& rootSheet();

		UiWindow& uiWindow();

		virtual void show();
		virtual void hide();

		virtual void cleanup();

		virtual void bind(Sheet* parent, size_t index);
		virtual void rebind(Sheet* parent, size_t index);
		
		unique_ptr<Widget> unbind();
		unique_ptr<Widget> extract();

		void remove();
		void destroy();
		void detach();

		void resetStyle(Style* style);
		void resetSkin(Style* style);

		void nextFrame(size_t tick, size_t delta);

		void toggleState(WidgetState);

		void markDirty();

		void activate();
		void deactivate();

		virtual void focused() {}
		virtual void unfocused() {}

		void hover();
		void unhover();

		void focus();
		void unfocus();

		void modal();
		void unmodal();

		Widget* copyTo(Sheet* sheet);

		virtual Widget* pinpoint(float x, float y, bool modal = false);

		Widget& prev();
		Widget& next();

		bool contains(Widget* widget);

		InputReceiver* propagateMouse(float x, float y);
		InputReceiver* propagateKey();

		bool keyUp(KeyCode code, char c) { UNUSED(code); UNUSED(c); return true; };
		bool keyDown(KeyCode code, char c) { UNUSED(code); UNUSED(c); return true; };

		bool mouseEntered(float x, float y);
		bool mouseLeaved(float x, float y);

		//bool mouseMoved(float xPos, float yPos, float xDif, float yDif) { UNUSED(xPos); UNUSED(yPos); UNUSED(xDif); UNUSED(yDif); return true; };
		//bool mousePressed(float xPos, float yPos, MouseButton button) { UNUSED(xPos); UNUSED(yPos); UNUSED(button); return false; };
		//bool mouseReleased(float xPos, float yPos, MouseButton button) { UNUSED(xPos); UNUSED(yPos); UNUSED(button); return false; };

		bool mouseMoved(float xPos, float yPos, float xDif, float yDif);
		bool mousePressed(float xPos, float yPos, MouseButton button);
		bool mouseReleased(float xPos, float yPos, MouseButton button);

		bool mouseWheel(float xPos, float yPos, float amount) { UNUSED(xPos); UNUSED(yPos); UNUSED(amount); return false; };

		bool leftPressed(float xPos, float yPos) { UNUSED(xPos); UNUSED(yPos); return true; };
		bool rightPressed(float xPos, float yPos) { UNUSED(xPos); UNUSED(yPos); return true; };

		bool leftClick(float xPos, float yPos) { UNUSED(xPos); UNUSED(yPos); return true; };
		bool rightClick(float xPos, float yPos) { UNUSED(xPos); UNUSED(yPos); return true; };

		bool rightDragStart(float xPos, float yPos) { UNUSED(xPos); UNUSED(yPos); return true; };
		bool rightDrag(float xPos, float yPos, float xDif, float yDif) { UNUSED(xPos); UNUSED(yPos); UNUSED(xDif); UNUSED(yDif); return true; };
		bool rightDragEnd(float xPos, float yPos) { UNUSED(xPos); UNUSED(yPos); return true; };

		bool leftDragStart(float xPos, float yPos) { UNUSED(xPos); UNUSED(yPos); return true; };
		bool leftDrag(float xPos, float yPos, float xDif, float yDif) { UNUSED(xPos); UNUSED(yPos); UNUSED(xDif); UNUSED(yDif); return true; };
		bool leftDragEnd(float xPos, float yPos) { UNUSED(xPos); UNUSED(yPos); return true; };

		typedef std::function<void(Widget&)> Trigger;

		static StyleType& cls() { static StyleType ty("Widget"); return ty; }

	protected:
		Sheet* mParent;
		Style* mStyle;
		unique_ptr<Frame> mFrame;
		WidgetState mState;

		static string sNullString;
	};

	class MK_UI_EXPORT Control : public Widget
	{
	public:
		Control();

		static StyleType& cls() { static StyleType ty("Control"); return ty; }
	};
}

#endif // MK_WIDGET_H_INCLUDED
