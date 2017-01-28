//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_ROOTSHEET_H
#define TOY_ROOTSHEET_H

/* toy */
#include <toyobj/Util/Timer.h>
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Input/InputDevice.h>
#include <toyui/Input/InputDispatcher.h>
#include <toyui/UiWindow.h>
#include <toyui/Frame/Layer.h>

namespace toy
{
	class _I_ TOY_UI_EXPORT RootSheet : public Sheet
	{
	public:
		RootSheet(UiWindow& window, StyleType& type = cls(), bool absolute = true);
		~RootSheet();

		UiWindow& uiWindow() { return m_window; }
		RootSheet& rootSheet() { return *this; }
		MasterLayer& layer() { return *m_layer; }

		Cursor& cursor() { return *m_cursor; }

		void nextFrame(size_t tick, size_t delta);

		virtual void transformCoordinates(MouseEvent& mouseEvent) { UNUSED(mouseEvent); }

		InputReceiver* dispatchEvent(InputEvent& inputEvent);

		static StyleType& cls() { static StyleType ty("RootSheet", Sheet::cls()); return ty; }

	protected:
		UiWindow& m_window;
		MasterLayer* m_layer;
		Cursor* m_cursor;
	};
}

#endif // TOY_ROOTSHEET_H
