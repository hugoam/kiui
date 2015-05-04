//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_ROOTSHEET_H_INCLUDED
#define MK_ROOTSHEET_H_INCLUDED

/* mk */
#include <Object/Util/mkTimer.h>
#include <Ui/mkUiForward.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Controller/mkController.h>
#include <Ui/mkUiWindow.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkLayer.h>

namespace mk
{
	class MK_UI_EXPORT _I_ RootSheet : public Sheet, public InputController
	{
	public:
		RootSheet(UiWindow& window, bool absolute = true);
		~RootSheet();

		FrameType frameType() { return LAYER; }
		UiWindow& uiWindow() { return mWindow; }
		RootSheet& rootSheet() { return *this; }
		Layer& layer() { return mFrame->as<Layer>(); }

		Cursor* cursor() { return mCursor; }

		float lastX() { return mLastX; }
		float lastY() { return mLastY; }

		float lastPressedX() { return mLastPressedX; }
		float lastPressedY() { return mLastPressedY; }

		void nextFrame(size_t tick, size_t delta);

		void takeControl(Controller* controller);
		void stackControl(Controller* controller);
		void yieldControl(Controller* controller);

		InputReceiver* controlMouse(float x, float y);
		InputReceiver* controlKey();

		bool keyUp(KeyCode code, char c);
		bool keyDown(KeyCode code, char c);

		bool mouseMoved(float xPos, float yPos, float xDif, float yDif);
		bool mouseWheel(float xPos, float yPos, float amount);

		bool mousePressed(float xPos, float yPos, MouseButton button);
		bool mouseReleased(float xPos, float yPos, MouseButton button);

		virtual void transformCoordinates(float& xPos, float& yPos) { UNUSED(xPos); UNUSED(yPos); }

		void focus(Widget* widget);
		void unfocus(Widget* widget);

		void contextOn(Widget* contextMenu);
		void contextOff();

		void modalOn(Widget* widget);
		void modalOff();

		static StyleType& cls() { static StyleType ty("RootSheet", Sheet::cls()); return ty; }

	protected:
		UiWindow& mWindow;

		Cursor* mCursor;

		float mLastX;
		float mLastY;

		float mLastPressedX;
		float mLastPressedY;

		InputController* mController;

		bool mLeftPressed;
		float mXDragStart;
		float mYDragStart;

		Widget* mActiveFrame;
		Widget* mContextMenu;

		std::vector<Widget*> mModals;
	};
}

#endif // MK_ROOTSHEET_H_INCLUDED
