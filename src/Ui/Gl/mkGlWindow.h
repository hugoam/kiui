//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#ifndef MK_NANOGL2_H
#define MK_NANOGL2_H

/* mk Og */
#include <Ui/mkUiForward.h>
#include <Ui/mkRenderWindow.h>
#include <Ui/Frame/mkRenderer.h>
#include <Ui/Input/mkInputDispatcher.h>
#include <Ui/mkUiWindow.h>

namespace mk
{
	class MK_UI_EXPORT GlRenderWindow : public RenderWindow
	{
	public:
		GlRenderWindow(const string& name, int width, int height);
		~GlRenderWindow();

		GLFWwindow* glWindow() { return m_glWindow; }

		void initContext();

		bool nextFrame();
		void resize();

	protected:
		GLFWwindow* m_glWindow;
	};

	class MK_UI_EXPORT GlInputWindow : public InputWindow
	{
	public:
		GlInputWindow(GlRenderWindow& renderWindow);
		~GlInputWindow();

		void initInput(Mouse& mouse, Keyboard& keyboard);

		bool nextFrame();

		void injectMouseMove(double x, double y);
		void injectMouseButton(int button, int action, int mods);
		void injectKey(int key, int scancode, int action, int mods);
		void injectChar(unsigned int codepoint, int mods = 0);
		void injectWheel(double x, double y);

		void resize(size_t width, size_t height);

	protected:
		GlRenderWindow& m_renderWindow;
		GLFWwindow* m_glWindow;

		float m_mouseX;
		float m_mouseY;

		Mouse* m_mouse;
		Keyboard* m_keyboard;
	};

#ifdef TOY_GL
	class MK_UI_EXPORT GlContext : public UiContext
	{
	public:
		GlContext(const string& resourcePath);

		virtual unique_ptr<RenderWindow> createRenderWindow(const string& name, int width, int height, bool fullScreen);
		virtual unique_ptr<InputWindow> createInputWindow(RenderWindow& renderWindow);
		virtual unique_ptr<Renderer> createRenderer(const string& resourcePath);

	protected:
		string m_resourcePath;
	};
#endif
}

#endif
