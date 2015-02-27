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
		virtual void mousePressed(float x, float y, MouseButton button) = 0;
		virtual void mouseMoved(float x, float y, float xDif, float yDif) = 0;
		virtual void mouseReleased(float x, float y, MouseButton button) = 0;
		virtual void mouseWheeled(float x, float y, float amount) = 0;

		virtual void keyPressed(KeyCode key, char c) = 0;
		virtual void keyReleased(KeyCode key, char c) = 0;
    };

	class MK_UI_EXPORT InputController
	{
	public:
		virtual InputReceiver* controlMouse(float x, float y) = 0;
		virtual InputReceiver* controlKey() = 0;

		virtual void activated() {}
		virtual void deactivated() {}
	};

	class MK_UI_EXPORT InputReceiver
	{
	public:
		virtual InputReceiver* propagateMouse(float x, float y) { return this; }
		virtual InputReceiver* propagateKey() { return this; }

		virtual bool keyUp(KeyCode code, char c) { return false; };
		virtual bool keyDown(KeyCode code, char c) { return false; };

		virtual bool mouseEntered(float xPos, float yPos) { return false; };
		virtual bool mouseLeaved(float xPos, float yPos) { return false; };

		virtual bool mouseMoved(float xPos, float yPos, float xDif, float yDif) { return false; };
		virtual bool mouseWheel(float xPos, float yPos, float amount) { return false; };

		virtual bool leftPressed(float xPos, float yPos) { return false; };
		virtual bool rightPressed(float xPos, float yPos) { return false; };

		virtual bool leftClick(float xPos, float yPos) { return false; };
		virtual bool rightClick(float xPos, float yPos) { return false; };

		virtual bool rightDragStart(float xPos, float yPos) { return false; };
		virtual bool rightDrag(float xPos, float yPos, float xDif, float yDif) { return false; };
		virtual bool rightDragEnd(float xPos, float yPos) { return false; };

		virtual bool leftDragStart(float xPos, float yPos) { return false; };
		virtual bool leftDrag(float xPos, float yPos, float xDif, float yDif) { return false; };
		virtual bool leftDragEnd(float xPos, float yPos) { return false; };
	};
}

#endif // MK_INPUTDISPATCHER_H_INCLUDED
