//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_INPUTDISPATCHER_H_INCLUDED
#define MK_INPUTDISPATCHER_H_INCLUDED

/* mk */
#include <Ui/Input/mkKeyCode.h>
#include <Ui/mkUiForward.h>

namespace mk
{
	class MK_UI_EXPORT InputWindow
	{
	public:
		virtual void initInput(InputDispatcher* dispatcher, size_t wndHandle) = 0;
		virtual void resize(size_t width, size_t height) = 0;
	};

    class MK_UI_EXPORT InputDispatcher
    {
	public:
		virtual void dispatchMousePressed(float x, float y, MouseButton button) = 0;
		virtual void dispatchMouseMoved(float x, float y, float xDif, float yDif) = 0;
		virtual void dispatchMouseReleased(float x, float y, MouseButton button) = 0;
		virtual void dispatchMouseWheeled(float x, float y, float amount) = 0;

		virtual void dispatchKeyPressed(KeyCode key, char c) = 0;
		virtual void dispatchKeyReleased(KeyCode key, char c) = 0;
    };

	class MK_UI_EXPORT InputController
	{
	public:
		virtual InputReceiver* controlMouse(float x, float y) = 0;
		virtual InputReceiver* controlKey() = 0;

		virtual void activated() {}
		virtual void deactivated() {}
	};

	class MK_UI_EXPORT InputReceiver// : public InputController
	{
	public:
		//InputReceiver* controlMouse(float x, float y) { UNUSED(x); UNUSED(y); return this; }
		//InputReceiver* controlKey() { return this; }

		virtual InputReceiver* propagateMouse(float x, float y) { UNUSED(x); UNUSED(y); return this; }
		virtual InputReceiver* propagateKey() { return this; }

		virtual bool keyUp(KeyCode code, char c) { UNUSED(code); UNUSED(c); return false; };
		virtual bool keyDown(KeyCode code, char c) { UNUSED(code); UNUSED(c); return false; };

		virtual bool mouseEntered(float xPos, float yPos) { UNUSED(xPos); UNUSED(yPos); return false; };
		virtual bool mouseLeaved(float xPos, float yPos) { UNUSED(xPos); UNUSED(yPos); return false; };

		virtual bool mouseMoved(float xPos, float yPos, float xDif, float yDif) { UNUSED(xPos); UNUSED(yPos); UNUSED(xDif); UNUSED(yDif); return false; };
		virtual bool mouseWheel(float xPos, float yPos, float amount) { UNUSED(xPos); UNUSED(yPos); UNUSED(amount); return false; };

		virtual bool mousePressed(float xPos, float yPos, MouseButton button) { UNUSED(xPos); UNUSED(yPos); UNUSED(button); return false; };
		virtual bool mouseReleased(float xPos, float yPos, MouseButton button) { UNUSED(xPos); UNUSED(yPos); UNUSED(button); return false; };

		virtual bool leftClick(float xPos, float yPos) { UNUSED(xPos); UNUSED(yPos); return false; };
		virtual bool rightClick(float xPos, float yPos) { UNUSED(xPos); UNUSED(yPos); return false; };

		virtual bool rightDragStart(float xPos, float yPos) { UNUSED(xPos); UNUSED(yPos); return false; };
		virtual bool rightDrag(float xPos, float yPos, float xDif, float yDif) { UNUSED(xPos); UNUSED(yPos); UNUSED(xDif); UNUSED(yDif); return false; };
		virtual bool rightDragEnd(float xPos, float yPos) { UNUSED(xPos); UNUSED(yPos); return false; };

		virtual bool leftDragStart(float xPos, float yPos) { UNUSED(xPos); UNUSED(yPos); return false; };
		virtual bool leftDrag(float xPos, float yPos, float xDif, float yDif) { UNUSED(xPos); UNUSED(yPos); UNUSED(xDif); UNUSED(yDif); return false; };
		virtual bool leftDragEnd(float xPos, float yPos) { UNUSED(xPos); UNUSED(yPos); return false; };
	};
}

#endif // MK_INPUTDISPATCHER_H_INCLUDED
