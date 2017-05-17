//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_ROOTSHEET_H
#define TOY_ROOTSHEET_H

/* toy */
#include <toyobj/Util/Timer.h>
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Widget/Cursor.h>
#include <toyui/Input/InputDispatcher.h>

namespace toy
{
	class _I_ TOY_UI_EXPORT RootSheet : public Container
	{
	public:
		RootSheet(UiWindow& window, Type& type = cls());
		RootSheet(Wedge& parent, Type& type = cls());
		~RootSheet();

		virtual RootSheet& rootSheet() { return *this; }

		UiWindow& uiWindow() { return m_window; }
		ControlSwitch& controller() { return *m_rootController; }
		Mouse& mouse() const { return *m_mouse; }
		Keyboard& keyboard() const { return *m_keyboard; }

		Cursor& cursor() { return m_cursor; }

		RenderTarget& target() { return *m_target; }

		void nextFrame(size_t tick, size_t delta);

		virtual void transformCoordinates(MouseEvent& mouseEvent) { UNUSED(mouseEvent); }

		virtual void handleUnbindWidget(Widget& widget);
		virtual void handleBindWidget(Widget& widget);

		static Type& cls() { static Type ty("RootSheet", Container::cls()); return ty; }

	protected:
		UiWindow& m_window;

		unique_ptr<ControlSwitch> m_rootController;

		unique_ptr<Mouse> m_mouse;
		unique_ptr<Keyboard> m_keyboard;

		unique_ptr<RenderTarget> m_target;

		Cursor m_cursor;
	};
}

#endif // TOY_ROOTSHEET_H
