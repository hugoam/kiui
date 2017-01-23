//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_UIWINDOW_H
#define TOY_UIWINDOW_H

/* toy Front */
#include <toyobj/Util/Colour.h>
#include <toyobj/Util/Timer.h>
#include <toyui/Forward.h>
#include <toyui/Input/InputDevice.h>
#include <toyui/Device/RootDevice.h>
#include <toyui/RenderWindow.h>
#include <toyui/ImageAtlas.h>

#include <vector>

namespace toy
{
	class TOY_UI_EXPORT UiContext
	{
	public:
		UiContext(const string& resourcePath);

		const string& resourcePath() const { return m_resourcePath; }

		virtual unique_ptr<RenderWindow> createRenderWindow(const string& name, int width, int height, bool fullScreen) = 0;
		virtual unique_ptr<InputWindow> createInputWindow(RenderWindow& renderWindow) = 0;
		virtual unique_ptr<Renderer> createRenderer(const string& resourcePath) = 0;

	protected:
		string m_resourcePath;
	};

	class TOY_UI_EXPORT UiWindow
	{
	public:
		UiWindow(UiContext& context, const string& name, int width, int height, bool fullScreen, User* user = nullptr);
		~UiWindow();

		UiContext& context() { return m_context; }

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

		Styler& styler() const { return *m_styler; }

		bool shutdownRequested() const { return m_shutdownRequested; }
		
		User& user() const { return *m_user; }

		void init();

		void resize(size_t width, size_t height);

		bool nextFrame();

		void shutdown();

		void handleResizeWindow(size_t width, size_t height);
		void handleDestroyWidget(Widget& widget);

		Image& createImage(const string& image, int width, int height, uint8_t* data);

	protected:
		void initResources();
		void loadResources();

	protected:
		UiContext& m_context;
		string m_resourcePath;

		unique_ptr<RenderWindow> m_renderWindow;
		unique_ptr<InputWindow> m_inputWindow;
		unique_ptr<Renderer> m_renderer;

		std::vector<Image> m_images;
		ImageAtlas m_atlas;

		float m_width;
		float m_height;

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
