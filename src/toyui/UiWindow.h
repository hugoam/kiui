//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_UIWINDOW_H
#define TOY_UIWINDOW_H

/* toy */
#include <toyobj/Object.h>
#include <toyobj/Util/Timer.h>
#include <toyui/Types.h>
#include <toyui/ImageAtlas.h>

#include <vector>

namespace toy
{
	class _refl_ TOY_UI_EXPORT UiWindow : public Object
	{
	public:
		UiWindow(RenderSystem& system, const string& name, int width, int height, bool fullScreen, User* user = nullptr);
		~UiWindow();

		void init();
		bool nextFrame();
		void shutdown();

		void resize(size_t width, size_t height);

		void handleResizeWindow(size_t width, size_t height);

		Image& createImage(const string& image, int width, int height, uint8_t* data, bool filtering = true);
		void removeImage(Image& image);
		Image& findImage(const string& name);

	protected:
		void initResources();
		void loadResources();

	public:
		RenderSystem& m_renderSystem;
		const string m_resourcePath;

		object_ptr<Context> m_context;
		object_ptr<Renderer> m_renderer;
		RenderWindow& m_renderWindow;

		std::vector<object_ptr<Image>> m_images;
		ImageAtlas m_atlas;

		float m_width;
		float m_height;

		object_ptr<Styler> m_styler;

		object_ptr<RootSheet> m_rootSheet;
		RootDevice* m_rootDevice;

		bool m_shutdownRequested;

		Clock m_clock;

		User* m_user;
	};
}

#endif
