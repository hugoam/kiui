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
		virtual void initInput(Mouse& mouse, Keyboard& keyboard, size_t wndHandle) = 0;
		virtual void resize(size_t width, size_t height) = 0;
	};

	class MK_UI_EXPORT InputReceiver
	{
	public:
		enum ControlMode
		{
			CM_NONE,
			CM_CONTROL,
			CM_MODAL,
			CM_ABSOLUTE
		};

		virtual InputReceiver* dispatchEvent(InputEvent& inputEvent) { UNUSED(inputEvent); return this; }
		virtual InputReceiver* controlEvent(InputEvent& inputEvent) { UNUSED(inputEvent); return this; }
		virtual InputReceiver* propagateEvent(InputEvent& inputEvent) { UNUSED(inputEvent); return this; }

		virtual void takeControl(ControlMode mode) = 0;
		virtual void yieldControl() = 0;
	};

	class MK_UI_EXPORT InputFrame : public InputReceiver
	{
	public:
		InputFrame();

		InputFrame* parentFrame() { return m_parentFrame; }

		InputFrame& rootFrame();

		InputReceiver* dispatchEvent(InputEvent& inputEvent);
		InputReceiver* controlEvent(InputEvent& inputEvent);
		InputReceiver* propagateEvent(InputEvent& inputEvent);

		void setController(InputFrame& inputFrame);

		void takeControl(ControlMode mode);
		void takeControl(InputFrame& inputFrame);
		void yieldControl();

		virtual void control() {};
		virtual void uncontrol() {};

		virtual void modal() {};
		virtual void unmodal() {};

	protected:
		InputFrame* m_controller;
		InputFrame* m_controlled;
		InputFrame* m_parentFrame;
		ControlMode m_controlMode;
	};


	class MK_UI_EXPORT InputWidget : public InputFrame
	{
	public:
		InputReceiver* dispatchEvent(InputEvent& inputEvent);

		virtual void mouseMoved(MouseEvent& mouseEvent);

		virtual void mouseEntered(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };
		virtual void mouseLeaved(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };

		virtual void mousePressed(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };
		virtual void mouseReleased(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };

		virtual void mouseWheel(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };

		virtual void leftClick(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };
		virtual void rightClick(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };
		virtual void middleClick(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };

		virtual void rightDragStart(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };
		virtual void rightDrag(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };
		virtual void rightDragEnd(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };

		virtual void leftDragStart(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };
		virtual void leftDrag(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };
		virtual void leftDragEnd(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };

		virtual void middleDragStart(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };
		virtual void middleDrag(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };
		virtual void middleDragEnd(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };
	};
}

#endif // MK_INPUTDISPATCHER_H_INCLUDED
