//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_ROOTSHEET_H_INCLUDED
#define MK_ROOTSHEET_H_INCLUDED

/* mk */
#include <Object/Util/mkTimer.h>
#include <Ui/mkUiForward.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Input/mkInputDevice.h>
#include <Ui/Input/mkInputDispatcher.h>
#include <Ui/mkUiWindow.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkLayer.h>

namespace mk
{
	class MK_UI_EXPORT _I_ RootSheet : public Sheet
	{
	public:
		RootSheet(UiWindow& window, InkTarget& target, bool absolute = true);
		~RootSheet();

		FrameType frameType() { return LAYER; }
		UiWindow& uiWindow() { return m_window; }
		InkTarget& inkTarget() { return m_target; }
		RootSheet& rootSheet() { return *this; }
		Layer& layer() { return m_frame->as<Layer>(); }

		Cursor& cursor() { return *m_cursor; }

		void nextFrame(size_t tick, size_t delta);

		virtual void transformCoordinates(MouseEvent& mouseEvent) { UNUSED(mouseEvent); }

		InputReceiver* dispatchEvent(InputEvent& inputEvent);

		static StyleType& cls() { static StyleType ty("RootSheet", Sheet::cls()); return ty; }

	protected:
		UiWindow& m_window;
		InkTarget& m_target;

		Cursor* m_cursor;
	};
}

#endif // MK_ROOTSHEET_H_INCLUDED
