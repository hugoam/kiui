//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toygfx/Config.h>
#include <toyui/Context/Bgfx/BgfxContext.h>

#include <toyui/UiWindow.h>
#include <toyui/Backend/Bgfx/BgfxRenderer.h>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include <bx/timer.h>

namespace toy
{
	BgfxContext::BgfxContext(BgfxSystem& gfx_system, const string& name, int width, int height, bool fullScreen, bool init)
#if TOY_PLATFORM_EMSCRIPTEN
		: EmContext(gfx_system, name, width, height, fullScreen)
#elif TOY_CONTEXT_WINDOWS
		: WinContext(gfx_system, name, width, height, fullScreen)
#else
		: GlfwContext(gfx_system, name, width, height, fullScreen, false)
#endif
	{
		if(init)
			gfx_system.init(*this);
	}

	BgfxSystem::BgfxSystem(const string& resourcePath)
		: RenderSystem(resourcePath, true)
		, m_frame(1)
		, m_initialized(false)
	{
		printf("Gfx System\n");
	}

	BgfxSystem::~BgfxSystem()
	{}

	object_ptr<Context> BgfxSystem::createContext(const string& name, int width, int height, bool fullScreen)
	{
		return make_object<BgfxContext>(*this, name, width, height, fullScreen, !m_initialized);
	}

	object_ptr<Renderer> BgfxSystem::createRenderer(Context& context)
	{
		return make_object<BgfxUiRenderer>(m_resourcePath);
	}

	UiWindow& BgfxSystem::createWindow(const string& name, int width, int height, bool fullScreen, User* user)
	{
		m_windows.emplace_back(make_object<UiWindow>(*this, name, width, height, fullScreen, user));
		return *m_windows.back();
	}

	void BgfxSystem::init(BgfxContext& context)
	{
		printf("GfxSystem: Native Handle = %p\n", context.m_renderWindow->m_nativeHandle);
		bgfx::PlatformData pd = {};
		pd.nwh = context.m_renderWindow->m_nativeHandle;
		pd.ndt = context.m_renderWindow->m_nativeTarget;
		bgfx::setPlatformData(pd);

		printf("GfxSystem: bgfx::init\n");
		bgfx::init();
		//bgfx::init(bgfx::RendererType::OpenGL);

		uint32_t width = context.m_renderWindow->m_width;
		uint32_t height = context.m_renderWindow->m_height;
		bgfx::reset(width, height, BGFX_RESET_NONE);

		bgfx::setDebug(BGFX_DEBUG_TEXT);

		bgfx::setViewRect(0, 0, 0, width, height);
		bgfx::setViewRect(255, 0, 0, width, height);

		bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x000000ff, 1.0f, 0);

		m_start_time = bx::getHPCounter();
		m_initialized = true;
	}

	bool BgfxSystem::nextFrame()
	{
		bool pursue = true;
		bgfx::touch(0);

		for(auto& window : m_windows)
			pursue &= window->nextFrame();

		m_frame = bgfx::frame();
		this->advance();

		return pursue;
	}

	void BgfxSystem::advance()
	{
		float time = float((bx::getHPCounter() - m_start_time) / double(bx::getHPFrequency()));
		m_frame_time = m_time - time;
		m_time = time;
		m_delta_time = float(m_frame_time / double(bx::getHPFrequency()));
	}
}
