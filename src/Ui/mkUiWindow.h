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
#include <Ui/Device/mkRootDevice.h>
#include <Ui/mkRenderWindow.h>
#include <Ui/mkImageAtlas.h>

#include <vector>

namespace mk
{
	class MK_UI_EXPORT UiWindow
	{
	public:
		UiWindow(const string& resourcePath = "", User* user = nullptr);
		~UiWindow();

		void setup(RenderWindow& renderWindow, InputWindow& inputWindow, Renderer& renderer);
		void init();

		std::vector<Image>& images() { return m_images; }
		ImageAtlas& imageAtlas() { return m_atlas; }

		const string& resourcePath() const { return m_resourcePath; }

		float width() const { return m_width; }
		float height() const { return m_height; }

		RenderWindow& renderWindow() const { return *m_renderWindow; }
		Renderer& renderer() const { return *m_renderer; }

		RootSheet& rootSheet() const { return *m_rootSheet; }
		RootDevice& rootDevice() const { return *m_rootDevice; }

		Mouse& mouse() const { return *m_mouse; }
		Keyboard& keyboard() const { return *m_keyboard; }

		User& user() const { return *m_user; }

		Styler& styler() const { return *m_styler; }

		bool shutdownRequested() const { return m_shutdownRequested; }

		void resize(size_t width, size_t height);

		bool nextFrame();

		void shutdown();

		void handleDestroyWidget(Widget& widget);

		Image& createImage(const string& image, int width, int height, uint8_t* data);

	protected:
		void initResources();

	protected:
		string m_resourcePath;
		std::vector<Image> m_images;

		ImageAtlas m_atlas;

		float m_width;
		float m_height;

		RenderWindow* m_renderWindow;
		InputWindow* m_inputWindow;
		Renderer* m_renderer;

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
