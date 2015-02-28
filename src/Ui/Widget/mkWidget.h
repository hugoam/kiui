//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WIDGET_H_INCLUDED
#define MK_WIDGET_H_INCLUDED

/* mk */
#include <Object/mkTyped.h>
#include <Object/String/mkString.h>
#include <Object/Util/mkUpdatable.h>
#include <Object/Store/mkRegistry.h>
#include <Ui/mkUiForward.h>
#include <Ui/Frame/mkUibox.h>
#include <Ui/Input/mkInputDispatcher.h>

#include <functional>
#include <memory>

namespace mk
{
	enum WidgetState : unsigned short
	{
		ENABLED = 0,
		HOVERED = 1,
		TRIGGERED = 2,
		ACTIVATED = 3,
		ACTIVATED_HOVERED = 4,
		FOCUSED = 5,
		DISABLED = 6
	};

	class MK_UI_EXPORT _I_ Widget : public TypeObject, public Typed<Widget>, public InputReceiver, public Updatable
	{
	public:
		Widget(string clas, Form* form = nullptr);
		~Widget();

		_A_ Sheet* parent() { return mParent; }
		_A_ string clas() { return mClas; }
		_A_ Frame* frame() { return mFrame.get(); }
		_A_ InkStyle* skin();
		_A_ LayoutStyle* layoutStyle();
		_A_ InkStyle* inkStyle();
		
		inline WidgetState state() { return mState; }
		inline Form* form() { return mForm; }

		virtual Sheet* clone(Sheet* parent);

		virtual InkStyle* elementSkin(string clas);
		virtual LayoutStyle* elementStyle(string clas);

		virtual FrameType frameType();
		virtual size_t zorder() { return 0; }

		virtual const string& name();
		virtual const string& label();
		virtual const string& image();
		virtual const string& tooltip();
		virtual const string& hoverCursor();

		virtual RootSheet* rootWidget();
		virtual InkTarget* inkTarget();

		UiWindow* uiWindow();

		virtual void build() {}

		void bind(Sheet* parent);
		void rebind(Sheet* parent, bool insert = false, size_t index = 0);

		unique_ptr<Widget> unbind();
		unique_ptr<Widget> extract();

		void destroy();
		void detach();

		Widget* copy(Sheet* parent);

		void reset(Form* form);
		void reset(string clas);

		void nextFrame(size_t tick, size_t delta);

		void updateState(WidgetState);

		void markDirty();

		void activate();
		void deactivate();
		void hover();
		void unhover();
		void focus();
		void unfocus();

		Widget* copyTo(Sheet* sheet);

		Widget* pinpoint(float x, float y, bool opaque = true);

		Widget* prev();
		Widget* next();

		bool contains(Widget* widget);

		InputReceiver* propagateMouse(float x, float y);
		InputReceiver* propagateKey();

		bool keyUp(KeyCode code, char c) { UNUSED(code); UNUSED(c); return true; };
		bool keyDown(KeyCode code, char c) { UNUSED(code); UNUSED(c); return true; };

		bool mouseEntered(float x, float y);
		bool mouseLeaved(float x, float y);

		bool mouseMoved(float xPos, float yPos, float xDif, float yDif) { UNUSED(xPos); UNUSED(yPos); UNUSED(xDif); UNUSED(yDif); return true; };
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
		string mClas;
		unique_ptr<Frame> mFrame;
		WidgetState mState;

		Form* mForm;

		static string sNullString;
	};
}

#endif // MK_WIDGET_H_INCLUDED
