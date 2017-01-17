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

namespace mk
{
	class MK_UI_EXPORT GlWindow : public RenderWindow, public InputWindow
	{
	public:
		GlWindow(size_t width, size_t height, string title, string resourcePath);
		~GlWindow();

		UiWindow& uiWindow() { return *m_uiWindow; }

		void initContext();
		void initInput(Mouse& mouse, Keyboard& keyboard);

		bool renderFrame();

		void injectMouseMove(double x, double y);
		void injectMouseButton(int button, int action, int mods);
		void injectKey(int key, int scancode, int action, int mods);
		void injectChar(unsigned int codepoint, int mods = 0);
		void injectWheel(double x, double y);

		void updateSize();

		void resize(size_t width, size_t height);

	protected:
		string m_resourcePath;
		unique_ptr<UiWindow> m_uiWindow;
		unique_ptr<GlRenderer> m_renderer;

		GLFWwindow* m_glWindow;

		float m_mouseX;
		float m_mouseY;

		Mouse* m_mouse;
		Keyboard* m_keyboard;
	};



}

#endif
