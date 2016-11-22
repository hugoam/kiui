//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_UIWINDOW_H
#define MK_UIWINDOW_H

/* mk Front */
#include <Object/Util/mkColour.h>
#include <Object/Util/mkTimer.h>
#include <Ui/mkUiForward.h>
#include <Ui/Input/mkInputDevice.h>
#include <Ui/mkRenderWindow.h>

namespace mk
{
	class MK_UI_EXPORT UiWindow
	{
	public:
		UiWindow(const string& resourcePath = "", User* user = nullptr);
		~UiWindow();

		void setup(RenderWindow& renderWindow, InkWindow& inkWindow, InputWindow* inputWindow);
		void init();

		const string& resourcePath() { return m_resourcePath; }

		float width() { return m_width; }
		float height() { return m_height; }

		RenderWindow& renderWindow() { return *m_renderWindow; }
		InkWindow& inkWindow() { return *m_inkWindow; }
		RootSheet& rootSheet() { return *m_rootSheet; }
		RootDevice& rootDevice() { return *m_rootDevice; }

		Mouse& mouse() { return *m_mouse; }
		Keyboard& keyboard() { return *m_keyboard; }

		User& user() { return *m_user; }

		Styler& styler() { return *m_styler; }

		bool shutdownRequested() { return m_shutdownRequested; }

		void resize(size_t width, size_t height);

		bool nextFrame();

		void shutdown();

		void handleDestroyWidget(Widget& widget);

	protected:
		string m_resourcePath;

		float m_width;
		float m_height;

		RenderWindow* m_renderWindow;
		InkWindow* m_inkWindow;
		InputWindow* m_inputWindow;

		unique_ptr<Styler> m_styler;

		unique_ptr<RootDevice> m_rootDevice;
		unique_ptr<RootSheet> m_rootSheet;

		unique_ptr<Mouse> m_mouse;
		unique_ptr<Keyboard> m_keyboard;

		bool m_shutdownRequested;

		Clock m_clock;

		User* m_user;
	};
}

#endif
