//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_EM_CONTEXT_H
#define TOY_EM_CONTEXT_H

/* toy Og */
#include <toyui/Types.h>
#include <toyui/Render/Context.h>
#include <toyui/Backend/Gl/GlRenderer.h>

#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

namespace toy
{
	class TOY_UI_EXPORT EmRenderWindow : public RenderWindow
	{
	public:
		EmRenderWindow(const string& name, int width, int height, bool autoSwap = true);

		void initContext();

		bool nextFrame();
		void resize();

	protected:
		EMSCRIPTEN_WEBGL_CONTEXT_HANDLE m_window;
	};

	class TOY_UI_EXPORT EmInputWindow : public InputWindow
	{
	public:
		EmInputWindow();

		virtual void initInput(RenderWindow& renderWindow, Mouse& mouse, Keyboard& keyboard) override;

		virtual bool nextFrame() override;

		bool injectMouseMove(const EmscriptenMouseEvent& mouseEvent);

		bool injectMouseDown(const EmscriptenMouseEvent& mouseEvent);
		bool injectMouseUp(const EmscriptenMouseEvent& mouseEvent);

		bool injectWheel(const EmscriptenWheelEvent& mouseEvent);

		bool injectKeyUp(const EmscriptenKeyboardEvent& keyEvent);
		bool injectKeyDown(const EmscriptenKeyboardEvent& keyEvent);
		bool injectKeyPress(const EmscriptenKeyboardEvent& keyEvent);

		virtual void resize(size_t width, size_t height) override;

	public:
		EmRenderWindow* m_renderWindow = nullptr;

		float m_mouseX;
		float m_mouseY;

		Mouse* m_mouse;
		Keyboard* m_keyboard;
	};

	class TOY_UI_EXPORT EmContext : public Context
	{
	public:
		EmContext(RenderSystem& renderSystem, const string& name, int width, int height, bool fullScreen);
	};

	class TOY_UI_EXPORT EmRenderSystem : public RenderSystem
	{
	public:
		EmRenderSystem(const string& resourcePath)
			: RenderSystem(resourcePath, false)
		{}

		virtual object_ptr<Context> createContext(const string& name, int width, int height, bool fullScreen)
		{
			return make_object<EmContext>(*this, name, width, height, fullScreen);
		}

		virtual object_ptr<Renderer> createRenderer(Context& context)
		{
			return make_object<GlRenderer>(m_resourcePath, true);
		}
	};
}

#endif
