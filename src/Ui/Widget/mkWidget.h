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
		NOSTATE = 0,
		ENABLED = 1 << 0,
		HOVERED = 1 << 1,
		TRIGGERED = 1 << 2,
		ACTIVATED = 1 << 3,
		FOCUSED = 1 << 4,
		DISABLED = 1 << 5,
		PRESSED = 1 << 6,
		DRAGGED = 1 << 7,
		MODAL = 1 << 8
	};

	class MK_UI_EXPORT _I_ Widget : public TypeObject, public Typed<Widget>, public InputReceiver, public Updatable
	{
	public:
		Widget(Style* style, Form* form = nullptr);
		~Widget();

		_A_ inline Sheet* parent() { return mParent; }
		_A_ inline Frame* frame() { return mFrame.get(); }
		_A_ inline Form* form() { return mForm; }
		_A_ inline WidgetState state() { return mState; }
		_A_ _M_ inline Style* style() { return mStyle; }

		void setStyle(Style* style);

		virtual Sheet* clone(Sheet* parent);

		virtual Style* fetchOverride(Style* style);

		virtual FrameType frameType();
		virtual size_t zorder() { return 0; }

		virtual const string& name();
		virtual const string& label();
		virtual const string& image();
		virtual const string& tooltip();
		virtual Style* hoverCursor();

		virtual RootSheet* rootSheet();
		virtual InkTarget* inkTarget();

		UiWindow* uiWindow();

		virtual void build() {}

		virtual void show();
		virtual void hide();

		virtual void cleanup();

		void bind(Sheet* parent, size_t index);
		void rebind(Sheet* parent, size_t index);
		
		unique_ptr<Widget> unbind();
		unique_ptr<Widget> extract();

		void destroy();
		void detach();

		Widget* copy(Sheet* parent);

		void reset(Form* form);
		void reset(Style* style);

		void nextFrame(size_t tick, size_t delta);

		void toggleState(WidgetState);

		void markDirty();

		void activate();
		void deactivate();

		void hover();
		void unhover();

		void focus();
		void unfocus();

		void modal();
		void unmodal();

		Widget* copyTo(Sheet* sheet);

		virtual Widget* pinpoint(float x, float y, bool modal = false);

		Widget* prev();
		Widget* next();

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

		bool mouseWheel(float xPos, float yPos, float amount) { UNUSED(xPos); UNUSED(yPos); UNUSED(amount); return true; };

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

		typedef std::function<void(Widget*)> Trigger;

	protected:
		Sheet* mParent;
		Style* mStyle;
		unique_ptr<Frame> mFrame;
		WidgetState mState;

		Form* mForm;

		static string sNullString;
	};
}

#endif // MK_WIDGET_H_INCLUDED
