//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_BGFX_CONTEXT_H
#define TOY_BGFX_CONTEXT_H

#include <toyui/Types.h>

#if TOY_PLATFORM_EMSCRIPTEN
#include <toyui/Context/Emscripten/EmscriptenContext.h>
#elif TOY_CONTEXT_WINDOWS
#include <toyui/Context/Windows/WindowsContext.h>
#else
#include <toyui/Context/Glfw/GlfwContext.h>
#endif

namespace toy
{
	class BgfxSystem;

#if TOY_PLATFORM_EMSCRIPTEN
	class BgfxContext : public EmContext
#elif TOY_CONTEXT_WINDOWS
	class BgfxContext : public WinContext
#else
	class BgfxContext : public GlfwContext
#endif
	{
	public:
		BgfxContext(BgfxSystem& gfx_system, const string& name, int width, int height, bool fullScreen, bool init);
	};

	class TOY_GFX_EXPORT BgfxSystem : public RenderSystem
	{
	public:
		BgfxSystem(const string& resourcePath);
		~BgfxSystem();

		virtual object_ptr<Context> createContext(const string& name, int width, int height, bool fullScreen);
		virtual object_ptr<Renderer> createRenderer(Context& context);

		void init(BgfxContext& context);
		bool nextFrame();
		void advance();

		UiWindow& createWindow(const string& name, int width, int height, bool fullScreen, User* user = nullptr);

	protected:
		bool m_initialized;

		std::vector<object_ptr<UiWindow>> m_windows;

		uint32_t m_frame;
		double m_start_time;

		float m_time;
		float m_frame_time;
		float m_delta_time;
	};
}

#endif // TOY_GFXSYSTEM_H
