//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_CONTROLLER_H_INCLUDED
#define MK_CONTROLLER_H_INCLUDED

/* mk */
#include <Ui/Input/mkKeyCode.h>
#include <Ui/Input/mkInputDispatcher.h>

/* std */
#include <map>
#include <vector>
#include <functional>

namespace mk
{
	class MK_UI_EXPORT Controller : public InputReceiver
	{
	public:
		Controller();
		virtual ~Controller();

		void take(Widget* widget);
		void stack(Widget* widget);
		void yield();

		void setLower(InputController* lower) { mLower = lower; }
		InputController* lower() { return mLower; }

		InputReceiver* controlMouse(float x, float y);
		InputReceiver* controlKey();

		InputReceiver* propagateMouse(float x, float y);
		InputReceiver* propagateKey();

		bool keyUp(KeyCode code, char c);
		bool keyDown(KeyCode code, char c);

	protected:
		InputController* mLower;
		Widget* mWidget;

		typedef std::function<void ()> KeyHandler;
		typedef std::map<KeyCode, KeyHandler> KeyMap;

		KeyMap keyDownHandlers;
		KeyMap keyUpHandlers;
	};
}

#endif // MK_CONTROLLER_H_INCLUDED
