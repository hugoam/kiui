//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_EM_CONTEXT_H
#define TOY_EM_CONTEXT_H

/* toy Og */
#include <toyui/Types.h>
#include <toyui/RenderWindow.h>
#include <toyui/Frame/Renderer.h>
#include <toyui/Input/InputDispatcher.h>
#include <toyui/Gl/GlRenderer.h>
#include <toyui/UiWindow.h>

#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

namespace toy
{
	class TOY_UI_EXPORT EmRenderWindow : public RenderWindow
	{
	public:
		EmRenderWindow(const string& name, int width, int height, bool autoSwap = true);
		~EmRenderWindow();

		void initContext();

		bool nextFrame();
		void resize();

	protected:
		EMSCRIPTEN_WEBGL_CONTEXT_HANDLE m_window;
	};

	class TOY_UI_EXPORT EmInputWindow : public InputWindow
	{
	public:
		EmInputWindow(EmRenderWindow& renderWindow);
		~EmInputWindow();

		void initInput(Mouse& mouse, Keyboard& keyboard);

		bool nextFrame();

		bool injectMouseMove(const EmscriptenMouseEvent& mouseEvent);

		bool injectMouseDown(const EmscriptenMouseEvent& mouseEvent);
		bool injectMouseUp(const EmscriptenMouseEvent& mouseEvent);

		bool injectWheel(const EmscriptenWheelEvent& mouseEvent);

		bool injectKeyUp(const EmscriptenKeyboardEvent& keyEvent);
		bool injectKeyDown(const EmscriptenKeyboardEvent& keyEvent);
		bool injectKeyPress(const EmscriptenKeyboardEvent& keyEvent);

		void resize(size_t width, size_t height);

	protected:
		EmRenderWindow& m_renderWindow;

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
			: RenderSystem(resourcePath)
		{}

		virtual unique_ptr<Context> createContext(const string& name, int width, int height, bool fullScreen)
		{
			return make_unique<EmContext>(*this, name, width, height, fullScreen);
		}

		virtual unique_ptr<Renderer> createRenderer(Context& context)
		{
			return make_unique<GlRenderer>(m_resourcePath);
		}
	};
}

#endif
